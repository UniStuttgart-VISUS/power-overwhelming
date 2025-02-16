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
#include <thread>

#include "visus/pwrowg/atomic_collector.h"
#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/csv_iomanip.h"
#include "visus/pwrowg/event.h"
#include "visus/pwrowg/literal.h"
#include "visus/pwrowg/sample.h"
#include "visus/pwrowg/thread_name.h"


PWROWG_NAMESPACE_BEGIN

template<class TStream, std::size_t PageSize = 512>
class csv_sink final {

public:

    /// <summary>
    /// The type of a character to be written to the stream.
    /// </summary>
    typedef typename TStream::char_type char_type;

    /// <summary>
    /// The type of the output stream.
    /// </summary>
    typedef TStream stream_type;

    /// <summary>
    /// The callback that must be registered with the sensor array to use the
    /// sink as target for the samples.
    /// </summary>
    /// <param name="samples"></param>
    /// <param name="cnt"></param>
    /// <param name="context"></param>
    static void sample_callback(_In_reads_(cnt) const sample *samples,
        _In_ const std::size_t cnt,
        _In_opt_ void *context);

    explicit csv_sink(_Inout_ stream_type&& stream);

private:

    /// <summary>
    /// The atomic collector used to dump the samples to.
    /// </summary>
    typedef atomic_collector<sample, PageSize> collector_type;

    /// <summary>
    /// Writes the CSV header to <see cref="_stream" />.
    /// </summary>
    void write_header(void);

    /// <summary>
    /// The code running in the <see cref="_writer" /> thread.
    /// </summary>
    void write(void);

    collector_type _collector;
    event_type _evt_write;
    stream_type _stream;
    std::thread _writer;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/csv_sink.inl"

#endif /* !defined(_PWROWG_CSV_SINK_H) */
