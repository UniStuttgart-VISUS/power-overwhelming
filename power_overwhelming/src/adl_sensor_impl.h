﻿// <copyright file="adl_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#pragma once

#include <atomic>
#include <functional>
#include <vector>

#include "power_overwhelming/adl_sensor_source.h"
#include "power_overwhelming/measurement.h"
#include "power_overwhelming/sampler_source.h"
#include "power_overwhelming/thermal_sample.h"
#include "power_overwhelming/throttling_sample.h"
#include "power_overwhelming/timestamp.h"

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
        /// Counts how many valid sensor readings are in <paramref name="data" />.
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        static std::size_t count_sensor_readings(const ADLPMLogData& data);

        /// <summary>
        /// Filter out the values we are interested in from the log data.
        /// </summary>
        /// <param name="voltage"></param>
        /// <param name="current"></param>
        /// <param name="power"></param>
        /// <param name="data"></param>
        /// <returns>The number of readings returned. If this is 1, only power
        /// has been set. If it is 2, voltage and current have been set.
        /// Otherwise, all values are set.</returns>
        static std::size_t filter_sensor_readings(unsigned int& voltage,
            unsigned int& current, unsigned int& power,
            const ADLPMLogData& data);

        /// <summary>
        /// Retrieve the value of the requested sensor ID if in the sensor data.
        /// </summary>
        /// <param name="value"></param>
        /// <param name="data"></param>
        /// <param name="id"></param>
        /// <returns></returns>
        static bool filter_sensor_readings(_Out_opt_ unsigned int& value,
            _In_ const ADLPMLogData& data, _In_ const ADL_PMLOG_SENSORS id);

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
        template<class TPredicate> static int find_if(const ADLPMLogData& data,
            const TPredicate& predicate);

        /// <summary>
        /// Gets the IDs of the hardware sensors associated with the specified
        /// source.
        /// </summary>
        /// <remarks>
        /// The sensors are ordered (if supported): voltage, current, power.
        /// </remarks>
        /// <param name="source">The source to be measured.</param>
        /// <returns>The IDs of the hardware sensors measuring the values at the
        /// source.</returns>
        static std::vector<ADL_PMLOG_SENSORS> get_sensor_ids(
            const adl_sensor_source source);

        /// <summary>
        /// Determine which sensors of the specified source are supported in the
        /// given <see cref="ADLPMLogSupportInfo" />.
        /// </summary>
        /// <param name="source"></param>
        /// <param name="supportInfo"></param>
        /// <returns>The intersection of the sensors supported according to
        /// <paramref name="supportInfo" /> and the sensors required for
        /// <paramref name="source" />.</returns>
        static std::vector<ADL_PMLOG_SENSORS> get_sensor_ids(
            const adl_sensor_source source,
            const ADLPMLogSupportInfo& supportInfo);

        /// <summary>
        /// Answer whether the given sensor ID refers to a current sensor.
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        static bool is_current(const ADL_PMLOG_SENSORS id);

        /// <summary>
        /// Answer whether the given sensor ID refers to a power sensor.
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        static bool is_power(const ADL_PMLOG_SENSORS id);

        /// <summary>
        /// Answer whether the given sensor ID refers to a voltage sensor.
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        static bool is_voltage(const ADL_PMLOG_SENSORS id);

        /// <summary>
        /// Answer the symbolic constant for the given sensor ID.
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        static std::wstring to_string(const ADL_PMLOG_SENSORS id);

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
        explicit adl_sensor_impl(const AdapterInfo& adapterInfo);

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
            std::vector<ADL_PMLOG_SENSORS>&& sensorIDs);

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
                _In_ ADLPMLogData& log_data) const noexcept {
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
        const ADLPMLogData& data, const TPredicate& predicate) {
    for (int i = 0; (i < ADL_PMLOG_MAX_SENSORS)
            && (data.ulValues[i][0] != ADL_SENSOR_MAXTYPES); ++i) {
        if (predicate(static_cast<ADL_PMLOG_SENSORS>(data.ulValues[i][0]))) {
            return i;
        }
    }

    return -1;
}
