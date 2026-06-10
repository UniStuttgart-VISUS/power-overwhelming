// <copyright file="visa_timeout_override.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_VISA_TIMEOUT_OVERRIDE_H)
#define _PWROWG_VISA_TIMEOUT_OVERRIDE_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_VISA)

#include "visus/pwrowg/visa_instrument.h"

#include "visa_library.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// RAAI class to temporarily override the timeout of a VISA instrument.
/// </summary>
/// <remarks>
/// The class holds a &quot;shallow&quot; copy of the session handle, which
/// means that this must only be used from within VISA wrapper classes that
/// control the life time of the session.
/// </remarks>
class PWROWG_TEST_API visa_timeout_override final {

public:

    /// <summary>
    /// Sets the <paramref name="timeout" /> of the given VISA session to the
    /// given value.
    /// </summary>
    /// <param name="session"></param>
    /// <param name="timeout"></param>
    visa_timeout_override(_In_ ViSession session,
        _In_ const visa_instrument::timeout_type timeout);

    /// <summary>
    /// Sets the <paramref name="timeout" /> of the given VISA session, but only
    /// if it is non-zero or <paramref name="force" /> is set.
    /// </summary>
    /// <param name="force"></param>
    /// <param name="session"></param>
    /// <param name="timeout"></param>
    visa_timeout_override(_In_ const bool force,
        _In_ ViSession session,
        _In_ const visa_instrument::timeout_type timeout);

    visa_timeout_override(const visa_timeout_override&) = delete;

    /// <summary>
    /// Restores the initial timeout of the VISA session.
    /// </summary>
    inline ~visa_timeout_override(void) noexcept;

    visa_timeout_override& operator =(const visa_timeout_override&) = delete;

private:

    ViSession _session;
    visa_instrument::timeout_type _timeout;
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
#endif /* !defined(_PWROWG_VISA_TIMEOUT_OVERRIDE_H) */
