// <copyright file="io.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_IO_UTIL_H)
#define _PWROWG_IO_UTIL_H
#pragma once

#include <cinttypes>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include <fcntl.h>

#if defined(_WIN32)
#include <Windows.h>
#include <io.h>
#else /* defined(_WIN32) */
#include <unistd.h>
#include <sys/types.h>
#endif /* defined(_WIN32) */

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

#if defined(_WIN32)
/// <summary>
/// Possible start locations for seeking.
/// </summary>
enum class win32_seek_origin : DWORD {

    /// <summary>
    /// Beginning of file.
    /// </summary>
    begin = FILE_BEGIN,

    /// <summary>
    /// Current position of file pointer.
    /// </summary>
    current = FILE_CURRENT,

    /// <summary>
    /// End of file.
    /// </summary>
    end = FILE_END
};
#endif /* defined(_WIN32) */

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

#if defined(_WIN32)
/// <summary>
/// Opens a native Win32 file handle.
/// </summary>
/// <remarks>
/// This function is only exported for testing.
/// </remarks>
/// <param name="path">The name of the file or device to be opened.</param>
/// <param name="desired_access">The requested access to the file or device.
/// Typically, this is one of <c>GENERIC_READ</c> or <c>GENERIC_WRITE</c>.
/// </param>
/// <param name="share_mode">The requested sharing mode.</param>
/// <param name="create_disposition">An action to take on a device or file
/// which exists or does not exist.</param>
/// <param name="flags">The file or device attribute flags.</param>
/// <returns>A handle for the opened file or device.</returns>
/// <exception cref="std::system_error">If opening the file or device
/// failed.</exception>
POWER_OVERWHELMING_API HANDLE open(_In_z_ const wchar_t *path,
    _In_ const DWORD desired_access,
    _In_ const DWORD share_mode,
    _In_ const DWORD create_disposition,
    _In_ const DWORD flags = FILE_ATTRIBUTE_NORMAL);
#endif /* defined(_WIN32) */

/// <summary>
/// Opens a file using POSIX API.
/// </summary>
/// <param name="path"></param>
/// <param name="flags"></param>
/// <param name="mode"></param>
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

#if defined(_WIN32)
/// <summary>
/// Reads all bytes from the file designated by the given descriptor.
/// </summary>
/// <remarks>
/// This function is only exported for testing.
/// </remarks>
/// <param name="handle"></param>
/// <returns></returns>
/// <exception cref="std::system_error"></exception>
POWER_OVERWHELMING_API std::vector<std::uint8_t> read_all_bytes(
    _In_ const HANDLE handle);
#endif /* defined(_WIN329 */

#if defined(_WIN32)
/// <summary>
/// Reads exactly <paramref name="cnt" /> bytes or fails.
/// </summary>
/// <param name="handle"></param>
/// <param name="dst"></param>
/// <param name="cnt"></param>
/// <returns></returns>
POWER_OVERWHELMING_API void read_bytes(_In_ const HANDLE handle,
    _Out_writes_bytes_(cnt) void *dst, _In_ const std::size_t cnt);
#endif /* defined(_WIN32) */

/// <summary>
/// Reads exactly <paramref name="cnt" /> bytes or fails.
/// </summary>
/// <remarks>
/// This function is only exported for testing.
/// </remarks>
/// <param name="fd"></param>
/// <param name="dst"></param>
/// <param name="cnt"></param>
/// <returns></returns>
POWER_OVERWHELMING_API void read_bytes(_In_ const int fd,
    _Out_writes_bytes_(cnt) void *dst, _In_ const std::size_t cnt);

#if defined(_WIN32)
/// <summary>
/// Seeks in a file.
/// </summary>
/// <remarks>
/// This function is only exported for testing.
/// </remarks>
/// <param name="handle">An open file handle.</param>
/// <param name="offset">The offset to seek in bytes.</param>
/// <param name="origin">The start of the seek operation.</param>
/// <returns>The new position of the file pointer.</returns>
/// <exception cref="std::system_error">If the operation failed.</exception>
POWER_OVERWHELMING_API std::streamoff seek(_In_ const HANDLE handle,
    _In_ const std::streamoff offset,
    _In_ const win32_seek_origin origin);
#endif /* defined(_WIN32) */

/// <summary>
/// Seeks in a file.
/// </summary>
/// <remarks>
/// This function is only exported for testing.
/// </remarks>
/// <param name="fd"></param>
/// <param name="offset"></param>
/// <param name="origin"></param>
/// <returns></returns>
/// <exception cref="std::system_error"></exception>
POWER_OVERWHELMING_API std::streamoff seek(_In_ const int fd,
    _In_ const std::streamoff offset,
    _In_ const posix_seek_origin origin);

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_IO_UTIL_H) */
