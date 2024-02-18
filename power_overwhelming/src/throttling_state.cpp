// <copyright file="throttling_state.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/throttling_state.h"

#include <type_traits>


/*
 * visus::power_overwhelming::operator |
 */
visus::power_overwhelming::throttling_state
visus::power_overwhelming::operator |(_In_ const throttling_state lhs,
        _In_ const throttling_state rhs) {
    typedef std::underlying_type<throttling_state>::type mask_type;
    auto retval = static_cast<mask_type>(lhs) | static_cast<mask_type>(rhs);
    return static_cast<throttling_state>(retval);
}


/*
 * visus::power_overwhelming::operator |
 */
visus::power_overwhelming::throttling_state
visus::power_overwhelming::operator &(_In_ const throttling_state lhs,
        _In_ const throttling_state rhs) {
    typedef std::underlying_type<throttling_state>::type mask_type;
    auto retval = static_cast<mask_type>(lhs) | static_cast<mask_type>(rhs);
    return static_cast<throttling_state>(retval);
}
