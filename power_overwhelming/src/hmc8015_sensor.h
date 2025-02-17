// <copyright file="hmc8015_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_HMC8015_SENSOR_H)
#define _PWROWG_HMC8015_SENSOR_H
#pragma once

#include <cassert>
#include <list>
#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "visus/pwrowg/hmc8015_configuration.h"
#include "visus/pwrowg/hmc8015_instrument.h"
#include "visus/pwrowg/sensor_array_callback.h"
#include "visus/pwrowg/sensor_description.h"
#include "visus/pwrowg/sensor_filters.h"

#include "sensor_description_builder.h"
#include "sensor_state.h"
#include "sensor_utilities.h"
#include "visa_exception.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Implementation of a power sensor using the NVIDIA management library to
/// read the internal sensors of the GPU.
/// </summary>
class PWROWG_TEST_API hmc8015_sensor final {

public:

    /// <summary>
    /// The type of sensor class configuration used by this sensor.
    /// </summary>
    typedef hmc8015_configuration configuration_type;

    /// <summary>
    /// The type of a list of sensors of this type.
    /// </summary>
    typedef std::list<hmc8015_sensor> list_type;

    /// <summary>
    /// Create descriptions for all supported Rohde &amp; Schwarz HMC 8015
    /// sensors in the system.
    /// </summary>
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

#if defined(POWER_OVERWHELMING_WITH_VISA)
    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="instrument"></param>
    /// <param name="owner"></param>
    /// <param name="index"></param>
    /// <parma name="functions"></param>
    hmc8015_sensor(_Inout_ hmc8015_instrument&& instrument,
        _In_ const sensor_array_impl *owner,
        _In_ const std::size_t index,
        _Inout_ std::vector<hmc8015_function>&& functions);
#else /* defined(POWER_OVERWHELMING_WITH_VISA) */
    hmc8015_sensor(void) = delete;
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

    hmc8015_sensor(const hmc8015_sensor& rhs) = delete;

    /// <summary>
    /// Starts or stops sampling the sensor.
    /// </summary>
    /// <param name="enable"><c>true</c> for enabling the sensor,
    /// <c>false</c> for disabling it.</param>
    void sample(_In_ const bool enable);

    hmc8015_sensor& operator =(const hmc8015_sensor& rhs) = delete;

private:

    /// <summary>
    /// Configure what the sensor readings are based on the given
    /// <paramref name="function" /> and return whether the provided
    /// function is supported or not.
    /// </summary>
    static bool specialise(_In_ sensor_description_builder& builder,
        _In_ const hmc8015_function function);

    /// <summary>
    /// A regular expression that is used to patch the name of the log file
    /// the HMC reports for downloading it.
    /// </summary>
    static const std::regex rx_log_patch;

    /// <summary>
    /// Provides access to the sensor configuration via the owner pointer.
    /// </summary>
    const configuration_type& configuration(void) const noexcept;

    std::vector<hmc8015_function> _functions;
    std::size_t _index;
#if defined(POWER_OVERWHELMING_WITH_VISA)
    hmc8015_instrument _instrument;
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
    const sensor_array_impl *_owner;
    sensor_state _state;
};

PWROWG_DETAIL_NAMESPACE_END

#include "hmc8015_sensor.inl"

#endif /* defined(_PWROWG_HMC8015_SENSOR_H) */
