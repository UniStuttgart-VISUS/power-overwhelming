// <copyright file="sensor_array_callback.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_ARRAY_CALLBACK_H)
#define _PWROWG_SENSOR_ARRAY_CALLBACK_H
#pragma once

#include <cstdlib>

#include "visus/pwrowg/sample.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// The type of callback that is invoked by the <see cref="sensor_array" /> for
/// all samples.
/// </summary>
/// <remarks>
/// <para>Implementations must make sure that the callback is reentrant
/// (multiple sensors may call it at the same time). Furthermore,
/// implementations must assume that they are a called in an arbitraty thread
/// context. No assumption must be made about specific sensors being delivered
/// by specific threads.</para>
/// <para>Implementations must not perform excessive work. The callback may be
/// running in context of a sensor-specific thread. Excessive work in the
/// callback may, therefore, negatively impact the sampling rate and can cause
/// samples to be dropped. Processing data and receiving samples should be
/// decoupled to avoid this.</para>
/// </remarks>
/// <param name="samples">An array of one or more <paramref name="sample" />s.
/// </param>
/// <param name="cnt">The number of samples in the <paramref name="samples" />
/// array.</param>
/// <param anem="context">A user-defined pointer that has been registered when
/// starting the sensor array.</param>
typedef void (*sensor_array_callback)(_In_reads_(cnt) const sample *samples,
    _In_ const std::size_t cnt, _In_opt_ void *context);

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_ARRAY_CALLBACK_H) */
