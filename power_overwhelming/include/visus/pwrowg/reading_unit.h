// <copyright file="reading_unit.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_READING_UNIT_H)
#define _READING_UNIT_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Enumerates possible units used for <see cref="reading" />s.
/// </summary>
enum class reading_unit {

    /// <summary>
    /// The unit is unknown. Consult the documentation of the sensor for how the
    /// data need to be interpreted.
    /// </summary>
    unknown = 0,

    /// <summary>
    /// Ampère, the unit for current.
    /// </summary>
    ampere,

    /// <summary>
    /// Volt, the unit for voltage.
    /// </summary>
    volt,

    /// <summary>
    /// Watt, the unit for power.
    /// </summary>
    watt
};

PWROWG_NAMESPACE_END

#endif /* !defined(_READING_UNIT_H) */
