// <copyright file="triple_buffering.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "triple_buffering.h"


/*
 * PWROWG_DETAIL_NAMESPACE::swap_read_buffer
 */
bool PWROWG_DETAIL_NAMESPACE::swap_read_buffer(triple_buffer_state& state) {
    auto cur = state.load();
    decltype(cur) nxt;

    do {
        if ((cur & 0x40) == 0) {
            /* Data has not changed. */
            return false;
        }
        nxt = (cur & 0x30)
            | ((cur & 0x03) << 2)
            | ((cur & 0x0c) >> 2);
    } while (!state.compare_exchange_weak(cur, nxt));
    /* Data has changed, buffers are now swapped. */

    return true;
}


/*
 * PWROWG_DETAIL_NAMESPACE::swap_write_buffer
 */
void PWROWG_DETAIL_NAMESPACE::swap_write_buffer(triple_buffer_state& state) {
    auto cur = state.load();
    decltype(cur) nxt;

    do {
        nxt = 0x40 | ((cur & 0x30) >> 2)
            | (cur & 0x03)
            | ((cur & 0x0c) << 2);
    } while (!state.compare_exchange_weak(cur, nxt));
}
