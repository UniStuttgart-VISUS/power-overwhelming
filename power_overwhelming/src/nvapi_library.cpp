// <copyright file="nvapi_library.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "nvapi_library.h"


#define __POWER_OVERWHELMING_GET_NVAPI_FUNC(n) \
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
        : library_base(TEXT("nvapi.dll")) {
#else /* defined(_WIN32) */
        : library_base("libnvapi.so") {
#endif /* defined(_WIN32) */
    __POWER_OVERWHELMING_GET_NVAPI_FUNC(NvAPI_Initialize);
    __POWER_OVERWHELMING_GET_NVAPI_FUNC(NvAPI_Unload);
}

#undef __POWER_OVERWHELMING_GET_NVAPI_FUNC
