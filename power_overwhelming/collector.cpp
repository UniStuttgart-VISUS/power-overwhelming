// <copyright file="collector.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2022 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#include "power_overwhelming/collector.h"

#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>

#include <nlohmann/json.hpp>

#include "power_overwhelming/convert_string.h"

#include "collector_impl.h"
#include "tinkerforge_sensor_impl.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    static constexpr const char *field_dev_guid = "deviceGuid";
    static constexpr const char *field_host = "host";
    static constexpr const char *field_name = "name";
    static constexpr const char *field_output = "outputPath";
    static constexpr const char *field_path = "path";
    static constexpr const char *field_port = "port";
    static constexpr const char *field_sampling = "samplingInterval";
    static constexpr const char *field_sensors = "sensors";
    static constexpr const char *field_source = "source";
    static constexpr const char *field_timeout = "timeout";
    static constexpr const char *field_type = "type";
    static constexpr const char *field_udid = "udid";
    static constexpr const char *field_uid = "uid";

    /// <summary>
    /// Create an in-memory JSON document with the template for configuring the
    /// sensors on the machine the software is running on.
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static nlohmann::json make_json_template(void) {
        using power_overwhelming::convert_string;

        nlohmann::json retval;

        retval[field_output] = "output.csv";
        retval[field_sampling] = 1000;
        auto& sensor_list = retval[field_sensors] = nlohmann::json::array();

        // Get all ADL sensors.
        try {
            std::vector<adl_sensor> sensors;
            sensors.resize(adl_sensor::for_all(nullptr, 0));
            adl_sensor::for_all(sensors.data(), sensors.size());

            for (auto& s : sensors) {
                sensor_list.push_back({
                    { field_type, "adl_sensor" },
                    { field_name, convert_string<char>(s.name()) },
                    { field_udid, s.udid() },
                    { field_source, convert_string<char>(to_string(adl_sensor_source::asic)) }  // TODO: write the real thing.
                });
            }
        } catch (...) { /* Just ignore the sensor. */ }

        // Get all R&S HMC8015 sensors.
        try {
            std::vector<hmc8015_sensor> sensors;
            sensors.resize(hmc8015_sensor::for_all(nullptr, 0));
            hmc8015_sensor::for_all(sensors.data(), sensors.size());

            for (auto& s : sensors) {
                sensor_list.push_back({
                    { field_type, "hmc8015_sensor" },
                    { field_name, convert_string<char>(s.name()) },
                    { field_path, s.path() },
                    { field_timeout, 3000 },
                });
            }
        } catch (...) { /* Just ignore the sensor. */ }

        // Get all NVML sensors.
        try {
            std::vector<nvml_sensor> sensors;
            sensors.resize(nvml_sensor::for_all(nullptr, 0));
            nvml_sensor::for_all(sensors.data(), sensors.size());

            for (auto& s : sensors) {
                sensor_list.push_back({
                    { field_type, "nvml_sensor" },
                    { field_name, convert_string<char>(s.name()) },
                    { field_dev_guid, s.device_guid() },
                });
            }
        } catch (...) { /* Just ignore the sensor. */ }

        // Get all R&S RTBxxxx sensors.
        try {
            std::vector<rtb_sensor> sensors;
            sensors.resize(rtb_sensor::for_all(nullptr, 0));
            rtb_sensor::for_all(sensors.data(), sensors.size());

            for (auto& s : sensors) {
                sensor_list.push_back({
                    { field_type, "rtb_sensor" },
                    { field_name, convert_string<char>(s.name()) },
                    { field_path, s.path() },
                    { field_timeout, 3000 }
                });
            }
        } catch (...) { /* Just ignore the sensor. */ }

        // Get all Tinkerforge sensors.
        try {
            std::vector<tinkerforge_sensor_definiton> descs;
            descs.resize(tinkerforge_sensor::get_definitions(nullptr, 0));
            auto cnt = tinkerforge_sensor::get_definitions(descs.data(),
                descs.size());

            const auto host = tinkerforge_sensor::default_host;
            const auto port = tinkerforge_sensor::default_port;

            for (auto& d : descs) {
                assert(d.uid() != nullptr);
                // We do not need to create the sensor to write its properties, the
                // definition and the API for the sensor name suffice.
                auto name = detail::tinkerforge_sensor_impl::get_sensor_name(
                    host, port, d.uid());

                sensor_list.push_back({
                    { field_type, "tinkerforge_sensor" },
                    { field_name, name },
                    { field_host, host },
                    { field_port, port },
                    { field_uid, d.uid() },
                });
            }
        } catch (...) { /* Just ignore the sensor. */ }

        return retval;
    }

    /// <summary>
    /// Apply the given JSON configuration to the given collector.
    /// </summary>
    /// <param name="dst"></param>
    /// <param name="cfg"></param>
    static void apply_template(collector_impl *dst, const nlohmann::json& cfg) {
        assert(dst != nullptr);
        auto& sensor_list = cfg[field_sensors];

        for (auto& s : sensor_list) {
            if (s[field_type] == "adl_sensor") {
                auto udid = s[field_udid].get<std::string>();
                auto sensor = adl_sensor::from_udid(udid.c_str(),
                    adl_sensor_source::asic);   // TODO: allow different types.
                dst->sensors.emplace_back(new adl_sensor(std::move(sensor)));

            } else if (s[field_type] == "hmc8015_sensor") {
                auto path = s[field_path].get<std::string>();
                auto timeout = s[field_timeout].get<std::int32_t>();
                hmc8015_sensor sensor(path.c_str(), timeout);
                dst->sensors.emplace_back(
                    new hmc8015_sensor(std::move(sensor)));

            } else if (s[field_type] == "nvml_sensor") {
                auto guid = s[field_dev_guid].get<std::string>();
                auto sensor = nvml_sensor::from_guid(guid.c_str());
                dst->sensors.emplace_back(
                    new nvml_sensor(std::move(sensor)));

            } else if (s[field_type] == "rtb_sensor") {
                auto path = s[field_path].get<std::string>();
                auto timeout = s[field_timeout].get<std::int32_t>();
                rtb_sensor sensor(path.c_str(), timeout);
                dst->sensors.emplace_back(
                    new rtb_sensor(std::move(sensor)));

            } else if (s[field_type] == "tinkerforge_sensor") {
                auto host = s[field_host].get<std::string>();
                auto port = s[field_port].get<std::uint16_t>();
                auto uid = s[field_uid].get<std::string>();
                tinkerforge_sensor sensor(uid.c_str(), host.c_str(), port);
                dst->sensors.emplace_back(
                    new tinkerforge_sensor(std::move(sensor)));

            } else {
                throw std::invalid_argument("An unknown type of sensor was "
                    "specified.");
            }
        }

        // If we have the sensors, create the output file and store the rest of the
        // properties.
        dst->stream = std::ofstream(cfg[field_output].get<std::string>(),
            std::ofstream::trunc);
        dst->sampling_interval
            = cfg[field_sampling].get<sensor::microseconds_type>();
    }

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */


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
visus::power_overwhelming::collector::from_json(const wchar_t *path) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to the configuration file must "
            "not be null.");
    }

    // Read the JSON configuration file into memory.
    nlohmann::json config;
    std::ifstream stream(path);
    stream >> config;

    auto retval = collector(new detail::collector_impl());

    // Apply the configuration.
    detail::apply_template(retval._impl, config);

    return retval;
}


/*
 * visus::power_overwhelming::collector::make_configuration_template
 */
void visus::power_overwhelming::collector::make_configuration_template(
        const wchar_t *path) {
    auto json = detail::make_json_template();

    std::ofstream stream(path, std::ofstream::out | std::ofstream::trunc);
    stream << json.dump(4);
}


/*
 * visus::power_overwhelming::collector::~collector
 */
visus::power_overwhelming::collector::~collector(void) {
    this->stop();
    delete this->_impl;
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

    for (auto& s : this->_impl->sensors) {
        // TODO: async is not yet part of the interface.
    }
}


/*
 * visus::power_overwhelming::collector::stop
 */
void visus::power_overwhelming::collector::stop(void) {
    if (this->_impl != nullptr) {
        // TODO: async is not yet part of the interface.
    }
}


/*
 * visus::power_overwhelming::collector::operator =
 */
visus::power_overwhelming::collector&
visus::power_overwhelming::collector::operator =(collector&& rhs) noexcept {
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
