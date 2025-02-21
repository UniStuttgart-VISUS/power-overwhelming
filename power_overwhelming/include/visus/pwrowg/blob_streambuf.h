// <copyright file="blob_streambuf.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_BLOB_STREAMBUF_H)
#define _PWROWG_BLOB_STREAMBUF_H
#pragma once

#include <streambuf>

#include "visus/pwrowg/blob.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Constructs a view on a <see cref="blob" /> that can be used by STL streams.
/// </summary>
/// <typeparam name="TChar">The type of characters in the stream.</typeparam>
/// <typeparam name="TTraits">The traits for <typeparamref name="TTraits" />.
/// </typeparam>
template<class TChar, class TTraits = std::char_traits<TChar>>
class blob_streambuf final : public std::basic_streambuf<TChar, TTraits> {

public:

    /// <summary>
    /// Initialsies a new instance.
    /// </summary>
    /// <param name="blob">The blob to be used in a stream.</param>
    explicit inline blob_streambuf(blob& blob) : _blob(blob) {
        this->setg(this->begin(), this->begin(), this->end());
    }

protected:

    /// <summary>
    /// Seek to the specified offset.
    /// </summary>
    pos_type seekoff(_In_ const off_type offset,
        _In_ const std::ios_base::seekdir direction,
        _In_ const std::ios_base::openmode mode) override;

    /// <summary>
    /// Seek to the specified position.
    /// </summary>
    pos_type seekpos(_In_ const pos_type position,
        _In_ const std::ios_base::openmode mode) override;

private:

    inline TChar *begin(void) noexcept {
        return this->_blob.as<TChar>();
    }

    inline TChar *end(void) noexcept {
        // Note the -1/+1 combo is necessary, because the blob would report
        // nullptr for an out-of-range access.
        return this->_blob.empty()
            ? nullptr
            : this->_blob.as<TChar>(this->_blob.size() - 1) + 1;
    }

    inline pos_type limit(void) noexcept {
        return this->_blob.size();
    }

    blob& _blob;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/blob_streambuf.inl"

#endif /* !defined(_PWROWG_BLOB_STREAMBUF_H) */
