// <copyright file="nvapi_util.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_NVAPI_UTIL_H)
#define _PWROWG_NVAPI_UTIL_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_NVAPI)

#include "nvapi_library.h"
#include "sensor_description_builder.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Sets the path to an NVAPI-based sensor in the given
/// <paramref name="builder"/>.
/// </summary>
/// <remarks>
/// This function is used by the asynchronous power sensor and the synchronous
/// throttling sensor to obtain consistens paths and ID strings.
/// </remarks>
/// <param name="builder"></param>
/// <param name="gpu"></param>
/// <param name="id_prefix"></param>
sensor_description_builder& set_nvapi_identity(
    _In_ sensor_description_builder& builder,
    _In_ NvPhysicalGpuHandle gpu,
    _In_z_ const wchar_t *id_prefix = L"NVAPI");

PWROWG_DETAIL_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_NVAPI) */
#endif /* !defined(_PWROWG_NVAPI_UTIL_H) */
