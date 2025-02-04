// <copyright file="adl_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_ADL_SENSOR_H)
#define _PWROWG_ADL_SENSOR_H
#pragma once

#include <vector>

#include "visus/pwrowg/adl_configuration.h"
#include "visus/pwrowg/sensor_description.h"

#include "adl_scope.h"
#include "adl_sensor_source.h"
#include "sensor.h"
#include "timezone.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A sensor drawing its information from the AMD display library (ADL).
/// </summary>
/// <remarks>
/// <para>Implementation note: There will always be one ADL sensor per AMD
/// device in a sensor array which samples all ADL data. The reason for that is
/// that ADL returns everything in one batch from the device.</para>
/// </remarks>
class adl_sensor final : public sensor {

public:

    /// <summary>
    /// The type of sensor class configuration used by this sensor.
    /// </summary>
    typedef adl_configuration configuration_type;

    /// <summary>
    /// Create descriptions for all supported AMD sensors in the system.
    /// </summary>
    /// <remarks>
    /// <para>It is safe to call this method on systems without AMD GPU.
    /// No descriptions are returned in this case.</para>
    /// </remarks>
    /// <returns>A list of sensor descriptors that can be used to instantiate a
    /// specific sensor.</returns>
    static std::vector<sensor_description> descriptions(void);

#if false
    ///// <summary>
    ///// Create a new instance for the specified adapter index.
    ///// </summary>
    ///// <param name="index">The adapter index to create the sensor for.
    ///// </param>
    ///// <param name="source">The sensor source to retrieve. If the source
    ///// is not supported, the method will fail.</param>
    ///// <returns></returns>
    ///// <exception cref="adl_exception">If the specified device was not
    ///// found, or another error occurred in ADL.</exception>
    //static adl_sensor from_index(_In_ const int index,
    //    _In_ const adl_sensor_source source);

    ///// <summary>
    ///// Create a new instance for the unique device ID.
    ///// </summary>
    ///// <param name="udid">The unique device ID to create the sensor for.
    ///// </param>
    ///// <param name="source">The sensor source to retrieve. If the source
    ///// is not supported, the method will fail.</param>
    ///// <returns></returns>
    ///// <exception cref="std::invalid_argument">If <paramref name="udid" />
    ///// is <c>nullptr</c> or if it did not match exactly one device.
    ///// </exception>
    ///// <exception cref="adl_exception">If the specified device was not
    ///// found, or another error occurred in ADL.</exception>
    //static adl_sensor from_udid(_In_z_ const char *udid,
    //    _In_ const adl_sensor_source source);

    ///// <summary>
    ///// Create a new instance for the unique device ID.
    ///// </summary>
    ///// <param name="udid">The unique device ID to create the sensor for.
    ///// </param>
    ///// <param name="source">The sensor source to retrieve. If the source
    ///// is not supported, the method will fail.</param>
    ///// <returns></returns>
    ///// <exception cref="std::invalid_argument">If <paramref name="udid" />
    ///// is <c>nullptr</c> or if it did not match exactly one device.
    ///// </exception>
    ///// <exception cref="adl_exception">If the specified device was not
    ///// found, or another error occurred in ADL.</exception>
    //static adl_sensor from_udid(_In_z_ const wchar_t *udid,
    //    _In_ const adl_sensor_source source);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <exception cref="std::bad_alloc">If the memory for the sensor state
    /// could not be allocated.</exception>
    /// <exception cref="std::system_error">If the ADL could not be loaded.
    /// </exception>
    /// <exception cref="adl_exception">If the ADL could not be initialised.
    /// </exception>
    adl_sensor(void);

    /// <summary>
    /// Move <paramref name="rhs" /> into a new instance.
    /// </summary>
    /// <param name="rhs"></param>
    /// <returns></returns>
    inline adl_sensor(_In_ adl_sensor&& rhs) noexcept : _impl(rhs._impl) {
        rhs._impl = nullptr;
    }

    /// <summary>
    /// Initialise a new instance from a status block.
    /// </summary>
    /// <remarks>
    /// This constructor is intended for internal use only.
    /// </remarks>
    /// <param name="impl">The status block, which must have been allocated
    /// using <c>new</c>. The object takes ownership of the status block.
    /// </param>
    inline explicit adl_sensor(
            _In_ detail::adl_sensor_impl *&& impl) noexcept
            : _impl(impl) {
        impl = nullptr;
    }

    /// <summary>
    /// Finalise the instance.
    /// </summary>
    virtual ~adl_sensor(void);

    /// <summary>
    /// Gets the name of the sensor.
    /// </summary>
    /// <returns>The implementation-defined, human-readable name of the
    /// sensor.</returns>
    virtual _Ret_maybenull_z_ const wchar_t *name(
        void) const noexcept override;

    /// <summary>
    /// Asynchronously sample the sensor every
    /// <paramref name="sampling_period "/> microseconds.
    /// </summary>
    /// <remarks>
    /// <para>This method <see cref="start" />s the sensor and regularly
    /// queries it on a background thread.</para>
    /// <para>If you have multiple sensors running asynchronously, it is
    /// recommended to use the same <paramref name="sampling_period" /> as
    /// the implementation can use the same background thread in this
    /// case.</para>
    /// </remarks>
    /// <param name="on_measurement">The callback to be invoked if new data
    /// arrived. If this is <c>nullptr</c>, the asynchronous sampling will
    /// be disabled.</param>
    /// <param name="period">The desired sampling period in
    /// microseconds. This parameter defaults to 1 millisecond.</param>
    /// <param name="context">A user-defined context pointer that is passed
    /// on to <see cref="on_measurement" />. This parameter defaults to
    /// <c>nullptr</c>.</para>
    /// <exception cref="std::runtime_error">If the sensor has been moved.
    /// </exception>
    /// <exception cref="std::logic_error">If the sensor is already being
    /// sampled asynchronously due to a previous call to the method.
    /// </exception>
    /// <exception cref="tinkerforge_exception">If the sensor could not be
    /// sampled. </exception>
    void sample(_In_opt_ const measurement_callback on_measurement,
        _In_ const microseconds_type period = default_sampling_period,
        _In_opt_ void *context = nullptr);

    using sensor::sample;

    /// <summary>
    /// Starts the sensor asynchronously collecting data.
    /// </summary>
    /// <remarks>
    /// <para>This method is for expert use only. It puts the sensor into
    /// sampling state, but does not deliver the data to any callback.
    /// Instead, callers are expected to retrieve data using the
    /// synchronous <see cref="sample" /> method in a separate thread.
    /// Note that putting the sensor in sampling state this way will prevent
    /// the asynchronous <see cref="sample" /> method from working. You
    /// should therefore either use either of the methods and never mix
    /// them.</para>
    /// </remarks>
    /// <param name="sampling_period">The desired sampling period in
    /// microseconds.</param>
    /// <exception cref="std::runtime_error">If the method is called when
    /// the sensor is already asynchronously collecting data.</exception>
    /// <exception cref="adl_exception">If the source could not be
    /// started.</exception>
    void start(_In_ const microseconds_type sampling_period);

    /// <summary>
    /// Stops the sensor from asynchronously collecting data.
    /// </summary>
    /// <remarks>
    /// <para>The method is for expert use only. If you call it while the
    /// asynchronous <see cref="sample" /> method is running, asynchronous
    /// sampling will be stopped as well.</para>
    /// <para>It is safe to call this method on a sensor that is not
    /// sampling asynchronously or that has been disposed by a move
    /// operation.</para>
    /// </remarks>
    void stop(void);

    /// <summary>
    /// Gets the type of the sensor source.
    /// </summary>
    /// <returns>The sensor source.</returns>
    adl_sensor_source source(void) const;

    /// <summary>
    /// Answer the unique device ID of the adapter the sensor is for.
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    _Ret_maybenull_z_ const char *udid(void) const noexcept;
#endif

    adl_sensor& operator =(const adl_sensor&) = delete;

private:

    /// <summary>
    /// The adpater index of the device, which is required for a series of
    /// APIs.
    /// </summary>
    decltype(AdapterInfo::iAdapterIndex) _adapter_index;

    /// <summary>
    /// The handle for the device the sensor is working on.
    /// </summary>
    ADL_D3DKMT_HANDLE _device;

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
    std::atomic<sensor_state> _state;

    /// <summary>
    /// The UTC offset of the local time, which is reported by ADL.
    /// </summary>
    timestamp::value_type _utc_offset;
};

PWROWG_DETAIL_NAMESPACE_END

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