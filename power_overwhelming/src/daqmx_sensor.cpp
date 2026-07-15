// <copyright file="daqmx_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "daqmx_sensor.h"

#include "visus/pwrowg/daqmx_current_channel.h"
#include "visus/pwrowg/daqmx_power_channel.h"
#include "visus/pwrowg/daqmx_voltage_channel.h"
#include "visus/pwrowg/daqmx_task.h"
#include "visus/pwrowg/trace.h"

#include "daqmx_error_category.h"
#include "daqmx_library.h"


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

    // Check whether the given channel is valid and exists on any device
    // attached to the machine running this code.
    const auto check_channel = [](const auto *c) {
        if (c == nullptr) {
            return false;
        }

        try {
            daqmx_task task("daqmx_sensor probe");
            task += *c;
            return true;
        } catch (...) {
            PWROWG_TRACE("Failed to configure channel %s.", c->channel());
            return false;
        }
    };

    for (std::size_t i = 0; i < cnt_sensors; ++i) {
        try {
            const auto& sensor = sensors[i];

            auto cur = sensor.current_channel();
            auto pow = sensor.power_channel();
            auto vfc = sensor.voltage_for_current_channel();
            auto vol = sensor.voltage_channel();
            const auto have_cur = check_channel(cur);
            const auto have_pow = check_channel(pow);
            const auto have_vfc = check_channel(vfc);
            const auto have_vol = check_channel(vol);

            if (have_cur) {
                if (retval < cnt) {
                    auto channel = cur->channel();
                    dst[retval] = builder
                        .with_path(channel)
                        .with_private_data(sensor)
                        .with_id("DAQmx/%s", channel)
                        .with_name("%s (current)", channel)
                        .with_type(sensor_type::current)
                        .measured_in(reading_unit::ampere)
                        .build();
                }

                ++retval;
            }

            if (have_pow) {
                if (retval < cnt) {
                    assert(pow != nullptr);
                    auto v = pow->voltage_channel();
                    auto c = pow->current_channel();
                    dst[retval] = builder
                        .with_path("%s+%s", v, c)
                        .with_private_data(sensor)
                        .with_id("DAQmx/%s+%s", v, c)
                        .with_name("%s+%s (on-device-computed power)", v, c)
                        .with_type(sensor_type::power)
                        .measured_in(reading_unit::watt)
                        .build();
                }

                ++retval;
            }

            if (have_vfc) {
                if (retval < cnt) {
                    auto channel = vfc->channel();
                    dst[retval] = builder
                        .with_path(channel)
                        .with_private_data(sensor)
                        .with_id("DAQmx/%s", channel)
                        .with_name("%s (current)", channel)
                        .with_type(sensor_type::current)
                        .measured_in(reading_unit::ampere)
                        .build();
                }

                ++retval;
            }

            if (have_vol) {
                if (retval < cnt) {
                    assert(vol != nullptr);
                    auto channel = vol->channel();
                    dst[retval] = builder
                        .with_path(channel)
                        .with_private_data(sensor)
                        .with_id("DAQmx/%s", channel)
                        .with_name("%s (voltage)", channel)
                        .with_type(sensor_type::voltage)
                        .measured_in(reading_unit::volt)
                        .build();
                }

                ++retval;
            }

            if (have_vol && have_cur) {
                if (retval < cnt) {
                    assert(vol != nullptr);
                    auto v = vol->channel();
                    auto c = cur->channel();
                    dst[retval] = builder
                        .with_path("%s*%s", v, c)
                        .with_private_data(sensor)
                        .with_id("DAQmx/%s*%s", v, c)
                        .with_name("%s*%s (power)", v, c)
                        .with_type(sensor_type::power)
                        .measured_in(reading_unit::watt)
                        .build();
                }

                ++retval;
            }

            if (have_vol && have_vfc) {
                if (retval < cnt) {
                    assert(vol != nullptr);
                    auto v = vol->channel();
                    auto c = vfc->channel();
                    dst[retval] = builder
                        .with_path("%s*%s", v, c)
                        .with_private_data(sensor)
                        .with_id("DAQmx/%s*%s", v, c)
                        .with_name("%s*%s (power)", v, c)
                        .with_type(sensor_type::power)
                        .measured_in(reading_unit::watt)
                        .build();
                }

                ++retval;
            }
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
