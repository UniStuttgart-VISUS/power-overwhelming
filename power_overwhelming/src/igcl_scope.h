// <copyright file="igcl_scope.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_IGCL_SCOPE_H)
#define _PWROWG_IGCL_SCOPE_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_IGCL)

#include <igcl_api.h>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A RAII container for the Intel Graphics Control Library.
/// </summary>
class PWROWG_TEST_API igcl_scope final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <exception cref="nvml_exception">If the NVML could not be loaded.
    /// </exception>
    igcl_scope(void);

    igcl_scope(const igcl_scope&) = delete;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~igcl_scope(void);

    igcl_scope& operator =(const igcl_scope&) = delete;

    /// <summary>
    /// Exposes the initialisation arguments provided by the library.
    /// </summary>
    /// <returns></returns>
    inline operator const ctl_init_args_t&(void) const noexcept {
        return this->_args;
    }

    /// <summary>
    /// Exposes the native library handle.
    /// </summary>
    /// <returns></returns>
    inline operator ctl_api_handle_t(void) const noexcept {
        return this->_handle;
    }

private:

    ctl_init_args_t _args;
    ctl_api_handle_t _handle;
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_IGCL) */
#endif /* !defined(_PWROWG_IGCL_SCOPE_H) */
