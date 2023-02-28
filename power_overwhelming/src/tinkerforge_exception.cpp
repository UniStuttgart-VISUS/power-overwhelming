// <copyright file="tinkerforge_exception.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_exception.h"

#include <ip_connection.h>


/// <summary>
/// Get a human-readable error description for the given Tinkerforge error code.
/// </summary>
/// <param name="code"></param>
/// <returns></returns>
static std::string tinkerforge_to_string(const int code) {
    switch (code) {
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
            return std::to_string(code);
    }
}

/*
 * visus::power_overwhelming::tinkerforge_exception::tinkerforge_exception
 */
visus::power_overwhelming::tinkerforge_exception::tinkerforge_exception(
        const value_type code)
    : std::exception(tinkerforge_to_string(code).c_str()), _code(code) { }
