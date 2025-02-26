// <copyright file="msr_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_MSR_SENSOR_H)
#define _PWROWG_MSR_SENSOR_H
#pragma once

#include <ios>
#include <list>
#include <utility>
#include <vector>

#include "visus/pwrowg/msr_configuration.h"
#include "visus/pwrowg/rapl_domain.h"
#include "visus/pwrowg/rapl_quantity.h"
#include "visus/pwrowg/sample.h"
#include "visus/pwrowg/sensor_array_callback.h"
#include "visus/pwrowg/sensor_description.h"
#include "visus/pwrowg/sensor_filters.h"
#include "visus/pwrowg/timestamp.h"

#include "msr_device.h"
#include "sensor_utilities.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Implementation of a power sensor using the device files for the RAPL
/// machine-specific registers (MSRs).
/// </summary>
class PWROWG_TEST_API msr_sensor final {

public:

    /// <summary>
    /// Identification of an MSRs and its unit divisor.
    /// </summary>
    struct register_identifier final {

        /// <summary>
        /// The divisor to convert the register value into the actual value.
        /// </summary>
        float divisor;

        /// <summary>
        /// The offset of the register.
        /// </summary>
        std::streamoff offset;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="offset">The offset of the register.</param>
        /// <param name="divisor"> The divisor to convert the register value
        /// into the actual value.</param>
        inline register_identifier(_In_ const std::streamoff offset,
                _In_ const float divisor = 1.0f)
            : divisor(divisor), offset(offset) { }
    };

    /// <summary>
    /// The type of sensor class configuration used by this sensor.
    /// </summary>
    typedef msr_configuration configuration_type;

    /// <summary>
    /// The type used to index CPU cores.
    /// </summary>
    typedef msr_device::core_type core_type;

    /// <summary>
    /// The type of a list of sensors of this type.
    /// </summary>
    typedef std::list<msr_sensor> list_type;

    /// <summary>
    /// The type of the raw samples read from the registers.
    /// </summary>
    typedef msr_device::sample_type raw_sample_type;

    /// <summary>
    /// Create descriptions for all supported MSR sensors in the system.
    /// </summary>
    /// <remarks>
    /// <para>It is safe to call this method on systems that do not support
    /// reading RAPL MSRs. No descriptions are returned in this case.
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

#if false
    /// <summary>
    /// Creates a new sensor for the specified core and RAPL domain,
    /// forcing the specified <see cref="offset" /> for the location of the
    /// energy sample in the MSR device file.
    /// </summary>
    /// <remarks>
    /// <para>This factory method exists due to the fact that the whole RAPL
    /// stuff is poorly documented and the implementation is copied from
    /// all over the internet. Furthermore, there is no centralised
    /// implementation for that stuff in Linux we can rely on to be up to
    /// date. Therefore, this method provides the opportunity for callers
    /// who know that a specific CPU supports a specific RAPL domain at a
    /// specific offset in the MSR device file to force the creation of the
    /// sensor, bypassing all built-in sanity checks based on the
    /// aforementioned sketchy information.</para>
    /// </remarks>
    /// <param name="core">The index of the CPU core for which the MSR
    /// sensor should be opened.</param>
    /// <param name="domain">The RAPL domain that is being sampled by the
    /// sensor. This information is only used for creating the sensor name,
    /// but has no effect on the actual data that are being read by the
    /// sensor.</param>
    /// <param name="data_location">The offset into the MSR device file
    /// where the samlpes are read from.</param>
    /// <returns>A new instance of the MSR sensor for the specified
    /// configuration.</returns>
    /// <exception cref="std::system_error">If the MSR device file could not
    /// be opened.</exception>
    static msr_sensor force_create(_In_ const core_type core,
        _In_ const rapl_domain domain,
        _In_ const std::streamoff data_location,
        _In_ const std::streamoff unit_location,
        _In_ const std::uint64_t unit_mask,
        _In_ const std::uint32_t unit_offset);

    /// <summary>
    /// Create an MSR sensor for the specified core and RAPL domain.
    /// </summary>
    /// <param name="core">The index of the CPU core for which the MSR
    /// sensor should be opened.</param>
    /// <param name="domain">The RAPL domain that is being sampled.</param>
    /// <returns></returns>
    /// <exception cref="runtime_error">If the CPU vendor could not be
    /// determined to find the RAPL offset.</exception>
    /// <exception cref="std::invalid_argument">If the RAPL domain is not
    /// supported for the specified CPU core.</exception>
    /// <exception cref="std::system_error">If the MSR device file could not
    /// be opened.</exception>
    static msr_sensor for_core(_In_ const core_type core,
        _In_ const rapl_domain domain);
#endif

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
    /// <param name="path"></param>
    /// <param name="registers"></param>
    /// <param name="index"></param>
    msr_sensor(_In_z_ const wchar_t *path,
        _Inout_ std::vector<register_identifier>&& registers,
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

private:

    /// <summary>
    /// The character type used for device paths.
    /// </summary>
    typedef msr_device::string_type::value_type path_char_type;

    msr_device _device;
    PWROWG_NAMESPACE::sample::source_type _index;
    std::vector<timestamp> _last_timestamp;
    std::vector<float> _last_value;
    std::vector<register_identifier> _registers;
};

PWROWG_DETAIL_NAMESPACE_END

#include "msr_sensor.inl"

#endif /* defined(_PWROWG_MSR_SENSOR_H) */
