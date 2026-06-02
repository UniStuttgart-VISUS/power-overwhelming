// <copyright file="rtx_sensor_trigger.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_sensor_trigger.h"

#include <cassert>
#include <memory>

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
void PWROWG_NAMESPACE::rtx_sensor_trigger::acquire(void) {
    assert(this->_impl != nullptr);

    while (check_state(this->_impl->state, detail::rtx_sensor_state::busy));

    for (auto& i : this->_impl->instruments) {
        PWROWG_TRACE("Arming single acquisition on \"%s\".", i.path());
        i.acquisition(this->_impl->acquisition);
    }

    if (this->_impl->external_trigger) {
        PWROWG_TRACE(_T("Triggering by raising parallel port pins %u for ")
            _T("%u ms."), this->_impl->external_trigger_pins,
            this->_impl->external_trigger_duration);
        this->_impl->external_trigger.pulse(
            this->_impl->external_trigger_pins,
            this->_impl->external_trigger_duration);

    } else if (this->_impl->trigger != nullptr) {
        PWROWG_TRACE(_T("Performing a manual single acquisition."));

        if (this->_impl->trigger_instrument < this->_impl->instruments.size()) {
            PWROWG_TRACE(_T("Triggering manually via daisy chain starting at ")
                _T("%zu."), this->_impl->trigger_instrument);
            assert(this->_impl->daisy_chain > 0.0f);
            auto& i = this->_impl->instruments[this->_impl->trigger_instrument];
            i.trigger_manually();

        } else {
            PWROWG_TRACE(_T("Triggering all instruments manually."));
            for (auto& i : this->_impl->instruments) {
                i.trigger_manually();
            }
        }
    } /* if (this->_impl->external_trigger) */
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
