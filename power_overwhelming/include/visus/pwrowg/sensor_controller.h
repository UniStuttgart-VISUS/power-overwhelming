// <copyright file="sensor_controller.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_CONTROLLER_H)
#define _PWROWG_SENSOR_CONTROLLER_H
#pragma once

#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <stdexcept>
#include <type_traits>

#include "visus/pwrowg/type_erased_storage.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Detects whether a type contains a controller type.
/// </summary>
/// <typeparam name="TType">A sensor configuration type.</typeparam>
template<class TType, class = void>
struct sensor_controller final : std::false_type {
    typedef std::nullptr_t type;

    template<class... TArgs>
    static inline void emplace(type_erased_storage&, TArgs...) { }
};


/// <summary>
/// Specialisation for types that contain a controller type.
/// </summary>
/// <typeparam name="TType">A sensor configuration type.</typeparam>
template<class TType> struct sensor_controller<TType,
        std::void_t<typename TType::controller_type>> final : std::true_type {
    typedef typename TType::controller_type _type;
    typedef _type *type;

    template<class... TArgs> static inline void emplace(
            _In_ type_erased_storage& dst,
            _In_ TArgs... args) {
        dst.emplace<_type>(std::forward<TArgs>(args)...);
    }
};


/// <summary>
/// Derives the type of the controller from the configuration
/// <typeparamref name="TType" />.
/// </summary>
/// <typeparam name="TType"></typeparam>
template<class TType>
using sensor_controller_t = typename sensor_controller<TType>::type;


/// <summary>
/// Indicates whether the configuration <typeparamref name="TType" /> declare a
/// controller type.
/// </summary>
/// <typeparam name="TType"></typeparam>
template<class TType>
constexpr bool sensor_controller_v = sensor_controller<TType>::value;

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_CONTROLLER_H) */
