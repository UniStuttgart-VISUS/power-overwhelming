// <copyright file="visa_scope.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <algorithm>
#include <cinttypes>
#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "visa_exception.h"
#include "visa_scope_impl.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// RAII container for a VISA connection.
    /// </summary>
    class visa_scope final {

    public:

        /// <summary>
        /// Create or obtain the scope for the given device path.
        /// </summary>
        /// <remarks>
        /// If a scope for the given connection does already exist, it is shared
        /// with the new object. Otherwise, a connection to the specified path
        /// is established.
        /// </remarks>
        /// <param name="path">The path to the device to be opened.</param>
        /// <param name="timeout">The timeout for establishing a connection to
        /// the device (in milliseconds). This parameter defaults to 3000.
        /// </param>
        /// <exception cref="std::invalid_argument">If <paramref name="path" />
        /// is <c>nullptr</c>.</exception>
        visa_scope(const char *path, const std::uint32_t timeout = 3000);

#if defined(POWER_OVERWHELMING_WITH_VISA)
        /// <summary>
        /// Converts the scope into the device session it represents.
        /// </summary>
        /// <returns></returns>
        inline operator ViSession(void) const noexcept {
            return this->_impl->session;
        }
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

    private:

        static std::map<std::string, std::weak_ptr<visa_scope_impl>> _scopes;
        static std::mutex _lock_scopes;

        std::shared_ptr<visa_scope_impl> _impl;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
