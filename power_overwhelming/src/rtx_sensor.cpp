// <copyright file="rtx_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "rtx_sensor.h"

#include <unordered_map>

#include "sensor_array_impl.h"
#include "unique_lock.h"


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::rtx_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    auto builder = sensor_description_builder::create()
        .with_vendor(L"Rohde & Schwarz")
        .with_editable_type(sensor_type::cpu
            | sensor_type::external
            | sensor_type::gpu
            | sensor_type::system)
        .produces(reading_type::floating_point);
    std::size_t retval = 0;

#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto cnt_sensors = config.count_sensors();
    std::vector<rtx_instrument> instruments;
    auto sensors = config.sensors();

    for (std::size_t i = 0; i < cnt_sensors; ++i) {
        try {
            std::string name("Rohde & Schwarz RTx");
            const auto& sensor = sensors[i];

            // Connect to the instrument.
            auto reset = false;
            rtx_instrument instrument(reset, sensor.path(), config.timeout());
            if (reset && config.reset_on_enumerate()) {
                instrument.reset(rtx_instrument_reset::all);
            }

            // Get the friendly name of the instrument the user might have
            // configured. We use that in the friendly name of the sensor to
            // facilitate identification of the instrument.
            {
                std::vector<char> buf(instrument.name(nullptr, 0), '\0');
                if (!buf.empty()) {
                    instrument.name(buf.data(), buf.size());
                    name = buf.data();
                }
            }

            // This function tries to read the channel label in order to find
            // out whether a channel exists.
            const auto check_channel = [&instrument](const rtx_channel& c) {
                // Channels that can be measured range from 1 to 4. The
                // instrument somehow accepts channel 0, but I have no idea what
                // this channel is, so we manually reject it here.
                if (c.channel() < 1) {
                    return false;
                }

                try {
                    auto label = instrument.write("CHAN%u:LAB?\n", c.channel())
                        .read_all();
                    return !label.empty();
                } catch (...) {
                    PWROWG_TRACE("Failed to configure channel %u on instrument "
                        "\"%s\".", c.channel(), instrument.path());
                    return false;
                }
            };

            // Try to configure the voltage and current channels.
            auto& cur = sensor.current_channel();
            auto& vol = sensor.voltage_channel();
            const auto have_cur = check_channel(cur);
            const auto have_vol = check_channel(vol);

            if (have_cur) {
                if (retval < cnt) {
                    dst[retval] = builder
                        .with_path(sensor.path())
                        .with_private_data(sensor)
                        .with_id("RTX/%s/CH%u", sensor.path(), cur.channel())
                        .with_name("%s Current (CH%u)", name.c_str(),
                            cur.channel())
                        .with_type(sensor_type::current)
                        .measured_in(reading_unit::ampere)
                        .build();
                }
                ++retval;
            }

            if (have_vol) {
                if (retval < cnt) {
                    dst[retval] = builder
                        .with_path(sensor.path())
                        .with_private_data(sensor)
                        .with_id("RTX/%s/CH%u", sensor.path(), vol.channel())
                        .with_name("%s Voltage (CH%u)", name.c_str(),
                            vol.channel())
                        .with_type(sensor_type::voltage)
                        .measured_in(reading_unit::volt)
                        .build();
                }
                ++retval;
            }

#if 0
            if (have_cur && have_vol) {
                if (retval < cnt) {
                    dst[retval] = builder
                        .with_path(sensor.path())
                        .with_private_data(sensor)
                        .with_id("RTX/%s/CH%u*CH%u", sensor.path(),
                            cur.channel(), vol.channel())
                        .with_name("%s Power (CH%u * CH%u)",
                            name.c_str(), cur.channel(), vol.channel())
                        .with_type(sensor_type::power)
                        .measured_in(reading_unit::watt)
                        .build();
                }

                ++retval;
            }
#endif

            // Keep the instrument alive until the end of the method because we
            // want to reuse existing connections to the same instrument
            // whenever possible.
            instruments.push_back(std::move(instrument));
        } catch (...) {
            PWROWG_TRACE(_T("Skipping sensor due to a VISA error."));
        }
    } /* for (std::size_t i = 0; i < cnt_sensors; ++i) */
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::rtx_sensor::sample(_In_ const bool enable) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    assert(this->_trigger._impl != nullptr);

    if (enable) {
        if (!this->_thread.joinable()) {
            PWROWG_TRACE(_T("Starting the RTX sensor controller thread."));
            assert(!check_state(this->_trigger._impl->state,
                rtx_sensor_state::stop));
            this->_thread = std::thread(&rtx_sensor::control_instruments, this);
        }

    } else {
        PWROWG_TRACE(_T("Signalling the RTX sensor controller to stop."));
        set_state(this->_trigger._impl->state, rtx_sensor_state::stop);

        if (this->_thread.joinable()) {
            for (auto& i : this->_trigger._impl->instruments) {
                PWROWG_TRACE("Unlocking instrument \"%s\".", i.path());
                i.operation_complete_async();
            }

            PWROWG_TRACE(_T("Waiting for the RTX sensor controller to exit."));
            this->_thread.join();
            PWROWG_TRACE(_T("RTX sensor controller thread has exited."));
        }
    }
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor::control_instruments
 */
void PWROWG_DETAIL_NAMESPACE::rtx_sensor::control_instruments(void) {
    set_thread_name("PwrOwg RTX Sensor Controller");
#if defined(POWER_OVERWHELMING_WITH_VISA)
    assert(this->_trigger._impl != nullptr);
    auto& trigger = *this->_trigger._impl;
    auto& instruments = trigger.instruments;
    PWROWG_TRACE(_T("The RTX sensor controller thread has started."));

    while (!check_state(trigger.state, rtx_sensor_state::stop)) {
        for (auto& i : instruments) {
            try {
                if (i.wait_status(visa_event_status::operation_complete)) {
                    //i.data(rtx_waveform_points::maximum)
                }
            } catch (...) {}

            //if (!i.wait(VI_EVENT_TRIG, 1000)) {
            //    continue;
            //}
        }

        //PWROWG_NAMED_UNIQUE_LOCK(lock, trigger.lock);
        //if (!check_state(trigger.state, rtx_sensor_state::passive)) {
        //    PWROWG_TRACE(_T("RTX sensor controller waits to be signalled."));
        //    trigger.condition.wait(lock);
        //}

        //if (check_state(trigger.state, rtx_sensor_state::stop)) {
        //    PWROWG_TRACE(_T("RTX sensor controller thread is stopping."));
        //    trigger.state = rtx_sensor_state::running;
        //    return;
        //}

        //if (check_state(trigger.state, rtx_sensor_state::trigger)) {
        //    if (trigger.external_trigger) {
        //        PWROWG_TRACE(_T("Triggering by raising parallel port pins %u ")
        //            _T("for %u ms."), trigger.external_trigger_pins,
        //            trigger.external_trigger_duration);
        //        trigger.external_trigger.pulse(
        //            trigger.external_trigger_pins,
        //            trigger.external_trigger_duration);

        //    } else if (this->_trigger_index < this->_instruments.size()) {
        //        PWROWG_TRACE(_T("Triggering manually via daisy chain."));
        //        assert(trigger.daisy_chain > 0.0f);
        //        this->_instruments[this->_trigger_index].acquisition(
        //            rtx_acquisition_state::single);

        //    } else {
        //        PWROWG_TRACE(_T("Triggering all instruments manually."));
        //        for (auto& i : this->_instruments) {
        //            i.acquisition(rtx_acquisition_state::single);
        //        }
        //    }
        //}



        //if (check_state(trigger.state, rtx_sensor_state::)) {
        //    PWROWG_TRACE(_T("RTX sensor controller thread is stopping."));
        //    return;
        //})
    }
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
}


#if false
#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/timestamp.h"

#include "rtx_sampler.h"
#include "rtx_sensor_impl.h"
#include "string_functions.h"
#include "tokenise.h"
#include "visa_library.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Determines the list of unique instruments for the
    /// <see cref="rtx_sensor" />s in the given range.
    /// </summary>
    template<class TIterator>
    std::vector<rtx_instrument *> unique_instruments(TIterator begin,
            TIterator end) {
        std::vector<rtx_instrument *> retval;
        retval.reserve(std::distance(begin, end));

        for (auto it = begin; it != end; ++it) {
            const auto instrument = it->instrument();
            const auto unique = std::none_of(retval.begin(), retval.end(),
                    [instrument](rtx_instrument *i) {
                return instrument->alias_of(*i);
            });

            if (unique) {
                retval.push_back(instrument);
            }
        }

        return retval;
    }

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */


/*
 * visus::power_overwhelming::rtx_sensor::configure_instrument
 */
_Ret_maybenull_
visus::power_overwhelming::rtx_instrument *
visus::power_overwhelming::rtx_sensor::configure_instrument(
    _In_reads_(cnt) rtx_sensor *sensors,
    _In_ const std::size_t cnt,
    _In_ const rtx_instrument_configuration& configuration) {
    if ((sensors == nullptr) || (cnt < 1)) {
        throw std::invalid_argument("The list of sensors to configure the "
            "instrument for must not be empty.");
    }
    if (configuration.slave()) {
        throw std::invalid_argument("The configuration provided must not "
            "be a configuration for a slave instrument.");
    }

    // Compile a list of unique instruments used by any of the sensors.
    auto instruments = detail::unique_instruments(sensors, sensors + cnt);

    // Apply the master configuration to the first instrument and a slave
    // configuration derived from it on all subsequent ones.
    auto master = true;
    auto slave_config = configuration.as_slave();

    for (auto i : instruments) {
        if (master) {
            master = false;
            configuration.apply(*i);
        } else {
            slave_config.apply(*i);
        }
    }

    return instruments.empty() ? nullptr : instruments.front();
}


/*
 * visus::power_overwhelming::rtx_sensor::for_all
 */
std::size_t visus::power_overwhelming::rtx_sensor::for_all(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) rtx_sensor *dst,
        _In_ std::size_t cnt,
        _In_ const visa_instrument::timeout_type time_range,
        _In_ const unsigned int samples,
        _In_ const waveform_decimation_method decimation_method,
        _In_ const visa_instrument::timeout_type timeout) {
    std::vector<rtx_sensor_definition> definitions;
    auto retval = rtx_sensor::get_definitions(nullptr, 0);

    if (dst != nullptr) {
        definitions.resize(retval);
        rtx_sensor::get_definitions(definitions.data(), definitions.size());

        for (std::size_t i = 0; (i < retval) && (i < cnt); ++i) {
            dst[i] = rtx_sensor(definitions[i], decimation_method, timeout);
        }

        // Configure the instruments using a mostly default configuration. If
        // the user-defined timeout is less than twice the range of the
        // acquisition, increase the timeout, because we want to be able to
        // safely wait for the acquisition to complete.
        rtx_instrument_configuration config(
            rtx_quantity(time_range, "ms"),
            (std::max)(timeout, 2 * time_range),
            samples);
        configure_instrument(dst, cnt, config);
    }

    return retval;
}


/*
 * visus::power_overwhelming::rtx_sensor::get_definitions
 */
std::size_t visus::power_overwhelming::rtx_sensor::get_definitions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) rtx_sensor_definition *dst,
        _In_ const std::size_t cnt,
        _In_ const rtx_channel& voltage_channel,
        _In_ const rtx_channel& current_channel,
        _In_ const std::size_t force_channels,
        _In_ const visa_instrument::timeout_type timeout) {
    // Search the instruments using VISA.
    std::string query("?*::");                      // Any protocol
    query += visa_instrument::rohde_und_schwarz;    // Only R&S
    query += "::";
    query += rtx_instrument::product_id;            // Only RTA/RTB
    query += "::?*::INSTR";                         // All serial numbers

    const auto devices = detail::visa_library::instance().find_resource(
        query.c_str());

    // Count the total number of sensors we can form from the instruments.
    // Furthermore, remember the number of sensors we can create on each of
    // instruments such that we do not have to count again later, as this
    // is a trial-and-error operation that is rather expensive.
    auto retval = 0;
    std::vector<std::size_t> sensors;
    sensors.reserve(devices.size());

    if (force_channels == 0) {
        // Probe the channels on each instrument to determine the overall
        // number of sensors we can create.
        for (auto& d : devices) {
            auto i = rtx_instrument::create_and_reset_new(d.c_str(), timeout);
            sensors.push_back(i.channels() / 2);
            retval += sensors.back();
        }

    } else {
        // We just assume that the user is right, so every instrument has the
        // same number of channels.
        std::fill_n(std::back_inserter(sensors), devices.size(),
            force_channels / 2);
        retval = devices.size() * force_channels / 2;
    }

    // Create the sensor definitions.
    if (dst != nullptr) {
        for (std::size_t i = 0, d = 0; d < devices.size(); ++d) {
            const auto path = convert_string<wchar_t>(devices[d]);

            for (std::size_t s = 0; (i < cnt) && (s < sensors[d]); ++s, ++i) {
                const auto cv = 2 * s + 1;
                const auto cc = cv + 1;
                const auto desc = path + L" (" + std::to_wstring(cv)
                    + L"+" + std::to_wstring(cc) + L")";
                dst[i] = rtx_sensor_definition(path.c_str(),
                    rtx_channel(cv, voltage_channel),
                    rtx_channel(cc, current_channel),
                    desc.c_str());
            }
        }
    }

    return retval;
}


/*
 * visus::power_overwhelming::rtx_sensor::get_definitions
 */
std::size_t visus::power_overwhelming::rtx_sensor::get_definitions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) rtx_sensor_definition *dst,
        _In_ const std::size_t cnt,
        _In_ const float voltage_attenuation,
        _In_ const float current_attenuation,
        _In_ const std::size_t force_channels,
        _In_ const visa_instrument::timeout_type timeout) {
    const rtx_quantity ca(current_attenuation, "A");
    const rtx_quantity va(voltage_attenuation, "V");
    return get_definitions(dst, cnt,
        rtx_channel().attenuation(va).state(true),
        rtx_channel().attenuation(ca).state(true),
        force_channels,
        timeout);
}


/*
 * visus::power_overwhelming::rtx_sensor::sample
 */
visus::power_overwhelming::rtx_sample
visus::power_overwhelming::rtx_sensor::sample(
        _In_ const rtx_instrument& device) {
    device.acquisition(rtx_acquisition_state::single, true);
    throw "TODO";

    return rtx_sample();
}


/*
 * visus::power_overwhelming::rtx_sensor::rtx_sensor
 */
visus::power_overwhelming::rtx_sensor::rtx_sensor(void) : _impl(nullptr) { }


/*
 * visus::power_overwhelming::rtx_sensor::rtx_sensor
 */
visus::power_overwhelming::rtx_sensor::rtx_sensor(
        _In_ const rtx_sensor_definition& definition,
        _In_ const waveform_decimation_method decimation_method,
        _In_ const visa_instrument::timeout_type timeout,
        _In_opt_ const rtx_instrument_configuration *instrument_config)
    : _impl(new detail::rtx_sensor_impl(definition.path(), timeout,
        &rtx_sensor::configure_new,
        const_cast<rtx_instrument_configuration *>(instrument_config))) {
    this->_impl->decimation_method = decimation_method;
    this->initialise(definition, timeout);
}


/*
 * visus::power_overwhelming::rtx_sensor::rtx_sensor
 */
visus::power_overwhelming::rtx_sensor::rtx_sensor(
        _Inout_ rtx_sensor&& rhs) noexcept
        : _impl(rhs._impl) {
    rhs._impl = nullptr;
}


/*
 * visus::power_overwhelming::rtx_sensor::~rtx_sensor
 */
visus::power_overwhelming::rtx_sensor::~rtx_sensor(void) noexcept {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::rtx_sensor::acquire
 */
visus::power_overwhelming::measurement_data_series
visus::power_overwhelming::rtx_sensor::acquire(void) const {
    const auto begin = power_overwhelming::timestamp::now();
    auto& instrument = this->check_not_disposed();
    assert(this->_impl != nullptr);
    assert(instrument == true);

    instrument.acquisition(rtx_acquisition_state::single, true);
    // If the acquisition before succeeded, the instrument must be valid and
    // therefore the sensor should be valid as well (and have a name).
    assert(this->name() != nullptr);

    // Download the data from the instrument.
    const auto current = instrument.data(this->_impl->channel_current,
        rtx_waveform_points::maximum);
    const auto voltage = instrument.data(this->_impl->channel_voltage,
        rtx_waveform_points::maximum);

    // Convert the two waveforms into a data series.
    assert(current.record_length() == voltage.record_length());
    measurement_data_series retval(this->name());
    auto dst = measurement_data_series::resize(retval, current.record_length());
    const auto dist = std::chrono::duration<float>(current.sample_distance());

    for (std::size_t i = 0; i < current.record_length(); ++i) {
        throw "TODO";
        //dst[i] = measurement_data(
        //    begin.value() + (i * dist),
        //    voltage.sample(i),
        //    current.sample(i));
    }

    return retval;
}


/*
 * visus::power_overwhelming::rtx_sensor::channel_current
 */
visus::power_overwhelming::rtx_instrument::channel_type
visus::power_overwhelming::rtx_sensor::channel_current(void) const noexcept {
    this->check_not_disposed();
    return this->_impl->channel_current;
}


/*
 * visus::power_overwhelming::rtx_sensor::channel_voltage
 */
visus::power_overwhelming::rtx_instrument::channel_type
visus::power_overwhelming::rtx_sensor::channel_voltage(void) const noexcept {
    this->check_not_disposed();
    return this->_impl->channel_voltage;
}


/*
 * visus::power_overwhelming::rtx_sensor::decimation_method
 */
visus::power_overwhelming::waveform_decimation_method
visus::power_overwhelming::rtx_sensor::decimation_method(void) const noexcept {
    this->check_not_disposed();
    return this->_impl->decimation_method;
}


/*
 * visus::power_overwhelming::rtx_sensor::instrument
 */
_Ret_maybenull_ visus::power_overwhelming::rtx_instrument *
visus::power_overwhelming::rtx_sensor::instrument(void) noexcept {
    return (this->_impl != nullptr)
        ? std::addressof(this->_impl->instrument)
        : nullptr;
}


/*
 * visus::power_overwhelming::rtx_sensor::instrument
 */
_Ret_maybenull_ const visus::power_overwhelming::rtx_instrument *
visus::power_overwhelming::rtx_sensor::instrument(void) const noexcept {
    return (this->_impl != nullptr)
        ? std::addressof(this->_impl->instrument)
        : nullptr;
}


/*
 * *visus::power_overwhelming::rtx_sensor::name
 */
_Ret_maybenull_z_ const wchar_t *visus::power_overwhelming::rtx_sensor::name(
        void) const noexcept {
    return (this->_impl != nullptr)
        ? this->_impl->sensor_name.c_str()
        : nullptr;
}


/*
 * visus::power_overwhelming::rtx_sensor::path
 */
_Ret_maybenull_z_ const char *visus::power_overwhelming::rtx_sensor::path(
        void) const noexcept {
    return (this->_impl != nullptr)
        ? this->_impl->instrument.path()
        : nullptr;
}


/*
 * visus::power_overwhelming::rtx_sensor::operator =
 */
visus::power_overwhelming::rtx_sensor&
visus::power_overwhelming::rtx_sensor::operator =(
        _Inout_ rtx_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        delete this->_impl;
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::rtx_sensor::operator bool
 */
visus::power_overwhelming::rtx_sensor::operator bool(void) const noexcept {
    return ((this->_impl != nullptr) && this->_impl->instrument);
}


/*
 * visus::power_overwhelming::rtx_sensor::sample_async
 */
void visus::power_overwhelming::rtx_sensor::sample_async(
        _Inout_ async_sampling&& sampling) {
    assert(*this == true);
    this->_impl->async_sampling = std::move(sampling);

    if (this->_impl->async_sampling) {
        detail::rtx_sampler::default_sampler.add(this->path(), this->_impl);
    } else {
        detail::rtx_sampler::default_sampler.remove(this->_impl);
    }
}



/*
 * visus::power_overwhelming::rtx_sensor::sample_sync
 */
visus::power_overwhelming::measurement_data
visus::power_overwhelming::rtx_sensor::sample_sync(void) const {
    assert(*this == true);
    return decimate(this->acquire(), this->_impl->decimation_method);
}


/*
 * visus::power_overwhelming::rtx_sensor::configure_new
 */
void visus::power_overwhelming::rtx_sensor::configure_new(
        _In_ rtx_instrument& instrument, _In_opt_ void *configuration) {
    if (configuration != nullptr) {
        auto c = static_cast<rtx_instrument_configuration *>(configuration);
        c->apply(instrument);
    }
}


/*
 * visus::power_overwhelming::rtx_sensor::decimate
 */
visus::power_overwhelming::measurement_data
visus::power_overwhelming::rtx_sensor::decimate(
        _In_ const measurement_data_series& series,
        _In_ const waveform_decimation_method method) {
    switch (method) {
        case waveform_decimation_method::first:
            return series.front();

        case waveform_decimation_method::last:
            return series.back();

        case waveform_decimation_method::mean: {
            const auto t = (series.back().timestamp()
                - series.front().timestamp()) / 2;

            auto c = 0.0f;
            auto v = 0.0f;

            for (std::size_t i = 0; i < series.size(); ++i) {
                auto& s = series.sample(i);
                c += (s.current() - c) / (i + 1);
                v += (s.voltage() - v) / (i + 1);
            }

            return measurement_data(timestamp(t.count()), v, c);
            }

        case waveform_decimation_method::middle:
            return series.sample(series.size() / 2);

        case waveform_decimation_method::rms:
        default: {
            const auto begin = series.front().timestamp();
            const auto t = begin + (series.back().timestamp() - begin) / 2;
            auto c = 0.0f;
            auto v = 0.0f;

            for (std::size_t i = 0; i < series.size(); ++i) {
                auto& s = series.sample(i);
                c += (s.current() * s.current() - c) / (i + 1);
                v += (s.voltage() * s.voltage() - v) / (i + 1);
            }

            c = std::sqrt(c);
            v = std::sqrt(v);

            return measurement_data(timestamp(t), v, c);
            }
    }
}


/*
 * visus::power_overwhelming::rtx_sensor::check_not_disposed
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_sensor::check_not_disposed(void) {
    sensor::check_not_disposed();
    assert(this->_impl != nullptr);
    return this->_impl->instrument;
}


/*
 * visus::power_overwhelming::rtx_sensor::check_not_disposed
 */
const visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_sensor::check_not_disposed(void) const {
    sensor::check_not_disposed();
    assert(this->_impl != nullptr);
    return this->_impl->instrument;
}


/*
 * visus::power_overwhelming::rtx_sensor::initialise
 */
void visus::power_overwhelming::rtx_sensor::initialise(
        _In_ const rtx_sensor_definition& definition,
        _In_ const visa_instrument::timeout_type timeout) {
    if (!definition) {
        throw std::invalid_argument("The RTA/RTB sensor definition provided "
            "to the constructor was invalid. Make sure to use only sensor "
            "definitions that describe a valid oscilloscope and configure "
            "the appropriate channels for voltage and current.");
    }
    if (definition.channel_current() == definition.channel_voltage()) {
        throw std::invalid_argument("The RTA/RTB sensor definition tries to "
            "use the same channel for voltage and current.");
    }

    auto& instrument = this->check_not_disposed();
    assert(this->_impl != nullptr);
    assert(instrument == true);

    // Set the connection timeout as VISA timeout as well.
    instrument.timeout(timeout);

    // Compose the name of the sensor.
    std::vector<char> id(instrument.identify(nullptr, 0));
    instrument.identify(id.data(), id.size());

    auto& name = this->_impl->sensor_name;
    name = convert_string<wchar_t>(id.data());
    name += L"/CH" + std::to_wstring(definition.channel_voltage());
    name += L"+CH" + std::to_wstring(definition.channel_current());

    // Make sure that time on instrument is in sync.
    instrument.synchronise_clock().operation_complete();

    // Configure the channels. We wait separately to reduce the probability
    // of a timeout.
    instrument.channel(definition.current_channel()).operation_complete();
    instrument.channel(definition.voltage_channel()).operation_complete();

    // Remember the channel indices such that we can download the data.
    this->_impl->channel_current = definition.channel_current();
    this->_impl->channel_voltage = definition.channel_voltage();
}
#endif
