﻿// <copyright file="api.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_API_H)
#define _PWROWG_API_H
#pragma once

#include "visus/pwrowg/macro_concat.h"


/******************************************************************************\
 * Update the ABI version (i.e. if something in the interface changes) here:  *
\******************************************************************************/
#define PWROWG_ABI_MAJOR 2
#define PWROWG_ABI_MINOR 0


/// <summary>
/// Creates the full ABI versison string.
/// </summary>
/// <param name="mj">The major version of the ABI.</param>
/// <param name="mn">The minor version of the ABI.</param>
#define PWROWG_ABI_VERSION(mj, mn) PWROWG_CONCAT(mj, PWROWG_CONCAT(_, mn))


/// <summary>
/// Creates the name of the namespace for the specified ABI version.
/// </summary>
/// <param name="mj">The major version of the ABI.</param>
/// <param name="mn">The minor version of the ABI.</param>
#define PWROWG_ABI_NAMESPACE(mj, mn) \
PWROWG_CONCAT(v, PWROWG_ABI_VERSION(mj, mn))


/// <summary>
/// Creates the name of the current ABI namespace.
/// </summary>
/// <remarks>
/// Use this macro when defining implementations in cpp or inline files.
/// </remarks>
#define PWROWG_NAMESPACE visus::pwrowg::\
PWROWG_ABI_NAMESPACE(PWROWG_ABI_MAJOR, PWROWG_ABI_MINOR)


/// <summary>
/// Creates the name of the namespace for the implementation details.
/// </summary>
/// <remarks>
/// Use this macro when defining implementations in cpp or inline files.
/// </remarks>
#define PWROWG_DETAIL_NAMESPACE PWROWG_NAMESPACE::detail


/// <summary>
/// Helper for opening the namespace <paramref name="n" />.
/// </summary>
#define _PWROWG_NAMESPACE_BEGIN(n) namespace n {


/// <summary>
/// Marks the begin of the current ABI namespace.
/// </summary>
#define PWROWG_NAMESPACE_BEGIN \
_PWROWG_NAMESPACE_BEGIN(visus)\
_PWROWG_NAMESPACE_BEGIN(pwrowg)\
inline _PWROWG_NAMESPACE_BEGIN(\
    PWROWG_ABI_NAMESPACE(PWROWG_ABI_MAJOR, PWROWG_ABI_MINOR))

/// <summary>
/// Marks the end of the current ABI namespace.
/// </summary>
#define PWROWG_NAMESPACE_END } } }

/// <summary>
/// Marks the begin of the namespace for implementation details.
/// </summary>
#define PWROWG_DETAIL_NAMESPACE_BEGIN \
PWROWG_NAMESPACE_BEGIN _PWROWG_NAMESPACE_BEGIN(detail)

/// <summary>
/// Marks the end of the namespace for implementation details.
/// </summary>
#define PWROWG_DETAIL_NAMESPACE_END } PWROWG_NAMESPACE_END


#if defined(_WIN32)

#if defined(POWER_OVERWHELMING_EXPORTS)
#define POWER_OVERWHELMING_API __declspec(dllexport)
#else /* defined(POWER_OVERWHELMING_EXPORTS) */
#define POWER_OVERWHELMING_API __declspec(dllimport)
#endif /* defined(POWER_OVERWHELMING_EXPORTS) */

#else /* defined(WIN32) */
#define POWER_OVERWHELMING_API

#endif /* defined(WIN32) */


/// <summary>
/// Marks an API as exported for testing only.
/// <summary>
#define PWROWG_TEST_API POWER_OVERWHELMING_API


#if defined(_WIN32)
#include <sal.h>
#else /* defined(_WIN32) */
#include "visus/pwrowg/nosal.h"
#endif /* defined(_WIN32) */

#endif /* !defined(_PWROWG_API_H) */
