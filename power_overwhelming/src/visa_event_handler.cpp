// <copyright file="visa_event_handler.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_VISA)
#include "visus/pwrowg/visa_event_handler.h"

#include "visus/pwrowg/visa_instrument.h"

#include "visa_error_category.h"
#include "visa_instrument_impl.h"


/*
 * PWROWG_DETAIL_NAMESPACE::visa_event_handler::visa_event_handler
 */
PWROWG_DETAIL_NAMESPACE::visa_event_handler::visa_event_handler(
        _In_ visa_instrument& instrument,
        _In_ const ViEventType type,
        _In_ const ViHndlr handler,
        _In_ const destructor_type dtor) noexcept
    : _dtor(dtor),
        _handler(handler),
        _instrument(instrument),
        _type(type) {
    assert(this->_dtor != nullptr);
    assert(this->_handler != nullptr);
    assert(this->_instrument);
}

#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */


#if 0
/*
 * PWROWG_DETAIL_NAMESPACE::visa_event_handler::visa_event_handler
 */
PWROWG_DETAIL_NAMESPACE::visa_event_handler::visa_event_handler(void)
    : _callback(nullptr), _context(nullptr), _context_deleter(nullptr) { }


/*
 * PWROWG_DETAIL_NAMESPACE::visa_event_handler::visa_event_handler
 */
PWROWG_DETAIL_NAMESPACE::visa_event_handler::visa_event_handler(
        _Inout_ visa_event_handler&& rhs) noexcept
    : _callback(rhs._callback), _context(rhs._context),
        _context_deleter(rhs._context_deleter) {
    rhs._callback = nullptr;
    rhs._context = nullptr;
    rhs._context_deleter = nullptr;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_event_handler::~visa_event_handler
 */
PWROWG_DETAIL_NAMESPACE::visa_event_handler::~visa_event_handler(
        void) {
    this->context(nullptr, nullptr);
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_event_handler::callback
 */
PWROWG_DETAIL_NAMESPACE::visa_event_handler&
PWROWG_DETAIL_NAMESPACE::visa_event_handler::callback(
        _In_opt_ const callback_type callback) noexcept {
    this->_callback = callback;
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_event_handler::context
 */
PWROWG_DETAIL_NAMESPACE::visa_event_handler&
PWROWG_DETAIL_NAMESPACE::visa_event_handler::context(
        _In_opt_ void *context,
        _In_opt_ const context_deleter_type context_deleter) {
    if ((this->_context != nullptr) && (this->_context_deleter != nullptr)) {
        // Delete any previously owned context.
        this->_context_deleter(this->_context);
    }

    this->_context = context;
    this->_context_deleter = context_deleter;

    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_event_handler::operator =
 */
PWROWG_DETAIL_NAMESPACE::visa_event_handler&
PWROWG_DETAIL_NAMESPACE::visa_event_handler::operator =(
        _Inout_ visa_event_handler&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_callback = rhs._callback;
        rhs._callback = nullptr;
        this->_context = rhs._context;
        rhs._context = nullptr;
        this->_context_deleter = rhs._context_deleter;
        rhs._context_deleter = nullptr;
    }

    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_event_handler::operator =
 */
PWROWG_DETAIL_NAMESPACE::visa_event_handler&
PWROWG_DETAIL_NAMESPACE::visa_event_handler::operator =(
        _In_opt_ const callback_type rhs) noexcept {
    this->_callback = rhs;
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_event_handler::operator ==
 */
bool PWROWG_DETAIL_NAMESPACE::visa_event_handler::operator ==(
        _In_opt_ const callback_type callback) const noexcept {
    return (this->_callback == callback);
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_event_handler::operator !=
 */
bool PWROWG_DETAIL_NAMESPACE::visa_event_handler::operator !=(
        _In_opt_ const callback_type callback) const noexcept {
    return (this->_callback != callback);
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_event_handler::operator ()
 */
bool PWROWG_DETAIL_NAMESPACE::visa_event_handler::operator ()(
        _In_ visa_instrument& instrument) const {
    auto retval = (this->_callback != nullptr);

    if (retval) {
        this->_callback(instrument, this->_context);
    }

    return retval;
}
#endif
