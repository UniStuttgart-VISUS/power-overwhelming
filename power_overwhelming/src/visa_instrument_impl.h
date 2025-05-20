// <copyright file="visa_instrument_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_VISA_INSTRUMENT_IMPL_H)
#define _PWROWG_VISA_INSTRUMENT_IMPL_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_VISA)

#include <atomic>
#include <cinttypes>
#include <cstdlib>
#include <functional>
#include <map>
#include <mutex>
#include <string>

#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/visa_instrument.h"

#include "string_functions.h"
#include "visa_error_category.h"
#include "visa_event_handler.h"
#include "visa_library.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Stores the actual VISA resources for the connection to the 
/// instrument and provides some convenience methods.
/// </summary>
struct visa_instrument_impl final {

public:

    /// <summary>
    /// The type representing a single byte.
    /// </summary>
    typedef blob::byte_type byte_type;

    /// <summary>
    /// Create or open the instrument at the specified path.
    /// </summary>
    /// <remarks>
    /// The lookup of existing instruments and the potential allocation of
    /// new ones is thread-safe.
    /// </remarks>
    /// <param name="path">The path to the device to open.</param>
    /// <param name="timeout">The timeout for establishing the connection
    /// in milliseconds.</param>
    /// <param name="is_new ">If not <c>nullptr</c>, this variable is set to
    /// <c>true</c> if the instance was newly created, or <c>false</c> if
    /// an existing connection was reused.</param>
    /// <returns>An implementation object for the VISA device matching the
    /// given path. This can either be an existing one or a new one.
    /// </returns>
    static visa_instrument_impl *create(_In_ const std::string& path,
        _In_ const std::uint32_t timeout,
        _Out_opt_ bool *is_new = nullptr);

    /// <summary>
    /// Create or open the instrument at the specified path.
    /// </summary>
    /// <remarks>
    /// The lookup of existing instruments and the potential allocation of
    /// new ones is thread-safe.
    /// </remarks>
    /// <param name="path">The path to the device to open.</param>
    /// <param name="timeout">The timeout for establishing the connection
    /// in milliseconds.</param>
    /// <param name="is_new ">If not <c>nullptr</c>, this variable is set to
    /// <c>true</c> if the instance was newly created, or <c>false</c> if
    /// an existing connection was reused.</param>
    /// <returns>An implementation object for the VISA device matching the
    /// given path. This can either be an existing one or a new one.
    /// </returns>
    static visa_instrument_impl *create(_In_z_ const wchar_t *path,
        _In_ const std::uint32_t timeout,
        _Out_opt_ bool *is_new = nullptr);

    /// <summary>
    /// Create or open the instrument at the specified path.
    /// </summary>
    /// <remarks>
    /// The lookup of existing instruments and the potential allocation of
    /// new ones is thread-safe.
    /// </remarks>
    /// <param name="path">The path to the device to open.</param>
    /// <param name="timeout">The timeout for establishing the connection
    /// in milliseconds.</param>
    /// <param name="is_new ">If not <c>nullptr</c>, this variable is set to
    /// <c>true</c> if the instance was newly created, or <c>false</c> if
    /// an existing connection was reused.</param>
    /// <returns>An implementation object for the VISA device matching the
    /// given path. This can either be an existing one or a new one.
    /// </returns>
    static visa_instrument_impl *create(_In_z_ const char *path,
        _In_ const std::uint32_t timeout,
        _Out_opt_ bool *is_new = nullptr);

    /// <summary>
    /// Enumerates all currently active instances of VISA instruments.
    /// </summary>
    /// <remarks>
    /// <para>This method is protected against concurrent creation and
    /// removal of instances.</para>
    /// <para>The callback passed to the method should not throw.</para>
    /// </remarks>
    /// <param name="callback">The callback to be invoked.</param>
    /// <returns>The number of times the callback has been invoked.
    /// </returns>
    static std::size_t foreach(
        _In_ const std::function<bool(visa_instrument_impl *)>& callback);

    /// <summary>
    /// Enables internal checks of the instrument's status.
    /// </summary>
    bool enable_system_checks;

    /// <summary>
    /// A callback for asynchronous OPC queries.
    /// </summary>
    visa_event_handler opc_callback;

    /// <summary>
    /// The default resource manager.
    /// </summary>
    ViSession resource_manager;

    /// <summary>
    /// The session representing the device connection.
    /// </summary>
    ViSession session;

    /// <summary>
    /// The terminal character to be appended to a command when using the
    /// string-parameterised <see cref="write" /> method.
    /// </summary>
    /// <remarks>
    /// The terminal character is only automatically appended if it is
    /// non-zero. Setting this field zero will disable the auto-termination
    /// functionality.
    /// </remarks>
    char terminal_character;

    /// <summary>
    /// Remembers whether the device is VXI-capable.
    /// </summary>
    bool vxi;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~visa_instrument_impl(void);

    /// <summary>
    /// Checks for a system error if <see cref="enable_system_checks" />
    /// is <c>true</c> and throws an exception if there is a system errror.
    /// </summary>
    void check_system_error(void) const;

    /// <summary>
    /// Answer the current value of the reference counter.
    /// </summary>
    /// <returns></returns>
    inline std::size_t counter(void) const noexcept {
        return this->_counter.load();
    }

    /// <summary>
    /// Prevents events of the specified type being delivered with the
    /// specified mechanism.
    /// </summary>
    /// <param name="event_type"></param>
    /// <param name="mechanism"></param>
    void disable_event(_In_ const ViEventType event_type,
        _In_ const ViUInt16 mechanism = VI_HNDLR);

    /// <summary>
    /// Enable delivery of events of the specified type using the specified
    /// mechanism.
    /// </summary>
    /// <param name="event_type"></param>
    /// <param name="mechanism"></param>
    /// <param name="context"></param>
    void enable_event(_In_  const ViEventType event_type,
        _In_ const ViUInt16 mechanism = VI_HNDLR,
        _In_ const ViEventFilter context = VI_NULL);

    /// <summary>
    /// Reads and discards all data that are possibly in the input buffer of
    /// the instrument.
    /// </summary>
    void flush_data(void);

    /// <summary>
    /// Invoke <see cref="viPrintf" /> on the instrument.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if the library was compiled without
    /// support for VISA.</para>
    /// <para>This method will perform a check of the system state on
    /// completion if <see cref="enable_system_checks" /> is <c>true</c>.
    /// </para>
    /// </remarks>
    /// <typeparam name="TArgs">The types of the arguments to be formatted.
    /// </typeparam>
    /// <param name="format">The <see cref="printf" />-style format string.
    /// </param>
    /// <param name="args">The list of arguments to format.</param>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    template<class... TArgs>
    void format(_In_z_ const char *format, TArgs&&... args) const;

    /// <summary>
    /// Send the &quot;identify&quot; SCPI command to the instrument and
    /// return its response.
    /// </summary>
    /// <returns>The name of the instrument.</returns>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    std::string identify(void) const;

    /// <summary>
    /// Installs the given callback for the given type of event.
    /// </summary>
    /// <remarks>
    /// <para>This method will perform a check of the system state on
    /// completion if <see cref="enable_system_checks" /> is <c>true</c>.
    /// </para>
    /// </remarks>
    /// <param name="event_type"></param>
    /// <param name="handler"></param>
    /// <param name="context"></param>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    void install_handler(_In_ const ViEventType event_type,
        _In_ const ViHndlr handler, _In_ ViAddr context);

    /// <summary>
    /// Gets the interface type of the underlying session.
    /// </summary>
    /// <returns>The interface type.</returns>
    /// <exception cref="std::runtime_error">If the method is called on an
    /// object that has been disposed by moving it.</exception>
    /// <exception cref="std::logic_error">If the library was compiled
    /// without support for VISA.</exception>
    std::uint16_t interface_type(void) const;

    /// <summary>
    /// Gets the path to the instrument.
    /// </summary>
    /// <returns>The path to the instrument.</returns>
    const std::string& path(void) const noexcept {
        return this->_path;
    }

    /// <summary>
    /// Read from the instrument into the given buffer.
    /// </summary>
    /// <remarks>
    /// <para>This method never checks the system state, because it is
    /// required for implementing the check of the system state.</para>
    /// </remarks>
    /// <param name="buffer">The buffer to write the data to.</param>
    /// <param name="cnt">The size of the buffer in bytes.</param>
    /// <returns>The number of bytes actually read. If this is equal to
    /// <see cref="cnt" />, the response has most likely not been read in
    /// total and you should call the method again.</returns>
    /// <exception cref="visa_exception">If the operation failed.</exception>
    std::size_t read(_Out_writes_bytes_(cnt) byte_type *buffer,
        _In_ const std::size_t cnt) const;

    /// <summary>
    /// Read a full response.
    /// </summary>
    /// <remarks>
    /// <para>This method never checks the system state, because it is
    /// required for implementing the check of the system state.</para>
    /// </para>
    /// </remarks>
    /// <param name="buffer">The buffer used to receive the response. The method
    /// will grow it as necessary. You can preallocate the buffer with the
    /// suggested initial size.</param>
    /// <returns><paramref name="buffer" />.</returns>
    /// <exception cref="visa_exception">If the operation failed.</exception>
    blob& read_all(_Inout_ blob& buffer) const;

    /// <summary>
    /// Reads a binary response starting with the # marker for the number of
    /// bytes to follow.
    /// </summary>
    /// <remarks>
    /// <para>This method never checks the system state, because it is
    /// required for implementing the check of the system state.</para>
    /// </para>
    /// </remarks>
    /// <returns>The binary data excluding the length marker.</returns>
    /// <exception cref="visa_exception">If the operation failed.</exception>
    /// <exception cref="std::runtime_error">If the data being read are not
    /// binary.</exception>
    blob read_binary(void) const;

    /// <summary>
    /// Release the reference on the object and free it if this was the last
    /// reference.
    /// </summary>
    /// <returns>The new value of the reference counter. If this is zero,
    /// the object has been freed.</returns>
    std::size_t release(void);

    /// <summary>
    /// Gets the <c>VI_ATTR_RSRC_CLASS</c> attribute.
    /// </summary>
    /// <returns>The resource class.</returns>
    std::string resource_class(void) const;

    /// <summary>
    /// Query the oldest error in the queue and returns the message
    /// associated with it to <paramref name="message" />.
    /// </summary>
    /// <param name="message">The message associated with the system error
    /// code returned.</param>
    /// <returns>The current system error, or zero if the system has no
    /// previous error.</returns>
    /// <exception cref="visa_exception">If the current system state could
    /// not be retrieved.</exception>
    int system_error(_Out_ std::string& message) const;

    /// <summary>
    /// Checks the instrument's state and throws a
    /// <see cref="std::runtime_exception" /> if the device is in an error
    /// state.
    /// </summary>
    /// <remarks>
    /// <para><b>Important:</c> This method must not be called from within
    /// any of the raw read or write functions in this implementation class
    /// as this will cause an infinite recursion. The <see cref="format" />
    /// template is OK as it is not used here.</para>
    /// </remarks>
    void throw_on_system_error(void) const;

    /// <summary>
    /// Uninstalls the specified callback.
    /// </summary>
    /// <remarks>
    /// <para>This method will perform a check of the system state on
    /// completion if <see cref="enable_system_checks" /> is <c>true</c>.
    /// </para>
    /// </remarks>
    /// <param name="event_type"></param>
    /// <param name="handler"></param>
    /// <param name="context"></param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    void uninstall_handler(_In_ const ViEventType event_type,
        _In_ const ViHndlr handler, _In_ ViAddr context);

    /// <summary>
    /// Write at most <paramref name="cnt" /> bytes of the given data to the
    /// instrument.
    /// </summary>
    /// <remarks>
    /// <para>This method never checks the system state, because it is
    /// required for implementing the check of the system state.</para>
    /// </para>
    /// </remarks>
    /// <param name="buffer">The buffer holding the data to write.</param>
    /// <param name="cnt">The size of <paramref name="buffer" /> in bytes.
    /// </param>
    /// <returns>The number of bytes actually written.</returns>
    /// <exception cref="visa_exception">If the operation failed.</exception>
    /// <
    std::size_t write(_In_reads_bytes_(cnt) const byte_type *buffer,
        _In_ const std::size_t cnt) const;

    /// <summary>
    /// Writes the given null-terminated data to the instrument.
    /// </summary>
    /// <remarks>
    /// <para>If the command is not terminated with
    /// <see cref="terminal_character" />, the terminal character will be
    /// appended to <see cref="str" /> before writing.</para>
    /// <para>This method never checks the system state, because it is
    /// required for implementing the check of the system state.</para>
    /// </para>
    /// </remarks>
    /// <param name="str">A null-terminated string to write to the device.
    /// </param>
    /// <exception cref="visa_exception">If the operation failed.</exception>
    void write(_In_z_ const char *str) const;

    /// <summary>
    /// Write the given data to the instrument.
    /// </summary>
    /// <remarks>
    /// <para>This method never checks the system state, because it is
    /// required for implementing the check of the system state.</para>
    /// </para>
    /// </remarks>
    /// <param name="buffer">The buffer holding the data to write.</param>
    /// <param name="cnt">The size of <paramref name="buffer" /> in bytes.
    /// </param>
    /// <returns><c>*this</c>.</returns>
    /// <exception cref="visa_exception">If the operation failed.
    /// </exception>
    void write_all(_In_reads_bytes_(cnt) const byte_type *buffer,
        _In_ const std::size_t cnt) const;

private:

    static std::map<std::string, visa_instrument_impl *> _instruments;
    static std::mutex _lock_instruments;
    std::atomic<std::size_t> _counter;
    std::string _path;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline visa_instrument_impl(void) :
        enable_system_checks(false), resource_manager(0), session(0),
        terminal_character('\n'), vxi(false),
        _counter(0) { }
};

PWROWG_DETAIL_NAMESPACE_END

#include "visa_instrument_impl.inl"

#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
#endif /* !defined(_PWROWG_VISA_INSTRUMENT_IMPL_H) */
