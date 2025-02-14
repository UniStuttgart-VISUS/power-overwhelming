// <copyright file="sensor_array_context_type.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_ARRAY_CONTEXT_TYPE_H)
#define _PWROWG_SENSOR_ARRAY_CONTEXT_TYPE_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Determines what is passed as context to the
/// <see cref="sensor_array_callback" />.
/// </summary>
enum class sensor_array_context_type {

    /// <summary>
    /// A user-defined pointer
    /// </summary>
    user_defined,

    /// <summary>
    /// A pointer to the sensor array itself.
    /// </summary>
    sensor_array,

    /// <summary>
    /// A pointer to the sensor descriptions.
    /// </summary>
    sensor_descs

};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_ARRAY_CONTEXT_TYPE_H) */
