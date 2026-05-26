// <copyright file="trace.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TRACE_H)
#define _PWROWG_TRACE_H
#pragma once

#include <cstdio>
#include <cwchar>
#include <iostream>
#include <thread>
#include <vector>

#if defined(_WIN32)
#include <tchar.h>
#include <Windows.h>
#else /* defined(_WIN32) */
#if !defined(_T)
#define _T(x) x
#endif /* !defined(_T) */
#endif /* defined(_WIN32) */

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Helper class for debug tracing which keeps track of the location where the
/// trace was placed.
/// </summary>
class tracer final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="file">The file where the trace was written.</param>
    /// <param name="line">The line where the trace was written.</param>
    inline tracer(_In_z_ const char *const file, _In_ int line) noexcept
        : _file(file), _line(line) {}

    /// <summary>
    /// Outputs a formatted trace message to the debugger console.
    /// </summary>
    /// <typeparam name="TArguments">The types of the arguments to be formatted
    /// in the output.</typeparam>
    /// <param name="format">The printf-style format string.</param>
    /// <param name="arguments">The arguments to be formatted.</param>
    template<class... TArguments>
    void operator ()(_In_z_ const char *const format,
        TArguments&&... arguments) noexcept;

    /// <summary>
    /// Outputs a formatted trace message to the debugger console.
    /// </summary>
    /// <typeparam name="TArguments">The types of the arguments to be formatted
    /// in the output.</typeparam>
    /// <param name="format">The printf-style format string.</param>
    /// <param name="arguments">The arguments to be formatted.</param>
    template<class... TArguments>
    void operator ()(_In_z_ const wchar_t *const format,
        TArguments&&... arguments) noexcept;

private:

    const char *const _file;
    const int _line;
};

PWROWG_DETAIL_NAMESPACE_END


#if (defined(_DEBUG) || defined(DEBUG))
#define PWROWG_TRACE PWROWG_DETAIL_NAMESPACE::tracer(__FILE__, __LINE__)
#else /* (defined(_DEBUG) || defined(DEBUG)) */
#define PWROWG_TRACE(...)
#endif /* (defined(_DEBUG) || defined(DEBUG)) */


#include "visus/pwrowg/trace.inl"

#endif /* !defined(_PWROWG_TRACE_H) */
