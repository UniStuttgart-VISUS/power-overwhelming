// <copyright file="filetime_period.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#pragma once

#include <chrono>


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// The 100ns period defining the reolution of <see cref="FILETIME" />.
    /// </summary>
    typedef std::ratio<1, 10000000> filetime_period;

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
