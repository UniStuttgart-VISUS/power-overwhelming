// <copyright file="rtx_acquisition.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_acquisition.h"


/*
 * PWROWG_NAMESPACE::rtx_acquisition::rtx_acquisition
 */
PWROWG_NAMESPACE::rtx_acquisition::rtx_acquisition(void)
    : _count(1), _points(0), _segmented(false),
        _state(rtx_acquisition_state::unknown) { }
