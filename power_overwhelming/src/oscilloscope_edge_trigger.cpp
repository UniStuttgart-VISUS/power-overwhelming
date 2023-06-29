// <copyright file="oscilloscope_edge_trigger.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/oscilloscope_edge_trigger.h"

#include <cassert>
#include <stdexcept>
#include <string>
#include <utility>

#include "power_overwhelming/convert_string.h"

#include "string_functions.h"


/*
 * ...::power_overwhelming::oscilloscope_edge_trigger::oscilloscope_edge_trigger
 */
visus::power_overwhelming::oscilloscope_edge_trigger::oscilloscope_edge_trigger(
        _In_ const char *source)
    : oscilloscope_trigger(source),
        _coupling(oscilloscope_trigger_coupling::direct_current),
        _hysteresis(oscilloscope_trigger_hysteresis::automatic),
        _input(0),
        _slope(oscilloscope_trigger_slope::rising) { }


/*
 * visus::power_overwhelming::oscilloscope_edge_trigger::type
 */
_Ret_z_ const char *visus::power_overwhelming::oscilloscope_edge_trigger::type(
        void) const noexcept {
    return "EDGE";
}
