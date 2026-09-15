// <copyright file="parquet_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_PARQUET_CONFIGURATION_H)
#define _PWROWG_PARQUET_CONFIGURATION_H
#pragma once

#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/parquet_identity_column.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Configures the behaviour of the <see cref="parquet_sink" />.
/// </summary>
class POWER_OVERWHELMING_API parquet_configuration final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// <param name="path">The path to the Parquet file to be written.</param>
    /// <param name="identity">The identity column.</param>
    /// <exception cref="std::invalid_argument">If <paramref name="path" /> is
    /// <see cref="nullptr" />.</exception>
    parquet_configuration(_In_z_ const wchar_t *path,
        _In_ const parquet_identity_column identity);

    /// <summary>
    /// Initialises a new instance.
    /// <param name="path">The path to the Parquet file to be written.</param>
    /// <exception cref="std::invalid_argument">If <paramref name="path" /> is
    /// <see cref="nullptr" />.</exception>
    parquet_configuration(_In_z_ const char *path,
        _In_ const parquet_identity_column identity);

    /// <summary>
    /// Initialises a new instance.
    /// <param name="path">The path to the Parquet file to be written.</param>
    /// <param name="identity">The identity column.</param>
    /// <exception cref="std::invalid_argument">If <paramref name="path" /> is
    /// <see cref="nullptr" />.</exception>
    explicit parquet_configuration(_In_z_ const wchar_t *path);

    /// <summary>
    /// Initialises a new instance.
    /// <param name="path">The path to the Parquet file to be written.</param>
    /// <exception cref="std::invalid_argument">If <paramref name="path" /> is
    /// <see cref="nullptr" />.</exception>
    explicit parquet_configuration(_In_z_ const char *path);

    /// <summary>
    /// Gets the sensor property that is used as the identity for a sensor
    /// in a reading.
    /// </summary>
    /// <returns>The identity column.</returns>
    inline parquet_identity_column identity(void) const noexcept {
        return this->_identity;
    }

    /// <summary>
    /// Sets the sensor property that is used as the identity for a sensor
    /// in a reading. The default is the sensor index, which required joining
    /// the sensor descriptions with the readings. Other properties might
    /// facilitate usage of the readings, but need to store strings rather than
    /// numbers.
    /// </summary>
    /// <param name="identity">The identity column.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline parquet_configuration& identity(
            _In_ const parquet_identity_column identity) noexcept {
        this->_identity = identity;
        return *this;
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
    inline parquet_configuration& raw(_In_ const bool raw) noexcept {
        this->_raw = raw;
        return *this;
    }

    /// <summary>
    /// Indicates whether the sensor identity is stored as string or as a
    /// number.
    /// </summary>
    /// <returns></returns>
    bool string_identity(void) const noexcept;

private:

    parquet_identity_column _identity;
    blob _path;
    bool _raw;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_PARQUET_CONFIGURATION_H) */
