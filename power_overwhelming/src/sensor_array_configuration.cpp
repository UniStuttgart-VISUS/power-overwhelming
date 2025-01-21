// <copyright file="sensor_array_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/sensor_array_configuration.h"

#include <cassert>


/*
 * PWROWG_NAMESPACE::sensor_array_configuration::sensor_array_configuration
 */
PWROWG_NAMESPACE::sensor_array_configuration::sensor_array_configuration(void) {
    this->filter(nullptr, nullptr);
}


/*
 * PWROWG_NAMESPACE::sensor_array_configuration::filter
 */
PWROWG_NAMESPACE::sensor_array_configuration&
PWROWG_NAMESPACE::sensor_array_configuration::filter(
        _In_opt_ const filter_func filter,
        _In_opt_ void *context) noexcept {
    static const auto allow_all = [](const sensor_description&, void *) {
        return true;
    };

    if (filter == nullptr) {
        this->_filter = allow_all;
    } else {
        this->_filter = filter;
    }

    this->_filter_context = context;

    return *this;
}


/*
 * PWROWG_NAMESPACE::sensor_array_configuration::filter
 */
bool PWROWG_NAMESPACE::sensor_array_configuration::filter(
        _In_ const sensor_description& desc) const {
    assert(this->_filter != nullptr);
    return this->_filter(desc, this->_filter_context);
}
