// <copyright file="daqmx_sample_clock_timing.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_SAMPLE_CLOCK_TIMING_H)
#define _PWROWG_DAQMX_SAMPLE_CLOCK_TIMING_H
#pragma once

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/daqmx_edge.h"
#include "visus/pwrowg/daqmx_timing.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Configures the timing of data acquisition of a NI-DAQmx device.
/// </summary>
class POWER_OVERWHELMING_API daqmx_sample_clock_timing final
        : public daqmx_timing {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="source">The name of the terminal where the sample clock is
    /// connected.</param>
    /// <param name="rate">The sampling rate samples per second per
    /// channel.</param>
    /// <param name="edge">The trigger edge.</param>
    /// <param name="mode">The sample mode.</param>
    /// <param name="samples">The number of samples.</param>
    daqmx_sample_clock_timing(
        _In_opt_z_ const char *source,
        _In_ const double rate,
        _In_ const daqmx_edge edge = daqmx_edge::rising,
        _In_ const daqmx_sample_mode mode = daqmx_sample_mode::finite,
        _In_ const std::uint64_t samples = 1024);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="source">The name of the terminal where the sample clock is
    /// connected.</param>
    /// <param name="rate">The sampling rate samples per second per
    /// channel.</param>
    /// <param name="edge">The trigger edge.</param>
    /// <param name="mode">The sample mode.</param>
    /// <param name="samples">The number of samples.</param>
    daqmx_sample_clock_timing(
        _In_opt_z_ const wchar_t *source,
        _In_ const double rate,
        _In_ const daqmx_edge edge = daqmx_edge::rising,
        _In_ const daqmx_sample_mode mode = daqmx_sample_mode::finite,
        _In_ const std::uint64_t samples = 1024);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <remarks>
    /// This constructor configures the timing to use the internal clock of the
    /// device.
    /// </remarks>
    /// <param name="source">The name of the terminal where the sample clock is
    /// connected.</param>
    /// <param name="rate">The sampling rate samples per second per
    /// channel.</param>
    /// <param name="edge">The trigger edge.</param>
    /// <param name="mode">The sample mode.</param>
    /// <param name="samples">The number of samples.</param>
    inline explicit daqmx_sample_clock_timing(
            _In_ const double rate,
            _In_ const daqmx_edge edge = daqmx_edge::rising,
            _In_ const daqmx_sample_mode mode = daqmx_sample_mode::finite,
            _In_ const std::uint64_t samples = 1024)
        : daqmx_timing(mode, samples), _edge(edge), _rate(rate) { }

    /// <summary>
    /// Indicates on which side of the sample clock the samples are acquired or
    /// generated.
    /// </summary>
    /// <returns>The trigger edge.</returns>
    inline daqmx_edge edge(void) const noexcept {
        return this->_edge;
    }

    /// <summary>
    /// Configures on which side of the sample clock the samples are acquired or
    /// generated.
    /// </summary>
    /// <param name="edge">The trigger edge.</param>
    /// <returns><c>*<see langword="this "/></c>.</returns>
    inline daqmx_sample_clock_timing& edge(
            _In_ const daqmx_edge edge) noexcept {
        this->_edge = edge;
        return *this;
    }

    using daqmx_timing::mode;

    /// <summary>
    /// Sets a new sample mode.
    /// </summary>
    /// <param name="mode">The new sample mode.</param>
    /// <returns><c>*<see langword="this "/></c>.</returns>
    inline daqmx_sample_clock_timing& mode(
            _In_ const daqmx_sample_mode mode) noexcept {
        daqmx_timing::mode(mode);
        return *this;
    }

    /// <summary>
    /// Gets the sampling rate in samples per second per channel.
    /// </summary>
    /// <returns>The sampling rate samples per second per channel.</returns>
    inline double rate(void) const noexcept {
        return this->_rate;
    }

    /// <summary>
    /// Sets the sampling rate.
    /// </summary>
    /// <remarks>
    /// If you use an external source for the sample clock, set this value to
    /// the maximum expected rate of that clock.
    /// </remarks>
    /// <param name="rate">The sampling rate samples per second per
    /// channel.</param>
    /// <returns><c>*<see langword="this "/></c>.</returns>
    inline daqmx_sample_clock_timing& rate(_In_ const double rate) noexcept {
        this->_rate = rate;
        return *this;
    }

    using daqmx_timing::samples;

    /// <summary>
    /// Sets the number of sample to acquire or generate per channel.
    /// </summary>
    /// <param name="samples">The number of samples to acquire or generate per
    /// channel.</param>
    /// <returns><c>*<see langword="this "/></c>.</returns>
    inline daqmx_sample_clock_timing& samples(
            _In_ const std::uint64_t samples) noexcept {
        daqmx_timing::samples(samples);
        return *this;
    }

    /// <summary>
    /// Gets the terminal where the sample clock is connected.
    /// </summary>
    /// <returns>The name of the terminal where the sample clock is connected,
    /// or <see langword="nullptr" /> when the internal clock is used.</returns>
    inline _Ret_maybenull_z_ const char *source(void) const noexcept {
        return this->_source.as<char>();
    }

    /// <summary>
    /// Sets the terminal where the sample clock is connected.
    /// </summary>
    /// <param name="source">The name of the terminal where the sample clock is
    /// connected. Use <see langword="nullptr" /> for the internal clock
    /// of the device.</param>
    /// <returns><c>*<see langword="this "/></c>.</returns>
    daqmx_sample_clock_timing& source(_In_opt_z_ const char *source);

    /// <summary>
    /// Sets the terminal where the sample clock is connected.
    /// </summary>
    /// <param name="source">The name of the terminal where the sample clock is
    /// connected. Use <see langword="nullptr" /> for the internal clock
    /// of the device.</param>
    /// <returns><c>*<see langword="this "/></c>.</returns>
    daqmx_sample_clock_timing& source(_In_opt_z_ const wchar_t *source);

    /// <summary>
    /// Sets the internal clock of the device as timing source.
    /// </summary>
    /// <returns><c>*<see langword="this "/></c>.</returns>
    daqmx_sample_clock_timing& source(_In_opt_z_ const std::nullptr_t) noexcept;

private:

    daqmx_edge _edge;
    double _rate;
    blob _source;
};

PWROWG_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
#endif /* !defined(_PWROWG_DAQMX_SAMPLE_CLOCK_TIMING_H) */
