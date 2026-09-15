// <copyright file="daqmx_done_handler.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include "visus/pwrowg/daqmx_done_handler.h"

#include "visus/pwrowg/daqmx_task.h"

#include "daqmx_error_category.h"
#include "daqmx_library.h"


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_done_handler::daqmx_done_handler
 */
PWROWG_DETAIL_NAMESPACE::daqmx_done_handler::daqmx_done_handler(
        _In_ daqmx_task& task,
        _In_ const destructor_type dtor) noexcept
    : _dtor(dtor), _task(task) { }


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_done_handler::~daqmx_done_handler
 */
PWROWG_DETAIL_NAMESPACE::daqmx_done_handler::~daqmx_done_handler(
        void) noexcept {
    daqmx_library::instance()._DAQmxRegisterDoneEvent(
        this->_task, 0, nullptr, nullptr);
    assert(this->_dtor != nullptr);
    this->_dtor(this + 1);
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_done_handler::install
 */
void PWROWG_DETAIL_NAMESPACE::daqmx_done_handler::install(
        _In_ const callback_type callback) {
    throw_if_daqmx_failed(daqmx_library::instance()._DAQmxRegisterDoneEvent(
        this->_task, 0, callback, this));
}

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
