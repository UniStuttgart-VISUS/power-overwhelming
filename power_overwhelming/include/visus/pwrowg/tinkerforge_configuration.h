// <copyright file="tinkerforge_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TINKERFORGE_CONFIGURATION_H)
#define _PWROWG_TINKERFORGE_CONFIGURATION_H
#pragma once

#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/tinkerforge_sample_averaging.h"
#include "visus/pwrowg/tinkerforge_sensor_source.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Provides additional configuration options for Tingerforge-based sensors when
/// creating a <see cref="sensor_array" />.
/// </summary>
class tinkerforge_configuration final {

public:

    /// <summary>
    /// Possible sources that can be read from Tinkerforge.
    /// </summary>
    typedef tinkerforge_sensor_source source_type;

    /// <summary>
    /// The default host on which brickd is assumed to run.
    /// </summary>
    static constexpr const char *default_host = "localhost";

    /// <summary>
    /// The default port on which brickd is assumed to listen on.
    /// </summary>
    static constexpr const std::uint16_t default_port = 4223;

    /// <summary>
    /// The default source to sample.
    /// </summary>
    static constexpr const source_type default_source = source_type::all;

    tinkerforge_configuration(void);

    /// <summary>
    /// Answer the host where the Tinkerforge daemon is running.
    /// </summary>
    /// <returns>The name of the host where the daemon is running.</returns>
    inline _Ret_maybenull_z_ const char *host(void) const noexcept {
        return this->_host.as<char>();
    }

    tinkerforge_configuration& host(_In_z_ const char *host);

    tinkerforge_configuration& host(_In_z_ const wchar_t *host);

    inline std::uint16_t port(void) const noexcept {
        return this->_port;
    }

    tinkerforge_configuration& port(_In_ const std::uint16_t port) noexcept;

    inline source_type source(void) const noexcept {
        return this->_source;
    }

    tinkerforge_configuration& source(_In_ const source_type source) noexcept;

private:

    blob _host;
    std::uint16_t _port;
    source_type _source;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_TINKERFORGE_CONFIGURATION_H) */
