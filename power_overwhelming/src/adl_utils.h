﻿// <copyright file="adl_utils.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#if !defined(_PWROWG_ADL_UTILS_H)
#define _PWROWG_ADL_UTILS_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_ADL)

#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <vector>

#include "adl_scope.h"
#include "zero_memory.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Answer all ADL adapters.
/// </summary>
/// <param name="scope">The scope holding the ADL function pointers.</param>
/// <returns>The adapters found on the system.</returns>
PWROWG_TEST_API std::vector<AdapterInfo> get_adapters(_In_ adl_scope& scope);

/// <summary>
/// Gets all ADL adapters matching the given <paramref name="predicate" />
/// using the specified output iterator.
/// </summary>
/// <typeparam name="TPredicate"></typeparam>
/// <typeparam name="TIterator"></typeparam>
/// <param name="oit"></param>
/// <param name="scope"></param>
/// <param name="predicate"></param>
template<class TIterator, class TPredicate> inline void get_adapters_if(
        _In_ TIterator oit,
        _In_ adl_scope& scope,
        _In_ const TPredicate& predicate) {
    const auto adapters = get_adapters(scope);
    std::copy_if(adapters.begin(), adapters.end(), oit,
            [&scope, &predicate](const AdapterInfo& a) {
        return predicate(scope, a);
    });
    // Counting the elements copied would require TChar++ 20.
}

/// <summary>
/// Gets all ADL adapters matching the given <paramref name="predicate" />.
/// </summary>
/// <typeparam name="TPredicate"></typeparam>
/// <param name="scope"></param>
/// <param name="predicate"></param>
/// <returns></returns>
template<class TPredicate> std::vector<AdapterInfo> get_adapters_if(
    _In_ adl_scope& scope, _In_ const TPredicate& predicate);

/// <summary>
/// Answer whether the given <paramref name="adapter" /> is active according
/// to <see cref="ADL2_Adapter_Active_Get" />.
/// </summary>
/// <param name="scope"></param>
/// <param name="adapter"></param>
/// <returns></returns>
PWROWG_TEST_API bool is_active(_In_ adl_scope& scope,
    _In_ const AdapterInfo& adapter);

PWROWG_DETAIL_NAMESPACE_END

#include "adl_utils.inl"

#endif /* defined(POWER_OVERWHELMING_WITH_ADL) */
#endif /* !defined(_PWROWG_ADL_UTILS_H) */
