// <copyright file="string_functions.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_HANDLER_FUNCTIONS_H)
#define _PWROWG_HANDLER_FUNCTIONS_H
#pragma once

#include <cassert>
#include <cinttypes>
#include <cstdlib>
#include <type_traits>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Allocates <paramref name="size" /> untyped bytes and space for a
/// <typeparamref name="TContext" /> behind it and initialises the
/// <typeparamref name="TContext" />, but not the data before.
/// </summary>
/// <remarks>
/// <para>This function is only intended for implementing the allocation
/// operators of event handler adapter classes that translate C++ callables to
/// C function pointers.</para>
/// <para>If copying/moving the <paramref name="context" /> fails, the
/// allocation is also considered to have failed and any previously allocated
/// memory will be released immediately.</para>
/// </remarks>
/// <typeparam name="TContext">The type of the context to be allocated directly
/// after the requested allocation size.</typeparam>
/// <param name="size">The number of bytes to be allocated.</param>
/// <param name="context">The context type to be copied behind the allocated
/// bytes.</param>
/// <returns>A pointer to <paramref name="size" /> bytes of uninitialised data,
/// which must be released using <see cref="free_with_context" />.</returns>
template<class TContext>
void *allocate_with_context(_In_ const std::size_t size,
    _In_ TContext&& context);

/// <summary>
/// Releases memory from <see cref="allocate_with_context" />, but does not call
/// the destructor of the context. The caller must have destructed the context
/// before.
/// </summary>
/// <remarks>
/// <para>This function is only intended for implementing the allocation
/// operators of event handler adapter classes that translate C++ callables to
/// C function pointers.</para>
/// </remarks>
/// <param name="ptr">A pointer to a piece of memory allocated using
/// <see cref="allocate_with_context" />.</param>
void POWER_OVERWHELMING_API free_with_context(_In_opt_ void *ptr) noexcept;

PWROWG_DETAIL_NAMESPACE_END

#include "visus/pwrowg/handler_functions.inl"

#endif /* !defined(_PWROWG_HANDLER_FUNCTIONS_H) */
