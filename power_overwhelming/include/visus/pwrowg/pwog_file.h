// <copyright file="pwog_file.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_PWOG_FILE_H)
#define _PWROWG_PWOG_FILE_H
#pragma once

#include <algorithm>
#include <iterator>
#include <memory>
#include <cinttypes>

#if defined(_WIN32)
#include <Windows.h>
#endif /* defined(_WIN32) */

#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/hdf5_configuration.h"
#include "visus/pwrowg/parquet_configuration.h"
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
    /// The FOURCC at the begin of each file.
    /// </summary>
    /// <remarks>
    /// The FOURCC prints &quot;PWOG&quot; in ASCII on little-endian systems.
    /// </remarks>
    static constexpr const std::uint32_t fourcc = 'GOWP';

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

#if defined(POWER_OVERWHELMING_WITH_HDF5)
    /// <summary>
    /// Converts the given <paramref name="file" /> to an HDF5 file.
    /// </summary>
    /// <param name="file">The PWOG file to be converted. This must have been
    /// opened for reading.</param>
    /// <param name="config">Configures the location and format of the HDF5
    /// file to be created.</param>
    /// <returns>The total number of samples that have been written into the
    /// HDF5 file.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="path" /> is
    /// <see langword="nullptr" />, or if <paramref name="file" /> is not in
    /// read mode, or if the specified <paramref name="identity" /> column
    /// is not supported (the latter is probably a bug).</exception>
    static std::size_t to_hdf5(_In_ const pwog_file& file,
        _In_ const hdf5_configuration& config);
#endif /* defined(POWER_OVERWHELMING_WITH_HDF5) */

#if defined(POWER_OVERWHELMING_WITH_PARQUET)
    /// <summary>
    /// Converts the given <paramref name="file" /> to an Apache Parquet file as
    /// decribed by the given <paramref name="config" />.
    /// </summary>
    /// <param name="file">The PWOG file to be converted. This must have been
    /// opened for reading.</param>
    /// <param name="config">Configures the location and format of the Parquet
    /// file to be created.</param>
    /// <param name="batch_size">The number of samples to read in one batch.
    /// </param>
    /// <returns>The total number of samples that have been written into the
    /// Parquet file.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="path" /> is
    /// <see langword="nullptr" />, or if <paramref name="file" /> is not in
    /// read mode, or if the specified <paramref name="identity" /> column
    /// is not supported (the latter is probably a bug).</exception>
    static std::size_t to_parquet(_In_ const pwog_file& file,
        _In_ const parquet_configuration& config,
        _In_ const std::size_t batch_size = 512);
#endif /* defined(POWER_OVERWHELMING_WITH_PARQUET) */

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
    /// Answer all meta data keys in the file, provided the file is in read
    /// mode.
    /// </summary>
    /// <param name="keys">A buffer to receive the keys of the meta data map
    /// in the file. This can be <see langword="nullptr" /> to determine the
    /// required buffer size. The object remains owner of the memory of the
    /// strings to which the pointers are returned.</param>
    /// <param name="cnt">The number of items that can be written to
    /// <paramref name="keys" />.</param>
    /// <returns>The number of meta data items in the file, regardless of
    /// whether anything has been copied to <paramref name="keys" /> or not.
    /// </returns>
    std::size_t meta_data(_Out_writes_opt_(cnt) const char **keys,
        _In_ std::size_t cnt) const;

    /// <summary>
    /// Reads at most <paramref name="cnt" /> samples from the file at the
    /// current reading position.
    /// </summary>
    /// <param name="samples">A buffer that can receive at least
    /// <paramref name="cnt" /> samples.</param>
    /// <param name="cnt">The number of samples that can be written to
    /// <paramref name="samples" />.</param>
    /// <returns>The number of samples read from the file, which may be less
    /// than <paramref name="cnt" /> if the end of the file is reached.
    /// </returns>
    std::size_t read(_Out_writes_(cnt) sample *samples,
        _In_ const std::size_t cnt) const;

    /// <summary>
    /// Reads at most <paramref name="cnt" /> samples from the file starting
    /// at the <paramref name="offset" />-th sample, thus resetting the file
    /// pointer.
    /// </summary>
    /// <remarks>
    /// The method will seek unconditionally to the specified offset (in read
    /// mode), even if nothing can be read.
    /// </remarks>
    /// <param name="offset">The offset in number of samples.</param>
    /// <param name="samples">A buffer that can receive at least
    /// <paramref name="cnt" /> samples.</param>
    /// <param name="cnt">The number of samples that can be written to
    /// <paramref name="samples" />.</param>
    /// <returns>The number of samples read from the file, which may be less
    /// than <paramref name="cnt" /> if the end of the file is reached.
    /// </returns>
    std::size_t read(_In_ const std::size_t offset,
        _Out_writes_(cnt) sample *samples,
        _In_ const std::size_t cnt) const;

    /// <summary>
    /// Answer all sensors the file, provided the file is in read mode.
    /// </summary>
    /// <param name="sensors">A buffer to receive a copy of the sensor
    /// descriptions. This can be <see langword="nullptr" /> to determine
    /// the required buffer size.</param>
    /// <param name="cnt">The number of sensors that can be written to
    /// <paramref name="sensors" />.</param>
    /// <returns>The number of sensors in the file, regardless of whether
    /// anything has been copied to <paramref name="sensors" /> or not.
    /// </returns>
    std::size_t sensors(_Out_writes_opt_(cnt) sensor_description *sensors,
        _In_ std::size_t cnt) const;

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
    pwog_file& write(_In_ const pwog_meta_data<TChar>& meta_data);

    /// <summary>
    /// Writes the given sensor descriptions to the file. The file must be in
    /// the state to receive meta data, in which case it will transition to the
    /// sensor description state, or in the sensor description state already.
    /// </summary>
    /// <remarks>
    /// Sensor descriptions must be written in-order as they will be referenced
    /// by their index in the file. You must write all descriptions from the
    /// sensor array producing the data to be stored in the order they are
    /// returned from the array.
    /// </remarks>
    /// <param name="sensors">An array of <paramref name="cnt" /> sensor
    /// descriptions to be written.</param>
    /// <param name="cnt">The number of sensor descriptions in
    /// <paramref name="sensors" />.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    /// <exception cref="std::logic_error">If the file is not in the expected
    /// state.</exception>
    pwog_file& write(_In_reads_(cnt) const sensor_description *sensors,
        _In_ std::size_t cnt);

    /// <summary>
    /// Writes the given samples to the file. The file must be in the state to
    /// receive samples or in a state that can be transitioned to this state.
    /// </summary>
    /// <param name="samples">An array of <paramref name="cnt" /> samples to be
    /// written.</param>
    /// <param name="cnt">The number of <paramref name="samples" />.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    /// <exception cref="std::logic_error">If the file is not in the expected
    /// state.</exception>
    pwog_file& write(_In_reads_(cnt) const sample* samples,
        _In_ std::size_t cnt);

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
    inline pwog_file& operator <<(_In_ const pwog_meta_data<TChar>& meta_data) {
        return this->write(meta_data);
    }

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
    inline pwog_file& operator <<(_In_ const sensor_description& sensor) {
        return this->write(&sensor, 1);
    }

    /// <summary>
    /// Writes a sample to the file. The file must be in the state to receive
    /// samples or in a state that can be transitioned to this state.
    /// </summary>
    /// <param name="sample">The sample to be written.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    /// <exception cref="std::logic_error">If the file is not in the expected
    /// state.</exception>
    inline pwog_file& operator <<(_In_ const sample& sample) {
        return this->write(&sample, 1);
    }

    /// <summary>
    /// Answer, if available, the meta datum with the specified key.
    /// </summary>
    /// <remarks>
    /// This operator will always return <see langword="nullptr" /> for files in
    /// write mode.
    /// </remarks>
    /// <param name="key">The meta data key to retrieve.</param>
    /// <returns>A pointer to the meta datum, or <see langword="nullptr" />
    /// if that item does not exist. The object remains owner of the memory.
    /// </returns>
    _Ret_maybenull_z_ const char *operator [](
        _In_ const char *key) const noexcept;

    /// <summary>
    /// Answer, if available, the sensor description at the specified index.
    /// </summary>
    /// <remarks>
    /// This operator will always return <see langword="nullptr" /> for files in
    /// write mode.
    /// </remarks>
    /// <param name="index">The zero-based index of the sensor to retrieve the
    /// ID for.</param>
    /// <returns>A pointer to the sensor description, or
    /// <see langword="nullptr" /> if that item does not exist. The object
    /// remains owner of the memory.</returns>
    _Ret_maybenull_ const sensor_description *operator [](
        _In_ const int index) const noexcept;

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
    /// Reds the sensor descriptors from the current location of the file pointer
    /// to <see cref="_sensors" />.
    /// </summary>
    void read_sensors(void);

    /// <summary>
    /// If indicated by <see cref="_swap" />, swaps the byte order of the given
    /// value.
    /// </summary>
    template<class TType> void swap(_Inout_ TType& value) const noexcept;

    /// <summary>
    /// If indicated by <see cref="_swap" />, swaps the byte order of the given
    /// array.
    /// </summary>
    template<std::size_t N>
    void swap(_Inout_ std::uint8_t(&value)[N]) const noexcept;

    /// <summary>
    /// If indicated by <see cref="_swap" />, swaps the byte order of the given
    /// <paramref name="value" />.
    /// </summary>
    void swap(_Inout_ timestamp& value) const noexcept;

    /// <summary>
    /// If indicated by <see cref="_swap" />, swaps the byte order of the fields
    /// in the given <paramref name="value" />.
    /// </summary>
    inline void swap(_Inout_ sample& value) const noexcept {
        this->swap(value.timestamp);
        this->swap(value.source);
        this->swap(value.reading.bytes);
    }

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

    std::size_t _data;
    handle_type _handle;
    type_erased_storage _meta_data;
    type_erased_storage _sensors;
    state _state;
    bool _swap;
    std::uint8_t _version[2];
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/pwog_file.inl"

#endif /* !defined(_PWROWG_PWOG_FILE_H) */
