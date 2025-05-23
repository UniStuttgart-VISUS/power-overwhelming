﻿// <copyright file="nvapi_error_category.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_NVAPI_ERROR_CATEGORY_H)
#define _PWROWG_NVAPI_ERROR_CATEGORY_H
#pragma once

#include <system_error>

#include "visus/pwrowg/api.h"

#if defined(POWER_OVERWHELMING_WITH_NVAPI)
#include <nvapi.h>


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// An error category for <see cref="NvAPI_Status" />.
/// </summary>
class PWROWG_TEST_API nvapi_error_category final : public std::error_category {

public:

    using std::error_category::error_category;

    /// <summary>
    /// Converts the error code into a portable description.
    /// </summary>
    /// <param name="status">The error code to be converted.</param>
    /// <returns>The portable description of the NVAPI error.</returns>
    std::error_condition default_error_condition(
        _In_ int status) const noexcept override;

    /// <summary>
    /// Convert the given error code into a string.
    /// </summary>
    /// <param name="status">The error code to get the message for.</param>
    /// <returns>The error message associated with the error code.
    /// </returns>
    std::string message(_In_ int status) const override;

    /// <summary>
    /// Answer the name of the error category.
    /// </summary>
    /// <returns>The name of the category.</returns>
    inline const char *name(void) const noexcept override {
        return "NVAPI";
    }
};


/// <summary>
/// Answer the one and only <see cref="nvapi_error_category" />.
/// </summary>
/// <returns>The only instance of <see cref="nvapi_error_category" />.
/// </returns>
PWROWG_TEST_API const std::error_category& nvapi_category(void) noexcept;

/// <summary>
/// Check whether <paramref name="status" /> indicates failure, and if so,
/// throw an exception.
/// </summary>
/// <param name="status">The status code to be checked.</param>
/// <param name="message">An optional error message to be included in the
/// exception.</param>
/// <exception cref="std::system_error">If <paramref name="status" /> indicates
/// failure.</exception>
PWROWG_TEST_API void throw_if_nvapi_failed(_In_ const NvAPI_Status status,
    _In_opt_z_ const char *message = nullptr);

PWROWG_DETAIL_NAMESPACE_END


namespace std {

    /// <summary>
    /// Tell STL that <see cref="NvAPI_Status" /> is an error code enumeration.
    /// </summary>
    template<> struct is_error_code_enum<NvAPI_Status> : true_type { };

    /// <summary>
    /// Allow STL to convert a <see cref="NvAPI_Status" /> into a generic error
    /// code.
    /// </summary>
    /// <param name="e">The NVAPI status to be converted.</param>
    /// <returns>The generic error code.</returns>
    inline std::error_code make_error_code(const NvAPI_Status e) noexcept {
        return std::error_code(
            static_cast<int>(e),
            PWROWG_DETAIL_NAMESPACE::nvapi_category());
    }
}

#endif /* defined(POWER_OVERWHELMING_WITH_NVAPI) */
#endif /* !defined(_PWROWG_NVAPI_ERROR_CATEGORY_H) */
