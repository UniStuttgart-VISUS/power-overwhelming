// <copyright file="rtx_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/rtx_sensor.h"

#include <algorithm>
#include <cassert>
#include <limits>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include "power_overwhelming/convert_string.h"

#include "string_functions.h"
#include "timestamp.h"
#include "tokenise.h"
#include "visa_library.h"


/*
 * visus::power_overwhelming::rtx_sensor::configure_instrument
 */
visus::power_overwhelming::rtx_instrument&
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
    std::vector<rtx_instrument *> instruments;
    for (std::size_t i = 0; i < cnt; ++i) {
        const auto ii = std::addressof(sensors[i]._instrument);
        if (std::none_of(instruments.begin(), instruments.end(),
                [ii](rtx_instrument *ij) { return ii->alias_of(*ij); })) {
            instruments.push_back(ii);
        }
    }

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

    return **(instruments.begin());
}


/*
 * visus::power_overwhelming::rtx_sensor::for_all
 */
std::size_t visus::power_overwhelming::rtx_sensor::for_all(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) rtx_sensor *dst,
        _In_ std::size_t cnt,
        _In_ const visa_instrument::timeout_type time_range,
        _In_ const visa_instrument::timeout_type timeout) {
    std::vector<rtx_sensor_definition> definitions;
    auto retval = rtx_sensor::get_definitions(nullptr, 0);

    if (dst != nullptr) {
        definitions.resize(retval);
        rtx_sensor::get_definitions(definitions.data(), definitions.size());

        for (std::size_t i = 0; (i < retval) && (i < cnt); ++i) {
            dst[i] = rtx_sensor(definitions[i], timeout);
        }

        // Configure the instruments using a mostly default configuration. If
        // the user-defined timeout is less than twice the range of the
        // acquisition, increase the timeout, because we want to be able to
        // safely wait for the acquisition to complete.
        rtx_instrument_configuration config(
            oscilloscope_quantity(time_range, "ms"),
            (std::max)(timeout, 2 * time_range));
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
        _In_ const oscilloscope_channel& voltage_channel,
        _In_ const oscilloscope_channel& current_channel,
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
                    oscilloscope_channel(cv, voltage_channel),
                    oscilloscope_channel(cc, current_channel),
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
    const oscilloscope_quantity ca(current_attenuation, "A");
    const oscilloscope_quantity va(voltage_attenuation, "V");
    return get_definitions(dst, cnt,
        oscilloscope_channel().attenuation(va).state(true),
        oscilloscope_channel().attenuation(ca).state(true),
        force_channels,
        timeout);
}


/*
 * visus::power_overwhelming::rtx_sensor::rtx_sensor
 */
visus::power_overwhelming::rtx_sensor::rtx_sensor(
        _In_ const rtx_sensor_definition& definition,
        _In_ const visa_instrument::timeout_type timeout)
    : _channel_current(0), _channel_voltage(0), _instrument(
        rtx_instrument::create_and_reset_new(definition.path(), timeout)) {
    this->initialise(definition, timeout);
}


/*
 * visus::power_overwhelming::rtx_sensor::acquire
 */
visus::power_overwhelming::measurement_data_series
visus::power_overwhelming::rtx_sensor::acquire(
        _In_ const timestamp_resolution resolution) {
    const auto begin = detail::create_timestamp(resolution);
    this->_instrument.acquisition(oscilloscope_acquisition_state::single, true);
    assert(this->name() != nullptr);

    // Download the data from the instrument.
    const auto current = this->_instrument.data(this->_channel_current,
        oscilloscope_waveform_points::maximum);
    const auto voltage = this->_instrument.data(this->_channel_voltage,
        oscilloscope_waveform_points::maximum);

    // Convert the two waveforms into a data series.
    assert(current.record_length() == voltage.record_length());
    measurement_data_series retval(this->name());
    auto dst = measurement_data_series::resize(retval, current.record_length());
    const auto dist = std::chrono::duration<float>(current.sample_distance());
    const auto dt = detail::convert(dist, resolution);
    assert(dt > 0);

    for (std::size_t i = 0; i < current.record_length(); ++i) {
        dst[i] = measurement_data(begin + i * dt,
            voltage.sample(i),
            current.sample(i));
    }

    return retval;
}


/*
 * *visus::power_overwhelming::rtx_sensor::name
 */
_Ret_maybenull_z_
const wchar_t *visus::power_overwhelming::rtx_sensor::name(
        void) const noexcept {
    return this->_name.as<wchar_t>();
}


/*
 * visus::power_overwhelming::rtx_sensor::operator bool
 */
visus::power_overwhelming::rtx_sensor::operator bool(void) const noexcept {
    return static_cast<bool>(this->_instrument);
}


/*
 * visus::power_overwhelming::rtx_sensor::sample_sync
 */
visus::power_overwhelming::measurement_data
visus::power_overwhelming::rtx_sensor::sample_sync(
        _In_ const timestamp_resolution resolution) const {
    throw "TODO";

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

    // Set the connection timeout as VISA timeout as well.
    this->_instrument.timeout(timeout);

    // Compose the name of the sensor.
    std::vector<char> id(this->_instrument.identify(nullptr, 0));
    this->_instrument.identify(id.data(), id.size());

    auto name = convert_string<wchar_t>(id.data());
    name += L"/CH" + std::to_wstring(definition.channel_voltage());
    name += L"+CH" + std::to_wstring(definition.channel_current());
    detail::safe_assign(this->_name, name);

    // Make sure that time on instrument is in sync.
    this->_instrument.synchronise_clock()
        .operation_complete();

    // Configure the channels. We wait separately to reduce the probability
    // of a timeout.
    this->_instrument.channel(definition.current_channel())
        .operation_complete();
    this->_instrument.channel(definition.voltage_channel())
        .operation_complete();

    // Remember the channel indices such that we can download the data.
    this->_channel_current = definition.channel_current();
    this->_channel_voltage = definition.channel_voltage();
}
