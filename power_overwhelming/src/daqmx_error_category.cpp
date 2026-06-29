// <copyright file="daqmx_error_category.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include "daqmx_error_category.h"

#include <string>
#include <vector>

#include "daqmx_library.h"


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_error_category::default_error_condition
 */
std::error_condition
PWROWG_DETAIL_NAMESPACE::daqmx_error_category::default_error_condition(
        int status) const noexcept {
    return std::error_condition(status, daqmx_category());
}


/*
 * PWROWG_DETAIL_NAMESPACE::message
 */
std::string PWROWG_DETAIL_NAMESPACE::daqmx_error_category::message(
        int status) const {
    const auto get_error = daqmx_library::instance()._DAQmxGetErrorString;

    auto cnt = get_error(status, nullptr, 0);
    if (cnt < 0) {
        return std::to_string(status);
    }

    std::vector<char> buffer(cnt);
    if (get_error(status, buffer.data(), cnt) < 0) {
        return std::to_string(status);
    }

    return buffer.data();
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_category
 */
const std::error_category& PWROWG_DETAIL_NAMESPACE::daqmx_category(
        void) noexcept {
    static const daqmx_error_category retval;
    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::throw_if_daqmx_failed
 */
void PWROWG_DETAIL_NAMESPACE::throw_if_daqmx_failed(
        _In_ const std::int32_t status,
        _In_opt_z_ const char *message) {
    if (status != 0) {
        if (message == nullptr) {
            throw std::system_error(status, daqmx_category());
        } else {
            throw std::system_error(status, daqmx_category(), message);
        }
    }
}

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
