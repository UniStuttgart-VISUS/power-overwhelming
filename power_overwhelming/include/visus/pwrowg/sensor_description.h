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
#include "visus/pwrowg/type_erased_storage.h"


// Forward declarations.
PWROWG_DETAIL_NAMESPACE_BEGIN
class sensor_description_builder;
PWROWG_DETAIL_NAMESPACE_END


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Describes a single sensor that can be activated in a
/// <see cref="sensor_array" />.
/// </summary>
/// <remarks>
/// <para>Note to implementors: Use the privte
/// <see cref="detail::sensor_description_builder" /> class to construct a
/// description for your sensor type.</para>
/// <para>Note to implementors: A sensor type must be able to create descriptors
/// of this type for all data sources it supports. Furthermore, the sensor
/// implementation must be able to instantiate a sensor from a descriptor of this
/// type. If this is not possible using the public data in this class, sensor
/// implementations can use the <see cref="_private" /> member of this class to
/// store arbitraty data. We use a <see cref="blob" /> to erase any
/// sensor-specific tyoe information from the descriptor. Implementors need to
/// provide a <see cref="detail::rule_of_five_eraser" /> if the data they store
/// in <see cref="_private" /> is not trivially copyable.</para>
/// </remarks>
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
    /// Answer whether all bits of <paramref name="test" /> are set in the
    /// sensor type.
    /// </summary>
    /// <param name="test">The bits to be tested.</param>
    /// <returns><c>true</c> if all bits are set, <c>false</c> otherwise.
    /// </returns>
    inline bool is_sensor_type(_In_ sensor_type test) const noexcept {
        return ((this->_sensor_type & test) == test);
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
    inline PWROWG_NAMESPACE::sensor_type sensor_type(void) const noexcept {
        return this->_sensor_type;
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
    sensor_description& sensor_type(
        _In_ const PWROWG_NAMESPACE::sensor_type type) noexcept;

    /// <summary>
    /// Gets the human-readable name of the vendor providing the sensor data.
    /// </summary>
    /// <returns>A pointer to the name of the vendor.</returns>
    inline _Ret_maybenull_z_ const wchar_t *vendor(void) const noexcept {
        return this->_vendor.as<wchar_t>();
    }

private:

    PWROWG_NAMESPACE::sensor_type _editable_type;
    blob _id;
    blob _label;
    blob _name;
    blob _path;
    PWROWG_NAMESPACE::type_erased_storage _private;
    PWROWG_NAMESPACE::reading_type _reading_type;
    PWROWG_NAMESPACE::reading_unit _reading_unit;
    PWROWG_NAMESPACE::sensor_type _sensor_type;
    blob _vendor;

    friend class PWROWG_DETAIL_NAMESPACE::sensor_description_builder;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_DESCRIPTION_H) */
