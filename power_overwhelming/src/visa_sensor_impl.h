// <copyright file="visa_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <string>
#include <vector>

#include "power_overwhelming/convert_string.h"

#include "visa_library.h"
#include "visa_scope.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Stores the data of a generic VISA-based sensor.
    /// </summary>
    struct visa_sensor_impl {

        /// <summary>
        /// Represents the type of native VISA status codes.
        /// </summary>
        typedef visa_exception::value_type status_type;

        /// <summary>
        /// The VISA path of the device.
        /// </summary>
        std::string path;

        /// <summary>
        /// The user-facing name of the sensor.
        /// </summary>
        std::wstring sensor_name;

        /// <summary>
        /// The VISA scope representing the connection to the device.
        /// </summary>
        visa_scope scope;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        visa_sensor_impl(_In_z_ const char *path,
            _In_ const std::int32_t timeout);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        visa_sensor_impl(_In_z_ const wchar_t *path,
            _In_ const std::int32_t timeout);

        /// <summary>
        /// Call <see cref="viClear" /> on the instrument, which will flush all
        /// buffers.
        /// </summary>
        /// <remarks>
        /// This method does nothing if the library was compiled without support
        /// for VISA.
        /// </remarks>
        /// <exception cref="visa_exception">If the operation failed.
        /// </exception>
        void clear(void);

        /// <summary>
        /// Clear the error queue of the instrument.
        /// </summary>
        /// <remarks>
        /// This method does nothing if the library was compiled without support
        /// for VISA.
        /// </remarks>
        /// <exception cref="visa_exception">If the operation failed.
        /// </exception>
        void clear_status(void);

        /// <summary>
        /// Send the &quot;identify&quot; SCPI command to the instrument and
        /// return its response.
        /// </summary>
        /// <returns></returns>
        /// <exception cref="visa_exception">If the operation failed.
        /// </exception>
        std::string identify(void);

        /// <summary>
        /// Invoke <see cref="viPrintf" /> on the instrument.
        /// </summary>
        /// <remarks>
        /// This method does nothing if the library was compiled without support
        /// for VISA.
        /// </remarks>
        /// <typeparam name="TArgs"></typeparam>
        /// <param name="format"></param>
        /// <param name="args"></param>
        /// <exception cref="visa_exception">If the operation failed. Note that
        /// a failure here only refers to the use of the API, ie the instrument
        /// can be in a failed state even if the call succeeded. Use
        /// <see cref="throw_on_system_error" /> to check the internal state of
        /// the instrument after the call.</exception>
        template<class... TArgs>
        void printf(_In_z_ const char *format, TArgs&&... args);

        /// <summary>
        /// Write the given data to the instrument and read a response of
        /// at most <paramref name="buffer_size" /> bytes.
        /// </summary>
        /// <param name="query"></param>
        /// <param name="cnt"></param>
        /// <param name="buffer_size"></param>
        /// <returns></returns>
        /// <exception cref="std::invalid_argument">If <paramref name="query" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="visa_exception">If the operation failed. Note that
        /// a failure here only refers to the use of the API, ie the instrument
        /// can be in a failed state even if the call succeeded. Use
        /// <see cref="throw_on_system_error" /> to check the internal state of
        /// the instrument after the call.</exception>
        std::vector<std::uint8_t> query(
            _In_reads_bytes_(cnt) const std::uint8_t *query,
            _In_ const std::size_t cnt,
            _In_ const std::size_t buffer_size = 1024);

        /// <summary>
        /// Write the given data to the instrument and read a response of
        /// at most <paramref name="buffer_size" /> bytes.
        /// </summary>
        /// <param name="query"></param>
        /// <param name="buffer_size"></param>
        /// <returns></returns>
        std::vector<std::uint8_t> query(_In_ const std::string& query,
            _In_ const std::size_t buffer_size = 1024);

        /// <summary>
        /// Write the given query string to the instrument and read a response
        /// of at most <paramref name="buffer_size" /> bytes.
        /// </summary>
        /// <param name="query"></param>
        /// <param name="buffer_size"></param>
        /// <returns></returns>
        std::vector<std::uint8_t> query(_In_ const std::wstring &query,
            _In_ const std::size_t buffer_size = 1024);

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
        /// <exception cref="visa_exception">If the operation failed. Note that
        /// a failure here only refers to the use of the API, ie the instrument
        /// can be in a failed state even if the call succeeded. Use
        /// <see cref="throw_on_system_error" /> to check the internal state of
        /// the instrument after the call.</exception>
        std::size_t read(_Out_writes_bytes_(cnt) std::uint8_t *buffer,
            _In_ const std::size_t cnt);

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
        /// <exception cref="visa_exception">If the operation failed. Note that
        /// a failure here only refers to the use of the API, ie the instrument
        /// can be in a failed state even if the call succeeded. Use
        /// <see cref="throw_on_system_error" /> to check the internal state of
        /// the instrument after the call.</exception>
        std::vector<std::uint8_t> read(
            _In_ const std::size_t buffer_size = 1024);

#if defined(POWER_OVERWHELMING_WITH_VISA)
        /// <summary>
        /// Shortcut to <see cref="viAttribute" /> on the device session
        /// represented by <see cref="scope" />.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="value"></param>
        /// <exception cref="visa_exception"></exception>
        void set_attribute(_In_ ViAttr name, _In_ ViAttrState value);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

        /// <summary>
        /// Shortcut to <see cref="viSetBuf" /> on the device session
        /// represented by <see cref="scope" />.
        /// </summary>
        /// <param name="mask"></param>
        /// <param name="size"></param>
        /// <exception cref="visa_exception">If the operation failed. Note that
        /// a failure here only refers to the use of the API, ie the instrument
        /// can be in a failed state even if the call succeeded. Use
        /// <see cref="throw_on_system_error" /> to check the internal state of
        /// the instrument after the call.</exception>
        void set_buffer(_In_ const std::uint16_t mask,
            _In_ const std::uint32_t size);

        /// <summary>
        /// Query the oldest error in the queue and returns the message
        /// associated with it to <paramref name="message" />.
        /// </summary>
        /// <remarks>
        /// This method always returns zero if the library was compiled without
        /// support for VISA.
        /// </remarks>
        /// <param name="message">The message associated with the system error
        /// code returned.</param>
        /// <returns>The current system error, or zero if the system has no
        /// previous error.</returns>
        /// <exception cref="visa_exception">If the current system state could
        /// not be retrieved.</exception>
        int system_error(_Out_ std::string& message);

        /// <summary>
        /// Query the oldes error in the queue.
        /// </summary>
        /// <remarks>
        /// This method always returns zero if the library was compiled without
        /// support for VISA.
        /// </remarks>
        /// <returns>The current system error, or zero if the system has no
        /// previous error.</returns>
        /// <exception cref="visa_exception">If the current system state could
        /// not be retrieved.</exception>
        int system_error(void);

        /// <summary>
        /// Write the given data to the instrument.
        /// </summary>
        /// <remarks>
        /// This method does nothing if the library was compiled without support
        /// for VISA.
        /// </remarks>
        /// <param name="buffer"></param>
        /// <param name="cnt"></param>
        /// <returns></returns>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="buffer" /> is <c>nullptr</c>.</exception>
        /// <exception cref="visa_exception">If the operation failed. Note that
        /// a failure here only refers to the use of the API, ie the instrument
        /// can be in a failed state even if the call succeeded. Use
        /// <see cref="throw_on_system_error" /> to check the internal state of
        /// the instrument after the call.</exception>
        std::size_t write(_In_reads_bytes_(cnt) const std::uint8_t *buffer,
            _In_ const std::size_t cnt);

        /// <summary>
        /// Write the given data to the instrument.
        /// </summary>
        /// <remarks>
        /// This method does nothing if the library was compiled without support
        /// for VISA.
        /// </remarks>
        /// <param name="buffer"></param>
        /// <returns></returns>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="buffer" /> is <c>nullptr</c>.</exception>
        /// <exception cref="visa_exception">If the operation failed. Note that
        /// a failure here only refers to the use of the API, ie the instrument
        /// can be in a failed state even if the call succeeded. Use
        /// <see cref="throw_on_system_error" /> to check the internal state of
        /// the instrument after the call.</exception>
        std::size_t write(_In_ const std::string& buffer);

        /// <summary>
        /// Write the given data to the instrument.
        /// </summary>
        /// <remarks>
        /// This method does nothing if the library was compiled without support
        /// for VISA.
        /// </remarks>
        /// <param name="buffer"></param>
        /// <returns></returns>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="buffer" /> is <c>nullptr</c>.</exception>
        /// <exception cref="visa_exception">If the operation failed. Note that
        /// a failure here only refers to the use of the API, ie the instrument
        /// can be in a failed state even if the call succeeded. Use
        /// <see cref="throw_on_system_error" /> to check the internal state of
        /// the instrument after the call.</exception>
        std::size_t write(_In_ const std::wstring& buffer);

    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "visa_sensor_impl.inl"
