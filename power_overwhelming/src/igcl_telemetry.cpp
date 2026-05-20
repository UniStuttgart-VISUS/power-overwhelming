// <copyright file="igcl_telemetry.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_IGCL)
#include "igcl_telemetry.h"

#include <cassert>
#include <limits>


/*
 * PWROWG_DETAIL_NAMESPACE::find_igcl_telemetry_disp
 */
std::size_t PWROWG_DETAIL_NAMESPACE::find_igcl_telemetry_disp(
        _In_ const decltype(make_igcl_data_type_list())& lut,
        _In_ const ctl_oc_telemetry_item_t& item) {
    for (std::size_t i = 0; i < lut.size(); ++i) {
        if (lut[i] == item.type) {
            return i;
        }
    }

    // If the LUT is correct, this should be unreachable.
    assert(false);
    return (std::numeric_limits<std::size_t>::max)();
}

#endif /* defined(POWER_OVERWHELMING_WITH_IGCL) */
