// <copyright file="tinkerforge_time_translator.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_time_translator.h"

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
    std::uint32_t time;

    const auto begin = create_timestamp(timestamp_resolution::milliseconds);
    const auto status = ::voltage_current_v2_get_time(&bricklet, &time);
    const auto end = create_timestamp(timestamp_resolution::milliseconds);
    if (status < 0) {
        throw tinkerforge_exception(status);
    }

    const auto dt = end - begin;
    return std::make_pair(begin + (dt >> 1), time);
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
        : _begin_bricklet(0), _begin_host(0), _time_offset(0),
        _time_scale(1.0) { }


/*
 * visus::power_overwhelming::detail::tinkerforge_time_translator::translate
 */
visus::power_overwhelming::timestamp_type
visus::power_overwhelming::detail::tinkerforge_time_translator::translate(
        _In_ const bricklet_time_type time,
        _In_ const timestamp_resolution resolution) {
    const auto offset = static_cast<double>(time) * this->_time_scale;
    return convert(timestamp_resolution::milliseconds,
        this->_time_offset + static_cast<timestamp_type>(offset),
        resolution);
}


/*
 * visus::power_overwhelming::detail::tinkerforge_time_translator::update
 */
bool visus::power_overwhelming::detail::tinkerforge_time_translator::update(
        _In_ bricklet_type& bricklet) noexcept {
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    assert(this->_begin_host > 0);
    std::uint32_t btime;

    // Determine the current time on the host and the bricklet.
    const auto begin = create_timestamp(timestamp_resolution::milliseconds);
    const auto status = ::voltage_current_v2_get_time(&bricklet, &btime);
    const auto end = create_timestamp(timestamp_resolution::milliseconds);
    if (status < 0) {
        return false;
    }

    const auto dt = end - begin;
    const auto htime = begin + (dt >> 1);

    // Compute the times elapsed on the host and on the bricklet.
    const auto db = static_cast<double>(btime) - this->_begin_bricklet;
    const auto dh = static_cast<double>(htime)
        - static_cast<double>(this->_begin_host);

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

    return true;
#else /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
    return false;
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}
