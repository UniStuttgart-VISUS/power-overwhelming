// <copyright file="visa_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <string>
#include <vector>

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
        /// <param name="path"></param>
        visa_sensor_impl(const char *path, const std::int32_t timeout);

        /// <summary>
        /// Call <see cref="viClear" /> on the instrument, which will clear any
        /// queued error states.
        /// </summary>
        /// <remarks>
        /// This method does nothing if the library was compiled without support
        /// for VISA.
        /// </remarks>
        void clear(void);

        /// <summary>
        /// Send the &quot;identify&quot; SCPI command to the instrument and
        /// return its response.
        /// </summary>
        /// <returns></returns>
        std::string identify(void);

#if defined(POWER_OVERWHELMING_WITH_VISA)
        /// <summary>
        /// Invoke <see cref="viPrintf" /> on the instrument.
        /// </summary>
        /// <typeparam name="TArgs"></typeparam>
        /// <param name="format"></param>
        /// <param name="args"></param>
        template<class... TArgs>
        void printf(ViConstString format, TArgs&&... args);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

#if defined(POWER_OVERWHELMING_WITH_VISA)
        /// <summary>
        /// Write the given data to the instrument and read a response of
        /// at most <paramref name="buffer_size" /> bytes.
        /// </summary>
        /// <param name="query"></param>
        /// <param name="cnt"></param>
        /// <param name="buffer_size"></param>
        /// <returns></returns>
        /// <exception cref="visa_exception"></exception>
        std::vector<ViByte> query(ViConstBuf query, ViUInt32 cnt,
            ViUInt32 buffer_size = 1024);

        /// <summary>
        /// Write the given data to the instrument and read a response of
        /// at most <paramref name="buffer_size" /> bytes.
        /// </summary>
        /// <param name="query"></param>
        /// <param name="buffer_size"></param>
        /// <returns></returns>
        inline std::vector<ViByte> query(const std::vector<ViByte>& query,
                ViUInt32 buffer_size = 1024) {
            return this->query(query.data(),
                static_cast<ViUInt32>(query.size()), buffer_size);
        }

        /// <summary>
        /// Write the given data to the instrument and read a response of
        /// at most <paramref name="buffer_size" /> bytes.
        /// </summary>
        /// <param name="query"></param>
        /// <param name="buffer_size"></param>
        /// <returns></returns>
        std::vector<ViByte> query(const std::string &query,
            ViUInt32 buffer_size = 1024);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

        /// <summary>
        /// Read from the instrument into the given buffer.
        /// </summary>
        /// <remarks>
        /// This method has no effect if the library has been compiled without
        /// support for VISA.
        /// </remarks>
        /// <param name="buffer">The buffer to write the data to.</param>
        /// <param name="cnt">The size of the buffer in bytes.</param>
        /// <returns></returns>
        /// <exception cref="visa_exception">If the operation did not succeed,
        /// which includes the warning state like an insufficient output buffer
        /// being provided.</exception>
        std::size_t read(std::uint8_t *buffer, std::size_t cnt);

#if defined(POWER_OVERWHELMING_WITH_VISA)
        /// <summary>
        /// Shortcut to <see cref="viAttribute" /> on the device session
        /// represented by <see cref="scope" />.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="value"></param>
        /// <exception cref="visa_exception"></exception>
        void set_attribute(ViAttr name, ViAttrState value);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

#if defined(POWER_OVERWHELMING_WITH_VISA)
        /// <summary>
        /// Shortcut to <see cref="viSetBuf" /> on the device session
        /// represented by <see cref="scope" />.
        /// </summary>
        /// <param name="mask"></param>
        /// <param name="size"></param>
        /// <exception cref="visa_exception"></exception>
        void set_buffer(ViUInt16 mask, ViUInt32 size);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

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
        int system_error(std::string& message);

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
        /// Checks <see cref="system_error" /> and throws a
        /// <see cref="std::runtime_error" /> if it does not return zero.
        /// </summary>
        /// <exception cref="visa_exception">If the current system state could
        /// not be retrieved.</exception>
        /// <exception cref="std::runtime_error">If the current system state was
        /// retrieved and is not zero.</exception>
        void throw_on_system_error(void);

#if defined(POWER_OVERWHELMING_WITH_VISA)
        /// <summary>
        /// Write the given data to the instrument.
        /// </summary>
        /// <param name="buffer"></param>
        /// <param name="cnt"></param>
        /// <returns></returns>
        /// <exception cref="visa_exception"></exception>
        ViUInt32 write(ViConstBuf buffer, ViUInt32 cnt);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "visa_sensor_impl.inl"
