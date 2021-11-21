// <copyright file="nvml_scope.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2021 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#include "nvml_scope.h"

#include "nvidia_management_library.h"
#include "nvml_exception.h"


/*
 * visus::power_overwhelming::nvml_scope::nvml_scope
 */
visus::power_overwhelming::nvml_scope::nvml_scope(void) : _abandoned(false) {
    auto status = detail::nvidia_management_library::instance().nvmlInit();

    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }
}


/*
 * visus::power_overwhelming::nvml_scope::~nvml_scope
 */
visus::power_overwhelming::nvml_scope::~nvml_scope(void) {
    if (!this->_abandoned) {
        detail::nvidia_management_library::instance().nvmlShutdown();
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
