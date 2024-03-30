// <copyright file="visa_event_handler.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visa_event_handler.h"

#include <memory>


/*
 * visus::power_overwhelming::detail::visa_event_handler::visa_event_handler
 */
visus::power_overwhelming::detail::visa_event_handler::visa_event_handler(void)
    : _callback(nullptr), _context(nullptr), _context_deleter(nullptr) { }


/*
 * visus::power_overwhelming::detail::visa_event_handler::visa_event_handler
 */
visus::power_overwhelming::detail::visa_event_handler::visa_event_handler(
        _Inout_ visa_event_handler&& rhs) noexcept
    : _callback(rhs._callback), _context(rhs._context),
        _context_deleter(rhs._context_deleter) {
    rhs._callback = nullptr;
    rhs._context = nullptr;
    rhs._context_deleter = nullptr;
}


/*
 * visus::power_overwhelming::detail::visa_event_handler::~visa_event_handler
 */
visus::power_overwhelming::detail::visa_event_handler::~visa_event_handler(
        void) {
    this->context(nullptr, nullptr);
}


/*
 * visus::power_overwhelming::detail::visa_event_handler::callback
 */
visus::power_overwhelming::detail::visa_event_handler&
visus::power_overwhelming::detail::visa_event_handler::callback(
        _In_opt_ const callback_type callback) noexcept {
    this->_callback = callback;
    return *this;
}


/*
 * visus::power_overwhelming::detail::visa_event_handler::context
 */
visus::power_overwhelming::detail::visa_event_handler&
visus::power_overwhelming::detail::visa_event_handler::context(
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
 * visus::power_overwhelming::detail::visa_event_handler::operator =
 */
visus::power_overwhelming::detail::visa_event_handler&
visus::power_overwhelming::detail::visa_event_handler::operator =(
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
 * visus::power_overwhelming::detail::visa_event_handler::operator =
 */
visus::power_overwhelming::detail::visa_event_handler&
visus::power_overwhelming::detail::visa_event_handler::operator =(
        _In_opt_ const callback_type rhs) noexcept {
    this->_callback = rhs;
    return *this;
}


/*
 * visus::power_overwhelming::detail::visa_event_handler::operator ==
 */
bool visus::power_overwhelming::detail::visa_event_handler::operator ==(
        _In_opt_ const callback_type callback) const noexcept {
    return (this->_callback == callback);
}


/*
 * visus::power_overwhelming::detail::visa_event_handler::operator !=
 */
bool visus::power_overwhelming::detail::visa_event_handler::operator !=(
        _In_opt_ const callback_type callback) const noexcept {
    return (this->_callback != callback);
}


/*
 * visus::power_overwhelming::detail::visa_event_handler::operator ()
 */
bool visus::power_overwhelming::detail::visa_event_handler::operator ()(
        _In_ visa_instrument& instrument) const {
    auto retval = (this->_callback != nullptr);

    if (retval) {
        this->_callback(instrument, this->_context);
    }

    return retval;
}
