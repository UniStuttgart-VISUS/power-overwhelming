// <copyright file="sensor_array_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/sensor_array_configuration.h"

#include <memory>
#include <stdexcept>

#include "sensor_array_configuration_impl.h"


/*
 * PWROWG_NAMESPACE::sensor_array_configuration::sensor_array_configuration
 */
PWROWG_NAMESPACE::sensor_array_configuration::sensor_array_configuration(void)
    : _impl(new PWROWG_DETAIL_NAMESPACE::sensor_array_configuration_impl()) { }


/*
 * PWROWG_NAMESPACE::sensor_array_configuration::~sensor_array_configuration
 */
PWROWG_NAMESPACE::sensor_array_configuration::~sensor_array_configuration(
        void) noexcept {
    delete this->_impl;
}


/*
 * PWROWG_NAMESPACE::sensor_array_configuration::operator =
 */
PWROWG_NAMESPACE::sensor_array_configuration&
PWROWG_NAMESPACE::sensor_array_configuration::operator =(
        _Inout_ sensor_array_configuration&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::sensor_array_configuration::configure
 */
PWROWG_NAMESPACE::sensor_array_configuration&
PWROWG_NAMESPACE::sensor_array_configuration::configure(
        _In_ void (*configure)(_In_ adl_configuration&, _In_opt_ void *),
        _In_opt_ void *context) {
    this->check_not_disposed().configure(configure, context);
}


/*
 * PWROWG_NAMESPACE::sensor_array_configuration::check_not_disposed
 */
PWROWG_NAMESPACE::sensor_array_configuration::impl_type&
PWROWG_NAMESPACE::sensor_array_configuration::check_not_disposed(void) {
    volatile auto retval = this->_impl;

    if (retval == nullptr) {
        throw std::runtime_error("A sensor array configuration which has been "
            "disposed by a move operation cannot be used anymore.");
    }

    return *retval;
}
