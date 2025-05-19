// <copyright file="adl_error_category.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_ADL)
#include "adl_error_category.h"

#include <string>

#include <adl_defines.h>


/*
 * PWROWG_DETAIL_NAMESPACE::adl_error_category::default_error_condition
 */
std::error_condition
PWROWG_DETAIL_NAMESPACE::adl_error_category::default_error_condition(
        int status) const noexcept {
    return std::error_condition(status, adl_category());
}


/*
 * PWROWG_DETAIL_NAMESPACE::message
 */
std::string PWROWG_DETAIL_NAMESPACE::adl_error_category::message(
        int status) const {
    switch (status) {
        case ADL_OK_WAIT:
            return "Try again later.";

        case ADL_OK_RESTART:
            return "The machine needs to be restarted.";

        case ADL_OK_MODE_CHANGE:
            return "A mode change is required.";

        case ADL_OK_WARNING:
            return "Warning";

        case ADL_OK:
            return "The ADL function completed successfully.";

        case ADL_ERR:
            return "The operation failed. Most likely, one or more of the "
                "escape calls to the driver failed.";

        case ADL_ERR_NOT_INIT:
            return "ADL was not initialised.";

        case ADL_ERR_INVALID_PARAM:
            return "One of the parameters is invalid.";

        case ADL_ERR_INVALID_PARAM_SIZE:
            return "One of the parameters has an invalid size.";

        case ADL_ERR_INVALID_ADL_IDX:
            return "The ADL index is out of range.";

        case ADL_ERR_INVALID_CONTROLLER_IDX:
            return "The controller index is out of range.";

        case ADL_ERR_INVALID_DIPLAY_IDX:
            return "The display index is out of range.";

        case ADL_ERR_NOT_SUPPORTED:
            return "The ADL function is not suppored by the driver.";

        case ADL_ERR_NULL_POINTER:
            return "An unexpected null pointer was found.";

        case ADL_ERR_DISABLED_ADAPTER:
            return "The adapter is disabled.";

        case ADL_ERR_INVALID_CALLBACK:
            return "The callback function is invalid.";

        case ADL_ERR_RESOURCE_CONFLICT:
            return "A display resource conflict occurred.";

        case ADL_ERR_SET_INCOMPLETE:
            return "Some of the values could not be updated.";

        case ADL_ERR_NO_XDISPLAY:
            return "No X display is available.";

        case ADL_ERR_CALL_TO_INCOMPATIABLE_DRIVER:
            return "The graphics drvier is incompatible with ADL.";

        default:
            return std::to_string(status);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::adl_category
 */
const std::error_category& PWROWG_DETAIL_NAMESPACE::adl_category(
        void) noexcept {
    static const adl_error_category retval;
    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::throw_if_adl_failed
 */
void PWROWG_DETAIL_NAMESPACE::throw_if_adl_failed(
        _In_ const int status,
        _In_opt_z_ const char *message) {
    if (status < 0) {
        if (message == nullptr) {
            throw std::system_error(status, adl_category());
        } else {
            throw std::system_error(status, adl_category(), message);
        }
    }
}

#endif /* defined(POWER_OVERWHELMING_WITH_ADL) */
