// <copyright file="msr_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_MSR_CONFIGURATION_H)
#define _PWROWG_MSR_CONFIGURATION_H
#pragma once

#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/sensor_configuration.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Provides additional configuration options for sensors based on model-specific
/// (RAPL) registers when creating a <see cref="sensor_array" />.
/// </summary>
class POWER_OVERWHELMING_API msr_configuration final
        : public sensor_configuration {

public:

    /// <summary>
    /// A unique identifer for the <see cref="msr_configuration" /> type.
    /// </summary>
    static const guid id;

    /// <summary>
    /// Gets the name used for the driver service if a valid driver was
    /// configured to be started by the MSR sensor.
    /// </summary>
    /// <returns>The name of the driver service.</returns>
    inline _Ret_maybenull_z_ const wchar_t *driver_name(void) const noexcept {
        return this->_driver_name.as<wchar_t>();
    }

    /// <summary>
    /// If not <c>nullptr</c>, the path to a kernel driver service to be started
    /// by the MSR sensor.
    /// </summary>
    /// <returns>The path to the driver service.</returns>
    inline _Ret_maybenull_z_ const wchar_t *driver_path(void) const noexcept {
        return this->_driver_path.as<wchar_t>();
    }

    /// <summary>
    /// Instructs the MSR sensor to start the given driver automatically.
    /// </summary>
    /// <param name="path">The path to the kernel driver.</param>
    /// <param name="name">The name of the service used for the driver. If
    /// <c>nullptr</c>, the sensor decides on the name.</param>
    /// <returns><c>*this</c>.</returns>
    msr_configuration& start_driver(_In_z_ const wchar_t *path,
        _In_opt_z_ const wchar_t *name = nullptr);

private:

    blob _driver_name;
    blob _driver_path;

};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_MSR_CONFIGURATION_H) */
