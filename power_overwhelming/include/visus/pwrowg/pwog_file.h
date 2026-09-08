// <copyright file="pwog_file.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_PWOG_FILE_H)
#define _PWROWG_PWOG_FILE_H
#pragma once

#include <cinttypes>

#if defined(_WIN32)
#include <Windows.h>
#endif /* defined(_WIN32) */

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// RAII object for interacting with a binary file format identified by the
/// &quot;PWOG&quot; FOURCC.
/// </summary>
class POWER_OVERWHELMING_API pwog_file final {

public:

    /// <summary>
    /// The fourcc at the begin of each file.
    /// </summary>
    static constexpr const std::uint32_t fourcc = 'PWOG';

    /// <summary>
    /// Opens the specified file for writing.
    /// </summary>
    /// <param name="path">The path to the file to be written.</param>
    /// <param name="force">If <see langword="true"/>, an existing file will be
    /// overwritten, otherwise, the operation will fail if the file already
    /// exists.</param>
    /// <returns>An object representing the opened file.</returns>
    static pwog_file create(_In_z_ const wchar_t *path,
        _In_ const bool force = false);

    /// <summary>
    /// Opens the specified file for writing.
    /// </summary>
    /// <param name="path">The path to the file to be written.</param>
    /// <param name="force">If <see langword="true"/>, an existing file will be
    /// overwritten, otherwise, the operation will fail if the file already
    /// exists.</param>
    /// <returns>An object representing the opened file.</returns>
    static pwog_file create(_In_z_ const char *path,
        _In_ const bool force = false);

    /// <summary>
    /// Opens the specified file for reading.
    /// </summary>
    /// <param name="path">The path to the file to be read.</param>
    /// <returns>An object representing the file in case it exists and is a
    /// valid PWOG file.</returns>
    static pwog_file read(_In_z_ const wchar_t *path);

    /// <summary>
    /// Opens the specified file for reading.
    /// </summary>
    /// <param name="path">The path to the file to be read.</param>
    /// <returns>An object representing the file in case it exists and is a
    /// valid PWOG file.</returns>
    static pwog_file read(_In_z_ const char *path);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    pwog_file(void) noexcept;

    /// <summary>
    /// Initialise from move.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    pwog_file(_Inout_ pwog_file&& rhs) noexcept;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    inline ~pwog_file(void) noexcept {
        this->close();
    }

    /// <summary>
    /// Close the file.
    /// </summary>
    void close(void) noexcept;

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    pwog_file& operator =(_Inout_ pwog_file&& rhs) noexcept;

    /// <summary>
    /// Indicates whether the file handle is valid.
    /// </summary>
    /// <returns><see langword="true"/> if the file handle is valid,
    /// <see langword="false"/> otherwise.</returns>
    inline operator bool(void) const noexcept {
        return (this->_handle != invalid);
    }

private:

#if defined(_WIN32)
    typedef HANDLE handle_type;
#else /* defined(_WIN32 */
    typedef int handle_type;
#endif /* defined(_WIN32 */

#if defined(_WIN32)
    static constexpr auto invalid = INVALID_HANDLE_VALUE;
#else /* defined(_WIN32) */
    static constexpr auto invalid = -1;
#endif /* defined(_WIN32) */

    /// <summary>
    /// Reads the FOURCC, checks whether it is expected and whether the byte
    /// order is the native one (the latter is stored to <see cref="_swap" />.
    /// </summary>
    void check_fourcc(void);

    /// <summary>
    /// Reads the version number and checks whether it is supported.
    /// </summary>
    void check_version(void);

    /// <summary>
    /// Writes the FOURCC to the current location in the file.
    /// </summary>
    void write_fourcc(void);

    /// <summary>
    /// Writes the version of the file format to the current location in the
    /// file.
    /// </summary>
    void write_version(void);

    handle_type _handle;
    bool _swap;
    std::uint8_t _version[2];
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_PWOG_FILE_H) */
