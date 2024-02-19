// <copyright file="adl_thermal_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/thermal_sensor.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations */
    namespace detail { struct adl_sensor_impl; }

    /// <summary>
    /// Defines a sensor for obtaining the temperature of an AMD GPU.
    /// </summary>
    class POWER_OVERWHELMING_API adl_thermal_sensor final
            : public thermal_sensor {

    public:

        /// <summary>
        /// Create sensors for all supported AMD cards in the system.
        /// </summary>
        /// <remarks>
        /// <para>It is safe to call this method on systems without AMD GPU.
        /// Zero is returned in this case.</para>
        /// </remarks>
        /// <param name="dst">Receives the sensors, if not <c>nullptr</c>. It
        /// is safe to pass <c>nullptr</c> to count the sensors.</param>
        /// <param name="cnt">The available space in <paramref name="dst" />.
        /// </param>
        /// <returns>The number of sensors available on the system, regardless
        /// of the size of the output array. If this number is larger than
        /// <paramref name="cnt" />, not all sensors have been returned.
        /// </returns>
        static std::size_t for_all(
            _Out_writes_opt_(cnt) adl_thermal_sensor *dst,
            _In_ const std::size_t cnt);

        /// <summary>
        /// Create a new instance for the unique device ID.
        /// </summary>
        /// <remarks>
        /// <para>It is safe to call this method on systems without AMD GPU.
        /// Zero is returned in this case.</para>
        /// </remarks>
        /// <param name="dst">Receives the sensors, if not <c>nullptr</c>. It
        /// is safe to pass <c>nullptr</c> to count the sensors.</param>
        /// <param name="cnt">The available space in <paramref name="dst" />.
        /// </param>
        /// <param name="udid">The unique device ID to create the sensor for.
        /// </param>
        /// <returns>The number of sensors available on the system, regardless
        /// of the size of the output array. If this number is larger than
        /// <paramref name="cnt" />, not all sensors have been returned.
        /// </returns>
        static std::size_t for_udid(
            _Out_writes_opt_(cnt) adl_thermal_sensor *dst,
            _In_ const std::size_t cnt,
            _In_z_ const char *udid);

        /// <summary>
        /// Create a new instance for the unique device ID.
        /// </summary>
        /// <remarks>
        /// <para>It is safe to call this method on systems without AMD GPU.
        /// Zero is returned in this case.</para>
        /// </remarks>
        /// <param name="dst">Receives the sensors, if not <c>nullptr</c>. It
        /// is safe to pass <c>nullptr</c> to count the sensors.</param>
        /// <param name="cnt">The available space in <paramref name="dst" />.
        /// </param>
        /// <param name="udid">The unique device ID to create the sensor for.
        /// </param>
        /// <returns>The number of sensors available on the system, regardless
        /// of the size of the output array. If this number is larger than
        /// <paramref name="cnt" />, not all sensors have been returned.
        /// </returns>
        static std::size_t for_udid(
            _Out_writes_opt_(cnt) adl_thermal_sensor *dst,
            _In_ const std::size_t cnt,
            _In_z_ const wchar_t *udid);

        /// <summary>
        /// Initialises a new, but invalid, instance.
        /// </summary>
        adl_thermal_sensor(void) noexcept;

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs"></param>
        /// <returns></returns>
        inline adl_thermal_sensor(
                _Inout_ adl_thermal_sensor&& rhs) noexcept
                : _impl(rhs._impl) {
            rhs._impl = nullptr;
        }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        virtual ~adl_thermal_sensor(void);

        /// <inheritdoc />
        temperature_metering_point metering_point(void) const noexcept override;

        /// <inheritdoc />
        _Ret_maybenull_z_ const wchar_t *name(void) const noexcept override;

        /// <inheritdoc />
        void sample(_Inout_ async_sampling&& async_sampling) override;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        adl_thermal_sensor& operator =(
            _Inout_ adl_thermal_sensor&& rhs) noexcept;

        /// <inheritdoc />
        operator bool(void) const noexcept override;

    private:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="impl"></param>
        explicit adl_thermal_sensor(
            _In_ detail::adl_sensor_impl *impl) noexcept;

        detail::adl_sensor_impl *_impl;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
