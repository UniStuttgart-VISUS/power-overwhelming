// <copyright file="dispatch_list.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DISPATCH_LIST_H)
#define _PWROWG_DISPATCH_LIST_H
#pragma once

#include <cstdlib>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A list to dispatch on (for instance enumeration) values that are defined at
/// compile time.
/// </summary>
/// <typeparam name="TType">The (enumeration) type.</typeparam>
/// <typeparam name="Values">The values to dispatch.</typeparam>
template<class TType, TType... Values> struct dispatch_list final {
    static constexpr std::size_t size = sizeof...(Values);
};


/// <summary>
/// Selects the element at index <paramref name="Idx" /> from a
/// <see cref="dispatch_list" />.
/// </summary>
/// <typeparam name="Idx">The index of the element to select.</typeparam>
/// <typeparam name="TList">The list to select from.</typeparam>
template<std::size_t Idx, class TList> struct dispatch_list_at;

/// <summary>
/// Specialisation for actual dispatch lists.
/// </summary>
template<std::size_t Idx, class TType, TType Head, TType... Tail>
struct dispatch_list_at<Idx, dispatch_list<TType, Head, Tail...>> final {
    typedef dispatch_list_at<Idx - 1, dispatch_list<TType, Tail...>> _tail;
    static constexpr TType value = (Idx == 0) ? Head : _tail::value;
};

/// <summary>
/// Recursion stop for dispatch list accessor.
/// </summary>
template<class TType, TType Head, TType... Tail>
struct dispatch_list_at<0, dispatch_list<TType, Head, Tail...>> final {
    static constexpr TType value = Head;
};


/// <summary>
/// Selects the element at index <paramref name="Idx" /> from a
/// <see cref="dispatch_list" />.
/// </summary>
/// <typeparam name="Idx">The index of the element to select.</typeparam>
/// <typeparam name="TList">The list to select from.</typeparam>
template<std::size_t Idx, class TList>
constexpr auto dispatch_list_at_v = dispatch_list_at<Idx, TList>::value;

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_DISPATCH_LIST_H) */
