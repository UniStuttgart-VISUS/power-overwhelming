// <copyright file="collector_settings.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/collector_settings.h"

#include <stdexcept>

#include "string_functions.h"


/*
 * visus::power_overwhelming::collector_settings::default_output_path
 */
constexpr const wchar_t *visus::power_overwhelming::collector_settings
::default_output_path;


/*
 * visus::power_overwhelming::collector_settings::collector_settings
 */
visus::power_overwhelming::collector_settings::collector_settings(void)
        : _output_path(nullptr), _sampling_interval(default_sampling_interval) {
    this->output_path(default_output_path);
}


/*
 * visus::power_overwhelming::collector_settings::collector_settings
 */
visus::power_overwhelming::collector_settings::collector_settings(
        _In_ const collector_settings& rhs) : _output_path(nullptr) {
    *this = rhs;
}


/*
 * visus::power_overwhelming::collector_settings::~collector_settings
 */
visus::power_overwhelming::collector_settings::~collector_settings(void) {
    if (this->_output_path != nullptr) {
        ::free(this->_output_path);
    }
}


/*
 * visus::power_overwhelming::collector_settings::output_path
 */
visus::power_overwhelming::collector_settings&
visus::power_overwhelming::collector_settings::output_path(
        _In_z_ const wchar_t *path) {
    if (path == nullptr) {
        throw std::invalid_argument("The output path must be a valid string.");
    }

    detail::safe_assign(this->_output_path, path);

    return *this;
}


/*
 * visus::power_overwhelming::collector_settings::sampling_interval
 */
visus::power_overwhelming::collector_settings&
visus::power_overwhelming::collector_settings::sampling_interval(
        _In_ const sampling_interval_type interval) {
    this->_sampling_interval = interval;
    return *this;
}


/*
 * visus::power_overwhelming::collector_settings::operator =
 */
visus::power_overwhelming::collector_settings&
visus::power_overwhelming::collector_settings::operator =(
        _In_ const collector_settings& rhs) {
    if (this != std::addressof(rhs)) {
        this->output_path(rhs._output_path);
        this->sampling_interval(rhs._sampling_interval);
    }

    return *this;
}
