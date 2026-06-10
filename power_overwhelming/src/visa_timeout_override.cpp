// <copyright file="visa_timeout_override.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_VISA)

#include "visus/pwrowg/trace.h"

#include "visa_error_category.h"
#include "visa_timeout_override.h"


/*
 * PWROWG_DETAIL_NAMESPACE::visa_timeout_override::visa_timeout_override
 */
PWROWG_DETAIL_NAMESPACE::visa_timeout_override::visa_timeout_override(
        _In_ ViSession session,
        _In_ const visa_instrument::timeout_type timeout)
    : _session(session),
        _timeout(0) {
    throw_if_visa_failed(visa_library::instance()._viGetAttribute(
        this->_session, VI_ATTR_TMO_VALUE, &this->_timeout));
    throw_if_visa_failed(visa_library::instance()._viSetAttribute(
        this->_session, VI_ATTR_TMO_VALUE, timeout));
    PWROWG_TRACE(_T("VISA timeout override of %u ms active."), timeout);
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_timeout_override::visa_timeout_override
 */
PWROWG_DETAIL_NAMESPACE::visa_timeout_override::visa_timeout_override(
        _In_ const bool force,
        _In_ ViSession session,
        _In_ const visa_instrument::timeout_type timeout)
    : _session(session),
        _timeout(0) {
    throw_if_visa_failed(visa_library::instance()._viGetAttribute(
        this->_session, VI_ATTR_TMO_VALUE, &this->_timeout));

    if ((timeout > 0) || force) {
        throw_if_visa_failed(visa_library::instance()._viSetAttribute(
            this->_session, VI_ATTR_TMO_VALUE, timeout));
        PWROWG_TRACE(_T("VISA timeout override of %u ms active."), timeout);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_timeout_override::~visa_timeout_override
 */
PWROWG_DETAIL_NAMESPACE::visa_timeout_override::~visa_timeout_override(
        void) noexcept {
    visa_library::instance()._viSetAttribute(
        this->_session, VI_ATTR_TMO_VALUE, this->_timeout);
    PWROWG_TRACE(_T("VISA timeout override of %u ms restored."),
        this->_timeout);
}

#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
