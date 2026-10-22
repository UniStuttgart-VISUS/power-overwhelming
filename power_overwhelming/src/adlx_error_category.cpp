// <copyright file="adlx_error_category.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_ADLX)
#include "adlx_error_category.h"

#include <string>

#include <adl_defines.h>


/*
 * PWROWG_DETAIL_NAMESPACE::adlx_error_category::default_error_condition
 */
std::error_condition
PWROWG_DETAIL_NAMESPACE::adlx_error_category::default_error_condition(
        int status) const noexcept {
    return std::error_condition(status, adlx_category());
}


/*
 * PWROWG_DETAIL_NAMESPACE::message
 */
std::string PWROWG_DETAIL_NAMESPACE::adlx_error_category::message(
        int status) const {
    switch (status) {
        case ADLX_OK:
            return "The operation completed successfully.";

        case ADLX_ALREADY_ENABLED:
            return "The functionality is already enabled.";

        case ADLX_ALREADY_INITIALIZED:
            return "ADLX is already initialised.";

        case ADLX_FAIL:
            return "An unexpected error occurred.";

        case ADLX_INVALID_ARGS:
            return "One or more of the arguments are invalid.";

        case ADLX_BAD_VER:
            return "The ADLX version is incompatible.";

        case ADLX_UNKNOWN_INTERFACE:
            return "The interface is unknown.";

        case ADLX_TERMINATED:
            return "ADLX has already been terminated.";

        case ADLX_ADL_INIT_ERROR:
            return "ADLX failed to initialise.";

        case ADLX_NOT_FOUND:
            return "The object was not found.";

        case ADLX_INVALID_OBJECT:
            return "The object is invalid.";

        case ADLX_ORPHAN_OBJECTS:
            return "The object is orphaned.";

        case ADLX_NOT_SUPPORTED:
            return "The functionality is not supported.";

        case ADLX_PENDING_OPERATION:
            return "An operation is already in progress.";

        case ADLX_GPU_INACTIVE:
            return "The GPU is inactive.";

        case ADLX_GPU_IN_USE:
            return "The GPU is in use.";

        case ADLX_TIMEOUT_OPERATION:
            return "An operation timed out";

        case ADLX_NOT_ACTIVE:
            return "The functionality is not active.";

        case ADLX_RESET_NEEDED:
            return "A factory reset is required.";

        default:
            return std::to_string(status);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::adlx_category
 */
const std::error_category& PWROWG_DETAIL_NAMESPACE::adlx_category(
        void) noexcept {
    static const adlx_error_category retval;
    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::throw_if_adlx_failed
 */
void PWROWG_DETAIL_NAMESPACE::throw_if_adlx_failed(
        _In_ const ADLX_RESULT status,
        _In_opt_z_ const char *message) {
    if (ADLX_FAILED(status)) {
        if (message == nullptr) {
            throw std::system_error(status, adlx_category());
        } else {
            throw std::system_error(status, adlx_category(), message);
        }
    }
}

#endif /* defined(POWER_OVERWHELMING_WITH_ADLX) */
