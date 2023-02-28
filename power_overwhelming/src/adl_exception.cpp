// <copyright file="nvml_exception.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "adl_exception.h"

#include <adl_defines.h>


/// <summary>
/// Get a human-readable error description for the given ADL error code.
/// </summary>
/// <param name="code"></param>
/// <returns></returns>
static std::string adl_to_string(const int code) {
    switch (code) {
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
            return std::to_string(code);
    }
}


/*
 * visus::power_overwhelming::adl_exception::adl_exception
 */
visus::power_overwhelming::adl_exception::adl_exception(const value_type code)
    : std::exception(adl_to_string(code).c_str()), _code(code) { }
