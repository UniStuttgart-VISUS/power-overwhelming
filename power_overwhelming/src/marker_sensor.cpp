// <copyright file="marker_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "marker_sensor.h"

#include <array>
#include <stdexcept>

#include "sensor_array_impl.h"
#include "sensor_description_builder.h"


/*
 * PWROWG_DETAIL_NAMESPACE_BEGIN::marker_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::marker_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    const auto retval = (config.size() > 0) ? 1 : 0;

    if ((retval > 0) && (cnt >= retval)) {
        auto builder = sensor_description_builder::create()
            .with_id(L"VISUS/Marker")
            .with_vendor(L"VISUS")
            .with_name(L"VISUS timestamp markers")
            .with_type(sensor_type::unknown)
            .produces(reading_type::unsigned_integer)
            .measured_in(reading_unit::unknown);
        *dst = builder.build();
    }

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::marker_sensor::emit
 */
bool PWROWG_DETAIL_NAMESPACE::marker_sensor::emit(
        _In_ const timestamp timestamp,
        _In_ const unsigned int id) {
    this->_emitting.store(true, std::memory_order_release);
    pwrowg_on_exit([this](void) { 
        this->_emitting.store(false, std::memory_order_release);
    });

    const auto retval = this->_state && (id < this->_markers);

    if (retval) {
        PWROWG_NAMESPACE::sample sample;
        sample.reading.unsigned_integer = id;
        sample.source = this->_index;
        sample.timestamp = timestamp;
        sensor_array_impl::callback(this->_owner, &sample, 1);
    }

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::marker_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::marker_sensor::sample(_In_ const bool enable) {
    if (enable) {
        this->_state.begin_start();
        this->_state.end_start();
    } else {
        this->_state.begin_stop();
        while (this->_emitting.load(std::memory_order::memory_order_acquire));
        this->_state.end_stop();
    }
}
