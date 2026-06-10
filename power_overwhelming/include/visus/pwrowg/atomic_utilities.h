// <copyright file="atomic_utilities.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_ATOMIC_UTILITIES_H)
#define _PWROWG_ATOMIC_UTILITIES_H
#pragma once

#include <atomic>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <new>
#include <thread>
#include <type_traits>

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
/// The size, in bytes, of a cache line on processors we use. 64 is our best
/// guess for that, because we are targetting x86 and x64.
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
extern POWER_OVERWHELMING_API _Ret_valid_ void *allocate_for_atomic(
    _In_ const std::size_t size);


/// <summary>
/// Atomically sets all of the bits of <paramref name="add" /> and unsets all
/// of the bits of in <paramref name="remove" /> in <paramref name="state" />
/// by performing a CAS loop.
/// </summary>
/// <typeparam name="TEnum">An enumeration type that is used as a bitmask.
/// </typeparam>
/// <param name="state"></param>
/// <param name="add"></param>
/// <param name="remove"></param>
/// <returns>The state immediately preceding the modification.</returns>
template<class TEnum>
std::enable_if_t<std::is_enum_v<TEnum>, TEnum> atomic_change(
    _In_ std::atomic<TEnum>& state,
    _In_ const TEnum add,
    _In_ const TEnum remove) noexcept;


/// <summary>
/// Atomically sets all of <paramref name="flags" /> in
/// <paramref name="state" /> by performing a CAS loop.
/// </summary>
/// <typeparam name="TEnum">An enumeration type that is used as a bitmask.
/// </typeparam>
/// <param name="state"></param>
/// <param name="flags"></param>
/// <returns>The state immediately preceding the modification.</returns>
template<class TEnum>
std::enable_if_t<std::is_enum_v<TEnum>, TEnum> atomic_set(
    _In_ std::atomic<TEnum>& state, _In_ const TEnum flags) noexcept;


/// <summary>
/// Atomically unsets all of <paramref name="flags" /> in
/// <paramref name="state" /> by performing a CAS loop.
/// </summary>
/// <typeparam name="TEnum">An enumeration type that is used as a bitmask.
/// </typeparam>
/// <param name="state"></param>
/// <param name="flags"></param>
/// <returns>The state immediately preceding the modification.</returns>
template<class TEnum>
std::enable_if_t<std::is_enum_v<TEnum>, TEnum> atomic_unset(
    _In_ std::atomic<TEnum>& state, _In_ const TEnum flags) noexcept;


/// <summary>
/// Frees a block of memory previously allocated by
/// <see cref="allocate_for_atomic" />.
/// </summary>
/// <param name="ptr">The pointer to be freed. It is safe to pass
/// <c>nullptr</c>.</param>
extern POWER_OVERWHELMING_API void free_for_atomic(_In_opt_ void *ptr) noexcept;


/// <summary>
/// Checks whether <i>all</i> bits of <paramref name="reference" /> are set in
/// <paramref name="state" />.
/// </summary>
/// <typeparam name="TEnum">An enumeration type that is used as a bitmask.
/// </typeparam>
/// <param name="state">The state variable check.</param>
/// <param name="reference">The reference bitmask to check against.</param>
/// <returns><see cref="true" /> if all bits of <paramref name="reference" />
/// are set in <paramref name="state" />, <see langword="false" /> otherwise.
/// </returns>
template<class TEnum>
inline std::enable_if_t<std::is_enum_v<TEnum>, bool> check_all(
        _In_ const std::atomic<TEnum>& state,
        _In_ const TEnum reference) noexcept {
    typedef std::underlying_type_t<TEnum> t;
    const auto r = static_cast<t>(reference);
    return ((static_cast<t>(state.load(std::memory_order_acquire)) & r) == r);
}


/// <summary>
/// Checks whether <i>any</i> bits of <paramref name="reference" /> are set in
/// <paramref name="state" />.
/// </summary>
/// <typeparam name="TEnum">An enumeration type that is used as a bitmask.
/// </typeparam>
/// <param name="state">The state variable check.</param>
/// <param name="reference">The reference bitmask to check against.</param>
/// <returns><see cref="true" /> if any of the bits of
/// <paramref name="reference" /> is set in <paramref name="state" />,
/// <see langword="false" /> otherwise.</returns>
template<class TEnum>
inline std::enable_if_t<std::is_enum_v<TEnum>, bool> check_any(
        _In_ const std::atomic<TEnum>& state,
        _In_ const TEnum reference) noexcept {
    typedef std::underlying_type_t<TEnum> t;
    const auto r = static_cast<t>(reference);
    return ((static_cast<t>(state.load(std::memory_order_acquire)) & r) != 0);
}


/// <summary>
/// Checks whether all bits of <paramref name="reference" /> are set in
/// <paramref name="state" />, or spins until this is the case.
/// </summary>
/// <remarks>
/// This function will yield when not in the expected state.
/// </remarks>
/// <typeparam name="TEnum">An enumeration type that is used as a bitmask.
/// </typeparam>
/// <param name="state">The state variable to spin on.</param>
/// <param name="reference">The reference bitmask to check against.</param>
template<class TEnum> std::enable_if_t<std::is_enum_v<TEnum>> spin_until_all(
    _In_ const std::atomic<TEnum>& state,
    _In_ const TEnum reference) noexcept;


/// <summary>
/// Checks whether all bits of <paramref name="reference" /> are set in
/// <paramref name="state" />, or spins until this is the case or the given
/// <paramref name="timeout" /> has elapsed.
/// </summary>
/// <typeparam name="TEnum">An enumeration type that is used as a bitmask.
/// </typeparam>
/// <typeparam Thename="TRep">The value type of the duration.</typeparam>
/// <typeparam name="TPeriod">The period of the duration.</typeparam>
/// <param name="state">The state variable to spin on.</param>
/// <param name="reference">The reference bitmask to check against.</param>
/// <param name="timeout">The maximum duration to spin.</param>
/// <returns><see langword="true" /> if the expected state was reached,
/// <see langword="false" /> if the operation timed out.</returns>
template<class TEnum, class TRep, class TPeriod>
std::enable_if_t<std::is_enum_v<TEnum>, bool> spin_until_all(
    _In_ const std::atomic<TEnum>& state,
    _In_ const TEnum reference,
    _In_ const std::chrono::duration<TRep, TPeriod> timeout) noexcept;


/// <summary>
/// Checks whether any of the bits of <paramref name="reference" /> is set in
/// <paramref name="state" /> and spins until this is the case.
/// </summary>
/// <remarks>
/// This function will yield when not in the expected state.
/// </remarks>
/// <typeparam name="TEnum">An enumeration type that is used as a bitmask.
/// </typeparam>
/// <param name="state">The state variable to spin on.</param>
/// <param name="reference">The reference bitmask to check against.</param>
template<class TEnum> std::enable_if_t<std::is_enum_v<TEnum>> spin_until_any(
    _In_ const std::atomic<TEnum>& state,
    _In_ const TEnum reference) noexcept;


/// <summary>
/// Checks whether any of the bits of <paramref name="reference" /> is set in
/// <paramref name="state" />, or spins until this is the case or the given
/// <paramref name="timeout" /> has elapsed.
/// </summary>
/// <typeparam name="TEnum">An enumeration type that is used as a bitmask.
/// </typeparam>
/// <typeparam Thename="TRep">The value type of the duration.</typeparam>
/// <typeparam name="TPeriod">The period of the duration.</typeparam>
/// <param name="state">The state variable to spin on.</param>
/// <param name="reference">The reference bitmask to check against.</param>
/// <param name="timeout">The maximum duration to spin.</param>
/// <returns><see langword="true" /> if the expected state was reached,
/// <see langword="false" /> if the operation timed out.</returns>
template<class TEnum, class TRep, class TPeriod>
std::enable_if_t<std::is_enum_v<TEnum>, bool> spin_until_any(
    _In_ const std::atomic<TEnum>& state,
    _In_ const TEnum reference,
    _In_ const std::chrono::duration<TRep, TPeriod> timeout) noexcept;


/// <summary>
/// Checks whether all bits of <paramref name="reference" /> are set in
/// <paramref name="state" /> and spins while this is the case.
/// </summary>
/// <remarks>
/// This function will yield when not in the expected state.
/// </remarks>
/// <typeparam name="TEnum">An enumeration type that is used as a bitmask.
/// </typeparam>
/// <param name="state">The state variable to spin on.</param>
/// <param name="reference">The reference bitmask to check against.</param>
template<class TEnum> std::enable_if_t<std::is_enum_v<TEnum>> spin_while_all(
    _In_ const std::atomic<TEnum>& state,
    _In_ const TEnum reference) noexcept;


/// <summary>
/// Checks whether all bits of <paramref name="reference" /> are set in
/// <paramref name="state" />, or spins while this is the case or the given
/// <paramref name="timeout" /> has elapsed.
/// </summary>
/// <typeparam name="TEnum">An enumeration type that is used as a bitmask.
/// </typeparam>
/// <typeparam Thename="TRep">The value type of the duration.</typeparam>
/// <typeparam name="TPeriod">The period of the duration.</typeparam>
/// <param name="state">The state variable to spin on.</param>
/// <param name="reference">The reference bitmask to check against.</param>
/// <param name="timeout">The maximum duration to spin.</param>
/// <returns><see langword="true" /> if the expected state was reached,
/// <see langword="false" /> if the operation timed out.</returns>
template<class TEnum, class TRep, class TPeriod>
std::enable_if_t<std::is_enum_v<TEnum>, bool> spin_while_all(
    _In_ const std::atomic<TEnum>& state,
    _In_ const TEnum reference,
    _In_ const std::chrono::duration<TRep, TPeriod> timeout) noexcept;


/// <summary>
/// Checks whether any of bits of <paramref name="reference" /> is set in
/// <paramref name="state" /> and spins while this is the case.
/// </summary>
/// <remarks>
/// This function will yield when not in the expected state.
/// </remarks>
/// <typeparam name="TEnum">An enumeration type that is used as a bitmask.
/// </typeparam>
/// <param name="state">The state variable to spin on.</param>
/// <param name="reference">The reference bitmask to check against.</param>
template<class TEnum> std::enable_if_t<std::is_enum_v<TEnum>> spin_while_any(
    _In_ const std::atomic<TEnum>& state,
    _In_ const TEnum reference) noexcept;


/// <summary>
/// Checks whether any of the bits of <paramref name="reference" /> is set in
/// <paramref name="state" />, or spins while this is the case or the given
/// <paramref name="timeout" /> has elapsed.
/// </summary>
/// <typeparam name="TEnum">An enumeration type that is used as a bitmask.
/// </typeparam>
/// <typeparam Thename="TRep">The value type of the duration.</typeparam>
/// <typeparam name="TPeriod">The period of the duration.</typeparam>
/// <param name="state">The state variable to spin on.</param>
/// <param name="reference">The reference bitmask to check against.</param>
/// <param name="timeout">The maximum duration to spin.</param>
/// <returns><see langword="true" /> if the expected state was reached,
/// <see langword="false" /> if the operation timed out.</returns>
template<class TEnum, class TRep, class TPeriod>
std::enable_if_t<std::is_enum_v<TEnum>, bool> spin_while_any(
    _In_ const std::atomic<TEnum>& state,
    _In_ const TEnum reference,
    _In_ const std::chrono::duration<TRep, TPeriod> timeout) noexcept;

PWROWG_DETAIL_NAMESPACE_END

#include "visus/pwrowg/atomic_utilities.inl"

#endif /* !defined(_PWROWG_ATOMIC_UTILITIES_H) */
