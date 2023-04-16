// <copyright file="collector.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/collector.h"

#include <memory>
#include <stdexcept>
#include <vector>

#include <nlohmann/json.hpp>

#include "power_overwhelming/computer_name.h"
#include "power_overwhelming/convert_string.h"

#include "collector_impl.h"
#include "sensor_utilities.h"
#include "tinkerforge_sensor_impl.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    static constexpr const char *field_computer_name = "machine";
    static constexpr const char *field_output = "outputPath";
    static constexpr const char *field_require_marker = "collectRequiresMarker";
    static constexpr const char *field_sampling = "samplingInterval";
    static constexpr const char *field_sensors = "sensors";

    /// <summary>
    /// Create an in-memory JSON document with the template for configuring the
    /// sensors on the machine the software is running on.
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static nlohmann::json make_json_template(void) {
        using power_overwhelming::convert_string;

        nlohmann::json retval;

        retval[field_computer_name] = computer_name<char>();
        retval[field_output] = "output.csv";
        retval[field_sampling] = 5000;  // 5000 µs == 5 ms
        retval[field_require_marker] = true;
        retval[field_sensors] = get_all_sensor_descs();

        return retval;
    }

    /// <summary>
    /// Apply the given JSON configuration to the given collector.
    /// </summary>
    /// <param name="dst"></param>
    /// <param name="cfg"></param>
    static void apply_template(collector_impl *dst, const nlohmann::json& cfg) {
        assert(dst != nullptr);

        // Parse the sensors from their JSON representation.
        auto& sensor_list = cfg[field_sensors];
        dst->sensors = detail::parse_sensors(sensor_list);

        // If we have the sensors, create the output file and store the rest of the
        // properties.
        dst->stream.open(cfg[field_output].get<std::string>(),
            std::ofstream::trunc);
        dst->sampling_interval = decltype(dst->sampling_interval)(
            cfg[field_sampling].get<sensor::microseconds_type>());
    }

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */


/*
 * visus::power_overwhelming::collector::for_all
 */
visus::power_overwhelming::collector
visus::power_overwhelming::collector::for_all(
        _In_ const collector_settings& settings) {
    auto retval = collector(new detail::collector_impl());
    retval._impl->apply(settings);
    retval._impl->sensors = detail::get_all_sensors();
    return retval;
}


/*
 * visus::power_overwhelming::collector::from_defaults
 */
visus::power_overwhelming::collector
visus::power_overwhelming::collector::from_defaults(void) {
    auto config = detail::make_json_template();
    auto retval = collector(new detail::collector_impl());
    detail::apply_template(retval._impl, config);
    return retval;
}


/*
 * visus::power_overwhelming::collector::from_json
 */
visus::power_overwhelming::collector
visus::power_overwhelming::collector::from_json(_In_z_ const wchar_t *path) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to the configuration file must "
            "not be null.");
    }

    auto retval = collector(new detail::collector_impl());
    detail::apply_template(retval._impl, detail::read_json(path));

    return retval;
}


/*
 * visus::power_overwhelming::collector::make_configuration_template
 */
void visus::power_overwhelming::collector::make_configuration_template(
        _In_z_ const wchar_t *path) {
    detail::write_json(path, detail::make_json_template());
}


/*
 * visus::power_overwhelming::collector::~collector
 */
visus::power_overwhelming::collector::~collector(void) {
    this->stop();
    delete this->_impl;
}


/*
 * visus::power_overwhelming::collector::marker
 */
void visus::power_overwhelming::collector::marker(
        _In_opt_z_ const wchar_t *marker) {
    if (this->_impl == nullptr) {
        throw std::runtime_error("The collector has been moved to another "
            "instance wherefore no marker can be set.");
    }

    this->_impl->marker(marker);
}


/*
 * visus::power_overwhelming::collector::size
 */
std::size_t visus::power_overwhelming::collector::size(void) const noexcept {
    return (this->_impl != nullptr) ? this->_impl->sensors.size() : 0;
}


/*
 * visus::power_overwhelming::collector::start
 */
void visus::power_overwhelming::collector::start(void) {
    if (this->_impl == nullptr) {
        throw std::runtime_error("The collector has been moved to another "
            "instance and therefore cannot be started.");
    }

    this->_impl->start();
}


/*
 * visus::power_overwhelming::collector::stop
 */
void visus::power_overwhelming::collector::stop(void) {
    if (this->_impl != nullptr) {
        this->_impl->stop();
    }
}


/*
 * visus::power_overwhelming::collector::operator =
 */
visus::power_overwhelming::collector&
visus::power_overwhelming::collector::operator =(
        _In_ collector&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::collector::operator bool
 */
visus::power_overwhelming::collector::operator bool(void) const noexcept {
    return (this->_impl != nullptr);
}


/*
 * visus::power_overwhelming::collector::prepare
 */
visus::power_overwhelming::collector
visus::power_overwhelming::collector::prepare(
        _In_ const collector_settings& settings,
        _In_ const std::size_t capacity) {
    auto retval = collector(new detail::collector_impl());
    retval._impl->sensors.reserve(capacity);
    retval._impl->apply(settings);
    return retval;
}


/*
 * visus::power_overwhelming::collector::add
 */
void visus::power_overwhelming::collector::add(_In_ sensor *sensor) {
    assert(*this);

    if (sensor == nullptr) {
        throw std::invalid_argument("None of the sensors added to a collector "
            "must be null.");
    }
    if (!*sensor) {
        throw std::invalid_argument("None of the sensors added to a collector "
            "must have been disposed.");
    }

    this->_impl->sensors.emplace_back(sensor);
}

