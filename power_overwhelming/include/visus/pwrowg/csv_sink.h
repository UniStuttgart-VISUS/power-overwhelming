// <copyright file="csv_sink.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_CSV_SINK_H)
#define _PWROWG_CSV_SINK_H
#pragma once

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "visus/pwrowg/atomic_sink.h"
#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/csv_iomanip.h"
#include "visus/pwrowg/literal.h"


PWROWG_NAMESPACE_BEGIN

template<class TStream> class csv_sink {

public:

    /// <summary>
    /// The type of a character to be written to the stream.
    /// </summary>
    typedef typename TStream::char_type char_type;

    /// <summary>
    /// The type of the output stream.
    /// </summary>
    typedef TStream stream_type;

    explicit csv_sink(_Inout_ stream_type&& stream);

protected:

    /// <summary>
    /// Write the given range of samples to the <see cref="_stream" />.
    /// </summary>
    template<class TIterator>
    void write_samples(_In_ const TIterator begin,
        _In_ const TIterator end,
        _In_ const sensor_description *sensors);

private:

    csv_column _columns;
    char_type _delimiter;
    stream_type _stream;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/csv_sink.inl"

#endif /* !defined(_PWROWG_CSV_SINK_H) */
