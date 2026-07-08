// <copyright file="daqmx_serialisation.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_SERIALISATION_H)
#define _PWROWG_DAQMX_SERIALISATION_H
#pragma once

#include <type_traits>

#include "visus/pwrowg/daqmx_current_channel.h"
#include "visus/pwrowg/daqmx_implicit_timing.h"
#include "visus/pwrowg/daqmx_power_channel.h"
#include "visus/pwrowg/daqmx_sample_clock_timing.h"
#include "visus/pwrowg/daqmx_voltage_channel.h"

#include "json_serialiser.h"


#define _PWROWG_DESERIALISE_FIELD(member) auto member = json_deserialise<\
    typename std::decay<decltype(std::declval<value_type>().member())>::type\
    >(json[#member])

#define _PWROWG_SERIALISE_FIELD(field) json_serialise(#field, value.field())


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Specialisation for <see cref="daqmx_current_channel" />.
/// </summary>
template<> struct json_serialiser<daqmx_current_channel, false, false> final {
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
template<> struct json_serialiser<daqmx_implicit_timing, false, false> final {
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
template<> struct json_serialiser<daqmx_power_channel, false, false> final {
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
template<> struct json_serialiser<daqmx_sample_clock_timing, false, false> final {
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
template<> struct json_serialiser<daqmx_voltage_channel, false, false> final {
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


#undef _PWROWG_DESERIALISE_FIELD
#undef _PWROWG_SERIALISE_FIELD

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_SERIALISATION_H) */
