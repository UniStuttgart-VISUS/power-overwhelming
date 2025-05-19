// <copyright file="adl_scope.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#if !defined(_PWROWG_ADL_SCOPE_H)
#define _PWROWG_ADL_SCOPE_H
#pragma once

#include <adl_sdk.h>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A RAII container for the ADL library.
/// </summary>
/// <remarks>
/// The implementation represents an ADL2 scope with a separate execution
/// context. APIs using the same scope should not be called concurrently.
/// </remarks>
class PWROWG_TEST_API adl_scope final {

public:

    /// <summary>
    /// Memory allocator passed to the ADL.
    /// </summary>
    /// <param name="cnt"></param>
    /// <returns></returns>
    static void *__stdcall allocate(int cnt);

    /// <summary>
    /// Deallocates memory that has been obtained from
    /// <see cref="allocate" />.
    /// </summary>
    /// <param name="buffer"></param>
    static void __stdcall deallocate(void **buffer);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <exception cref="adl_exception">If the ADL could not be loaded.
    /// </exception>
    adl_scope(void);

    adl_scope(const adl_scope&) = delete;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~adl_scope(void);

    adl_scope& operator =(const adl_scope&) = delete;

    /// <summary>
    /// Implicit conversion to the context handle represented by the scope.
    /// </summary>
    /// <returns>The context handle, which is guaranteed to be valid.
    /// </returns>
    inline operator ADL_CONTEXT_HANDLE(void) {
        return this->_handle;
    }

private:

    ADL_CONTEXT_HANDLE _handle;
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_ADL_SCOPE_H) */
