// <copyright file="type_list.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TYPE_LIST_H)
#define _PWROWG_TYPE_LIST_H
#pragma once

#include <cinttypes>
#include <type_traits>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A list of zero or more types.
/// </summary>
/// <typeparam name="TTypes">The types in the list.</typeparam>
template<class... TTypes> struct type_list { };


/// <summary>
/// Extracts the <paramref name="Index" />th type from a
/// <see cref="type_list" />.
/// </summary>
/// <typeparam name="TList"></typeparam>
/// <typeparam name="Index"></typeparam>
template<std::size_t Index, class TList>
struct type_list_at { };

/// <summary>
/// Recursion case where the requested <typeparamref name="Index" /> has not yet
/// been reached.
/// </summary>
template<std::size_t Index, class THead, class... TTail>
struct type_list_at<Index, type_list<THead, TTail...>> {
    typedef typename type_list_at<Index - 1, type_list<TTail...>>::type type;
};

/// <summary>
/// Specialisation extracting <typeparamref name="THead" />.
/// </summary>
template<class THead, class... TTail>
struct type_list_at<0, type_list<THead, TTail...>> {
    typedef THead type;
};

/// <summary>
/// Extracts the <paramref name="Index" />th type from a
/// <see cref="type_list" />.
/// </summary>
/// <typeparam name="TList"></typeparam>
/// <typeparam name="Index"></typeparam>
template<std::size_t Index, class TList>
using type_list_at_t = typename type_list_at<Index, TList>::type;


/// <summary>
/// Appends <typeparamref name="TType" /> to a <see cref="type_list" />.
/// </summary>
/// <typeparam name="TList"></typeparam>
/// <typeparam name="TType"></typeparam>
template<class TList, class TType>
struct type_list_cat { };

/// <summary>
/// Specialisation for two <see cref="type_list" />s.
/// </summary>
template<class TType, class... TTypes>
struct type_list_cat<type_list<TTypes...>, TType> {
    typedef type_list<TTypes..., TType> type;
};

/// <summary>
/// Specialisation for an empty<see cref="type_list" />s.
/// </summary>
template<class... TTypes>
struct type_list_cat<type_list<TTypes...>, type_list<>> {
    typedef type_list<TTypes...> type;
};

/// <summary>
/// Specialisation for actual <see cref="type_list" />s.
/// </summary>
template<class... TTypes, class... TOthers>
struct type_list_cat<type_list<TTypes...>, type_list<TOthers...>> {
    typedef type_list<TTypes..., TOthers...> type;
};


/// <summary>
/// Appends <typeparamref name="TType" /> to a <see cref="type_list" />.
/// </summary>
/// <typeparam name="TList"></typeparam>
/// <typeparam name="TType"></typeparam>
template<class TList, class TType>
using type_list_cat_t = typename type_list_cat<TList, TType>::type;


/// <summary>
/// Generates a new <see cref="type_list" /> holding only the types in
/// <typeparamref name="TList" /> that match <typeparamref name="TPredicate" />.
/// </summary>
/// <typeparam name="TList"></typeparam>
template<template<class> class TPredicate, class TList>
struct type_list_filter { };

/// <summary>
/// Recursive filtering of a <see cref="type_list" /> .
/// </summary>
template<template<class> class TPredicate, class THead, class... TTail>
struct type_list_filter<TPredicate, type_list<THead, TTail...>> {
    typedef type_list<THead> head_type;
    typedef type_list<TTail...> tail_type;
    typedef type_list_cat_t<
        typename type_list_filter<TPredicate, head_type>::type,
        typename type_list_filter<TPredicate, tail_type>::type> type;
};

/// <summary>
/// Recursion stop for <see cref="type_list_filter" />.
/// </summary>
template<template<class> class TPredicate, class THead>
struct type_list_filter<TPredicate, type_list<THead>> {
    typedef std::conditional_t<TPredicate<THead>::value,
        type_list<THead>,
        type_list<>> type;
};

/// <summary>
/// Generates a new <see cref="type_list" /> holding only the types in
/// <typeparamref name="TList" /> that match <typeparamref name="TPredicate" />.
/// </summary>
/// <typeparam name="TList"></typeparam>
template<template<class> class TPredicate, class TList>
using type_list_filter_t = typename type_list_filter<TPredicate, TList>::type;

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_REGISTRY_H) */
