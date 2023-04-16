// <copyright file="msr_device.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <ios>
#include <string>
#include <vector>

#include "power_overwhelming/msr_sensor.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Private wrapper around the an MSR device file.
    /// </summary>
    /// <remarks>
    /// <para>The rationale for the design of this class and its use in the
    /// <see cref="msr_sensor_impl" /> is the same as for the
    /// <see cref="emi_device" />.</para>
    /// </remarks>
    class msr_device final {

    public:

        /// <summary>
        /// The type used to identify a CPU core.
        /// </summary>
        typedef msr_sensor::core_type core_type;

        /// <summary>
        /// The type of data read from the MSR device file.
        /// </summary>
        typedef std::uint64_t sample_type;

        /// <summary>
        /// The type used to specify device names.
        /// </summary>
        typedef std::basic_string<char> string_type;

        /// <summary>
        /// Determines the path of the MSR device file for the specified CPU
        /// core.
        /// </summary>
        /// <param name="core">The zero-based index of the CPU core to open the
        /// MSR device file for.</param>
        /// <returns>The path to the MSR device file.</returns>
        static string_type path(_In_ const core_type core);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="path">The path to the MSR device.</param>
        explicit msr_device(_In_ const string_type& path);

        msr_device(const msr_device &) = delete;

        /// <summary>
        /// Initialise a new instance by moving another.
        /// </summary>
        /// <param name="rhs">The object ot be moved.</param>
        msr_device(_In_ msr_device&& rhs) noexcept;

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        ~msr_device(void) noexcept;

        /// <summary>
        /// Reads a sample from the file.
        /// </summary>
        /// <param name="where">The offset into the file where to read, which
        /// determines which data are returned.</param>
        /// <returns>The content of the MSR file at the specified lcoation.
        /// </returns>
        /// <exception cref="std::system_error">If reading the MSR file failed.
        /// </exception>
        sample_type read(_In_ const std::streamoff where) const;

        /// <summary>
        /// Reads the whole content of the file
        /// </summary>
        /// <returns>The whole content of the device file.</returns>
        /// <exception cref="std::system_error">If reading the MSR file failed.
        /// </exception>
        std::vector<std::uint8_t> read(void) const;

        msr_device& operator =(const msr_device&) = delete;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        /// <returns><c>*this</c>.</returns>
        msr_device& operator =(_In_ msr_device&& rhs) noexcept;

        /// <summary>
        /// Answer whether the device handle is valid.
        /// </summary>
        /// <returns><c>true</c> if the handle is valid, <c>false</c> otherwise.
        /// </returns>
        inline operator bool(void) const noexcept {
            return (this->_handle != -1);
        }

        /// <summary>
        /// Exposes the native file descriptor.
        /// </summary>
        /// <remarks>
        /// Callers must not close this handle as the object remains its owner.
        /// </remarks>
        /// <returns>The handle for the device.</returns>
        inline operator int(void) const noexcept {
            return this->_handle;
        }

    private:

        int _handle;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
