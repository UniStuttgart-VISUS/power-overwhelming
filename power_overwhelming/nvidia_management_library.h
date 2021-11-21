// <copyright file="nvidia_management_library.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <nvml.h>

#include "library_base.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

#define __POWER_OVERWHELMING_NVML_FUNC(f) decltype(&f) f = nullptr

    /// <summary>
    /// Wrapper for lazily loading NVML.
    /// </summary>
    class nvidia_management_library final : library_base {

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
        __POWER_OVERWHELMING_NVML_FUNC(nvmlErrorString);
        __POWER_OVERWHELMING_NVML_FUNC(nvmlInit);
        __POWER_OVERWHELMING_NVML_FUNC(nvmlShutdown);

    private:

        nvidia_management_library(void);

    };

#undef __POWER_OVERWHELMING_NVML_FUNC

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
