// <copyright file="sensor_array.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_ARRAY_H)
#define _PWROWG_SENSOR_ARRAY_H
#pragma once

#include "visus/pwrowg/sensor_description.h"


/* Forward declarations*/
PWROWG_DETAIL_NAMESPACE_BEGIN
struct sensor_array_impl;
PWROWG_DETAIL_NAMESPACE_END

PWROWG_NAMESPACE_BEGIN

/// <summary>
/// The sensor array is the main structure of Power Overwhelming v2 as is
/// manages a set of sensors that are sampled simultaneously. Sensors can only
/// be created as membery of a sensor array.
/// </summary>
class sensor_array final {

public:

    /// <summary>
    /// Defines the interface of a filter that can be applied when creating a
    /// sensor array to select the sensors included in the array based on their
    /// description.
    /// </summary>
    typedef bool (*filter_func)(_In_ const sensor_description&, void *);


private:

    PWROWG_DETAIL_NAMESPACE::sensor_array_impl *_impl;

};

PWROWG_NAMESPACE_END

#endif  /* !defined(_PWROWG_SENSOR_ARRAY_H) */
