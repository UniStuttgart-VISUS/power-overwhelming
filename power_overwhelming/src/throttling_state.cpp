// <copyright file="throttling_state.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/throttling_state.h"

#include <type_traits>


/*
 * PWROWG_NAMESPACE::operator |
 */
PWROWG_NAMESPACE::throttling_state PWROWG_NAMESPACE::operator |(
        _In_ const throttling_state lhs,
        _In_ const throttling_state rhs) {
    typedef std::underlying_type<throttling_state>::type mask_type;
    auto retval = static_cast<mask_type>(lhs) | static_cast<mask_type>(rhs);
    return static_cast<throttling_state>(retval);
}


/*
 * PWROWG_NAMESPACE::operator &
 */
PWROWG_NAMESPACE::throttling_state PWROWG_NAMESPACE::operator &(
        _In_ const throttling_state lhs,
        _In_ const throttling_state rhs) {
    typedef std::underlying_type<throttling_state>::type mask_type;
    auto retval = static_cast<mask_type>(lhs) | static_cast<mask_type>(rhs);
    return static_cast<throttling_state>(retval);
}
