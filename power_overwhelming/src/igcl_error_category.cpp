// <copyright file="igcl_error_category.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_IGCL)
#include "igcl_error_category.h"

#include <string>

#include "igcl_library.h"

/*
 * PWROWG_DETAIL_NAMESPACE::igcl_error_category::default_error_condition
 */
std::error_condition
PWROWG_DETAIL_NAMESPACE::igcl_error_category::default_error_condition(
        int status) const noexcept {
    return std::error_condition(status, igcl_category());
}


/*
 * PWROWG_DETAIL_NAMESPACE::message
 */
std::string PWROWG_DETAIL_NAMESPACE::igcl_error_category::message(
        int status) const {
    switch (static_cast<ctl_result_t>(status)) {
        case CTL_RESULT_SUCCESS:
            return "Success";
        case CTL_RESULT_SUCCESS_STILL_OPEN_BY_ANOTHER_CALLER:
            return "The library is still open by another caller.";

        case CTL_RESULT_ERROR_NOT_INITIALIZED:
            return "The result was not initialised.";
        case CTL_RESULT_ERROR_ALREADY_INITIALIZED:
            return "The library was already initialised.";
        case CTL_RESULT_ERROR_DEVICE_LOST:
            return "Device hung, was reset or was removed, or a driver "
                "update occurred.";
        case CTL_RESULT_ERROR_OUT_OF_HOST_MEMORY:
            return "Insufficient host memory to satisfy the call.";
        case CTL_RESULT_ERROR_OUT_OF_DEVICE_MEMORY:
            return "Insufficient device memory to satisfy the call.";
        case CTL_RESULT_ERROR_INSUFFICIENT_PERMISSIONS:
            return "Access denied due to permission level.";
        case CTL_RESULT_ERROR_NOT_AVAILABLE:
            return "Resource was removed or not available.";
        case CTL_RESULT_ERROR_UNINITIALIZED:
            return "The library was not initialised.";
        case CTL_RESULT_ERROR_UNSUPPORTED_VERSION:
            return "Unsupported version.";
        case CTL_RESULT_ERROR_UNSUPPORTED_FEATURE:
            return "Unsupported feature.";
        case CTL_RESULT_ERROR_INVALID_ARGUMENT:
            return "Invalid argument.";
        case CTL_RESULT_ERROR_INVALID_API_HANDLE:
            return "Invalid API handle.";
        case CTL_RESULT_ERROR_INVALID_NULL_HANDLE:
            return "Invalid handle argument.";
        case CTL_RESULT_ERROR_INVALID_NULL_POINTER:
            return "Invalid pointer argument.";
        case CTL_RESULT_ERROR_INVALID_SIZE:
            return "Invalid size argument.";
        case CTL_RESULT_ERROR_UNSUPPORTED_SIZE:
            return "Size argument not supported by device.";
        case CTL_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT:
            return "Image format not supported by device.";
        case CTL_RESULT_ERROR_DATA_READ:
            return "Data read error.";
        case CTL_RESULT_ERROR_DATA_WRITE:
            return "Data write error.";
        case CTL_RESULT_ERROR_DATA_NOT_FOUND:
            return "Data not found.";
        case CTL_RESULT_ERROR_NOT_IMPLEMENTED:
            return "Function not implemented.";
        case CTL_RESULT_ERROR_OS_CALL:
            return "Operating system call failed.";
        case CTL_RESULT_ERROR_KMD_CALL:
            return "Kernel mode driver call failed.";
        case CTL_RESULT_ERROR_UNLOAD:
            return "Library unload failed.";
        case CTL_RESULT_ERROR_ZE_LOADER:
            return "Level-0 loader not found.";
        case CTL_RESULT_ERROR_INVALID_OPERATION_TYPE:
            return "Invalid operation type.";
        case CTL_RESULT_ERROR_NULL_OS_INTERFACE:
            return "No operating system interface.";
        case CTL_RESULT_ERROR_NULL_OS_ADAPATER_HANDLE:
            return "No operating system adapter handle.";
        case CTL_RESULT_ERROR_NULL_OS_DISPLAY_OUTPUT_HANDLE:
            return "No operating system display output handle.";
        case CTL_RESULT_ERROR_WAIT_TIMEOUT:
            return "Operation timed out.";
        case CTL_RESULT_ERROR_PERSISTANCE_NOT_SUPPORTED:
            return "Persistence not supported.";
        case CTL_RESULT_ERROR_PLATFORM_NOT_SUPPORTED:
            return "Platform not supported.";
        case CTL_RESULT_ERROR_UNKNOWN_APPLICATION_UID:
            return "Unknown application UID in initialisation call.";
        case CTL_RESULT_ERROR_INVALID_ENUMERATION:
            return "Invalid enumeration value.";
        case CTL_RESULT_ERROR_FILE_DELETE:
            return "Error deleting file.";
        case CTL_RESULT_ERROR_RESET_DEVICE_REQUIRED:
            return "Device requires a reset.";
        case CTL_RESULT_ERROR_FULL_REBOOT_REQUIRED:
            return "Device requires a full reboot.";
        case CTL_RESULT_ERROR_LOAD:
            return "Library load failed.";
        case CTL_RESULT_ERROR_DEVICE_UNAVAILABLE:
            return "Device unavailable.";
        case CTL_RESULT_ERROR_UNKNOWN:
            return "Unknown or internal error.";
        case CTL_RESULT_ERROR_RETRY_OPERATION:
            return "Operation failed, retry the previous operation.";
        case CTL_RESULT_ERROR_IGSC_LOADER:
            return "IGSC library loader not found.";
        case CTL_RESULT_ERROR_RESTRICTED_APPLICATION:
            return "Restricted or unsupported application.";
        case CTL_RESULT_ERROR_CORE_OVERCLOCK_NOT_SUPPORTED:
            return "Overclock not supported.";
        case CTL_RESULT_ERROR_CORE_OVERCLOCK_VOLTAGE_OUTSIDE_RANGE:
            return "Overclock voltage outside acceptable range.";
        case CTL_RESULT_ERROR_CORE_OVERCLOCK_FREQUENCY_OUTSIDE_RANGE:
            return "Overclock frequency outside acceptable range.";
        case CTL_RESULT_ERROR_CORE_OVERCLOCK_POWER_OUTSIDE_RANGE:
            return "Overclock power outside acceptable range.";
        case CTL_RESULT_ERROR_CORE_OVERCLOCK_TEMPERATURE_OUTSIDE_RANGE:
            return "Overclock temperature outside acceptable range.";
        case CTL_RESULT_ERROR_CORE_OVERCLOCK_IN_VOLTAGE_LOCKED_MODE:
            return "Overclock in voltage-locked mode.";
        case CTL_RESULT_ERROR_CORE_OVERCLOCK_RESET_REQUIRED:
            return "Requested change requires device reset to apply.";
        case CTL_RESULT_ERROR_CORE_OVERCLOCK_WAIVER_NOT_SET:
            return "Overclock waiver not set.";
        case CTL_RESULT_ERROR_CORE_OVERCLOCK_DEPRECATED_API:
            return "Deprecated overclock API. Switch to newer API if "
                "available.";
        case CTL_RESULT_ERROR_CORE_LED_GET_STATE_NOT_SUPPORTED_FOR_I2C_LED:
            return "Cannot get LED state for I2C LED.";
        case CTL_RESULT_ERROR_CORE_LED_SET_STATE_NOT_SUPPORTED_FOR_I2C_LED:
            return "Cannot set LED state for I2C LED.";
        case CTL_RESULT_ERROR_CORE_LED_TOO_FREQUENT_SET_REQUESTS:
            return "LED set requests are too frequent.";
        case CTL_RESULT_ERROR_CORE_OVERCLOCK_VRAM_MEMORY_SPEED_OUTSIDE_RANGE:
            return "VRAM memory speed outside acceptable range.";
        case CTL_RESULT_ERROR_CORE_OVERCLOCK_INVALID_CUSTOM_VF_CURVE:
            return "Invalid custom VF curve for overclock.";
        case CTL_RESULT_ERROR_INVALID_AUX_ACCESS_FLAG:
            return "Invalid AUX access flag.";
        case CTL_RESULT_ERROR_INVALID_SHARPNESS_FILTER_FLAG:
            return "Invalid sharpness filter flag.";
        case CTL_RESULT_ERROR_DISPLAY_NOT_ATTACHED:
            return "Display not attached.";
        case CTL_RESULT_ERROR_DISPLAY_NOT_ACTIVE:
            return "Display attached but not active.";
        case CTL_RESULT_ERROR_INVALID_POWERFEATURE_OPTIMIZATION_FLAG:
            return "Invalid power feature optimization flag.";
        case CTL_RESULT_ERROR_INVALID_POWERSOURCE_TYPE_FOR_DPST:
            return "Invalid power source type for DPST (supported only in "
                "DC mode).";
        case CTL_RESULT_ERROR_INVALID_PIXTX_GET_CONFIG_QUERY_TYPE:
            return "Invalid pixel transformation get-configuration query type.";
        case CTL_RESULT_ERROR_INVALID_PIXTX_SET_CONFIG_OPERATION_TYPE:
            return "Invalid pixel transformation set-configuration operation "
                "type.";
        case CTL_RESULT_ERROR_INVALID_SET_CONFIG_NUMBER_OF_SAMPLES:
            return "Invalid number of samples for pixel transformation.";
        case CTL_RESULT_ERROR_INVALID_PIXTX_BLOCK_ID:
            return "Invalid pixel transformation block ID.";
        case CTL_RESULT_ERROR_INVALID_PIXTX_BLOCK_TYPE:
            return "Invalid pixel transformation block type.";
        case CTL_RESULT_ERROR_INVALID_PIXTX_BLOCK_NUMBER:
            return "Invalid pixel transformation block number.";
        case CTL_RESULT_ERROR_INSUFFICIENT_PIXTX_BLOCK_CONFIG_MEMORY:
            return "Insufficient memory allocated for pixel transformation "
                "block configurations.";
        case CTL_RESULT_ERROR_3DLUT_INVALID_PIPE:
            return "Invalid 3D LUT pipe.";
        case CTL_RESULT_ERROR_3DLUT_INVALID_DATA:
            return "Invalid 3D LUT data.";
        case CTL_RESULT_ERROR_3DLUT_NOT_SUPPORTED_IN_HDR:
            return "3D LUT not supported in HDR.";
        case CTL_RESULT_ERROR_3DLUT_INVALID_OPERATION:
            return "Invalid 3D LUT operation.";
        case CTL_RESULT_ERROR_3DLUT_UNSUCCESSFUL:
            return "3D LUT call unsuccessful.";
        case CTL_RESULT_ERROR_AUX_DEFER:
            return "AUX defer failure.";
        case CTL_RESULT_ERROR_AUX_TIMEOUT:
            return "AUX timeout.";
        case CTL_RESULT_ERROR_AUX_INCOMPLETE_WRITE:
            return "AUX incomplete write failure.";
        case CTL_RESULT_ERROR_I2C_AUX_STATUS_UNKNOWN:
            return "I2C/AUX status unknown.";
        case CTL_RESULT_ERROR_I2C_AUX_UNSUCCESSFUL:
            return "I2C/AUX unsuccessful.";
        case CTL_RESULT_ERROR_LACE_INVALID_DATA_ARGUMENT_PASSED:
            return "Invalid LACE data argument passed.";
        case CTL_RESULT_ERROR_EXTERNAL_DISPLAY_ATTACHED:
            return "External display attached; display switch failed.";
        case CTL_RESULT_ERROR_CUSTOM_MODE_STANDARD_CUSTOM_MODE_EXISTS:
            return "Standard custom mode already exists.";
        case CTL_RESULT_ERROR_CUSTOM_MODE_NON_CUSTOM_MATCHING_MODE_EXISTS:
            return "Non-custom matching mode exists.";
        case CTL_RESULT_ERROR_CUSTOM_MODE_INSUFFICIENT_MEMORY:
            return "Insufficient memory for custom mode.";
        case CTL_RESULT_ERROR_ADAPTER_ALREADY_LINKED:
            return "Adapter already linked.";
        case CTL_RESULT_ERROR_ADAPTER_NOT_IDENTICAL:
            return "Adapter not identical for linking.";
        case CTL_RESULT_ERROR_ADAPTER_NOT_SUPPORTED_ON_LDA_SECONDARY:
            return "Adapter not supported on LDA secondary.";
        case CTL_RESULT_ERROR_SET_FBC_FEATURE_NOT_SUPPORTED:
            return "Set FBC feature not supported.";
        default:
            return std::to_string(status);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::igcl_category
 */
const std::error_category& PWROWG_DETAIL_NAMESPACE::igcl_category(
        void) noexcept {
    static const igcl_error_category retval;
    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::throw_if_igcl_failed
 */
void PWROWG_DETAIL_NAMESPACE::throw_if_igcl_failed(
        _In_ const ctl_result_t status,
        _In_opt_z_ const char *message) {
    if (status > CTL_RESULT_ERROR_SUCCESS_END) {
        if (message == nullptr) {
            throw std::system_error(status, igcl_category());
        } else {
            throw std::system_error(status, igcl_category(), message);
        }
    }
}

#endif /* defined(POWER_OVERWHELMING_WITH_IGCL) */
