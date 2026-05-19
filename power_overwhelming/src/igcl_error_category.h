// <copyright file="igcl_error_category.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_IGCL_ERROR_CATEGORY_H)
#define _PWROWG_IGCL_ERROR_CATEGORY_H
#pragma once

#include <system_error>

#include "visus/pwrowg/api.h"

#if defined(POWER_OVERWHELMING_WITH_IGCL)
#include <igcl_api.h>


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// An error category for <see cref="ctl_result_t" />.
/// </summary>
class PWROWG_TEST_API igcl_error_category final : public std::error_category {

public:

    using std::error_category::error_category;

    /// <summary>
    /// Converts the error code into a portable description.
    /// </summary>
    /// <param name="status">The error code to be converted.</param>
    /// <returns>The portable description of the NVML error.</returns>
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
        return "NVML";
    }
};


/// <summary>
/// Answer the one and only <see cref="igcl_error_category" />.
/// </summary>
/// <returns>The only instance of <see cref="igcl_error_category" />.
/// </returns>
PWROWG_TEST_API const std::error_category& igcl_category(void) noexcept;

/// <summary>
/// Check whether <paramref name="status" /> indicates failure, and if so,
/// throw an exception.
/// </summary>
/// <param name="status">The status code to be checked.</param>
/// <param name="message">An optional error message to be included in the
/// exception.</param>
/// <exception cref="std::system_error">If <paramref name="status" /> indicates
/// failure.</exception>
PWROWG_TEST_API void throw_if_igcl_failed(_In_ const ctl_result_t status,
    _In_opt_z_ const char *message = nullptr);

PWROWG_DETAIL_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_IGCL) */
#endif /* !defined(_PWROWG_IGCL_ERROR_CATEGORY_H) */
