// <copyright file="rtx_sensor_state.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "rtx_sensor_state.h"

#include <type_traits>

#include "visus/pwrowg/trace.h"


/*
 * PWROWG_DETAIL_NAMESPACE::clear_state
 */
bool PWROWG_DETAIL_NAMESPACE::clear_state(
        _Inout_ rtx_sensor_state& state,
        _In_ const rtx_sensor_state old_state) noexcept {
    typedef std::underlying_type_t<rtx_sensor_state> underlying_type;

    if (check_state(state, rtx_sensor_state::stop)) {
        PWROWG_TRACE(_T("Changing rtx_sensor_state is not possible, "
            "because the sensor is already stopping."));
        return false;
    }

    auto e = static_cast<underlying_type>(state);
    auto o = static_cast<underlying_type>(old_state);
    state = static_cast<rtx_sensor_state>(e & ~o);
    return true;
}


/*
 * PWROWG_DETAIL_NAMESPACE::clear_state
 */
bool PWROWG_DETAIL_NAMESPACE::clear_state(
        _Inout_ std::atomic<rtx_sensor_state>& state,
        _In_ const rtx_sensor_state old_state) noexcept {
    typedef std::underlying_type_t<rtx_sensor_state> underlying_type;
    auto expected = state.load(std::memory_order_acquire);

    while (true) {
        if (check_state(expected, rtx_sensor_state::stop)) {
            PWROWG_TRACE(_T("Changing rtx_sensor_state is not possible, "
                "because the sensor is already stopping."));
            return false;
        }

        auto e = static_cast<underlying_type>(expected);
        auto o = static_cast<underlying_type>(old_state);
        auto desired = static_cast<rtx_sensor_state>(e & ~o);
        if (state.compare_exchange_weak(
            expected,
            desired,
            std::memory_order_acq_rel)) {
            return true;
        }
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::set_state
 */
bool PWROWG_DETAIL_NAMESPACE::set_state(
        _Inout_ rtx_sensor_state& state,
        _In_ const rtx_sensor_state new_state) noexcept {
    typedef std::underlying_type_t<rtx_sensor_state> underlying_type;

    if (check_state(state, rtx_sensor_state::stop)) {
        PWROWG_TRACE(_T("Changing rtx_sensor_state is not possible, "
            "because the sensor is already stopping."));
        return false;
    }

    auto e = static_cast<underlying_type>(state);
    auto n = static_cast<underlying_type>(new_state);
    state = static_cast<rtx_sensor_state>(e | n);
    return true;
}


/*
 * PWROWG_DETAIL_NAMESPACE::set_state
 */
bool PWROWG_DETAIL_NAMESPACE::set_state(
        _Inout_ std::atomic<rtx_sensor_state>& state,
        _In_ const rtx_sensor_state new_state) noexcept {
    typedef std::underlying_type_t<rtx_sensor_state> underlying_type;
    auto expected = state.load(std::memory_order_acquire);

    while (true) {
        if (check_state(expected, rtx_sensor_state::stop)) {
            PWROWG_TRACE(_T("Changing rtx_sensor_state is not possible, "
                "because the sensor is already stopping."));
            return false;
        }

        auto e = static_cast<underlying_type>(expected);
        auto n = static_cast<underlying_type>(new_state);
        auto desired = static_cast<rtx_sensor_state>(e | n);
        if (state.compare_exchange_weak(
                expected,
                desired,
                std::memory_order_acq_rel)) {
            return true;
        }
    }
}
