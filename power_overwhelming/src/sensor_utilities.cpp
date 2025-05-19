// <copyright file="sensor_utilities.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "sensor_utilities.h"

#include <stdexcept>

#include "sensor_array_configuration_impl.h"
#include "sensor_array_impl.h"

//#include <cassert>
//#include <fstream>
//#include <type_traits>
//
//#include "visus/pwrowg/convert_string.h"
//
//#include "sensor_desc.h"
//
//
//namespace visus {
//namespace power_overwhelming {
//namespace detail {
//
//    /// <summary>
//    /// Retrieve JSON descriptors for all sensors if the descriptor class
//    /// implements serialisation at once.
//    /// </summary>
//    template<class TSensor>
//    typename std::enable_if<
//        has_serialise_all<sensor_desc<TSensor>>::value>::type
//    add_descs_of(nlohmann::json& dst) {
//        auto descs = sensor_desc<TSensor>::serialise_all();
//        dst.insert(dst.end(), descs.begin(), descs.end());
//    }
//
//    /// <summary>
//    /// Retrieve JSON descriptors for all sensors if the descriptor class
//    /// does not implement a one-step serialisation.
//    /// </summary>
//    template<class TSensor>
//    typename std::enable_if<
//        !has_serialise_all<sensor_desc<TSensor>>::value>::type
//    add_descs_of(nlohmann::json& dst) {
//        auto sensors = get_all_sensors_of<TSensor>();
//        for (auto& s : sensors) {
//            dst.push_back(sensor_desc<TSensor>::serialise(s));
//        }
//    }
//
//    /// <summary>
//    /// Add descriptors for all sensors of the specified types to the given
//    /// list of sensors.
//    /// </summary>
//    template<class TSensor, class... TSensors>
//    void add_descs(nlohmann::json& dst,
//            sensor_list_type<TSensor, TSensors ...>) {
//        add_descs(dst, sensor_list_type<TSensor>());
//        add_descs(dst, sensor_list_type<TSensors ...>());
//    }
//
//    /// <summary>
//    /// Recursion stop for <see cref="add_descs" />.
//    /// </summary>
//    template<class TSensor>
//    inline void add_descs(nlohmann::json& dst, sensor_list_type<TSensor>) {
//        try {
//            add_descs_of<TSensor>(dst);
//        } catch (...) { /* Ignore any failing sensor. */ }
//    }
//
//    /// <summary>
//    /// Add all sensors of the specified types to the given list of sensors.
//    /// </summary>
//    template<class TSensor, class... TSensors>
//    void add_sensors(std::vector<std::unique_ptr<sensor>>& dst,
//            sensor_list_type<TSensor, TSensors ...>) {
//        add_sensors(dst, sensor_list_type<TSensor>());
//        add_sensors(dst, sensor_list_type<TSensors ...>());
//    }
//
//    /// <summary>
//    /// Recursion stop for <see cref="add_sensors" />.
//    /// </summary>
//    template<class TSensor>
//    inline void add_sensors(std::vector<std::unique_ptr<sensor>>& dst,
//            sensor_list_type<TSensor>) {
//        try {
//            move_sensors(dst, get_all_sensors_of<TSensor>());
//        } catch (...) { /* Ignore any failing sensor. */ }
//    }
//
//
//    /// <summary>
//    /// Check whether the given JSON can be parsed as sensor definition and
//    /// if so, create the sensor defined therein.
//    /// </summary>
//    template<class TSensor, class... TSensors>
//    std::unique_ptr<sensor> parse_sensor(const nlohmann::json& desc,
//            sensor_list_type<TSensor, TSensors ...>) {
//        if (sensor_desc<TSensor>::describes(desc)) {
//            return std::unique_ptr<sensor>(new TSensor(
//                sensor_desc<TSensor>::deserialise(desc)));
//
//        } else {
//            // Try the rest of the sensor list.
//            return parse_sensor(desc, sensor_list_type<TSensors ...>());
//        }
//    }
//
//    /// <summary>
//    /// Recursion stop for <see cref="parse_sensor" />.
//    /// </summary>
//    inline std::unique_ptr<sensor> parse_sensor(const nlohmann::json& desc,
//            sensor_list_type<>) {
//        throw std::invalid_argument("An unknown type of sensor was specified.");
//    }
//
//} /* namespace detail */
//} /* namespace power_overwhelming */
//} /* namespace visus */
//
//
///*
// * visus::power_overwhelming::detail::get_all_sensor_descs
// */
//nlohmann::json visus::power_overwhelming::detail::get_all_sensor_descs(void) {
//    auto retval = nlohmann::json::array();
//    add_descs(retval, sensor_list());
//    return retval;
//}
//
//
///*
// * visus::power_overwhelming::detail::get_all_sensors
// */
//std::vector<std::unique_ptr<visus::power_overwhelming::sensor>>
//visus::power_overwhelming::detail::get_all_sensors(void) {
//    std::vector<std::unique_ptr<sensor>> retval;
//    add_sensors(retval, sensor_list());
//    return retval;
//}
//
//
//
///*
// * visus::power_overwhelming::detail::parse_sensors
// */
//std::vector<std::unique_ptr<visus::power_overwhelming::sensor>>
//visus::power_overwhelming::detail::parse_sensors(const nlohmann::json& descs) {
//    std::vector<std::unique_ptr<sensor>> retval;
//
//    if (descs.type() == nlohmann::json::value_t::array) {
//        retval.reserve(descs.size());
//        for (auto& s : descs) {
//            retval.emplace_back(detail::parse_sensor(s, sensor_list()));
//        }
//
//    } else if (descs.type() == nlohmann::json::value_t::object) {
//        retval.emplace_back(detail::parse_sensor(descs, sensor_list()));
//    }
//
//    return retval;
//}
//
//
///*
// * visus::power_overwhelming::detail::read_json
// */
//nlohmann::json visus::power_overwhelming::detail::read_json(const char *path) {
//    std::ifstream s;
//    s.exceptions(s.exceptions() | std::ios::failbit | std::ios::badbit);
//    s.open(path);
//    nlohmann::json retval;
//    s >> retval;
//    return retval;
//}
//
//
///*
// * visus::power_overwhelming::detail::read_json
// */
//nlohmann::json visus::power_overwhelming::detail::read_json(
//        const wchar_t *path) {
//    std::ifstream s;
//    s.exceptions(s.exceptions() | std::ios::failbit | std::ios::badbit);
//
//#if defined(_WIN32)
//    s.open(path);
//#else /* defined(_WIN32) */
//    auto p = power_overwhelming::convert_string<char>(path);
//    s.open(p);
//#endif /* defined(_WIN32) */
//
//    nlohmann::json retval;
//    s >> retval;
//
//    return retval;
//}
//
//
///*
// * visus::power_overwhelming::detail::write_json
// */
//void visus::power_overwhelming::detail::write_json(const char *path,
//        const nlohmann::json& json) {
//    std::ofstream s;
//    s.exceptions(s.exceptions() | std::ios::failbit | std::ios::badbit);
//    s.open(path, std::ofstream::out | std::ofstream::trunc);
//    s << json.dump(4);
//    s.flush();
//}
//
//
///*
// * visus::power_overwhelming::detail::write_json
// */
//void visus::power_overwhelming::detail::write_json(const wchar_t *path,
//        const nlohmann::json& json) {
//    std::ofstream s;
//    s.exceptions(s.exceptions() | std::ios::failbit | std::ios::badbit);
//
//#if defined(_WIN32)
//    s.open(path, std::ofstream::out | std::ofstream::trunc);
//#else /* defined(_WIN32) */
//    auto p = power_overwhelming::convert_string<char>(path);
//    s.open(p, std::ofstream::out | std::ofstream::trunc);
//#endif /* defined(_WIN32) */
//
//    s << json.dump(4);
//    s.flush();
//}


/*
 * PWROWG_NAMESPACE::get_sampling_interval
 */
std::chrono::milliseconds PWROWG_DETAIL_NAMESPACE::get_sampling_interval(
        _In_ const sensor_array_configuration_impl& config) noexcept {
    return config.interval;
}


/*
 * PWROWG_NAMESPACE::get_sampling_interval
 */
std::chrono::milliseconds PWROWG_DETAIL_NAMESPACE::get_sampling_interval(
        _In_ const sensor_array_impl& sensors) {
    if (sensors.configuration == nullptr) {
        throw std::invalid_argument("A sensor array with a valid configuration "
            "must be used to obtain the sampling rate.");
    }

    return get_sampling_interval(*sensors.configuration);
}


/*
 * PWROWG_DETAIL_NAMESPACE::pwr_volt_cur_mask
 */
PWROWG_NAMESPACE::sensor_type PWROWG_DETAIL_NAMESPACE::pwr_volt_cur_mask(
        _In_ const sensor_description &desc) {
    const auto mask = sensor_type::power
        | sensor_type::voltage
        | sensor_type::current;
    return (desc.sensor_type() & mask);
}
