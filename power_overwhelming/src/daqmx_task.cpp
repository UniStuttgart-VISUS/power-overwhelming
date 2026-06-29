// <copyright file="daqmx_task.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include "visus/pwrowg/daqmx_task.h"

#include <memory>
#include <stdexcept>

#include "daqmx_error_category.h"
#include "daqmx_library.h"


/*
 * PWROWG_NAMESPACE::daqmx_task::daqmx_task
 */
PWROWG_NAMESPACE::daqmx_task::daqmx_task(_In_z_ const char *name) {
    if (name == nullptr) {
        throw std::invalid_argument("A valid name for the task must be "
            "provided.");
    }

    detail::throw_if_daqmx_failed(detail::daqmx_library::instance()
        ._DAQmxCreateTask(name, &this->_handle));
}


/*
 * PWROWG_NAMESPACE::daqmx_task::daqmx_task
 */
PWROWG_NAMESPACE::daqmx_task::daqmx_task(_Inout_ daqmx_task&& other) noexcept
        : _handle(other._handle) {
    other._handle = nullptr;
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
 * PWROWG_NAMESPACE::daqmx_task::operator =
 */
PWROWG_NAMESPACE::daqmx_task& PWROWG_NAMESPACE::daqmx_task::operator =(
        _Inout_ daqmx_task&& rhs) noexcept {
    if (this == std::addressof(rhs)) {
        this->_handle = rhs._handle;
        rhs._handle = nullptr;
    }

    return *this;
}

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
