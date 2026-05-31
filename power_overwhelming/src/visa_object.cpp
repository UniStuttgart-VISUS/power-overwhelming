// <copyright file="visa_object.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_VISA)
#include "visus/pwrowg/visa_object.h"

#include "visus/pwrowg/trace.h"

#include "visa_library.h"


/*
 * PWROWG_NAMESPACE::visa_object::visa_object
 */
PWROWG_NAMESPACE::visa_object::visa_object(void) noexcept : _object(VI_NULL) { }


/*
 * PWROWG_NAMESPACE::visa_object::visa_object
 */
PWROWG_NAMESPACE::visa_object::visa_object(_Inout_ visa_object&& other) noexcept
        : _object(other._object) {
    other._object = VI_NULL;
}


/*
 * PWROWG_NAMESPACE::visa_object::visa_object
 */
PWROWG_NAMESPACE::visa_object::visa_object(_Inout_ ViObject&& object) noexcept
        : _object(object) {
    object = VI_NULL;
}


/*
 * PWROWG_NAMESPACE::visa_object::reset
 */
void PWROWG_NAMESPACE::visa_object::reset(void) noexcept {
    try {
        detail::visa_library::instance()._viClose(this->_object);
    } catch (...) {
        PWROWG_TRACE(_T("The VISA library used to close a VISA object was "
            "invalid. It is really impressive that this could happen, because "
            "the library should have been used before to obtain an object."));
    }
}


/*
 * PWROWG_NAMESPACE::visa_object::operator =
 */
PWROWG_NAMESPACE::visa_object& PWROWG_NAMESPACE::visa_object::operator =(
        _Inout_ visa_object&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        *this->put() = rhs._object;
        rhs._object = VI_NULL;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::visa_object::operator bool
 */
PWROWG_NAMESPACE::visa_object::operator bool(void) const noexcept {
    return (this->_object != VI_NULL);
}

#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
