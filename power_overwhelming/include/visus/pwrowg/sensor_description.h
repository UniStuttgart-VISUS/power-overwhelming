// <copyright file="sensor_description.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_DESCRIPTION_H)
#define _PWROWG_SENSOR_DESCRIPTION_H
#pragma once

#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/reading_type.h"
#include "visus/pwrowg/reading_unit.h"
#include "visus/pwrowg/sensor_type.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Describes a single sensor that can be activated in a
/// <see cref="sensor_array" />.
/// </summary>
class POWER_OVERWHELMING_API sensor_description final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    sensor_description(void) noexcept;

    /// <summary>
    /// Gets a unique ID for the sensor, which should be persistent across
    /// processes.
    /// </summary>
    /// <remarks>
    /// As the ID usually includes something like the <see cref="path" />, it
    /// may not be persistent across systems or even within the same system when
    /// the hardware configuration is changed.
    /// </remarks>
    /// <returns>A pointer to the sensor ID.</returns>
    inline _Ret_maybenull_z_ const wchar_t *id(void) const noexcept {
        return this->_id.as<wchar_t>();
    }

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
    /// Gets the machine-readable path to the sensor source.
    /// </summary>
    /// <remarks>
    /// Applications typically have little use for this. The path is something
    /// that the <see cref="sensor_array" /> uses to create a sensor from its
    /// description. The path might be an actual path to a device file or another
    /// identifier that allows the array to instantiate the sensor.
    /// </remarks>
    /// <returns>A pointer to the path.</returns>
    inline _Ret_maybenull_z_ const wchar_t *path(void) const noexcept {
        return this->_path.as<wchar_t>();
    }

    /// <summary>
    /// Answer how the <see cref="reading" />s of the sensor have to be
    /// interpreted.
    /// </summary>
    /// <returns>The interpretation of the sensor readings.</returns>
    inline PWROWG_NAMESPACE::reading_type reading_type(void) const noexcept {
        return this->_reading_type;
    }

    /// <summary>
    /// Answer what the unit of the <see cref="reading" />s of the sensor is.
    /// </summary>
    /// <returns>The unit of the sensor readings.</returns>
    inline PWROWG_NAMESPACE::reading_unit reading_unit(void) const noexcept {
        return this->_reading_unit;
    }

    /// <summary>
    /// Gets the type of the sensor.
    /// </summary>
    /// <returns>A bitmask describing the type of the sensor.</returns>
    inline sensor_type type(void) const noexcept {
        return this->_type;
    }

    /// <summary>
    /// Updates the type of the sensor.
    /// </summary>
    /// <remarks>
    /// Some sensors might allow users to change parts of their type. For
    /// instance, the Tinkerforge sensor allows setting what the specific sensor
    /// is actually measuring. If a sensor has marked some or all bits as
    /// editable, these can be changed via this method. All other bits are masked
    /// and remain unchanged.
    /// </remarks>
    /// <param name="type">The type to be set. Note that only bits that have been
    /// marked editable by the sensor can be changed.</param>
    /// <returns><c>*this</c>.</returns>
    sensor_description& type(_In_ const sensor_type type) noexcept;

    /// <summary>
    /// Gets the human-readable name of the vendor providing the sensor data.
    /// </summary>
    /// <returns>A pointer to the name of the vendor.</returns>
    inline _Ret_maybenull_z_ const wchar_t *vendor(void) const noexcept {
        return this->_vendor.as<wchar_t>();
    }

private:

    sensor_type _editable_type;
    blob _id;
    blob _label;
    blob _name;
    blob _path;
    PWROWG_NAMESPACE::reading_type _reading_type;
    PWROWG_NAMESPACE::reading_unit _reading_unit;
    blob _reserved;
    sensor_type _type;
    blob _vendor;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_DESCRIPTION_H) */
