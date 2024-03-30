// <copyright file="nvml_scope.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart.
// Licenced under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// A RAII container for the NVML library.
    /// </summary>
    /// <remarks>
    /// As NVML uses an internal reference counter, multiple scopes can be used
    /// by an application. NVML will not be unloaded unless the last scope was
    /// destroyed.
    /// </remarks>
    class nvml_scope final {

    public:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <exception cref="nvml_exception">If the NVML could not be loaded.
        /// </exception>
        nvml_scope(void);

        nvml_scope(const nvml_scope&) = delete;

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~nvml_scope(void);

        nvml_scope& operator =(const nvml_scope&) = delete;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
