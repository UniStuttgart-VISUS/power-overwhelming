// <copyright file="nvml_scope.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "nvml_scope.h"

#if defined(POWER_OVERWHELMING_WITH_NVML)
#include "nvml_exception.h"


/*
 * visus::power_overwhelming::nvml_scope::nvml_scope
 */
visus::power_overwhelming::nvml_scope::nvml_scope(void) : _abandoned(false) {
    auto status = ::nvmlInit();

    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }
}


/*
 * visus::power_overwhelming::nvml_scope::~nvml_scope
 */
visus::power_overwhelming::nvml_scope::~nvml_scope(void) {
    if (!this->_abandoned) {
        ::nvmlShutdown();
    }
}


/*
 * visus::power_overwhelming::nvml_scope::operator =
 */
visus::power_overwhelming::nvml_scope&
visus::power_overwhelming::nvml_scope::operator =(nvml_scope&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_abandoned = rhs._abandoned;  // 'rhs' might already be abandoned.
        rhs._abandoned = true;              // 'rhs' is now surely abandoned.
    }

    return *this;
}
#endif /* defined(POWER_OVERWHELMING_WITH_NVML) */
