// <copyright file="sensor_array.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/sensor_array.h"

#include <memory>
#include <stdexcept>

#include "sensor_array_configuration_impl.h"
#include "sensor_array_impl.h"
#include "sensor_registry.h"


/*
 * PWROWG_NAMESPACE::sensor_array::all_descriptions
 */
std::size_t PWROWG_NAMESPACE::sensor_array::all_descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const sensor_array_configuration& config) {
    if (!config) {
        throw std::invalid_argument("A valid array configuration object must "
            "be provided.");
    }

    return detail::sensor_registry::descriptions(dst, cnt, *config._impl);
}


/*
 * PWROWG_NAMESPACE::sensor_array::sensor_array
 */
PWROWG_NAMESPACE::sensor_array::sensor_array(
        _In_reads_(cnt) const sensor_description *descs,
        _In_ const std::size_t cnt)
        : _impl(new PWROWG_DETAIL_NAMESPACE::sensor_array_impl()) {
    if (descs != nullptr) {
        std::copy(descs,
            descs + cnt,
            std::back_inserter(this->_impl->descriptions));
        auto end = detail::sensor_registry::create(this->_impl->sensors,
            this->_impl->descriptions.begin(),
            this->_impl->descriptions.end());
        this->_impl->descriptions.erase(end, this->_impl->descriptions.end());
    }
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

    impl->state.begin_start();

    // TODO: start the stuff.

    impl->state.end_start();
}


/*
 * PWROWG_NAMESPACE::sensor_array::sensor_array::stop
 */
void PWROWG_NAMESPACE::sensor_array::sensor_array::stop(void) {
    using PWROWG_DETAIL_NAMESPACE::sensor_state;

    volatile auto impl = this->check_not_disposed();

    impl->state.begin_stop();

    // TODO: terminate all threads
    // TODO: join all threads

    impl->state.end_stop();
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
