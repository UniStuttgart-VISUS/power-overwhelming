// <copyright file="unique_lock.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_UNIQUE_LOCK_H)
#define _PWROWG_UNIQUE_LOCK_H
#pragma once

#include "visus/pwrowg/unique_variable.h"

#include <mutex>


/// <summary>
/// Declares a unique lock variable named <paramref name="n"/> for
/// <paramref name="l"/>.
/// </summary>
#define PWROWG_NAMED_UNIQUE_LOCK(n, l) std::unique_lock<decltype(l)> n(l)

/// <summary>
/// Declares a unique lock variable for <paramref name="l"/>.
/// </summary>
#define PWROWG_UNIQUE_LOCK(l) PWROWG_NAMED_UNIQUE_LOCK(\
PWROWG_UNIQUE_VARIABLE(__ul), l)

#endif /* !defined(_PWROWG_UNIQUE_LOCK_H) */
