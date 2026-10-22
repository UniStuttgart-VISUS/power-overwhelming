// <copyright file="amd_display_library.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_AMD_DEVICE_LIBRARY_EXTRA_H)
#define _PWROWG_AMD_DEVICE_LIBRARY_EXTRA_H
#pragma once

#if defined(POWER_OVERWHELMING_WITH_ADLX)

#include <memory>
#include <utility>

#include <ADLX.h>

#include "library_base.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

typedef ADLXInitialize_Fn ADLXInitializeWithIncompatibleDriver_Fn;
typedef ADLXInitialize2_Fn ADLXInitializeWithIncompatibleDriver2_Fn;


#define __POWER_OVERWHELMING_ADLX_FUNC(f, r) f##_Fn _##f = nullptr


/// <summary>
/// Wrapper for dynamically loading the AMD Device Library eXtra.
/// </summary>
class PWROWG_TEST_API amd_device_library_extra final : public library_base {

public:

    /// <summary>
    /// Gets the only instance of the class.
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    /// <exception cref="std::system_error">If the library could not
    /// be loaded, eg because the machine does not have an AMD GPU.
    /// </exception>
    static const amd_device_library_extra& instance(void);

    __POWER_OVERWHELMING_ADLX_FUNC(ADLXQueryFullVersion, true);
    __POWER_OVERWHELMING_ADLX_FUNC(ADLXQueryVersion, true);
    __POWER_OVERWHELMING_ADLX_FUNC(ADLXInitializeWithCallerAdl, true);
    __POWER_OVERWHELMING_ADLX_FUNC(ADLXInitialize, false);
    __POWER_OVERWHELMING_ADLX_FUNC(ADLXInitializeWithIncompatibleDriver, false);
    __POWER_OVERWHELMING_ADLX_FUNC(ADLXInitialize2, false);
    __POWER_OVERWHELMING_ADLX_FUNC(ADLXInitializeWithIncompatibleDriver2, false);
    __POWER_OVERWHELMING_ADLX_FUNC(ADLXTerminate, true);

private:

    /// <summary>
    /// Initialise a new instance.
    /// </summary>
    amd_device_library_extra(void);
};

#undef __POWER_OVERWHELMING_ADLX_FUNC

PWROWG_DETAIL_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_ADLX) */
#endif /* !defined(_PWROWG_AMD_DEVICE_LIBRARY_EXTRA_H) */
