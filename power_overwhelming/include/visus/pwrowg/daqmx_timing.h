// <copyright file="daqmx_timing.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_TIMING_H)
#define _PWROWG_DAQMX_TIMING_H
#pragma once

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include "visus/pwrowg/daqmx_sample_mode.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// The base class for timing configurations of NI-DAQmx tasks.
/// </summary>
class POWER_OVERWHELMING_API daqmx_timing {

public:

    /// <summary>
    /// Answer the sample mode.
    /// </summary>
    /// <returns>The sample mode.</returns>
    inline daqmx_sample_mode mode(void) const noexcept {
        return this->_mode;
    }

    /// <summary>
    /// Answer the number of samples to acquire or generate per channel.
    /// </summary>
    /// <returns>The number of samples per channel.</returns>
    inline std::uint64_t samples(void) const noexcept {
        return this->_samples;
    }

protected:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="mode"></param>
    /// <param name="samples"></param>
    explicit daqmx_timing(
        _In_ const daqmx_sample_mode mode = daqmx_sample_mode::finite,
        _In_ const std::uint64_t samples = 1024);

    /// <summary>
    /// Sets a new sample mode.
    /// </summary>
    /// <param name="mode">The new sample mode.</param>
    inline void mode(_In_ const daqmx_sample_mode mode) noexcept {
        this->_mode = mode;
    }

    /// <summary>
    /// Sets the number of sample to acquire or generate per channel.
    /// </summary>
    /// <param name="samples">The number of samples to acquire or generate per
    /// channel.</param>
    inline void samples(_In_ const std::uint64_t samples) noexcept {
        this->_samples = samples;
    }

private:

    daqmx_sample_mode _mode;
    std::uint64_t _samples;
};

PWROWG_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
#endif /* !defined(_PWROWG_DAQMX_TIMING_H) */
