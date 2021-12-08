// <copyright file="hmc8015_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cstddef>
#include <cstdint>

#include "power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations */
    namespace detail { struct visa_sensor_impl; }

    /// <summary>
    /// Allows for controlling a Rohde & Schwarz HMC8015 power analyser.
    /// </summary>
    class POWER_OVERWHELMING_API hmc8015_sensor final {

    public:

        /// <summary>
        /// Create sensor objects for all Rohde &amp; Schwarz HMC8015 devices
        /// that can be enumerated via VISA.
        /// </summary>
        /// <param name="out_sensors">An array receiving the sensors. If this is
        /// <c>nullptr</c>, nothing is returned.</param>
        /// <param name="cnt_sensors">The number of sensors that can be stored in
        /// <paramref name="out_sensors" />.</param>
        /// <param name="timeout">The timeout in milliseconds for establishing a
        /// connection to each instrument that was found. This parameter defaults
        /// to 3000.</param>
        /// <returns></returns>
        static std::size_t for_all(hmc8015_sensor *out_sensors,
            const std::size_t cnt_sensors,
            const std::int32_t timeout = 3000);

        /// <summary>
        /// The product ID of the HMC8015.
        /// </summary>
        /// <remarks>
        /// This is the ID reported by the device we use at VISUS. If this does
        /// not work, use the RsVisaTester tool and discover the device via the
        /// &quot;Find Resource&quot; functionality.
        /// </remarks>
        static constexpr const char *product_id = "0x0135";

        /// <summary>
        /// The vendor ID of Rohde &amp; Schwarz.
        /// </summary>
        static constexpr const char *vendor_id = "0x0AAD";

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        hmc8015_sensor(void);

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
        hmc8015_sensor(const char *path, const std::int32_t timeout);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline hmc8015_sensor(hmc8015_sensor&& rhs) noexcept
                : _impl(rhs._impl) {
            rhs._impl = nullptr;
        }

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        ~hmc8015_sensor(void);

        /// <summary>
        /// Gets the name of the sensor.
        /// </summary>
        /// <returns>The implementation-defined, human-readable name of the
        /// sensor.</returns>
        const wchar_t *name(void) const noexcept;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        hmc8015_sensor& operator =(hmc8015_sensor&& rhs) noexcept;

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

        detail::visa_sensor_impl *_impl;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
