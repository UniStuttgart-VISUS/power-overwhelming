// <copyright file="daqmx_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/daqmx_configuration.h"

#include <vector>

#include "json_serialiser.h"
#include "daqmx_serialisation.h"


/*
 * PWROWG_NAMESPACE::daqmx_configuration::id
 */
const PWROWG_NAMESPACE::guid PWROWG_NAMESPACE::daqmx_configuration::id(
    0x505ee24b, 0x3e1e, 0x43a2, 0xad15, 0x91, 0xbe, 0x37, 0x2a, 0x91, 0xbf);


/*
 * PWROWG_NAMESPACE::daqmx_configuration::from_json
 */
PWROWG_NAMESPACE::daqmx_configuration
PWROWG_NAMESPACE::daqmx_configuration::from_json(_In_z_ const char *json) {
    if (json == nullptr) {
        throw std::invalid_argument("A valid JSON string must be provided.");
    }

    const auto j = nlohmann::json::parse(json);
    return detail::json_deserialise<daqmx_configuration>(j);
}


/*
 * PWROWG_NAMESPACE::daqmx_configuration::load
 */
PWROWG_NAMESPACE::daqmx_configuration
PWROWG_NAMESPACE::daqmx_configuration::load(_In_z_ const wchar_t *path) {
    auto json = detail::load_json(path);
    return detail::json_deserialise<daqmx_configuration>(json);
}


/*
 * PWROWG_NAMESPACE::daqmx_configuration::load
 */
PWROWG_NAMESPACE::daqmx_configuration
PWROWG_NAMESPACE::daqmx_configuration::load(_In_z_ const char *path) {
    auto json = detail::load_json(path);
    return detail::json_deserialise<daqmx_configuration>(json);
}


/*
 * PWROWG_NAMESPACE::daqmx_configuration::daqmx_configuration
 */
PWROWG_NAMESPACE::daqmx_configuration::daqmx_configuration(void) {
    this->_sensors.emplace<std::vector<daqmx_sensor_definition>>();
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    this->_timing.emplace<daqmx_sample_clock_timing>(1000.0);
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
}


/*
 * PWROWG_NAMESPACE::daqmx_configuration::add_sensor
 */
PWROWG_NAMESPACE::daqmx_configuration&
PWROWG_NAMESPACE::daqmx_configuration::add_sensor(
        _In_ const daqmx_sensor_definition& sensor) {
    assert(this->_sensors);
    const auto s = this->_sensors.get<std::vector<daqmx_sensor_definition>>();
    assert(s != nullptr);
    s->push_back(sensor);
    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_configuration::add_sensor
 */
PWROWG_NAMESPACE::daqmx_configuration&
PWROWG_NAMESPACE::daqmx_configuration::add_sensor(
        _Inout_ daqmx_sensor_definition&& sensor) {
    assert(this->_sensors);
    const auto s = this->_sensors.get<std::vector<daqmx_sensor_definition>>();
    assert(s != nullptr);
    s->push_back(std::move(sensor));
    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_configuration::count_sensors
 */
std::size_t PWROWG_NAMESPACE::daqmx_configuration::count_sensors(
        void) const noexcept {
    assert(this->_sensors);
    const auto s = this->_sensors.get<std::vector<daqmx_sensor_definition>>();
    return (s != nullptr) ? s->size() : 0;
}


/*
 * PWROWG_NAMESPACE::daqmx_configuration::save
 */
void PWROWG_NAMESPACE::daqmx_configuration::save(
        _In_z_ const wchar_t *path) const {
    detail::save_json(detail::json_serialise(*this), path);
}


/*
 * PWROWG_NAMESPACE::daqmx_configuration::save
 */
void PWROWG_NAMESPACE::daqmx_configuration::save(
        _In_z_ const char *path) const {
    detail::save_json(detail::json_serialise(*this), path);
}


/*
 * PWROWG_NAMESPACE::daqmx_configuration::sensor
 */
const PWROWG_NAMESPACE::daqmx_sensor_definition&
PWROWG_NAMESPACE::daqmx_configuration::sensor(_In_ const std::size_t index) const {
    assert(this->_sensors);
    const auto s = this->_sensors.get<std::vector<daqmx_sensor_definition>>();
    assert(s != nullptr);

    if ((s == nullptr) || (index >= s->size())) {
        throw std::out_of_range("The specified sensor does not exist.");
    }

    return (*s)[index];
}


/*
 * PWROWG_NAMESPACE::daqmx_configuration::sensors
 */
_Ret_valid_ const PWROWG_NAMESPACE::daqmx_sensor_definition *
PWROWG_NAMESPACE::daqmx_configuration::sensors(void) const noexcept {
    assert(this->_sensors);
    const auto s = this->_sensors.get<std::vector<daqmx_sensor_definition>>();
    assert(s != nullptr);
    return s->data();
}


/*
 * PWROWG_NAMESPACE::daqmx_configuration::sensors
 */
PWROWG_NAMESPACE::daqmx_configuration&
PWROWG_NAMESPACE::daqmx_configuration::sensors(
        _In_reads_opt_(cnt) daqmx_sensor_definition *sensors,
        _In_ const std::size_t cnt) {
    assert(this->_sensors);
    auto s = this->_sensors.get<std::vector<daqmx_sensor_definition>>();

    if (s == nullptr) {
        this->_sensors.emplace<std::vector<daqmx_sensor_definition>>();
        s = this->_sensors.get<std::vector<daqmx_sensor_definition>>();
    } else {
        s->clear();
    }
    assert(s != nullptr);
    assert(s->empty());

    if (sensors != nullptr) {
        std::copy_n(sensors, cnt, std::back_inserter(*s));
    }

    return *this;
}


#if defined(POWER_OVERWHELMING_WITH_DAQMX)
/*
 * PWROWG_NAMESPACE::daqmx_configuration::timing
 */
const PWROWG_NAMESPACE::daqmx_timing&
PWROWG_NAMESPACE::daqmx_configuration::timing(void) const {
    assert(this->_timing);
    auto retval = this->_timing.get<daqmx_timing>();
    assert(retval != nullptr);
    return *retval;
}


/*
 * PWROWG_NAMESPACE::daqmx_configuration::timing
 */
PWROWG_NAMESPACE::daqmx_configuration&
PWROWG_NAMESPACE::daqmx_configuration::timing(
        _In_ const daqmx_implicit_timing& timing) {
    this->_timing.emplace<daqmx_implicit_timing>(timing);
    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_configuration::timing
 */
PWROWG_NAMESPACE::daqmx_configuration&
PWROWG_NAMESPACE::daqmx_configuration::timing(
        _Inout_ daqmx_implicit_timing&& timing) {
    this->_timing.emplace<daqmx_implicit_timing>(std::move(timing));
    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_configuration::timing
 */
PWROWG_NAMESPACE::daqmx_configuration&
PWROWG_NAMESPACE::daqmx_configuration::timing(
        _In_ const daqmx_sample_clock_timing& timing) {
    this->_timing.emplace<daqmx_sample_clock_timing>(timing);
    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_configuration::timing
 */
PWROWG_NAMESPACE::daqmx_configuration&
PWROWG_NAMESPACE::daqmx_configuration::timing(
        _Inout_ daqmx_sample_clock_timing&& timing) {
    this->_timing.emplace<daqmx_sample_clock_timing>(std::move(timing));
    return *this;
}
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */


#if defined(POWER_OVERWHELMING_WITH_DAQMX)
/*
 * PWROWG_NAMESPACE::daqmx_configuration::try_get
 */
bool PWROWG_NAMESPACE::daqmx_configuration::try_get(
        _Out_opt_ const daqmx_implicit_timing *& timing) const {
    auto t = this->_timing.get<daqmx_timing>();
    if (t == nullptr) {
        return false;
    }

    timing = dynamic_cast<const daqmx_implicit_timing *>(t);
    return (timing != nullptr);
}


/*
 * PWROWG_NAMESPACE::daqmx_configuration::try_get
 */
bool PWROWG_NAMESPACE::daqmx_configuration::try_get(
        _Out_opt_ const daqmx_sample_clock_timing *& timing) const {
    auto t = this->_timing.get<daqmx_timing>();
    if (t == nullptr) {
        return false;
    }

    timing = dynamic_cast<const daqmx_sample_clock_timing *>(t);
    return (timing != nullptr);
}
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
