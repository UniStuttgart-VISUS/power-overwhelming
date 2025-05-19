// <copyright file="rtx_trigger_coupling.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_trigger_coupling.h"

#include <stdexcept>


/*
 * PWROWG_NAMESPACE::parse_rtx_trigger_coupling
 */
PWROWG_NAMESPACE::rtx_trigger_coupling
PWROWG_NAMESPACE::parse_rtx_trigger_coupling(_In_z_ const wchar_t *str) {
#define _GCC_IS_SHIT(v) L##v
#define _FROM_STRING_CASE(v) if (::wcscmp(str, _GCC_IS_SHIT(#v)) == 0) \
return rtx_trigger_coupling::v

    if (str == nullptr) {
        throw std::invalid_argument("The string to be parsed not not be null.");
    }

    _FROM_STRING_CASE(direct_current);
    _FROM_STRING_CASE(alternating_current);
    _FROM_STRING_CASE(low_frequency_reject);

    throw std::invalid_argument("The specified string could not be parsed as "
        "trigger coupling. Make sure to add all new enumeration members in "
        "the parsing function.");

#undef _GCC_IS_SHIT
#undef _FROM_STRING_CASE
}


/*
 * PWROWG_NAMESPACE::to_string
 */
_Ret_valid_ const wchar_t *PWROWG_NAMESPACE::to_string(
        _In_ const rtx_trigger_coupling value) {
#define _GCC_IS_SHIT(v) L##v
#define _TO_STRING_CASE(v) case rtx_trigger_coupling::v:\
    return _GCC_IS_SHIT(#v)

    switch (value) {
        _TO_STRING_CASE(direct_current);
        _TO_STRING_CASE(alternating_current);
        _TO_STRING_CASE(low_frequency_reject);

        default:
            throw std::invalid_argument("The specified trigger coupling is "
                "unknown. Make sure to add all new enumeration members in "
                "to_string.");
    }

#undef _GCC_IS_SHIT
#undef _TO_STRING_CASE
}
