// <copyright file="tinkerforge_controller.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/tinkerforge_controller.h"

#include "tinkerforge_sensor.h"


/*
 * PWROWG_NAMESPACE::tinkerforge_controller::~tinkerforge_controller
 */
PWROWG_NAMESPACE::tinkerforge_controller::~tinkerforge_controller(
        void) noexcept {
    delete[] this->_sensors;
}


/*
 * PWROWG_NAMESPACE::tinkerforge_controller::resync_clock
 */
void PWROWG_NAMESPACE::tinkerforge_controller::resync_clock(void) const {
    assert((this->_sensors != nullptr) || (this->_cnt == 0));
    for (std::size_t i = 0; i < this->_cnt; ++i) {
        assert(this->_sensors[i] != nullptr);
        this->_sensors[i]->resync_internal_clock();
    }
}


/*
 * PWROWG_NAMESPACE::tinkerforge_controller::operator =
 */
PWROWG_NAMESPACE::tinkerforge_controller&
PWROWG_NAMESPACE::tinkerforge_controller::operator =(
        _In_ const tinkerforge_controller& rhs) {
    if (this != std::addressof(rhs)) {
        auto sensors = new sensor_type *[rhs._cnt];
        std::copy(rhs._sensors, rhs._sensors + rhs._cnt, sensors);
        delete[] this->_sensors;

        this->_cnt = rhs._cnt;
        this->_sensors = sensors;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::tinkerforge_controller::operator =
 */
PWROWG_NAMESPACE::tinkerforge_controller&
PWROWG_NAMESPACE::tinkerforge_controller::operator =(
        _Inout_ tinkerforge_controller&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_cnt = rhs._cnt;
        rhs._cnt = 0;
        this->_sensors = rhs._sensors;
        rhs._sensors = nullptr;
    }

    return *this;
}

