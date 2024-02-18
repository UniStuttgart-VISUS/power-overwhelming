// <copyright file="throttling_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/throttling_sensor.h"


/*
 * visus::power_overwhelming::throttling_sensor::check_not_disposed
 */
void visus::power_overwhelming::throttling_sensor::check_not_disposed(
        void) const {
    if (!*this) {
        throw std::runtime_error("A sensor which has been disposed by "
            "a move operation cannot be used anymore.");
    }
}
