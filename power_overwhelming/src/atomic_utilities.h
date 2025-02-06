// <copyright file="atomic_utilities.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_ATOMIC_UTILITIES_H)
#define _PWROWG_ATOMIC_UTILITIES_H
#pragma once

#include <atomic>
#include <new>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

#if defined(__cpp_lib_hardware_interference_size)
/// <summary>
/// The size, in bytes, of a cache line.
/// </summary>
constexpr std::size_t false_sharing_range
    = std::hardware_destructive_interference_size;

#else /* defined(__cpp_lib_hardware_interference_size) */
/// <summary>
/// The size, in bytes, of a cache line on processors we use.
/// </summary>
constexpr std::size_t false_sharing_range = 64;
#endif /* defined(__cpp_lib_hardware_interference_size) */

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_ATOMIC_UTILITIES_H) */
