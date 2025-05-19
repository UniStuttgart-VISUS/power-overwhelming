// <copyright file="tinkerforge_exception.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TINKERFORGE_EXCEPTION_H)
#define _PWROWG_TINKERFORGE_EXCEPTION_H

#pragma once

#include <stdexcept>
#include <string>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// An exception representing an error in the Tinkerforge API.
/// </summary>
class PWROWG_TEST_API tinkerforge_exception final
        : public std::runtime_error {

public:

    /// <summary>
    /// The native error type.
    /// </summary>
    typedef int value_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="code">The error code, which also determines the error
    /// message.</param>
    tinkerforge_exception(const value_type code);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="code">The error code.</param>
    /// <param name="message">A custom error message.</param>
    tinkerforge_exception(const value_type code, const std::string& message)
        : std::runtime_error(message.c_str()), _code(code) { }

    /// <summary>
    /// Answer the native error code associated with the exception.
    /// </summary>
    /// <returns></returns>
    value_type code(void) const noexcept {
        return this->_code;
    }

private:

    value_type _code;
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_TINKERFORGE_EXCEPTION_H) */
