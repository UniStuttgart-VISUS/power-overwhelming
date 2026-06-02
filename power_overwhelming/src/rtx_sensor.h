// <copyright file="rtx_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <list>
#include <string>
#include <thread>
#include <vector>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/rtx_configuration.h"
#include "visus/pwrowg/sensor_filters.h"
#include "visus/pwrowg/string_functions.h"
#include "visus/pwrowg/thread_name.h"
#include "visus/pwrowg/trace.h"

#include "rtx_sensor_trigger_impl.h"
#include "sensor_description_builder.h"
#include "sensor_utilities.h"
#include "sensor_state.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A sensor using a Rohde &amp; Schwarz RTA and RTB series oscilloscope. This
/// sensor class manages all sensors defined on all oscilloscopes attached to
/// the machine.
/// </summary>
class PWROWG_TEST_API rtx_sensor final {

public:

    /// <summary>
    /// The type of sensor class configuration used by this sensor.
    /// </summary>
    typedef rtx_configuration configuration_type;

    /// <summary>
    /// The type of a list of sensors of this type.
    /// </summary>
    typedef std::list<rtx_sensor> list_type;

    /// <summary>
    /// Create descriptions for all RTX-based sensors in the system.
    /// </summary>
    /// <remarks>
    /// <para>It is safe to call this method on systems without a connection to a
    /// Rohde & Schwarz RTA or RTB series oscilloscope. No descriptions are
    /// returned in this case.</para>
    /// <para>The number of sensors returned is affected by the
    /// <see cref="rtx_configuration" /> used by the sensor array. Only sensors
    /// configured there will be returned if the device used in the sensor
    /// description matches the path to any of the devices attached to the
    /// machine.</para>
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
    /// Initialises a new instance.
    /// </summary>
    /// <typeparam name="TIterator">An iterator over
    /// <see cref="sensor_description" />s.</typeparam>
    /// <param name="begin">The begin of the range of sensor descriptions for
    /// RTX sensors.</param>
    /// <param name="end">The end of the range of sensor descriptions for
    /// RTX sensors.</param>
    /// <param name="index">The index for the sensor described by the
    /// <paramref name="begin" /> iterator.</param>
    /// <param name="owner">The sensor array owning the sensors to be created.
    /// </param>
    /// <param name="config">The configuration for the sensor class, obtained
    /// from the <paramref name="owner" />.</param>
    template<class TIterator>
    rtx_sensor(_In_ const TIterator begin,
        _In_ const TIterator end,
        _In_ std::size_t index,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config);

    rtx_sensor(const rtx_sensor&) = delete;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    inline ~rtx_sensor(void) noexcept {
        this->sample(false);
    }

    /// <summary>
    /// Starts or stops sampling the sensor.
    /// </summary>
    /// <param name="enable"><c>true</c> for enabling the sensor,
    /// <c>false</c> for disabling it.</param>
    void sample(_In_ const bool enable);

    rtx_sensor& operator =(const rtx_sensor&) = delete;

private:

    /// <summary>
    /// The instrument controller thread that serialises all communication with
    /// the oscilloscopes. This thread will check the
    /// <see="rtx_sensor_trigger_impl::status" /> of <see cref="_trigger" /> and
    /// perform the necessary operations to get data from the instruments to fulfil
    /// the trigger requests.
    /// </summary>
    void control_instruments(void);

    std::vector<std::string> _channels;
    std::size_t _index;
    const sensor_array_impl *_owner;
    std::thread _thread;
    rtx_sensor_trigger _trigger;
};

#include "rtx_sensor.inl"

PWROWG_DETAIL_NAMESPACE_END
