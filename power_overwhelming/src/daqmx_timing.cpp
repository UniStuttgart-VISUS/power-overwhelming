// <copyright file="daqmx_timing.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/daqmx_timing.h"


/*
 * PWROWG_NAMESPACE::daqmx_timing::daqmx_timing
 */
PWROWG_NAMESPACE::daqmx_timing::daqmx_timing(
        _In_ const daqmx_sample_mode mode,
        _In_ const std::uint64_t samples)
    : _mode(mode), _samples(samples) { }
