// <copyright file="tinkerforge_error_count.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Provides a container for the error statistics that can be retrieved from
/// the <see cref="tinkerforge_sensor" />.
/// </summary>
struct POWER_OVERWHELMING_API tinkerforge_error_count final {

    /// <summary>
    /// The number of ACK checksum errors.
    /// </summary>
    std::uint32_t ack_checksum;

    /// <summary>
    /// The number of framing errors.
    /// </summary>
    std::uint32_t frame;

    /// <summary>
    /// The number of message checksum errors.
    /// </summary>
    std::uint32_t message_checksum;

    /// <summary>
    /// The number of overflow errors.
    /// </summary>
    std::uint32_t overflow;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline tinkerforge_error_count(void) noexcept : ack_checksum(0),
        frame(0), message_checksum(0), overflow(0) { }
};

PWROWG_NAMESPACE_END
