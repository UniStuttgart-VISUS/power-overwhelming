// <copyright file="rtb_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <climits>
#include <cstddef>
#include <cstdint>
#include <cinttypes>

#include "instrument_range.h"
#include "log_mode.h"
#include "measurement.h"
#include "timestamp_resolution.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations */
    namespace detail { struct visa_sensor_impl; }

    /// <summary>
    /// A sensor using a Rohde &amp; Schwarz RTB series oscilloscope.
    /// </summary>
    class POWER_OVERWHELMING_API rtb_sensor final {

    public:

        /// <summary>
        /// Create sensor objects for all Rohde &amp; Schwarz RTB2004
        /// instruments that can be enumerated via VISA.
        /// </summary>
        /// <param name="out_sensors">An array receiving the sensors. If this is
        /// <c>nullptr</c>, nothing is returned.</param>
        /// <param name="cnt_sensors">The number of sensors that can be stored in
        /// <paramref name="out_sensors" />.</param>
        /// <param name="timeout">The timeout in milliseconds for establishing a
        /// connection to each instrument that was found. This parameter defaults
        /// to 3000.</param>
        /// <returns>The number of HMC8015 instruments found, regardless of how
        /// many have been returned to <paramref name="out_sensors" />.</returns>
        static std::size_t for_all(rtb_sensor *out_sensors,
            const std::size_t cnt_sensors,
            const std::int32_t timeout = 3000);

        /// <summary>
        /// The product ID of the RTB2004.
        /// </summary>
        /// <remarks>
        /// This is the ID reported by the device we use at VISUS. If this does
        /// not work, use the RsVisaTester tool and discover the device via the
        /// &quot;Find Resource&quot; functionality.
        /// </remarks>
        static constexpr const char *rtb2004_id = "0x01D6";

        /// <summary>
        /// The vendor ID of Rohde &amp; Schwarz.
        /// </summary>
        static constexpr const char *vendor_id = "0x0AAD";

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        rtb_sensor(void);

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
        rtb_sensor(const char *path, const std::int32_t timeout);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline rtb_sensor(rtb_sensor&& rhs) noexcept : _impl(rhs._impl) {
            rhs._impl = nullptr;
        }

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        ~rtb_sensor(void);

        /// <summary>
        /// Gets the name of the sensor.
        /// </summary>
        /// <returns>The implementation-defined, human-readable name of the
        /// sensor.</returns>
        const wchar_t *name(void) const noexcept;

        void unit(const std::uint32_t channel, const char *unit);

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        rtb_sensor& operator =(rtb_sensor&& rhs) noexcept;

        /// <summary>
        /// Determines whether the sensor is valid.
        /// </summary>
        /// <remarks>
        /// A sensor is considered valid until it has been disposed by a move
        /// operation.
        /// </remarks>
        /// <returns><c>true</c> if the sensor is valid, <c>false</c>
        /// otherwise.</returns>
        operator bool(void) const noexcept;

    private:

        void check_not_disposed(void);

        detail::visa_sensor_impl *_impl;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
