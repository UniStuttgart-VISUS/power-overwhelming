// <copyright file="daqmx_task.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/daqmx_task.h"

#include <memory>


/*
 * PWROWG_NAMESPACE::daqmx_task::daqmx_task
 */
PWROWG_NAMESPACE::daqmx_task::daqmx_task(_In_z_ const char *name) {
    //DAQmxCreateTask(const char taskName[], TaskHandle *taskHandle)
}


/*
 * PWROWG_NAMESPACE::daqmx_task::daqmx_task
 */
PWROWG_NAMESPACE::daqmx_task::daqmx_task(_Inout_ daqmx_task&& other) noexcept {

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
    // DAQmxClearTask(TaskHandle taskHandle)
}


/*
 * PWROWG_NAMESPACE::daqmx_task::start
 */
void PWROWG_NAMESPACE::daqmx_task::start(void) {
    // DAQmxStartTask(TaskHandle taskHandle)
}


/*
 * PWROWG_NAMESPACE::daqmx_task::stop
 */
void PWROWG_NAMESPACE::daqmx_task::stop(void) {

}


/*
 * PWROWG_NAMESPACE::daqmx_task::wait
 */
bool PWROWG_NAMESPACE::daqmx_task::wait(_In_ const double timeout) const {
    return false;
}


/*
 * PWROWG_NAMESPACE::daqmx_task::operator =
 */
PWROWG_NAMESPACE::daqmx_task& PWROWG_NAMESPACE::daqmx_task::operator =(
        _Inout_ daqmx_task&& rhs) noexcept {
    if (this == std::addressof(rhs)) {
    }

    return *this;
}
