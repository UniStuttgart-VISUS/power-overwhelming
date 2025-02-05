// <copyright file="type_list.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TYPE_LIST_H)
#define _PWROWG_TYPE_LIST_H
#pragma once


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A list of zero or more types.
/// </summary>
/// <typeparam name="TTypes">The types in the list.</typeparam>
template<class... TTypes> struct type_list { };

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_REGISTRY_H) */
