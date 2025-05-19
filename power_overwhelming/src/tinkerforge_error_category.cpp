// <copyright file="tinkerforge_error_category.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_error_category.h"

#include <string>

#include <ip_connection.h>


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_error_category::default_error_condition
 */
std::error_condition
PWROWG_DETAIL_NAMESPACE::tinkerforge_error_category::default_error_condition(
        int status) const noexcept {
    return std::error_condition(status, tinkerforge_category());
}


/*
 * PWROWG_DETAIL_NAMESPACE::message
 */
std::string PWROWG_DETAIL_NAMESPACE::tinkerforge_error_category::message(
        int status) const {
    switch (status) {
        case E_OK:
            return "The operation completed successfully.";

        case E_TIMEOUT:
            return "The operation timed out.";

        case E_NO_STREAM_SOCKET:
            return "Failed to create a stream socket.";

        case E_HOSTNAME_INVALID:
            return "The given host name is invalid.";

        case E_NO_CONNECT:
            return "Failed to connect.";

        case E_NO_THREAD:
            return "Failed to start a thread.";

        case E_NOT_ADDED:
            return "E_NOT_ADDED";   // This is unused according to the docs.

        case E_ALREADY_CONNECTED:
            return "The connection has already been established.";

        case E_NOT_CONNECTED:
            return "The connection has not been established.";

        case E_INVALID_PARAMETER:
            return "A parameter has an invalid value.";

        case E_NOT_SUPPORTED:
            return "The operation is not supported.";

        case E_UNKNOWN_ERROR_CODE:
            return "An unknown device error occurred.";

        case E_STREAM_OUT_OF_SYNC:
            return "The stream is out of sync.";

        case E_INVALID_UID:
            return "The specified unique identifier is invalid.";

        case E_NON_ASCII_CHAR_IN_SECRET:
            return "Non-ASCII characters are not allowed in secrets.";

        case E_WRONG_DEVICE_TYPE:
            return "The device has an unexpected type.";

        case E_DEVICE_REPLACED:
            return "The device has been replaced.";

        case E_WRONG_RESPONSE_LENGTH:
            return "The response has an unexpected length.";

        default:
            return std::to_string(status);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_category
 */
const std::error_category& PWROWG_DETAIL_NAMESPACE::tinkerforge_category(
        void) noexcept {
    static const tinkerforge_error_category retval;
    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::throw_if_tinkerforge_failed
 */
void PWROWG_DETAIL_NAMESPACE::throw_if_tinkerforge_failed(
        _In_ const int status,
        _In_opt_z_ const char *message) {
    if (status < 0) {
        if (message == nullptr) {
            throw std::system_error(status, tinkerforge_category());
        } else {
            throw std::system_error(status, tinkerforge_category(), message);
        }
    }
}
