// <copyright file="visa_timeout_override.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_VISA_TIMEOUT_OVERRIDE_H)
#define _PWROWG_VISA_TIMEOUT_OVERRIDE_H
#pragma once

#include "visus/pwrowg/visa_instrument.h"

#include "visa_exception.h"
#include "visa_library.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

#if defined(POWER_OVERWHELMING_WITH_VISA)
/// <summary>
/// RAAI class to temporarily override the timeout of a VISA instrument.
/// </summary>
/// <remarks>
/// The class holds a &quot;shallow&quot; copy of the session handle, which
/// means that this must only be used from within VISA wrapper classes that
/// control the life time of the session.
/// </remarks>
class visa_timeout_override final {

public:

    /// <summary>
    /// Sets the timeout of the given VISA session to the given value.
    /// </summary>
    /// <param name="session"></param>
    /// <param name="timeout"></param>
    inline visa_timeout_override(_In_ ViSession session,
            _In_ const visa_instrument::timeout_type timeout)
        : _session(session),
            _timeout(0) {
        visa_exception::throw_on_error(visa_library::instance()
            .viGetAttribute(this->_session, VI_ATTR_TMO_VALUE,
                &this->_timeout));
        visa_exception::throw_on_error(visa_library::instance()
            .viSetAttribute(this->_session, VI_ATTR_TMO_VALUE,
                timeout));
    }

    visa_timeout_override(const visa_timeout_override&) = delete;

    /// <summary>
    /// Restores the initial timeout of the VISA session.
    /// </summary>
    inline ~visa_timeout_override(void) {
        visa_library::instance().viSetAttribute(this->_session,
            VI_ATTR_TMO_VALUE, this->_timeout);
    }

    visa_timeout_override& operator =(
        const visa_timeout_override&) = delete;

private:

    ViSession _session;
    visa_instrument::timeout_type _timeout;
};
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_VISA_TIMEOUT_OVERRIDE_H) */
