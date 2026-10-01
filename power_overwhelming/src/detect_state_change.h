// <copyright file="detect_state_change.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DETECT_STATE_CHANGE_H)
#define _PWROWG_DETECT_STATE_CHANGE_H
#pragma once

#include "detector.h"
#include "sensor_state.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// The detector type for sensors that want to be notified of state changes via
/// the <see ref="has_state_change" />.
/// </summary>
/// <typeparam name="TType">The type to be check for the state change method.
/// </typeparam>
template<class TType>
using _state_change = decltype(std::declval<TType &>().state_change(
    std::declval<sensor_state::value_type>()));

/// <summary>
/// Detects whether <typeparamref name="TType" /> has a <c>state_change</c>
/// method the <see cref="sensor_array" /> should call when its state changes.
/// </summary>
/// <typeparam name="TType">The type to be check for the state change method.
/// </typeparam>
template<class TType>
using has_state_change = typename detector<_state_change, void, TType>::type;

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_DETECT_STATE_CHANGE_H) */
