// <copyright file="hmc8015_function.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/hmc8015_function.h"

#include <stdexcept>

#include "visus/pwrowg/convert_string.h"

#include "string_functions.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// The lookup table for the function enumeration.
/// </summary>
static const struct {
    hmc8015_function function;
    const wchar_t *name;
} hmc8015_functions[] {
    { hmc8015_function::empty, L"EMPT" },
    { hmc8015_function::active_power, L"P" },
    { hmc8015_function::apparent_power, L"S" },
    { hmc8015_function::reactive_power, L"Q" },
    { hmc8015_function::power_factor, L"LAMB" },
    { hmc8015_function::phase_difference, L"PHI" },
    { hmc8015_function::voltage_frequency, L"FU" },
    { hmc8015_function::current_frequency, L"FI" },
    { hmc8015_function::rms_voltage, L"URMS" },
    { hmc8015_function::average_voltage, L"UAVG" },
    { hmc8015_function::rms_current, L"IRMS" },
    { hmc8015_function::current_average, L"IAVG" },
    { hmc8015_function::voltage_distortion, L"UTHD" },
    { hmc8015_function::current_distortion, L"ITHD" },
    { hmc8015_function::phase_locked_loop_frequency, L"FPLL" },
    { hmc8015_function::integration_time, L"TIME" },
    { hmc8015_function::watt_hour, L"WH" },
    { hmc8015_function::positive_watt_hour, L"WHP" },
    { hmc8015_function::negative_watt_hour, L"WHM" },
    { hmc8015_function::ampere_hour, L"AH" },
    { hmc8015_function::positive_ampere_hour, L"AHP" },
    { hmc8015_function::negative_ampere_hour, L"AHM" },
    { hmc8015_function::voltage_range, L"URAN" },
    { hmc8015_function::current_range, L"IRAN" },
    { hmc8015_function::empty, nullptr }
};

PWROWG_DETAIL_NAMESPACE_END


/*
 * PWROWG_NAMESPACE::is_current
 */
bool PWROWG_NAMESPACE::is_current(
        _In_ const hmc8015_function function) noexcept {
    switch (function) {
        case hmc8015_function::rms_current:
        case hmc8015_function::current_average:
            return true;

        default:
            return false;
    }
}


/*
 * PWROWG_NAMESPACE::is_energy
 */
bool PWROWG_NAMESPACE::is_energy(
        _In_ const hmc8015_function function) noexcept {
    switch (function) {
        case hmc8015_function::watt_hour:
        case hmc8015_function::positive_watt_hour:
        case hmc8015_function::negative_watt_hour:
            return true;

        default:
            return false;
    }
}


/*
 * PWROWG_NAMESPACE::is_power
 */
bool PWROWG_NAMESPACE::is_power(
        _In_ const hmc8015_function function) noexcept {
    switch (function) {
        case hmc8015_function::active_power:
        case hmc8015_function::apparent_power:
        case hmc8015_function::reactive_power:

            return true;

        default:
            return false;
    }
}


/*
 * PWROWG_NAMESPACE::is_voltage
 */
bool PWROWG_NAMESPACE::is_voltage(
        _In_ const hmc8015_function function) noexcept {
    switch (function) {
        case hmc8015_function::rms_voltage:
        case hmc8015_function::average_voltage:
            return true;

        default:
            return false;
    }
}


/*
 * PWROWG_NAMESPACE::parse_hmc8015_function
 */
PWROWG_NAMESPACE::hmc8015_function PWROWG_NAMESPACE::parse_hmc8015_function(
        _In_z_ const wchar_t *function) {
    if (function == nullptr) {
        throw std::invalid_argument("A valid string must be provided.");
    }

    for (auto f = detail::hmc8015_functions; (f->name != nullptr); ++f) {
        if (detail::equals(function, f->name, true)) {
            return f->function;
        }
    }

    throw std::invalid_argument("The specified string is not a valid HMC8015 "
        "measurement function.");
}


/*
 * PWROWG_NAMESPACE::parse_hmc8015_function
 */
PWROWG_NAMESPACE::hmc8015_function PWROWG_NAMESPACE::parse_hmc8015_function(
        _In_z_ const char *function) {
    if (function == nullptr) {
        throw std::invalid_argument("A valid string must be provided.");
    }

    const auto f = convert_string<wchar_t>(function);
    return parse_hmc8015_function(f.c_str());
}


/*
 * PWROWG_NAMESPACE::to_string
 */
_Ret_valid_ const wchar_t *PWROWG_NAMESPACE::to_string(
        _In_ const hmc8015_function function) {
    for (auto f = detail::hmc8015_functions; (f->name != nullptr); ++f) {
        if (f->function == function) {
            return f->name;
        }
    }

    throw std::invalid_argument("The specified HMC8015 measurement function "
        "is unknown.");
}
