// <copyright file="handler_functions.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/handler_functions.h"


/*
 * PWROWG_NAMESPACE::detail::free_with_context
 */
void PWROWG_NAMESPACE::detail::free_with_context(_In_opt_ void *ptr) noexcept {
    operator delete(ptr);
}
