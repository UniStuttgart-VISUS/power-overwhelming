// <copyright file="rtx_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "rtx_sensor.h"

#include <algorithm>
#include <unordered_map>

#include "sensor_array_impl.h"
#include "unique_lock.h"


#if defined(POWER_OVERWHELMING_WITH_VISA)
PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Generates a timestamp for a <paramref name="sample" /> in the given
/// <paramref name="waveform" /> based on the trigger timestamp recorded
/// for the given <paramref name="instrument" />.
/// </summary>
static timestamp get_instrument_timestamp(
        _In_ const rtx_waveform& waveform,
        _In_ const std::size_t sample,
        _In_ const rtx_sensor_trigger_impl& trigger,
        _In_ const std::size_t instrument) {
    typedef std::chrono::duration<float> instrument_duration;
    assert(sample < waveform.size());
    assert(instrument < trigger.instruments.size());
    const instrument_duration offset(waveform.sample_time(sample));
    return trigger.trigger_timestamps[instrument] + offset;
}


/// <summary>
/// Generates a timestamp for a <paramref name="sample" /> in the given
/// <paramref name="waveform" /> based on the trigger timestamp.
/// </summary>
static timestamp get_software_timestamp(
        _In_ const rtx_waveform& waveform,
        _In_ const std::size_t sample,
        _In_ const rtx_sensor_trigger_impl& trigger,
        _In_ const std::size_t) {
    typedef std::chrono::duration<float> instrument_duration;
    assert(sample < waveform.size());
    assert(!trigger.instruments.empty());
    const instrument_duration offset(waveform.sample_time(sample));
    return trigger.trigger_timestamps.front() + offset;
}


/// <summary>
/// Gets the instrument-generated timestamp for a <paramref name="sample" /> in
/// the given <paramref name="waveform" />.
/// </summary>
static timestamp get_waveform_timestamp(
        _In_ const rtx_waveform& waveform,
        _In_ const std::size_t sample,
        _In_ const rtx_sensor_trigger_impl&,
        _In_ const std::size_t) {
    return waveform.sample_timestamp(sample);
}

PWROWG_DETAIL_NAMESPACE_END
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::rtx_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    auto builder = sensor_description_builder::create()
        .with_vendor(L"Rohde & Schwarz")
        .with_class(configuration_type::id)
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
            rtx_instrument instrument(reset, sensor.path(),
                config.base_configuration().timeout());
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
    auto& trigger = *this->_trigger._impl;

    if (enable) {
        if ((atomic_set(trigger.state, sensor_trigger_state::running)
                & sensor_trigger_state::running)
                != sensor_trigger_state::running) {
            PWROWG_TRACE(_T("Starting the RTX sensor controller thread."));
            this->_thread = std::thread(&rtx_sensor::control_instruments, this);
        }

    } else {
        PWROWG_TRACE(_T("Signalling the RTX sensor controller to stop."));
        atomic_unset(trigger.state, sensor_trigger_state::running
            | sensor_trigger_state::armed);

        PWROWG_TRACE(_T("Making sure that the controller thread is not ")
            _T("working on the instruments anymore before injecting an OPC to ")
            _T("wake it up."));
        spin_while_all(trigger.state, sensor_trigger_state::busy);

#if false
        while (this->_thread.joinable()) {
            for (auto& i : trigger.instruments) {
                PWROWG_TRACE("Unlocking instrument \"%s\".", i.path());
                i.operation_complete_async();
            }
            std::this_thread::yield();
        }
#else 
        if (this->_thread.joinable()) {
            for (auto& i : trigger.instruments) {
                PWROWG_TRACE("Unlocking instrument \"%s\".", i.path());
                i.operation_complete_async();
            }

            PWROWG_TRACE(_T("Waiting for the RTX sensor controller to exit, ")
                _T("because the contract of sample requires them method not ")
                _T("to return until all pending samples have been delivered."));
            this->_thread.join();
        }
#endif
    }
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor::control_instruments
 */
void PWROWG_DETAIL_NAMESPACE::rtx_sensor::control_instruments(void) {
    set_thread_name("PwrOwg RTX Sensor Controller");
#if defined(POWER_OVERWHELMING_WITH_VISA)
    constexpr auto opc = visa_event_status::operation_complete;
    assert(this->_trigger._impl != nullptr);

    std::vector<PWROWG_NAMESPACE::sample> samples;
    auto& trigger = *this->_trigger._impl;
    auto& instruments = trigger.instruments;
    PWROWG_TRACE(_T("The RTX sensor controller thread has started."));

    while (check_all(trigger.state, sensor_trigger_state::running)) {
        auto source = this->_index;

        for (std::size_t i = 0; i < instruments.size(); ++i) {
            assert(i < this->_channels.size());
            auto& instrument = instruments[i];

            try {
                PWROWG_TRACE("Waiting for \"%s\" to complete an acquisition "
                    "started from the RTX sensor trigger.", instrument.path());
                if (!instrument.wait_status(opc)) {
                    assert(false);
                    continue;
                }

                // Delete the armed state and set the busy state. If the armed
                // state was not set before that, the previous instrument must
                // have already set the busy state.
                const auto prev_state = atomic_change(trigger.state,
                    sensor_trigger_state::busy,
                    sensor_trigger_state::armed);
                if ((prev_state & sensor_trigger_state::running)
                        != sensor_trigger_state::running) {
                    PWROWG_TRACE(_T("Termination of the RTX sensor thread ")
                        _T("was requested while waiting for data."));
                    break;
                };

                PWROWG_TRACE(_T("The RTX controller thread is processing the ")
                    _T("latest waveforms."));
                std::map<rtx_channel::channel_type, rtx_waveform> waveforms;
                for (std::size_t c = 0; c < this->_channels[i].size(); ++c) {
                    const auto& chan = this->_channels[i][c];
                    const auto src = source + c;
                    this->make_samples(samples, src, i, chan, waveforms);
                    assert(!samples.empty());
                    PWROWG_TRACE("Delivering %zu samples from instrument "
                        "\"%s\". ", samples.size(), instrument.path());
                    sensor_array_impl::callback(this->_owner, samples.data(),
                        samples.size());
                }
            } catch (const std::exception& ex) {
                PWROWG_TRACE("An error occurred while processing waveforms "
                    "from instrument \"%s\": %s", instrument.path(), ex.what());
                if (!trigger.when_failed(std::current_exception(),
                        trigger.when_failed_context)) {
                    throw;
                }
            }

            // This line makes sure that the sensor offset for subsequent
            // instruments is correct even if one of the them has failed.
            source += this->_channels[i].size();
        } /* for (std::size_t i = 0; i < instruments.size(); ++i) */

        PWROWG_TRACE(_T("The RTX controller thread is done processing the ")
            _T("latest waveforms."));
        atomic_unset(trigger.state, sensor_trigger_state::busy);
        trigger.when_done(trigger.when_done_context);
    } /* while (!check_state(trigger.state, sensor_trigger_state::stop)) */

    PWROWG_TRACE(_T("The RTX sensor controller thread is exiting."));
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
}


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor::make_samples
 */
std::vector<PWROWG_NAMESPACE::sample>&
PWROWG_DETAIL_NAMESPACE::rtx_sensor::make_samples(
        _Inout_ std::vector<PWROWG_NAMESPACE::sample>& samples,
        _In_ const PWROWG_NAMESPACE::sample::source_type source,
        _In_ const std::size_t instrument,
        _In_ const sensor_channel& channel,
        _Inout_ std::map<rtx_channel::channel_type, rtx_waveform>& cache) {
    assert(this->_trigger._impl != nullptr);
    auto& trigger = *this->_trigger._impl;
    assert(instrument < trigger.instruments.size());
    auto& inst = trigger.instruments[instrument];

    // Generates the timestamp for the given 'sample', either from the cached
    // trigger timestamp or from the waveform itself as a fallback.
    timestamp (*get_timestamp)(const rtx_waveform&, const std::size_t,
            const rtx_sensor_trigger_impl&, const std::size_t)
        = (instrument < trigger.trigger_timestamps.size())
        ? detail::get_instrument_timestamp
        : !trigger.trigger_timestamps.empty()
        ? detail::get_software_timestamp
        : detail::get_waveform_timestamp;

    // Gets the waveform for the given channel 'c', preferably from the 'cache'.
    const auto get_waveform = [this, &inst, &cache](
            const rtx_channel::channel_type& c) -> rtx_waveform& {
        auto& retval = cache[c];

        if (retval.empty()) {
            PWROWG_TRACE(_T("Channel %u was not cached."), c);
            retval = inst.data(
                c,
                rtx_waveform_points::maximum,
                this->_download_timeout,
                this->_download_retries);
        }

        return retval;
    };

    if (channel.current == 0) {
        PWROWG_TRACE(_T("Sample single-channel sensor on %u."),
            channel.channel);
        auto& waveform = get_waveform(channel.channel);

        samples.resize(waveform.size());
        assert(samples.size() == waveform.size());

        for (std::size_t s = 0; s < samples.size(); ++s) {
            // TODO: unit?
            const auto t = get_timestamp(waveform, s, trigger, instrument);
            const auto v = waveform.sample(s);
            samples[s] = PWROWG_NAMESPACE::sample(source, t, v);
        }

    } else {
        PWROWG_TRACE(_T("Sample power sensor on %u, %u."), channel.channel,
            channel.current);
        auto& voltage = get_waveform(channel.channel);
        auto& current = get_waveform(channel.current);

        samples.resize(voltage.size());
        assert(samples.size() == voltage.size());
        assert(samples.size() == current.size());

        for (std::size_t s = 0; s < samples.size(); ++s) {
            // TODO: unit?
            const auto t = get_timestamp(voltage, s, trigger, instrument);
            const auto v = voltage.sample(s) * current.sample(s);
            samples[s] = PWROWG_NAMESPACE::sample(source, t, v);
        }
    }

    return samples;
}
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
