// <copyright file="detector.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DETECTOR_H)
#define _PWROWG_DETECTOR_H
#pragma once

#include "type_collapse.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Detector for a method as described on
/// https://stackoverflow.com/questions/87372/check-if-a-class-has-a-member-function-of-a-given-signature.
/// </summary>
/// <typeparam name="TFunc"></typeparam>
/// <typeparam name="TVoid"></typeparam>
/// <typeparam name="TArgs"></typeparam>
template<template<class...> class TFunc, class TVoid, class... TArgs>
struct detector : std::false_type { };


/// <summary>
/// Specialisation for types that have the method.
/// </summary>
/// <typeparam name="TFunc"></typeparam>
/// <typeparam name="TArgs"></typeparam>
template<template<class...> class TFunc, class... TArgs>
struct detector<TFunc, type_collapse<TFunc<TArgs...>>, TArgs...>
    : std::true_type { };

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_DETECTOR_H) */
