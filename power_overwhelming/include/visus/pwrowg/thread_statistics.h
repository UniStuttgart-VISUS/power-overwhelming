// <copyright file="thread_statistics.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_THREAD_STATISTICS_H)
#define _PWROWG_THREAD_STATISTICS_H
#pragma once

#include <cstdlib>

#if defined(_WIN32)
#include <Windows.h>
#endif /* defined(_WIN32) */

#include "visus/pwrowg/api.h"
#include "visus/pwrowg/unique_variable.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A RAII class that will log statistics of the thread from which the
/// destructor is called.
/// </summary>
class POWER_OVERWHELMING_API thread_statistics final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="path">The path to the file where the statistics will be
    /// stored.</param>
    thread_statistics(_In_z_ const wchar_t *path);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="path">The path to the file where the statistics will be
    /// stored.</param>
    thread_statistics(_In_z_ const char *path);

    thread_statistics(const thread_statistics&) = delete;

    /// <summary>
    /// Finalises the instance logs the statistics to the file specified at
    /// construction time.
    /// </summary>
    ~thread_statistics(void) noexcept;

    thread_statistics operator =(const thread_statistics&) = delete;

private:

    void write(_In_z_ const char *text);

    void write(_In_reads_(cnt) const char *text, _In_ const std::size_t cnt);

#if defined(_WIN32)
    typedef HANDLE handle;
#else /* defined(_WIN32) */
    typedef int handle;
#endif /* defined(_WIN32) */

    handle _handle;
};

PWROWG_NAMESPACE_END

/// <summary>
/// Creates an instance of <see cref="thread_statistics" /> which will log
/// statistics of the thread running its destructor to a file at the specified
/// location.
/// </summary>
#define PWROWG_THREAD_STATS(path) PWROWG_NAMESPACE::thread_statistics\
    PWROWG_UNIQUE_VARIABLE(__pwrowgthrdstat)(path)

#endif /* !defined(_PWROWG_THREAD_STATISTICS_H) */
