// <copyright file="nvml_error_category.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_NVML)
#include "nvml_error_category.h"

#include "nvidia_management_library.h"


/*
 * PWROWG_DETAIL_NAMESPACE::nvml_error_category::default_error_condition
 */
std::error_condition
PWROWG_DETAIL_NAMESPACE::nvml_error_category::default_error_condition(
        int status) const noexcept {
    return std::error_condition(status, nvml_category());
}


/*
 * PWROWG_DETAIL_NAMESPACE::message
 */
std::string PWROWG_DETAIL_NAMESPACE::nvml_error_category::message(
        int status) const {
    return nvidia_management_library::instance().nvmlErrorString(
        static_cast<nvmlReturn_t>(status));
}


/*
 * PWROWG_DETAIL_NAMESPACE::nvml_category
 */
const std::error_category& PWROWG_DETAIL_NAMESPACE::nvml_category(
        void) noexcept {
    static const nvml_error_category retval;
    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::throw_if_nvml_failed
 */
void PWROWG_DETAIL_NAMESPACE::throw_if_nvml_failed(
        _In_ const nvmlReturn_t status,
        _In_opt_z_ const char *message) {
    if (status != NVML_SUCCESS) {
        if (message == nullptr) {
            throw std::system_error(status, nvml_category());
        } else {
            throw std::system_error(status, nvml_category(), message);
        }
    }
}

#endif /* defined(POWER_OVERWHELMING_WITH_NVML) */
