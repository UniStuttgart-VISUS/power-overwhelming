// <copyright file="nvapi_throttling_reason.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_NVAPI_THROTTLING_REASON_H)
#define _PWROWG_NVAPI_THROTTLING_REASON_H
#pragma once

#include <cinttypes>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Describes the elements of the throttling mask returned by the
/// <see cref="nvapi_synchronous_sensor" /> reporting the current throttling
/// state of an NVIDIA GPU. These masks are derived from the
/// <see cref="NV_GPU_PERF_POLICY_ID_SW" /> enumeration of NVAPI.
/// </summary>
enum class nvapi_throttling_reason : std::uint32_t {

    /// <summary>
    /// The performance is not throttled at all.
    /// </summary>
    none = 0,

    /// <summary>
    /// The performance is limited by the total power limit of the GPU.
    /// </summary>
    power = (1 << 0),

    /// <summary>
    /// The performance is limited by the temperature limit of the GPU.
    /// </summary>
    thermal = (1 << 1),

    /// <summary>
    /// The performance is limited by the reliability of the input voltage.
    /// </summary>
    reliability = 1 << 2,

    /// <summary>
    /// The performance is limited by the maximum operating voltage of the GPU.
    /// </summary>
    voltage = 1 << 3,

    /// <summary>
    /// The performance is limited by GPU utilisation.
    /// </summary>
    utilisation = 1 << 4,

    /// <summary>
    /// The performance is limited by SLI GPUBoost synchronisation.
    /// </summary>
    sli_gpu_boost_synchronisation = 1 << 5
};
PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_NVAPI_THROTTLING_REASON_H) */
