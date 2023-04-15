// <copyright file="io.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include <fcntl.h> 
#include <io.h>

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Reads all bytes from the file designated by the given descriptor.
    /// </summary>
    /// <remarks>
    /// This function is only exported for testing.
    /// </remarks>
    /// <param name="fd"></param>
    /// <returns></returns>
    POWER_OVERWHELMING_API std::vector<std::uint8_t> read_all_bytes(
        _In_ const int fd);


} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
