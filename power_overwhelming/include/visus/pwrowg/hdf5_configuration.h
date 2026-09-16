// <copyright file="hdf5_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_PARQUET_CONFIGURATION_H)
#define _PWROWG_PARQUET_CONFIGURATION_H
#pragma once

#include <algorithm>

#include "visus/pwrowg/blob.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Configures the behaviour of the <see cref="hdf5_sink" />.
/// </summary>
class POWER_OVERWHELMING_API hdf5_configuration final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// <param name="path">The path to the HDF5 file to be written.</param>
    /// <param name="overwrite">Indicates whether the file should be overwritten
    /// if it exists. This parameter defaults to <see langword="false" />.
    /// </param>
    /// <exception cref="std::invalid_argument">If <paramref name="path" /> is
    /// <see cref="nullptr" />.</exception>
    hdf5_configuration(_In_z_ const wchar_t *path,
        _In_ const bool overwrite = false);

    /// <summary>
    /// Initialises a new instance.
    /// <param name="path">The path to the HDF5 file to be written.</param>
    /// <param name="overwrite">Indicates whether the file should be overwritten
    /// if it exists. This parameter defaults to <see langword="false" />.
    /// </param>
    /// <exception cref="std::invalid_argument">If <paramref name="path" /> is
    /// <see cref="nullptr" />.</exception>
    hdf5_configuration(_In_z_ const char *path,
        _In_ const bool overwrite = false);

    /// <summary>
    /// Answer the chunk size used for the sample data set.
    /// </summary>
    /// <returns>The chunk size of the sample data set.</returns>
    inline std::size_t chunk_size(void) const noexcept {
        return this->_chunk_size;
    }

    /// <summary>
    /// Sets teh chunk size used for the sample data set.
    /// </summary>
    /// <param name="chunk_size">The number of elements in a chunk.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline hdf5_configuration& chunk_size(
            _In_ const std::size_t chunk_size) noexcept {
        this->_chunk_size = (std::max)(static_cast<std::size_t>(1), chunk_size);
        return *this;
    }

    /// <summary>
    /// Indicates whether an existing file should be overwritten or whether the
    /// sink should fail in this case.
    /// </summary>
    /// <returns><see langword="true"/> if the file should be overwritte,
    /// <see langword="false" /> otherwise.</returns>
    inline bool overwrite(void) const noexcept {
        return this->_overwrite;
    }

    /// <summary>
    /// Gets the path to the Parquet file to be written.
    /// </summary>
    /// <returns>The path to the Parquet file.</returns>
    _Ret_z_ inline const char *path(void) const noexcept {
        _Analysis_assume_(this->_path.as<char>() != nullptr);
        return this->_path.as<char>();
    }

    /// <summary>
    /// Indicates whether the raw bytes of the sensor reading should be stored
    /// rather than forcing a conversion to <see langword="float" /> numbers.
    /// </summary>
    /// <returns><see langword="true "/> if the raw bytes should be stored,
    /// <see langword="false" /> if everything should be converted to
    /// floating-point numbers.</returns>
    inline bool raw(void) const noexcept {
        return this->_raw;
    }

    /// <summary>
    /// Configures whether the raw bytes of the sensor reading should be stored
    /// rather than forcing a conversion to <see langword="float" /> numbers.
    /// </summary>
    /// <param name="raw"><see langword="true "/> if the raw bytes should be
    /// stored, <see langword="false" /> if everything should be converted to
    /// floating-point numbers.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline hdf5_configuration& raw(_In_ const bool raw) noexcept {
        this->_raw = raw;
        return *this;
    }

private:

    std::size_t _chunk_size;
    bool _overwrite;
    blob _path;
    bool _raw;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_PARQUET_CONFIGURATION_H) */
