// <copyright file="daqmx_analog_edge_trigger.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_ANALOG_EDGE_TRIGGER_H)
#define _PWROWG_DAQMX_ANALOG_EDGE_TRIGGER_H
#pragma once

#include "visus/pwrowg/daqmx_edge.h"
#include "visus/pwrowg/blob.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// If configured as the trigger of a <see cref="daqmx_task" />, the task will
/// start sampling once the specified level of the signal on the specified
/// source channel is crossed.
/// </summary>
class POWER_OVERWHELMING_API daqmx_analog_edge_trigger final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="source">The name of a channel or terminal where there is
    /// an analog signal to use as the source of the trigger. </param>
    /// <param name="edge">Specifies on which slope of the signal to start
    /// acquiring or generating samples when the signal crosses trigger
    /// <paramref name="level" />.</param>
    /// <param name="level">The threshold at which to start acquiring or
    /// generating samples.</param>
    daqmx_analog_edge_trigger(_In_z_ const char *source, _In_ daqmx_edge edge,
        _In_ double level);

    /// <summary>
    /// Gets on which slope of the signal to start acquiring or generating
    /// samples when the signal crosses the specified level.
    /// </summary>
    /// <returns>The edge on which to trigger.</returns>
    inline daqmx_edge edge(void) const {
        return this->_edge;
    }

    /// <summary>
    /// Gets the threshold at which to start acquiring or generating samples.
    /// </summary>
    /// <returns>The trigger level.</returns>
    inline double level(void) const {
        return this->_level;
    }

    /// <summary>
    /// Gets the name of the channel or terminal where the trigger signal is
    /// expected to be connected.
    /// </summary>
    /// <returns>The name of the channel to trigger on.</returns>
    inline const char *source(void) const {
        return this->_source.as<char>();
    }

private:

    daqmx_edge _edge;
    double _level;
    blob _source;
};

PWROWG_NAMESPACE_END

#endif /*!defined(_PWROWG_DAQMX_ANALOG_EDGE_TRIGGER_H) */
