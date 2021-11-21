// <copyright file="nvml_scope.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "nvml_scope.h"

#include "nvidia_management_library.h"
#include "nvml_exception.h"


/*
 * visus::power_overwhelming::nvml_scope::nvml_scope
 */
visus::power_overwhelming::nvml_scope::nvml_scope(void) {
    auto status = detail::nvidia_management_library::instance().nvmlInit();

    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }
}


/*
 * visus::power_overwhelming::nvml_scope::~nvml_scope
 */
visus::power_overwhelming::nvml_scope::~nvml_scope(void) {
    detail::nvidia_management_library::instance().nvmlShutdown();
}
