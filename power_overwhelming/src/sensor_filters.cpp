// <copyright file="sensor_filters.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/sensor_filters.h"

#include "string_functions.h"


/*
 * PWROWG_NAMESPACE::is_current_sensor
 */
bool PWROWG_NAMESPACE::is_current_sensor(
        _In_ const sensor_description& desc) noexcept {
    return desc.is_sensor_type(sensor_type::current);
}


/*
 * PWROWG_NAMESPACE::is_nvml_sensor
 */
bool PWROWG_NAMESPACE::is_nvml_sensor(
        _In_ const sensor_description& desc) noexcept {
    return detail::starts_with(desc.name(), L"NVML/");
}


/*
 * PWROWG_NAMESPACE::is_power_sensor
 */
bool PWROWG_NAMESPACE::is_power_sensor(
        _In_ const sensor_description& desc) noexcept {
    return desc.is_sensor_type(sensor_type::power);
}


/*
 * PWROWG_NAMESPACE::is_tinkerforge_sensor
 */
bool PWROWG_NAMESPACE::is_tinkerforge_sensor(
        _In_ const sensor_description& desc) noexcept {
    return detail::starts_with(desc.name(), L"Tinkerforge/");
}


/*
 * PWROWG_NAMESPACE::is_usb_pd_sensor
 */
bool PWROWG_NAMESPACE::is_usb_pd_sensor(
        _In_ const sensor_description& desc) noexcept {
    return detail::starts_with(desc.name(), L"USB PD/");
}


/*
 * PWROWG_NAMESPACE::is_voltage_sensor
 */
bool PWROWG_NAMESPACE::is_voltage_sensor(
        _In_ const sensor_description& desc) noexcept {
    return desc.is_sensor_type(sensor_type::voltage);
}
