// <copyright file="sensor_array.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/sensor_array.h"

#include <memory>
#include <stdexcept>

#include "sensor_array_impl.h"


/*
 * PWROWG_NAMESPACE::sensor_array::all_descriptions
 */
std::size_t PWROWG_NAMESPACE::sensor_array::all_descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt) {
    throw "TODO";
}


/*
 * PWROWG_NAMESPACE::sensor_array::sensor_array
 */
PWROWG_NAMESPACE::sensor_array::sensor_array(
        _In_reads_(cnt) const sensor_description *descs,
        _In_ const std::size_t cnt)
        : _impl(new PWROWG_DETAIL_NAMESPACE::sensor_array_impl()) {
    throw "TODO";
}


/*
 * PWROWG_NAMESPACE::sensor_array::~sensor_array
 */
PWROWG_NAMESPACE::sensor_array::~sensor_array(void) noexcept {
    delete this->_impl;
}


/*
 * PWROWG_NAMESPACE::sensor_array::descriptions
 */
std::size_t PWROWG_NAMESPACE::sensor_array::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt) {
    volatile auto impl = this->_impl;  // sic!

    if (impl != nullptr) {
        if (dst != nullptr) {
            for (std::size_t i = 0; (i < this->size()) && (i < cnt); ++i) {
                dst[i] = impl->descriptions[i];
            }
        }

        return this->size();

    } else {
        return 0;
    }
}


/*
 * PWROWG_NAMESPACE::sensor_array::start
 */
void PWROWG_NAMESPACE::sensor_array::start(
        _In_ const sensor_array_callback callback,
        _In_opt_ void *context) {
    using PWROWG_DETAIL_NAMESPACE::sensor_state;

    volatile auto impl = this->check_not_disposed();

    {
        auto expected = sensor_state::stopped;
        auto desired = sensor_state::starting;

        if (!impl->state.compare_exchange_strong(expected, desired)) {
            throw std::logic_error("The sensor array is already running or in "
                "a transitional state.");
        }
    }

    // TODO: start the stuff.

    {
        auto expected = sensor_state::starting;
        auto desired = sensor_state::running;

        if (!impl->state.compare_exchange_strong(expected, desired)) {
            throw std::logic_error("The state of the sensor array has been "
                "manipulated concurrently in an unsafe way.");
        }
    }
}


/*
 * PWROWG_NAMESPACE::sensor_array::sensor_array::stop
 */
void PWROWG_NAMESPACE::sensor_array::sensor_array::stop(void) {
    using PWROWG_DETAIL_NAMESPACE::sensor_state;

    volatile auto impl = this->check_not_disposed();

    {
        auto expected = sensor_state::stopping;
        auto desired = sensor_state::running;

        if (!impl->state.compare_exchange_strong(expected, desired)) {
            throw std::logic_error("The sensor array is not running.");
        }
    }

    // TODO: terminate all threads
    // TODO: join all threads

    {
        auto expected = sensor_state::stopping;
        auto desired = sensor_state::stopped;

        if (!impl->state.compare_exchange_strong(expected, desired)) {
            throw std::logic_error("The state of the sensor array has been "
                "manipulated concurrently in an unsafe way.");
        }
    }
}


/*
 * PWROWG_NAMESPACE::sensor_array::size
 */
std::size_t PWROWG_NAMESPACE::sensor_array::size(void) const noexcept {
    volatile auto impl = this->_impl;  // sic!
    return (impl != nullptr) ? impl->descriptions.size() : 0;
}


/*
 * PWROWG_NAMESPACE::sensor_array::operator =
 */
PWROWG_NAMESPACE::sensor_array& PWROWG_NAMESPACE::sensor_array::operator =(
        _Inout_ sensor_array&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::sensor_array::operator []
 */
const PWROWG_NAMESPACE::sensor_description&
PWROWG_NAMESPACE::sensor_array::operator [](_In_ int idx) const {
    volatile auto impl = this->check_not_disposed();

    if ((idx < 0) && (idx >= impl->descriptions.size())) {
        throw std::range_error("The specified index is out of range.");
    }

    return impl->descriptions[idx];
}


/*
 * PWROWG_NAMESPACE::sensor_array::operator []
 */
PWROWG_NAMESPACE::sensor_description&
PWROWG_NAMESPACE::sensor_array::operator [](_In_ int idx) {
    volatile auto impl = this->check_not_disposed();

    if ((idx < 0) && (idx >= impl->descriptions.size())) {
        throw std::range_error("The specified index is out of range.");
    }

    return impl->descriptions[idx];
}


/*
 * PWROWG_NAMESPACE::sensor_array::check_not_disposed
 */
PWROWG_DETAIL_NAMESPACE::sensor_array_impl *
PWROWG_NAMESPACE::sensor_array::check_not_disposed(void) const {
    volatile auto retval = this->_impl;

    if (retval == nullptr) {
        throw std::runtime_error("A sensor array which has been disposed by "
            "a move operation cannot be used anymore.");
    }

    return retval;
}
