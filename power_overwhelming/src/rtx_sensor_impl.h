﻿//// <copyright file="rtx_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
//// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
//// Licensed under the MIT licence. See LICENCE file for details.
//// </copyright>
//// <author>Christoph Müller</author>
//
//#pragma once
//
//#include <string>
//
//#include "visus/pwrowg/async_sampling.h"
//#include "visus/pwrowg/rtx_instrument.h"
//#include "visus/pwrowg/rtx_instrument_configuration.h"
//#include "visus/pwrowg/waveform_decimation_method.h"
//
//
//namespace visus {
//namespace power_overwhelming {
//namespace detail {
//
//    /// <summary>
//    /// Implementation details for <see cref="rtx_sensor" />.
//    /// </summary>
//    struct rtx_sensor_impl final {
//        power_overwhelming::async_sampling async_sampling;
//        rtx_instrument::channel_type channel_current;
//        rtx_instrument::channel_type channel_voltage;
//        waveform_decimation_method decimation_method;
//        rtx_instrument instrument;
//        std::wstring sensor_name;
//
//        inline rtx_sensor_impl(_In_z_ const char *path,
//                _In_ const visa_instrument::timeout_type timeout,
//                _In_ void (*on_new_instrument)(rtx_instrument&, void *),
//                _In_ rtx_instrument_configuration *instrument_config)
//            : channel_current(0),
//                channel_voltage(0),
//                decimation_method(waveform_decimation_method::mean),
//                instrument(rtx_instrument::create(path, on_new_instrument,
//                    instrument_config, timeout)) { }
//
//        ~rtx_sensor_impl(void);
//    };
//
//} /* namespace detail */
//} /* namespace power_overwhelming */
//} /* namespace visus */
