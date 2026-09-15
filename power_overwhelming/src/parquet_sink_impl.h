// <copyright file="parquet_sink_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_PARQUET_SINK_IMPL_H)
#define _PWROWG_PARQUET_SINK_IMPL_H
#pragma once

#if defined(POWER_OVERWHELMING_WITH_PARQUET)
#include <cassert>
#include <memory>
#include <string>
#include <vector>

#if (defined(_MSC_VER) && defined(min))
#pragma push_macro("min")
#undef min
#define _PWROWG_POP_MIN
#endif /* (defined(_MSC_VER) && defined(min)) */

#include <arrow/io/api.h>
#include <arrow/util/type_fwd.h>

#include <parquet/arrow/writer.h>
#include <parquet/stream_writer.h>

#if defined(_PWROWG_POP_MIN)
#pragma pop_macro("min")
#endif /* _PWROWG_POP_MIN */

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/parquet_configuration.h"
#include "visus/pwrowg/sensor_description.h"
#include "visus/pwrowg/string_functions.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Holds the implementation details of a <see cref="parquet_sink" />.
/// </summary>
struct parquet_sink_impl final {

    /// <summary>
    /// If not empty, serves as the LUT for the sensor identities to be
    /// written to the parquet file.
    /// </summary>
    std::vector<std::string> identities;

    /// <summary>
    /// Remembers the identity column.
    /// </summary>
    parquet_identity_column identity;

    /// <summary>
    /// Controls whether the raw bytes of the readings are written or whether
    /// everything is converted to <see langword="float" />s.
    /// </summary>
    bool raw;

    /// <summary>
    /// The output stream for <see cref="writer" /> to write to.
    /// </summary>
    std::shared_ptr<arrow::io::FileOutputStream> stream;

    /// <summary>
    /// The Parquet file writer for the configured output file.
    /// </summary>
    //std::unique_ptr<parquet::arrow::FileWriter> writer;
    parquet::StreamWriter writer;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="config">The configuration of the Parquet output.</param>
    explicit parquet_sink_impl(_In_ const parquet_configuration& config);

    /// <summary>
    /// Creates an ID string for the <paramref name="idx" />-th sensor in
    /// <paramref name="sensors" />.
    /// </summary>
    inline std::string get_id(
            _In_reads_(idx) const sensor_description *sensors,
            _In_ const size_t idx) const {
        assert(sensors != nullptr);
        return PWROWG_NAMESPACE::convert_string<char>(sensors[idx].id());
    }

    /// <summary>
    /// If enabled by <pararmef name="identity" />, creates all identity strings
    /// up to <paramref name="idx" /> from <paramref name="sensors" /> and 
    /// returns the <paramref name="idx" />-th identity string from the local
    /// cache in <see cref="identities" />. This method will lazily create all
    /// identity strings up to <paramref name="idx" />.
    /// </summary>
    const std::string& get_identity(
        _In_reads_(idx) const sensor_description *sensors,
        _In_ const size_t idx);

    /// <summary>
    /// Creates a label string for the <paramref name="idx" />-th sensor in
    /// <paramref name="sensors" />, either by using the user-provided label
    /// or the ID as fallback.
    /// </summary>
    inline std::string get_label(
            _In_reads_(idx) const sensor_description *sensors,
            _In_ const size_t idx) const {
        assert(sensors != nullptr);
        return empty(sensors[idx].label())
            ? PWROWG_NAMESPACE::convert_string<char>(sensors[idx].id())
            : PWROWG_NAMESPACE::convert_string<char>(sensors[idx].label());
    }
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_PARQUET_SINK_IMPL_H) */
#endif /* !defined(_PWROWG_PARQUET_SINK_IMPL_H) */
