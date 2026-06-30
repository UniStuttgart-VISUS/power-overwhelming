// <copyright file="daqmx_implicit_timing.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/daqmx_implicit_timing.h"


/*
 * PWROWG_NAMESPACE::daqmx_implicit_timing::daqmx_implicit_timing
 */
PWROWG_NAMESPACE::daqmx_implicit_timing::daqmx_implicit_timing(
        _In_ const daqmx_sample_mode mode,
        _In_ const std::uint64_t samples)
    : daqmx_timing(mode, samples) { }
