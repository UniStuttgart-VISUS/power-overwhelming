// <copyright file="tinkerforge_time_translator.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_time_translator.h"

#include <limits>
#include <stdexcept>

#include "tinkerforge_error_category.h"


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_time_translator::check_support
 */
bool PWROWG_DETAIL_NAMESPACE::tinkerforge_time_translator
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
PWROWG_DETAIL_NAMESPACE::tinkerforge_time_translator::times_type
PWROWG_DETAIL_NAMESPACE::tinkerforge_time_translator::get_coord_times(
        _In_ bricklet_type& bricklet) {
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    using namespace std::chrono;
    std::uint32_t time;

    const auto begin = timestamp::now();
    const auto status = ::voltage_current_v2_get_time(&bricklet, &time);
    const auto end = timestamp::now();
    throw_if_tinkerforge_failed(status);

    const auto dt = duration_cast<milliseconds>(end - begin).count();
    return times_type(timestamp::middle(begin, end), time);

#else /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
    throw std::logic_error("This operation is not supported without the "
        "customised firmware to read the clock of the bricklet.");
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}


/*
 * ...::detail::tinkerforge_time_translator::tinkerforge_time_translator
 */
PWROWG_DETAIL_NAMESPACE::tinkerforge_time_translator
::tinkerforge_time_translator(void) noexcept {
    initialise_triple_buffer_state(this->_state);
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_time_translator::update
 */
bool PWROWG_DETAIL_NAMESPACE::tinkerforge_time_translator::update(
        _In_ bricklet_type& bricklet) noexcept {
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    assert(this->_begin.host != 0);
    assert(this->_begin.bricklet != 0);

    // Determine the current time on the host and the bricklet.
    auto& b = this->_buffer[get_write_buffer_index(this->_state)];
    b.first = get_coord_times(bricklet);

    // Compute the times elapsed on the host and on the bricklet.
    assert(b.first.bricklet > this->_begin.bricklet);
    const auto db = b.first.bricklet - this->_begin.bricklet;
    const auto dh = std::chrono::duration_cast<float_millis>(
        b.first.host - this->_begin.host);

    // Compute the scaling of the bricklet clock and the host clock.
    b.second = dh.count() / static_cast<double>(db);

    // Publish the new values.
    swap_write_buffer(this->_state);

    return true;
#else /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
    assert(this->_begin.host == timestamp::zero);
    assert(this->_begin.bricklet == 0);
    return false;
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_time_translator::operator ()
 */
PWROWG_NAMESPACE::timestamp
PWROWG_DETAIL_NAMESPACE::tinkerforge_time_translator::operator ()(
        _In_ const bricklet_time_type time,
        _In_ bricklet_type& bricklet) {
    swap_read_buffer(this->_state);
    auto& b = this->_buffer[get_read_buffer_index(this->_state)];

    const auto cur = static_cast<std::int64_t>(time);
    const auto last = static_cast<std::int64_t>(b.first.bricklet);
    assert(last >= cur);

    const auto dt = static_cast<double>(last - cur);
    const auto retval = b.first.host + float_millis(dt * b.second);

    return retval;
}
