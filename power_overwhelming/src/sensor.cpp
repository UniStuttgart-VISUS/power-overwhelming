// <copyright file="sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/sensor.h"


/*
 * visus::power_overwhelming::sensor::sample
 */
visus::power_overwhelming::measurement
visus::power_overwhelming::sensor::sample(
        _In_ const timestamp_resolution resolution) const {
    this->check_not_disposed();
    auto name = this->name();
    _Analysis_assume_(name != nullptr);
    return measurement(name, this->sample_sync(resolution));
}


/*
 *visus::power_overwhelming::sensor::sample
 */
void visus::power_overwhelming::sensor::sample(
        _Inout_ async_sampling&& async_sampling) {
    this->check_not_disposed();
    this->sample_async(std::move(async_sampling));
}


/*
 * visus::power_overwhelming::sensor::check_not_disposed
 */
void visus::power_overwhelming::sensor::check_not_disposed(void) const {
    if (!*this) {
        throw std::runtime_error("A sensor which has been disposed by "
            "a move operation cannot be used anymore.");
    }
}
