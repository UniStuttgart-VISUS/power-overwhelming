﻿// <copyright file="visa_library.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_VISA)
#include "visa_library.h"

#include "visus/pwrowg/on_exit.h"

#include "visa_error_category.h"

#define __POWER_OVERWHELMING_GET_VISA_FUNC(n) \
    this->n = this->get_function<decltype(this->n)>(#n)


/*
 * PWROWG_DETAIL_NAMESPACE::visa_library::instance
 */
const PWROWG_DETAIL_NAMESPACE::visa_library&
PWROWG_DETAIL_NAMESPACE::visa_library::instance(void) {
    static const visa_library instance;
    return instance;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_library::visa_library
 */
PWROWG_DETAIL_NAMESPACE::visa_library::visa_library(void)
#if defined(_WIN32)
        : library_base(TEXT("visa64.dll"), TEXT("visa32.dll")) {
#else /* defined(_WIN32) */
        : library_base("librsvisa.so") {
#endif /* defined(_WIN32) */
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
 * PWROWG_DETAIL_NAMESPACE::visa_library::find_resource
 */
std::vector<std::string>
PWROWG_DETAIL_NAMESPACE::visa_library::find_resource(
        const char *expression) const {
    if (expression == nullptr) {
        throw std::invalid_argument("The search expression cannot be null.");
    }

    std::vector<std::string> retval;

    ViUInt32 cnt = 0;
    ViChar desc[1024];
    ViFindList hFind;
    ViSession rm;

    {
        auto status = viOpenDefaultRM(&rm);
        throw_if_visa_failed(status, "Could not open resource manager.");
    }
    auto gRm = on_exit([this, rm](void) { viClose(rm); });

    {
        auto status = viFindRsrc(rm, expression, &hFind, &cnt, desc);
        throw_if_visa_failed(status);
    }

    retval.reserve(cnt);
    retval.push_back(desc);

    while (true) {
        auto status = visa_library::instance().viFindNext(hFind, desc);

        if (status == VI_ERROR_RSRC_NFOUND) {
            break;
        } else {
            throw_if_visa_failed(status);
            retval.push_back(desc);
        }
    }

    return retval;
}

#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
