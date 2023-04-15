// <copyright file="sensor_desc.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "nlohmann/json.hpp"

#include "power_overwhelming/adl_sensor.h"
#include "power_overwhelming/emi_sensor.h"
#include "power_overwhelming/hmc8015_sensor.h"
#include "power_overwhelming/nvml_sensor.h"
#include "power_overwhelming/rtb_sensor.h"
#include "power_overwhelming/tinkerforge_sensor.h"


namespace visus {
namespace power_overwhelming {

namespace detail {

    static constexpr const char *json_field_channel = "channel";
    static constexpr const char *json_field_description = "description";
    static constexpr const char *json_field_dev_guid = "deviceGuid";
    static constexpr const char *json_field_host = "host";
    static constexpr const char *json_field_name = "name";
    static constexpr const char *json_field_output = "outputPath";
    static constexpr const char *json_field_path = "path";
    static constexpr const char *json_field_port = "port";
    static constexpr const char *json_field_require_marker
        = "collectRequiresMarker";
    static constexpr const char *json_field_sampling = "samplingInterval";
    static constexpr const char *json_field_sensors = "sensors";
    static constexpr const char *json_field_source = "source";
    static constexpr const char *json_field_timeout = "timeout";
    static constexpr const char *json_field_type = "type";
    static constexpr const char *json_field_udid = "udid";
    static constexpr const char *json_field_uid = "uid";


    /// <summary>
    /// Allows for deriving the type of a sensor from a descriptor instance.
    /// </summary>
    template<class> struct sensor_type;

    /// <summary>
    /// Specialisation for descriptors.
    /// </summary>
    template<class TSensor, template<class> class TDesc>
    struct sensor_type<TDesc<TSensor>> {
        typedef TSensor type;
    };


    /// <summary>
    /// Base class for sensor descriptors.
    /// </summary>
    template<class TDerived> struct sensor_desc_base {

        /// <summary>
        /// The type of the sensor described by
        /// <typeparamref name="TDerived" />.
        /// </summary>
        typedef typename sensor_type<TDerived>::type value_type;

        /// <summary>
        /// Answer whether the given JSON value describes a sensor described by
        /// <typeparamref name="TDerived" />.
        /// </summary>
        /// <typeparam name="TSensor"></typeparam>
        static inline bool describes(const nlohmann::json& value) {
            return (value[detail::json_field_type] == TDerived::type_name);
        }
    };


    /// <summary>
    /// A list to enumerate all known sensors at compile time.
    /// </summary>
    template<class...> struct sensor_list { };

} /* namespace detail */


    /// <summary>
    /// Provides compile-time metadata for a sensor of type
    /// <see cref="TSensor" />.
    /// </summary>
    /// <remarks>
    /// <para>Implementors of new kinds of sensors must provide a full template
    /// specialisation of this type that describes the new sensor.</para>
    /// <para>For convenience, implementors should inherit from
    /// <see cref="detail::sensor_desc_base" /> to provide the type of the
    /// sensor and the test for the type name automatically.</para>
    /// </remarks>
    /// <typeparam name="TSensor">The type of the sensor described by the
    /// template instance.</typeparam>
    template<class TSensor> struct sensor_desc final { };

    /// <summary>
    /// Specialisation for <see cref="adl_sensor" />.
    /// </summary>
    template<> struct sensor_desc<adl_sensor> final
            : detail::sensor_desc_base<sensor_desc<adl_sensor>> {
        static constexpr const char *type_name = "adl_sensor";

        static inline value_type deserialise(const nlohmann::json& value) {
            auto source = convert_string<wchar_t>(
                value[detail::json_field_source].get<std::string>());
            auto udid = value[detail::json_field_udid].get<std::string>();
            return value_type::from_udid(udid.c_str(),
                parse_adl_sensor_source(source.c_str()));
        }

        static inline nlohmann::json serialise(const value_type& value) {
            auto name = convert_string<char>(value.name());
            auto source = convert_string<char>(to_string(value.source()));

            return nlohmann::json::object({
                { detail::json_field_type, type_name },
                { detail::json_field_name, name },
                { detail::json_field_udid, value.udid() },
                { detail::json_field_source, source  }
            });
        }
    };

    /// <summary>
    /// Specialisation for <see cref="emi_sensor" />.
    /// </summary>
    template<> struct sensor_desc<emi_sensor> final
            : detail::sensor_desc_base<sensor_desc<emi_sensor>> {
        static constexpr const char *type_name = "emi_sensor";

        static inline value_type deserialise(const nlohmann::json& value) {
            throw "TODO: Not implemented yet";
        }

        static inline nlohmann::json serialise(const value_type& value) {
            auto channel = value.channel();
            auto name = convert_string<char>(value.name());
            auto path = convert_string<char>(value.path());

            return nlohmann::json::object({
                { detail::json_field_type, type_name },
                { detail::json_field_name, name },
                { detail::json_field_path, path },
                { detail::json_field_channel, channel }
            });
        }
    };

    /// <summary>
    /// Specialisation for <see cref="hmc8015_sensor" />.
    /// </summary>
    template<> struct sensor_desc<hmc8015_sensor> final
            : detail::sensor_desc_base<sensor_desc<hmc8015_sensor>> {
        static constexpr const char *type_name = "hmc8015_sensor";

        static inline value_type deserialise(const nlohmann::json& value) {
            auto path = value[detail::json_field_path].get<std::string>();
            auto timeout = value[detail::json_field_timeout].get<std::int32_t>();
            return value_type(path.c_str(), timeout);
        }

        static inline nlohmann::json serialise(const value_type& value) {
            auto name = convert_string<char>(value.name());
            auto path = convert_string<char>(value.path());

            return nlohmann::json::object({
                { detail::json_field_type, type_name },
                { detail::json_field_name, name },
                { detail::json_field_path, path },
                { detail::json_field_channel, 3000 }
            });
        }
    };

    /// <summary>
    /// Specialisation for <see cref="nvml_sensor" />.
    /// </summary>
    template<> struct sensor_desc<nvml_sensor> final
            : detail::sensor_desc_base<sensor_desc<nvml_sensor>> {
        static constexpr const char *type_name = "nvml_sensor";

        static inline value_type deserialise(const nlohmann::json& value) {
            auto guid = value[detail::json_field_dev_guid].get<std::string>();
            return value_type::from_guid(guid.c_str());
        }

        static inline nlohmann::json serialise(const value_type& value) {
            auto guid = value.device_guid();
            auto name = convert_string<char>(value.name());

            return nlohmann::json::object({
                { detail::json_field_type, type_name },
                { detail::json_field_name, name },
                { detail::json_field_dev_guid, guid }
            });
        }
    };

    /// <summary>
    /// Specialisation for <see cref="rtb_sensor" />.
    /// </summary>
    template<> struct sensor_desc<rtb_sensor> final
            : detail::sensor_desc_base<sensor_desc<rtb_sensor>> {
        static constexpr const char *type_name = "rtb_sensor";

        static inline value_type deserialise(const nlohmann::json& value) {
            auto path = value[detail::json_field_path].get<std::string>();
            auto timeout = value[detail::json_field_timeout].get<std::int32_t>();
            return value_type(path.c_str(), timeout);
        }

        static inline nlohmann::json serialise(const value_type& value) {
            auto name = convert_string<char>(value.name());
            auto path = convert_string<char>(value.path());

            return nlohmann::json::object({
                { detail::json_field_type, type_name },
                { detail::json_field_name, name },
                { detail::json_field_path, path },
                { detail::json_field_channel, 3000 }
            });
        }
    };

    /// <summary>
    /// Specialisation for <see cref="tinkerforge_sensor" />.
    /// </summary>
    template<> struct sensor_desc<tinkerforge_sensor> final
            : detail::sensor_desc_base<sensor_desc<tinkerforge_sensor>> {
        static constexpr const char *type_name = "tinkerforge_sensor";

        static inline value_type deserialise(const nlohmann::json& value) {
            const auto dit = value.find(detail::json_field_description);
            const auto hit = value.find(detail::json_field_host);
            const auto pit = value.find(detail::json_field_port);

            auto host = (hit != value.end())
                ? hit->get<std::string>()
                : value_type::default_host;
            auto port = (pit != value.end())
                ? pit->get<std::uint16_t>()
                : value_type::default_port;
            auto uid = value[detail::json_field_uid].get<std::string>();

            if (dit != value.end()) {
                auto desc = convert_string<wchar_t>(dit->get<std::string>());
                return value_type(uid.c_str(), desc.c_str(), host.c_str(),
                    port);
            } else {
                return value_type(uid.c_str(), host.c_str(), port);
            }
        }

        static inline nlohmann::json serialise(const value_type& value) {
            throw "TODO: extract host, port, uid from sensor requires new API";
            auto desc = convert_string<char>(value.description());
            auto host = tinkerforge_sensor::default_host;
            auto name = convert_string<char>(value.name());
            auto port = tinkerforge_sensor::default_port;
            auto source = convert_string<char>(to_string(
                tinkerforge_sensor_source::all));

            return nlohmann::json::object({
                { detail::json_field_type, type_name },
                { detail::json_field_name, name },
                { detail::json_field_host, host },
                { detail::json_field_port, port },
                //{ detail::json_field_uid, d.uid() },
                { detail::json_field_description, desc },
                { detail::json_field_source, source }
            });
        }
    };


    /// <summary>
    /// A type list of all known sensors, which allows for compile-time
    /// enumeration of known sensor types.
    /// </summary>
    typedef detail::sensor_list<
        adl_sensor,
        emi_sensor,
        hmc8015_sensor,
        nvml_sensor,
        rtb_sensor,
        tinkerforge_sensor>
        sensor_list;

} /* namespace power_overwhelming */
} /* namespace visus */
