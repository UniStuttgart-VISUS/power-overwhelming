// <copyright file="rtx_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/rtx_sensor.h"

#include <algorithm>
#include <cassert>
#include <limits>
#include <stdexcept>
#include <utility>

#include "power_overwhelming/convert_string.h"

#include "timestamp.h"
#include "tokenise.h"
#include "visa_library.h"


/*
 * visus::power_overwhelming::rtx_sensor::configure_instrument
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_sensor::configure_instrument(
        _In_reads_(cnt) const rtx_sensor *sensors,
        _In_ const std::size_t cnt,
        _In_ const rtx_instrument_configuration& configuration) {
    if ((sensors == nullptr) || (cnt < 1)) {
        throw std::invalid_argument("The list of sensors to configure the "
            "instrument for must not be empty.");
    }

    throw "TODO";
}


/*
 * visus::power_overwhelming::rtx_sensor::for_all
 */
std::size_t visus::power_overwhelming::rtx_sensor::for_all(
        _Out_writes_opt_(cnt_sensors) rtx_sensor *out_sensors,
        _In_ std::size_t cnt_sensors,
        _In_ const std::int32_t timeout) {
    std::string query("?*::");                      // Any protocol
    query += visa_instrument::rohde_und_schwarz;    // Only R&S
    query += "::";
    query += rtx_instrument::product_id;            // Only RTA/RTB
    query += "::?*::INSTR";                         // All serial numbers

    // Search the instruments using VISA.
    auto devices = detail::visa_library::instance().find_resource(
        query.c_str());

    // Guard against misuse.
    if (out_sensors == nullptr) {
        cnt_sensors = 0;
    }

    // Create a sensor for each instrument we found.
    for (std::size_t i = 0; (i < cnt_sensors) && (i < devices.size()); ++i) {
        out_sensors[i] = rtx_sensor(devices[i].c_str(), timeout);
    }

    return devices.size();
}


/*
 * visus::power_overwhelming::rtx_sensor::rtx_sensor
 */
visus::power_overwhelming::rtx_sensor::rtx_sensor(
        _In_z_ const char *path,
        _In_ const visa_instrument::timeout_type timeout)
        : _instrument(path, timeout) {
    this->initialise();
}


/*
 * visus::power_overwhelming::rtx_sensor::rtx_sensor
 */
visus::power_overwhelming::rtx_sensor::rtx_sensor(
        _In_z_ const wchar_t *path,
        _In_ const visa_instrument::timeout_type timeout)
        : _instrument(path, timeout) {
    this->initialise();
}


/*
 * visus::power_overwhelming::rtx_sensor::~rtx_sensor
 */
visus::power_overwhelming::rtx_sensor::~rtx_sensor(void) { }


/*
 * *visus::power_overwhelming::rtx_sensor::name
 */
_Ret_maybenull_z_ const wchar_t *visus::power_overwhelming::rtx_sensor::name(
        void) const noexcept {
    return this->_name.as<wchar_t>();
}


/*
 * visus::power_overwhelming::rtx_sensor::operator bool
 */
visus::power_overwhelming::rtx_sensor::operator bool(void) const noexcept {
    return static_cast<bool>(this->_instrument);
}


/*
 * visus::power_overwhelming::rtx_sensor::sample_sync
 */
visus::power_overwhelming::measurement_data
visus::power_overwhelming::rtx_sensor::sample_sync(
        _In_ const timestamp_resolution resolution) const {
    throw "TODO";

}


/*
 * visus::power_overwhelming::rtx_sensor::initialise
 */
void visus::power_overwhelming::rtx_sensor::initialise(void) {
    std::vector<char> id(this->_instrument.identify(nullptr, 0));
    this->_instrument.identify(id.data(), id.size());


    // TODO: compose name
}
