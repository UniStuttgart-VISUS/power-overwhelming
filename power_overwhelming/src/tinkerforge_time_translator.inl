﻿// <copyright file="tinkerforge_time_translator.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::detail::tinkerforge_time_translator::reset
 */
template<class TRep>
void visus::power_overwhelming::detail::tinkerforge_time_translator::reset(
        _In_ bricklet_type& bricklet,
        _In_ const std::chrono::duration<timestamp_type, TRep> time_span) {
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    // Get the times on the host and the bricklet, wait for the user-defined
    // time span and do it again.
    const auto begin = get_coord_times(bricklet);
    std::this_thread::sleep_for(time_span);
    const auto end = get_coord_times(bricklet);

    // Compute the times elapsed on the host and on the bricklet.
    this->_begin_bricklet = static_cast<double>(begin.second);
    this->_begin_host = begin.first;
    const auto db = static_cast<double>(end.second) - this->_begin_bricklet;
    const auto dh = static_cast<double>(end.first)
        - static_cast<double>(begin.first);

    // Assuming both clocks having started at the same point in time, compute
    // the scaling of the bricklet clock such that it runs at the same rate as
    // the host system.
    this->_time_scale = dh / db;

    // Compute the (probable) point in time on the host when the time on the
    // bricklet was zero. We need to scale the offset, because the result should
    // be in the units of the clock on the host, but the offset we have is in
    // ticks on the bricklet.
    const auto origin_offset = static_cast<timestamp_type>(
        this->_time_scale * this->_begin_bricklet);
    this->_time_offset = this->_begin_host - origin_offset;
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}