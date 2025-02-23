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
        _In_ std::size_t index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config);

    /// <summary>
    /// Create a new instance for the specified adapter index.
    /// </summary>
    /// <param name="index">The adapter index to create the sensor for.
    /// </param>
    /// <param name="sources">The sensor sources to retrieve.</param>
    /// <param name="owner">The sensor array that owns the sensor, which is
    /// required to obtain the requested sampling rate.</param>
    /// <returns></returns>
    /// <exception cref="adl_exception">If the specified device was not
    /// found, or another error occurred in ADL.</exception>
    static inline std::shared_ptr<adl_sensor> from_index(
            _In_ const int index,
            _In_ const std::vector<ADL_PMLOG_SENSORS>& sources,
            _In_ const sensor_array_impl *owner) {
        // Note: We cannot use make_shared here, because it does not honour our
        // requirements for alignment.
        return std::shared_ptr<adl_sensor>(
            new adl_sensor(index, sources, owner));
    }

    /// <summary>
    /// Create a new instance for the unique device ID.
    /// </summary>
    /// <param name="udid">The unique device ID to create the sensor for.
    /// </param>
    /// <param name="sources">The sensor sources to retrieve.</param>
    /// <param name="owner">The sensor array that owns the sensor, which is
    /// required to obtain the requested sampling rate.</param>
    /// <returns></returns>
    /// <exception cref="std::invalid_argument">If <paramref name="udid" />
    /// is <c>nullptr</c> or if it did not match exactly one device.
    /// </exception>
    /// <exception cref="adl_exception">If the specified device was not
    /// found, or another error occurred in ADL.</exception>
    static std::shared_ptr<adl_sensor> from_udid(
        _In_z_ const char *udid,
        _In_ const std::vector<ADL_PMLOG_SENSORS>& sources,
        _In_ const sensor_array_impl *owner);

    /// <summary>
    /// Create a new instance for the unique device ID.
    /// </summary>
    /// <param name="udid">The unique device ID to create the sensor for.
    /// </param>
    /// <param name="sources">The sensor sources to retrieve.</param>
    /// <param name="owner">The sensor array that owns the sensor, which is
    /// required to obtain the requested sampling rate.</param>
    /// <returns></returns>
    /// <exception cref="std::invalid_argument">If <paramref name="udid" />
    /// is <c>nullptr</c> or if it did not match exactly one device.
    /// </exception>
    /// <exception cref="adl_exception">If the specified device was not
    /// found, or another error occurred in ADL.</exception>
    static inline std::shared_ptr<adl_sensor> from_udid(
            _In_z_ const wchar_t *udid,
            _In_ const std::vector<ADL_PMLOG_SENSORS>& sources,
            _In_ const sensor_array_impl *owner) {
        auto u = PWROWG_NAMESPACE::convert_string<char>(udid);
        return from_udid(u.c_str(), sources, owner);
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="adapter">The index of the adapter to create the sensor for.
    /// </param>
    /// <param name="sources">The sources to be sampled from the adapter.</param>
    /// <param name="owner">The sensor array that owns the sensor, which is
    /// required to obtain the requested sampling rate.</param>
    adl_sensor(_In_ const adapter_type adapter,
        _In_ const std::vector<ADL_PMLOG_SENSORS>& sources,
        _In_ const sensor_array_impl *owner);

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
    /// Specialises the description builder for the given type of sensor.
    /// </summary>
    static bool specialise(_In_ sensor_description_builder& builder,
        _In_ const AdapterInfo& info,
        _In_ const ADL_PMLOG_SENSORS sensor);

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
    /// The owner of this sensor.
    /// </summary>
    const sensor_array_impl *_owner;

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
    /// Remembers whether the sensor is running and sampling asynchronously
    /// to <see cref="start_output" />.
    /// </summary>
    sensor_state _state;

    /// <summary>
    /// The UTC offset of the local time, which is reported by ADL.
    /// </summary>
    timestamp::value_type _utc_offset;
};

PWROWG_DETAIL_NAMESPACE_END

#include "adl_sensor.inl"

#endif /* defined(_PWROWG_ADL_SENSOR_H) */


#if false
// <copyright file="adl_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#pragma once

#include <atomic>
#include <functional>
#include <vector>

#include "visus/pwrowg/adl_sensor_source.h"
#include "visus/pwrowg/measurement.h"
#include "visus/pwrowg/sampler_source.h"
#include "visus/pwrowg/thermal_sample.h"
#include "visus/pwrowg/throttling_sample.h"
#include "visus/pwrowg/timestamp.h"

#include "adl_scope.h"
#include "amd_display_library.h"
#include "sampler.h"
#include "timezone.h"


namespace visus {
    namespace power_overwhelming {
        namespace detail {

            /// <summary>
            /// Private data container for <see cref="adl_sensor" />.
            /// </summary>
            struct adl_sensor_impl final : public sampler_source {

                /// <summary>
                /// Find the index of the first sensor in <paramref name="data" />
                /// matching the given predicate.
                /// </summary>
                /// <typeparam name="TPredicate">The type of the predicate to be
                /// evaluated for each sensor reading. The predicate must accept an
                /// <see cref="ADL_PMLOG_SENSORS" /> enumeration member, which
                /// identifies the sensor, and must return a <c>bool</c> indicating
                /// whether the sensor matches.</typeparam>
                /// <param name="data"></param>
                /// <param name="predicate"></param>
                /// <returns>The index of the first sensor matching the given predicate,
                /// or -1 if no sensor matches the predicate.</returns>
                template<class TPredicate> static int find_if(const ADLPMLogData &data,
                    const TPredicate &predicate);

                /// <summary>
                /// The dedicated sampler for ADL sensors.
                /// </summary>
                /// <remarks>
                /// We need to hold a dedicated sampler for ADL as we want to stop the
                /// sensor if all samplers have been removed.
                /// </remarks>
                static power_overwhelming::detail::sampler sampler;

                /// <summary>
                /// Stores the asynchronous sampling configuration for the sensor.
                /// </summary>
                /// <remarks>
                /// We cannot inherit the implementation of the basic sampler source,
                /// because the ADL sensor must be able to 
                /// </remarks>
                power_overwhelming::async_sampling async_sampling;

                /// <summary>
                /// The adpater index of the device, which is required for a series of
                /// APIs.
                /// </summary>
                decltype(AdapterInfo::iAdapterIndex) adapter_index;

                /// <summary>
                /// The handle for the device the sensor is working on.
                /// </summary>
                ADL_D3DKMT_HANDLE device;

                /// <summary>
                /// The name of the device.
                /// </summary>
                std::wstring device_name;

                /// <summary>
                /// The ADL scope making sure the library is ready while the sensor
                /// exists.
                /// </summary>
                adl_scope scope;

                /// <summary>
                /// The sensor name.
                /// </summary>
                std::wstring sensor_name;

                /// <summary>
                /// The input for the sensor start function (selection of sensors to
                /// report).
                /// </summary>
                ADLPMLogStartInput start_input;

                /// <summary>
                /// The output of the sensor start function (valid only as long as the
                /// sensor is running).
                /// </summary>
                ADLPMLogStartOutput start_output;

                /// <summary>
                /// Remembers whether the sensor is running and sampling asynchronously
                /// to <see cref="start_output" />.
                /// </summary>
                /// <remarks>
                /// The following values are used here: zero, if the sensor is not
                /// running, one if it is running and two if it is in a transition
                /// state.
                /// </remarks>
                std::atomic<int> state;

                /// <summary>
                /// Remembers the type of the source.
                /// </summary>
                adl_sensor_source source;

                /// <summary>
                /// The unique device ID of the adapter the sensor is for.
                /// </summary>
                std::string udid;

                /// <summary>
                /// The UTC offset of the local time, which is reported by ADL.
                /// </summary>
                power_overwhelming::timestamp::value_type utc_offset;

                /// <summary>
                /// Initialises a new instance.
                /// </summary>
                adl_sensor_impl(void);

                /// <summary>
                /// Initialises a new instance.
                /// </summary>
                /// <param name="adapterInfo"></param>
                explicit adl_sensor_impl(const AdapterInfo &adapterInfo);

                /// <summary>
                /// Finalises the instance.
                /// </summary>
                ~adl_sensor_impl(void);

                /// <summary>
                /// Prepares <see cref="start_input" /> for the specified sensor source.
                /// </summary>
                /// <param name="source"></param>
                /// <param name="sensorIDs"></param>
                void configure_source(const adl_sensor_source source,
                    std::vector<ADL_PMLOG_SENSORS> &&sensorIDs);

                /// <summary>
                /// Prepares <see cref="start_input" /> for the specified sensor source.
                /// </summary>
                /// <param name="sensor_id"></param>
                void configure_source(_In_ const ADL_PMLOG_SENSORS sensor_id);

                /// <inheritdoc />
                bool deliver(void) const override;

                /// <inheritdoc />
                interval_type interval(void) const noexcept override;

                /// <summary>
                /// Checks whether <see cref="state" /> represents the running
                /// state (not stopped or transitional).
                /// </summary>
                /// <returns><c>true</c> if the sensor is marked running, <c>false</c>
                /// if it is stopped or in a transitional state.</returns>
                inline bool running(void) const {
                    return (this->state.load() == 1);
                }

                /// <summary>
                /// Obtain a single sample from the sensor.
                /// </summary>
                /// <remarks>
                /// <para>The sensor must be running in order to produce meaningful
                /// results. The implementation does not verify that, though, for
                /// performance reasons. Callers must make sure that this invariant
                /// is met.</para>
                /// <para>The method checks how the data in <see cref="start_output" />
                /// are best converted into an instance of <see cref="measurement" />
                /// (based on the sensor readings available) and creates the instance
                /// for the <see cref="sensor_name" />.</para>
                /// <para>Valid combinations of input data are: power measurements only,
                /// measurements of voltage and current and measurement of all of the
                /// sensors before. Any other combination will cause the method to
                /// fail.</para>
                /// <para>HAZARD: It is totally unclear to me how AMD achieves thread
                /// safety with that. The code is taken from their sample
                /// https://github.com/GPUOpen-LibrariesAndSDKs/display-library/blob/79cdb8e22b8650c861b390d5a9895032492ce8c5/Sample/PMLog/PMLog.cpp
                /// which is completely unprotected against races IMHO.</para>
                /// </remarks>
                /// <returns>The current measurement from the sensor.</returns>
                measurement_data sample(void) const;

                /// <summary>
                /// Samples the first sensor in <see cref="start_input" /> as thermal
                /// sensor.
                /// </summary>
                /// <returns>The latest thermal reading of the sensor.</returns>
                thermal_sample sample_thermal(void) const;

                /// <summary>
                /// Samples the first sensor in <see cref="start_input" /> as throttling
                ///  state of the GPU.
                /// </summary>
                /// <returns>The latest throttling state of the sensor.</returns>
                throttling_sample sample_throttling(void) const;

                /// <summary>
                /// Starts the source if not yet running.
                /// </summary>
                /// <param name="samplingRate">The sampling rate at which the sensor
                /// should update.</param>
                /// <exception cref="std::runtime_error">If the method is called when
                /// <see cref="is_sampling" /> is already <c>true</c>.</exception>
                /// <exception cref="adl_exception">If the source could not be
                /// started.</exception>
                void start(const unsigned long samplingRate);

                /// <summary>
                /// Stops the source if <see cref="state" /> is <c>1</c>.
                /// </summary>
                void stop(void);

                /// <summary>
                /// Gets the timestamp from <see cref="log_data" />.
                /// </summary>
                /// <param name="log_data">The log data to get the timestamp from.
                /// </param>
                /// <returns>The latest update timestamp from the sensor.</returns>
                inline measurement_data::timestamp_type timestamp(
                    _In_ ADLPMLogData &log_data) const noexcept {
                    // We found empirically that the timestamp from ADL is in 100 ns
                    // units (at least on Windows). Based on this assumption, convert
                    // to the requested unit.
                    const auto timestamp = static_cast<measurement::timestamp_type>(
                        log_data.ulLastUpdated + this->utc_offset);
                    return power_overwhelming::timestamp(timestamp);
                }
            };

        } /* namespace detail */
    } /* namespace power_overwhelming */
} /* namespace visus */


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::find_if
 */
template<class TPredicate>
int visus::power_overwhelming::detail::adl_sensor_impl::find_if(
    const ADLPMLogData &data, const TPredicate &predicate) {
    for (int i = 0; (i < ADL_PMLOG_MAX_SENSORS)
        && (data.ulValues[i][0] != ADL_SENSOR_MAXTYPES); ++i) {
        if (predicate(static_cast<ADL_PMLOG_SENSORS>(data.ulValues[i][0]))) {
            return i;
        }
    }

    return -1;
}

#endif