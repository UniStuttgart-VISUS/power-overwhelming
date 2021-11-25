// <copyright file="adl_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <vector>

#include "amd_display_library.h"
#include "adl_scope.h"
#include "adl_sensor_source.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Private data container for <see cref="adl_sensor" />.
    /// </summary>
    struct adl_sensor_impl final {

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
        static std::vector<int> get_sensor_ids(const adl_sensor_source source);

        /// <summary>
        /// Determine which sensors of the specified source are supported in the
        /// given <see cref="ADLPMLogSupportInfo" />.
        /// </summary>
        /// <param name="source"></param>
        /// <param name="supportInfo"></param>
        /// <returns>The intersection of the sensors supported according to
        /// <paramref name="supportInfo" /> and the sensors required for
        /// <paramref name="source" />.</returns>
        static std::vector<int> get_sensor_ids(const adl_sensor_source source,
            const ADLPMLogSupportInfo& supportInfo);

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
            std::vector<int>&& sensorIDs);
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
