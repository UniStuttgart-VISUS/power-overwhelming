// <copyright file="csv_iomanip.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "csv_iomanip.h"


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


/*
 * visus::power_overwhelming::detail::io_index_quote_char
 */
int visus::power_overwhelming::detail::io_index_quote_char(void) noexcept {
    return ::idx_quote_char;
}
