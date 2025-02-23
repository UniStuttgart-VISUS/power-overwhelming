// <copyright file="adl_exception.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#if !defined(_PWROWG_ADL_EXCEPTION_H)
#define _PWROWG_ADL_EXCEPTION_H
#pragma once

#include <stdexcept>
#include <string>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// An exception caused by a failure in the AMD Display Library.
/// </summary>
class PWROWG_TEST_API adl_exception : public std::runtime_error {

public:

    /// <summary>
    /// The native error type.
    /// </summary>
    typedef int value_type;

    /// <summary>
    /// Tests wheher <paramref name="status" /> indicates an ADL error.
    /// </summary>
    /// <param name="status">The error code to be tested.</param>
    /// <returns><c>true</c> if <paramref name="status" /> indicates an error,
    /// <c>false</c> otherwise.</returns>
    static bool check_error(_In_ const value_type status);

    /// <summary>
    /// If <paramref name="status" /> indicates an ADL error, throw a
    /// <see cref="adl_exception" />.
    /// </summary>
    /// <param name="status">The error code to be tested.</param>
    /// <exception cref="adl_exception">If the given status code
    /// represents an error state.</exception>
    static void throw_on_error(_In_ const value_type status);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="code">The error code, which also determines the error
    /// message.</param>
    adl_exception(_In_ const value_type code);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="code">The error code.</param>
    /// <param name="message">A custom error message.</param>
    adl_exception(_In_ const value_type code, _In_  const std::string& message)
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

#endif /* !defined(_PWROWG_ADL_EXCEPTION_H) */
