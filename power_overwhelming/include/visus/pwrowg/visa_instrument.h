// <copyright file="visa_instrument.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_VISA_INSTRUMENT_H)
#define _PWROWG_VISA_INSTRUMENT_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_VISA)

#include <cassert>
#include <functional>
#include <memory>
#include <string>

#include <visa.h>

#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/visa_event_status.h"
#include "visus/pwrowg/visa_status_byte.h"


/* Forward declarations. */
PWROWG_DETAIL_NAMESPACE_BEGIN
struct visa_instrument_impl;
PWROWG_DETAIL_NAMESPACE_END


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Implementation of a VISA instrument, which can be used to implement a sensor
/// or control an instrument like an oscilloscope manually.
/// </summary>
/// <remarks>
/// <para>The <see cref="visa_instrument" /> manages a <see cref="ViSession" />
/// on a single device, which might be used by multiple <see cref="sensor" />s.
/// </para>
/// </remarks>
class POWER_OVERWHELMING_API visa_instrument {

public:

    /// <summary>
    /// The type representing a single byte.
    /// </summary>
    typedef blob::byte_type byte_type;

    /// <summary>
    /// The type used to express device timeouts in milliseconds.
    /// </summary>
    typedef std::uint32_t timeout_type;

    /// <summary>
    /// Find all resources matching the given VISA resource query.
    /// </summary>
    /// <param name="query">The query to issue on the resource manager.
    /// </param>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// <para>The return value is a multi-sz string which can be procesed
    /// as follows:</para>
    /// <code>
    /// for (auto d = devices.as&lt;wchar_t&gt;();
    ///         (d != nullptr) && (*d != 0);
    ///         d += ::wcslen(d) + 1) {
    ///     visa_instrument instrument(d, 5000);
    ///     // Do something with the instrument.
    /// }
    /// </code>
    /// </remarks>
    /// <returns>A <c>wchar_t</c> <see cref="blob" /> holding a a multi-sz
    /// string (registry type) of all device paths matching the query.
    /// </returns>
    /// <exception cref="std::invalid_argument">If <paramref name="query" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If the query failed.</exception>
    /// <exception cref="std::bad_alloc">If the memory for the output could
    /// not be allocated.</exception>
    static blob find_resources(_In_z_ const wchar_t *query);

    /// <summary>
    /// Find all resources matching the given VISA resource query.
    /// </summary>
    /// <param name="query">The query to issue on the resource manager.
    /// </param>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// <para>The return value is a multi-sz string which can be procesed
    /// as follows:</para>
    /// <code>
    /// for (auto d = devices.as&lt;char&gt;();
    ///         (d != nullptr) && (*d != 0);
    ///         d += ::strlen(d) + 1) {
    ///     visa_instrument instrument(d, 5000);
    ///     // Do something with the instrument.
    /// }
    /// </code>
    /// </remarks>
    /// <returns>A <c>char</c> <see cref="blob" /> holding a a multi-sz
    /// string (registry type) of all device paths matching the query.
    /// </returns>
    /// <exception cref="std::invalid_argument">If <paramref name="query" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If the query failed.</exception>
    /// <exception cref="std::bad_alloc">If the memory for the output could
    /// not be allocated.</exception>
    static blob find_resources(_In_z_ const char *query);

    /// <summary>
    /// Find all instruments of the specified type connected to the machine
    /// the code is running on.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// </remarks>
    /// <param name="vendor_id">The ID of the vendor to search for.</param>
    /// <param name="instrument_id">The ID of the instrument to search for.
    /// </param>
    /// <returns>A <c>char</c> <see cref="blob" /> holding a a multi-sz
    /// string (registry type) of all device paths matching the query.
    /// </returns>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="vendor_id" /> is <c>nullptr</c> or if
    ///  <paramref name="instrument_id" /> is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If the query failed.</exception>
    /// <exception cref="std::bad_alloc">If the memory for the output could
    /// not be allocated.</exception>
    static blob find_resources(_In_z_ const wchar_t *vendor_id,
        _In_z_ const wchar_t *instrument_id);

    /// <summary>
    /// Find all instruments of the specified type connected to the machine
    /// the code is running on.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// </remarks>
    /// <param name="vendor_id">The ID of the vendor to search for.</param>
    /// <param name="instrument_id">The ID of the instrument to search for.
    /// </param>
    /// <returns>A <c>char</c> <see cref="blob" /> holding a a multi-sz
    /// string (registry type) of all device paths matching the query.
    /// </returns>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="vendor_id" /> is <c>nullptr</c> or if
    ///  <paramref name="instrument_id" /> is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If the query failed.</exception>
    /// <exception cref="std::bad_alloc">If the memory for the output could
    /// not be allocated.</exception>
    static blob find_resources(_In_z_ const char *vendor_id,
        _In_z_ const char *instrument_id);

    /// <summary>
    /// Invokes <paramref name="callback" /> for each active instance of a
    /// <see cref="visa_instrument" />.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// </remarks>
    /// <param name="callback">The callback to be invoked for each
    /// instrument. If the callback returns <c>false</c>, the enumeration
    /// will be stopped after the current call. If the callback throws
    /// an exception, this will be caught and treated as if the callback
    /// had returned <c>false</c>.</param>
    /// <param name="context">A user-defined context passed to the callback
    /// function.</param>
    /// <returns>The number of times the callback has been sucessfully
    /// invoked. If the callback always returns <c>true</c>, this is the
    /// number of active VISA instruments at the time of the call.</returns>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="callback" /> is <c>nullptr</c>.</exception>
    static std::size_t foreach_instance(
        _In_ bool (*callback)(visa_instrument&, void *),
        _In_opt_ void *context = nullptr);

    /// <summary>
    /// The default timeout for connecting to a VISA instruments, in
    /// milliseconds.
    /// </summary>
    static constexpr const timeout_type default_timeout = 5000;

    /// <summary>
    /// The vendor ID of Rohde &amp; Schwarz.
    /// </summary>
    static constexpr const char *rohde_und_schwarz = "0x0AAD";

    /// <summary>
    /// Initialises a new, but invalid instance.
    /// </summary>
    visa_instrument(void);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="path">The VISA resource path of the instrument.</param>
    /// <param name="timeout">The timeout for the connection attempt in
    /// milliseconds. This parameter defaults to
    /// <see cref="default_timeout" />.</param>
    /// <exception cref="std::invalid_argument">If <paramref name="path" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="std::bad_alloc">If the memory for the sensor state
    /// could not be allocated.</exception>
    /// <exception cref="std::system_error">If the VISA library could not be
    /// loaded.</exception>
    /// <exception cref="visa_exception">If the sensor could not be
    /// initialised.</exception>
    visa_instrument(_In_z_ const wchar_t *path,
        _In_ const timeout_type timeout = default_timeout);

    /// <summary>
    /// Initialises a new instance.
    /// <param name="path">The VISA resource path of the instrument.</param>
    /// <param name="timeout">The timeout for the connection attempt in
    /// milliseconds. This parameter defaults to
    /// <see cref="default_timeout" />.</param>
    /// <exception cref="std::invalid_argument">If <paramref name="path" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="std::bad_alloc">If the memory for the sensor state
    /// could not be allocated.</exception>
    /// <exception cref="std::system_error">If the VISA library could not be
    /// loaded.</exception>
    /// <exception cref="visa_exception">If the sensor could not be
    /// initialised.</exception>
    visa_instrument(_In_z_ const char *path,
        _In_ const timeout_type timeout = default_timeout);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="is_new_connection">Indicates whether a new connection
    /// to an instrument was established or an existing one was reused. If
    /// this parameter returns <c>false</c>, callers should be aware that
    /// multiple code paths might manipulate the instrument independently.
    /// </param>
    /// <param name="path">The VISA resource path of the instrument.</param>
    /// <param name="timeout">The timeout for the connection attempt in
    /// milliseconds. This parameter defaults to
    /// <see cref="default_timeout" />.</param>
    /// <exception cref="std::invalid_argument">If <paramref name="path" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="std::bad_alloc">If the memory for the sensor state
    /// could not be allocated.</exception>
    /// <exception cref="std::system_error">If the VISA library could not be
    /// loaded.</exception>
    /// <exception cref="visa_exception">If the sensor could not be
    /// initialised.</exception>
    visa_instrument(_Out_ bool& is_new_connection,
        _In_z_ const wchar_t *path,
        _In_ const timeout_type timeout = default_timeout);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="is_new_connection">Indicates whether a new connection
    /// to an instrument was established or an existing one was reused. If
    /// this parameter returns <c>false</c>, callers should be aware that
    /// multiple code paths might manipulate the instrument independently.
    /// </param>
    /// <param name="path">The VISA resource path of the instrument.</param>
    /// <param name="timeout">The timeout for the connection attempt in
    /// milliseconds. This parameter defaults to
    /// <see cref="default_timeout" />.</param>
    /// <exception cref="std::invalid_argument">If <paramref name="path" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="std::bad_alloc">If the memory for the sensor state
    /// could not be allocated.</exception>
    /// <exception cref="std::system_error">If the VISA library could not be
    /// loaded.</exception>
    /// <exception cref="visa_exception">If the sensor could not be
    /// initialised.</exception>
    visa_instrument(_Out_ bool& is_new_connection,
        _In_z_ const char *path,
        _In_ const timeout_type timeout = default_timeout);

    visa_instrument(const visa_instrument&) = delete;

    /// <summary>
    /// Move <paramref name="rhs" /> into a new instance.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    inline visa_instrument(_Inout_ visa_instrument&& rhs) noexcept
            : _impl(rhs._impl) {
        rhs._impl = nullptr;
    }

    /// <summary>
    /// Finalise the instance.
    /// </summary>
    virtual ~visa_instrument(void);

    /// <summary>
    /// Indicates whether the instrument is aliased, ie whether there are
    /// other instances of <see cref="visa_instrument" /> using the same
    /// hardware.
    /// </summary>
    /// <remarks>
    /// <para>It is safe to call this method if the library was compiled
    /// without support for VISA, in which case the result will be
    /// <c>false</c>.</para>
    /// <para>It is safe to call this method on a disposed instance, in
    /// which case the result will be <c>false</c>.</para>
    /// </remarks>
    /// <returns><c>true</c> if multiple instances use the hardware,
    /// <c>false</c> otherwise.</returns>
    bool aliased(void) const noexcept;

    /// <summary>
    /// Answer whether this instance uses the same hardware as
    /// <paramref name="instance" />.
    /// </summary>
    /// <remarks>
    /// <para>It is safe to call this method if the library was compiled
    /// without support for VISA, in which case the result will be
    /// <c>false</c>.</para>
    /// <para>It is safe to call this method on a disposed instance, in
    /// which case the result will be <c>false</c>.</para>
    /// </remarks>
    /// <param name="instrument">The instrument to be compared. It is safe
    /// to pass a disposed instrument.</param>
    /// <returns><c>true</c> if this instrument and
    /// <paramref name="instrument" /> share the same implementation object,
    /// <c>false</c> otherwise.</returns>
    bool alias_of(_In_ const visa_instrument& instrument) const noexcept;

    /// <summary>
    /// Read an attribute value from the instrument.
    /// </summary>
    /// <param name="dst">Receives the current value of the attribute. The
    /// size of this buffer must match the type of the attribute.</param>
    /// <param name="name">The name of the attribute to be retrieve.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    const visa_instrument& attribute(_Out_ void *dst,
        _In_ ViAttr name) const;

    /// <summary>
    /// Set an attribute of the instrument.
    /// </summary>
    /// <param name="name">The name of the attribute to be set.</param>
    /// <param name="value">The new value of teh attribute.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    visa_instrument& attribute(_In_ ViAttr name,
        _In_ ViAttrState value);

    /// <summary>
    /// Makes the instrument beep <paramref name="cnt" /> times.
    /// </summary>
    /// <remarks>
    /// This method has no effect if the library was compiled without
    /// support for VISA.
    /// </remarks>
    /// <param name="cnt">The number of times the method should beep. This
    /// defaults to one.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    visa_instrument& beep(_In_ const std::size_t cnt = 1);

    /// <summary>
    /// Answer whether the instrument beeps if it encounters an error.
    /// </summary>
    /// <remarks>
    /// The answer will always be <c>false</c> if the library was compiled
    /// without support for VISA.
    /// </remarks>
    /// <returns><c>true</c> if the beep is enabled, <c>false</c> otherwise.
    /// </returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    bool beep_on_error(void);

    /// <summary>
    /// Configures the instrument to beep or not to beep if it encounters
    /// an error.
    /// </summary>
    /// <remarks>
    /// This method has no effect if the library was compiled without
    /// support for VISA.
    /// </remarks>
    /// <param name="enable">Set <c>true</c> to enable beeps on errors,
    /// <c>false</c> to disable them.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    visa_instrument& beep_on_error(_In_ const bool enable);

    /// <summary>
    /// Shortcut to <see cref="viSetBuf" /> on the device session
    /// represented by <see cref="scope" />.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// </remarks>
    /// <param name="mask"></param>
    /// <param name="size"></param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed. Note that
    /// a failure here only refers to the use of the API, ie the instrument
    /// can be in a failed state even if the call succeeded. Use
    /// <see cref="throw_on_system_error" /> to check the internal state of
    /// the instrument after the call.</exception>
    visa_instrument& buffer(_In_ const std::uint16_t mask,
        _In_ const std::uint32_t size);

    /// <summary>
    /// Call <see cref="viClear" /> on the instrument, which will flush all
    /// buffers.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// </remarks>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    visa_instrument& clear(void);

    /// <summary>
    /// Clear the error queue of the instrument.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// </remarks>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    visa_instrument& clear_status(void);

    /// <summary>
    /// Enables internal checks of the instrument's system state after
    /// changes to its configuration were made.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// <para>Within the methods of the instrument, there are checks of the
    /// system state of the instrument after important changes. If you
    /// enable these system checks, the code will fail early in case you
    /// make any change that puts the system into an invalid state. By
    /// default, the checks are disabled, because they cause significant
    /// overhead. It is suggested to enable this only for debugging purposes
    /// during development.</para>
    /// </remarks>
    /// <param name="enable">Indicates whether the checks are enabled or
    /// disabled. This parameter defaults to <c>true</c>.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    visa_instrument& enable_system_checks(_In_ const bool enable = true);

    /// <summary>
    /// Reads the event status register using a <c>*ESR?</c> command.
    /// </summary>
    /// <returns>The current value of the event status register.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    /// <exception cref="std::logic_error">If the library was compiled
    /// without support for VISA.</exception>
    visa_event_status event_status(void) const;

    /// <summary>
    /// Changes the event status enable state to the given bitmask using
    /// the <c>*ESE</c> command.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// <para>This method will add an <c>*OPC?</c> query after the set
    /// operation, which makes sure that it does not return until the
    /// command was executed on the instrument.</para>
    /// </remarks>
    /// <param name="status">The status of the individual event bits.
    /// </param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    visa_instrument& event_status(_In_ const visa_event_status status);

    /// <summary>
    /// Send the &quot;identify&quot; SCPI command to the instrument and
    /// return its response.
    /// </summary>
    /// <remarks>
    /// <para>The identity of an instrument is always the empty string if
    /// the library was compiled without support for VISA.</para>
    /// </remarks>
    /// <param name="dst">If not <c>nullptr</c>, receives at most
    /// <paramref name="cnt" /> characters of the identification string. It
    /// is safe to pass <c>nulltpr</c> in which case the string will only
    /// be measured, but not returned. It is guaranteed that this string is
    /// null-terminated even if it was truncated.</param>
    /// <param name="cnt">The size of <paramref name="dst" /> in characters.
    /// </param>
    /// <returns>The number of characters, including the terminating null,
    /// required to store the identity of the instrument.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    std::size_t identify(_Out_writes_opt_z_(cnt) wchar_t *dst,
        _In_ const std::size_t cnt) const;

    /// <summary>
    /// Send the &quot;identify&quot; SCPI command to the instrument and
    /// return its response.
    /// </summary>
    /// <remarks>
    /// <para>The identity of an instrument is always the empty string if
    /// the library was compiled without support for VISA.</para>
    /// </remarks>
    /// <param name="dst">If not <c>nullptr</c>, receives at most
    /// <paramref name="cnt" /> characters of the identification string. It
    /// is safe to pass <c>nulltpr</c> in which case the string will only
    /// be measured, but not returned. It is guaranteed that this string is
    /// null-terminated even if it was truncated.</param>
    /// <param name="cnt">The size of <paramref name="dst" /> in characters.
    /// </param>
    /// <returns>The number of characters, including the terminating null,
    /// required to store the identity of the instrument.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    std::size_t identify(_Out_writes_opt_z_(cnt) char *dst,
        _In_ const std::size_t cnt) const;

    /// <summary>
    /// Counts the number of characters (including the terminating null)
    /// required to hold the name of the device.
    /// </summary>
    /// <param name="dst">A <c>nullptr</c>.</param>
    /// <param name="cnt">This parameter is ignored.</param>
    /// <returns>The number of characters, including the terminating null,
    /// required to store the identity of the instrument.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    std::size_t identify(_In_opt_ std::nullptr_t dst,
        _In_ const std::size_t cnt);

    /// <summary>
    /// Gets the interface type of the underlying session in the form of one
    /// of the enumerated values <c>VI_INTF_GPIB</c>, <c>VI_INTF_VXI</c>,
    /// <c>VI_INTF_GPIB_VXI</c>, <c>VI_INTF_ASRL</c>, <c>VI_INTF_PXI</c>,
    /// <c>VI_INTF_TCPIP</c> or <c>VI_INTF_USB</c>.
    /// </summary>
    /// <returns>The interface type.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="std::logic_error">If the library was compiled
    /// without support for VISA.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    std::uint16_t interface_type(void) const;

    /// <summary>
    /// Gets the configured name of the instrument.
    /// </summary>
    /// <param name="dst">A buffer that is able to hold at least
    /// <paramref name="cnt" /> elements. It is safe to pass <c>nullptr</c>,
    /// in which case the method will only measure the required buffer size.
    /// </param>
    /// <param name="cnt">The size of <paramref name="dst" /> in number of
    /// characters. The name of the R&S instruments we use cannot exceed 20
    /// ASCII characters, so a buffer of 21 characters should always
    /// suffice.</param>
    /// <returns>The required buffer size for the name, including the
    /// terminating zero.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    std::size_t name(_Out_writes_(cnt) wchar_t *dst,
        _In_ const std::size_t cnt) const;

    /// <summary>
    /// Gets the configured name of the instrument.
    /// </summary>
    /// <param name="dst">A buffer that is able to hold at least
    /// <paramref name="cnt" /> elements. It is safe to pass <c>nullptr</c>,
    /// in which case the method will only measure the required buffer size.
    /// </param>
    /// <param name="cnt">The size of <paramref name="dst" /> in number of
    /// characters. The name of the R&S instruments we use cannot exceed 20
    /// ASCII characters, so a buffer of 21 characters should always
    /// suffice.</param>
    /// <returns>The required buffer size for the name, including the
    /// terminating zero.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    std::size_t name(_Out_writes_(cnt) char *dst,
        _In_ const std::size_t cnt) const;

    /// <summary>
    /// Measures the size of the buffer to hold the name of the instrument.
    /// </summary>
    /// <param name="dst"><c>nullptr</c>.</param>
    /// <param name="cnt">This parameter is ignored.</param>
    /// <returns>The required buffer size for the name, including the
    /// terminating zero.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    std::size_t name(_In_opt_ const std::nullptr_t dst,
        _In_ const std::size_t cnt) const;

    /// <summary>
    /// Sets the user-defined name of the instrument.
    /// </summary>
    /// <param name="name">The new name of the instrument.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="name" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    visa_instrument& name(_In_z_ const wchar_t *name);

    /// <summary>
    /// Sets the name of the instrument.
    /// </summary>
    /// <param name="name">The new name of the instrument.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="name" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    visa_instrument& name(_In_z_ const char *name);

    /// <summary>
    /// Installs a <paramref name="callback" /> to be invoked if an
    /// ansynchronous <c>*OPC</c> instruction was reached.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// </remarks>
    /// <param name="callback">The callback to be invoked on an operation
    /// completing. If this is <c>nullptr</c>, an existing callback will be
    /// uninstalled.</param>
    /// <param name="context">A user-defined context pointer to be passed
    /// to the callback.</param>
    /// <param name="context_deleter">If not <c>nullptr</c>, the object
    /// takes ownership of the <paramref name="context" /> and will delete
    /// it using this function when no longer needed.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    visa_instrument& on_operation_complete(
        _In_opt_ void (*callback)(visa_instrument &, void *),
        _In_opt_ void *context = nullptr,
        _In_opt_ void (*context_deleter)(void *) = nullptr);

    /// <summary>
    /// Installs a <paramref name="callback" /> to be invoked if an
    /// asynchronous <c>*OPC</c> instruction was reached.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// <para>The <pararmef name="context" /> passed to the method will be
    /// moved to newly allocated heap memory that lives as long as the
    /// callback is active. The object will take care of destructing the
    /// object and freeing the heap mempry allocated for it.</para>
    /// </remarks>
    /// <typeparam name="TContext">The type of the context object passed to
    /// the callback. This type must be movable.</typeparam>
    /// <param name="callback">The callback to be invoked on an operation
    /// completing. If this is <c>nullptr</c>, an existing callback will be
    /// uninstalled.</param>
    /// <param name="context">The context passed to the callback. The
    /// instrument takes ownership of this object.</param>
    /// <returns></returns>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    template<class TContext> visa_instrument& on_operation_complete_ex(
        _In_opt_ void (*callback)(visa_instrument&, void *),
        _Inout_ TContext&& context);

    /// <summary>
    /// Installs a functional (<see cref="std::function" />, functor object
    /// or lambda expression) to be invoked if an asynchronous <c>*OPC</c>
    /// instruction was reached.
    /// </summary>
    /// <typeparam name="TFunctor">The type of the functor to register. This
    /// functor must accept a reference to <see cref="visa_instrument" />.
    /// Please note that you cannot use a custom context pointer with
    /// functor objects. Use a closure if you need to capture the context of
    /// a lambda expression.</typeparam>
    /// <param name="callback"></param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    template<class TFunctor> visa_instrument& on_operation_complete_ex(
        _In_ TFunctor&& callback);

    /// <summary>
    /// Issue and wait for an OPC query.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// </remarks>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    const visa_instrument& operation_complete(void) const;

    /// <summary>
    /// Queues an <c>*OPC</c> instruction on the instrument, which will
    /// cause the callback installed via
    /// <see cref="on_operation_complete" /> being invoked if the instrument
    /// reaches the instruction.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// </remarks>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    const visa_instrument& operation_complete_async(void) const;

    /// <summary>
    /// Gets the VISA path of the device.
    /// </summary>
    /// <returns>The VISA path used to open the device. If the instrument
    /// has been disposed using a move operation, the path will be
    /// <c>nullptr</c>.</returns>
    _Ret_maybenull_z_ const char *path(void) const noexcept;

    ///// <summary>
    ///// Sets the ESE filter to the OPC bit, sets the OPC bit and afterwards
    ///// polls the status byte for the operation setting this bit being
    ///// executed.
    ///// </summary>
    ///// <param name=""></param>
    ///// <returns></returns>
    //visa_instrument& poll_status_byte(void);

    /// <summary>
    /// Write the given data to the instrument and directly read the
    /// response using a buffer size of <paramref name="buffer_size" />
    /// bytes.
    /// </summary>
    /// <param name="query">The query to send to the instrument.</param>
    /// <param name="cnt">The size of <paramref name="query" /> in bytes.
    /// </param>
    /// <param name="buffer_size">The buffer size used to read the response.
    /// This parameter defaults to 1024.</param>
    /// <returns>The data received from the instrument.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="query" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed. Note that
    /// a failure here only refers to the use of the API, ie the instrument
    /// can be in a failed state even if the call succeeded. Use
    /// <see cref="throw_on_system_error" /> to check the internal state of
    /// the instrument after the call.</exception>
    blob query(_In_reads_bytes_(cnt) const byte_type *query,
        _In_ const std::size_t cnt,
        _In_ const std::size_t buffer_size = 1024) const;

    /// <summary>
    /// Write the given null-terminated query to the instrument and directly
    /// read the response using a buffer size of
    /// <paramref name="buffer_size" /> bytes.
    /// </summary>
    /// <param name="query">The query to be sent to the instrument.</param>
    /// <param name="buffer_size">The buffer size used to read the response.
    /// This parameter defaults to 1024.</param>
    /// <returns>The data received from the instrument.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="query" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed. Note that
    /// a failure here only refers to the use of the API, ie the instrument
    /// can be in a failed state even if the call succeeded. Use
    /// <see cref="throw_on_system_error" /> to check the internal state of
    /// the instrument after the call.</exception>
    blob query(_In_z_ const char *query,
        _In_ const std::size_t buffer_size = 1024) const;

    /// <summary>
    /// Write the given null-terminated query to the instrument and directly
    /// read the response using a buffer size of
    /// <paramref name="buffer_size" /> bytes.
    /// </summary>
    /// <param name="query">The query to be sent to the instrument.</param>
    /// <param name="buffer_size">The buffer size used to read the response.
    /// This parameter defaults to 1024.</param>
    /// <returns>The data received from the instrument.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="query" />
    /// is <c>nullptr</c>.</exception>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed. Note that
    /// a failure here only refers to the use of the API, ie the instrument
    /// can be in a failed state even if the call succeeded. Use
    /// <see cref="throw_on_system_error" /> to check the internal state of
    /// the instrument after the call.</exception>
    blob query(_In_z_ const wchar_t *query,
        _In_ const std::size_t buffer_size = 1024) const;

    /// <summary>
    /// Read from the instrument into the given buffer.
    /// </summary>
    /// <remarks>
    /// <para>This method has no effect if the library has been compiled
    /// without support for VISA.</para>
    /// </remarks>
    /// <param name="buffer">The buffer to write the data to.</param>
    /// <param name="cnt">The size of the buffer in bytes.</param>
    /// <returns>The number of bytes actually read. If this is equal to
    /// <see cref="cnt" />, the response has most likely not been read in
    /// total and you should call the method again.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="buffer" /> is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If the operation failed. Note that
    /// a failure here only refers to the use of the API, ie the instrument
    /// can be in a failed state even if the call succeeded. Use
    /// <see cref="throw_on_system_error" /> to check the internal state of
    /// the instrument after the call.</exception>
    std::size_t read(_Out_writes_bytes_(cnt) byte_type *buffer,
        _In_ const std::size_t cnt) const;

    /// <summary>
    /// Read a full response.
    /// </summary>
    /// <remarks>
    /// This method has no effect if the library has been compiled without
    /// support for VISA.
    /// </remarks>
    /// <param name="buffer_size">The size of the read buffer being used. If
    /// this is less than the response size, the buffer will be resized
    /// until everything was read.
    /// </param>
    /// <returns>The full output from the device. The buffer will have
    /// exactly the size of the response, all padding will be removed before
    /// the buffer is returned.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed. Note that
    /// a failure here only refers to the use of the API, ie the instrument
    /// can be in a failed state even if the call succeeded. Use
    /// <see cref="throw_on_system_error" /> to check the internal state of
    /// the instrument after the call.</exception>
    blob read_all(_In_ const std::size_t buffer_size = 1024) const;

    /// <summary>
    /// Reads a binary response starting with the # marker for the number of
    /// bytes to follow.
    /// </summary>
    /// <returns>The binary data excluding the length marker.</returns>
    /// <exception cref="visa_exception">If the operation failed.</exception>
    /// <exception cref="std::runtime_error">If the data being read are not
    /// binary.</exception>
    blob read_binary(void) const;

    /// <summary>
    /// Resets the instrument to its default state by issuing the
    /// <c>*RST</c> command.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// <para>This method will issue an <c>*OPC?</c> query immediately after
    /// the reset request in order to make sure that the calling code is
    /// blocked until the instrument finished resetting. If the I/O buffers
    /// are flushed and/or the status bits are cleared, these operations
    /// are also guaranteed to have completed before the method returns.
    /// </para>
    /// </remarks>
    /// <param name="flush_buffers">Also clear all I/O buffers before the
    /// reset using <c>viClear</c>.</param>
    /// <param name="clear_status">Also clear the status bits before
    /// resetting the device.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    visa_instrument& reset(_In_ const bool flush_buffers = false,
        _In_ const bool clear_status = false);

    /// <summary>
    /// Changes the bits enabled in the service request enable (SRE)
    /// register.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// <para>This method will add an <c>*OPC?</c> query after the set
    /// operation, which makes sure that it does not return until the
    /// command was executed on the instrument.</para>
    /// </remarks>
    /// <param name="status">The status of the individual SRE bits.
    /// </param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    visa_instrument& service_request_status(
        _In_ const visa_status_byte status);

    /// <summary>
    /// Reads the currently enabled bits in the service request enable (SRE)
    /// register.
    /// </summary>
    /// <returns>The current value of the SRE register.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    /// <exception cref="std::logic_error">If the library was compiled
    /// without support for VISA.</exception>
    visa_status_byte service_request_status(void) const;

    /// <summary>
    /// Synchonises the date and time on the instrument with the system
    /// clock of the computer calling this API.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// </remarks>
    /// <param name="utc">If <c>true</c>, UTC will be used, the local time
    /// otherwise. This parameter defaults to <c>false</c>.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the VISA command was not
    /// processed successfully.</exception>
    visa_instrument& synchronise_clock(_In_ const bool utc = false);

    /// <summary>
    /// Reads the status bytes.
    /// </summary>
    /// <returns>The status bytes.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    /// <exception cref="std::logic_error">If the library was compiled
    /// without support for VISA.</exception>
    visa_status_byte status(void) const;

    /// <summary>
    /// Query the oldest error in the queue.
    /// </summary>
    /// <remarks>
    /// <para>This method always returns zero if the library was compiled
    /// without support for VISA.</para>
    /// </remarks>
    /// <returns>The current system error, or zero if the system has no
    /// previous error.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the current system state could
    /// not be retrieved.</exception>
    int system_error(void) const;

    /// <summary>
    /// Checks the return value of <see cref="system_error" /> and throws a
    /// <see cref="std::runtime_error" /> if it does not return zero.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// <para>It is safe to call this method on a disposed instrument, in
    /// which case nothing will happen.</para>
    /// </remarks>
    /// <exception cref="visa_exception">If the current system state could
    /// not be retrieved.</exception>
    /// <exception cref="std::runtime_error">If the current system state was
    /// retrieved and is not zero.</exception>
    void throw_on_system_error(void) const;

    /// <summary>
    /// Query the current timeout from the instrument.
    /// </summary>
    /// <returns>The current timeout of the instrument in milliseconds.
    /// </returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the current system state could
    /// not be retrieved.</exception>
    /// <exception cref="std::logic_error">If the library was compiled
    /// without support for VISA.</exception>
    timeout_type timeout(void) const;

    /// <summary>
    /// Sets the timeout of the underlying VISA session.
    /// </summary>
    /// <remarks>
    /// <para>This method has no effect if the library was compiled without
    /// support for VISA.</para>
    /// </remarks>
    /// <param name="timeout">The timeout in milliseconds.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the current system state could
    /// not be retrieved.</exception>
    visa_instrument& timeout(_In_ const timeout_type timeout);

    /// <summary>
    /// Waits for all previous commands to complete before continuing with
    /// commands issued afterwards.
    /// </summary>
    /// <remarks>
    /// <para>This method issues a <c>*WAI</c> command.</para>
    /// </remarks>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    visa_instrument& wait(void);

    /// <summary>
    /// Write at most <paramref name="cnt" /> bytes of the given data to the
    /// instrument.
    /// </summary>
    /// <param name="buffer">The buffer holding the data to write.</param>
    /// <param name="cnt">The size of <paramref name="buffer" /> in bytes.
    /// </param>
    /// <returns>The number of bytes actually written.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="buffer" /> is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If the operation failed. Note that
    /// a failure here only refers to the use of the API, ie the instrument
    /// can be in a failed state even if the call succeeded. Use
    /// <see cref="throw_on_system_error" /> to check the internal state of
    /// the instrument after the call.</exception>
    std::size_t write(_In_reads_bytes_(cnt) const byte_type *buffer,
        _In_ const std::size_t cnt) const;

    /// <summary>
    /// Writes the given null-terminated data to the instrument.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// </remarks>
    /// <param name="str">A null-terminated string to write to the device.
    /// If this string does not end with the terminal character for
    /// commands, it is appended by the method before writing.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="str" /> is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If the operation failed. Note that
    /// a failure here only refers to the use of the API, ie the instrument
    /// can be in a failed state even if the call succeeded. Use
    /// <see cref="throw_on_system_error" /> to check the internal state of
    /// the instrument after the call.</exception>
    const visa_instrument& write(_In_z_ const char *str) const;

    /// <summary>
    /// Writes the given null-terminated data to the instrument.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// </remarks>
    /// <param name="str">A null-terminated string to write to the device.
    /// If this string does not end with the terminal character for
    /// commands, it is appended by the method before writing.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="str" /> is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If the operation failed. Note that
    /// a failure here only refers to the use of the API, ie the instrument
    /// can be in a failed state even if the call succeeded. Use
    /// <see cref="throw_on_system_error" /> to check the internal state of
    /// the instrument after the call.</exception>
    /// <exception cref="std::logic_error">If the library was compiled
    /// without support for VISA.</exception>
    const visa_instrument& write(_In_z_ const wchar_t *str) const;

    /// <summary>
    /// Writes the given string to the instrument.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// </remarks>
    /// <typeparam name="TChar">The character type in a string. Only
    /// <c>wchar_t</c> and <c>char</c> are supported here.</typeparam>
    /// <param name="str">A string to write to the device.</param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="visa_exception">If the operation failed. Note that
    /// a failure here only refers to the use of the API, ie the instrument
    /// can be in a failed state even if the call succeeded. Use
    /// <see cref="throw_on_system_error" /> to check the internal state of
    /// the instrument after the call.</exception>
    template<class TChar>
    const visa_instrument& write(
        _In_ const std::basic_string<TChar>& str) const;

    /// <summary>
    /// Write the given data to the instrument.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// </remarks>
    /// <param name="buffer">The buffer holding the data to write.</param>
    /// <param name="cnt">The size of <paramref name="buffer" /> in bytes.
    /// </param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="buffer" /> is <c>nullptr</c>.</exception>
    /// <exception cref="visa_exception">If the operation failed. Note that
    /// a failure here only refers to the use of the API, ie the instrument
    /// can be in a failed state even if the call succeeded. Use
    /// <see cref="throw_on_system_error" /> to check the internal state of
    /// the instrument after the call.</exception>
    const visa_instrument& write_all(
        _In_reads_bytes_(cnt) const byte_type *buffer,
        _In_ const std::size_t cnt) const;

    visa_instrument& operator =(const visa_instrument&) = delete;

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The right-hand side operand</param>
    /// <returns><c>*this</c>.</returns>
    visa_instrument& operator =(_Inout_ visa_instrument&& rhs) noexcept;

    /// <summary>
    /// Determines whether the object is valid.
    /// </summary>
    /// <remarks>
    /// An instrument is considered valid until it has been disposed by a
    /// move operation.
    /// </remarks>
    /// <returns><c>true</c> if the instrument is valid, <c>false</c>
    /// otherwise.</returns>
    operator bool(void) const noexcept;

protected:

    /// <summary>
    /// Checks whether the instance is valid and throws an
    /// <see cref="std::runtime_error" /> if this is not the case.
    /// </summary>
    /// <returns>The implementation object for the instrument.</returns>
    /// <exception cref="std::runtime_error">If the implementation has been
    /// released.</exception>
    detail::visa_instrument_impl& check_not_disposed(void);

    /// <summary>
    /// Checks whether the instance is valid and throws an
    /// <see cref="std::runtime_error" /> if this is not the case.
    /// </summary>
    /// <returns>The implementation object for the instrument.</returns>
    /// <exception cref="std::runtime_error">If the implementation has been
    /// released.</exception>
    const detail::visa_instrument_impl& check_not_disposed(void) const;

private:

    static ViStatus _VI_FUNCH on_event(ViSession session,
        ViEventType event_type, ViEvent event, ViAddr context);

    PWROWG_DETAIL_NAMESPACE::visa_instrument_impl *_impl;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/visa_instrument.inl"

#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
#endif /* !defined(_PWROWG_VISA_INSTRUMENT_H) */
