// <copyright file="daqmx_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_CONFIGURATION_H)
#define _PWROWG_DAQMX_CONFIGURATION_H
#pragma once

#include "visus/pwrowg/daqmx_implicit_timing.h"
#include "visus/pwrowg/daqmx_sensor_definition.h"
#include "visus/pwrowg/daqmx_sample_clock_timing.h"
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

    /// <summary>
    /// Deserialises a JSON string into a new
    /// <see cref="daqmx_configuration" /> object.
    /// </summary>
    /// <param name="json">The JSON text to be parsed.</param>
    /// <returns>The configuration object encoded in the given JSON.</returns>
    static daqmx_configuration from_json(_In_z_ const char *json);

    /// <summary>
    /// Loads an <see cref="daqmx_configuration" /> from a JSON file.
    /// </summary>
    /// <param name="path">The path to the JSON file to be parsed.</param>
    /// <returns>The configuration object encoded in the given JSON file.
    /// </returns>
    static daqmx_configuration load(_In_z_ const wchar_t *path);

    /// <summary>
    /// Loads an <see cref="daqmx_configuration" /> from a JSON file.
    /// </summary>
    /// <param name="path">The path to the JSON file to be parsed.</param>
    /// <returns>The configuration object encoded in the given JSON file.
    /// </returns>
    static daqmx_configuration load(_In_z_ const char *path);

    /// <summary>
    /// A unique identifier for the <see cref="daqmx_configuration" /> type.
    /// </summary>
    static const guid id;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    daqmx_configuration(void);

    /// <summary>
    /// Adds a new sensor definition to the configuration.
    /// </summary>
    /// <param name="sensor">The sensor to be added.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    daqmx_configuration& add_sensor(_In_ const daqmx_sensor_definition& sensor);

    /// <summary>
    /// Adds a new sensor definition to the configuration.
    /// </summary>
    /// <param name="sensor">The sensor to be added.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    daqmx_configuration& add_sensor(_Inout_ daqmx_sensor_definition&& sensor);

    /// <summary>
    /// Answer the number of sensors (voltage/current pairs) that have been
    /// configured.
    /// </summary>
    /// <returns>The number of configured sensors.</returns>
    std::size_t count_sensors(void) const noexcept;

    /// <summary>
    /// Saves the configuration to a JSON file.
    /// </summary>
    /// <param name="path">The location of the output file.</param>
    void save(_In_z_ const wchar_t *path) const;

    /// <summary>
    /// Saves the configuration to a JSON file.
    /// </summary>
    /// <param name="path">The location of the output file.</param>
    void save(_In_z_ const char *path) const;

    /// <summary>
    /// Answer the <paramref name="index" />th sensor.
    /// </summary>
    /// <param name="index">The zero-based index of the sensor.</param>
    /// <returns>The sensor definition at the specified index.</returns>
    /// <exception cref="std::out_of_range">The index is greater than or equal
    /// to the number of sensors.</exception>
    const daqmx_sensor_definition& sensor(_In_ const std::size_t index) const;

    /// <summary>
    /// Answer the array of registered <see cref="daqmx_sensor_definition" />s.
    /// </summary>
    /// <remarks>
    /// The size of the array can be obtained from
    /// <see cref="count_sensors" />.
    /// </remarks>
    /// <returns>The configured sensors.</returns>
    _Ret_valid_ const daqmx_sensor_definition *sensors(void) const noexcept;

    /// <summary>
    /// Replaces any existing <see cref="daqmx_sensor_definition" />s with the given
    /// array of new sensors.
    /// </summary>
    /// <param name="sensors">An array of at least <paramref name="cnt" /> sensor
    /// definitions.</param>
    /// <param name="cnt">The number of sensor definitions provided.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    daqmx_configuration& sensors(
        _In_reads_opt_(cnt) daqmx_sensor_definition *sensors,
        _In_ const std::size_t cnt);

    /// <summary>
    /// Answer the acquistion timing configuration for the sensors.
    /// </summary>
    /// <returns>The timing configuration, which must be cast to the actual
    /// type using a <see langword="dynamic_cast" />.</returns>
    const daqmx_timing& timing(void) const;

    /// <summary>
    /// Sets a new timing configuration.
    /// </summary>
    /// <param name="timing">The new timing configuration.</param>
    /// <returns><c>*<see langword="this" /><c>.</returns>
    daqmx_configuration& timing(_In_ const daqmx_implicit_timing& timing);

    /// <summary>
    /// Sets a new timing configuration.
    /// </summary>
    /// <param name="timing">The new timing configuration.</param>
    /// <returns><c>*<see langword="this" /><c>.</returns>
    daqmx_configuration& timing(_Inout_ daqmx_implicit_timing&& timing);

    /// <summary>
    /// Sets a new timing configuration.
    /// </summary>
    /// <param name="timing">The new timing configuration.</param>
    /// <returns><c>*<see langword="this" /><c>.</returns>
    daqmx_configuration& timing(_In_ const daqmx_sample_clock_timing& timing);

    /// <summary>
    /// Sets a new timing configuration.
    /// </summary>
    /// <param name="timing">The new timing configuration.</param>
    /// <returns><c>*<see langword="this" /><c>.</returns>
    daqmx_configuration& timing(_Inout_ daqmx_sample_clock_timing&& timing);

    /// <summary>
    /// Checks whether the timing configuration is of type
    /// <see cref="daqmx_implicit_timing" />, and if so, returns it.
    /// </summary>
    /// <param name="timing">Receives a pointer to the timing configuration in case
    /// of success.</param>
    /// <returns><see langword="true "/> if a configuration was written to
    /// <paramref name="timing" />, <see langword="false" /> otherwise.</returns>
    bool try_get(_Out_opt_ const daqmx_implicit_timing *& timing) const;

    /// <summary>
    /// Checks whether the timing configuration is of type
    /// <see cref="daqmx_sample_clock_timing" />, and if so, returns it.
    /// </summary>
    /// <param name="timing">Receives a pointer to the timing configuration in case
    /// of success.</param>
    /// <returns><see langword="true "/> if a configuration was written to
    /// <paramref name="timing" />, <see langword="false" /> otherwise.</returns>
    bool try_get(_Out_opt_ const daqmx_sample_clock_timing *& timing) const;

private:

    type_erased_storage _sensors;
    type_erased_storage _timing;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_CONFIGURATION_H) */
