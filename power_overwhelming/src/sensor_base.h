// <copyright file="sensor_base.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_BASE_H)
#define _PWROWG_SENSOR_BASE_H
#pragma once

#include <atomic>
#include <cstdlib>
#include <functional>

#include "sensor_state.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// The base class of all sensors, which defines the interface used by the
/// <see cref="sensor_array" />.
/// </summary>
class sensor_base {

public:

    virtual void sample(_In_ const std::function<void()> callback) = 0;

    virtual bool start(void) = 0;

    virtual void stop(void) = 0;

private:

    std::size_t _index;
    std::atomic<sensor_state> _state;
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_BASE_H) */
