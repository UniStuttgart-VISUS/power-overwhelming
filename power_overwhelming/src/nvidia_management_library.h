// <copyright file="nvidia_management_library.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_NVIDIA_MANAGEMENT_LIBRARY_H)
#define _PWROWG_NVIDIA_MANAGEMENT_LIBRARY_H
#pragma once

#include <nvml.h>

#include "library_base.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

#define __POWER_OVERWHELMING_NVML_FUNC(f) decltype(&::f) f = nullptr

/// <summary>
/// Wrapper for lazily loading NVML.
/// </summary>
class PWROWG_TEST_API nvidia_management_library final : library_base {

public:

    /// <summary>
    /// Gets the only instance of the class.
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    /// <exception cref="std::system_error">If the library could not
    /// be loaded, eg because the machine does not have an NVIDIA GPU.
    /// </exception>
    static const nvidia_management_library& instance(void);

    __POWER_OVERWHELMING_NVML_FUNC(nvmlDeviceGetCount);
    __POWER_OVERWHELMING_NVML_FUNC(nvmlDeviceGetName);
    __POWER_OVERWHELMING_NVML_FUNC(nvmlDeviceGetPciInfo);
    __POWER_OVERWHELMING_NVML_FUNC(nvmlDeviceGetPowerUsage);
    __POWER_OVERWHELMING_NVML_FUNC(nvmlDeviceGetHandleByIndex);
    __POWER_OVERWHELMING_NVML_FUNC(nvmlDeviceGetHandleByPciBusId);
    __POWER_OVERWHELMING_NVML_FUNC(nvmlDeviceGetHandleBySerial);
    __POWER_OVERWHELMING_NVML_FUNC(nvmlDeviceGetHandleByUUID);
    __POWER_OVERWHELMING_NVML_FUNC(nvmlDeviceGetUUID);
    __POWER_OVERWHELMING_NVML_FUNC(nvmlErrorString);
    __POWER_OVERWHELMING_NVML_FUNC(nvmlInit);
    __POWER_OVERWHELMING_NVML_FUNC(nvmlShutdown);

private:

    nvidia_management_library(void);

};

#undef __POWER_OVERWHELMING_NVML_FUNC

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_NVIDIA_MANAGEMENT_LIBRARY_H) */
