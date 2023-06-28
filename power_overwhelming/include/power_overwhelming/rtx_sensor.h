// <copyright file="rtx_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <climits>
#include <cstddef>
#include <cstdint>
#include <cinttypes>

#include "power_overwhelming/oscilloscope_edge_trigger.h"
#include "power_overwhelming/oscilloscope_reference_point.h"
#include "power_overwhelming/oscilloscope_sensor_definition.h"
#include "power_overwhelming/visa_sensor.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations */
    namespace detail { struct visa_sensor_impl; }

    /// <summary>
    /// A sensor using a Rohde &amp; Schwarz RTA and RTB series oscilloscope.
    /// </summary>
    class POWER_OVERWHELMING_API rtx_sensor final : public detail::visa_sensor {

    public:

        /// <summary>
        /// Create sensor objects for all Rohde &amp; Schwarz RTA/RTB
        /// instruments that can be enumerated via VISA.
        /// </summary>
        /// <param name="out_sensors">An array receiving the sensors. If this is
        /// <c>nullptr</c>, nothing is returned.</param>
        /// <param name="cnt_sensors">The number of sensors that can be stored in
        /// <paramref name="out_sensors" />.</param>
        /// <param name="timeout">The timeout in milliseconds for establishing a
        /// connection to each instrument that was found. This parameter defaults
        /// to 3000.</param>
        /// <returns>The number of RTA/RTB instruments found, regardless of how
        /// many have been returned to <paramref name="out_sensors" />.</returns>
        static std::size_t for_all(
            _Out_writes_opt_(cnt_sensors) rtx_sensor *out_sensors,
            _In_ std::size_t cnt_sensors,
            _In_ const std::int32_t timeout = 3000);

        /// <summary>
        /// The product ID of the RTA and RTB series oscilloscopes.
        /// </summary>
        /// <remarks>
        /// This is the ID reported by the RTB2004 and RTA4004 devices we use at
        /// VISUS. If this does not work, use the RsVisaTester tool and discover
        /// the device via the &quot;Find Resource&quot; functionality. Do not
        /// forget to put the device in USB mode if discovering via USB.
        /// </remarks>
        static constexpr const char *rtb2004_id = "0x01D6";

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline rtx_sensor(void) { }

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="path"></param>
        /// <param name="timeout"></param>
        /// <exception cref="std::invalid_argument">If <paramref name="path" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="std::bad_alloc">If the memory for the sensor state
        /// could not be allocated.</exception>
        /// <exception cref="std::system_error">If the VISA library could not be
        /// loaded.</exception>
        /// <exception cref="visa_exception">If the sensor could not be
        /// initialised.</exception>
        rtx_sensor(_In_z_ const char *path, _In_ const std::int32_t timeout);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="path"></param>
        /// <param name="timeout"></param>
        /// <exception cref="std::invalid_argument">If <paramref name="path" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="std::bad_alloc">If the memory for the sensor state
        /// could not be allocated.</exception>
        /// <exception cref="std::system_error">If the VISA library could not be
        /// loaded.</exception>
        /// <exception cref="visa_exception">If the sensor could not be
        /// initialised.</exception>
        rtx_sensor(_In_z_ const wchar_t *path, _In_ const std::int32_t timeout);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline rtx_sensor(_In_ rtx_sensor&& rhs) noexcept
            : detail::visa_sensor(std::move(rhs)) { }

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        ~rtx_sensor(void);

        void configure(
            _In_reads_(cnt) const oscilloscope_sensor_definition *sensors,
            _In_ const std::size_t cnt);

        /// <summary>
        /// Enable an configure one of the mathematical expressions.
        /// </summary>
        /// <param name="channel">The maths channel to be configured. For an
        /// RTB2004, this must be within [1, 4].</param>
        /// <param name="expression">The arithmetic expression to be computed,
        /// ie &quot;CH1*CH2&quot;.</param>
        /// <param name="unit">The unit of the resulting values. If
        /// <c>nullptr</c>, the currently set unit will be unchanged. This
        /// parameter defaults to <c>nullptr</c>.</param>
        void expression(_In_ const std::uint32_t channel,
            _In_opt_z_ const char *expression,
            _In_opt_z_ const char *unit = nullptr);

        ///// <summary>
        ///// Sets the path to the log file.
        ///// </summary>
        ///// <param name="path">The path to the log file, usually just the
        ///// file name.</param>
        ///// <param name="overwrite">If <c>true</c>, the file will be cleared
        ///// if it already exists. This parameter defaults to <c>false</c>.
        ///// </param>
        ///// <param name="use_usb">If <c>true</c>, the file will be written to
        ///// the attached USB stick instead of internal memory. This parameter
        ///// defaults to <c>false</c>.</param>
        ///// <exception cref="std::runtime_error">If the method is called on an
        ///// object that has been disposed by moving it.</exception>
        ///// <exception cref="visa_exception">If the VISA command was not
        ///// processed successfully.</exception>
        //void log_file(const char *path, const bool overwrite = false,
        //    const bool use_usb = false);

        /// <summary>
        /// Sets the reference point in the diagram.
        /// </summary>
        /// <param name="position">The location of the reference point on the
        /// horizontal axis, which can be the left side, the middle or the
        /// right side.</param>
        void reference_position(
            _In_ const oscilloscope_reference_point position);

        /// <summary>
        /// Sets the unit of the specified channel.
        /// </summary>
        /// <param name="channel">The number (starting at 1) of the channel to
        /// be configured.</param>
        /// <param name="unit">The unit being measured (either &quot;A&quot;
        /// or &quot;V&quot;).</param>
        /// <exception cref="std::invalid_argument">If <paramref name="unit" />
        /// is <c>nullptr</c>.</exception>
        void unit(_In_ const std::uint32_t channel, _In_z_ const char *unit);

        /// <summary>
        /// Sets the horizontal scale for all channels in time units per
        /// division.
        /// </summary>
        /// <param name="scale">Time scale within [1e-9, 50].</param>
        /// <param name="unit">The time unit, which defaults to seconds.</param>
        void time_scale(_In_ const float scale, _In_z_ const char *unit = "s");

        /// <summary>
        /// Configures the trigger.
        /// </summary>
        /// <param name="trigger">The trigger configuration.</param>
        void trigger(const oscilloscope_trigger& trigger);

        /// <summary>
        /// Sets the trigger position, which is the time distance from the
        /// trigger point to the reference point.
        /// </summary>
        /// <remarks>
        /// <para>The trigger point is the horizontal origin of the diagram.
        /// Changing the horizontal position you can move the trigger, even
        /// outside the screen.</para>
        /// </remarks>
        /// <param name="offset">The offset of the trigger points in
        /// <paramref name="unit" />s.</param>
        /// <param name="unit">The unit of the time offset, which defaults to
        /// seconds.</param>
        void trigger_position(_In_ const float offset,
            _In_z_ const char *unit = "s");

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        inline rtx_sensor& operator =(rtx_sensor&& rhs) noexcept {
            visa_sensor::operator =(std::move(rhs));
            return *this;
        }

    protected:

        /// <inheritdoc />
        measurement_data sample_sync(
            _In_ const timestamp_resolution resolution) const override;

    };

} /* namespace power_overwhelming */
} /* namespace visus */
