// <copyright file="no_visa_error_msg.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph M�ller</author>

#pragma once


namespace visus {
namespace power_overwhelming {
namespace detail {

    static constexpr const char *no_visa_error_msg = "The Power Overwhelming "
        "library was compiled without support for the Virtual Instrument Software "
        "Architecture.";

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
