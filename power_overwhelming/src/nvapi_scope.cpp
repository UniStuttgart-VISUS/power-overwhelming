// <copyright file="nvapi_scope.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_NVAPI)
#include "nvapi_scope.h"

#include "nvapi_error_category.h"
#include "nvapi_library.h"


/*
 * PWROWG_DETAIL_NAMESPACE::nvapi_scope::nvapi_scope
 */
PWROWG_DETAIL_NAMESPACE::nvapi_scope::nvapi_scope(void) {
    auto status = nvapi_library::instance().NvAPI_Initialize();
    throw_if_nvapi_failed(status);
}


/*
 * PWROWG_DETAIL_NAMESPACE::nvapi_scope::~nvapi_scope
 */
PWROWG_DETAIL_NAMESPACE::nvapi_scope::~nvapi_scope(void) {
    nvapi_library::instance().NvAPI_Unload();
}
#endif /* defined(POWER_OVERWHELMING_WITH_NVAPI) */
