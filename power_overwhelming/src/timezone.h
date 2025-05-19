// <copyright file="timezone.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TIMEZONE_H)
#define _PWROWG_TIMEZONE_H
#pragma once

#include "visus/pwrowg/timestamp.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Gets the timezone bias of the system in 100 ns units.
/// </summary>
/// <returns>The timezone bias in 100 ns units.</returns>
extern PWROWG_TEST_API timestamp::value_type get_timezone_bias(void);

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_TIMEZONE_H) */