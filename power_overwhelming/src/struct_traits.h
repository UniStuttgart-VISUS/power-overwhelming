// <copyright file="struct_traits.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_STRUCT_TRAITS_H)
#define _PWROWG_STRUCT_TRAITS_H
#pragma once

#include <cassert>
#include <cstdlib>
#include <cinttypes>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN


/// <summary>
/// Gets the member at the specified <paramref name="offset" /> in
/// <paramref name="object" />.
/// </summary>
/// <typeparam name="TMember"></typeparam>
/// <typeparam name="TObject"></typeparam>
/// <param name="object"></param>
/// <param name="offset"></param>
/// <returns></returns>
template<class TMember, class TObject> constexpr const TMember& member_at(
        _In_ const TObject& object,
        _In_ const std::size_t offset) {
    assert(offset <= sizeof(TObject) - sizeof(TMember));
    auto o = reinterpret_cast<const std::uint8_t *>(std::addressof(object));
    return *reinterpret_cast<const TMember *>(o + offset);
}


/// <summary>
/// Answer the offset of the given <paramref name="member" /> from the start
/// of its containing <paramref name="object" />.
/// </summary>
/// <typeparam name="TObject"></typeparam>
/// <typeparam name="TMember"></typeparam>
/// <param name="object"></param>
/// <param name="member"></param>
/// <returns></returns>
template<class TObject, class TMember> constexpr std::size_t member_offset(
        _In_opt_ const TObject *object,
        _In_ const TMember *member) {
    auto o = reinterpret_cast<const std::uint8_t *>(object);
    auto m = reinterpret_cast<const std::uint8_t *>(member);
    assert(m >= o);
    const auto retval = (m - o);
    assert(retval < sizeof(TObject));
    return retval;
}

PWROWG_DETAIL_NAMESPACE_END

#endif /* defined(_PWROWG_STRUCT_TRAITS_H) */
