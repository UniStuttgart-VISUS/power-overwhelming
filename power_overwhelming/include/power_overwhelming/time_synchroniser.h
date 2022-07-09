// <copyright file="time_synchroniser.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations */
    namespace detail { struct time_synchroniser_impl; }

    /// <summary>
    /// A collector is a set of sensors that asynchronously collect data and
    /// write them to a file.
    /// </summary>
    class POWER_OVERWHELMING_API time_synchroniser final {

    public:

        /// <summary>
        /// Initialise a new instance.
        /// </summary>
        /// <remarks>
        /// The default instance is created disposed, ie cannot be used for
        /// anything, but assigning another instance created by one of the
        /// static factory methods.
        /// </remarks>
        inline time_synchroniser(void) : _impl(nullptr) { }

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs"></param>
        /// <returns></returns>
        inline time_synchroniser(time_synchroniser&& rhs) noexcept
                : _impl(rhs._impl) {
            rhs._impl = nullptr;
        }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~time_synchroniser(void);

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        time_synchroniser& operator =(time_synchroniser&& rhs) noexcept;

        /// <summary>
        /// Determines whether the object is valid.
        /// </summary>
        /// <remarks>
        /// The synchroniser is considered valid until it has been disposed by a
        /// move operation.
        /// </remarks>
        /// <returns><c>true</c> if the object is valid, <c>false</c>
        /// otherwise.</returns>
        operator bool(void) const noexcept;

    private:

        detail::time_synchroniser_impl *_impl;

    };

} /* namespace power_overwhelming */
} /* namespace visus */
