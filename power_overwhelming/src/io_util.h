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
#include <memory>
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

/// <summary>
/// The type of the seek origin for platform-native file handles.
/// </summary>
#if defined(_WIN32)
typedef win32_seek_origin native_seek_origin;
#else /* defined(_WIN32) */
typedef posix_seek_origin native_seek_origin;
#endif /* defined(_WIN32) */

/// <summary>
/// Answer the the of the file designated by the given descriptor.
/// </summary>
/// <param name="fd">A file descriptor.</param>
/// <returns>The size of the file, in bytes.</returns>
PWROWG_TEST_API std::size_t file_size(_In_ const int fd);

#if defined(_WIN32)
/// <summary>
/// Answer the the of the file designated by the given handle.
/// </summary>
/// <param name="handle">A file handle.</param>
/// <returns>The size of the file, in bytes.</returns>
PWROWG_TEST_API std::size_t file_size(_In_ const HANDLE handle);
#endif /* defined(_WIN32) */

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
PWROWG_TEST_API HANDLE open(_In_z_ const wchar_t *path,
    _In_ const DWORD desired_access,
    _In_ const DWORD share_mode,
    _In_ const DWORD create_disposition,
    _In_ const DWORD flags = FILE_ATTRIBUTE_NORMAL);
#endif /* defined(_WIN32) */

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
PWROWG_TEST_API HANDLE open(_In_z_ const char *path,
    _In_ const DWORD desired_access,
    _In_ const DWORD share_mode,
    _In_ const DWORD create_disposition,
    _In_ const DWORD flags = FILE_ATTRIBUTE_NORMAL);
#endif /* defined(_WIN32) */

#if defined(_WIN32)
/// <summary>
/// Opens a native Win32 file handle and wraps it in a unique pointer with a
/// custom deleter.
/// </summary>
/// <typeparam name="TChar">The character type of the path string.</typeparam>
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
template<class TChar>
std::unique_ptr<std::remove_pointer_t<HANDLE>, decltype(&::CloseHandle)>
open_unique(_In_z_ const TChar *path,
        _In_ const DWORD desired_access,
        _In_ const DWORD share_mode,
        _In_ const DWORD create_disposition,
        _In_ const DWORD flags = FILE_ATTRIBUTE_NORMAL) {
    typedef std::unique_ptr<std::remove_pointer_t<HANDLE>,
        decltype(&::CloseHandle)> return_type;
    return return_type(
        open(path, desired_access, share_mode, create_disposition, flags),
        &::CloseHandle);
}
#endif /* defined(_WIN32) */

/// <summary>
/// Opens a file using POSIX API.
/// </summary>
/// <param name="path"></param>
/// <param name="flags"></param>
/// <param name="mode"></param>
/// <returns></returns>
/// <exception cref="std::system_error"></exception>
PWROWG_TEST_API int open(_In_z_ const wchar_t *path,
    _In_ const int flags, _In_ const int mode = 0);

/// <summary>
/// Opens a file using POSIX API.
/// </summary>
/// <param name="path"></param>
/// <param name="flags"></param>
/// <param name="mode"></param>
/// <returns></returns>
/// <exception cref="std::system_error"></exception>
PWROWG_TEST_API int open(_In_z_ const char *path,
    _In_ const int flags, _In_ const int mode = 0);

/// <summary>
/// Opens a file using POSIX API.
/// </summary>
/// <typeparam name="TChar">The character type of the path string.</typeparam>
/// <param name="path">The name of the file or device to be opened.</param>
/// <param name="flags"></param>
/// <param name="mode"></param>
/// <returns>A handle for the opened file or device.</returns>
/// <exception cref="std::system_error">If opening the file or device
/// failed.</exception>
template<class TChar> std::unique_ptr<int, decltype(&::close)> open_unique(
        _In_z_ const TChar *path,
        _In_ const int flags,
        _In_ const int mode = 0) {
    typedef std::unique_ptr<int, decltype(&::close)> return_type;
    return return_type(open(path, flags, mode), &::close);
}

/// <summary>
/// Reads all bytes from the file designated by the given descriptor.
/// </summary>
/// <remarks>
/// This function is only exported for testing.
/// </remarks>
/// <param name="fd"></param>
/// <returns></returns>
/// <exception cref="std::system_error"></exception>
PWROWG_TEST_API std::vector<std::uint8_t> read_all_bytes(
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
PWROWG_TEST_API std::vector<std::uint8_t> read_all_bytes(
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
PWROWG_TEST_API void read_bytes(_In_ const HANDLE handle,
    _Out_writes_bytes_all_(cnt) void *dst, _In_ const std::size_t cnt);
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
PWROWG_TEST_API void read_bytes(_In_ const int fd,
    _Out_writes_bytes_all_(cnt) void *dst, _In_ const std::size_t cnt);

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
PWROWG_TEST_API std::streamoff seek(_In_ const int fd,
    _In_ const std::streamoff offset,
    _In_ const posix_seek_origin origin);

#if defined(_WIN32)
/// <summary>
/// Answer the current position in the file.
/// </summary>
/// <param name="handle"></param>
/// <returns></returns>
/// <exception cref="std::system_error"></exception>
PWROWG_TEST_API std::size_t tell(_In_ const HANDLE handle);
#endif /* defined(_WIN32) */

/// <summary>
/// Answer the current position in the file.
/// </summary>
/// <param name="fd"></param>
/// <returns></returns>
/// <exception cref="std::system_error"></exception>
PWROWG_TEST_API std::size_t tell(_In_ const int fd);

#if defined(_WIN32)
/// <summary>
/// Reads at most <paramref name="cnt" /> bytes.
/// </summary>
/// <remarks>
/// This function is only exported for testing.
/// </remarks>
/// <param name="handle"></param>
/// <param name="dst"></param>
/// <param name="cnt"></param>
/// <returns>The number of bytes actually read.</returns>
/// <exception cref="std::system_error">If the read failed.</exception>
PWROWG_TEST_API std::size_t try_read_bytes(_In_ const HANDLE handle,
    _Out_writes_bytes_(cnt) void *dst, _In_ const std::size_t cnt);
#endif /* defined(_WIN32) */

/// <summary>
/// Reads at most <paramref name="cnt" /> bytes.
/// </summary>
/// <remarks>
/// This function is only exported for testing.
/// </remarks>
/// <param name="fd"></param>
/// <param name="dst"></param>
/// <param name="cnt"></param>
/// <returns>The number of bytes actually read.</returns>
/// <exception cref="std::system_error">If the read failed.</exception>
PWROWG_TEST_API std::size_t try_read_bytes(_In_ const int fd,
    _Out_writes_bytes_(cnt) void *dst, _In_ const std::size_t cnt);

/// <summary>
/// Reads a most the available memory in the given <paramref name="buffer" />
/// starting at <paramref name="offset" />.
/// </summary>
/// <typeparam name="THandle"></typeparam>
/// <typeparam name="TElement"></typeparam>
/// <param name="handle"></param>
/// <param name="buffer"></param>
/// <param name="offset"></param>
/// <returns>The number of bytes actually read.</returns>
/// <exception cref="std::system_error">If the read failed.</exception>
template<class THandle, class TElement> inline std::size_t try_read(
        _In_ const THandle handle,
        _In_ std::vector<TElement>& buffer,
        _In_ const std::size_t offset = 0) {
    assert(offset < buffer.size());
    const auto size = (buffer.size() - offset) * sizeof(TElement);
    return try_read_bytes(handle, buffer.data() + offset, size);
}

/// <summary>
/// Reads at most <paramref name="cnt" /> bytes.
/// </summary>
/// <remarks>
/// This function is only exported for testing.
/// </remarks>
/// <param name="fd"></param>
/// <param name="dst"></param>
/// <param name="cnt"></param>
/// <returns></returns>
/// <exception cref="std::system_error">If the read failed.</exception>
POWER_OVERWHELMING_API std::size_t try_read_bytes(_In_ const int fd,
    _Out_writes_bytes_(cnt) void *dst, _In_ const std::size_t cnt);

#if defined(_WIN32)
/// <summary>
/// Writes exactly <paramref name="cnt" /> bytes or fails.
/// </summary>
/// <param name="handle"></param>
/// <param name="src"></param>
/// <param name="cnt"></param>
/// <returns></returns>
PWROWG_TEST_API void write_all_bytes(_In_ const HANDLE handle,
    _In_reads_bytes_(cnt) const void *src, _In_ std::size_t cnt);
#endif /* defined(_WIN32) */

/// <summary>
/// Writes exactly <paramref name="cnt" /> bytes or fails.
/// </summary>
/// <remarks>
/// This function is only exported for testing.
/// </remarks>
/// <param name="fd"></param>
/// <param name="src"></param>
/// <param name="cnt"></param>
/// <returns></returns>
PWROWG_TEST_API void write_all_bytes(_In_ const int fd,
    _In_reads_bytes_(cnt) const void *src, _In_ std::size_t cnt);

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_IO_UTIL_H) */
