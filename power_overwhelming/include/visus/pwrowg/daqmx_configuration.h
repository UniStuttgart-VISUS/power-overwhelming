// <copyright file="daqmx_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_CONFIGURATION_H)
#define _PWROWG_DAQMX_CONFIGURATION_H
#pragma once

#include "visus/pwrowg/sensor_configuration.h"
#include "visus/pwrowg/type_erased_storage.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Provides additional configuration options for NI-DAQmx-based sensors when
/// creating a <see cref="sensor_array" />.
/// </summary>
class POWER_OVERWHELMING_API daqmx_configuration final
        : public sensor_configuration {

public:

    ///// <summary>
    ///// Deserialises a JSON string into a new
    ///// <see cref="daqmx_configuration" /> object.
    ///// </summary>
    ///// <param name="json">The JSON text to be parsed.</param>
    ///// <returns>The configuration object encoded in the given JSON.</returns>
    //static daqmx_configuration from_json(_In_z_ const char *json);

    ///// <summary>
    ///// Loads an <see cref="daqmx_configuration" /> from a JSON file.
    ///// </summary>
    ///// <param name="path">The path to the JSON file to be parsed.</param>
    ///// <returns>The configuration object encoded in the given JSON file.
    ///// </returns>
    //static daqmx_configuration load(_In_z_ const wchar_t *path);

    ///// <summary>
    ///// Loads an <see cref="daqmx_configuration" /> from a JSON file.
    ///// </summary>
    ///// <param name="path">The path to the JSON file to be parsed.</param>
    ///// <returns>The configuration object encoded in the given JSON file.
    ///// </returns>
    //static daqmx_configuration load(_In_z_ const char *path);

    /// <summary>
    /// A unique identifier for the <see cref="daqmx_configuration" /> type.
    /// </summary>
    static const guid id;

    ///// <summary>
    ///// Saves the configuration to a JSON file.
    ///// </summary>
    ///// <param name="path">The location of the output file.</param>
    //void save(_In_z_ const wchar_t *path) const;

    ///// <summary>
    ///// Saves the configuration to a JSON file.
    ///// </summary>
    ///// <param name="path">The location of the output file.</param>
    //void save(_In_z_ const char *path) const;

private:

    type_erased_storage _sensors;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_CONFIGURATION_H) */
