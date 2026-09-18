// <copyright file="pwog_meta_data.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_PWOG_META_DATA_H)
#define _PWROWG_PWOG_META_DATA_H
#pragma once

#include <stdexcept>
#include <string>
#include <utility>

#include "visus/pwrowg/string_functions.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Provides way to pass key-value pairs of meta data to be stored in a PWOG
/// file. The caller remains owner of the strings in this structure and the API
/// of <see cref="pwog_file" /> will create a deep copy before returning.
/// </summary>
template<class TChar> class pwog_meta_data final {

public:

    /// <summary>
    /// The character type of the key and value strings.
    /// </summary>
    typedef TChar char_type;

    /// <summary>
    /// The string type compatible to <see cref="char_type" />.
    /// </summary>
    /// <typeparam name="TTraits">The character traits of the string type.
    /// </typeparam>
    /// <typeparam name="TAlloc">The allocator of the string type.</typeparam>
    template<class TTraits, class TAlloc>
    using string_type = std::basic_string<char_type, TTraits, TAlloc>;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="key">A non-empty key.</param>
    /// <param name="value">The value associated with the key.</param>
    /// <exception cref="std::invalid_argument">If <paramref name="key" />
    /// is <see langword="nullptr" /> or an empty string.</exception>
    pwog_meta_data(_In_z_ const char_type *key,
        _In_z_ const char_type *value);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <remarks>
    /// The constructor will create a shallow copy to the data in the strings.
    /// The caller must ensure that the strings are not modified or destroyed
    /// before the newly created instance is destroyed.
    /// </remarks>
    /// <typeparam name="TTraits">The character traits of the string type.
    /// </typeparam>
    /// <typeparam name="TAlloc">The allocator of the string type.</typeparam>
    /// <param name="key">A non-empty key.</param>
    /// <param name="value">The value associated with the key.</param>
    /// <exception cref="std::invalid_argument">If <paramref name="key" /> an
    /// empty string.</exception>
    template<class TTraits, class TAlloc>
    pwog_meta_data(_In_ const string_type<TTraits, TAlloc>& key,
            _In_ const string_type<TTraits, TAlloc>& value)
        : pwog_meta_data(key.c_str(), value.c_str()) { }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <remarks>
    /// The constructor will create a shallow copy to the data in the strings.
    /// The caller must ensure that the strings are not modified or destroyed
    /// before the newly created instance is destroyed.
    /// </remarks>
    /// <typeparam name="TTraits">The character traits of the string type.
    /// </typeparam>
    /// <typeparam name="TAlloc">The allocator of the string type.</typeparam>
    /// <param name="key">A non-empty key.</param>
    /// <param name="value">The value associated with the key.</param>
    /// <exception cref="std::invalid_argument">If <paramref name="key" /> an
    /// empty string.</exception>
    template<class TTraits, class TAlloc>
    pwog_meta_data(_In_z_ const char_type *key,
            _In_ const string_type<TTraits, TAlloc>& value)
        : pwog_meta_data(key, value.c_str()) { }

    pwog_meta_data(_In_ const pwog_meta_data&) = delete;

    /// <summary>
    /// Answer the key of the meta datum.
    /// </summary>
    /// <returns>The key of the meta datum.</returns>
    inline _Ret_z_ const char_type *key(void) const noexcept {
        return this->_key;
    }

    /// <summary>
    /// Answer the meta datum.
    /// </summary>
    /// <returns>The meta datum itself.</returns>
    inline _Ret_maybenull_z_ const char_type *value(void) const noexcept {
        return this->_value;
    }

    pwog_meta_data& operator =(_In_ const pwog_meta_data&) = delete;

private:

    _Field_z_ const char_type *_key;
    _Field_z_ const char_type *_value;
};


/// <summary>
/// Creates a new instance of <see cref="pwog_meta_data" /> with the given key
/// and value. Please be sure that both strings remain valid for the lifetime
/// of the returned instance.
/// </summary>
/// <typeparam name="TKey">The string type of the key.</typeparam>
/// <typeparam name="TValue">The string type of the value.</typeparam>
/// <param name="key"></param>
/// <param name="value"></param>
/// <returns></returns>
template<class TKey, class TValue>
pwog_meta_data<TKey> make_pwog_meta_data(_In_z_ const TKey *key,
        _In_ TValue&& value) {
    return pwog_meta_data<TKey>(key, std::forward<TValue>(value));
}


/// <summary>
/// Creates a new instance of <see cref="pwog_meta_data" /> with the given key
/// and value. Please be sure that both strings remain valid for the lifetime
/// of the returned instance.
/// </summary>
/// <typeparam name="TKey">The character type of the key.</typeparam>
/// <typeparam name="TValue">The string type of the value.</typeparam>
/// <param name="kv">A pair containing the key and value.</param>
/// <exception cref="std::invalid_argument">If <paramref name="key" /> an
/// empty string.</exception>
template<class TKey, class TTraits, class TAlloc, class TValue>
pwog_meta_data<std::decay_t<TKey>> make_pwog_meta_data(_In_ const std::pair<
        const std::basic_string<TKey, TTraits, TAlloc>, TValue>& key_value) {
    return pwog_meta_data<std::decay_t<TKey>>(key_value.first.c_str(),
        key_value.second);
}

PWROWG_NAMESPACE_END

#include "visus/pwrowg/pwog_meta_data.inl"

#endif /* !defined(_PWROWG_PWOG_META_DATA_H) */
