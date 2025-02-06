// <copyright file="type_collapse.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TYPE_COLLAPSE_H)
#define _PWROWG_TYPE_COLLAPSE_H
#pragma once

#include "visus/pwrowg/api.h"

PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Collapses an arbitrary number of types to <c>void</c>.
/// </summary>
/// <typeparam name="TTypes">The types in the list.</typeparam>
template<class... TTypes>
using type_collapse = void;

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_TYPE_COLLAPSE_H) */
