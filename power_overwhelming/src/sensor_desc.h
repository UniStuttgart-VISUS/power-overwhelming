//// <copyright file="sensor_desc.h" company="Visualisierungsinstitut der Universität Stuttgart">
//// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
//// Licensed under the MIT licence. See LICENCE file for details.
//// </copyright>
//// <author>Christoph Müller</author>
//
//#pragma once
//
//#include <type_traits>
//
//#include "nlohmann/json.hpp"
//
//#include "visus/pwrowg/adl_sensor.h"
//#include "visus/pwrowg/emi_sensor.h"
//#include "visus/pwrowg/hmc8015_sensor.h"
//#include "visus/pwrowg/msr_sensor.h"
//#include "visus/pwrowg/nvml_sensor.h"
//#include "visus/pwrowg/regex_escape.h"
//#include "visus/pwrowg/rtx_sensor.h"
//#include "visus/pwrowg/tinkerforge_sensor.h"
//
//#include "described_sensor_type.h"
//#include "msr_sensor_impl.h"
//#include "rtx_serialisation.h"
//#include "tinkerforge_sensor_impl.h"
//
//
///// <summary>
///// Declares the static constant <c>type_name</c> for the sensor with the
///// given name.
///// </summary>
//#define POWER_OVERWHELMING_DECLARE_SENSOR_NAME(name)\
//    static constexpr const char *type_name = #name
//
///// <summary>
///// Declares the static constant <c>intrinsic_async</c> specifying whether a
///// sensor is intrinsically asynchronous and should not be sampled by polling if
///// used in a <see cref="visus::power_overwhelming::collector" />.
///// </summary>
//#define POWER_OVERWHELMING_DECLARE_INTRINSIC_ASYNC(value)\
//    static constexpr bool intrinsic_async = (value)
//
//
//namespace visus {
//namespace power_overwhelming {
//namespace detail {
//
//    static constexpr const char *json_field_channel = "channel";
//    static constexpr const char *json_field_channel_current = "current";
//    static constexpr const char *json_field_channel_voltage = "voltage";
//    static constexpr const char *json_field_core = "core";
//    static constexpr const char *json_field_decimation = "decimation";
//    static constexpr const char *json_field_description = "description";
//    static constexpr const char *json_field_dev_guid = "deviceGuid";
//    static constexpr const char *json_field_domain = "domain"; 
//    static constexpr const char *json_field_host = "host";
//    static constexpr const char *json_field_instrument = "instrument";
//    static constexpr const char *json_field_name = "name";
//    static constexpr const char *json_field_offset = "offset";
//    static constexpr const char *json_field_path = "path";
//    static constexpr const char *json_field_port = "port";
//    static constexpr const char *json_field_source = "source";
//    static constexpr const char *json_field_timeout = "timeout";
//    static constexpr const char *json_field_type = "type";
//    static constexpr const char *json_field_udid = "udid";
//    static constexpr const char *json_field_uid = "uid";
//    static constexpr const char *json_field_unit_divisor = "unitDivisor";
//
//    /// <summary>
//    /// Test whether a descriptor has the ability to serialise all sensors at
//    /// once.
//    /// </summary>
//    template<class TDesc> class has_serialise_all final {
//
//    private:
//
//        template<class T>
//        static std::uint16_t test(decltype(T::serialise_all()) *);
//
//        template<class T>
//        static std::uint8_t test(...);
//
//    public:
//
//        static constexpr bool value = (sizeof(decltype(test<TDesc>(nullptr)))
//            == sizeof(std::uint16_t));
//    };
//
//
//    /// <summary>
//    /// Base class for sensor descriptors.
//    /// </summary>
//    template<class TDerived> struct sensor_desc_base {
//
//        /// <summary>
//        /// The type of the sensor described by
//        /// <typeparamref name="TDerived" />.
//        /// </summary>
//        typedef typename described_sensor_type<TDerived>::type value_type;
//
//        /// <summary>
//        /// Answer whether the given JSON value describes a sensor described by
//        /// <typeparamref name="TDerived" />.
//        /// </summary>
//        static inline bool describes(const nlohmann::json& value) {
//            return (value[detail::json_field_type] == TDerived::type_name);
//        }
//
//    };
//
//
//    /// <summary>
//    /// Type of a list to enumerate all known sensors at compile time,
//    /// which is declared at the end of this file.
//    /// </summary>
//    template<class...> struct sensor_list_type final { };
//
//
//    /// <summary>
//    /// Provides compile-time metadata for a sensor of type
//    /// <see cref="TSensor" />.
//    /// </summary>
//    /// <remarks>
//    /// <para>Implementors of new kinds of sensors must provide a full template
//    /// specialisation of this type that describes the new sensor.</para>
//    /// <para>For convenience, implementors should inherit from
//    /// <see cref="detail::sensor_desc_base" /> to provide the type of the
//    /// sensor and the test for the type name automatically.</para>
//    /// </remarks>
//    /// <typeparam name="TSensor">The type of the sensor described by the
//    /// template instance.</typeparam>
//    template<class TSensor> struct sensor_desc final { };
//
//    /// <summary>
//    /// Specialisation for <see cref="adl_sensor" />.
//    /// </summary>
//    template<> struct sensor_desc<adl_sensor> final
//            : detail::sensor_desc_base<sensor_desc<adl_sensor>> {
//        POWER_OVERWHELMING_DECLARE_SENSOR_NAME(adl_sensor);
//        POWER_OVERWHELMING_DECLARE_INTRINSIC_ASYNC(false);
//
//        static inline value_type deserialise(const nlohmann::json& value) {
//            auto source0 = value[json_field_source].get<std::string>();
//            auto source = power_overwhelming::convert_string<wchar_t>(source0);
//            auto udid = value[json_field_udid].get<std::string>();
//            return value_type::from_udid(udid.c_str(),
//                parse_adl_sensor_source(source.c_str()));
//        }
//
//        static inline nlohmann::json serialise(const value_type& value) {
//            return nlohmann::json::object({
//                json_serialise(json_field_type, type_name),
//                json_serialise(json_field_name, value.name()),
//                json_serialise(json_field_udid, value.udid()),
//                json_serialise(json_field_source, to_string(value.source()))
//            });
//        }
//    };
//
//    /// <summary>
//    /// Specialisation for <see cref="emi_sensor" />.
//    /// </summary>
//    template<> struct sensor_desc<emi_sensor> final
//            : detail::sensor_desc_base<sensor_desc<emi_sensor>> {
//        POWER_OVERWHELMING_DECLARE_SENSOR_NAME(emi_sensor);
//        POWER_OVERWHELMING_DECLARE_INTRINSIC_ASYNC(false);
//
//        static inline value_type deserialise(const nlohmann::json& value) {
//#if defined(_WIN32)
//            auto channel = value[json_field_channel]
//                .get<emi_sensor::channel_type>();
//            auto path0 = value[json_field_path].get<std::string>();
//            auto path = power_overwhelming::convert_string<wchar_t>(path0);
//
//            std::size_t cnt = 0;
//            value_type retval;
//
//            try {
//                cnt = value_type::for_device_and_channel(&retval, 1,
//                    path.c_str(), channel);
//            } catch (std::regex_error) {
//                // Second chance: User might have specified a literal name,
//                // which is usually not a valid regular expression, so we
//                // escape it now and retry.
//                path = power_overwhelming::regex_escape(path);
//                cnt = value_type::for_device_and_channel(&retval, 1,
//                    path.c_str(), channel);
//            }
//
//            if (cnt == 0) {
//                throw std::invalid_argument("The specified EMI device and "
//                    "channel are not available on this machine.");
//            } else if (cnt > 1) {
//                throw std::invalid_argument("The specified EMI device and "
//                    "channel are ambiguous.");
//            }
//
//            return retval;
//#else /* defined(_WIN32) */
//            throw std::logic_error("The Energy Meter Interface is not "
//                "available on this platform.");
//#endif /* defined(_WIN32) */
//        }
//
//        static inline nlohmann::json serialise(const value_type& value) {
//            return nlohmann::json::object({
//                json_serialise(json_field_type, type_name),
//                json_serialise(json_field_name, value.name()),
//                json_serialise(json_field_path, value.path()),
//                json_serialise(json_field_channel, value.channel())
//            });
//        }
//    };
//
//    /// <summary>
//    /// Specialisation for <see cref="hmc8015_sensor" />.
//    /// </summary>
//    template<> struct sensor_desc<hmc8015_sensor> final
//            : detail::sensor_desc_base<sensor_desc<hmc8015_sensor>> {
//        POWER_OVERWHELMING_DECLARE_SENSOR_NAME(hmc8015_sensor);
//        POWER_OVERWHELMING_DECLARE_INTRINSIC_ASYNC(false);
//
//        static inline value_type deserialise(const nlohmann::json& value) {
//            auto path = value[json_field_path].get<std::string>();
//            auto timeout = value[json_field_timeout].get<std::int32_t>();
//            return value_type(path.c_str(), timeout);
//        }
//
//        static inline nlohmann::json serialise(const value_type& value) {
//            return nlohmann::json::object({
//                json_serialise(json_field_type, type_name),
//                json_serialise(json_field_name, value.name()),
//                json_serialise(json_field_path, value.path()),
//                json_serialise(json_field_channel, 3000)
//            });
//        }
//    };
//
//    /// <summary>
//    /// Specialisation for <see cref="msr_sensor" />.
//    /// </summary>
//    template<> struct sensor_desc<msr_sensor> final
//            : detail::sensor_desc_base<sensor_desc<msr_sensor>> {
//        POWER_OVERWHELMING_DECLARE_SENSOR_NAME(msr_sensor);
//        POWER_OVERWHELMING_DECLARE_INTRINSIC_ASYNC(false);
//
//        static inline value_type deserialise(_In_ const nlohmann::json& value) {
//            auto core = value[json_field_core].get<msr_sensor::core_type>();
//            auto divisor = value[json_field_unit_divisor].get<float>();
//            auto domain0 = value[json_field_domain].get<std::string>();
//            auto domain1 = power_overwhelming::convert_string<wchar_t>(domain0);
//            auto domain = parse_rapl_domain(domain1.c_str());
//            auto offset = value[json_field_offset].get<std::streamoff>();
//            // Create using BS values for offset ...
//            auto retval = value_type::force_create(core, domain, offset, 0, 0,
//                0);
//            // ... and overwrite with result from previous offset computation.
//            retval._impl->unit_divisor = divisor;
//            return retval;
//        }
//
//        static inline nlohmann::json serialise(_In_ const value_type& value) {
//            return nlohmann::json::object({
//                json_serialise(json_field_type, type_name),
//                json_serialise(json_field_name, value.name()),
//                json_serialise(json_field_core, value.core()),
//                json_serialise(json_field_domain, to_string(value.domain())),
//                json_serialise(json_field_offset, value._impl->offset),
//                json_serialise(json_field_unit_divisor,
//                    value._impl->unit_divisor)
//            });
//        }
//    };
//
//    /// <summary>
//    /// Specialisation for <see cref="nvml_sensor" />.
//    /// </summary>
//    template<> struct sensor_desc<nvml_sensor> final
//            : detail::sensor_desc_base<sensor_desc<nvml_sensor>> {
//        POWER_OVERWHELMING_DECLARE_SENSOR_NAME(nvml_sensor);
//        POWER_OVERWHELMING_DECLARE_INTRINSIC_ASYNC(false);
//
//        static inline value_type deserialise(const nlohmann::json& value) {
//            auto guid = value[json_field_dev_guid].get<std::string>();
//            return value_type::from_guid(guid.c_str());
//        }
//
//        static inline nlohmann::json serialise(const value_type& value) {
//            return nlohmann::json::object({
//                json_serialise(json_field_type, type_name),
//                json_serialise(json_field_name, value.name()),
//                json_serialise(json_field_dev_guid, value.device_guid())
//            });
//        }
//    };
//
//    /// <summary>
//    /// Specialisation for <see cref="rtx_sensor" />.
//    /// </summary>
//    template<> struct sensor_desc<rtx_sensor> final
//            : detail::sensor_desc_base<sensor_desc<rtx_sensor>> {
//        POWER_OVERWHELMING_DECLARE_SENSOR_NAME(rtx_sensor);
//        POWER_OVERWHELMING_DECLARE_INTRINSIC_ASYNC(false);
//
//        static inline value_type deserialise(const nlohmann::json& value) {
//            auto channel_current = json_deserialise<rtx_channel>(
//                value[json_field_channel_current]);
//            auto channel_voltage = json_deserialise<rtx_channel>(
//                value[json_field_channel_voltage]);
//            auto decimation = json_deserialise<waveform_decimation_method>(
//                value[json_field_decimation]);
//            auto instrument_config = json_deserialise<
//                rtx_instrument_configuration>(value[json_field_instrument]);
//            auto path = json_deserialise<std::string>(value[json_field_path]);
//
//            rtx_sensor_definition definition(path.c_str(),
//                channel_voltage,
//                channel_current);
//
//            return value_type(definition,
//                decimation,
//                instrument_config.timeout(),
//                &instrument_config);
//        }
//
//        static inline nlohmann::json serialise(const value_type& value) {
//            auto instrument = value.instrument();
//            auto channel_current = instrument->channel(value.channel_current());
//            auto channel_voltage = instrument->channel(value.channel_voltage());
//            rtx_instrument_configuration instrument_config(*instrument);
//
//            return nlohmann::json::object({
//                json_serialise(json_field_type, type_name),
//                json_serialise(json_field_name, value.name()),
//                json_serialise(json_field_path, value.path()),
//                json_serialise(json_field_channel_current, channel_current),
//                json_serialise(json_field_channel_voltage, channel_voltage),
//                json_serialise(json_field_decimation, value.decimation_method()),
//                { json_field_instrument, json_serialise(instrument_config) }
//            });
//        }
//    };
//
//    /// <summary>
//    /// Specialisation for <see cref="tinkerforge_sensor" />.
//    /// </summary>
//    template<> struct sensor_desc<tinkerforge_sensor> final
//            : detail::sensor_desc_base<sensor_desc<tinkerforge_sensor>> {
//        POWER_OVERWHELMING_DECLARE_SENSOR_NAME(tinkerforge_sensor);
//        POWER_OVERWHELMING_DECLARE_INTRINSIC_ASYNC(true);
//
//        static inline value_type deserialise(const nlohmann::json& value) {
//            const auto dit = value.find(json_field_description);
//            const auto hit = value.find(json_field_host);
//            const auto pit = value.find(json_field_port);
//
//            auto host = (hit != value.end())
//                ? hit->get<std::string>()
//                : value_type::default_host;
//            auto port = (pit != value.end())
//                ? pit->get<std::uint16_t>()
//                : value_type::default_port;
//            auto uid = value[json_field_uid].get<std::string>();
//
//            if (dit != value.end()) {
//                auto desc0 = dit->get<std::string>();
//                auto desc = power_overwhelming::convert_string<wchar_t>(desc0);
//                return value_type(uid.c_str(), desc.c_str(), host.c_str(),
//                    port);
//            } else {
//                return value_type(uid.c_str(), host.c_str(), port);
//            }
//        }
//
//        static inline nlohmann::json serialise(const value_type& value) {
//            char uid[8];
//            value.identify(uid);
//
//            json_serialiser<char(&)[8]>::serialise(uid);
//
//            return nlohmann::json::object({
//                json_serialise(json_field_type, type_name),
//                json_serialise(json_field_name, value.name()),
//                json_serialise(json_field_host, value_type::default_host),
//                json_serialise(json_field_port, value_type::default_port),
//                json_serialise(json_field_uid, uid),
//                json_serialise(json_field_description, value.description()),
//                // TODO: Provide an API that allows for retrieving the callbacks enabled from the sensor.
//                json_serialise(json_field_source, to_string(
//                    tinkerforge_sensor_source::all))
//            });
//        }
//
//        static inline nlohmann::json serialise_all(void) {
//            auto retval = nlohmann::json::array();
//
//            const auto source = power_overwhelming::convert_string<char>(
//                to_string(tinkerforge_sensor_source::all));
//
//            // We do not need to create the sensor to write its properties,
//            // the definition and the API for the sensor name suffice.
//            std::vector<tinkerforge_sensor_definition> descs;
//            descs.resize(tinkerforge_sensor::get_definitions(nullptr, 0));
//            const auto cnt = tinkerforge_sensor::get_definitions(descs.data(),
//                descs.size());
//
//            for (auto& d : descs) {
//                const auto uid = d.uid();
//                assert(uid != nullptr);
//                _Analysis_assume_(uid != nullptr);
//                auto name = tinkerforge_sensor_impl::get_sensor_name(
//                    value_type::default_host, value_type::default_port, uid);
//
//                retval.push_back({
//                    json_serialise(json_field_type, type_name),
//                    json_serialise(json_field_name, name),
//                    json_serialise(json_field_host, value_type::default_host),
//                    json_serialise(json_field_port, value_type::default_port),
//                    json_serialise(json_field_uid, uid),
//                    json_serialise(json_field_source, source)
//                });
//            }
//
//            return retval;
//        }
//    };
//
//#undef POWER_OVERWHELMING_DECLARE_SENSOR_NAME
//#undef POWER_OVERWHELMING_DECLARE_INTRINSIC_ASYNC
//
//
//    /// <summary>
//    /// A type list of all known sensors, which allows for compile-time
//    /// enumeration of known sensor types.
//    /// </summary>
//    /// <remarks>
//    /// Implementors of new sensors should register their class here in order to
//    /// make it eligible for automated enumeration and instantiation.
//    /// </remarks>
//    typedef sensor_list_type<
//        adl_sensor,
//        emi_sensor,
//        hmc8015_sensor,
//        msr_sensor,
//        nvml_sensor,
//        rtx_sensor,
//        tinkerforge_sensor>
//        sensor_list;
//
//} /* namespace detail */
//} /* namespace power_overwhelming */
//} /* namespace visus */
