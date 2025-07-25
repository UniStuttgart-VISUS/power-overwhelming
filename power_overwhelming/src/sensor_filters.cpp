﻿// <copyright file="sensor_filters.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/sensor_filters.h"

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/hmc8015_instrument.h"

#include "string_functions.h"


/*
 * PWROWG_NAMESPACE::is_adl_sensor
 */
bool PWROWG_NAMESPACE::is_adl_sensor(
        _In_ const sensor_description& desc) noexcept {
    return detail::starts_with(desc.id(), L"ADL/");
}


/*
 * PWROWG_NAMESPACE::is_cpu_sensor
 */
bool PWROWG_NAMESPACE::is_cpu_sensor(
        _In_ const sensor_description& desc) noexcept {
    return desc.is_sensor_type(sensor_type::cpu);
}


/*
 * PWROWG_NAMESPACE::is_current_sensor
 */
bool PWROWG_NAMESPACE::is_current_sensor(
        _In_ const sensor_description& desc) noexcept {
    return desc.is_sensor_type(sensor_type::current);
}


/*
 * PWROWG_NAMESPACE::is_emi_sensor
 */
bool PWROWG_NAMESPACE::is_emi_sensor(
        _In_ const sensor_description& desc) noexcept {
    return detail::starts_with(desc.id(), L"EMI/");
}


/*
 * PWROWG_NAMESPACE::is_energy_sensor
 */
bool PWROWG_NAMESPACE::is_energy_sensor(
        _In_ const sensor_description& desc) noexcept {
    return desc.is_sensor_type(sensor_type::energy);
}


/*
 * PWROWG_NAMESPACE::is_gpu_sensor
 */
bool PWROWG_NAMESPACE::is_gpu_sensor(
        _In_ const sensor_description& desc) noexcept {
    return desc.is_sensor_type(sensor_type::gpu);
}


/*
 * PWROWG_NAMESPACE::is_hmc8015_sensor
 */
bool PWROWG_NAMESPACE::is_hmc8015_sensor(
        _In_ const sensor_description& desc) noexcept {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto product = convert_string<wchar_t>(hmc8015_instrument::product_id);
    auto vendor = convert_string<wchar_t>(visa_instrument::rohde_und_schwarz);

    product.insert(0, L"::");
    product.append(L"::");
    vendor.insert(0, L"::");
    vendor.append(L"::");

    return detail::contains(desc.path(), product.c_str(), true)
        && detail::contains(desc.path(), vendor.c_str(), true);
#else /* defined(POWER_OVERWHELMING_WITH_VISA) */
    return false;
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * PWROWG_NAMESPACE::is_marker_sensor
 */
POWER_OVERWHELMING_API bool PWROWG_NAMESPACE::is_marker_sensor(
        _In_ const sensor_description& desc) noexcept {
    return detail::equals(desc.id(), L"VISUS/Marker");
}


/*
 * PWROWG_NAMESPACE::is_msr_sensor
 */
bool PWROWG_NAMESPACE::is_msr_sensor(
        _In_ const sensor_description& desc) noexcept {
    return detail::starts_with(desc.id(), L"MSR/");
}


/*
 * PWROWG_NAMESPACE::is_nvapi_sensor
 */
bool PWROWG_NAMESPACE::is_nvapi_sensor(
        _In_ const sensor_description& desc) noexcept {
    return detail::starts_with(desc.id(), L"NVAPI/");
}


/*
 * PWROWG_NAMESPACE::is_nvml_sensor
 */
bool PWROWG_NAMESPACE::is_nvml_sensor(
        _In_ const sensor_description& desc) noexcept {
    return detail::starts_with(desc.id(), L"NVML/");
}


/*
 * PWROWG_NAMESPACE::is_powenetics_sensor
 */
bool PWROWG_NAMESPACE::is_powenetics_sensor(
        _In_ const sensor_description& desc) noexcept {
    return detail::starts_with(desc.id(), L"Powenetics/");
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
    return detail::starts_with(desc.id(), L"Tinkerforge/");
}


/*
 * PWROWG_NAMESPACE::is_usb_pd_sensor
 */
bool PWROWG_NAMESPACE::is_usb_pd_sensor(
        _In_ const sensor_description& desc) noexcept {
    return detail::starts_with(desc.name(), L"USB PD ");
}


/*
 * PWROWG_NAMESPACE::is_voltage_sensor
 */
bool PWROWG_NAMESPACE::is_voltage_sensor(
        _In_ const sensor_description& desc) noexcept {
    return desc.is_sensor_type(sensor_type::voltage);
}
