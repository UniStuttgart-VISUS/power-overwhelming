// <copyright file="tinkerforge_time_translator.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::detail::tinkerforge_time_translator::reset
 */
template<class TRep>
void visus::power_overwhelming::detail::tinkerforge_time_translator::reset(
        _In_ bricklet_type& bricklet,
        _In_ const std::chrono::duration<timestamp::value_type, TRep> ts) {
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    if (check_support(bricklet)) {
        // Get the times on the host and the bricklet, wait for the user-defined
        // time span and do it again.
        this->_begin = get_coord_times(bricklet);
        std::this_thread::sleep_for(ts);

        this->update(bricklet);
    } else {
        throw std::runtime_error("The given bricklet does not have the custom "
            "firmware required for time translation.");
    }
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}
