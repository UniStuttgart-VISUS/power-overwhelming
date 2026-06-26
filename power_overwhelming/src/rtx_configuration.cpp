// <copyright file="rtx_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_configuration.h"

#include <iterator>
#include <memory>
#include <vector>

#include "visus/pwrowg/convert_string.h"

#include "json_serialiser.h"
#include "rtx_serialisation.h"


/*
 * PWROWG_NAMESPACE::rtx_configuration::id
 */
const PWROWG_NAMESPACE::guid PWROWG_NAMESPACE::rtx_configuration::id(
    0xebfa0324, 0x7d7a, 0x464e, 0x85, 0x10, 0xc1, 0xa1, 0x9c, 0xba, 0xac, 0xaf);


/*
 * PWROWG_NAMESPACE::rtx_configuration::from_json
 */
PWROWG_NAMESPACE::rtx_configuration
PWROWG_NAMESPACE::rtx_configuration::from_json(_In_z_ const char *json) {
    if (json == nullptr) {
        throw std::invalid_argument("A valid JSON string must be provided.");
    }

    const auto j = nlohmann::json::parse(json);
    return detail::json_deserialise<rtx_configuration>(j);
}


/*
 * PWROWG_NAMESPACE::rtx_configuration::load
 */
PWROWG_NAMESPACE::rtx_configuration PWROWG_NAMESPACE::rtx_configuration::load(
        _In_z_ const wchar_t *path) {
    auto json = detail::load_json(path);
    return detail::json_deserialise<rtx_configuration>(json);
}


/*
 * PWROWG_NAMESPACE::rtx_configuration::load
 */
PWROWG_NAMESPACE::rtx_configuration PWROWG_NAMESPACE::rtx_configuration::load(
        _In_z_ const char *path) {
    auto json = detail::load_json(path);
    return detail::json_deserialise<rtx_configuration>(json);
}

/*
 * PWROWG_NAMESPACE::rtx_configuration::rtx_configuration
 */
PWROWG_NAMESPACE::rtx_configuration::rtx_configuration(void)
        : _download_retries(1),
        _download_timeout(0),
        _reset_flags(rtx_instrument_reset::reset
            | rtx_instrument_reset::status),
        _reset_on_enumerate(false) {
    this->_sensors.emplace<std::vector<rtx_sensor_definition>>();
}


/*
 * PWROWG_NAMESPACE::rtx_configuration::add_sensor
 */
PWROWG_NAMESPACE::rtx_configuration&
PWROWG_NAMESPACE::rtx_configuration::add_sensor(
        _In_ const rtx_sensor_definition& sensor) {
    assert(this->_sensors);
    const auto s = this->_sensors.get<std::vector<rtx_sensor_definition>>();
    assert(s != nullptr);
    s->push_back(sensor);
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_configuration::add_sensor
 */
PWROWG_NAMESPACE::rtx_configuration&
PWROWG_NAMESPACE::rtx_configuration::add_sensor(
        _Inout_ rtx_sensor_definition&& sensor) {
    assert(this->_sensors);
    const auto s = this->_sensors.get<std::vector<rtx_sensor_definition>>();
    assert(s != nullptr);
    s->push_back(std::move(sensor));
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_configuration::add_sensor
 */
PWROWG_NAMESPACE::rtx_configuration&
PWROWG_NAMESPACE::rtx_configuration::add_sensor(
        _In_z_ const wchar_t *path,
        _In_ const rtx_channel& voltage_channel,
        _In_ const rtx_channel& current_channel,
        _In_ const rtx_waveform_points waveform_points) {
    rtx_sensor_definition sensor(path, voltage_channel, current_channel,
        nullptr, waveform_points);
    return this->add_sensor(std::move(sensor));
}


/*
 * PWROWG_NAMESPACE::rtx_configuration::add_sensor
 */
PWROWG_NAMESPACE::rtx_configuration&
PWROWG_NAMESPACE::rtx_configuration::add_sensor(
        _In_z_ const char *path,
        _In_ const rtx_channel& voltage_channel,
        _In_ const rtx_channel& current_channel,
        _In_ const rtx_waveform_points waveform_points) {
    rtx_sensor_definition sensor(path, voltage_channel, current_channel,
        nullptr, waveform_points);
    return this->add_sensor(std::move(sensor));
}


/*
 * PWROWG_NAMESPACE::rtx_configuration::count_sensors
 */
std::size_t PWROWG_NAMESPACE::rtx_configuration::count_sensors(
        void) const noexcept {
    assert(this->_sensors);
    const auto s = this->_sensors.get<std::vector<rtx_sensor_definition>>();
    assert(s != nullptr);
    return s->size();
}


/*
 * PWROWG_NAMESPACE::rtx_configuration::save
 */
void PWROWG_NAMESPACE::rtx_configuration::save(
        _In_z_ const wchar_t *path) const {
    detail::save_json(detail::json_serialise(*this), path);
}


/*
 * PWROWG_NAMESPACE::rtx_configuration::save
 */
void PWROWG_NAMESPACE::rtx_configuration::save(_In_z_ const char *path) const {
    detail::save_json(detail::json_serialise(*this), path);
}


/*
 * PWROWG_NAMESPACE::rtx_configuration::sensor
 */
const PWROWG_NAMESPACE::rtx_sensor_definition&
PWROWG_NAMESPACE::rtx_configuration::sensor(_In_ const std::size_t index) const {
    assert(this->_sensors);
    const auto s = this->_sensors.get<std::vector<rtx_sensor_definition>>();
    assert(s != nullptr);

    if (index >= s->size()) {
        throw std::out_of_range("The specified sensor does not exist.");
    }

    return (*s)[index];
}


/*
 * PWROWG_NAMESPACE::rtx_configuration::sensors
 */
_Ret_valid_ const PWROWG_NAMESPACE::rtx_sensor_definition *
PWROWG_NAMESPACE::rtx_configuration::sensors(void) const noexcept {
    assert(this->_sensors);
    const auto s = this->_sensors.get<std::vector<rtx_sensor_definition>>();
    assert(s != nullptr);
    return s->data();
}


/*
 * PWROWG_NAMESPACE::rtx_configuration::sensors
 */
PWROWG_NAMESPACE::rtx_configuration&
PWROWG_NAMESPACE::rtx_configuration::sensors(
        _In_reads_opt_(cnt) rtx_sensor_definition *sensors,
        _In_ const std::size_t cnt) {
    assert(this->_sensors);
    auto s = this->_sensors.get<std::vector<rtx_sensor_definition>>();
    assert(s != nullptr);
    s->clear();

    if (sensors != nullptr) {
        std::copy_n(sensors, cnt, std::back_inserter(*s));
    }

    return *this;
}
