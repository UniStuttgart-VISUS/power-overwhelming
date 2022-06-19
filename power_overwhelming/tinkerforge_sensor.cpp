// <copyright file="tinkerforge_sensor.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2021 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#include "tinkerforge_sensor.h"

#include <chrono>
#include <thread>
#include <vector>

#include <bricklet_voltage_current_v2.h>

#include "timestamp.h"
#include "tinkerforge_exception.h"
#include "tinkerforge_sensor_impl.h"


/*
 * visus::power_overwhelming::tinkerforge_sensor::get_definitions
 */
std::size_t visus::power_overwhelming::tinkerforge_sensor::get_definitions(
        tinkerforge_sensor_definiton *out_definitions,
        const std::size_t cnt_definitions, const std::size_t timeout,
        const char *host, const std::uint16_t port) {
    std::vector<detail::tinkerforge_bricklet> bricklets;
    detail::tinkerforge_scope scope(host, port);

    auto retval = scope.copy_bricklets(std::back_inserter(bricklets),
        [](const detail::tinkerforge_bricklet& b) {
            return (b.device_type() == VOLTAGE_CURRENT_V2_DEVICE_IDENTIFIER);
        }, std::chrono::milliseconds(timeout), cnt_definitions);

    if (out_definitions != nullptr) {
        for (std::size_t i = 0; (i < cnt_definitions) && (i < retval); ++i) {
            out_definitions[i] = tinkerforge_sensor_definiton(
                bricklets[i].uid().c_str());
        }
    }

    return retval;
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
        (host != nullptr) ? host : default_host,
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
        (host != nullptr) ? host : default_host,
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
        (host != nullptr) ? host : default_host,
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
 * visus::power_overwhelming::tinkerforge_sensor::sample
 */
visus::power_overwhelming::measurement
visus::power_overwhelming::tinkerforge_sensor::sample(
        const timestamp_resolution resolution) const {
    if (!*this) {
        throw std::runtime_error("A disposed instance of tinkerforge_sensor "
            "cannot be sampled.");
    }

    static const auto thousand = static_cast<measurement::value_type>(1000);
    std::int32_t current = 0;   // Current in mA.
    std::int32_t power = 0;     // Power in mW.
    std::int32_t voltage = 0;   // Voltage in mV.

    {
        auto status = ::voltage_current_v2_get_voltage(&this->_impl->bricklet,
            &voltage);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }

    {
        auto status = ::voltage_current_v2_get_current(&this->_impl->bricklet,
            &voltage);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }

    {
        auto status = ::voltage_current_v2_get_power(&this->_impl->bricklet,
            &power);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }

    return measurement(this->_impl->sensor_name.c_str(),
        create_timestamp(resolution),
        static_cast<measurement::value_type>(voltage) / thousand,
        static_cast<measurement::value_type>(current) / thousand,
        static_cast<measurement::value_type>(power) / thousand);
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::sample
 */
void visus::power_overwhelming::tinkerforge_sensor::sample(
        const measurement_callback on_measurement,
        const std::int32_t sampling_period) {
    if (!*this) {
        throw std::runtime_error("A disposed instance of tinkerforge_sensor "
            "cannot be sampled.");
    }

    if (on_measurement != nullptr) {
        // Callback is non-null, so user wants to enable asynchronous sampling.
        measurement_callback expected = nullptr;

        if (!this->_impl->on_measurement.compare_exchange_strong(expected,
                on_measurement)) {
            throw std::logic_error("Asynchronous sampling cannot be started "
                "while it is already running.");
        }

        try {
            this->_impl->enable_callbacks(sampling_period);
        } catch (...) {
            // Clear the guard in case the operation failed.
            this->_impl->on_measurement.exchange(nullptr);
            throw;
        }

    } else {
        // If the callback is null, disable asynchronous sampling.
        if (this->_impl->on_measurement != nullptr) {
            this->_impl->disable_callbacks();
        }

        this->_impl->on_measurement.exchange(on_measurement);
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
