// <copyright file="no_visa_error_msg.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_NO_VISA_ERROR_MSG_H)
#define _PWROWG_NO_VISA_ERROR_MSG_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

static constexpr const char *no_visa_error_msg = "The Power Overwhelming "
    "library was compiled without support for the Virtual Instrument Software "
    "Architecture.";

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_NO_VISA_ERROR_MSG_H) */
