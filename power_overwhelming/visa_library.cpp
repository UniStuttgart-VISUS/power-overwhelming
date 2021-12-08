// <copyright file="visa_library.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "visa_library.h"

#include "on_exit.h"
#include "visa_exception.h"


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
    __POWER_OVERWHELMING_GET_VISA_FUNC(viFindNext);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viFindRsrc);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viGetAttribute);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viInstallHandler);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viOpen);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viOpenDefaultRM);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viPrintf);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viRead);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viReadSTB);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viSetAttribute);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viSetBuf);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viStatusDesc);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viUninstallHandler);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viWaitOnEvent);
    __POWER_OVERWHELMING_GET_VISA_FUNC(viWrite);
}


/*
 * visus::power_overwhelming::detail::visa_library::find_resource
 */
std::vector<std::string>
visus::power_overwhelming::detail::visa_library::find_resource(
        const char *expression) const {
    if (expression == nullptr) {
        throw std::invalid_argument("The search expression cannot be null.");
    }

    std::vector<std::string> retval;

#if defined(POWER_OVERWHELMING_WITH_VISA)
    ViUInt32 cnt = 0;
    ViChar desc[1024];
    ViFindList hFind;
    ViSession rm;

    {
        auto status = viOpenDefaultRM(&rm);
        if (status < VI_SUCCESS) {
            throw visa_exception(status, "Could not open resource manager.");
        }
    }
    auto gRm = on_exit([this, rm](void) { viClose(rm); });

    {
        auto status = viFindRsrc(rm, expression, &hFind, &cnt, desc);
        visa_exception::throw_on_error(status);
    }

    retval.reserve(cnt);
    retval.push_back(desc);

    while (true) {
        auto status = visa_library::instance().viFindNext(hFind, desc);

        if (status == VI_ERROR_RSRC_NFOUND) {
            break;
        } else {
            visa_exception::throw_on_error(status);
            retval.push_back(desc);
        }
    }
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

    return retval;
}
