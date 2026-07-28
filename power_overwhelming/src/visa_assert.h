// <copyright file="visa_assert.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_VISA_ASSERT_H)
#define _PWROWG_VISA_ASSERT_H
#pragma once

#include <cassert>

#include "visus/pwrowg/visa_instrument.h"


#if defined(PWROWG_ASSERT_VISA_INSTRUMENT_STATE)
/// <summary>
/// Asserts that the given instrument has no VISA error.
/// </summary>
/// <param name="instrument">The instrument to check.</param>
#define PWROWG_ASSERT_NO_VISA_ERROR(instrument)\
    assert((instrument).system_error() == 0)
#else /* !defined(PWROWG_ASSERT_VISA_INSTRUMENT_STATE) */
#define PWROWG_ASSERT_NO_VISA_ERROR(instrument) ((void) 0)
#endif /* defined(PWROWG_ASSERT_VISA_INSTRUMENT_STATE) */

#endif /* !defined(_PWROWG_VISA_ASSERT_H) */
