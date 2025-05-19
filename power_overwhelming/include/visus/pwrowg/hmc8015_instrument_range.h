// <copyright file="hmc8015_instrument_range.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_HMC8015_INSTRUMENT_RANGE_H)
#define _PWROWG_HMC8015_INSTRUMENT_RANGE_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines how the range setters of the <see cref="hmc8015_sensor" /> behave.
/// </summary>
enum class hmc8015_instrument_range {

    /// <summary>
    /// Determine the measurement range automatically.
    /// </summary>
    /// <remarks>
    /// The instrument will adjust the measurement range by itself as
    /// necessary. However, if that happens, any integration of values will
    /// fail, wherefore it is reasonable to set an explicit or the maximum
    /// possible range if integration is desired.
    /// </remarks>
    automatically,

    /// <summary>
    /// Use the explicitly set range.
    /// </summary>
    /// <remarks>
    /// A valid value for the range must be provided in this case. Consult
    /// the documentation of the instrument to find out what valid values
    /// for the quantity in question are.
    /// </remarks>
    explicitly,

    /// <summary>
    /// Use the minimum possible range.
    /// </summary>
    minimum,

    /// <summary>
    /// Use the maximum possible range.
    /// </summary>
    maximum
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_HMC8015_INSTRUMENT_RANGE_H) */
