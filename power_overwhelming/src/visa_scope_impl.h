// <copyright file="visa_scope_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>

#include "visa_exception.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Stores the actual VISA resources and provides some convenience methods.
    /// </summary>
    struct visa_scope_impl final {

#if defined(POWER_OVERWHELMING_WITH_VISA)
        /// <summary>
        /// The default resource manager.
        /// </summary>
        ViSession resource_manager;

        /// <summary>
        /// The session representing the device connection.
        /// </summary>
        ViSession session;
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="path"></param>
        /// <param name="timeout"></param>
        visa_scope_impl(const std::string& path, const std::uint32_t timeout);

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~visa_scope_impl(void);
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
