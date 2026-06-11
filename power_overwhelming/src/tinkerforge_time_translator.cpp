// <copyright file="tinkerforge_time_translator.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_time_translator.h"

#include <limits>
#include <stdexcept>


/*
 * visus::power_overwhelming::detail::tinkerforge_time_translator::check_support
 */
bool visus::power_overwhelming::detail::tinkerforge_time_translator
::check_support(_In_ bricklet_type& bricklet) noexcept {
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    char connected_to_uid[8];
    std::uint16_t device_id;
    std::uint8_t firmware_version[3];
    std::uint8_t hardware_version[3];
    char position;
    char uid[8];

    // Get the firmware version so that we can find out whether the bricklet
    // supports our customised callback that includes on-device time.
    {
        auto status = ::voltage_current_v2_get_identity(&bricklet, uid,
            connected_to_uid, &position, hardware_version, firmware_version,
            &device_id);
        if (status < 0) {
            return false;
        }
    }

    // Check against the configured firmware version. The major version must
    // always be set by the build system, the remainer is only checked if set.
    if (firmware_version[0] != CUSTOM_TINKERFORGE_FIRMWARE_MJ) {
        return false;
    }

#if defined(CUSTOM_TINKERFORGE_FIRMWARE_MN)
    if (firmware_version[1] != CUSTOM_TINKERFORGE_FIRMWARE_MN) {
        return false;
    }
#endif /* CUSTOM_TINKERFORGE_FIRMWARE_MN */

#if defined(CUSTOM_TINKERFORGE_FIRMWARE_RV)
    if (firmware_version[2] != CUSTOM_TINKERFORGE_FIRMWARE_RV) {
        return false;
    }
#endif /* CUSTOM_TINKERFORGE_FIRMWARE_RV */

    // No conflicting version found, so it should be supported.
    return true;

#else /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
    return false;
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}


/*
 * ...::detail::tinkerforge_time_translator::get_coord_times
 */
visus::power_overwhelming::detail::tinkerforge_time_translator::times_type
visus::power_overwhelming::detail::tinkerforge_time_translator::get_coord_times(
        _In_ bricklet_type& bricklet) {
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    using namespace std::chrono;
    std::uint32_t time;

    const auto begin = timestamp::now();
    const auto status = ::voltage_current_v2_get_time(&bricklet, &time);
    const auto end = timestamp::now();
    if (status < 0) {
        throw tinkerforge_exception(status);
    }

    const auto dt = duration_cast<milliseconds>(end - begin).count();
    return std::make_pair(begin + milliseconds(dt / 2), time);

#else /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
    throw std::logic_error("This operation is not supported without the "
        "customised firmware to read the clock of the bricklet.");
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}


/*
 * ...::detail::tinkerforge_time_translator::tinkerforge_time_translator
 */
visus::power_overwhelming::detail::tinkerforge_time_translator
::tinkerforge_time_translator(void) noexcept
        : _begin{},
        _last_update{},
        _time_scale(1.0),
        _next_update((std::numeric_limits<std::size_t>::max)()),
        _update_every((std::numeric_limits<std::size_t>::max)()) { }


/*
 * visus::power_overwhelming::detail::tinkerforge_time_translator::update
 */
bool visus::power_overwhelming::detail::tinkerforge_time_translator::update(
        _In_ bricklet_type& bricklet) noexcept {
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    using namespace std::chrono;
    assert(this->_begin.first != 0);
    assert(this->_begin.second != 0);

    // Determine the current time on the host and the bricklet.
    this->_last_update = get_coord_times(bricklet);

    // Compute the times elapsed on the host and on the bricklet since last reset.
    const auto db = static_cast<double>(this->_last_update.second - this->_begin.second);
    const auto dh = duration_cast<duration<double, std::milli>>(this->_last_update.first - this->_begin.first).count();
    assert(db > 0.0);

    // Compute the scaling of the bricklet clock in relation to the host system.
    this->_time_scale = dh / db;

    // Reset the update counter.
    this->_next_update = this->_update_every;

    return true;
#else /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
    assert(this->_begin_host == 0);
    assert(this->_time_offset.count() == 0);
    return false;
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}


/*
 * visus::power_overwhelming::detail::tinkerforge_time_translator::operator ()
 */
visus::power_overwhelming::timestamp
visus::power_overwhelming::detail::tinkerforge_time_translator::operator ()(
        _In_ const bricklet_time_type time,
        _In_ bricklet_type& bricklet) {
    using namespace std::chrono;

    const auto db = static_cast<double>(static_cast<int64_t>(time) - static_cast<int64_t>(this->_last_update.second));
    const auto retval = this->_last_update.first + duration<double, std::milli>(db * this->_time_scale);

    if (this->_next_update == 0) {
        this->update(bricklet);
    } else {
        --this->_next_update;
    }

    return retval;
}
