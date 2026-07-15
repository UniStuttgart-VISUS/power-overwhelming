// <copyright file="daqmx_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "daqmx_sensor.h"

#include "visus/pwrowg/trace.h"


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::daqmx_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    auto builder = sensor_description_builder::create()
        .with_vendor(L"National Instruments")
        .with_class(configuration_type::id)
        .with_editable_type(sensor_type::cpu
            | sensor_type::external
            | sensor_type::gpu
            | sensor_type::system)
        .produces(reading_type::floating_point);
    std::size_t retval = 0;

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    const auto cnt_sensors = config.count_sensors();
    auto sensors = config.sensors();

    for (std::size_t i = 0; i < cnt_sensors; ++i) {
        try {
            std::string name("NI-DAQmx");
            const auto& sensor = sensors[i];

//
//            // Connect to the instrument.
//            auto reset = false;
//            rtx_instrument instrument(reset, sensor.path(),
//                config.base_configuration().timeout());
//            if (reset && config.reset_on_enumerate()) {
//                instrument.reset(rtx_instrument_reset::all);
//            }
//
//            // Get the friendly name of the instrument the user might have
//            // configured. We use that in the friendly name of the sensor to
//            // facilitate identification of the instrument.
//            {
//                std::vector<char> buf(instrument.name(nullptr, 0), '\0');
//                if (!buf.empty()) {
//                    instrument.name(buf.data(), buf.size());
//                    name = buf.data();
//                }
//            }
//
//            // This function tries to read the channel label in order to find
//            // out whether a channel exists.
//            const auto check_channel = [&instrument](const rtx_channel& c) {
//                // Channels that can be measured range from 1 to 4. The
//                // instrument somehow accepts channel 0, but I have no idea what
//                // this channel is, so we manually reject it here.
//                if (c.channel() < 1) {
//                    return false;
//                }
//
//                try {
//                    auto label = instrument.write("CHAN%u:LAB?\n", c.channel())
//                        .read_all();
//                    return !label.empty();
//                } catch (...) {
//                    PWROWG_TRACE("Failed to configure channel %u on instrument "
//                        "\"%s\".", c.channel(), instrument.path());
//                    return false;
//                }
//            };
//
//            // Try to configure the voltage and current channels.
//            auto& cur = sensor.current_channel();
//            auto& vol = sensor.voltage_channel();
//            const auto have_cur = check_channel(cur);
//            const auto have_vol = check_channel(vol);
//
//            if (have_cur) {
//                if (retval < cnt) {
//                    dst[retval] = builder
//                        .with_path(sensor.path())
//                        .with_private_data(sensor)
//                        .with_id("RTX/%s/CH%u", sensor.path(), cur.channel())
//                        .with_name("%s Current (CH%u)", name.c_str(),
//                            cur.channel())
//                        .with_type(sensor_type::current)
//                        .measured_in(reading_unit::ampere)
//                        .build();
//                }
//                ++retval;
//            }
//
//            if (have_vol) {
//                if (retval < cnt) {
//                    dst[retval] = builder
//                        .with_path(sensor.path())
//                        .with_private_data(sensor)
//                        .with_id("RTX/%s/CH%u", sensor.path(), vol.channel())
//                        .with_name("%s Voltage (CH%u)", name.c_str(),
//                            vol.channel())
//                        .with_type(sensor_type::voltage)
//                        .measured_in(reading_unit::volt)
//                        .build();
//                }
//                ++retval;
//            }
//
//            if (have_cur && have_vol) {
//                if (retval < cnt) {
//                    dst[retval] = builder
//                        .with_path(sensor.path())
//                        .with_private_data(sensor)
//                        .with_id("RTX/%s/CH%u*CH%u", sensor.path(),
//                            cur.channel(), vol.channel())
//                        .with_name("%s Power (CH%u * CH%u)",
//                            name.c_str(), cur.channel(), vol.channel())
//                        .with_type(sensor_type::power)
//                        .measured_in(reading_unit::watt)
//                        .build();
//                }
//
//                ++retval;
//            }
//
//            // Keep the instrument alive until the end of the method because we
//            // want to reuse existing connections to the same instrument
//            // whenever possible.
//            instruments.push_back(std::move(instrument));
        } catch (...) {
            PWROWG_TRACE(_T("Skipping sensor due to a NI-DAQmx error."));
        }
    } /* for (std::size_t i = 0; i < cnt_sensors; ++i) */
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::daqmx_sensor::sample(_In_ const bool enable) {
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    assert(this->_trigger._impl != nullptr);
    auto& trigger = *this->_trigger._impl;
    throw "TODO";

    //if (enable) {
    //    if ((atomic_set(trigger.state, sensor_trigger_state::running)
    //            & sensor_trigger_state::running)
    //            != sensor_trigger_state::running) {
    //        PWROWG_TRACE(_T("Starting the RTX sensor controller thread."));
    //        this->_thread = std::thread(&rtx_sensor::control_instruments, this);
    //    }

    //} else {
    //    PWROWG_TRACE(_T("Signalling the RTX sensor controller to stop."));
    //    atomic_unset(trigger.state, sensor_trigger_state::running
    //        | sensor_trigger_state::armed);

    //    PWROWG_TRACE(_T("Making sure that the controller thread is not ")
    //        _T("working on the instruments anymore before injecting an OPC to ")
    //        _T("wake it up."));
    //    spin_while_all(trigger.state, sensor_trigger_state::busy);

    //    if (this->_thread.joinable()) {
    //        for (auto& i : trigger.instruments) {
    //            PWROWG_TRACE("Unlocking instrument \"%s\".", i.path());
    //            i.operation_complete_async();
    //        }

    //        PWROWG_TRACE(_T("Waiting for the RTX sensor controller to exit, ")
    //            _T("because the contract of sample requires them method not ")
    //            _T("to return until all pending samples have been delivered."));
    //        this->_thread.join();
    //    }
    //}
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
}
