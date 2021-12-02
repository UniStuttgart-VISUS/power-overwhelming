// <copyright file="tinkerforge_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_sensor.h"

#include <thread>
#include <vector>

#include "tinkerforge_sensor_impl.h"


/*
 * visus::power_overwhelming::tinkerforge_sensor::get_sensors
 */
std::size_t visus::power_overwhelming::tinkerforge_sensor::get_sensors(
        tinkerforge_sensor_definiton *outSensors, const std::size_t cntSensors,
        const char *host, const std::uint16_t port) {
    std::vector<detail::tinkerforge_bricklet> bricklets;
    detail::tinkerforge_scope scope(host, port);

    for (auto i = 0; i < 4; ++i) {
        scope.copy_bricklets(std::back_inserter(bricklets));

        if (bricklets.empty()) {
            // Bricklets are enumerated asynchronously, so if we are calling
            // that for the first time, we might not yet have any information.
            // The (hacky) solution is to wait for a bit and try again ...
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } else {
            // We have at least some bricklets, albeit it is not sure that
            // we have all of them ...
            break;
        }
    }


    // TODO
    return 0;
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::tinkerforge_sensor
 */
visus::power_overwhelming::tinkerforge_sensor::tinkerforge_sensor(
        const char *uid, const char *host, const std::uint16_t port)
        : _impl(nullptr) {
    // The implementation will (i) obtain and manage the scope with the
    // connection to the master brick, (ii) allocate the voltage/current
    // bricklet and manage its life time.
    this->_impl = new detail::tinkerforge_sensor_impl(
        (host != nullptr) ? host : "localhost",
        port,
        uid);
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::tinkerforge_sensor
 */
visus::power_overwhelming::tinkerforge_sensor::tinkerforge_sensor(
        const char *uid, const wchar_t *description, const char *host,
        const std::uint16_t port) : _impl(nullptr) {
    this->_impl = new detail::tinkerforge_sensor_impl(
        (host != nullptr) ? host : "localhost",
        port,
        uid);

    if (description != nullptr) {
        this->_impl->description = description;
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::tinkerforge_sensor
 */
visus::power_overwhelming::tinkerforge_sensor::tinkerforge_sensor(
        const tinkerforge_sensor_definiton& definition,
        const char *host, const std::uint16_t port) : _impl(nullptr) {
    this->_impl = new detail::tinkerforge_sensor_impl(
        (host != nullptr) ? host : "localhost",
        port,
        definition.uid());

    if (definition.description() != nullptr) {
        this->_impl->description = definition.description();
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::~tinkerforge_sensor
 */
visus::power_overwhelming::tinkerforge_sensor::~tinkerforge_sensor(
        void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::description
 */
const wchar_t *visus::power_overwhelming::tinkerforge_sensor::description(
        void) const noexcept {
    if (this->_impl != nullptr) {
        return this->_impl->description.c_str();
    } else {
        return nullptr;
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::name
 */
const wchar_t *visus::power_overwhelming::tinkerforge_sensor::name(
        void) const noexcept {
    if (this->_impl != nullptr) {
        return this->_impl->sensor_name.c_str();
    } else {
        return nullptr;
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::operator =
 */
visus::power_overwhelming::tinkerforge_sensor&
visus::power_overwhelming::tinkerforge_sensor::operator =(
        tinkerforge_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::operator bool
 */
visus::power_overwhelming::tinkerforge_sensor::operator bool(
        void) const noexcept {
    return (this->_impl != nullptr);
}
