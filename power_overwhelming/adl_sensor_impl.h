// <copyright file="adl_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <functional>
#include <vector>

#include "amd_display_library.h"
#include "adl_scope.h"
#include "adl_sensor_source.h"
#include "measurement.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Private data container for <see cref="adl_sensor" />.
    /// </summary>
    struct adl_sensor_impl final {

        /// <summary>
        /// Counts how many valid sensor readings are in <paramref name="data" />.
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        static std::size_t count_sensor_readings(const ADLPMLogData& data);

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
        /// <param name="sampleRate"></param>
        void configure_source(const adl_sensor_source source,
            std::vector<ADL_PMLOG_SENSORS>&& sensorIDs);

        /// <summary>
        /// Convert the given log data to an instance of
        /// <see cref="measurement" />.
        /// </summary>
        /// <remarks>
        /// <para>The method checks how the given data are best converted into
        /// an instance of <see cref="measurement" /> (based on the sensor
        /// readings available) and creates the instance for the
        /// <see cref="sensor_name" /> configured in the object.</para>
        /// <para>Valid combinations of input data are: power measurements only,
        /// measurements of voltage and current and measurement of all of the
        /// sensors before. Any other combination will cause the method to
        /// fail.</para>
        /// </remarks>
        /// <param name="data">The sensor readings obtained from ADL.</param>
        /// <returns>A measurement object containing the normalised data from
        /// the sensor readings.</returns>
        /// <exception cref="std::logic_error">In case the given data do not
        /// contain the required sensor readings.</exception>
        measurement to_measurement(const ADLPMLogData& data,
            const timestamp_resolution resolution);
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
