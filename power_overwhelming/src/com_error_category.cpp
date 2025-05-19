// <copyright file="com_error_category.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "com_error_category.h"

#if defined(_WIN32)
#include <codecvt>
#include <vector>

#include <comdef.h>


/*
 * PWROWG_DETAIL_NAMESPACE::detail::com_error_category::default_error_condition
 */
std::error_condition
PWROWG_DETAIL_NAMESPACE::com_error_category::default_error_condition(
        const int hr) const noexcept {
    auto error = HRESULT_CODE(hr);

    if (error || (hr == ERROR_SUCCESS)) {
        // 'hr' is a default Windows code mapped to HRESULT.
        return std::system_category().default_error_condition(error);
    } else {
        // This is an actual COM error.
        return std::error_condition(hr, com_category());
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::message
 */
std::string PWROWG_DETAIL_NAMESPACE::com_error_category::message(
        int hr) const {
    _com_error e(hr);

#if (defined(UNICODE) || defined(_UNICODE))
    std::size_t cnt = 0;
    std::vector<char> buffer(::wcslen(e.ErrorMessage()) + 1, 0);
    ::wcstombs_s(&cnt, buffer.data(), buffer.size(), e.ErrorMessage(),
        _TRUNCATE);
    return std::string(buffer.data(), buffer.data() + cnt);
#else /* (defined(UNICODE) || defined(_UNICODE)) */
    return e.ErrorMessage();
#endif /* (defined(UNICODE) || defined(_UNICODE)) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::com_category
 */
const std::error_category& PWROWG_DETAIL_NAMESPACE::com_category(
        void) noexcept {
    static const com_error_category retval;
    return retval;
}
#endif /* defined(_WIN32) */
