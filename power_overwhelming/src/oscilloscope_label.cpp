// <copyright file="oscilloscope_label.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/oscilloscope_label.h"

#include <memory>

#include "visus/pwrowg/convert_string.h"

#include "string_functions.h"


/*
 * visus::power_overwhelming::oscilloscope_label::oscilloscope_label
 */
visus::power_overwhelming::oscilloscope_label::oscilloscope_label(
        _In_opt_z_ const wchar_t *text, _In_ const bool visible)
        : _text(nullptr), _visible(visible) {
    this->text(text);
}


/*
 * visus::power_overwhelming::oscilloscope_label::oscilloscope_label
 */
visus::power_overwhelming::oscilloscope_label::oscilloscope_label(
        _In_opt_z_ const char *text, _In_ const bool visible)
        : _text(nullptr), _visible(visible) {
    this->text(text);
}


/*
 * visus::power_overwhelming::oscilloscope_label::~oscilloscope_label
 */
visus::power_overwhelming::oscilloscope_label::~oscilloscope_label(void) {
    detail::safe_assign(this->_text, nullptr);
}


/*
 * visus::power_overwhelming::oscilloscope_label::oscilloscope_label
 */
visus::power_overwhelming::oscilloscope_label::oscilloscope_label(
        _In_ const oscilloscope_label& rhs)
        : _text(nullptr), _visible(rhs._visible) {
    detail::safe_assign(this->_text, rhs._text);
}


/*
 * visus::power_overwhelming::oscilloscope_label::oscilloscope_label
 */

visus::power_overwhelming::oscilloscope_label::oscilloscope_label(
        _Inout_ oscilloscope_label&& rhs) noexcept
        : _text(rhs._text), _visible(rhs._visible) {
    rhs._text = nullptr;
    rhs._visible = false;
}


/*
 * visus::power_overwhelming::oscilloscope_label::text
 */
_Ret_z_ const char *visus::power_overwhelming::oscilloscope_label::text(
        void) const noexcept {
    return (this->_text != nullptr) ? this->_text : "";
}


/*
 * visus::power_overwhelming::oscilloscope_label::text
 */
visus::power_overwhelming::oscilloscope_label&
visus::power_overwhelming::oscilloscope_label::text(
        _In_opt_z_ const wchar_t *text) {
    const auto t = convert_string<char>(text);
    detail::safe_assign(this->_text, t);
    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_label::text
 */
visus::power_overwhelming::oscilloscope_label&
visus::power_overwhelming::oscilloscope_label::text(
        _In_opt_z_ const char *text) {
    detail::safe_assign(this->_text, text);
    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_label::operator =
 */
visus::power_overwhelming::oscilloscope_label&
visus::power_overwhelming::oscilloscope_label::operator =(
        _In_ const oscilloscope_label& rhs) {
    if (this != std::addressof(rhs)) {
        detail::safe_assign(this->_text, rhs._text);
        this->_visible = rhs._visible;
    }

    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_label::operator =
 */
visus::power_overwhelming::oscilloscope_label&
visus::power_overwhelming::oscilloscope_label::operator =(
        _Inout_ oscilloscope_label&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        detail::safe_assign(this->_text, std::move(rhs._text));
        this->_visible = rhs._visible;
        rhs._visible = true;
    }

    return *this;
}
