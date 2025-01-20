// <copyright file="sensor_description.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_DESCRIPTION_H)
#define _PWROWG_SENSOR_DESCRIPTION_H
#pragma once

#include "visus/pwrowg/sensor_type.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Describes a single sensor that can be activated in a
/// <see cref="sensor_array" />.
/// </summary>
class sensor_description final {

public:

    /// <summary>
    /// Gets the human-readable name of the sensor.
    /// </summary>
    /// <returns>A pointer to the name of the sensor.</returns>
    inline _Ret_maybenull_z_ const wchar_t *name(void) const noexcept {
        return this->_name;
    }

    /// <summary>
    /// Gets the type of the sensor.
    /// </summary>
    /// <returns>A bitmask describing the type of the sensor.</returns>
    inline sensor_type type(void) const noexcept {
        return this->_type;
    }

    /// <summary>
    /// Gets the human-readable name of the vendor providing the sensor data.
    /// </summary>
    /// <returns>A pointer to the name of the vendor.</returns>
    inline _Ret_maybenull_z_ const wchar_t *vendor(void) const noexcept {
        return this->_vendor;
    }

private:

    wchar_t *_name;
    sensor_type _type;
    wchar_t *_vendor;
    // TODO: type/class?
    // TODO: hardware/target?
    // TODO: unique/persistent ID?

};

PWROWG_NAMESPACE_END

#endif  /* !defined(_PWROWG_SENSOR_DESCRIPTION_H) */
