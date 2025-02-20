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
    explicit inline blob_streambuf(blob& blob) {
        this->setg(blob.as<TChar>(),
            blob.as<TChar>(),
            blob.as<TChar>(blob.size()));
    }
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_BLOB_STREAMBUF_H) */
