// <copyright file="hdf5_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_HDF5_CONFIGURATION_H)
#define _PWROWG_HDF5_CONFIGURATION_H
#pragma once

#include <algorithm>
#include <string>

#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/type_erased_storage.h"


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
    /// Retrieves the keys of all meta data entries to be stored as attributes
    /// in the HDF5 file.
    /// </summary>
    /// <param name="keys">A buffer to receive the keys of the meta data map
    /// in the file. This can be <see langword="nullptr" /> to determine the
    /// required buffer size. The object remains owner of the memory of the
    /// strings to which the pointers are returned.</param>
    /// <param name="cnt">The number of items that can be written to
    /// <paramref name="keys" />.</param>
    /// <returns>The number of meta data items in the file, regardless of
    /// whether anything has been copied to <paramref name="keys" /> or not.
    /// </returns>
    std::size_t meta_data(_Out_writes_opt_(cnt) const char **keys,
        _In_ std::size_t cnt) const noexcept;

    /// <summary>
    /// Retrieves the value of a meta data entry by its key.
    /// </summary>
    /// <param name="key">The key of the meta data entry.</param>
    /// <returns>The value associated with the specified key, or
    /// <see langword="nullptr" /> if the key does not exist. The object remains
    /// owner of the memory.</returns>
    _Ret_maybenull_z_ const char *meta_data(
        _In_z_ const char *key) const noexcept;

    /// <summary>
    /// Adds a new meta data element to be added as attribute to the HDF5 file.
    /// If the key already exists, its value is overwritten with the new value.
    /// </summary>
    /// <param name="key">The key of the meta data entry. This must be a
    /// non-empty string.</param>
    /// <param name="value">The value to be added.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    hdf5_configuration& meta_data(_In_z_ const char *key,
        _In_z_ const char *value);

    /// <summary>
    /// Adds a new meta data element to be added as attribute to the HDF5 file.
    /// If the key already exists, its value is overwritten with the new value.
    /// </summary>
    /// <param name="key">The key of the meta data entry. This must be a
    /// non-empty string.</param>
    /// <param name="value">The value to be added.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline hdf5_configuration& meta_data(_In_z_ const char *key,
            _In_ const std::string& value) {
        return this->meta_data(key, value.c_str());
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
    type_erased_storage _meta_data;
    bool _overwrite;
    blob _path;
    bool _raw;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_HDF5_CONFIGURATION_H) */
