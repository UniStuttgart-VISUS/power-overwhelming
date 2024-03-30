// <copyright file="nvidia_management_library.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "nvidia_management_library.h"


#define __POWER_OVERWHELMING_GET_NVML_FUNC(n) \
    this->n = this->get_function<decltype(this->n)>(#n)


/*
 * visus::power_overwhelming::detail::nvidia_management_library::instance
 */
const visus::power_overwhelming::detail::nvidia_management_library&
visus::power_overwhelming::detail::nvidia_management_library::instance(void) {
    static const nvidia_management_library instance;
    return instance;
}


/*
 * ...::detail::nvidia_management_library::nvidia_management_library
 */
visus::power_overwhelming::detail::nvidia_management_library
::nvidia_management_library(void)
#if defined(_WIN32)
        : library_base(TEXT("nvml.dll")) {
#else /* defined(_WIN32) */
        : library_base("libnvidia-ml.so") {
#endif /* defined(_WIN32) */
    __POWER_OVERWHELMING_GET_NVML_FUNC(nvmlDeviceGetCount);
    __POWER_OVERWHELMING_GET_NVML_FUNC(nvmlDeviceGetName);
    __POWER_OVERWHELMING_GET_NVML_FUNC(nvmlDeviceGetPciInfo);
    __POWER_OVERWHELMING_GET_NVML_FUNC(nvmlDeviceGetPowerUsage);
    __POWER_OVERWHELMING_GET_NVML_FUNC(nvmlDeviceGetHandleByIndex);
    __POWER_OVERWHELMING_GET_NVML_FUNC(nvmlDeviceGetHandleByPciBusId);
    __POWER_OVERWHELMING_GET_NVML_FUNC(nvmlDeviceGetHandleBySerial);
    __POWER_OVERWHELMING_GET_NVML_FUNC(nvmlDeviceGetHandleByUUID);
    __POWER_OVERWHELMING_GET_NVML_FUNC(nvmlDeviceGetUUID);
    __POWER_OVERWHELMING_GET_NVML_FUNC(nvmlErrorString);
    __POWER_OVERWHELMING_GET_NVML_FUNC(nvmlInit);
    __POWER_OVERWHELMING_GET_NVML_FUNC(nvmlShutdown);
}
