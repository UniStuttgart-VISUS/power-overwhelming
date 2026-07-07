// <copyright file="daqmx_sample_handler.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include "visus/pwrowg/daqmx_sample_handler.h"

#include "visus/pwrowg/daqmx_task.h"

#include "daqmx_error_category.h"
#include "daqmx_library.h"


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sample_handler::daqmx_sample_handler
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sample_handler::daqmx_sample_handler(
        _In_ daqmx_task& task,
        _In_ const daqmx_sample_event_type type,
        _In_ const destructor_type dtor) noexcept
    : _dtor(dtor), _task(task), _type(type) { }


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sample_handler::~daqmx_sample_handler
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sample_handler::~daqmx_sample_handler(
        void) noexcept {
    const auto t = static_cast<int32>(this->_type);
    daqmx_library::instance()._DAQmxRegisterEveryNSamplesEvent(
        this->_task, t, 0, 0, nullptr, nullptr);
    assert(this->_dtor != nullptr);
    this->_dtor(this + 1);
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sample_handler::install
 */
void PWROWG_DETAIL_NAMESPACE::daqmx_sample_handler::install(
        _In_ const uInt32 samples,
        _In_ const callback_type callback) {
    const auto t = static_cast<int32>(this->_type);
    throw_if_daqmx_failed(daqmx_library::instance()
        ._DAQmxRegisterEveryNSamplesEvent(
            this->_task, t, samples, 0, callback, this));
}

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
