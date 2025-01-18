// <copyright file="oscilloscope_acquisition.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/oscilloscope_acquisition.h"


/*
 * visus::power_overwhelming::oscilloscope_acquisition::oscilloscope_acquisition
 */
visus::power_overwhelming::oscilloscope_acquisition::oscilloscope_acquisition(
        void)
    : _count(1), _points(0), _segmented(false),
        _state(oscilloscope_acquisition_state::unknown) { }
