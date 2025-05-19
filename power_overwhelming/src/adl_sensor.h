// <copyright file="adl_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_ADL_SENSOR_H)
#define _PWROWG_ADL_SENSOR_H
#pragma once

#include <chrono>
#include <list>
#include <vector>

#include "visus/pwrowg/adl_configuration.h"
#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/sensor_array_callback.h"
#include "visus/pwrowg/sensor_description.h"
#include "visus/pwrowg/sensor_filters.h"

#include "adl_scope.h"
#include "adl_exception.h"
#include "amd_display_library.h"
#include "sensor_description_builder.h"
#include "sensor_utilities.h"
#include "timezone.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A sensor drawing its information from the AMD display library (ADL).
/// </summary>
/// <remarks>
/// <para>Implementation note: There will always be one ADL sensor per AMD
/// device in a sensor array which samples all ADL data. The reason for that is
/// that ADL returns everything in one batch from the device.</para>
/// <para>The ADL sensor is weird in that is internally asynchronous, because
/// the driver delivers the samples without our intervention. However, we need to
/// retrieve them synchronously from the designated memory area.</para>
/// </remarks>
class PWROWG_TEST_API adl_sensor final {

public:

    /// <summary>
    /// The type used to refer to an adapter via its index.
    /// </summary>
    typedef decltype(AdapterInfo::iAdapterIndex) adapter_type;

    /// <summary>
    /// The type of sensor class configuration used by this sensor.
    /// </summary>
    typedef adl_configuration configuration_type;

    /// <summary>
    /// The type of a list of sensors of this type.
    /// </summary>
    typedef std::list<adl_sensor> list_type;

    /// <summary>
    /// The type used to express the ADL sampling rate.
    /// </summary>
    typedef std::chrono::duration<unsigned long, std::milli> sampling_rate_type;

    /// <summary>
    /// Create descriptions for all supported ADL sensors in the system.
    /// </summary>
    /// <remarks>
    /// <para>It is safe to call this method on systems without ADL GPU.
    /// No descriptions are returned in this case.</para>
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

    /// <summary>
    /// Create a new instance for the specified adapter index.
    /// </summary>
    /// <param name="adapter_index">The adapter index to create the sensor for.
    /// </param>
    /// <param name="sources">The sensor sources to retrieve.</param>
    /// <param name="sampling_rate">The sampling rate at which the ADL should
    /// provide new data.</param>
    /// <param name="index">The index of the first of the
    /// <paramref name="sources" />.</param>
    /// <returns></returns>
    /// <exception cref="adl_exception">If the specified device was not
    /// found, or another error occurred in ADL.</exception>
    static inline std::shared_ptr<adl_sensor> from_index(
            _In_ const int adapter_index,
            _In_ const std::vector<ADL_PMLOG_SENSORS>& sources,
            _In_ const sampling_rate_type sampling_rate,
            _In_ const PWROWG_NAMESPACE::sample::source_type index) {
        return std::make_shared<adl_sensor>(adapter_index,
            sources,
            sampling_rate,
            index);
    }

    /// <summary>
    /// Create a new instance for the unique device ID.
    /// </summary>
    /// <param name="udid">The unique device ID to create the sensor for.
    /// </param>
    /// <param name="sources">The sensor sources to retrieve.</param>
    /// <param name="sampling_rate">The sampling rate at which the ADL should
    /// provide new data.</param>
    /// <param name="index">The index of the first of the
    /// <paramref name="sources" />.</param>
    /// <returns></returns>
    /// <exception cref="std::invalid_argument">If <paramref name="udid" />
    /// is <c>nullptr</c> or if it did not match exactly one device.
    /// </exception>
    /// <exception cref="adl_exception">If the specified device was not
    /// found, or another error occurred in ADL.</exception>
    static std::shared_ptr<adl_sensor> from_udid(
        _In_z_ const char *udid,
        _In_ const std::vector<ADL_PMLOG_SENSORS>& sources,
        _In_ const sampling_rate_type sampling_rate,
        _In_ const PWROWG_NAMESPACE::sample::source_type index);

    /// <summary>
    /// Create a new instance for the unique device ID.
    /// </summary>
    /// <param name="udid">The unique device ID to create the sensor for.
    /// </param>
    /// <param name="sources">The sensor sources to retrieve.</param>
    /// <param name="sampling_rate">The sampling rate at which the ADL should
    /// provide new data.</param>
    /// <param name="index">The index of the first of the
    /// <paramref name="sources" />.</param>
    /// <returns></returns>
    /// <exception cref="std::invalid_argument">If <paramref name="udid" />
    /// is <c>nullptr</c> or if it did not match exactly one device.
    /// </exception>
    /// <exception cref="adl_exception">If the specified device was not
    /// found, or another error occurred in ADL.</exception>
    static inline std::shared_ptr<adl_sensor> from_udid(
            _In_z_ const wchar_t *udid,
            _In_ const std::vector<ADL_PMLOG_SENSORS>& sources,
            _In_ const sampling_rate_type sampling_rate,
            _In_ const PWROWG_NAMESPACE::sample::source_type index) {
        auto u = PWROWG_NAMESPACE::convert_string<char>(udid);
        return from_udid(u.c_str(), sources, sampling_rate, index);
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="adapter">The index of the adapter to create the sensor for.
    /// </param>
    /// <param name="sources">The sources to be sampled from the adapter.</param>
    /// <param name="sampling_rate">The sampling rate at which the ADL should
    /// provide new data.</param>
    /// <param name="index">The index of the first of the
    /// <paramref name="sources" />.</param>
    adl_sensor(_In_ const adapter_type adapter,
        _In_ const std::vector<ADL_PMLOG_SENSORS>& sources,
        _In_ const sampling_rate_type sampling_rate,
        _In_ const PWROWG_NAMESPACE::sample::source_type index);

    adl_sensor(const adl_sensor&) = delete;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~adl_sensor(void) noexcept;

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

    adl_sensor& operator =(const adl_sensor&) = delete;

private:

    /// <summary>
    /// The sensor-specific data embedded in a description.
    /// </summary>
    struct private_data {
        adapter_type adapter;
        ADL_PMLOG_SENSORS source;
        inline private_data(_In_ const adapter_type adapter,
                _In_ const ADL_PMLOG_SENSORS source)
            : adapter(adapter), source(source) { }
    };

    /// <summary>
    /// The type of a timestamp.
    /// </summary>
    typedef PWROWG_NAMESPACE::timestamp timestamp_type;

    /// <summary>
    /// Specialises the description builder for the given type of sensor.
    /// </summary>
    static bool specialise(_In_ sensor_description_builder& builder,
        _In_ const AdapterInfo& info,
        _In_ const ADL_PMLOG_SENSORS sensor);

    /// <summary>
    /// Convert the last update time of <paramref name="data" /> to a timestamp.
    /// </summary>
    inline timestamp_type timestamp(_In_ const ADLPMLogData& data) noexcept {
        auto local = static_cast<timestamp_type::value_type>(data.ulLastUpdated);
        return timestamp_type(local + this->_utc_offset);
    }

    /// <summary>
    /// The adpater index of the device, which is required for a series of
    /// APIs.
    /// </summary>
    adapter_type _adapter_index;

    /// <summary>
    /// The handle for the device the sensor is working on.
    /// </summary>
    ADL_D3DKMT_HANDLE _device;

    /// <summary>
    /// The index of the first source.
    /// </summary>
    PWROWG_NAMESPACE::sample::source_type _index;

    /// <summary>
    /// The ADL scope making sure the library is ready while the sensor
    /// exists.
    /// </summary>
    adl_scope _scope;

    /// <summary>
    /// The input for the sensor start function (selection of sensors to
    /// report).
    /// </summary>
    ADLPMLogStartInput _start_input;

    /// <summary>
    /// The output of the sensor start function (valid only as long as the
    /// sensor is running).
    /// </summary>
    ADLPMLogStartOutput _start_output;

    /// <summary>
    /// The UTC offset of the local time, which is reported by ADL.
    /// </summary>
    timestamp_type::value_type _utc_offset;
};

PWROWG_DETAIL_NAMESPACE_END

#include "adl_sensor.inl"

#endif /* defined(_PWROWG_ADL_SENSOR_H) */
