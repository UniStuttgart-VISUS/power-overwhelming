// <copyright file="nvapi_library.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_NVAPI)
#include "nvapi_library.h"


#define __POWER_OVERWHELMING_NVAPI_FUNC(n) \
    this->n = this->get_function<decltype(this->n)>(#n)


/*
 * PWROWG_DETAIL_NAMESPACE::nvapi_library::instance
 */
const PWROWG_DETAIL_NAMESPACE::nvapi_library&
PWROWG_DETAIL_NAMESPACE::nvapi_library::instance(void) {
    static const nvapi_library instance;
    return instance;
}


/*
 * PWROWG_DETAIL_NAMESPACE::nvapi_library
 */
PWROWG_DETAIL_NAMESPACE::nvapi_library::nvapi_library(void)
#if defined(_WIN32)
        : library_base(TEXT("pwrovrnvapi.dll")) {
#endif /* defined(_WIN32) */
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_enumerate_physical_gpus);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_finalise);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_get_error_message);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_get_gpu_bus_id);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_get_gpu_name);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_get_gpu_pci_identifiers);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_get_gpu_slot_id);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_initialise);
    __POWER_OVERWHELMING_NVAPI_FUNC(nvapi_register_power_callback);
}

#undef __POWER_OVERWHELMING_NVAPI_FUNC
#endif /* defined(POWER_OVERWHELMING_WITH_NVAPI) */
