// <copyright file="hdf5_sink_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_HDF5_SINK_IMPL_H)
#define _PWROWG_HDF5_SINK_IMPL_H
#pragma once

#if defined(POWER_OVERWHELMING_WITH_HDF5)
#include <cassert>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include <H5Cpp.h>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/hdf5_configuration.h"
#include "visus/pwrowg/sample.h"
#include "visus/pwrowg/sensor_description.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// The HDF5 representation of a <see cref="sensor_description" />.
/// </summary>
struct hdf5_sensor_description final {
    std::uint32_t source;
    _Field_z_ const char *id;
    _Field_z_ const char *label;
    _Field_z_ const char *name;
    _Field_z_ const char *path;
    reading_type reading_type;
    reading_unit reading_unit;
    _Field_z_ const char *sensor_class;
    sensor_type sensor_type;

    /// <summary>
    /// Create an HDF5 composite type representing this structure.
    /// </summary>
    static H5::CompType create(void);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    hdf5_sensor_description(_In_ const std::uint32_t source,
        _In_ const sensor_description& desc,
        _Inout_ std::set<std::string>& buffer);
};


/// <summary>
/// Holds the implementation details of a <see cref="hdf5_sink" />.
/// </summary>
struct hdf5_sink_impl final {

    /// <summary>
    /// Returns the unmodified floating-point reading.
    /// </summary>
    static inline float from_floating_point(_In_ const reading& r) noexcept {
        return r.floating_point;
    }

    /// <summary>
    /// Returns the reading as floating-point value.
    /// </summary>
    static inline float from_signed_integer(_In_ const reading& r) noexcept {
        return static_cast<float>(r.signed_integer);
    }

    /// <summary>
    /// Returns the reading as floating-point value.
    /// </summary>
    static inline float from_unsigned_integer(_In_ const reading& r) noexcept {
        return static_cast<float>(r.unsigned_integer);
    }

    /// <summary>
    /// A conversion buffer for batching samples before writing them to disk.
    /// </summary>
    std::vector<sample> buffer;

    /// <summary>
    /// If required, a sensor-indexed list of converters that convert the raw
    /// sensor reading to a floating point value. The write method of the sink
    /// will call this method 
    /// </summary>
    std::vector<float (*)(const reading&)> converters;

    /// <summary>
    /// The HDF5 file we are writing to.
    /// </summary>
    H5::H5File file;

    /// <summary>
    /// Indicates whether the samples should be written as byte array or
    /// converted to float.
    /// </summary>
    bool raw;

    /// <summary>
    /// The sample data set.
    /// </summary>
    H5::DataSet samples;

    /// <summary>
    /// Remembers whether we have already written the sensor descriptions.
    /// </summary>
    bool sensors_written;

    /// <summary>
    /// The type used to represent a sample in HDF5.
    /// </summary>
    H5::CompType type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    explicit hdf5_sink_impl(_In_ const hdf5_configuration& config);
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(POWER_OVERWHELMING_WITH_HDF5) */
#endif /* !defined(_PWROWG_HDF5_SINK_IMPL_H) */
