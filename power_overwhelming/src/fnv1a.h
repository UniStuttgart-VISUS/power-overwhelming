// <copyright file="fnv1a.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_BASE_FNV1A_H)
#define _PWROWG_BASE_FNV1A_H
#pragma once

#include <cinttypes>
#include <iterator>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Type traits for the Fowler-Noll-Vo hash function.
/// </summary>
/// <typeparam name="TType">The integer type to get the FNV constants for.
/// </typeparam>
template<class TType> struct fnv1a_traits;

/// <summary>
/// Specialisation for 32-bit hashes.
/// </summary>
template<> struct fnv1a_traits<std::uint32_t> {
    typedef std::uint32_t value_type;
    static constexpr value_type magic_prime = 0x01000193;
    static constexpr value_type offset_basis = 0x811c9dc5;
};

/// <summary>
/// Specialisation for 64-bit hashes.
/// </summary>
template<> struct fnv1a_traits<std::uint64_t> {
    typedef std::uint64_t value_type;
    static constexpr value_type magic_prime = 0x00000100000001b3;
    static constexpr value_type offset_basis = 0xcbf29ce484222325;
};


/// <summary>
/// Implements the Fowler-Noll-Vo hash function.
/// </summary>
/// <typeparam name="TResult">The type of the result the hash produces, which must
/// be one of <c>std::uint32_t</c> or <c>std::uint64_t</c>.</typeparam>
template<class TResult> class fnv1a {
    typedef detail::fnv1a_traits<TResult> _traits;

public:

    /// <summary>
    /// The type of result the hash produces.
    /// </summary>
    typedef typename _traits::value_type result_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline fnv1a(void) noexcept : _value(_traits::offset_basis) { }

    /// <summary>
    /// Appends the given range of bytes to the hash value.
    /// </summary>
    /// <typeparam name="TIterator">An iterator over bytes.</typeparam>
    /// <param name="begin">The begin of the range of bytes to be added.</param>
    /// <param name="end">The end of the range of bytes to be added.</param>
    template<class TIterator> void operator ()(_In_ const TIterator begin,
        _In_ const TIterator end) noexcept;

    /// <summary>
    /// Answer the (current) hash value.
    /// </summary>
    /// <returns>The hash value.</returns>
    inline operator result_type(void) const noexcept {
        return this->_value;
    }

private:

    result_type _value;
};

PWROWG_DETAIL_NAMESPACE_END

#include "fnv1a.inl"

#endif /* !defined(_PWROWG_BASE_FNV1A_H) */
