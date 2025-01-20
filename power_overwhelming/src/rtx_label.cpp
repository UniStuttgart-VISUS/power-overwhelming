// <copyright file="rtx_label.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_label.h"

#include <memory>

#include "visus/pwrowg/convert_string.h"

#include "string_functions.h"


/*
 * PWROWG_NAMESPACE::rtx_label::rtx_label
 */
PWROWG_NAMESPACE::rtx_label::rtx_label(_In_opt_z_ const wchar_t *text,
        _In_ const bool visible)
        : _text(nullptr), _visible(visible) {
    this->text(text);
}


/*
 * PWROWG_NAMESPACE::rtx_label::rtx_label
 */
PWROWG_NAMESPACE::rtx_label::rtx_label(_In_opt_z_ const char *text,
        _In_ const bool visible)
        : _text(nullptr), _visible(visible) {
    this->text(text);
}


/*
 * PWROWG_NAMESPACE::rtx_label::~rtx_label
 */
PWROWG_NAMESPACE::rtx_label::~rtx_label(void) {
    detail::safe_assign(this->_text, nullptr);
}


/*
 * PWROWG_NAMESPACE::rtx_label::rtx_label
 */
PWROWG_NAMESPACE::rtx_label::rtx_label(
        _In_ const rtx_label& rhs)
        : _text(nullptr), _visible(rhs._visible) {
    detail::safe_assign(this->_text, rhs._text);
}


/*
 * PWROWG_NAMESPACE::rtx_label::rtx_label
 */

PWROWG_NAMESPACE::rtx_label::rtx_label(
        _Inout_ rtx_label&& rhs) noexcept
        : _text(rhs._text), _visible(rhs._visible) {
    rhs._text = nullptr;
    rhs._visible = false;
}


/*
 * PWROWG_NAMESPACE::rtx_label::text
 */
_Ret_z_ const char *PWROWG_NAMESPACE::rtx_label::text(
        void) const noexcept {
    return (this->_text != nullptr) ? this->_text : "";
}


/*
 * PWROWG_NAMESPACE::rtx_label::text
 */
PWROWG_NAMESPACE::rtx_label& PWROWG_NAMESPACE::rtx_label::text(
        _In_opt_z_ const wchar_t *text) {
    const auto t = convert_string<char>(text);
    detail::safe_assign(this->_text, t);
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_label::text
 */
PWROWG_NAMESPACE::rtx_label& PWROWG_NAMESPACE::rtx_label::text(
        _In_opt_z_ const char *text) {
    detail::safe_assign(this->_text, text);
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_label::operator =
 */
PWROWG_NAMESPACE::rtx_label&
PWROWG_NAMESPACE::rtx_label::operator =(_In_ const rtx_label& rhs) {
    if (this != std::addressof(rhs)) {
        detail::safe_assign(this->_text, rhs._text);
        this->_visible = rhs._visible;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_label::operator =
 */
PWROWG_NAMESPACE::rtx_label&
PWROWG_NAMESPACE::rtx_label::operator =(_Inout_ rtx_label&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        detail::safe_assign(this->_text, std::move(rhs._text));
        this->_visible = rhs._visible;
        rhs._visible = true;
    }

    return *this;
}
