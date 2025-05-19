// <copyright file="emi_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_EMI_SENSOR_H)
#define _PWROWG_EMI_SENSOR_H
#pragma once

#include <list>
#include <vector>

#if defined(_WIN32)
#include <Windows.h>
#include <emi.h>
#include <tchar.h>
#endif /* defined(_WIN32) */

#include "visus/pwrowg/emi_configuration.h"
#include "visus/pwrowg/sensor_array_callback.h"
#include "visus/pwrowg/sensor_description.h"
#include "visus/pwrowg/sensor_filters.h"

#include "emi_device_factory.h"
#include "sensor_utilities.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Implementation of a power sensor using the Energy Meter Interface
/// available in Windows 10 and above.
/// </summary>
class PWROWG_TEST_API emi_sensor final {

public:

#if defined(_WIN32)
    /// <summary>
    /// The type used to identify a channel in EMIv2.
    /// </summary>
    typedef decltype(EMI_METADATA_V2::ChannelCount) channel_type;
#endif /* defined(_WIN32) */

    /// <summary>
    /// The type used for strings that are passed to the OS API.
    /// </summary>
    typedef wchar_t char_type;

    /// <summary>
    /// The type of sensor class configuration used by this sensor.
    /// </summary>
    typedef emi_configuration configuration_type;

#if defined(_WIN32)
    /// <summary>
    /// The type that EMI uses to store absolute energy.
    /// </summary>
    typedef decltype(EMI_CHANNEL_MEASUREMENT_DATA::AbsoluteEnergy) energy_type;
#endif /* defined(_WIN32) */

    /// <summary>
    /// The type of a list of sensors of this type.
    /// </summary>
    typedef std::list<emi_sensor> list_type;

#if defined(_WIN32)
    /// <summary>
    /// The type that EMI uses to store timestamps.
    /// </summary>
    /// <remarks>
    /// According to the documentation, absolute timestamps are in 100 ns
    /// units from an arbitrary starting point (probably the start of the
    /// system).
    /// </remarks>
    typedef decltype(EMI_CHANNEL_MEASUREMENT_DATA::AbsoluteTime) time_type;
#endif /* defined(_WIN32) */

#if defined(_WIN32)
    /// <summary>
    /// The type used to store the version of the EMI.
    /// </summary>
    typedef decltype(EMI_VERSION::EmiVersion) version_type;
#endif /* defined(_WIN32) */

    /// <summary>
    /// Create descriptions for all supported EMI sensors in the system.
    /// </summary>
    /// <remarks>
    /// <para>It is safe to call this method on systems that do not support the
    /// Energy Metering Interface. No descriptions are returned in this case.
    /// </para>
    /// </remarks>
    /// <param name="config">The global sensor configuration which might affect
    /// which sensors can be enumerated.</param>
    /// <returns>The number of available sensors, independently from the fact
    /// whether all of them have been returned.</returns>
    static std::size_t descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
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
    /// <typeparam name="TInput">The type of the input iterator over the
    /// <see cref="sensor_description" />s.</typeparam>
    /// <param name="dst">The output list, which will receive the sensors and the
    /// sampler callbacks.</param>
    /// <param name="index">The index to be used for the first sensor created.
    /// </param>
    /// <param name="begin">The begin of the range of sensor descriptions.
    /// </param>
    /// <param name="end">The end of the range of sensor descriptions.</param>
    /// <param name="owner">The sensor array owning the sensors to be created.
    /// This pointer is required to gain access to the callback pointers and
    /// the context data. It can also be used to access the per-sensor class
    /// configuration contained  in <paramref name="config" /> later on.</param>
    /// <param name="config">The configuration for the sensor class.</param>
    /// <returns>The iterator to the first sensor description within
    /// <paramref name="begin" /> and <paramref name="end" /> that has not been
    /// used for creating a sensor.</returns>
    template<class TInput>
    static TInput from_descriptions(_In_ list_type& dst,
        _In_ sample::source_type index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config);

#if defined(_WIN32)
    emi_sensor(_In_z_ const wchar_t *path,
        _In_ std::vector<channel_type>&& channels,
        _In_ const PWROWG_NAMESPACE::sample::source_type index);

    /// <summary>
    /// Deliver a sample to the given <paramref name="callback" />.
    /// </summary>
    /// <param name="callback">The callback to be invoked.</param>
    /// <param name="sensors">The sensor descriptions passed to the
    /// <paramref name="callback" />.</param>
    /// <param name="context">An optional context pointer passed to the
    /// <paramref name="callback" />.</param>
    void sample(_In_ const sensor_array_callback callback,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context = nullptr);

#else /* defined(_WIN32) */
    emi_sensor(void) = delete;
#endif /* defined(_WIN32) */

private:

#if defined(_WIN32)
    /// <summary>
    /// Computes the required buffer size.
    /// </summary>
    std::size_t buffer_size(void) const;

    /// <summary>
    /// Evaluate the given channel data and save them as the previous
    /// measurement in <see cref="_last_energy" /> and
    /// <see cref="_last_time" />.
    /// </summary>
    void evaluate(_In_ const EMI_CHANNEL_MEASUREMENT_DATA& data,
        _In_ const sensor_array_callback callback,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context);

    /// <summary>
    /// Evaluate the channel represented by this sensor with data from the
    /// given measurement and and same them as the previous measurement in
    /// <see cref="_last_energy" /> and <see cref="_last_time" />.
    /// </summary>
    void evaluate(_In_ const EMI_MEASUREMENT_DATA_V2& data,
        _In_ const sensor_array_callback callback,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context);

    /// <summary>
    /// Obtain a new raw sample from the device via an IOCTL.
    /// </summary>
    std::size_t sample(_Out_writes_bytes_opt_(cnt) void *buffer,
        _In_ const std::size_t cnt);

    /// <summary>
    /// Answer the EMI version.
    /// </summary>
    inline version_type version(void) const noexcept {
        assert(this->_device != nullptr);
        return this->_device->version().EmiVersion;
    }

    /// <summary>
    /// The channels sampled by this sensor.
    /// </summary>
    std::vector<channel_type> _channels;

    /// <summary>
    /// The RAII wrapper for the EMI device handle.
    /// </summary>
    emi_device_factory::device_type _device;

    /// <summary>
    /// The index of the (first) sensor.
    /// </summary>
    PWROWG_NAMESPACE::sample::source_type _index;

    /// <summary>
    /// Remembers the absolute energy from when the sensor was last sampled.
    /// </summary>
    std::vector<energy_type> _last_energy;

    /// <summary>
    /// Remembers the absolute time when the sensor was last sampled.
    /// </summary>
    std::vector<time_type> _last_time;

    /// <summary>
    /// The offset of the world clock time from the timestamps of the EMI
    /// sensor, because EMI counts since the start of the system, but we need to
    /// report a wall-clock time.
    /// </summary>
    std::vector<decltype(LARGE_INTEGER::QuadPart)> _time_offset;
#endif /* defined(_WIN32) */
};

PWROWG_DETAIL_NAMESPACE_END

#include "emi_sensor.inl"

#endif /* defined(_PWROWG_EMI_SENSOR_H) */

