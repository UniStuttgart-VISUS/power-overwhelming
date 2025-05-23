﻿// <copyright file="hmc8015_instrument.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_HMC8015_INSTRUMENT_H)
#define _PWROWG_HMC8015_INSTRUMENT_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_VISA)

#include <array>
#include <cinttypes>
#include <climits>
#include <cstddef>
#include <cstdint>

#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/hmc8015_function.h"
#include "visus/pwrowg/hmc8015_integrator_mode.h"
#include "visus/pwrowg/hmc8015_instrument_range.h"
#include "visus/pwrowg/hmc8015_log_mode.h"
#include "visus/pwrowg/visa_instrument.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Allows for controlling a Rohde &amp; Schwarz HMC8015 power analyser.
/// </summary>
class POWER_OVERWHELMING_API hmc8015_instrument final : public visa_instrument {

public:

    /// <summary>
    /// Create sensor objects for all Rohde &amp; Schwarz HMC8015
    /// instruments that can be enumerated via VISA.
    /// </summary>
    /// <param name="dst">An array receiving the sensors. If this is
    /// <c>nullptr</c>, nothing is returned.</param>
    /// <param name="cnt">The number of sensors that can be stored in
    /// <paramref name="cnt" />.</param>
    /// <param name="timeout">The timeout in milliseconds for establishing a
    /// connection to each instrument that was found. This parameter defaults
    /// to 3000.</param>
    /// <returns>The number of HMC8015 instruments found, regardless of how
    /// many have been returned to <paramref name="out_sensors" />.</returns>
    static std::size_t for_all(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) hmc8015_instrument *dst,
        _In_ std::size_t cnt,
        _In_ const std::int32_t timeout = 3000);

    /// <summary>
    /// The directory used on the front USB drive for storing log files.
    /// </summary>
    static constexpr const char *ext_log_directory = "DATA/";

    /// <summary>
    /// The file name extension of the log file.
    /// </summary>
    static constexpr const char *log_extension = ".CSV";

    /// <summary>
    /// The product ID of the HMC8015.
    /// </summary>
    /// <remarks>
    /// This is the ID reported by the device we use at VISUS. If this does
    /// not work, use the RsVisaTester tool and discover the device via the
    /// &quot;Find Resource&quot; functionality.
    /// </remarks>
    static constexpr const char *product_id = "0x0135";

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    hmc8015_instrument(void) = default;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="path">The path to the sensor</param>
    /// <param name="timeout">The timeout in milliseconds for connecting to
    /// the sensor.</param>
    /// <exception cref="std::invalid_argument">If <paramref name="path" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="std::bad_alloc">If the memory for the sensor state
    /// could not be allocated.</exception>
    /// <exception cref="std::system_error">If the VISA library could not be
    /// loaded.</exception>
    /// <exception cref="visa_exception">If the sensor could not be
    /// initialised.</exception>
    hmc8015_instrument(_In_z_ const wchar_t *path,
        _In_ const visa_instrument::timeout_type timeout);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="path">The path to the sensor</param>
    /// <param name="timeout">The timeout in milliseconds for connecting to
    /// the sensor.</param>
    /// <exception cref="std::invalid_argument">If <paramref name="path" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="std::bad_alloc">If the memory for the sensor state
    /// could not be allocated.</exception>
    /// <exception cref="std::system_error">If the VISA library could not be
    /// loaded.</exception>
    /// <exception cref="visa_exception">If the sensor could not be
    /// initialised.</exception>
    hmc8015_instrument(_In_z_ const char *path,
        _In_ const visa_instrument::timeout_type timeout);

    /// <summary>
    /// Move <paramref name="rhs" /> into a new instance.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    hmc8015_instrument(_Inout_ hmc8015_instrument&& rhs) noexcept;

    /// <summary>
    /// Finalise the instance.
    /// </summary>
    ~hmc8015_instrument(void);

    /// <summary>
    /// Enumerates all files in internal memory and deletes them.
    /// </summary>
    void clear_internal_memory(void);

    /// <summary>
    /// Reads a file from the device into memory.
    /// </summary>
    /// <remarks>
    /// The specified file is downloaded in binary mode, ie if the file
    /// contained text, the data received is not necessarily
    /// null-terminated. If you expect a text file, copy the whole range of
    /// the <see cref="blob" /> into a string object.
    /// </remarks>
    /// <param name="name">The name of the file to retrieve.</param>
    /// <param name="use_usb">If <c>true</c>, the file is copied from a USB
    /// thumb drive attached to the device rather than into the internal
    /// memory of the device. This parameter defaults to <c>false</c>, ie
    /// to the internal memory.</param>
    /// <returns>The content of the file.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="std::invalid_argument">If <paramref name="name" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    /// <exception cref="std::logic_error">If the method is called while
    /// the library was compiled without support for VISA.</exception>
    blob copy_file_from_instrument(_In_z_ const wchar_t *name,
        _In_ const bool use_usb = false) const;

    /// <summary>
    /// Reads a file from the device into memory.
    /// </summary>
    /// <remarks>
    /// The specified file is downloaded in binary mode, ie if the file
    /// contained text, the data received is not necessarily
    /// null-terminated. If you expect a text file, copy the whole range of
    /// the <see cref="blob" /> into a string object.
    /// </remarks>
    /// <param name="name">The name of the file to retrieve.</param>
    /// <param name="use_usb">If <c>true</c>, the file is copied from a USB
    /// thumb drive attached to the device rather than into the internal
    /// memory of the device. This parameter defaults to <c>false</c>, ie
    /// to the internal memory.</param>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="std::invalid_argument">If <paramref name="name" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    /// <exception cref="std::logic_error">If the method is called while
    /// the library was compiled without support for VISA.</exception>
    blob copy_file_from_instrument(_In_z_ const char *name,
        _In_ const bool use_usb = false) const;

    /// <summary>
    /// Reads a file from the device into memory.
    /// </summary>
    /// <remarks>
    /// The specified file is downloaded in binary mode, ie if the file
    /// contained text, the data received is not necessarily
    /// null-terminated. If you expect a text file, copy the whole range of
    /// the <see cref="blob" /> into a string object.
    /// </remarks>
    /// <param name="name">The name of the file to retrieve. This must include
    /// the suffix &quot;,INT&quot; or &quot;,EXT&quot; to indicate whether the
    /// file is in internal memory or on a USB thumb drive.</param>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="std::invalid_argument">If <paramref name="name" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    /// <exception cref="std::logic_error">If the method is called while
    /// the library was compiled without support for VISA.</exception>
    blob copy_file_from_instrument_or_usb(_In_z_ const wchar_t *name) const;

    /// <summary>
    /// Reads a file from the device into memory.
    /// </summary>
    /// <remarks>
    /// The specified file is downloaded in binary mode, ie if the file
    /// contained text, the data received is not necessarily
    /// null-terminated. If you expect a text file, copy the whole range of
    /// the <see cref="blob" /> into a string object.
    /// </remarks>
    /// <param name="name">The name of the file to retrieve. This must include
    /// the suffix &quot;,INT&quot; or &quot;,EXT&quot; to indicate whether the
    /// file is in internal memory or on a USB thumb drive.</param>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="std::invalid_argument">If <paramref name="name" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    /// <exception cref="std::logic_error">If the method is called while
    /// the library was compiled without support for VISA.</exception>
    blob copy_file_from_instrument_or_usb(_In_z_ const char *name) const;

    /// <summary>
    /// Sets the current range.
    /// </summary>
    /// <remarks>
    /// <para>The instrument can be instructed to select a reasonable range
    /// by specifying <see cref="instrument_range::automatically" />.
    /// However, this will prevent a correct integration of measurements if
    /// the range changes during the measurement period. Therefore, it is
    /// reasonable to specify a safe range explictly in such an application
    /// case.</para>
    /// </remarks>
    /// <param name="range">Defines how <paramref name="value" /> is
    /// interpreted.</param>
    /// <param name="value">The current range in Amperes. This parameter
    /// is only used if <paramref name="range" /> is set to
    /// <see cref="instrument_range::explicitly" />. Valid values are
    /// 0.005, 0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1, 2, 5, 10 an 20.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    inline hmc8015_instrument& current_range(
            _In_ const hmc8015_instrument_range range,
            _In_ const float value = 0.0f) {
        // Note: HMC8015 supports only one channel, so this is hard coded.
        this->set_range(1, "CURR", range, value);
        return *this;
    }

    /// <summary>
    /// Changes the functions the instrument is sampling to the given
    /// user-defined ones.
    /// </summary>
    /// <remarks>
    /// <para>This is an advanced API which should only be used if you know
    /// what you are doing. The <see cref="sample" /> method expects certain
    /// functions to be enabled in a specific order. If you change this
    /// here, the results of the sensor might be wrong or the sensor might
    /// crash. The functions must therefore only changed for logging to a
    /// file while never using the generic sampling methods defined by
    /// <see cref="sensor" />. You can reset the functions to be sampled
    /// using the <see cref="default_functions" /> method.</para>
    /// </remarks>
    /// <param name="functions">An array of <paramref name="cnt" />
    /// <see cref="hmc8015_function" />s to measure.</param>
    /// <param name="cnt">The number of functions to measure.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="functions" /> is <c>nullptr</c>.</exception>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    hmc8015_instrument& custom_functions(
        _In_reads_(cnt) const hmc8015_function *functions,
        _In_ const std::size_t cnt);

    /// <summary>
    /// Changes the functions the instrument is sampling to the given
    /// compile-time list.
    /// </summary>
    /// <remarks>
    /// <para>This is an advanced API which should only be used if you know
    /// what you are doing. The <see cref="sample" /> method expects certain
    /// functions to be enabled in a specific order. If you change this
    /// here, the results of the sensor might be wrong or the sensor might
    /// crash. The functions must therefore only changed for logging to a
    /// file while never using the generic sampling methods defined by
    /// <see cref="sensor" />. You can reset the functions to be sampled
    /// using the <see cref="default_functions" /> method.</para>
    /// <para>This method allows for easy specification of compile-time
    /// function lists without declaring an array.</para>
    /// </remarks>
    /// <param name="functions">An initialiser list of the functions to be
    /// enabled.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="functions" /> is <c>nullptr</c>.</exception>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    inline std::size_t custom_functions(
            _In_ std::initializer_list<hmc8015_function> functions) {
        return this->custom_functions(functions.begin(), functions.size());
    }

    /// <summary>
    /// Enables the functions that are required for sampling the sensor
    /// using <see cref="sample" />.
    /// </summary>
    /// <remarks>
    /// <para>The <see cref="sample" /> function assumes certain values in a
    /// specific order. If the caller has changed these functions using
    /// the <see cref="custom_functions" /> method, for instance to create a
    /// custom log file, and wants to sample the instrument as a
    /// sensor, this function needs to be called to reset the functions
    /// to the expected layout.</para>
    /// <para>For performance reasons, <see cref="sample" /> will not check
    /// whether the functions have been reconfigured and do not match
    /// the expected layout.</para>
    /// </remarks>
    /// <returns><c>*this</c>.</returns>
    hmc8015_instrument& default_functions(void);

    /// <summary>
    /// Deletes the specified file from the instrument.
    /// </summary>
    /// <remarks>
    /// This method can be called if the library has been compiled without
    /// support for VISA. It has no effect in this case.
    /// </remarks>
    /// <param name="name">The name of the file to be deleted.</param>
    /// <param name="use_usb">If <c>true</c>, the file is on a USB thumb
    /// drive attached to the device rather than into the internal memory
    /// of the device. This parameter defaults to <c>false</c>, ie to the
    ///  internal memory.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="std::invalid_argument">If any of the parameters
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    hmc8015_instrument& delete_file_from_instrument(_In_z_ const wchar_t *name,
        _In_ const bool use_usb = false);

    /// <summary>
    /// Deletes the specified file from the instrument.
    /// </summary>
    /// <remarks>
    /// This method can be called if the library has been compiled without
    /// support for VISA. It has no effect in this case.
    /// </remarks>
    /// <param name="name">The name of the file to be deleted.</param>
    /// <param name="use_usb">If <c>true</c>, the file is on a USB thumb
    /// drive attached to the device rather than into the internal memory
    /// of the device. This parameter defaults to <c>false</c>, ie to the
    ///  internal memory.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="std::invalid_argument">If any of the parameters
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    hmc8015_instrument& delete_file_from_instrument(_In_z_ const char *name,
        _In_ const bool use_usb = false);

    /// <summary>
    /// Deletes the specified file from the instrument or USB thumb drive.
    /// </summary>
    /// <remarks>
    /// This method can be called if the library has been compiled without
    /// support for VISA. It has no effect in this case.
    /// </remarks>
    /// <param name="name">The name of the file to be deleted. This must include
    /// the suffix &quot;,INT&quot; or &quot;,EXT&quot; to indicate whether the
    /// file is in internal memory or on a USB thumb drive.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="std::invalid_argument">If any of the parameters
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    hmc8015_instrument& delete_file_from_instrument_or_usb(
        _In_z_ const wchar_t *name);

    /// <summary>
    /// Deletes the specified file from the instrument or USB thumb drive.
    /// </summary>
    /// <remarks>
    /// This method can be called if the library has been compiled without
    /// support for VISA. It has no effect in this case.
    /// </remarks>
    /// <param name="name">The name of the file to be deleted. This must include
    /// the suffix &quot;,INT&quot; or &quot;,EXT&quot; to indicate whether the
    /// file is in internal memory or on a USB thumb drive.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="std::invalid_argument">If any of the parameters
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    hmc8015_instrument& delete_file_from_instrument_or_usb(
        _In_z_ const char *name);

    /// <summary>
    /// Displays the given text or clears the display.
    /// </summary>
    /// <param name="text">The text to be displayed or <c>nullptr</c> to
    /// clear the display.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    hmc8015_instrument& display(_In_opt_z_ const char *text);

    /// <summary>
    /// Displays the given text or clears the display.
    /// </summary>
    /// <param name="text">The text to be displayed or <c>nullptr</c> to
    /// clear the display.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    hmc8015_instrument& display(_In_opt_z_ const wchar_t *text);

    /// <summary>
    /// Clears the display.
    /// </summary>
    /// <param name="text"><c>nullptr</c>.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    inline hmc8015_instrument& display(_In_opt_ const std::nullptr_t text) {
        return this->display(static_cast<char *>(nullptr));
    }

    /// <summary>
    /// Answer the functions the instrument is currently sampling in form of
    /// a comma-separated list.
    /// </summary>
    /// <param name="dst">A buffer to receive at least
    /// <paramref name="cnt" /> characters.</param>
    /// <param name="cnt">The size of <paramref name="dst" /> in characters.
    /// </param>
    /// <returns>The required buffer size to store the whole output, in
    /// characters.</returns>
    std::size_t functions(_Out_writes_opt_z_(cnt) char *dst,
        _In_ const std::size_t cnt) const;

    /// <summary>
    /// Configures the behaviour of the integrator.
    /// </summary>
    /// <param name="mode">Specifies the mode of the integrator, which
    /// determines which of the remaining parameters are relevant. In
    /// <see cref="integrator_mode::manual" />, all other parameters
    /// are ignored.</param>
    /// <param name="duration">The integration duration in seconds.</param>
    /// <param name="year">The year when to start integration in case
    /// the <paramref name="mode" /> is
    ///  <see cref="integration_mode::time_span" />.</param>
    /// <param name="month">The month when to start integration in case
    /// the <paramref name="mode" /> is
    ///  <see cref="integration_mode::time_span" />.</param>
    /// <param name="day">The day when to start integration in case
    /// the <paramref name="mode" /> is
    ///  <see cref="integration_mode::time_span" />.</param>
    /// <param name="hour">The hour when to start integration in case
    /// the <paramref name="mode" /> is
    ///  <see cref="integration_mode::time_span" />.</param>
    /// <param name="minute">The minute when to start integration in case
    /// the <paramref name="mode" /> is
    ///  <see cref="integration_mode::time_span" />.</param>
    /// <param name="second">The second when to start integration in case
    /// the <paramref name="mode" /> is
    ///  <see cref="integration_mode::time_span" />.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    hmc8015_instrument& integrator_behaviour(
        _In_ const hmc8015_integrator_mode mode,
        _In_ const int duration = std::numeric_limits<int>::lowest(),
        _In_ const std::int32_t year = 0,
        _In_ const std::int32_t month = 0,
        _In_ const std::int32_t day = 0,
        _In_ const std::int32_t hour = 0,
        _In_ const std::int32_t minute = 0,
        _In_ const std::int32_t second = 0);

    /// <summary>
    /// Gets whether logging is enabled or not.
    /// </summary>
    /// <returns><c>true</c> if the instrument is currently logging,
    /// <c>false</c> otherwise.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    inline bool is_log(void) const {
        return this->logging();
    }

    /// <summary>
    /// Answer a comma-separated list of files on the instrument or the USB thumb
    /// drive connected to the instrument.
    /// </summary>
    /// <param name="dst">If not <c>nullptr</c>, receives at most
    /// <paramref name="cnt" /> characters of the string.</param>
    /// <param name="cnt">The buffer size in number of characters.</param>
    /// <param name="use_usb">If <c>true</c>, list the contents of the USB drive
    /// rather than the internal files.</param>
    /// <returns>The required buffer size for <paramref name="dst" />.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    std::size_t list_files_on_instrument(
        _Out_writes_opt_z_(cnt) char *dst,
        _In_ const std::size_t cnt,
        _In_ const bool use_usb = false) const;

    /// <summary>
    /// Enables or disables logging.
    /// </summary>
    /// <param name="enable">Start logging if <c>true</c>, otherwise, stop
    /// it.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    hmc8015_instrument& log(_In_ const bool enable);

    /// <summary>
    /// Gets whether logging is enabled or not.
    /// </summary>
    /// <returns><c>true</c> if the instrument is currently logging,
    /// <c>false</c> otherwise.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    bool logging(void) const;

    /// <summary>
    /// Configures how logging started by <see cref="log" /> behaves.
    /// </summary>
    /// <param name="interval">The interval between samples in seconds.
    /// Specifying the lowest/maximum value of <c>float</c> is interpreted
    /// as special values &quot;MIN&quot; and &quot;MAX&quot; respectively.
    /// </param>
    /// <param name="mode">The logging mode.</param>
    /// <param name="value">The count (number of samples) or duration (in
    /// seconds), depending on the given <paramref name="mode" />. This
    /// value is ignored for <see cref="log_mode::unlimited" />. Specifying
    /// the lowest/maximum value of <c>int</c> is interpreted as special
    /// values &quot;MIN&quot; and &quot;MAX&quot; respectively.</param>
    /// <param name="year">The year of the start time if
    /// <see cref="log_mode::time_span" /> is selected.</param>
    /// <param name="month">The month of the start time if
    /// <see cref="log_mode::time_span" /> is selected.</param>
    /// <param name="day">The day of the start time if
    /// <see cref="log_mode::time_span" /> is selected.</param>
    /// <param name="hour">The hour of the start time if
    /// <see cref="log_mode::time_span" /> is selected.</param>
    /// <param name="minute">The minute of the start time if
    /// <see cref="log_mode::time_span" /> is selected.</param>
    /// <param name="second">The second of the start time if
    /// <see cref="log_mode::time_span" /> is selected.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    hmc8015_instrument& log_behaviour(_In_ const float interval,
        _In_ const hmc8015_log_mode mode,
        _In_ const int value = INT_MAX,
        _In_ const std::int32_t year = 0,
        _In_ const std::int32_t month = 0,
        _In_ const std::int32_t day = 0,
        _In_ const std::int32_t hour = 0,
        _In_ const std::int32_t minute = 0,
        _In_ const std::int32_t second = 0);

    /// <summary>
    /// Gets the path to the log file.
    /// </summary>
    /// <param name="path">The buffer receiving the log file. Note that
    /// this is the path and a designator whether the internal or USB
    /// memory is used. If this parameter is <c>nullptr</c>, nothing will
    /// be written. The output string is guaranteed to be null-terminated
    /// if anything has been written.</param>
    /// <param name="cnt">The maximum number of bytes that can be written
    /// to <paramref name="path "/>.</param>
    /// <returns>The actual length of the path, including the terminating
    /// null character.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    std::size_t log_file(_Out_writes_opt_z_(cnt) char *path,
        _In_ const std::size_t cnt);

    /// <summary>
    /// Measures the size of the path to the log file.
    /// </summary>
    /// <param name="path">Must be <c>nullptr</c>.</param>
    /// <param name="cnt">The parameter is ignored.</param>
    /// <returns>The actual length of the path, including the terminating
    /// null character.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    inline std::size_t log_file(_In_opt_ std::nullptr_t path,
            _In_ const std::size_t cnt) {
        return this->log_file(static_cast<char *>(nullptr), 0);
    }

    /// <summary>
    /// Sets the path to the log file.
    /// </summary>
    /// <param name="path">The path to the log file, usually just the
    /// file name.</param>
    /// <param name="overwrite">If <c>true</c>, the file will be cleared
    /// if it already exists. This parameter defaults to <c>false</c>.
    /// </param>
    /// <param name="use_usb">If <c>true</c>, the file will be written to
    /// the attached USB stick instead of internal memory. This parameter
    /// defaults to <c>false</c>.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    hmc8015_instrument& log_file(_In_z_ const char *path,
        _In_ const bool overwrite = false,
        _In_ const bool use_usb = false);

    /// <summary>
    /// Sets the path to the log file.
    /// </summary>
    /// <param name="path">The path to the log file, usually just the
    /// file name.</param>
    /// <param name="overwrite">If <c>true</c>, the file will be cleared
    /// if it already exists. This parameter defaults to <c>false</c>.
    /// </param>
    /// <param name="use_usb">If <c>true</c>, the file will be written to
    /// the attached USB stick instead of internal memory. This parameter
    /// defaults to <c>false</c>.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    hmc8015_instrument& log_file(_In_z_ const wchar_t *path,
        _In_ const bool overwrite = false,
        _In_ const bool use_usb = false);

    /// <summary>
    /// Resets the manual integration time, which is displayed on the
    /// display (status line).
    /// </summary>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    hmc8015_instrument& reset_integrator(void);

    /// <summary>
    /// Starts the integrator if in manual mode.
    /// </summary>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    hmc8015_instrument& start_integrator(void);

    /// <summary>
    /// Stops the integrator if in manual mode.
    /// </summary>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    hmc8015_instrument& stop_integrator(void);

    /// <summary>
    /// Sets the voltage range.
    /// </summary>
    /// <remarks>
    /// <para>The instrument can be instructed to select a reasonable range
    /// by specifying <see cref="instrument_range::automatically" />.
    /// However, this will prevent a correct integration of measurements if
    /// the range changes during the measurement period. Therefore, it is
    /// reasonable to specify a safe range explictly in such an application
    /// case.</para>
    /// </remarks>
    /// <param name="range">Defines how <paramref name="value" /> is
    /// interpreted.</param>
    /// <param name="value">The current range in Volts. This parameter
    /// is only used if <paramref name="range" /> is set to
    /// <see cref="instrument_range::explicitly" />. Valid values are
    /// 5, 15, 30, 60, 150, 300 and 600.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    inline hmc8015_instrument& voltage_range(
            _In_ const hmc8015_instrument_range range,
            _In_ const std::int32_t value = 0) {
        // Note: HMC8015 supports only one channel, so this is hard coded.
        this->set_range(1, "VOLT", range, static_cast<float>(value));
        return *this;
    }

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The right-hand side operand</param>
    /// <returns><c>*this</c></returns>
    hmc8015_instrument& operator =(_Inout_ hmc8015_instrument&& rhs) noexcept;

private:

    void configure(void);

    void initialise(void);

    void set_range(_In_ const std::int32_t channel,
        _In_z_ const char *quantity,
        _In_ const hmc8015_instrument_range range,
        _In_ const float value);
};

PWROWG_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
#endif /* !defined(_PWROWG_HMC8015_INSTRUMENT_H) */
