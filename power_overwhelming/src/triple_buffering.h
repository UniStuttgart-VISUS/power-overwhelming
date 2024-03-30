// <copyright file="triple_buffering.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <atomic>
#include <cinttypes>


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// The type used to store the state of a triple buffer.
    /// </summary>
    typedef std::atomic<std::uint_fast8_t> triple_buffer_state;

    /// <summary>
    /// Gets the index of the current read buffer of the given triple buffer.
    /// </summary>
    /// <remarks>
    /// According to https://en.cppreference.com/w/cpp/atomic/atomic, atomics
    /// should have a <c>value_type</c> member regarless of whether they are
    /// specialised or not, but on Linux, this seems to be missing, so we do a
    /// wild <c>decltype</c> hack instead.
    /// </remarks>
    /// <param name="state"></param>
    /// <returns></returns>
    inline auto get_read_buffer_index(triple_buffer_state& state)
            -> decltype(state.load()) {
        return (state.load() & 0x03);
    }

    /// <summary>
    /// Gets the index of the current write buffer of the given triple buffer.
    /// </summary>
    /// <remarks>
    /// See <see cref="get_read_buffer_index" />.
    /// </remarks>
    /// <param name="state"></param>
    /// <returns></returns>
    inline auto get_write_buffer_index(triple_buffer_state& state) 
            -> decltype(state.load()) {
        return ((state.load() & 0x30) >> 4);
    }

    /// <summary>
    /// Assigns the correct initial state to a triple buffer.
    /// </summary>
    /// <param name="state"></param>
    inline void initialise_triple_buffer_state(triple_buffer_state& state) {
        state = 0x6;
    }

    /// <summary>
    /// Swaps the index of the read buffer, ie signals that the reader is done
    /// consuming the data.
    /// </summary>
    /// <param name="state"></param>
    /// <returns><c>true</c> if the buffer was actually swapped and new data are
    /// available, <c>false</c> if the read buffer index is unchanged as no new
    /// data are available.</returns>
    bool swap_read_buffer(triple_buffer_state& state);

    /// <summary>
    /// Swaps the index of the wrie buffer, ie signals that the writer completed
    /// storing new data.
    /// </summary>
    /// <param name="state"></param>
    void swap_write_buffer(triple_buffer_state& state);

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
