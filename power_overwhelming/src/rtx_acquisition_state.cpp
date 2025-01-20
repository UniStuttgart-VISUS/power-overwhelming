// <copyright file="rtx_acquisition_state.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_acquisition_state.h"

#include <stdexcept>


/*
 * PWROWG_NAMESPACE::rtx_acquisition_state
 */
PWROWG_NAMESPACE::rtx_acquisition_state
PWROWG_NAMESPACE::parse_rtx_acquisition_state(
        _In_z_ const wchar_t *str) {
#define _GCC_IS_SHIT(v) L##v
#define _FROM_STRING_CASE(v) if (::wcscmp(str, _GCC_IS_SHIT(#v)) == 0) \
return rtx_acquisition_state::v

    if (str == nullptr) {
        throw std::invalid_argument("The string to be parsed not not be null.");
    }

    _FROM_STRING_CASE(run);
    _FROM_STRING_CASE(stop);
    _FROM_STRING_CASE(interrupt);
    _FROM_STRING_CASE(single);

    throw std::invalid_argument("The specified string could not be parsed as "
        "an acquisition state. Make sure to add all new enumeration members in "
        "the parsing function.");

#undef _GCC_IS_SHIT
#undef _FROM_STRING_CASE
}

/*
 * PWROWG_NAMESPACE::to_string
 */
_Ret_valid_ const wchar_t *PWROWG_NAMESPACE::to_string(
        _In_ const rtx_acquisition_state state) {
#define _GCC_IS_SHIT(v) L##v
#define _TO_STRING_CASE(v) case rtx_acquisition_state::v:\
    return _GCC_IS_SHIT(#v)

    switch (state) {
        _TO_STRING_CASE(run);
        _TO_STRING_CASE(stop);
        _TO_STRING_CASE(interrupt);
        _TO_STRING_CASE(single);

        default:
            throw std::invalid_argument("The specified acquisition state is "
                "unknown. Make sure to add all new enumeration members in "
                "to_string.");
    }

#undef _GCC_IS_SHIT
#undef _TO_STRING_CASE
}
