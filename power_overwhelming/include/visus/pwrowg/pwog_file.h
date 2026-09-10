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

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/pwog_meta_data.h"
#include "visus/pwrowg/sample.h"
#include "visus/pwrowg/sensor_description.h"
#include "visus/pwrowg/type_erased_storage.h"


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

    /// <summary>
    /// Writes the specified meta data to the file. The file must be in the
    /// state to receive meta data, i.e. it must have been created for writing
    /// and only the header has been written so far.
    /// </summary>
    /// <typeparam name="TChar">The character type used for the meta-data. If
    /// this is <see langword="char" />, the text must be encoded in UTF-8.
    /// </typeparam>
    /// <param name="meta_data">The meta data to be written. The contents of
    /// this object must be valid until the method returns.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    /// <exception cref="std::logic_error">If the file is not in the expected
    /// state.</exception>
    template<class TChar>
    pwog_file& operator <<(_In_ const pwog_meta_data<TChar>& meta_data);

    /// <summary>
    /// Writes a sensor description to the file. The file must be in the state
    /// to receive meta data, in which case it will transition to the sensor
    /// description state, or in the sensor description state already.
    /// </summary>
    /// <remarks>
    /// Sensor descriptions must be written in-order as they will be referenced
    /// by their index in the file. You must write all descriptions from the
    /// sensor array producing the data to be stored in the order they are
    /// returned from the array.
    /// </remarks>
    /// <param name="sensor">The sensor description to be written.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    /// <exception cref="std::logic_error">If the file is not in the expected
    /// state.</exception>
    pwog_file& operator <<(_In_ const sensor_description& sensor);

    /// <summary>
    /// Writes a sample to the file. The file must be in the state to receive
    /// samples or in a state that can be transitioned to this state.
    /// </summary>
    /// <param name="sample">The sample to be written.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    /// <exception cref="std::logic_error">If the file is not in the expected
    /// state.</exception>
    pwog_file& operator <<(_In_ const sample& sample);

private:

#if defined(_WIN32)
    typedef HANDLE handle_type;
#else /* defined(_WIN32 */
    typedef int handle_type;
#endif /* defined(_WIN32 */

    /// <summary>
    /// Tracks the state of the file in write mode.
    /// </summary>
    enum class state {
        /// <summary>
        /// The file is open in read mode.
        /// </summary>
        read,

        /// <summary>
        /// The file writes the header. This comprises the FOURCC and the file
        /// version.
        /// </summary>
        header,

        /// <summary>
        /// The writer is writing the meta data block directly following the
        /// header.
        /// </summary>
        meta_data,

        /// <summary>
        /// The writer is writing the sensor descriptions following the
        /// user-defined meta data.
        /// </summary>
        sensors,

        /// <summary>
        /// The writer is writing samples following the sensor descriptions.
        /// </summary>
        samples
    };

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
    /// Initialises the file in the mode defined by <paramref name="state" />.
    /// </summary>
    void initialise(_In_ const handle_type handle, _In_ const state state);

    /// <summary>
    /// Reads the meta data block to <see cref="_meta_data" /> from the current
    /// location of the file pointer.
    /// </summary>
    void read_meta_data(void);

    /// <summary>
    /// Writes a null-terminated string to the file, including the terminating
    /// null character.
    /// </summary>
    void write(_In_opt_z_ const char *string);

    /// <summary>
    /// Writes a null-terminated string to the file, including the terminating
    /// null character.
    /// </summary>
    void write(_In_opt_z_ const wchar_t *string);

    handle_type _handle;
    type_erased_storage _meta_data;
    state _state;
    bool _swap;
    std::uint8_t _version[2];
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/pwog_file.inl"

#endif /* !defined(_PWROWG_PWOG_FILE_H) */
