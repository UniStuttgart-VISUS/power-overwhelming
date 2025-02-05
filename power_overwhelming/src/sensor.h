// <copyright file="sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_H)
#define _PWROWG_SENSOR_H
#pragma once

#include <cinttypes>
#include <cstdlib>

#include "visus/pwrowg/api.h"

#include "sensor_state.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Defines the interface for a generic sensor.
/// </summary>
class sensor {

protected:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="index">The zero-based index of the sensor in the sensor
    /// array owning it.</param>
    inline sensor(_In_ const std::size_t index) : _index(index) { }

    /// <summary>
    /// Answer the zero-based index of the sensor, which must be used for the
    /// samples it generates.
    /// </summary>
    /// <returns>The zero-based index of the sensor.</returns>
    inline std::size_t index(void) const noexcept {
        return this->_index;
    }

private:

    std::size_t _index;
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_H) */
