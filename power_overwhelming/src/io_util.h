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

#if defined(_WIN32)
#include <io.h>
#else /* defined(_WIN32) */
#include <unistd.h>
#include <sys/types.h>
#endif /* defined(_WIN32) */

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Possible start locations for seeking.
    /// </summary>
    enum class posix_seek_origin : int {

        /// <summary>
        /// Beginning of file.
        /// </summary>
        begin = SEEK_SET,

        /// <summary>
        /// Current position of file pointer.
        /// </summary>
        current = SEEK_CUR,

        /// <summary>
        /// End of file.
        /// </summary>
        end = SEEK_END
    };

    /// <summary>
    /// Opens a file using POSIX API.
    /// </summary>
    /// <param name="path"></param>
    /// <param name="flags"></param>
    /// <param name=""></param>
    /// <returns></returns>
    /// <exception cref="std::system_error"></exception>
    POWER_OVERWHELMING_API int open(_In_z_ const char *path,
        _In_ const int flags, _In_ const int mode = 0);

    /// <summary>
    /// Reads all bytes from the file designated by the given descriptor.
    /// </summary>
    /// <remarks>
    /// This function is only exported for testing.
    /// </remarks>
    /// <param name="fd"></param>
    /// <returns></returns>
    /// <exception cref="std::system_error"></exception>
    POWER_OVERWHELMING_API std::vector<std::uint8_t> read_all_bytes(
        _In_ const int fd);

    /// <summary>
    /// Reads exactly <paramref name="cnt" /> bytes or fails.
    /// </summary>
    /// <param name="fd"></param>
    /// <param name="dst"></param>
    /// <param name="cnt"></param>
    /// <returns></returns>
    POWER_OVERWHELMING_API void read_bytes(_In_ const int fd,
        _Out_writes_bytes_(cnt) void *dst, _In_ const std::size_t cnt);

    /// <summary>
    /// Seeks in a file.
    /// </summary>
    /// <param name="fd"></param>
    /// <param name="offset"></param>
    /// <param name="origin"></param>
    /// <returns></returns>
    /// <exception cref="std::system_error"></exception>
    POWER_OVERWHELMING_API std::streamoff seek(_In_ const int fd,
        _In_ const std::streamoff offset,
        _In_ const posix_seek_origin origin);


} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
