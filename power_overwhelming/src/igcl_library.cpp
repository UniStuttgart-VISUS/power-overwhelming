// <copyright file="igcl_library.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_IGCL)
#include "igcl_library.h"


#define __POWER_OVERWHELMING_IGCL_FUNC(f) \
    this->_##f = this->get_function<decltype(this->_##f)>(#f)


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
    __POWER_OVERWHELMING_IGCL_FUNC(ctlEnumerateDevices);
    __POWER_OVERWHELMING_IGCL_FUNC(ctlEnumPowerDomains);
    __POWER_OVERWHELMING_IGCL_FUNC(ctlGetDeviceProperties);
    __POWER_OVERWHELMING_IGCL_FUNC(ctlGetZeDevice);
    __POWER_OVERWHELMING_IGCL_FUNC(ctlInit);
    __POWER_OVERWHELMING_IGCL_FUNC(ctlPciGetProperties);
    __POWER_OVERWHELMING_IGCL_FUNC(ctlPowerGetProperties);
    __POWER_OVERWHELMING_IGCL_FUNC(ctlPowerGetEnergyCounter);
    __POWER_OVERWHELMING_IGCL_FUNC(ctlPowerGetLimits);
    __POWER_OVERWHELMING_IGCL_FUNC(ctlPowerTelemetryGet);
}

#undef __POWER_OVERWHELMING_IGCL_FUNC
#endif /* defined(POWER_OVERWHELMING_WITH_IGCL) */
