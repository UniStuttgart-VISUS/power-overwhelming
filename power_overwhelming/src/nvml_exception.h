// <copyright file="nvml_exception.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <exception>
#include <string>

#include <nvml.h>


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// An exception caused by a failure in the NVIDIA Management Library.
    /// </summary>
    class nvml_exception : public std::exception {

    public:

        /// <summary>
        /// The native error type.
        /// </summary>
        typedef ::nvmlReturn_t value_type;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="code">The error code, which also determines the error
        /// message.</param>
        nvml_exception(const value_type code);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="code">The error code.</param>
        /// <param name="message">A custom error message.</param>
        nvml_exception(const value_type code, const char *message)
            : std::exception(message), _code(code) { }

        /// <summary>
        /// Answer the native error code associated with the exception.
        /// </summary>
        /// <returns></returns>
        value_type code(void) const noexcept {
            return this->_code;
        }

    private:

        value_type _code;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
