// <copyright file="igcl_library.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_IGCL)
#include "igcl_library.h"


#define __POWER_OVERWHELMING_IGCL_FUNC(n) \
    this->n = this->get_function<decltype(this->n)>(#n)


/*
 * PWROWG_DETAIL_NAMESPACE::igcl_library::instance
 */
const PWROWG_DETAIL_NAMESPACE::igcl_library&
PWROWG_DETAIL_NAMESPACE::igcl_library::instance(void) {
    static const igcl_library instance;
    return instance;
}


/*
 * PWROWG_DETAIL_NAMESPACE::igcl_library
 */
PWROWG_DETAIL_NAMESPACE::igcl_library::igcl_library(void)
        : library_base(TEXT("ControlLib.dll"), TEXT("ControlLib32.dll")) {
    __POWER_OVERWHELMING_IGCL_FUNC(ctlClose);
    __POWER_OVERWHELMING_IGCL_FUNC(ctlInit);
    __POWER_OVERWHELMING_IGCL_FUNC(ctlPowerTelemetryGet);
}

#undef __POWER_OVERWHELMING_IGCL_FUNC
#endif /* defined(POWER_OVERWHELMING_WITH_IGCL) */
