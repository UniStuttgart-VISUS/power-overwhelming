// <copyright file="nvapi_error_category.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_NVAPI)
#include "nvapi_error_category.h"

#include "nvapi_library.h"


/*
 * PWROWG_DETAIL_NAMESPACE::nvapi_error_category::default_error_condition
 */
std::error_condition
PWROWG_DETAIL_NAMESPACE::nvapi_error_category::default_error_condition(
        int status) const noexcept {
    return std::error_condition(status, nvapi_category());
}


/*
 * PWROWG_DETAIL_NAMESPACE::message
 */
std::string PWROWG_DETAIL_NAMESPACE::nvapi_error_category::message(
        int status) const {
    NvAPI_ShortString msg;
    nvapi_library::instance().NvAPI_GetErrorMessage(
        static_cast<NvAPI_Status>(status), msg);
    return msg;
}


/*
 * PWROWG_DETAIL_NAMESPACE::nvapi_category
 */
const std::error_category& PWROWG_DETAIL_NAMESPACE::nvapi_category(
        void) noexcept {
    static const nvapi_error_category retval;
    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::throw_if_nvapi_failed
 */
void PWROWG_DETAIL_NAMESPACE::throw_if_nvapi_failed(
        _In_ const NvAPI_Status status,
        _In_opt_z_ const char *message) {
    if (status < 0) {
        if (message == nullptr) {
            throw std::system_error(status, nvapi_category());
        } else {
            throw std::system_error(status, nvapi_category(), message);
        }
    }
}

#endif /* defined(POWER_OVERWHELMING_WITH_NVAPI) */
