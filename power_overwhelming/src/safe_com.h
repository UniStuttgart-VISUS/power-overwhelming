// <copyright file="safe_com.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SAFE_COM_H)
#define _PWROWG_SAFE_COM_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Increments the reference count if <paramref name="ptr" /> is not
/// <c>nullptr</c>.
/// </summary>
/// <typeparam name="TPointer">The type of the pointer.</typeparam>
/// <param name="ptr">The pointer to increment the reference count of.
/// </param>
template<class TPointer> inline void safe_add_ref(TPointer *ptr) noexcept {
    if (ptr != nullptr) {
        ptr->AddRef();
    }
}

/// <summary>
/// Moves the reference from <paramref name="src" /> to
/// <paramref name="dst" />, making sure to release <paramref name="dst" />
/// before the assignment.
/// </summary>
/// <remarks>
/// This function must not be used if <paramref name="dst" /> and
/// <paramref name="src" /> refer to the same object. Albeit the function
/// checks the pointer identity, this might not be enough if using some
/// COM constructs.
/// </remarks>
/// <typeparam name="TPointer">The type of the pointer.</typeparam>
/// <param name="dst">The target variable, which will be released before
/// assigning <paramref name="src" />.</param>
/// <param name="src">The source variable, which will be moved and set to
/// <c>nullptr</c>.</param>
template<class TPointer>
inline void safe_move(TPointer *& dst, TPointer *&& src) noexcept {
    if (dst != src) {
        if (dst != nullptr) {
            dst->Release();
        }

        dst = src;
        src = nullptr;
    }
}

/// <summary>
/// Releases <paramref name="ptr" /> if it is not <c>nullptr</c>.
/// </summary>
/// <typeparam name="TPointer">The type of the pointer.</typeparam>
/// <param name="ptr">A reference to the pointer to be released.</param>
template<class TPointer>
inline void safe_release(TPointer *& ptr) noexcept {
    if (ptr != nullptr) {
        ptr->Release();
        ptr = nullptr;
    }
}

/// <summary>
/// Safely replaces <paramref name="dst" /> with <paramref name="src" />
/// making sure that the reference count is correctly set and no invalid
/// pointers are accessed.
/// </summary>
/// <typeparam name="TPointer">The type of the pointer.</typeparam>
/// <param name="dst">The target variable, which will be released before
/// assigning <paramref name="src" />.</param>
/// <param name="src">The source variable, which to a reference is added.
/// </param>
template<class TPointer>
inline void safe_replace(TPointer *&dst, TPointer *src) noexcept {
    // Add a reference to 'src' before releasing 'dst', because this
    // could be the same pointer.
    safe_add_ref(src);

    if (dst != nullptr) {
        dst->Release();
    }

    dst = src;
}

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SAFE_COM_H) */
