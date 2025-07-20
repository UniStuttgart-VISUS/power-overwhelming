// <copyright file="nvapi_scope.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_NVAPI_SCOPE_H)
#define _PWROWG_NVAPI_SCOPE_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_NVAPI)

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A RAII container for the NVAPI library.
/// </summary>
/// <remarks>
/// As NVAPI uses an internal reference counter, multiple scopes can be used
/// by an application. NVAPI will not be unloaded unless the last scope was
/// destroyed.
/// </remarks>
class PWROWG_TEST_API nvapi_scope final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <exception cref="std::system_error">If the NVAPI could not be loaded.
    /// </exception>
    nvapi_scope(void);

    nvapi_scope(const nvapi_scope&) = delete;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~nvapi_scope(void);

    nvapi_scope& operator =(const nvapi_scope&) = delete;
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_NVAPI) */
#endif /* !defined(_PWROWG_NVAPI_SCOPE_H) */
