// <copyright file="visa_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "sensor.h"

namespace visus {
namespace power_overwhelming {
namespace detail {

    /* Forward declarations. */
    struct visa_sensor_impl;

    /// <summary>
    /// Base class for sensors using VISA instruments.
    /// </summary>
    class POWER_OVERWHELMING_API visa_sensor : public sensor {

    public:

        /// <summary>
        /// The vendor ID of Rohde &amp; Schwarz.
        /// </summary>
        static constexpr const char *rohde_und_schwarz = "0x0AAD";

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        visa_sensor(void);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <remarks>
        /// This constructor will set the name of the sensor to the identity
        /// string of the instrument, reset the instrument and clear any error
        /// state in the instrument.
        /// </remarks>
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
        visa_sensor(const char *path, const std::int32_t timeout);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline visa_sensor(visa_sensor&& rhs) noexcept : _impl(rhs._impl) {
            rhs._impl = nullptr;
        }

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        virtual ~visa_sensor(void);

        /// <summary>
        /// Gets the name of the sensor.
        /// </summary>
        /// <remarks>
        /// It is safe to call this method on a disposed object, in which case
        /// the name will be <c>nullptr</c>.
        /// </remarks>
        /// <returns>The implementation-defined, human-readable name of the
        /// sensor.</returns>
        virtual const wchar_t *name(void) const noexcept override;

        /// <summary>
        /// Gets the VISA path of the device.
        /// </summary>
        /// <returns>The VISA path used to open the device.</returns>
        const char *path(void) const noexcept;

        /// <summary>
        /// Resets the instrument to its default state.
        /// </summary>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If the VISA command was not
        /// processed successfully.</exception>
        virtual void reset(void);

        /// <summary>
        /// Synchonises the date and time on the instrument with the system
        /// clock of the computer calling this API.
        /// </summary>
        /// <param name="utc">If <c>true</c>, UTC will be used, the local time
        /// otherwise. This parameter defaults to <c>false</c>.</param>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If the VISA command was not
        /// processed successfully.</exception>
        void synchronise_clock(const bool utc = false);

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        visa_sensor& operator =(visa_sensor&& rhs) noexcept;

        /// <summary>
        /// Determines whether the sensor is valid.
        /// </summary>
        /// <remarks>
        /// A sensor is considered valid until it has been disposed by a move
        /// operation.
        /// </remarks>
        /// <returns><c>true</c> if the sensor is valid, <c>false</c>
        /// otherwise.</returns>
        virtual operator bool(void) const noexcept override;

    protected:

        /// <summary>
        /// Clear all queued error codes.
        /// </summary>
        void clear_status(void);

        /// <summary>
        /// Checks <see cref="system_error" /> and throws a
        /// <see cref="std::runtime_error" /> if it does not return zero.
        /// </summary>
        /// <exception cref="visa_exception">If the current system state could
        /// not be retrieved.</exception>
        /// <exception cref="std::runtime_error">If the current system state was
        /// retrieved and is not zero.</exception>
        void throw_on_system_error(void);

        /// <summary>
        /// Exposes the sensor implementation.
        /// </summary>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        operator visa_sensor_impl&(void) const;

        /// <summary>
        /// Exposes the sensor implementation.
        /// </summary>
        /// <param name=""></param>
        /// <returns></returns>
        inline operator visa_sensor_impl *(void) const noexcept {
            return this->_impl;
        }

    private:

        detail::visa_sensor_impl *_impl;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
