// <copyright file="sensor_state.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "sensor_state.h"

#include <stdexcept>


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_state::begin_start
 */
void PWROWG_DETAIL_NAMESPACE::sensor_state::begin_start(void) {
    auto expected = value_type::stopped;
    auto desired = value_type::starting;

    if (!this->_value.compare_exchange_strong(expected,
            desired,
            std::memory_order_acq_rel,
            std::memory_order_relaxed)) {
        throw std::logic_error("The sensor (array) is already running or in a "
            "transitional state.");
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_state::begin_stop
 */
void PWROWG_DETAIL_NAMESPACE::sensor_state::begin_stop(void) {
    auto expected = value_type::running;
    auto desired = value_type::stopping;

    if (!this->_value.compare_exchange_strong(expected,
            desired,
            std::memory_order_acq_rel,
            std::memory_order_relaxed)) {
        throw std::logic_error("The sensor (array) is not running or in a "
            "transitional state.");
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_state::end_start
 */
void PWROWG_DETAIL_NAMESPACE::sensor_state::end_start(void) {
    auto expected = value_type::starting;
    auto desired = value_type::running;

    if (!this->_value.compare_exchange_strong(expected,
            desired,
            std::memory_order_acq_rel,
            std::memory_order_relaxed)) {
        throw std::logic_error("The state of the sensor (array) has been "
            "manipulated concurrently in an unsafe way during startup.");
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_state::end_stop
 */
void PWROWG_DETAIL_NAMESPACE::sensor_state::end_stop(void) {
    auto expected = value_type::stopping;
    auto desired = value_type::stopped;

    if (!this->_value.compare_exchange_strong(expected,
            desired,
            std::memory_order_acq_rel,
            std::memory_order_relaxed)) {
        if (expected != value_type::stopped) {
            // Note: we assume a duplicate stop to be safe.
            throw std::logic_error("The state of the sensor (array) has been "
                "manipulated concurrently in an unsafe way during shutdown.");
        }
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_state::stop
 */
void PWROWG_DETAIL_NAMESPACE::sensor_state::stop(void) {
    this->_value.store(value_type::stopped, std::memory_order_release);
}
