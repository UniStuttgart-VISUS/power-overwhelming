// <copyright file="daqmx_task.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include "visus/pwrowg/daqmx_task.h"

#include <limits>
#include <memory>
#include <stdexcept>

#include "visus/pwrowg/trace.h"

#include "daqmx_error_category.h"
#include "daqmx_library.h"


/*
 * PWROWG_NAMESPACE::daqmx_task::daqmx_task
 */
PWROWG_NAMESPACE::daqmx_task::daqmx_task(_In_z_ const char *name)
        : _on_done(nullptr), _on_sample(nullptr) {
    if (name == nullptr) {
        throw std::invalid_argument("A valid name for the task must be "
            "provided.");
    }

    detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
        ._DAQmxCreateTask(name, &this->_handle));
}


/*
 * PWROWG_NAMESPACE::daqmx_task::~daqmx_task
 */
PWROWG_NAMESPACE::daqmx_task::~daqmx_task(void) noexcept {
    this->clear();
}


/*
 * PWROWG_NAMESPACE::daqmx_task::clear
 */
void PWROWG_NAMESPACE::daqmx_task::clear(void) noexcept {
    delete this->_on_done;
    this->_on_done = nullptr;
    delete this->_on_sample;
    this->_on_sample = nullptr;
    detail::daqmx_library::instance()._DAQmxClearTask(this->_handle);
    this->_handle = nullptr;
}


/*
 * PWROWG_NAMESPACE::daqmx_task::done
 */
bool PWROWG_NAMESPACE::daqmx_task::done(void) const {
    bool32 done = 0;
    detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
        ._DAQmxIsTaskDone(this->_handle, &done));
    return (done != 0);
}


/*
 * PWROWG_NAMESPACE::daqmx_task::input_buffer
 */
PWROWG_NAMESPACE::daqmx_task& PWROWG_NAMESPACE::daqmx_task::input_buffer(
        _In_ const std::size_t size) {
    const auto s = (size > (std::numeric_limits<uInt32>::max)())
        ? (std::numeric_limits<uInt32>::max)()
        : static_cast<uInt32>(size);
    detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
        ._DAQmxCfgInputBuffer(this->_handle, s));
    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_task::output_buffer
 */
PWROWG_NAMESPACE::daqmx_task& PWROWG_NAMESPACE::daqmx_task::output_buffer(
        _In_ const std::size_t size) {
    const auto s = (size > (std::numeric_limits<uInt32>::max)())
        ? (std::numeric_limits<uInt32>::max)()
        : static_cast<uInt32>(size);
    detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
        ._DAQmxCfgOutputBuffer(this->_handle, s));
    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_task::read
 */
std::size_t PWROWG_NAMESPACE::daqmx_task::read(
        _Out_writes_(cnt * samples) double *dst,
        _In_ const std::size_t cnt,
        _In_ const int32 samples,
        _In_ const bool interleaved,
        _In_ const double timeout) {
    const auto avail = (cnt > (std::numeric_limits<uInt32>::max)())
        ? (std::numeric_limits<uInt32>::max)()
        : static_cast<uInt32>(cnt);
    const auto fill = interleaved
        ? DAQmx_Val_GroupByChannel
        : DAQmx_Val_GroupByScanNumber;

    int32 read = 0;
    const auto status = detail::daqmx_library::instance()
        ._DAQmxReadAnalogF64(
            this->_handle,
            static_cast<int32>(samples),
            timeout,
            fill,
            dst,
            avail,
            &read,
            nullptr);

    switch (status) {
        case DAQmxErrorTimeoutExceeded:
            return 0;

        default:
            detail::throw_if_daqmx_failed(status);
            break;
    }

    return static_cast<std::size_t>(read);
}


/*
 * PWROWG_NAMESPACE::daqmx_task::start
 */
void PWROWG_NAMESPACE::daqmx_task::start(void) {
    detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
        ._DAQmxStartTask(this->_handle));
}


/*
 * PWROWG_NAMESPACE::daqmx_task::stop
 */
void PWROWG_NAMESPACE::daqmx_task::stop(void) {
    detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
        ._DAQmxStopTask(this->_handle));
}


/*
 * PWROWG_NAMESPACE::daqmx_task::timing
 */
PWROWG_NAMESPACE::daqmx_task& PWROWG_NAMESPACE::daqmx_task::timing(
        _In_ const daqmx_implicit_timing& timing) {
    detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
        ._DAQmxCfgImplicitTiming(
            this->_handle,
            static_cast<int32>(timing.mode()),
            timing.samples()));
    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_task::timing
 */
PWROWG_NAMESPACE::daqmx_task& PWROWG_NAMESPACE::daqmx_task::timing(
        _In_ const daqmx_sample_clock_timing& timing) {
    detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
        ._DAQmxCfgSampClkTiming(
            this->_handle,
            timing.source(),
            timing.rate(),
            static_cast<int32>(timing.edge()),
            static_cast<int32>(timing.mode()),
            timing.samples()));
    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_task::wait
 */
bool PWROWG_NAMESPACE::daqmx_task::wait(_In_ const double timeout) const {
    const auto status = detail::daqmx_library::instance()
        ._DAQmxWaitUntilTaskDone(this->_handle, timeout);
    if (status == DAQmxErrorTimeoutExceeded) {
        return false;
    }

    detail::throw_if_daqmx_failed(status);

    return true;
}


/*
 * PWROWG_NAMESPACE::daqmx_task::operator +=
 */
PWROWG_NAMESPACE::daqmx_task& PWROWG_NAMESPACE::daqmx_task::operator +=(
        _In_ const daqmx_current_channel& rhs) {
    PWROWG_TRACE("Adding current channel \"%s\" as \"%s\" with terminal "
        "configuration %d, range [%g, %g], shunt resistor %d, shunt value %g.",
        rhs.channel(), rhs.name(), rhs.terminal_configuration(),
        rhs.min_value(), rhs.max_value(), rhs.shunt_resistor_location(),
        rhs.shunt_resistor_value());
    detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
        ._DAQmxCreateAICurrentChan(
            this->_handle,
            rhs.channel(),
            rhs.name(),
            static_cast<int32>(rhs.terminal_configuration()),
            rhs.min_value(),
            rhs.max_value(),
            DAQmx_Val_Amps,
            static_cast<int32>(rhs.shunt_resistor_location()),
            rhs.shunt_resistor_value(),
            nullptr));
    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_task::operator +=
 */
PWROWG_NAMESPACE::daqmx_task& PWROWG_NAMESPACE::daqmx_task::operator +=(
        _In_ const daqmx_power_channel& rhs) {
    PWROWG_TRACE("Adding power channel \"%s\" (voltage), \"%s\" (current) as "
        "\"%s\" with terminal configuration %d, range [%g, %g] (voltage), "
        "[%g, %g] (current), shunt resistor %d, shunt value %g.",
        rhs.voltage_channel(), rhs.current_channel(), rhs.name(),
        rhs.terminal_configuration(), rhs.voltage_min_value(),
        rhs.voltage_max_value(), rhs.current_min_value(),
        rhs.current_max_value(), rhs.shunt_resistor_location(),
        rhs.shunt_resistor_value());
    detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
        ._DAQmxCreateAICalculatedPowerChan(
            this->_handle,
            rhs.voltage_channel(),
            rhs.current_channel(),
            rhs.name(),
            static_cast<int32>(rhs.terminal_configuration()),
            rhs.voltage_min_value(),
            rhs.voltage_max_value(),
            rhs.current_min_value(),
            rhs.current_max_value(),
            DAQmx_Val_Watts,
            static_cast<int32>(rhs.shunt_resistor_location()),
            rhs.shunt_resistor_value(),
            nullptr));
    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_task::operator +=
 */
PWROWG_NAMESPACE::daqmx_task& PWROWG_NAMESPACE::daqmx_task::operator +=(
        _In_ const daqmx_voltage_channel& rhs) {
    PWROWG_TRACE("Adding voltage channel \"%s\" as \"%s\" with terminal "
        "configuration %d, range [%g, %g].",
        rhs.channel(), rhs.name(), rhs.terminal_configuration(),
        rhs.min_value(), rhs.max_value());
    detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
        ._DAQmxCreateAIVoltageChan(
            this->_handle,
            rhs.channel(),
            rhs.name(),
            static_cast<int32>(rhs.terminal_configuration()),
            rhs.min_value(),
            rhs.max_value(),
            DAQmx_Val_Volts,
            nullptr));
    return *this;
}

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
