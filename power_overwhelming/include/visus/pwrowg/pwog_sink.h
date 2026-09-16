// <copyright file="pwog_sink.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_PWOG_SINK_H)
#define _PWROWG_PWOG_SINK_H
#pragma once

#include "visus/pwrowg/pwog_file.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A sink writing to our custom binary file format.
/// </summary>
class POWER_OVERWHELMING_API pwog_sink {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="file">The file to write to, which must have been opened for
    /// writing and be in the meta data state or be able to transition to the
    /// meta data state.</param>
    explicit inline pwog_sink(_In_ pwog_file&& file)
            : _file(std::move(file)), _first(true) {
        this->write_meta_data();
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="path">The path to the output file.</param>
    explicit inline pwog_sink(_In_z_ const wchar_t *path)
        : pwog_sink(pwog_file::create(path, true)) { }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="path">The path to the output file.</param>
    explicit inline pwog_sink(_In_z_ const char *path)
        : pwog_sink(pwog_file::create(path, true)) { }

protected:

    /// <summary>
    /// Write the given range of samples to the <see cref="_file" />.
    /// </summary>
    template<class TIterator>
    void write_samples(_In_ const TIterator begin,
        _In_ const TIterator end,
        _In_reads_(cnt) const sensor_description *sensors,
        _In_ const std::size_t cnt);

private:

    /// <summary>
    /// Inserts default meta data into the <see cref="_file" />.
    /// </summary>
    void write_meta_data(void);

    pwog_file _file;
    bool _first;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/pwog_sink.inl"

#endif /* !defined(_PWROWG_PWOG_SINK_H) */
