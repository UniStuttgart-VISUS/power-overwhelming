// <copyright file="timezone.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/timestamp.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Gets the timezone bias of the system in 100 ns units.
    /// </summary>
    /// <returns>The timezone bias in 100 ns units.</returns>
    timestamp::value_type get_timezone_bias(void);

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
