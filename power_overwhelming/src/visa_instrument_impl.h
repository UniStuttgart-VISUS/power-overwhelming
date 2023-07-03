// <copyright file="visa_instrument_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <atomic>
#include <cinttypes>
#include <cstdlib>
#include <map>
#include <mutex>
#include <string>

#include "power_overwhelming/blob.h"
#include "power_overwhelming/convert_string.h"

#include "string_functions.h"
#include "visa_exception.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

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
        /// <returns></returns>
        static visa_instrument_impl *create(_In_ const std::string& path,
            _In_ const std::uint32_t timeout);

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
        /// <returns></returns>
        static visa_instrument_impl *create(_In_z_ const wchar_t *path,
            _In_ const std::uint32_t timeout);

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
        /// <returns></returns>
        static visa_instrument_impl *create(_In_z_ const char *path,
            _In_ const std::uint32_t timeout);

#if defined(POWER_OVERWHELMING_WITH_VISA)
        /// <summary>
        /// The default resource manager.
        /// </summary>
        ViSession resource_manager;

        /// <summary>
        /// The session representing the device connection.
        /// </summary>
        ViSession session;
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~visa_instrument_impl(void);

        /// <summary>
        /// Invoke <see cref="viPrintf" /> on the instrument.
        /// </summary>
        /// <remarks>
        /// This method does nothing if the library was compiled without support
        /// for VISA.
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
        /// Gets the path to the instrument.
        /// </summary>
        /// <returns>The path to the instrument.</returns>
        const std::string& path(void) const noexcept {
            return this->_path;
        }

        /// <summary>
        /// Read from the instrument into the given buffer.
        /// </summary>
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
        /// <param name="buffer_size">The size of the read buffer being used. If
        /// this is less than the response size, the buffer will be resized
        /// until everything was read.
        /// </param>
        /// <returns>The full output from the device.</returns>
        /// <exception cref="visa_exception">If the operation failed.</exception>
        blob read_all(_In_ const std::size_t buffer_size = 1024) const;

        /// <summary>
        /// Release the reference on the object and free it if this was the last
        /// reference.
        /// </summary>
        /// <returns>The new value of the reference counter. If this is zero,
        /// the object has been freed.</returns>
        std::size_t release(void);

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
        /// Write at most <paramref name="cnt" /> bytes of the given data to the
        /// instrument.
        /// </summary>
        /// <param name="buffer">The buffer holding the data to write.</param>
        /// <param name="cnt">The size of <paramref name="buffer" /> in bytes.
        /// </param>
        /// <returns>The number of bytes actually written.</returns>
        /// <exception cref="visa_exception">If the operation failed.</exception>
        std::size_t write(_In_reads_bytes_(cnt) const byte_type *buffer,
            _In_ const std::size_t cnt) const;

        /// <summary>
        /// Writes the given null-terminated data to the instrument.
        /// </summary>
        /// <param name="str">A null-terminated string to write to the device.
        /// </param>
        /// <exception cref="visa_exception">If the operation failed.</exception>
        void write(_In_z_ const char *str) const;

        /// <summary>
        /// Write the given data to the instrument.
        /// </summary>
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
#if defined(POWER_OVERWHELMING_WITH_VISA)
            resource_manager(0), session(0),
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
            _counter(0) { }
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "visa_instrument_impl.inl"
