// <copyright file="fnv1a.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE.txt file in the project root for full licence information.
// </copyright>
// <author>Christoph Müller</author>

#include "fnv1a.h"


/*
 * PWROWG_DETAIL_NAMESPACE::fnv1a<std::uint32_t>::fnv1a
 */
PWROWG_DETAIL_NAMESPACE::fnv1a<std::uint32_t>::fnv1a(void) noexcept
    : _value(0x811c9dc5) {}


/*
 * PWROWG_DETAIL_NAMESPACE::fnv1a<std::uint64_t>::fnv1a
 */
PWROWG_DETAIL_NAMESPACE::fnv1a<std::uint64_t>::fnv1a(void) noexcept
    : _value(0xcbf29ce484222325) {}
