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
/// <param name="source">The zero-based index of the sensor that has created
/// the samples. The <see cref="sensor_description" /> of this sensor can be
/// used to obtain information about how to interpret the sensor readings.
/// </param>
/// <param name="samples">An array of one or more <paramref name="sample" />s.
/// </param>
/// <param name="cnt">The number of samples in the <paramref name="samples" />
/// array.</param>
/// <param anem="context">A user-defined pointer that has been registered when
/// starting the sensor array.</param>
typedef void (*sensor_array_callback)(_In_ const std::size_t source,
    _In_reads_(cnt) const sample *samples, _In_ const std::size_t cnt,
    _In_ void *context);

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_ARRAY_CALLBACK_H) */
