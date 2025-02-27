// <copyright file="com_error_category.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_COM_ERROR_CATEGORY_H)
#define _PWROWG_COM_ERROR_CATEGORY_H
#pragma once

#include <system_error>

#if defined(_WIN32)
#include <Windows.h>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// An error category for HRESULTs obtained from calls to COM APIs.
/// </summary>
class PWROWG_TEST_API com_error_category final : public std::error_category {

public:

    using std::error_category::error_category;

    /// <summary>
    /// Converts the error code into a portable description.
    /// </summary>
    /// <param name="hr">The error code to be converted.</param>
    /// <returns>The portable description of the COM error.</returns>
    std::error_condition default_error_condition(
        int hr) const noexcept override;

    /// <summary>
    /// Convert the given error code into a string.
    /// </summary>
    /// <param name="hr">The error code to get the message for.</param>
    /// <returns>The error message associated with the error code.
    /// </returns>
    std::string message(int hr) const override;

    /// <summary>
    /// Answer the name of the error category.
    /// </summary>
    /// <returns>The name of the category.</returns>
    inline const char *name(void) const noexcept override {
        return "Component Object Model";
    }
};


/// <summary>
/// Answer the one and only <see cref="com_error_category" />.
/// </summary>
/// <returns>The only instance of <see cref="com_error_category" />.
/// </returns>
const std::error_category& com_category(void) noexcept;

PWROWG_DETAIL_NAMESPACE_END


namespace std {

    /// <summary>
    /// Tell STL that <see cref="HRESULT" /> is an error code enumeration.
    /// </summary>
    template<> struct is_error_code_enum<HRESULT> : true_type { };

    /// <summary>
    /// Allow STL to convert a <see cref="HRESULT" /> into a generic error
    /// code.
    /// </summary>
    /// <param name="e">The COM error to be converted.</param>
    /// <returns>The generic error code.</returns>
    inline std::error_code make_error_code(const HRESULT e) noexcept {
        return std::error_code(static_cast<int>(e),
            PWROWG_DETAIL_NAMESPACE::com_category());
    }
}

#else /* defined(_WIN32) */

/// <summary>
/// Answer the one and only <see cref="com_error_category" />.
/// </summary>
/// <returns>The only instance of <see cref="com_error_category" />.
/// </returns>
inline PWROWG_TEST_API const std::error_category& com_category(void) noexcept {
    return std::system_category();
}

#endif /* defined(_WIN32) */

#endif /* !defined(_PWROWG_COM_ERROR_CATEGORY_H) */