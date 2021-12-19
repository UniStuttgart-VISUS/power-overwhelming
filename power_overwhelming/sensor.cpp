// <copyright file="nvml_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "sensor.h"


/*
 * visus::power_overwhelming::sensor::check_not_disposed
 */
void visus::power_overwhelming::sensor::check_not_disposed(void) const {
    if (!*this) {
        throw std::runtime_error("A disposed sensor which has been disposed by "
            "a move operation cannot be sampled.");
    }
}
