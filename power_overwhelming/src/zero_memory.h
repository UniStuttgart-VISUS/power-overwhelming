// <copyright file="zero_memory.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#if defined(_WIN32)
#include <Windows.h>

#else /* defined(_WIN32) */
#include <cstddef>
#include <cstring>


/// <summary>
/// Fills a block of memory with zeros.
/// </summary>
/// <param name="ptr">A pointer to the block that will be filled with zeros.
/// </param>
/// <param name="cnt">The size of the block to be filled with zeros in bytes.
/// </param>
inline void ZeroMemory(void *ptr, const std::size_t cnt) {
    ::memset(ptr, 0, cnt);
}

#endif /* defined(_WIN32) */

