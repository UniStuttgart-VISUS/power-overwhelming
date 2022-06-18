// <copyright file="conversion_time.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Possible values for averaging samples of Tinkerforge sensors.
    /// </summary>
    enum class sample_averaging : std::uint8_t {

        average_of_1 = 0,
        average_of_4 = 1,
        average_of_16 = 2,
        average_of_64 = 3,
        average_of_128 = 4,
        average_of_256 = 5,
        average_of_512 = 6,
        average_of_1024 = 7,
    };

} /* namespace power_overwhelming */
} /* namespace visus */
