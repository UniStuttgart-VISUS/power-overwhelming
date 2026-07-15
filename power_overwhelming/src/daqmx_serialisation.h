// <copyright file="daqmx_serialisation.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_SERIALISATION_H)
#define _PWROWG_DAQMX_SERIALISATION_H
#pragma once

#include <stdexcept>
#include <type_traits>

#include "visus/pwrowg/macro_concat.h"
#include "visus/pwrowg/daqmx_configuration.h"
#include "visus/pwrowg/daqmx_current_channel.h"
#include "visus/pwrowg/daqmx_implicit_timing.h"
#include "visus/pwrowg/daqmx_power_channel.h"
#include "visus/pwrowg/daqmx_sample_clock_timing.h"
#include "visus/pwrowg/daqmx_sensor_definition.h"
#include "visus/pwrowg/daqmx_voltage_channel.h"
#include "visus/pwrowg/convert_string.h"

#include "json_serialiser.h"


#define _PWROWG_DESERIALISE_FIELD(member) auto member = json_deserialise<\
    typename std::decay<decltype(std::declval<value_type>().member())>::type>\
    (json[PWROWG_CONCAT(u8, #member)])

#define _PWROWG_SERIALISE_FIELD(field) json_serialise(\
    PWROWG_CONCAT(u8, #field), value.field())


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Specialisation for <see cref="daqmx_current_channel" />.
/// </summary>
template<bool IsArithmetic, bool IsEnum>
struct json_serialiser<daqmx_current_channel, IsArithmetic, IsEnum> final {
    typedef daqmx_current_channel value_type;

    static inline value_type deserialise(_In_ const nlohmann::json& json) {
        _PWROWG_DESERIALISE_FIELD(channel);
        _PWROWG_DESERIALISE_FIELD(max_value);
        _PWROWG_DESERIALISE_FIELD(min_value);
        _PWROWG_DESERIALISE_FIELD(name);
        _PWROWG_DESERIALISE_FIELD(shunt_resistor_value);
        _PWROWG_DESERIALISE_FIELD(shunt_resistor_location);
        _PWROWG_DESERIALISE_FIELD(terminal_configuration);
        return value_type(channel.c_str())
            .max_value(max_value)
            .min_value(min_value)
            .name(name.c_str())
            .shunt_resistor_value(shunt_resistor_value)
            .shunt_resistor_location(shunt_resistor_location)
            .terminal_configuration(terminal_configuration);
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        return nlohmann::json::object({
            _PWROWG_SERIALISE_FIELD(channel),
            _PWROWG_SERIALISE_FIELD(max_value),
            _PWROWG_SERIALISE_FIELD(min_value),
            _PWROWG_SERIALISE_FIELD(name),
            _PWROWG_SERIALISE_FIELD(shunt_resistor_value),
            _PWROWG_SERIALISE_FIELD(shunt_resistor_location),
            _PWROWG_SERIALISE_FIELD(terminal_configuration)
        });
    }
};


#if defined(POWER_OVERWHELMING_WITH_DAQMX)
/// <summary>
/// Specialisation for <see cref="daqmx_implicit_timing" />.
/// </summary>
template<bool IsArithmetic, bool IsEnum>
struct json_serialiser<daqmx_implicit_timing, IsArithmetic, IsEnum> final {
    typedef daqmx_implicit_timing value_type;

    static inline value_type deserialise(_In_ const nlohmann::json& json) {
        _PWROWG_DESERIALISE_FIELD(mode);
        _PWROWG_DESERIALISE_FIELD(samples);
        return value_type(mode, samples);
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        return nlohmann::json::object({
            _PWROWG_SERIALISE_FIELD(mode),
            _PWROWG_SERIALISE_FIELD(samples)
        });
    }
};
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */


/// <summary>
/// Specialisation for <see cref="daqmx_power_channel" />.
/// </summary>
template<bool IsArithmetic, bool IsEnum>
struct json_serialiser<daqmx_power_channel, IsArithmetic, IsEnum> final {
    typedef daqmx_power_channel value_type;

    static inline value_type deserialise(_In_ const nlohmann::json& json) {
        _PWROWG_DESERIALISE_FIELD(current_channel);
        _PWROWG_DESERIALISE_FIELD(current_max_value);
        _PWROWG_DESERIALISE_FIELD(current_min_value);
        _PWROWG_DESERIALISE_FIELD(name);
        _PWROWG_DESERIALISE_FIELD(shunt_resistor_value);
        _PWROWG_DESERIALISE_FIELD(shunt_resistor_location);
        _PWROWG_DESERIALISE_FIELD(terminal_configuration);
        _PWROWG_DESERIALISE_FIELD(voltage_channel);
        _PWROWG_DESERIALISE_FIELD(voltage_max_value);
        _PWROWG_DESERIALISE_FIELD(voltage_min_value);
        return value_type(voltage_channel.c_str(), current_channel.c_str())
            .current_max_value(current_max_value)
            .current_min_value(current_min_value)
            .name(name.c_str())
            .shunt_resistor_value(shunt_resistor_value)
            .shunt_resistor_location(shunt_resistor_location)
            .terminal_configuration(terminal_configuration)
            .voltage_max_value(voltage_max_value)
            .voltage_min_value(voltage_min_value);
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        return nlohmann::json::object({
            _PWROWG_SERIALISE_FIELD(current_channel),
            _PWROWG_SERIALISE_FIELD(current_max_value),
            _PWROWG_SERIALISE_FIELD(current_min_value),
            _PWROWG_SERIALISE_FIELD(name),
            _PWROWG_SERIALISE_FIELD(shunt_resistor_value),
            _PWROWG_SERIALISE_FIELD(shunt_resistor_location),
            _PWROWG_SERIALISE_FIELD(terminal_configuration),
            _PWROWG_SERIALISE_FIELD(voltage_channel),
            _PWROWG_SERIALISE_FIELD(voltage_max_value),
            _PWROWG_SERIALISE_FIELD(voltage_min_value)
        });
    }
};


#if defined(POWER_OVERWHELMING_WITH_DAQMX)
/// <summary>
/// Specialisation for <see cref="daqmx_sample_clock_timing" />.
/// </summary>
template<bool IsArithmetic, bool IsEnum>
struct json_serialiser<daqmx_sample_clock_timing, IsArithmetic, IsEnum> final {
    typedef daqmx_sample_clock_timing value_type;

    static inline value_type deserialise(_In_ const nlohmann::json& json) {
        _PWROWG_DESERIALISE_FIELD(edge);
        _PWROWG_DESERIALISE_FIELD(mode);
        _PWROWG_DESERIALISE_FIELD(rate);
        _PWROWG_DESERIALISE_FIELD(samples);
        _PWROWG_DESERIALISE_FIELD(source);
        return value_type(source.c_str(), rate, edge, mode, samples);
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        return nlohmann::json::object({
            _PWROWG_SERIALISE_FIELD(edge),
            _PWROWG_SERIALISE_FIELD(mode),
            _PWROWG_SERIALISE_FIELD(rate),
            _PWROWG_SERIALISE_FIELD(samples),
            _PWROWG_SERIALISE_FIELD(source)
        });
    }
};
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */


/// <summary>
/// Specialisation for <see cref="daqmx_voltage_channel" />.
/// </summary>
template<bool IsArithmetic, bool IsEnum>
struct json_serialiser<daqmx_voltage_channel, IsArithmetic, IsEnum> final {
    typedef daqmx_voltage_channel value_type;

    static inline value_type deserialise(_In_ const nlohmann::json& json) {
        _PWROWG_DESERIALISE_FIELD(channel);
        _PWROWG_DESERIALISE_FIELD(max_value);
        _PWROWG_DESERIALISE_FIELD(min_value);
        _PWROWG_DESERIALISE_FIELD(name);
        _PWROWG_DESERIALISE_FIELD(terminal_configuration);
        return value_type(channel.c_str())
            .max_value(max_value)
            .min_value(min_value)
            .name(name.c_str())
            .terminal_configuration(terminal_configuration);
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        return nlohmann::json::object({
            _PWROWG_SERIALISE_FIELD(channel),
            _PWROWG_SERIALISE_FIELD(max_value),
            _PWROWG_SERIALISE_FIELD(min_value),
            _PWROWG_SERIALISE_FIELD(name),
            _PWROWG_SERIALISE_FIELD(terminal_configuration)
            });
    }
};


/// <summary>
/// Specialisation for <see cref="daqmx_sensor_definition" />.
/// </summary>
template<bool IsArithmetic, bool IsEnum>
struct json_serialiser<daqmx_sensor_definition, IsArithmetic, IsEnum> final {
    typedef daqmx_sensor_definition value_type;

    static inline value_type deserialise(_In_ const nlohmann::json& json) {
        auto c = json.find(u8"current_channel");
        _PWROWG_DESERIALISE_FIELD(description);
        auto d = PWROWG_NAMESPACE::convert_string<wchar_t>(description);
        auto p = json.find(u8"power_channel");
        auto v = json.find(u8"voltage_channel");
        auto vc = json.find(u8"voltage_for_current_channel");
        _PWROWG_DESERIALISE_FIELD(volt_per_ampere);

        if ((c != json.end()) && c->is_object()
                && (v != json.end()) && v->is_object()) {
            auto voltage_channel = json_deserialise<daqmx_voltage_channel>(*v);
            auto current_channel = json_deserialise<daqmx_current_channel>(*c);
            return value_type(voltage_channel, current_channel, d.c_str());

        } else if ((p != json.end()) && p->is_object()) {
            auto power_channel = json_deserialise<daqmx_power_channel>(*p);
            return value_type(power_channel, d.c_str());

        } else if ((v != json.end()) && v->is_object()
                && (vc != json.end()) && vc->is_object()) {
            auto voltage_channel = json_deserialise<daqmx_voltage_channel>(*v);
            auto vc_channel = json_deserialise<daqmx_voltage_channel>(*vc);
            return value_type(voltage_channel, vc_channel, volt_per_ampere,
                d.c_str());

        } else {
            throw std::invalid_argument("The given JSON does not contain a "
                "valid NI-DAQmx sensor definition");
        }
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        auto retval = nlohmann::json::object({
            _PWROWG_SERIALISE_FIELD(description),
            _PWROWG_SERIALISE_FIELD(volt_per_ampere)
        });

        {
            auto c = value.current_channel();
            if (c != nullptr) {
                retval[u8"current_channel"] = json_serialise(*c);
            }
        }

        {
            auto c = value.power_channel();
            if (c != nullptr) {
                retval[u8"power_channel"] = json_serialise(*c);
            }
        }

        {
            auto c = value.voltage_channel();
            if (c != nullptr) {
                retval[u8"voltage_channel"] = json_serialise(*c);
            }
        }

        {
            auto c = value.voltage_for_current_channel();
            if (c != nullptr) {
                retval[u8"voltage_for_current_channel"] = json_serialise(*c);
            }
        }

        return retval;
    }
};


/// <summary>
/// Specialisation for <see cref="daqmx_configuration" />.
/// </summary>
template<bool IsArithmetic, bool IsEnum>
struct json_serialiser<daqmx_configuration, IsArithmetic, IsEnum> final {
    typedef daqmx_configuration value_type;

    static inline value_type deserialise(_In_ const nlohmann::json& json) {
        value_type retval;
        return retval;
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        auto retval = nlohmann::json::object({ });
        return retval;
    }
};

#undef _PWROWG_DESERIALISE_FIELD
#undef _PWROWG_SERIALISE_FIELD

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_SERIALISATION_H) */
