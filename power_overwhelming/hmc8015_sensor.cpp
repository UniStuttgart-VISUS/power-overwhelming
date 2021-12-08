// <copyright file="hmc8015_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "hmc8015_sensor.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

#include "convert_string.h"
#include "visa_library.h"
#include "visa_sensor_impl.h"


/*
 * visus::power_overwhelming::hmc8015_sensor::for_all
 */
std::size_t visus::power_overwhelming::hmc8015_sensor::for_all(
        hmc8015_sensor *out_sensors, const std::size_t cnt_sensors,
        const std::int32_t timeout) {
    // Build the query for all R&S HMC8015 instruments.
    std::string query("?*::");      // Any protocol
    query += vendor_id;             // Only R&S
    query += "::";
    query += product_id;            // Only HMC8015
    query += "::?*::INSTR";         // All serial numbers.

    // Search the instruments using VISA.
    auto devices = detail::visa_library::instance().find_resource(
        query.c_str());

    // Create a sensor for each instrument we found.
    for (std::size_t i = 0; (i < cnt_sensors) && (i < devices.size()); ++i) {
        out_sensors[i] = hmc8015_sensor(devices[i].c_str(), timeout);
    }

    return devices.size();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::hmc8015_sensor
 */
visus::power_overwhelming::hmc8015_sensor::hmc8015_sensor(void)
    : _impl(nullptr) { }


/*
 * visus::power_overwhelming::hmc8015_sensor::hmc8015_sensor
 */
visus::power_overwhelming::hmc8015_sensor::hmc8015_sensor(
        const char *path, const std::int32_t timeout)
    : _impl(new detail::visa_sensor_impl(path, timeout)) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    // Configure the device as in the R&S instrument driver.
    this->_impl->set_attribute(VI_ATTR_TMO_VALUE, 5000);
    this->_impl->set_buffer((VI_READ_BUF | VI_WRITE_BUF), 4096);
    this->_impl->set_attribute(VI_ATTR_WR_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS);
    this->_impl->set_attribute(VI_ATTR_RD_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS);

    // Query the instrument name for use a sensor name.
    this->_impl->sensor_name = detail::convert_string(this->_impl->identify());
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::hmc8015_sensor::~hmc8015_sensor
 */
visus::power_overwhelming::hmc8015_sensor::~hmc8015_sensor(void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::hmc8015_sensor::name
 */
const wchar_t *visus::power_overwhelming::hmc8015_sensor::name(
        void) const noexcept {
    return (this->_impl != nullptr)
        ? this->_impl->sensor_name.c_str()
        : nullptr;
}


/*
 * visus::power_overwhelming::hmc8015_sensor::operator =
 */
visus::power_overwhelming::hmc8015_sensor&
visus::power_overwhelming::hmc8015_sensor::operator =(
        hmc8015_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::hmc8015_sensor::operator bool
 */
visus::power_overwhelming::hmc8015_sensor::operator bool(void) const noexcept {
    return (this->_impl != nullptr);
}
