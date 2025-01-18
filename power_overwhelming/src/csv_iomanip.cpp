// <copyright file="csv_iomanip.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/csv_iomanip.h"


static const int idx_delimiter = std::ios_base::xalloc();
static const int idx_header = std::ios_base::xalloc();
static const int idx_quote = std::ios_base::xalloc();
static const int idx_quote_char = std::ios_base::xalloc();


/*
 * visus::power_overwhelming::detail::io_index_delimiter
 */
int visus::power_overwhelming::detail::io_index_delimiter(void) noexcept {
    return ::idx_delimiter;
}


/*
 * visus::power_overwhelming::detail::io_index_header
 */
int visus::power_overwhelming::detail::io_index_header(void) noexcept {
    return ::idx_header;
}


/*
 * visus::power_overwhelming::detail::io_index_quote
 */
int visus::power_overwhelming::detail::io_index_quote(void) noexcept {
    return ::idx_quote;
}
