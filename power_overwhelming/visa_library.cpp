// <copyright file="visa_library.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "visa_library.h"


#if defined(POWER_OVERWHELMING_WITH_VISA)
#define __POWER_OVERWHELMING_GET_VISA_FUNC(n) \
    this->n = this->get_function<decltype(this->n)>(#n)
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
#define __POWER_OVERWHELMING_GET_VISA_FUNC(n)
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */


/*
 * visus::power_overwhelming::detail::visa_library::instance
 */
const visus::power_overwhelming::detail::visa_library&
visus::power_overwhelming::detail::visa_library::instance(void) {
    static const visa_library instance;
    return instance;
}


/*
 * visus::power_overwhelming::detail::visa_library::visa_library
 */
visus::power_overwhelming::detail::visa_library::visa_library(void)
        : library_base(TEXT("visa64.dll"), TEXT("visa32.dll")) {
    __POWER_OVERWHELMING_GET_VISA_FUNC(viClear);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viClose);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viDisableEvent);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viDiscardEvents);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viEnableEvent);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viGetAttribute);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viInstallHandler);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viOpen);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viOpenDefaultRM);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viRead);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viReadSTB);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viSetAttribute);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viStatusDesc);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viUninstallHandler);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viWaitOnEvent);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viWrite);
}
