// <copyright file="sensor_description.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_DESCRIPTION_H)
#define _PWROWG_SENSOR_DESCRIPTION_H
#pragma once

#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/sensor_type.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Describes a single sensor that can be activated in a
/// <see cref="sensor_array" />.
/// </summary>
class sensor_description final {

public:

    /// <summary>
    /// Gets a user-defined label for the sensor.
    /// </summary>
    /// <returns>A pointer to the label of the sensor.</returns>
    inline _Ret_maybenull_z_ const wchar_t *label(void) const noexcept {
        return this->_label.as<wchar_t>();
    }

    /// <summary>
    /// Sets a user-defined label.
    /// </summary>
    /// <param name="label">The label being assigned to the sensor.</param>
    /// <returns><c>*this</c>.</returns>
    sensor_description& label(_In_opt_z_ const wchar_t *label);

    /// <summary>
    /// Sets a user-defined label.
    /// </summary>
    /// <param name="label">The label being assigned to the sensor.</param>
    /// <returns><c>*this</c>.</returns>
    sensor_description& label(_In_opt_z_ const char *label);

    /// <summary>
    /// Gets the human-readable name of the sensor.
    /// </summary>
    /// <returns>A pointer to the name of the sensor.</returns>
    inline _Ret_maybenull_z_ const wchar_t *name(void) const noexcept {
        return this->_name.as<wchar_t>();
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
        return this->_vendor.as<wchar_t>();
    }

private:

    blob _label;
    blob _name;
    sensor_type _type;
    blob _vendor;
    // TODO: type/class?
    // TODO: hardware/target?
    // TODO: unique/persistent ID?

};

PWROWG_NAMESPACE_END

#endif  /* !defined(_PWROWG_SENSOR_DESCRIPTION_H) */
