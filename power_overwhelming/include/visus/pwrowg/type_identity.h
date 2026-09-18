// <copyright file="type_identity.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TYPE_IDENTITY_H)
#define _PWROWG_TYPE_IDENTITY_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Creates a deduced context for <typeparamref name="TType" /> via an identity
/// transform.
/// </summary>
/// <typeparam name="TType">A type.</typeparam>
template<class TType> struct type_identity final {
    typedef TType type;
};


/// <summary>
/// Creates a deduced context for <typeparamref name="TType" /> via an identity
/// transform.
/// </summary>
/// <typeparam name="TType">A type.</typeparam>
template< class TType>
using type_identity_t = type_identity<TType>::type;

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_TYPE_IDENTITY_H) */
