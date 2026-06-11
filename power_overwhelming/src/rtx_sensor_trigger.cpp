// <copyright file="rtx_sensor_trigger.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_sensor_trigger.h"

#include <cassert>
#include <memory>

#include "visus/pwrowg/atomic_utilities.h"
#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/trace.h"

#include "rtx_sensor_trigger_impl.h"
#include "unique_lock.h"


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger::rtx_sensor_trigger
 */
PWROWG_NAMESPACE::rtx_sensor_trigger::rtx_sensor_trigger(void)
    : _impl(new detail::rtx_sensor_trigger_impl()) {
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger::rtx_sensor_trigger
 */
PWROWG_NAMESPACE::rtx_sensor_trigger::rtx_sensor_trigger(
    _In_ const rtx_sensor_trigger& other) : _impl(other._impl) {
    assert(this->_impl != nullptr);
    if (this->_impl != nullptr) {
        ++this->_impl->references;
    }
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger::rtx_sensor_trigger
 */
PWROWG_NAMESPACE::rtx_sensor_trigger::rtx_sensor_trigger(
    _Inout_ rtx_sensor_trigger&& other) noexcept : _impl(other._impl) {
    assert(this->_impl != nullptr);
    other._impl = nullptr;
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger::acquire
 */
bool PWROWG_NAMESPACE::rtx_sensor_trigger::acquire(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    using detail::rtx_sensor_state;
    assert(this->_impl != nullptr);

    PWROWG_TRACE(_T("Making sure that the instrument controller thread is not ")
        _T("working on the instruments anymore before triggering."));
    detail::spin_while_all(this->_impl->state, rtx_sensor_state::busy);

    if ((detail::atomic_set(this->_impl->state, rtx_sensor_state::armed)
            & rtx_sensor_state::running) != rtx_sensor_state::running) {
        PWROWG_TRACE(_T("The RTX sensor controller was shut down while trying ")
            _T("to arm the trigger."));
        return false;
    }

    for (auto& i : this->_impl->instruments) {
        PWROWG_TRACE("Arming single acquisition on \"%s\" followed by an "
            "asynchronous OPC.", i.path());
        i.acquisition(rtx_acquisition_state::single).operation_complete_async();
    }

    if (this->_impl->external_trigger) {
        PWROWG_TRACE(_T("Triggering by raising parallel port pins %u for ")
            _T("%u ms."), this->_impl->external_trigger_pins,
            this->_impl->external_trigger_duration);
        const auto b = timestamp::now();
        this->_impl->external_trigger.pulse(
            this->_impl->external_trigger_pins,
            this->_impl->external_trigger_duration);
        const auto e = timestamp::now();

        if (!this->_impl->trigger_timestamps.empty()) {
            this->_impl->trigger_timestamps.front() = timestamp::middle(b, e);
            PWROWG_TRACE(_T("Recorded external trigger timestamp: %" PRIu64),
                this->_impl->trigger_timestamps.front().value());
        }

    } else if (this->_impl->trigger != nullptr) {
        PWROWG_TRACE(_T("Performing a manual single acquisition."));
        auto& timestamps = this->_impl->trigger_timestamps;

        if (this->_impl->trigger_instrument < this->_impl->instruments.size()) {
            PWROWG_TRACE(_T("Triggering manually via daisy chain starting at ")
                _T("%zu."), this->_impl->trigger_instrument);
            assert(this->_impl->daisy_chain > 0.0f);
            auto& i = this->_impl->instruments[this->_impl->trigger_instrument];
            const auto b = timestamp::now();
            i.trigger_manually();
            const auto e = timestamp::now();

            if (!timestamps.empty()) {
                timestamps.front() = timestamp::middle(b, e);
                PWROWG_TRACE(_T("Recorded manual trigger timestamp: %" PRIu64),
                    timestamps.front().value());
            }

        } else {
            PWROWG_TRACE(_T("Triggering all instruments manually."));
            for (auto& i : this->_impl->instruments) {
                i.trigger_manually();
            }
        }
    } /* if (this->_impl->external_trigger) */
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

    return true;
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger::path
 */
_Ret_z_ const char *PWROWG_NAMESPACE::rtx_sensor_trigger::path(
        void) const noexcept {
    assert(this->_impl != nullptr);
    return (this->_impl != nullptr) ? this->_impl->path.c_str() : "";
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger::trigger
 */
_Ret_maybenull_ const PWROWG_NAMESPACE::rtx_trigger *
PWROWG_NAMESPACE::rtx_sensor_trigger::trigger(void) const noexcept {
    assert(this->_impl != nullptr);
    return (this->_impl != nullptr) ? this->_impl->trigger.get() : nullptr;
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger::operator =
 */
PWROWG_NAMESPACE::rtx_sensor_trigger&
PWROWG_NAMESPACE::rtx_sensor_trigger::operator =(
        _In_ const rtx_sensor_trigger& rhs) {
    if (this != std::addressof(rhs)) {
        this->reset(rhs._impl);
    }

    assert(this->_impl != nullptr);
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger::operator =
 */
PWROWG_NAMESPACE::rtx_sensor_trigger&
PWROWG_NAMESPACE::rtx_sensor_trigger::operator =(
        _Inout_ rtx_sensor_trigger&& rhs) noexcept {
    if ((this->_impl != rhs._impl) && this->reset(rhs._impl)) {
        rhs.reset(nullptr);
    }

    assert(this->_impl != nullptr);
    assert(rhs._impl == nullptr);
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger::reset
 */
bool PWROWG_NAMESPACE::rtx_sensor_trigger::reset(
        _In_opt_ detail::rtx_sensor_trigger_impl *impl) noexcept {
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
