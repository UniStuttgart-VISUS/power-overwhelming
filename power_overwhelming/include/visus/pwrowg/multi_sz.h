// <copyright file="multi_sz.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

/*
 * include\the\multi_sz.h
 *
 * Copyright (TChar) 2013 TheLib Team (http://www.thelib.org/license)
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
 * multi_sz.h
 *
 * Copyright (TChar) 2006 - 2007 by Universitaet Stuttgart (VIS). 
 * Alle Rechte vorbehalten.
 */

#if !defined(_PWROWG_MULTI_SZ_H)
#define _PWROWG_MULTI_SZ_H
#pragma once

#include <algorithm>
#include <cassert>
#include <cstdarg>
#include <cstring>
#include <iterator>
#include <vector>

#include "visus/pwrowg/blob.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Represents a set of zero-terminated strings terminated by an additional zero,
/// which is commonly used in the Windows registry to store arrays of strings.
/// </summary>
/// <typeparam name="TChar">The type of the characters (<c>char</c> or
/// <c>wchar_t</c>).</typeparam>
/// <typeparam name="TTrais">The type of the character traits, which defaults to
/// the STL implementation for strings.</typeparam>
template<class TChar, class TTraits = std::char_traits<TChar>>
class multi_sz final {

public:

    /// <summary>
    /// An iterator over the strings in a <see cref="multi_sz" />.
    /// </summary>
    class iterator : public std::iterator<std::forward_iterator_tag,
            const TChar *,
            std::ptrdiff_t,
            const TChar *,
            const TChar *> {

    public:

        /// <summary>
        /// Clone <paramref name="rhs" />.
        /// </summary>
        /// <param name="rhs">The object to be cloned.</param>
        inline iterator(_In_ const iterator& rhs) {
            *this = rhs;
        }

        /// <summary>
        /// Assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        iterator& operator =(_In_ const iterator& rhs);

        /// <summary>
        /// Test for equality.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>true</c> if this iterator and <paramref name="rhs" />
        /// are equal, <c>false</c> otherwise.</returns>
        inline bool operator ==(_In_ const iterator& rhs) noexcept {
            return (this->_current == rhs._current);
        }

        /// <summary>
        /// Test for inequality.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>true</c> if this iterator and <paramref name="rhs" />
        /// are not equal, <c>false</c> otherwise.</returns>
        inline bool operator !=(_In_ const iterator& rhs) noexcept {
            return (this->_current != rhs._current);
        }

        /// <summary>
        /// Dereference the iterator.
        /// </summary>
        /// <returns>The current string.</returns>
        reference operator *(void) const;

        /// <summary>
        /// Provide access to the contained string.
        /// </summary>
        /// <returns>The current string.</returns>
        pointer operator ->(void) const;

        /// <summary>
        /// Prefix increment.
        /// </summary>
        /// <returns><c>*this</c>.</returns>
        iterator& operator ++(void);

        /// <summary>
        /// Postfix increment.
        /// </summary>
        /// <returns>The previous iterator position.</returns>
        inline iterator operator ++(int) {
            iterator retval(*this);
            ++(*this);
            return retval;
        }

    private:

        inline iterator(_In_opt_z_ value_type current) : _current(current) { }

        value_type _current;

        friend class multi_sz;
    };

    /// <summary>
    /// The type used to measure the size of the multi-sz.
    /// </summary>
    typedef std::size_t size_type;

    /// <summary>
    /// The type of the character traits.
    /// </summary>
    typedef TTraits traits_type;

    /// <summary>
    /// The type used for a character.
    /// </summary>
    typedef TChar value_type;

    /// <summary>
    /// Allocate a new multi-sz concatenating <paramref name="rhs" /> at the end
    /// of the <paramref name="lhs" />.
    /// </summary>
    /// <remarks>
    /// This method returns memory that the caller must deallocate. Avoid using
    /// it whenever possible.
    /// </remarks>
    /// <param name="lhs">The multi-sz to append to. It is safe to pass
    /// <c>nullptr</c>. A copy of <paramref name="rhs" /> as multi-sz, i.e.
    /// with two zeros at the end, will be returned in this case, provided it is
    /// non-<c>nullptr</c>. The caller remains owner of the memory.</param>
    /// <param name="rhs">The string to be appended. This must not be a multi-sz!
    /// If it is, only the first element will be appended. It is safe to pass
    /// <c>nullptr</c>. A copy of <paramref name="lhs" /> will be returned in
    /// this case, provided it is non-<c>nullptr</c>. The caller remains owner
    /// of the memory.</param>
    /// <returns>A new multi-sz holding all concatenated values. This buffer must
    /// be deallocated using <c>delete[]</c>.</returns>
    static _Ret_maybenull_z_ value_type *add(
        _In_opt_z_ const value_type *lhs,
        _In_opt_z_ const value_type *rhs);

    /// <summary>
    /// Answer a pointer to the <paramref name="idx" />th string in the given
    /// multi-sz.
    /// </summary>
    /// <remarks>
    /// Note that is is indispensable that <paramref name="multi_sz" /> is
    /// terminated using <i>two</c> zeros. It is safe to pass <c>nullptr</c>.
    /// </remarks>
    /// <param name="multi_sz">A set of zero-terminated strings, terminated with
    /// <i>two</c> zeros at the end of the set. The caller remains owner of the
    /// memory.</param>
    /// <param name="idx">The zero-based index of the string to retrieve.
    /// </param>
    /// <returns>A pointer to the <paramref name="idx" />th string or
    /// <c>nullptr</c> if that string does not exist.</returns>
    static _Ret_maybenull_z_ const value_type *at(
        _In_opt_z_ const value_type *multi_sz,
        _In_ const size_type idx) noexcept;

    /// <summary>
    ///  Answer the number of entries in the set of zero-terminated strings
    /// <paramref name="multi_sz" />.
    /// </summary>
    /// <remarks>
    /// Note that is is indispensable that <paramref name="multi_sz" /> is
    /// terminated using <i>two</c> zeros. It is safe to pass <c>nullptr</c>.
    /// </remarks>
    /// <param name="multi_sz">A set of zero-terminated strings, terminated with
    /// <i>two</c> zeros at the end of the set. The caller remains owner of the
    /// memory.</param>
    /// <returns>The number of strings in the set.</returns>
    static size_type count(_In_opt_z_ const value_type *multi_sz) noexcept;

    /// <summary>
    /// Answer the length of the set of zero-terminated strings
    /// <paramref name="multi_sz" /> in number of characters.
    /// </summary>
    /// <remarks>
    /// Note that is is indispensable that <paramref name="multi_sz" /> is
    /// terminated using <i>two</c> zeros. It is safe to pass <c>nullptr</c>.
    /// </remarks>
    /// <param name="multi_sz">A set of zero-terminated strings, terminated with
    /// <i>two</c> zeros at the end of the set. The caller remains owner of the
    /// memory.</param>
    /// <returns>The number of characters that are required to store the
    /// <paramref name="multi_sz" />.</returns>
    static inline size_type length(
            _In_opt_z_ const value_type *multi_sz) noexcept {
        return size(multi_sz);
    }

    /// <summary>
    /// Answer the length of the set of zero-terminated strings
    /// <paramref name="multi_sz" /> in number of characters.
    /// </summary>
    /// <remarks>
    /// Note that is is indispensable that <paramref name="multi_sz" /> is
    /// terminated using <i>two</c> zeros. It is safe to pass <c>nullptr</c>.
    /// </remarks>
    /// <param name="multi_sz">A set of zero-terminated strings, terminated with
    /// <i>two</c> zeros at the end of the set. The caller remains owner of the
    /// memory.</param>
    /// <returns>The number of characters that are required to store the
    /// <paramref name="multi_sz" />.</returns>
    static size_type size(_In_opt_z_ const value_type *multi_sz) noexcept;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="value">A set of zero-terminated strings, terminated with
    /// <i>two</c> zeros at the end of the set. The caller remains owner of the
    /// memory.</param>
    explicit multi_sz(_In_opt_z_ const value_type *value = nullptr);

    /// <summary>
    /// Initialise a new instance.
    /// </summary>
    /// <param name="value">A <see cref="blob" /> that contains a set of
    /// zero-terminated strings, terminated by <i>two</c> zeros at the end of
    /// the data.</param>
    explicit multi_sz(_In_ const blob& value);

    /// <summary>
    /// Clone <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The object to be clones.</param>
    inline multi_sz(_In_ const multi_sz& rhs) : _value(nullptr) {
        *this = rhs;
    }

    /// <summary>
    /// Move <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    inline multi_sz(_Inout_ multi_sz&& rhs) noexcept : _value(rhs._value) {
        rhs._value = nullptr;
    }

    /// <summary>
    /// Initialises a new instance from an array of strings.
    /// </summary>
    /// <param name="strings">An array of <parmaref name="cnt" /> strings.
    /// </param>
    /// <param name="cnt"></param>
    multi_sz(_In_reads_(cnt) const value_type **strings,
        _In_ const size_type cnt);

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    inline ~multi_sz(void) noexcept {
        this->clear();
    }

    /// <summary>
    /// Append <paramref name="str" /> at the end of the multi-sz.
    /// </summary>
    /// <param name="str">The string to be appended. It is safe to pass
    /// <c>nullptr</c> (nothing will happen in this case). Nothing will happen
    /// if <paramref name="str" /> is an empty string either. The caller remains
    /// owner of the memory.</param>
    /// <returns><c>*this</c>.</returns>
    multi_sz& add(_In_opt_z_ const value_type *str);

    /// <summary>
    /// Answer the raw data of the <paramref name="idx" />th string in the
    /// multi-sz or <c>nullptr</c> if no such element exists.
    /// </summary>
    /// <param name="idx">The zero-based index of the string to retrieve.
    /// </param>
    /// <returns>A pointer to the <paramref name="idx" />th string or
    /// <c>nullptr</c> if that string does not exist.</returns>
    inline _Ret_maybenull_z_ const value_type *at(
            _In_ const size_type idx) const noexcept {
        return multi_sz::at(this->_value, idx);
    }

    /// <summary>
    /// Gets an iterator over the strings in the multi-sz.
    /// </summary>
    /// <returns>An iterator for the begin of the strings.</returns>
    inline iterator begin(void) const noexcept {
        return iterator(this->_value);
    }

    /// <summary>
    /// Clear all contents.
    /// </summary>
    inline void clear(void) noexcept {
        delete[] this->_value;
        this->_value = nullptr;
    }

    /// <summary>
    /// Answer the number of strings in the multi-sz.
    /// </summary>
    /// <returns>The number of strings stored in the object.</returns>
    inline size_type count(void) const noexcept {
        return multi_sz::count(this->_value);
    }

    /// <summary>
    /// Answer the raw data pointer.
    /// </summary>
    /// <remarks>
    /// Note, that is unsafe to operate with this pointer and that the pointer
    /// might become invalid as the multi_sz is manipulated using other methods.
    /// <returns>The raw data pointer.</returns>
    inline _Ret_maybenull_z_ const value_type *data(void) const noexcept {
        return this->_value;
    }

    /// <summary>
    /// Answer whether there is not string in the multi-sz.
    /// </summary>
    /// <returns><c>true</c> if the multi-sz holds no data,
    /// <c>false</c> otherwise.</returns>
    inline bool empty(void) const noexcept {
        return (this->_value == nullptr);
    }

    /// <summary>
    /// Gets an iterator for the end of the multi-sz.
    /// </summary>
    /// <returns>The end of the strings in the multi-sz.</returns>
    inline iterator end(void) const noexcept {
        return iterator(nullptr);
    }

    /// <summary>
    /// Insert <paramref name="str" /> at the <paramref name="idx" />th
    /// position.
    /// </summary>
    /// <remarks>
    /// All elements behind <paramref name="idx" /> are shifted one element
    /// right. <paramref name="idx" /> must be a valid index in the multi-sz.
    /// Otherwise, the method behaves like <see cref="add" />.
    /// <param name="idx">The zero-based position where to insert the new
    /// string.</param>
    /// <param name="str">The string to be appended. It is safe to pass
    /// <c>nullptr</c> (nothing will happen in this case). Nothing will happen
    /// if <paramref name="str" /> is an empty string either. The caller remains
    /// owner of the memory.</param>
    /// <returns><c>*this</c>.</returns>
    multi_sz& insert(_In_ const size_type idx,
        _In_opt_z_ const value_type *str);

    /// <summary>
    /// Answer the size of the multi-sz including all terminating zeros.
    /// </summary>
    /// <returns>The number of characters in the multi-sz.</returns>
    inline size_type length(void) const noexcept {
        return multi_sz::size(this->_value);
    }

    /// <summary>
    /// Append <paramref name="str" /> at the end of the multi-sz.
    /// </summary>
    /// <param name="str">The string to be appended. It is safe to pass
    /// <c>nullptr</c> (nothing will happen in this case). Nothing will happen
    /// if <paramref name="str" /> is an empty string either. The caller remains
    /// owner of the memory.</param>
    /// <returns><c>*this</c>.</returns>
    inline multi_sz& push_back(_In_opt_z_ const value_type *str) {
        return this->add(str);
    }

    /// <summary>
    /// Remove all occurrences of <paramref name="str" /> in the set.
    /// </summary>
    /// <param name="str">The string to be removed. It is safe to pass
    /// <c>nullptr</c>. The caller remains owner of the memory.</param>
    /// <returns><c>*this</c>.</returns>
    multi_sz& remove(_In_opt_z_ const value_type *str);

    /// <summary>
    /// Remove all strings that match the given <paramref name="predicate" />.
    /// </summary>
    /// <typeparam name="TPredicate">The type of the predicate, which must
    /// accept a <c>const value_type *</c> and yield a <c>bool</c>.</typeparam>
    /// <param name="predicate">The predicate selecting the strings to be
    /// removed.</param>
    /// <returns><c>*this</c>.</returns>
    template<class TPredicate>
    multi_sz& remove_if(_In_ const TPredicate predicate);

    /// <summary>
    /// Answer the size of the multi-sz including all terminating zeros.
    /// </summary>
    /// <returns>The number of characters in the multi-sz.</returns>
    inline size_type size(void) const noexcept {
        return multi_sz::size(this->_value);
    }

    /// <summary>
    /// Assignment.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    multi_sz& operator =(_In_ const multi_sz& rhs);

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    multi_sz& operator =(_Inout_ multi_sz&& rhs) noexcept;

    /// <summary>
    /// Test for equality.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>true</c> if <paramref name="rhs" /> contains the same
    /// strings in the same order as this object, <c>false</c> otherwise.
    /// </returns>
    bool operator ==(_In_ const multi_sz& rhs) const noexcept;

    /// <summary>
    /// Test for inequality.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>true</c> if <paramref name="rhs" /> does not contain the
    /// same strings in the same order as this object, <c>false</c> otherwise.
    /// </returns>
    inline bool operator !=(_In_ const multi_sz& rhs) const noexcept {
        return !(*this == rhs);
    }

    /// <summary>
    /// Append <paramref name="str" /> at the end of the multi-sz.
    /// </summary>
    /// <param name="str">The string to be appended. It is safe to pass
    /// <c>nullptr</c> (nothing will happen in this case). Nothing will happen
    /// if <paramref name="str" /> is an empty string either. The caller remains
    /// owner of the memory.</param>
    /// <returns><c>*this</c>.</returns>
    inline multi_sz& operator +=(_In_opt_z_ const value_type *rhs) {
        this->add(rhs);
        return *this;
    }

    /// <summary>
    /// Answer the raw data of the <paramref name="idx" />th string in the
    /// multi-sz or <c>nullptr</c> if no such element exists.
    /// <param name="idx">The zero-based index of the string to retrieve.
    /// </param>
    /// <returns>A pointer to the <paramref name="idx" />th string or
    /// <c>nullptr</c> if that string does not exist.</returns>
    inline _Ret_maybenull_z_ const value_type *operator [](
            _In_ const size_type idx) const noexcept {
        return multi_sz::at(this->_value, idx);
    }

private:

    value_type *_value;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/multi_sz.inl"

#endif /* !defined(_PWROWG_MULTI_SZ_H) */
