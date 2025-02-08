// <copyright file="atomic_utilities.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_ATOMIC_UTILITIES_H)
#define _PWROWG_ATOMIC_UTILITIES_H
#pragma once

#include <atomic>
#include <cstdlib>
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


/// <summary>
/// Performs an allocation aligned to the
/// <see cref="false_sharing_range" /> such that an atomic value stored
/// within does not interfere with other memory accesses.
/// </summary>
/// <param name="size">The size of the allocation in bytes.</param>
/// <returns>A pointer to the memory, which must be freed using
/// <see cref="free_for_atomic" />.</returns>
/// <exception cref="std::bad_alloc">If the allocation failed.</exception>
extern PWROWG_TEST_API _Ret_valid_ void *allocate_for_atomic(
    _In_ const std::size_t size);

/// <summary>
/// Frees a block of memory previously allocated by
/// <see cref="allocate_for_atomic" />.
/// </summary>
/// <param name="ptr">The pointer to be freed. It is safe to pass
/// <c>nullptr</c>.</param>
extern PWROWG_TEST_API void free_for_atomic(_In_opt_ void *ptr) noexcept;

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_ATOMIC_UTILITIES_H) */
