// <copyright file="guid.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

/*
 * include\the\guid.h
 *
 * Copyright (C) 2013 TheLib Team (http://www.thelib.org/license)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of TheLib, TheLib Team, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THELIB TEAM AS IS AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THELIB TEAM BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * GUID.h
 *
 * Copyright (C) 2006 - 2008 by Universitaet Stuttgart (VIS). 
 * Alle Rechte vorbehalten.
 */

#if !defined(_PWROWG_GUID_H)
#define _PWROWG_GUID_H
#pragma once

#include <cinttypes>
#include <cstdlib>
#include <string>
#include <vector>

#if defined(_WIN32)
#include <guiddef.h>
#elif defined(_WIN32)
#include <uuid/uuid.h>
#endif /* defined(_WIN32) */

#if defined(_MSC_VER)
#pragma comment(lib, "rpcrt4")
#endif /* defined(_MSC_VER) */

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A globally unique identifier (GUID).
/// </summary>
class POWER_OVERWHELMING_API guid final {

public:

    /// <summary>
    /// The native type of a GUID value.
    /// </summary>
#if defined(_WIN32)
    typedef ::GUID value_type;
#elif defined(_WIN32)
    typedef ::uuid_t value_type;
#endif /* defined(_WIN32) */

    /// <summary>
    /// Make a new GUID.
    /// </summary>
    /// <param name="retval">Receives the newly created GUID.</param>
    /// <param name="no_mac">If this flag is set, an algorithm will be used that
    /// does not include the MAC address in the GUID.This is the default.
    /// </param>
    /// <returns><paramref name="retval" />.</returns>
    /// <exception cref="std::system_error">If the operation failed, e.g. because
    /// the machine has no network adapter.</exception>
    static guid& create(_Out_ guid& retval, _In_ const bool no_mac = true);

    /// <summary>
    /// Make a new GUID.
    /// </summary>
    /// <param name="no_mac">If this flag is set, an algorithm will be used that
    /// does not include the MAC address in the GUID.This is the default.
    /// </param>
    /// <returns>A new GUID value.</returns>
    /// <exception cref="std::system_error">If the operation failed, e.g. because
    /// the machine has no network adapter.</exception>
    static inline guid create(_In_ const bool no_mac = true) {
        guid retval;
        return guid::create(retval, no_mac);
    }

    /// <summary>
    /// Parse the GUID from a string representation.
    /// </summary>
    /// <param name="retval">Recevies the parsed GUID.</param>
    /// <param name="str">The string to parse the GUID from.</param>
    /// <returns><paramref name="retval" />.</returns>
    /// <exception cref="std::argument_exception">If <paramref name="str" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="std::system_error">If <paramref name="str" /> does
    /// not represent a valid GUID.</exception>
    static guid& parse(_Out_ guid& retval, _In_z_ const char *str);

    /// <summary>
    /// Parse the GUID from a string representation.
    /// </summary>
    /// <param name="retval">Recevies the parsed GUID.</param>
    /// <param name="str">The string to parse the GUID from.</param>
    /// <returns><paramref name="retval" />.</returns>
    /// <exception cref="std::argument_exception">If <paramref name="str" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="std::system_error">If <paramref name="str" /> does
    /// not represent a valid GUID.</exception>
    static guid& parse(_Out_ guid& retval, _In_z_ const wchar_t *str);

    /// <summary>
    /// Parse the GUID from a string representation.
    /// </summary>
    /// <param name="str">The string to parse the GUID from.</param>
    /// <returns>The parsed GUID.</returns>
    /// <exception cref="std::argument_exception">If <paramref name="str" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="std::system_error">If <paramref name="str" /> does
    /// not represent a valid GUID.</exception>
    static inline guid parse(_In_z_ const char *str) {
        guid retval;
        return guid::parse(retval, str);
    }

    /// <summary>
    /// Parse the GUID from a string representation.
    /// </summary>
    /// <param name="str">The string to parse the GUID from.</param>
    /// <returns>The parsed GUID.</returns>
    /// <exception cref="std::argument_exception">If <paramref name="str" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="std::system_error">If <paramref name="str" /> does
    /// not represent a valid GUID.</exception>
    static inline guid parse(_In_z_ const wchar_t *str) {
        guid retval;
        return guid::parse(retval, str);
    }

    /// <summary>
    /// Parse the GUID from a string representation.
    /// </summary>
    /// <typeparam name="TChar">The type used to represent a character.
    /// </typeparam>
    /// <typeparam name="TTraits">The character traits for
    /// <see cref="TChar" />.</typeparam>
    /// <typeparam name="TAlloc">The allocator of the string.</typeparam>
    /// <param name="str">The string to parse the GUID from.</param>
    /// <returns>The parsed GUID.</returns>
    /// <exception cref="std::system_error">If <paramref name="str" /> does
    /// not represent a valid GUID.</exception>
    template<class TChar, class TTraits, class TAlloc> static inline guid parse(
            _In_ const std::basic_string<TChar, TTraits, TAlloc>& str) {
        guid retval;
        return guid::parse(retval, str.c_str());
    }

    /// <summary>
    /// A constant of a GUID that is zero-initialised.
    /// </summary>
    static const guid zero;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <remarks>
    /// This constructor creates an all-zero GUID.
    /// </remarks>
    guid(void) noexcept;

    /// <summary>
    /// Clone <pamamref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The object ot be cloned.</param>
    inline guid(_In_ const guid& rhs) noexcept {
        *this = rhs;
    }

    /// <summary>
    /// Initialise from a native <see cref="value_type" />.
    /// </summary>
    /// <remarks>
    /// This constructor allows for implicit conversion from
    /// <see cref="value_type" />.
    /// </remarks>
    /// <param name="rhs">The native GUID value.</param>
    inline guid(_In_ const value_type& rhs) noexcept {
        *this = rhs;
    }

    /// <summary>
    /// Initialise from an array of 16 bytes.
    /// </summary>
    /// <param name="rhs">An array of 16 bytes.</param>
    /// <exception cref="std::argument_exception">If <paramref name="rhs" />
    /// is <c>nullptr</c>.</exception>
    guid(_In_reads_(16) const std::uint8_t rhs[16]);

    /// <summary>
    /// Initialise a new instance from 16 individual bytes.
    /// </summary>
    /// <param name="b1">Byte #1.</param>
    /// <param name="b2">Byte #2.</param>
    /// <param name="b3">Byte #3.</param>
    /// <param name="b4">Byte #4.</param>
    /// <param name="b5">Byte #5.</param>
    /// <param name="b6">Byte #6.</param>
    /// <param name="b7">Byte #7.</param>
    /// <param name="b8">Byte #8.</param>
    /// <param name="b9">Byte #9.</param>
    /// <param name="b10">Byte #10.</param>
    /// <param name="b11">Byte #11.</param>
    /// <param name="b12">Byte #12.</param>
    /// <param name="b13">Byte #13.</param>
    /// <param name="b14">Byte #14.</param>
    /// <param name="b15">Byte #15.</param>
    /// <param name="b16">Byte #16.</param>
    guid(_In_ const std::uint8_t b1, _In_ const std::uint8_t b2,
        _In_ const std::uint8_t b3, _In_ const std::uint8_t b4,
        _In_ const std::uint8_t b5, _In_ const std::uint8_t b6,
        _In_ const std::uint8_t b7, _In_ const std::uint8_t b8,
        _In_ const std::uint8_t b9, _In_ const std::uint8_t b10,
        _In_ const std::uint8_t b11, _In_ const std::uint8_t b12,
        _In_ const std::uint8_t b13, _In_ const std::uint8_t b14,
        _In_ const std::uint8_t b15, _In_ const std::uint8_t b16) noexcept;

    /// <summary>
    /// Initialises a new instance from an integer, two shorts and eight bytes.
    /// </summary>
    /// <param name="i">The first four bytes.</param>
    /// <param name="s1">Bytes #5 and #6.</param>
    /// <param name="s2">Bytes #7 and #8.</param>
    /// <param name="b1">Byte #9.</param>
    /// <param name="b2">Byte #10.</param>
    /// <param name="b3">Byte #11.</param>
    /// <param name="b4">Byte #12.</param>
    /// <param name="b5">Byte #13.</param>
    /// <param name="b6">Byte #14.</param>
    /// <param name="b7">Byte #15.</param>
    /// <param name="b8">Byte #16.</param>
    guid(_In_ const std::uint32_t i,
        _In_ const uint16_t s1, _In_ const uint16_t s2,
        _In_ const std::uint8_t b1, _In_ const std::uint8_t b2,
        _In_ const std::uint8_t b3, _In_ const std::uint8_t b4,
        _In_ const std::uint8_t b5, _In_ const std::uint8_t b6,
        _In_ const std::uint8_t b7, _In_ const std::uint8_t b8) noexcept;

    /// <summary>
    /// Initialises a new instance from an integer, two shorts and an array of
    /// eight bytes.
    /// </summary>
    /// <param name="i">The first four bytes.</param>
    /// <param name="s1">Bytes #5 and #6.</param>
    /// <param name="s2">Bytes #7 and #8.</param>
    /// <param name="b">Bytes #9 through #16</param>
    /// <exception cref="std::argument_exception">If <paramref name="b" />
    /// is <c>nullptr</c>.</exception>
    guid(_In_ const std::uint32_t i,
        _In_ const std::uint16_t s1, const std::uint16_t s2,
        _In_reads_(8) const std::uint8_t b[8]);

    /// <summary>
    /// Set all bytes to zero.
    /// </summary>
    void clear(void) noexcept;

    /// <summary>
    /// Answer whether the GUID is all-zero.
    /// </summary>
    /// <returns><c>true</c> if the GUID is all-zero, <c>false</c> if at least
    /// one byte is non-zero.</returns>
    bool empty(void) const noexcept;

    /// <summary>
    /// Create a string representation of the GUID.
    /// </summary>
    /// <param name="dst">Receives the string representation. If this parameter
    /// is <c>nullptr</c>, only the required buffer size is measured.</param>
    /// <param name="cnt">The size of <paramref name="dst" /> in number of
    /// characters.</param>
    /// <returns>The required buffer size in number of characters.</returns>
    std::size_t to_string(_Out_writes_opt_z_(cnt) char *dst,
        _In_ const std::size_t cnt) const;

    /// <summary>
    /// Create a string representation of the GUID.
    /// </summary>
    /// <param name="dst">Receives the string representation. If this parameter
    /// is <c>nullptr</c>, only the required buffer size is measured.</param>
    /// <param name="cnt">The size of <paramref name="dst" /> in number of
    /// characters.</param>
    /// <returns>The required buffer size in number of characters.</returns>
    std::size_t to_string(_Out_writes_opt_z_(cnt) wchar_t *dst,
        _In_ const std::size_t cnt) const;

    /// <summary>
    /// Creates a string representation of the GUID.
    /// </summary>
    /// <typeparam name="TChar">The type of a character.</typeparam>
    /// <returns>The string representation of the GUID.</returns>
    template<class TChar>
    inline std::basic_string<TChar> to_string(void) const {
        auto dst = static_cast<TChar *>(nullptr);
        std::vector<TChar> retval(this->to_string(dst, 0));
        this->to_string(retval.data(), retval.size());
        return retval.data();
    }

    /// <summary>
    /// Assignment.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    guid& operator =(_In_ const guid& rhs) noexcept;

    /// <summary>
    /// Assignment from a native GUID.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    guid& operator =(_In_ const value_type& rhs) noexcept;

    /// <summary>
    /// Assignment from a native GUID.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::argument_exception">If <paramref name="rhs" /> is
    /// <c>nullptr</c>.</<exception>
    guid& operator =(_In_ const value_type *rhs);

    /// <summary>
    /// Test for equality.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>true</c> if this GUID and <paramref name="rhs" /> are equal,
    /// <c>false</c> otherwise.</returns>
    bool operator ==(_In_ const guid& rhs) const noexcept;

    /// <summary>
    /// Test for inequality.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>true</c> if this GUID and <paramref name="rhs" /> are
    /// not equal, <c>false</c> otherwise.</returns>
    inline bool operator !=(_In_ const guid& rhs) const noexcept {
        return !(*this == rhs);
    }

    /// <summary>
    /// Answer whether this GUID should be sorted before <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>true</c> if this object is before <paramref name="rhs" />,
    /// <c>false</c> otherwise.</returns>
    bool operator <(_In_ const guid& rhs) const noexcept;

    /// <summary>
    /// Answer whether this GUID should be sorted after <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>true</c> if this object is after <paramref name="rhs" />,
    /// <c>false</c> otherwise.</returns>
    inline bool operator >(_In_ const guid& rhs) const noexcept {
        return (rhs < *this);
    }

    /// <summary>
    /// Answer whether this GUID is less than or equal to
    /// <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>true</c> if this object is less than or equal to
    /// <paramref name="rhs" />, <c>false</c> otherwise.</returns>
    bool operator <= (_In_ const guid& rhs) const noexcept;

    /// <summary>
    /// Answer whether this GUID is greater than or equal to
    /// <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>true</c> if this object is greater than or equal to
    /// <paramref name="rhs" />, <c>false</c> otherwise.</returns>
    inline bool operator >= (_In_ const guid& rhs) const noexcept {
        return (rhs <= *this);
    }

    /// <summary>
    /// Provide access to the native GUID.
    /// </summary>
     /// <remarks>
    /// This operator allows for implicit conversion to the native GUID type.
    /// </remarks>
    /// <returns>The native GUID representation.</returns>
    inline operator value_type&(void) noexcept {
        return this->_value;
    }

    /// <summary>
    /// Provide access to the native GUID.
    /// </summary>
    /// <remarks>
    /// This operator allows for implicit conversion to the native GUID type.
    /// </remarks>
    /// <returns>The native GUID representation.</returns>
    inline operator const value_type&(void) const noexcept {
        return this->_value;
    }

    /// <summary>
    /// Provide access to the native GUID.
    /// </summary>
     /// <remarks>
    /// This operator allows for implicit conversion to the native GUID type.
    /// </remarks>
    /// <returns>A pointer to the ative GUID representation.</returns>
    inline operator value_type *(void) noexcept {
        return &this->_value;
    }

    /// <summary>
    /// Provide access to the native GUID.
    /// </summary>
    /// <remarks>
    /// This operator allows for implicit conversion to the native GUID type.
    /// </remarks>
    /// <returns>A pointer to the ative GUID representation.</returns>
    inline operator const value_type *(void) const noexcept {
        return &this->_value;
    }

private:

    value_type _value;
};

PWROWG_NAMESPACE_END


/// <summary>
/// Hash specialisation for GUIDs.
/// </summary>
template<> struct POWER_OVERWHELMING_API std::hash<PWROWG_NAMESPACE::guid> {

    /// <summary>
    /// Computes a hash value for <paramref name="guid" />.
    /// </summary>
    /// <param name="guid">The GUID to compute the hash for.</param>
    /// <returns>The hash for <paramref name="guid" />.</returns>
    inline std::size_t operator ()(
            _In_ const PWROWG_NAMESPACE::guid& guid) const noexcept {
        typedef PWROWG_NAMESPACE::guid::value_type value_type;
        auto g = static_cast<const value_type *>(guid);
        auto h = reinterpret_cast<const std::uint8_t *>(g);

        // DJB2 hash function.
        std::size_t retval = 0;
        for (std::size_t i = 0; i < sizeof(value_type); ++i) {
            retval = ((retval << 5) + retval) + static_cast<std::size_t>(h[i]);
        }

        return retval;
    }
};

#endif /* !defined(_PWROWG_GUID_H) */
