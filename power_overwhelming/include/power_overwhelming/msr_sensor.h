// <copyright file="msr_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <ios>

#include "power_overwhelming/rapl_domain.h"
#include "power_overwhelming/rapl_quantity.h"
#include "power_overwhelming/sensor.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations */
    namespace detail { struct msr_sensor_impl; }
    namespace detail { template<class T> struct sensor_desc; }


    /// <summary>
    /// Implementation of a power sensor using the device files for the RAPL
    /// machine-specific registers (MSRs).
    /// </summary>
    class POWER_OVERWHELMING_API msr_sensor final : public sensor {

    public:

        /// <summary>
        /// The type of the raw samples read from the registers.
        /// </summary>
        typedef std::uint64_t raw_sample_type;

        /// <summary>
        /// The type used to index CPU cores.
        /// </summary>
        typedef std::uint32_t core_type;

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
        /// Create sensors for all MSR files.
        /// </summary>
        /// <param name="out_sensors">Receives the sensors, if not
        /// <c>nullptr</c>.</param>
        /// <param name="cnt_sensors">The available space in
        /// <paramref name="out_sensors" />.</param>
        /// <param name="reserved">Reserved for future use. Must be
        /// <c>false</c>.</param>
        /// <returns>The number of sensors available on the system, regardless
        /// of the size of the output array. If this number is larger than
        /// <paramref name="cntSensors" />, not all sensors have been returned.
        /// </returns>
        /// <exception cref="std::system_error">If enumerating or opening the
        /// devices failed.</exception>
        static std::size_t for_all(
            _Out_writes_opt_(cnt_sensors) msr_sensor *out_sensors,
            _In_ const std::size_t cnt_sensors,
            _In_ const bool reserved = false);

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

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        msr_sensor(void);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline msr_sensor(_In_ msr_sensor&& rhs) noexcept : _impl(rhs._impl) {
            rhs._impl = nullptr;
        }

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        virtual ~msr_sensor(void);

        /// <summary>
        /// Answer the core the sensor is sampling.
        /// </summary>
        /// <returns>The index ofo the core the sensor is sampling.</returns>
        /// <exception cref="std::runtime_error">If the method is called on a
        /// sensor that has been disposed.</exception>
        core_type core(void) const;

        /// <summary>
        /// Answer the RAPL domain the sensor is sampling.
        /// </summary>
        /// <returns>The RAPL domain the sensor is sampling.</returns>
        /// <exception cref="std::runtime_error">If the method is called on a
        /// sensor that has been disposed.</exception>
        rapl_domain domain(void) const;

        /// <summary>
        /// Reads the raw sensor data and applies the unit transformation such
        /// that the return value is in Joules (accumulated since an undefined
        /// start point).
        /// </summary>
        /// <returns>The current value of the counter in Joules.</returns>
        raw_sample_type read(void) const;

        /// <inheritdoc />
        virtual _Ret_maybenull_z_ const wchar_t *name(
            void) const noexcept override;

        using sensor::sample;

        /// <summary>
        /// Asynchronously sample the sensor every
        /// <paramref name="sampling_period "/> microseconds.
        /// </summary>
        /// <param name="on_measurement">The callback to be invoked if new data
        /// arrived. If this is <c>nullptr</c>, the asynchronous sampling will
        /// be disabled.</param>
        /// <param name="period">The desired sampling period in
        /// microseconds. This parameter defaults to 1 millisecond.</param>
        /// <param name="timestamp_resolution">The resolution of the timestamps
        /// that are generated by the sensor. This parameter defaults to
        /// <see cref="timestamp_resolution::milliseconds" />.</param>
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
            _In_ const timestamp_resolution timestamp_resolution
                = timestamp_resolution::milliseconds,
            _In_opt_ void *context = nullptr);

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        msr_sensor& operator =(_In_ msr_sensor&& rhs) noexcept;

        /// <inheritdoc />
        virtual operator bool(void) const noexcept override;

    protected:

        /// <inheritdoc />
        measurement_data sample_sync(
            _In_ const timestamp_resolution resolution) const override;

    private:

        detail::msr_sensor_impl *_impl;

        friend struct detail::msr_sensor_impl;
        template<class T> friend struct detail::sensor_desc;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
