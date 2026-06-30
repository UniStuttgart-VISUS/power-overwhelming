// <copyright file="daqmx_sample_clock_timing.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include "visus/pwrowg/daqmx_sample_clock_timing.h"

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/string_functions.h"


/*
 * PWROWG_NAMESPACE::daqmx_sample_clock_timing::daqmx_sample_clock_timing
 */
PWROWG_NAMESPACE::daqmx_sample_clock_timing::daqmx_sample_clock_timing(
        _In_opt_z_ const char *source,
        _In_ const double rate,
        _In_ const daqmx_edge edge,
        _In_ const daqmx_sample_mode mode,
        _In_ const std::uint64_t samples)
    : daqmx_timing(mode, samples),
        _edge(edge),
        _rate(rate) {
    this->source(source);
}


/*
 * PWROWG_NAMESPACE::daqmx_sample_clock_timing::daqmx_sample_clock_timing
 */
PWROWG_NAMESPACE::daqmx_sample_clock_timing::daqmx_sample_clock_timing(
        _In_opt_z_ const wchar_t *source,
        _In_ const double rate,
        _In_ const daqmx_edge edge,
        _In_ const daqmx_sample_mode mode,
        _In_ const std::uint64_t samples)
    : daqmx_timing(mode, samples),
        _edge(edge),
        _rate(rate) {
    this->source(source);
}


/*
 * PWROWG_NAMESPACE::daqmx_sample_clock_timing::source
 */
PWROWG_NAMESPACE::daqmx_sample_clock_timing&
PWROWG_NAMESPACE::daqmx_sample_clock_timing::source(
        _In_opt_z_ const char *source) {
    if (source == nullptr) {
        this->_source.clear();
    } else {
        detail::safe_assign(this->_source, source);
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_sample_clock_timing::source
 */
PWROWG_NAMESPACE::daqmx_sample_clock_timing&
PWROWG_NAMESPACE::daqmx_sample_clock_timing::source(
        _In_opt_z_ const wchar_t *source) {
    if (source == nullptr) {
        this->_source.clear();
    } else {
        auto s = convert_string<char>(source);
        detail::safe_assign(this->_source, s);
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_sample_clock_timing::source
 */
PWROWG_NAMESPACE::daqmx_sample_clock_timing&
PWROWG_NAMESPACE::daqmx_sample_clock_timing::source(
        _In_opt_z_ const std::nullptr_t) noexcept {
    this->_source.clear();
    return *this;
}

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
