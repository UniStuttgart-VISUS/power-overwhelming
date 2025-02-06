// <copyright file="tinkerforge_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TINKERFORGE_CONFIGURATION_H)
#define _PWROWG_TINKERFORGE_CONFIGURATION_H
#pragma once

#include <chrono>
#include <cmath>

#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/sensor_configuration.h"
#include "visus/pwrowg/tinkerforge_conversion_time.h"
#include "visus/pwrowg/tinkerforge_error_count.h"
#include "visus/pwrowg/tinkerforge_sample_averaging.h"

#include "tinkerforge_bricklet.h"
#include "tinkerforge_exception.h"
#include "tinkerforge_scope.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Provides additional configuration options for Tingerforge-based sensors when
/// creating a <see cref="sensor_array" />.
/// </summary>
class POWER_OVERWHELMING_API tinkerforge_configuration final
        : public sensor_configuration {

public:

    /// <summary>
    /// Represents the location of a Tinkerforge Brickd.
    /// </summary>
    class end_point final {

    public:

        /// <summary>
        /// Initialises a new instance with the default port on localhost.
        /// </summary>
        end_point(void);

        /// <summary>
        /// Initialises a new instance with the default port.
        /// </summary>
        /// <param name="host">The host name or address.</param>
        end_point(_In_z_ const char *host);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="host">The host name or address.</param>
        /// <param name="port">The port number.</param>
        end_point(_In_z_ const char *host, _In_ const std::uint16_t port);

        /// <summary>
        /// Answer the name or address of the host where Brickd is runnning.
        /// </summary>
        /// <returns>The host name or address.</returns>
        inline _Ret_maybenull_z_ const char *name(void) const noexcept {
            return this->_name.as<char>();
        }

        /// <summary>
        /// Answer the port the Brickd is listening on.
        /// </summary>
        /// <returns>The port of the Brick.</returns>
        inline std::uint16_t port(void) const noexcept {
            return this->_port;
        }

    private:

        blob _name;
        std::uint16_t _port;
    };

    /// <summary>
    /// A unique identifer for the <see cref="tinkerforge_configuration" /> type.
    /// </summary>
    static const guid id;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    tinkerforge_configuration(void);

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~tinkerforge_configuration(void);

    /// <summary>
    /// Adds the given end point to the list of end points.
    /// </summary>
    /// <param name="address">The end point to be added.</param>
    /// <returns><c>*this</c>.</returns>
    tinkerforge_configuration& add_end_point(_In_ const end_point& address);

    /// <summary>
    /// Answer the number of registered end points.
    /// </summary>
    /// <returns>The number of registered end points.</returns>
    std::size_t count_end_points(void) const noexcept;

    /// <summary>
    /// Answer the array of registered <see cref="end_point" />s.
    /// </summary>
    /// <remarks>
    /// The size of the array can be obtained from
    /// <see cref="count_end_points" />.
    /// </remarks>
    /// <returns>The end points of the Brickds.</returns>
    inline _Ret_valid_ const end_point *end_points(void) const noexcept {
        auto retval = this->_end_points.as<end_point>();
        _Analysis_assume_(retval != nullptr);
        return retval;
    }

    /// <summary>
    /// Sets all end points.
    /// </summary>
    /// <param name="addresses">An array of at least <paramref name="cnt" /> end
    /// point addresses.</param>
    /// <param name="cnt">The number of end points provided.</param>
    /// <returns><c>*this</c>.</returns>
    tinkerforge_configuration& end_points(_In_reads_(cnt) end_point *addresses,
        _In_ const std::size_t cnt);

    /// <summary>
    /// Answer the timeout for connecting to the brickd, in milliseconds.
    /// </summary>
    /// <returns>The timeout in milliseconds.</returns>
    inline std::uint32_t timeout(void) const noexcept {
        return this->_timeout;
    }

    /// <summary>
    /// Sets the timeout for connecting to the brickd.
    /// </summary>
    /// <typeparam name="TType"></typeparam>
    /// <typeparam name="TPeriod"></typeparam>
    /// <param name="timeout"></param>
    /// <returns></returns>
    template<class TType, class TPeriod>
    inline tinkerforge_configuration& timeout(
            _In_ const std::chrono::duration<TType, TPeriod> timeout) {
        auto m= std::chrono::duration_cast<std::chrono::milliseconds>(timeout);
        this->_timeout = std::abs(m.count());
        return *this;
    }

private:

    /// <summary>
    /// Destruct all existing <see cref="_end_points" />, but do not free the
    /// memory.
    /// </summary>
    void destroy_end_points(void);

    blob _end_points;
    std::uint64_t _timeout;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_TINKERFORGE_CONFIGURATION_H) */
