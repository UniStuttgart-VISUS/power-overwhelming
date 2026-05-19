// <copyright file="igcl_library.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_IGCL_LIBRARY_H)
#define _PWROWG_IGCL_LIBRARY_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_IGCL)

#include <igcl_api.h>

#include "library_base.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

#define __POWER_OVERWHELMING_IGCL_FUNC(f) decltype(&::f) f = nullptr

/// <summary>
/// Wrapper for lazily loading the Intel Graphics Control Library.
/// </summary>
class PWROWG_TEST_API igcl_library final : library_base {

public:

    /// <summary>
    /// Gets the only instance of the class.
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    /// <exception cref="std::system_error">If the library could not
    /// be loaded, eg because the machine does not have an Intel GPU.
    /// </exception>
    static const igcl_library& instance(void);

    __POWER_OVERWHELMING_IGCL_FUNC(ctlClose);
    __POWER_OVERWHELMING_IGCL_FUNC(ctlInit);
    __POWER_OVERWHELMING_IGCL_FUNC(ctlPowerTelemetryGet);

private:

    igcl_library(void);

};

#undef __POWER_OVERWHELMING_IGCL_FUNC

PWROWG_DETAIL_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_IGCL) */
#endif /* !defined(_PWROWG_IGCL_LIBRARY_H) */
