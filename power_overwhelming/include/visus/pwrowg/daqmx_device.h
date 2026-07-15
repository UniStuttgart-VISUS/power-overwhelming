// <copyright file="daqmx_device.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_DEVICE_H)
#define _PWROWG_DAQMX_DEVICE_H
#pragma once

#include "visus/pwrowg/blob.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A descriptor for NI DAQmx devices.
/// </summary>
/// <remarks>
/// This class is only used for identifying the devices and their capabilities.
/// Measurements are performed using the <see cref="daqmx_task" />.
/// </remarks>
class POWER_OVERWHELMING_API daqmx_device final {

public:

    /// <summary>
    /// Gets descriptors for all devices that can be found on the system.
    /// </summary>
    /// <param name="dst">Receives the descriptors. It is safe to pass
    /// <see langword="nullptr" />, in which case the number of instruments
    /// will be counted.</param>
    /// <param name="cnt">The number of elements in <paramref name="dst" />.
    /// </param>
    /// <returns>The number of devices found on the machine.</returns>
    /// <exception cref="std::system_error">If any of the API calls failed.
    /// </exception>
    static std::size_t all(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) daqmx_device *dst,
        _In_ std::size_t cnt);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <remarks>
    /// An instance creates using the default constructor does not contain any
    /// valid data.
    /// </remarks>
    daqmx_device(void) noexcept = default;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="name">The name of the device to get the properties of.
    /// </param>
    daqmx_device(_In_z_ const wchar_t *name);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="name">The name of the device to get the properties of.
    /// </param>
    daqmx_device(_In_z_ const char *name);

    /// <summary>
    /// Gets the names of the analog input channels of the device in form of a
    /// multi-sz string.
    /// </summary>
    /// <returns>The names of the analog input channels.</returns>
    _Ret_maybenull_z_ inline const char *analog_inputs(void) const noexcept {
        return this->_analog_inputs.as<char>();
    }

    /// <summary>
    /// Gets the names of the analog output channels of the device in form of a
    /// multi-sz string.
    /// </summary>
    /// <returns>The names of the analog output channels.</returns>
    _Ret_maybenull_z_ inline const char *analog_outputs(void) const noexcept {
        return this->_analog_outputs.as<char>();
    }

    /// <summary>
    /// Gets the name of the device.
    /// </summary>
    /// <returns>The name of the device.</returns>
    _Ret_maybenull_z_ inline const char *name(void) const noexcept {
        return this->_name.as<char>();
    }

    /// <summary>
    /// Indicates whether the device is simulated or not.
    /// </summary>
    /// <returns><see langword="true "/> if the device is simulated,
    /// <see langword="false" /> otherwise.</returns>
    inline bool simulated(void) const noexcept {
        return this->_simulated;
    }

    /// <summary>
    /// Gets the type (product name) of the device.
    /// </summary>
    /// <returns>The type of the device.</returns>
    _Ret_maybenull_z_ inline const char *type(void) const noexcept {
        return this->_type.as<char>();
    }

private:

    void populate(void);

    blob _analog_inputs;
    blob _analog_outputs;
    blob _name;
    bool _simulated;
    blob _type;

};

PWROWG_NAMESPACE_END

#endif /*!defined(_PWROWG_DAQMX_DEVICE_H) */
