// <copyright file="tinkerforge_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TINKERFORGE_SENSOR_H)
#define _PWROWG_TINKERFORGE_SENSOR_H
#pragma once

#include <bricklet_voltage_current_v2.h>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/tinkerforge_configuration.h"
#include "visus/pwrowg/tinkerforge_error_count.h"
#include "visus/pwrowg/tinkerforge_sample_averaging.h"
#include "visus/pwrowg/tinkerforge_sensor_source.h"

#include "sensor.h"
#include "sensor_description_builder.h"
#include "sensor_utilities.h"
#include "sensor_state.h"
#include "tinkerforge_bricklet.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A power sensor based on the Tinkerforge current/voltage bricklet v2.
/// </summary>
class PWROWG_TEST_API tinkerforge_sensor final : public sensor {

public:

    /// <summary>
    /// The type of sensor class configuration used by this sensor.
    /// </summary>
    typedef tinkerforge_configuration configuration_type;

    /// <summary>
    /// Create descriptions for all supported Tinkerforge sensors in the system.
    /// </summary>
    /// <remarks>
    /// <para>It is safe to call this method on systems without a connection to a
    /// Tinkerforge brick. No descriptions are returned in this case.</para>
    /// </remarks>
    /// <param name="config">The global sensor configuration which might affect
    /// which sensors can be enumerated.</param>
    /// <returns>A list of sensor descriptors that can be used to instantiate a
    /// specific sensor.</returns>
    template<class TOutput> static void descriptions(_In_ TOutput oit,
        _In_ const configuration_type& config);

    /// <summary>
    /// Generate sensors for all matching configurations within
    /// <paramref name="begin" /> and <paramref name="end" />.
    /// </summary>
    /// <remarks>
    /// <para>The method will go through all sensor descriptions provided and
    /// created sensors for each description that is recognised as one of its
    /// own. All of these matching descriptions are sorted to the begin of the
    /// range. All other descriptions, which could not be used to create a
    /// sensor of this type, are move to the end of the range and the returned
    /// iterator points to the first of those descriptions.</para>
    /// </remarks>
    /// <typeparam name="TOutput">An output iterator for shared pointers of
    /// sensors that is able to receive at least a sensor for every element
    /// <paramref name="begin" /> and <paramref name="end" />.</typeparam>
    /// <typeparam name="TInput">The type of the input iterator over the
    /// <see cref="sensor_description" />s.</typeparam>
    /// <param name="oit">The output iterator receiving the sensors.</param>
    /// <param name="index">The index to be used for the first sensor created.
    /// </param>
    /// <param name="begin">The begin of the range of sensor descriptions.
    /// </param>
    /// <param name="end">The end of the range of sensor descriptions.</param>
    /// <returns>The iterator to the first sensor description within
    /// <paramref name="begin" /> and <paramref name="end" /> that has not been
    /// used for creating a sensor.</returns>
    template<class TOutput, class TInput>
    static TInput from_descriptions(_In_ TOutput oit, _In_ std::size_t index,
        _In_ const TInput begin, _In_ const TInput end);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="scope">The scope managing the connection with the Brick
    /// daemon.</param>
    /// <param name="uid">The unique identifier of the voltage/current
    /// bricklet addressed by the sensor.</param>
    /// <param name="source">A bitmask of the sources enabled on the
    /// bricklet.</param>
    /// <exception cref="std::invalid_argument">If <paramref name="uid" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="tinkerforge_exception">If the bricklet could not be
    /// opened.</exception>
    tinkerforge_sensor(_In_ tinkerforge_scope scope,
        _In_z_ const char *uid,
        _In_ const tinkerforge_sensor_source source);

    /// <summary>
    /// Retrieves the current configuration of the bricklet.
    /// </summary>
    /// <param name="averaging">Receives the number of samples to average.
    /// </param>
    /// <param name="voltage_conversion_time">Receives the A/D conversion
    /// time for voltage.</param>
    /// <param name="current_conversion_time">Receives the A/D conversion
    /// time for current.</param>
    /// <exception cref="std::runtime_error">If the sensor has been disposed
    /// by a move before.</exception>
    /// <exception cref="tinkerforge_exception">If the operation failed.
    /// </exception>
    void configuration(_Out_ tinkerforge_sample_averaging& averaging,
        _Out_ tinkerforge_conversion_time &voltage_conversion_time,
        _Out_ tinkerforge_conversion_time &current_conversion_time);

    /// <summary>
    /// Configures the bricklet.
    /// </summary>
    /// <param name="averaging">The number of samples to average.</param>
    /// <param name="voltage_conversion_time">The A/D conversion time for
    /// voltage.</param>
    /// <param name="current_conversion_time">The A/D conversion time for
    /// current.</param>
    /// <exception cref="std::runtime_error">If the sensor has been disposed
    /// by a move before.</exception>
    /// <exception cref="tinkerforge_exception">If the operation failed.
    /// </exception>
    void configuration(_In_ const tinkerforge_sample_averaging averaging,
        _In_ const tinkerforge_conversion_time voltage_conversion_time,
        _In_ const tinkerforge_conversion_time current_conversion_time);

    /// <summary>
    /// Answer the number of errors that occured while the brick
    /// communicated to the bricklet.
    /// </summary>
    /// <returns>The error statistics</returns>
    /// <exception cref="std::runtime_error">If the sensor has been disposed
    /// by a move before.</exception>
    /// <exception cref="tinkerforge_exception">If the operation failed.
    /// </exception>
    tinkerforge_error_count error_count(void) const;

    /// <summary>
    /// Identify the bricklet used for the sensor.
    /// </summary>
    /// <param name="uid">Receives the UID of the sensor bricklet.</param>
    /// <param name="connected_to_uid">Receives the UID of the brick the
    /// sensor is connected to.</param>
    /// <param name="position">Receives the position ('a' to 'h') where the
    /// bricklet is connected to the brick.</param>
    /// <param name="hardware_version">Receives the major, minor, revision
    /// version of the hardware.</param>
    /// <param name="firmware_version">Receives the major, minor, revision
    /// version of the firmware.</param>
    /// <param name="device_id">Receives the ID of the hardware type, which
    /// should be 2105 for the Voltage/Current Bricklet 2.0. See
    /// https://www.tinkerforge.com/de/doc/Software/Device_Identifier.html#device-identifier
    /// for a list of identifiers.</param>
    /// <exception cref="std::runtime_error">If the sensor has been disposed
    /// by a move before.</exception>
    /// <exception cref="tinkerforge_exception">If the operation failed.
    /// </exception>
    void identify(_Out_writes_(8) char uid[8],
        _Out_writes_(8) char connected_to_uid[8],
        _Out_ char& position,
        _Out_writes_(3) std::uint8_t hardware_version[3],
        _Out_writes_(3) std::uint8_t firmware_version[3],
        _Out_ std::uint16_t& device_id) const;

    /// <summary>
    /// Answer the UID of the bricklet used for the sensor.
    /// </summary>
    /// <param name="uid">Receives the UID of the sensor bricklet.</param>
    /// <exception cref="std::runtime_error">If the sensor has been disposed
    /// by a move before.</exception>
    /// <exception cref="tinkerforge_exception">If the operation failed.
    /// </exception>
    void identify(_Out_writes_(8) char uid[8]) const;

    /// <summary>
    /// Reset the bricklet.
    /// </summary>
    /// <remarks>
    /// If the library is using our custom firmware, this will also trigger
    /// a resynchronisation of the internal clock with the wall clock time.
    /// This can take some time, expecially when using many bricklets.
    /// </remarks>
    void reset(void);

    /// <summary>
    /// Forces the implementation to resynchronise the internal clock of
    /// the bricklet with the wall-clock of the PC.
    /// </summary>
    /// <remarks>
    /// This method has no effect if the library has not been built with
    /// support for our custom firmware or the bricklet does not run this
    /// firmware.
    /// </remarks>
    /// <param name="cnt">The number of time translations (measurements)
    /// that can be made with the same synchronisation state.</param>
    void resync_internal_clock(void);

    /// <summary>
    /// Instructs the implementation to synchronise the internal clock of
    /// the bricklet with the wall-clock of the PC every
    /// <paramref name="cnt" /> measurements.
    /// </summary>
    /// <remarks>
    /// This method has no effect if the library has not been built with
    /// support for our custom firmware or the bricklet does not run this
    /// firmware.
    /// </remarks>
    /// <param name="cnt">The number of time translations (measurements)
    /// that can be made with the same synchronisation state.</param>
    void resync_internal_clock_after(_In_ const std::size_t cnt);

private:

    /// <summary>
    /// The private data stored in the <see cref="sensor_description" />.
    /// </summary>
    struct private_data {
        tinkerforge_configuration::end_point end_point;
        tinkerforge_sensor_source source;

        inline private_data(
                _In_ const tinkerforge_configuration::end_point& end_point,
                _In_ const tinkerforge_sensor_source source)
            : end_point(end_point), source(source) { }
    };

    /// <summary>
    /// Specialise the <paramref name="builder" /> for the given bricklet.
    /// </summary>
    static sensor_description_builder& specialise(
        _In_ sensor_description_builder& builder,
        _In_ const tinkerforge_configuration::end_point& end_point,
        _In_ const tinkerforge_bricklet& bricklet,
        _In_ const tinkerforge_sensor_source source,
        _In_ const sensor_type type,
        _In_ const reading_unit unit);

    mutable VoltageCurrentV2 _bricklet;
    tinkerforge_scope _scope;
    tinkerforge_sensor_source _source;
    sensor_state _state;
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    tinkerforge_time_translator _time_xlate;
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
    std::string _uid;
};

PWROWG_DETAIL_NAMESPACE_END

#include "tinkerforge_sensor.inl"

#endif /* !defined(_PWROWG_TINKERFORGE_SENSOR_H) */
