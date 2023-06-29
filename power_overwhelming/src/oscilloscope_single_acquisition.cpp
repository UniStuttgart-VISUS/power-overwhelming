// <copyright file="oscilloscope_channel.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/oscilloscope_single_acquisition.h"


/*
 * ...::oscilloscope_single_acquisition::oscilloscope_single_acquisition
 */
visus::power_overwhelming::oscilloscope_single_acquisition::oscilloscope_single_acquisition(void)
        : _count(1), _points(0) { }
