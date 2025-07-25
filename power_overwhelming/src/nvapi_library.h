﻿// <copyright file="nvapi_library.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_NVAPI_LIBRARY_H)
#define _PWROWG_NVAPI_LIBRARY_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_NVAPI)

#include <nvapi.h>

#include "library_base.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

#define __POWER_OVERWHELMING_NVAPI_FUNC(f) decltype(&::f) f = nullptr

/// <summary>
/// Wrapper for lazily loading NVAPI.
/// </summary>
class PWROWG_TEST_API nvapi_library final : library_base {

public:

    /// <summary>
    /// Gets the only instance of the class.
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    /// <exception cref="std::system_error">If the library could not
    /// be loaded, eg because the machine does not have an NVIDIA GPU.
    /// </exception>
    static const nvapi_library& instance(void);

    __POWER_OVERWHELMING_NVAPI_FUNC(NvAPI_EnumPhysicalGPUs);
    __POWER_OVERWHELMING_NVAPI_FUNC(NvAPI_GetErrorMessage);
    __POWER_OVERWHELMING_NVAPI_FUNC(NvAPI_GetGPUIDfromPhysicalGPU);
    __POWER_OVERWHELMING_NVAPI_FUNC(NvAPI_GetPhysicalGPUFromGPUID);
    __POWER_OVERWHELMING_NVAPI_FUNC(NvAPI_GPU_GetBusId);
    __POWER_OVERWHELMING_NVAPI_FUNC(NvAPI_GPU_GetFullName);
    __POWER_OVERWHELMING_NVAPI_FUNC(NvAPI_GPU_GetPCIIdentifiers);
    __POWER_OVERWHELMING_NVAPI_FUNC(NvAPI_Initialize);
    __POWER_OVERWHELMING_NVAPI_FUNC(NvAPI_Unload);

private:

    nvapi_library(void);

};

#undef __POWER_OVERWHELMING_NVAPI_FUNC

PWROWG_DETAIL_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_NVAPI) */
#endif /* !defined(_PWROWG_NVAPI_LIBRARY_H) */
