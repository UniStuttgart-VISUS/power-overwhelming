// <copyright file="nvml_scope.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_NVML_SCOPE_H)
#define _PWROWG_NVML_SCOPE_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_NVML)

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A RAII container for the NVML library.
/// </summary>
/// <remarks>
/// As NVML uses an internal reference counter, multiple scopes can be used
/// by an application. NVML will not be unloaded unless the last scope was
/// destroyed.
/// </remarks>
class PWROWG_TEST_API nvml_scope final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <exception cref="nvml_exception">If the NVML could not be loaded.
    /// </exception>
    nvml_scope(void);

    nvml_scope(const nvml_scope&) = delete;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~nvml_scope(void);

    nvml_scope& operator =(const nvml_scope&) = delete;
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_NVML) */
#endif /* !defined(_PWROWG_NVML_SCOPE_H) */
