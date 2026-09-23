// <copyright file="zero_adjust.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <chrono>

#if defined(_WIN32)
#include <Windows.h>
#include <tchar.h>
#endif /* defined(_WIN32) */


#include "visus/pwrowg/rtx_configuration.h"

/// <summary>
/// Performs a zero adjustment of all current channels in the given sensor
/// configuration.
/// </summary>
void zero_adjust(_In_z_ const TCHAR *path,
    _In_ const std::chrono::duration<float> range,
    _In_ const std::chrono::duration<float> degauss,
    _In_ const std::size_t retries,
    _In_ const bool no_wait,
    _In_ const bool apply);
