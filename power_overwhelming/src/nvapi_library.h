// <copyright file="nvapi_library.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_NVAPI_LIBRARY_H)
#define _PWROWG_NVAPI_LIBRARY_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_NVAPI)

#include <pwrovrnvapi.h>

#include "library_base.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

#define __POWER_OVERWHELMING_NVAPI_FUNC(f) decltype(&::f) f = nullptr

/// <summary>
/// Wrapper for lazily loading NVAPI.
/// </summary>
/// <remarks>
/// All of this is a giant hack as we do not lod NVAPI directly, but our own
/// warpper that passes all calls through to NVAPI. The reason is that NVAPI
/// does not export the symbols of its APIs, so we cannot load them dynamically.
/// However, as we have the NDA version of NVAPI, including the required import
/// library, our wrapper can do so. Then, we can dynamically load our wrapper
/// and use the symbols exported from there. It is no solution linking against
/// NVAPI directly, because this would Power Overwhelming prevent from running
/// on machines without an NVIDIA GPU.
/// </remarks>
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

    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_enumerate_physical_gpus);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_finalise);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_get_error_message);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_get_gpu_bus_id);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_get_gpu_from_id);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_get_gpu_id);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_get_gpu_name);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_get_gpu_pci_identifiers);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_initialise);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_register_power_callback);

private:

    nvapi_library(void);
};

#undef __POWER_OVERWHELMING_NVAPI_FUNC

PWROWG_DETAIL_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_NVAPI) */
#endif /* !defined(_PWROWG_NVAPI_LIBRARY_H) */
