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
/// Implements the Fowler-Noll-Vo hash function.
/// </summary>
/// <typeredef="TResult">The type of the result the hash produces.</typeparam>
template<class TResult> class fnv1a;

/// <summary>
/// Implements the 32-bit variant of the Fowler-Noll-Vo hash function.
/// </summary>
template<> class PWROWG_TEST_API fnv1a<std::uint32_t> {

public:

    /// <summary>
    /// The type of result the hash produces.
    /// </summary>
    typedef std::uint32_t result_type;

    /// <summary>
    /// Initialises a new instane.
    /// </summary>
    fnv1a(void) noexcept;

    /// <summary>
    /// Appends the given range of bytes to the hash value.
    /// </summary>
    /// <typeparam name="TIterator">An iterator over bytes.</typeparam>
    /// <param name="begin">The begin of the range of bytes to be added.</param>
    /// <param name="end">The end of the range of ybtes to be added.</param>
    template<class TIterator> void operator ()(_In_ const TIterator begin,
        _In_ const TIterator end) noexcept;

    /// <summary>
    /// Answer the (current) hash value.
    /// </summary>
    /// <returns>The hash value.</returns>
    inline operator result_type() const noexcept {
        return this->_value;
    }

private:

    result_type _value;
};

/// <summary>
/// Implements the 64-bit variant of the Fowler-Noll-Vo hash function.
/// </summary>
template<> class PWROWG_TEST_API fnv1a<std::uint64_t> {

public:

    /// <summary>
    /// The type of result the hash produces.
    /// </summary>
    typedef std::uint64_t result_type;

    /// <summary>
    /// Initialises a new instane.
    /// </summary>
    fnv1a(void) noexcept;

    /// <summary>
    /// Appends the given range of bytes to the hash value.
    /// </summary>
    /// <typeparam name="TIterator">An iterator over bytes.</typeparam>
    /// <param name="begin">The begin of the range of bytes to be added.</param>
    /// <param name="end">The end of the range of ybtes to be added.</param>
    template<class TIterator> void operator ()(_In_ const TIterator begin,
        _In_ const TIterator end) noexcept;

    /// <summary>
    /// Answer the (current) hash value.
    /// </summary>
    /// <returns>The hash value.</returns>
    inline operator result_type() const noexcept {
        return this->_value;
    }

private:

    result_type _value;
};

PWROWG_DETAIL_NAMESPACE_END

#include "fnv1a.inl"

#endif /* !defined(_PWROWG_BASE_FNV1A_H) */
