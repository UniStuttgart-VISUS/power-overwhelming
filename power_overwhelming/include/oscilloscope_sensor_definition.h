// <copyright file="oscilloscope_sensor_definition.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>

#include "power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines a power sensor using a voltage and a current probe of an
    /// oscilloscope.
    /// </summary>
    class POWER_OVERWHELMING_API oscilloscope_sensor_definition final {

    public:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="description">The description of the sensor, which must
        /// not be <c>nullptr</c>.</param>
        /// <param name="channel_voltage">The channel which to the voltage probe
        /// is attached.</param>
        /// <param name="channel_current">The channel which to the current probe
        /// is attached.</param>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="description" /> is <c>nullptr</c>.</exception>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="channel_voltage" /> and 
        /// <paramref name="channel_current" /> are the same.</exception>
        /// <exception cref="std::bad_alloc">If the memory for storing the
        /// description could not be allocated.</exception>
        oscilloscope_sensor_definition(const wchar_t *description,
            const std::uint32_t channel_voltage,
            const std::uint32_t channel_current);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="description">The description of the sensor, which must
        /// not be <c>nullptr</c>.</param>
        /// <param name="channel_voltage">The channel which to the voltage probe
        /// is attached.</param>
        /// <param name="attenuation_voltage">The attenuation or gain of the
        /// voltage probe. Consult the manual of the instrument on which values
        /// are valid for this parameter.</param>
        /// <param name="channel_current">The channel which to the current probe
        /// is attached.</param>
        /// <param name="attenuation_current">The attenuation or gain of the
        /// current probe. Consult the manual of the instrument on which values
        /// are valid for this parameter.</param>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="description" /> is <c>nullptr</c>.</exception>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="channel_voltage" /> and 
        /// <paramref name="channel_current" /> are the same.</exception>
        /// <exception cref="std::bad_alloc">If the memory for storing the
        /// description could not be allocated.</exception>
        oscilloscope_sensor_definition(const wchar_t *description,
            const std::uint32_t channel_voltage,
            const float attenuation_voltage,
            const std::uint32_t channel_current,
            const float attenuation_current);

        /// <summary>
        /// Clone <paramref name="rhs" />.
        /// </summary>
        /// <param name="rhs">The object to be cloned.</param>
        oscilloscope_sensor_definition(
            const oscilloscope_sensor_definition& rhs);

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~oscilloscope_sensor_definition(void);

        /// <summary>
        /// Gets the attenuation of the current probe.
        /// </summary>
        /// <returns>The attenuation or gain of the current probe if the probe
        /// was not detected by the instrument.</returns>
        inline float attenuation_current(void) const noexcept {
            return this->_attenuation_current;
        }

        /// <summary>
        /// Gets the attenuation of the voltage probe.
        /// </summary>
        /// <returns>The attenuation or gain of the voltage probe if the probe
        /// was not detected by the instrument.</returns>
        inline float attenuation_voltage(void) const noexcept {
            return this->_attenuation_voltage;
        }

        /// <summary>
        /// Determines whether the current probe uses an automatically detected
        /// attenuation.
        /// </summary>
        /// <returns><c>true</c> if not manual attenuation or gain was set for
        /// the current probe, <c>false</c> otherwise.</returns>
        inline float auto_attenuation_current(void) const noexcept {
            return (this->_attenuation_current <= 0.0f);
        }

        /// <summary>
        /// Determines whether the current probe uses an automatically detected
        /// attenuation.
        /// </summary>
        /// <returns><c>true</c> if not manual attenuation or gain was set for
        /// the voltage probe, <c>false</c> otherwise.</returns>
        inline float auto_attenuation_voltage(void) const noexcept {
            return (this->_attenuation_voltage <= 0.0f);
        }

        /// <summary>
        /// Gets the channel of the current probe.
        /// </summary>
        /// <returns>The number of the channel which to the current probe is
        /// attached.</returns>
        inline std::uint32_t channel_current(void) const noexcept {
            return this->_channel_current;
        }

        /// <summary>
        /// Gets the channel of the voltage probe.
        /// </summary>
        /// <returns>The number of the channel which to the voltage probe is
        /// attached.</returns>
        inline std::uint32_t channel_voltage(void) const noexcept {
            return this->_channel_voltage;
        }

        /// <summary>
        /// Gets the description of the sensor.
        /// </summary>
        /// <returns>The description of the sensor. The object remains owner of
        /// the string returned.</returns>
        inline const wchar_t *description(void) const noexcept {
            return this->_description;
        }

        /// <summary>
        /// Assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::bad_alloc">If the necessary memory for the
        /// copy could not be acquired.</exception>
        oscilloscope_sensor_definition& operator =(
            const oscilloscope_sensor_definition& rhs);

    private:

        float _attenuation_current;
        float _attenuation_voltage;
        std::uint32_t _channel_current;
        std::uint32_t _channel_voltage;
        wchar_t *_description;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
