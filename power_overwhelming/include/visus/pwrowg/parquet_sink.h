// <copyright file="parquet_sink.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_PARQUET_SINK_H)
#define _PWROWG_PARQUET_SINK_H
#pragma once

#if defined(POWER_OVERWHELMING_WITH_PARQUET)
#include "visus/pwrowg/parquet_configuration.h"
#include "visus/pwrowg/sample.h"
#include "visus/pwrowg/sensor_description.h"


PWROWG_NAMESPACE_BEGIN

// Forward declarations.
namespace detail { struct parquet_sink_impl; }


/// <summary>
/// A sink writing the power measurements to an Apache Parquet file.
/// </summary>
class POWER_OVERWHELMING_API parquet_sink {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="config">The configuration for the Parquet sink.</param>
    explicit parquet_sink(_In_ const parquet_configuration& config);

    /// <summary>
    /// Initialise from move.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    inline parquet_sink(_Inout_ parquet_sink&& rhs) noexcept
            : _impl(rhs._impl) {
        rhs._impl = nullptr;
    }

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~parquet_sink(void) noexcept;

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    parquet_sink& operator =(_Inout_ parquet_sink&& rhs) noexcept;

protected:

    /// <summary>
    /// Write the given range of samples to the <see cref="_stream" />.
    /// </summary>
    template<class TIterator>
    void write_samples(_In_ const TIterator begin,
        _In_ const TIterator end,
        _In_ const sensor_description *sensors);

private:

    void end_row_group(void);

    void write_sample(_In_ const sample& s,
        _In_ const sensor_description *sensors);

    detail::parquet_sink_impl *_impl;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/parquet_sink.inl"

#endif /* defined(POWER_OVERWHELMING_WITH_PARQUET) */
#endif /* !defined(_PWROWG_PARQUET_SINK_H) */
