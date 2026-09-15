// <copyright file="daqmx_analog_edge_trigger.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/daqmx_analog_edge_trigger.h"

#include "visus/pwrowg/string_functions.h"


/*
 * PWROWG_NAMESPACE::daqmx_analog_edge_trigger::daqmx_analog_edge_trigger
 */
PWROWG_NAMESPACE::daqmx_analog_edge_trigger::daqmx_analog_edge_trigger(
        _In_z_ const char *source,
        _In_ daqmx_edge edge,
        _In_ double level)
    : _edge(edge),
        _level(level) {
    detail::safe_assign(this->_source, source);
}
