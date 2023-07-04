// <copyright file="rtx_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/sensor.h"
#include "power_overwhelming/rtx_instrument.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// A sensor using a Rohde &amp; Schwarz RTA and RTB series oscilloscope.
    /// </summary>
    class POWER_OVERWHELMING_API rtx_sensor final : public sensor {

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
        /// Initialises a new instance.
        /// </summary>
        inline rtx_sensor(void) : _name(nullptr) { }

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
        rtx_sensor(_In_z_ const char *path,
            _In_ const visa_instrument::timeout_type timeout);

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
        rtx_sensor(_In_z_ const wchar_t *path,
            _In_ const visa_instrument::timeout_type timeout);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        rtx_sensor(_Inout_ rtx_sensor&& rhs) noexcept;

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        virtual ~rtx_sensor(void);

        /// <summary>
        /// Gets the name of the sensor.
        /// </summary>
        /// <remarks>
        /// It is safe to call this method on a disposed object, in which case
        /// the name will be <c>nullptr</c>.
        /// </remarks>
        /// <returns>The implementation-defined, human-readable name of the
        /// sensor.</returns>
        _Ret_maybenull_z_ virtual const wchar_t *name(
            void) const noexcept override;

        /// <summary>
        /// Gets the VISA path of the instrument.
        /// </summary>
        /// <returns>The path of the instrument.</returns>
        inline _Ret_maybenull_z_ const char *path(void) const noexcept {
            return this->_instrument.path();
        }

        using sensor::sample;

        /// <summary>
        /// Synchonises the date and time on the instrument with the system
        /// clock of the computer calling this API.
        /// </summary>
        /// <param name="utc">If <c>true</c>, UTC will be used, the local time
        /// otherwise. This parameter defaults to <c>false</c>.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If the VISA command was not
        /// processed successfully.</exception>
        inline rtx_sensor& synchronise_clock(_In_ const bool utc = false) {
            this->_instrument.synchronise_clock(utc);
            return *this;
        }

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        rtx_sensor& operator =(_Inout_ rtx_sensor&& rhs) noexcept;

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

        /// <inheritdoc />
        measurement_data sample_sync(
            _In_ const timestamp_resolution resolution) const override;

    private:

        void initialise(void);

        rtx_instrument _instrument;
        wchar_t *_name;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
