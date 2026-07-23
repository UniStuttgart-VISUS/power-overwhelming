// <copyright file="daqmx_sensor_trigger.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/daqmx_sensor_trigger.h"

#include <cassert>
#include <memory>

#include "visus/pwrowg/atomic_utilities.h"
#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/event.h"
#include "visus/pwrowg/trace.h"

#include "daqmx_sensor_trigger_impl.h"
#include "unique_lock.h"


/*
 * PWROWG_NAMESPACE::daqmx_sensor_trigger::daqmx_sensor_trigger
 */
PWROWG_NAMESPACE::daqmx_sensor_trigger::daqmx_sensor_trigger(void)
    : _impl(new detail::daqmx_sensor_trigger_impl()) { }


/*
 * PWROWG_NAMESPACE::daqmx_sensor_trigger::daqmx_sensor_trigger
 */
PWROWG_NAMESPACE::daqmx_sensor_trigger::daqmx_sensor_trigger(
        _In_ const daqmx_sensor_trigger& other) : _impl(other._impl) {
    assert(this->_impl != nullptr);
    if (this->_impl != nullptr) {
        ++this->_impl->references;
    }
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_trigger::daqmx_sensor_trigger
 */
PWROWG_NAMESPACE::daqmx_sensor_trigger::daqmx_sensor_trigger(
        _Inout_ daqmx_sensor_trigger&& other) noexcept : _impl(other._impl) {
    assert(this->_impl != nullptr);
    other._impl = nullptr;
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_trigger::operator =
 */
PWROWG_NAMESPACE::daqmx_sensor_trigger&
PWROWG_NAMESPACE::daqmx_sensor_trigger::operator =(
        _In_ const daqmx_sensor_trigger& rhs) {
    if (this != std::addressof(rhs)) {
        this->reset(rhs._impl);
    }

    assert(this->_impl != nullptr);
    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_trigger::operator =
 */
PWROWG_NAMESPACE::daqmx_sensor_trigger&
PWROWG_NAMESPACE::daqmx_sensor_trigger::operator =(
        _Inout_ daqmx_sensor_trigger&& rhs) noexcept {
    if ((this->_impl != rhs._impl) && this->reset(rhs._impl)) {
        rhs.reset(nullptr);
    }

    assert(this->_impl != nullptr);
    assert(rhs._impl == nullptr);
    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_trigger::default_failure
 */
void PWROWG_NAMESPACE::daqmx_sensor_trigger::default_failure(
        const std::exception_ptr, const type_erased_storage&)  noexcept {
    PWROWG_TRACE(_T("Fatal error in DAQmx sensor acquisition."));
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_trigger::acquire
 */
bool PWROWG_NAMESPACE::daqmx_sensor_trigger::acquire(
        _In_ void (*done)(const type_erased_storage&),
        _Inout_ type_erased_storage&& done_context,
        _In_ void (*failed)(const std::exception_ptr,
            const type_erased_storage&),
        _Inout_ type_erased_storage&& failed_context) {
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    using detail::sensor_trigger_state;

    assert(this->_impl != nullptr);
    if (this->_impl == nullptr) {
        return false;
    }

    if (!this->_impl->external_trigger) {
        PWROWG_TRACE(_T("Manual triggering is only supported via a parallel ")
            _T("port, which must be set at configuration time."));
        return false;
    }

    if (detail::check_all(this->_impl->state, sensor_trigger_state::armed)) {
        PWROWG_TRACE(_T("The trigger has already been armed and not fired ")
            _T("yet."));
        return false;
    }

    // Setup the end-user callbacks. The DAQmx callbacks cannot use these at
    // this point, because the trigger has not been armed yet.
    this->_impl->when_done = done;
    this->_impl->when_done_context = std::move(done_context);
    this->_impl->when_failed = failed;
    this->_impl->when_failed_context = std::move(failed_context);

    if ((detail::atomic_set(this->_impl->state, sensor_trigger_state::armed)
            & sensor_trigger_state::running) != sensor_trigger_state::running) {
        PWROWG_TRACE(_T("The DAQmx sensor was shut down while trying to arm ")
            _T("the trigger."));
        return false;
    }

    PWROWG_TRACE(_T("Triggering by raising parallel port pins %u for %u ms."),
        this->_impl->external_trigger_pins,
        this->_impl->external_trigger_duration);
    const auto b = timestamp::now();
    this->_impl->external_trigger.pulse(
        this->_impl->external_trigger_pins,
        this->_impl->external_trigger_duration);
    const auto e = timestamp::now();
    this->_impl->trigger_timestamp = timestamp::middle(b, e);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

    return true;
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_trigger::reset
 */
bool PWROWG_NAMESPACE::daqmx_sensor_trigger::reset(
        _In_opt_ detail::daqmx_sensor_trigger_impl *impl) noexcept {
    if (this->_impl != nullptr) {
        assert(this->_impl->references > 0);
        if (this->_impl->references.fetch_sub(1, std::memory_order_acq_rel)
                == 1) {
            delete this->_impl;
        }
    }

    const auto retval((this->_impl = impl) != nullptr);

    if (retval) {
        this->_impl->references.fetch_add(1, std::memory_order_acq_rel);
    }

    return retval;
}
