// <copyright file="daqmx_device.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/daqmx_device.h"

#include <cassert>
#include <cctype>
#include <cstring>
#include <vector>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/multi_sz.h"
#include "visus/pwrowg/string_functions.h"

#include "daqmx_error_category.h"
#include "daqmx_library.h"


/// <summary>
/// Terminate the strings in <paramref name="list" /> and return the pointers
/// to the individual strings.
/// </summary>
static std::vector<const char *> split_daqmx_list(_Inout_ char *list) {
    std::vector<const char *> retval;

    for (auto p = list; *p != 0;) {
        // Find the end of the string, which is either the end of the input
        // string or a comma between two strings.
        auto e = p;
        while ((*e != 0) && (*e != ',')) {
            ++e;
        }
        // If this was the last string, i.e. the input ends here, we must not
        // skip spaces below.
        const auto last = (*e == 0);
        if (!last) {
            *e = 0;
        }

        // Add the output pointer.
        retval.push_back(p);

        // Skip any spaces between strings.
        for (p = last ? e : e + 1; (*p != 0) && std::isspace(*p); ++p);
    }

    return retval;
}


/*
 * PWROWG_NAMESPACE::daqmx_device::all
 */
std::size_t PWROWG_NAMESPACE::daqmx_device::all(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) daqmx_device *dst,
        _In_ std::size_t cnt) {
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    const auto l = detail::daqmx_library::instance()
        ._DAQmxGetSysDevNames(nullptr, 0);
    detail::throw_if_daqmx_failed(l);

    std::vector<char> buffer(l);
    detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
        ._DAQmxGetSysDevNames(buffer.data(), l));

    auto names = ::split_daqmx_list(buffer.data());
    if (dst != nullptr) {
        std::copy_n(names.begin(), (std::min)(names.size(), cnt), dst);
    }

    return names.size();
#else /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
    return 0;
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
}


/*
 * PWROWG_NAMESPACE::daqmx_device::daqmx_device
 */
PWROWG_NAMESPACE::daqmx_device::daqmx_device(_In_z_ const wchar_t *name) {
    auto n = convert_string<char>(name);
    detail::safe_assign(this->_name, n.c_str());
    this->populate();
}


/*
 * PWROWG_NAMESPACE::daqmx_device::daqmx_device
 */
PWROWG_NAMESPACE::daqmx_device::daqmx_device(_In_z_ const char *name) {
    detail::safe_assign(this->_name, name);
    this->populate();
}


/*
 * PWROWG_NAMESPACE::daqmx_device::analog_input_current_ranges
 */
bool PWROWG_NAMESPACE::daqmx_device::analog_input_current_ranges(
        _Out_ const double *& values, _Out_ std::size_t& cnt) const noexcept {
    const auto& ranges = this->_analog_input_current_ranges;
    const auto retval = !ranges.empty();

    if (retval) {
        values = this->_analog_inputs.as<double>();
        assert(ranges.size() % sizeof(double) == 0);
        cnt = ranges.size() / sizeof(double);
    } else {
        values = nullptr;
        cnt = 0;
    }

    return retval;
}


/*
 * PWROWG_NAMESPACE::daqmx_device::analog_input_voltage_ranges
 */
bool PWROWG_NAMESPACE::daqmx_device::analog_input_voltage_ranges(
        _Out_ const double *& values, _Out_ std::size_t& cnt) const noexcept {
    const auto& ranges = this->_analog_input_voltage_ranges;
    const auto retval = !ranges.empty();

    if (retval) {
        values = this->_analog_inputs.as<double>();
        assert(ranges.size() % sizeof(double) == 0);
        cnt = ranges.size() / sizeof(double);
    } else {
        values = nullptr;
        cnt = 0;
    }

    return retval;
}


/*
 * PWROWG_NAMESPACE::daqmx_device::populate
 */
void PWROWG_NAMESPACE::daqmx_device::populate(void) {
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    assert(this->name() != nullptr);

    {
        bool32 b;
        detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
            ._DAQmxGetDevIsSimulated(this->name(), &b));
        this->_simulated = (b != 0);
    }

    {
        const auto l = detail::daqmx_library::instance()
            ._DAQmxGetDevProductType(this->name(), nullptr, 0);
        detail::throw_if_daqmx_failed(l);
        this->_type.resize(l);
        detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
            ._DAQmxGetDevProductType(this->name(), this->_type.as<char>(), l));
    }

    {
        const auto l = detail::daqmx_library::instance()
            ._DAQmxGetDevAICurrentRngs(this->name(), nullptr, 0);
        detail::throw_if_daqmx_failed(l);
        this->_analog_input_current_ranges.resize(l * sizeof(float64));
        detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
            ._DAQmxGetDevAICurrentRngs(
                this->name(),
                this->_analog_input_current_ranges.as<float64>(),
                l));
    }

    {
        const auto l = detail::daqmx_library::instance()
            ._DAQmxGetDevAIVoltageRngs(this->name(), nullptr, 0);
        detail::throw_if_daqmx_failed(l);
        this->_analog_input_voltage_ranges.resize(l * sizeof(float64));
        detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
            ._DAQmxGetDevAIVoltageRngs(
                this->name(),
                this->_analog_input_voltage_ranges.as<float64>(),
                l));
    }

    {
        const auto l = detail::daqmx_library::instance()
            ._DAQmxGetDevAIPhysicalChans(this->name(), nullptr, 0);
        detail::throw_if_daqmx_failed(l);
        std::vector<char> channels(l);
        detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
            ._DAQmxGetDevAIPhysicalChans(this->name(), channels.data(), l));

        auto names = ::split_daqmx_list(channels.data());
        auto d = static_cast<char *>(this->_analog_inputs.resize(
            multi_sz<char>::size(names.begin(), names.end()) * sizeof(char)));
        assert(d != nullptr);

        for (auto it = names.begin(); it != names.end(); ++it) {
            while (*d++ = *(*it)++);
        }

        *d = static_cast<char>(0);
    }

    {
        const auto l = detail::daqmx_library::instance()
            ._DAQmxGetDevAOPhysicalChans(this->name(), nullptr, 0);
        detail::throw_if_daqmx_failed(l);
        std::vector<char> channels(l);
        detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
            ._DAQmxGetDevAOPhysicalChans(this->name(), channels.data(), l));

        auto names = ::split_daqmx_list(channels.data());
        auto d = static_cast<char *>(this->_analog_outputs.resize(
            multi_sz<char>::size(names.begin(), names.end()) * sizeof(char)));
        assert(d != nullptr);

        for (auto it = names.begin(); it != names.end(); ++it) {
            while (*d++ = *(*it)++);
        }

        *d = static_cast<char>(0);
    }
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
}


/*
 * PWROWG_NAMESPACE::daqmx_device::operator bool
 */
PWROWG_NAMESPACE::daqmx_device::operator bool(void) const noexcept {
    return (!this->_name.empty() && !this->_type.empty());
}
