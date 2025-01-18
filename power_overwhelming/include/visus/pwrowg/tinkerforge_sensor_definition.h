// <copyright file="tinkerforge_sensor_definition.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "visus/pwrowg/api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Definition of a Tinkerforge sensor allowing the sensor UID and a
    /// description to be specified at the same time.
    /// </summary>
    class POWER_OVERWHELMING_API tinkerforge_sensor_definition final {

    public:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline tinkerforge_sensor_definition(void)
            : _description(nullptr), _uid(nullptr) { }

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="uid">The UID of the sensor.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="uid" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="std::bad_alloc">If the memory for the UID
        /// could not be allocated.</exception>
        tinkerforge_sensor_definition(_In_z_ const char *uid);

        /// <summary>
        /// Clone <paramref name="rhs" />.
        /// </summary>
        /// <param name="rhs">The object to be cloned.</param>
        /// <exception cref="std::bad_alloc">If the memory for the copied data
        /// could not be allocated.</exception>
        tinkerforge_sensor_definition(
            _In_ const tinkerforge_sensor_definition& rhs);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new object.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline tinkerforge_sensor_definition(
                _In_ tinkerforge_sensor_definition&& rhs) noexcept
                : _description(rhs._description), _uid(rhs._uid) {
            rhs._description = nullptr;
            rhs._uid = nullptr;
        }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~tinkerforge_sensor_definition(void);

        /// <summary>
        /// Gets the user-defined description of the sensor.
        /// </summary>
        /// <returns>The description of the sensor. The object remains owner of
        /// the memory returned.</returns>
        _Ret_maybenull_z_ const wchar_t *description(void) const noexcept {
            return this->_description;
        }

        /// <summary>
        /// Sets the user-defined description of the sensor.
        /// </summary>
        /// <param name="description">The new description of the sensor. It is
        /// safe to pass <c>nullptr</c>.</param>
        /// <exception cref="std::bad_alloc">If the memory for the description
        /// could not be allocated.</exception>
        void description(_In_opt_z_ const wchar_t *description);

        /// <summary>
        /// Gets the UID of the sensor.
        /// </summary>
        /// <returns>The UID of the sensor. The object remains owner of the
        /// memory returned.</returns>
        _Ret_maybenull_z_ const char *uid(void) const noexcept {
            return this->_uid;
        }

        /// <summary>
        /// Assignment operator.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>*this</c></returns>
        /// <exception cref="std::bad_alloc">If the memory for the copied data
        /// could not be allocated.</exception>
        tinkerforge_sensor_definition& operator =(
            _In_ const tinkerforge_sensor_definition& rhs);

        /// <summary>
        /// Move-assignment operator.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>*this</c></returns>
        tinkerforge_sensor_definition& operator =(
            _In_ tinkerforge_sensor_definition&& rhs) noexcept;

    private:

        wchar_t *_description;
        char *_uid;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
