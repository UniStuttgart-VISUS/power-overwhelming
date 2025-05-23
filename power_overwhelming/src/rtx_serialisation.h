﻿// <copyright file="rtx_serialisation.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_SERIALISATION_H)
#define _PWROWG_RTX_SERIALISATION_H
#pragma once

#include "visus/pwrowg/rtx_acquisition.h"
#include "visus/pwrowg/rtx_channel.h"
#include "visus/pwrowg/rtx_instrument_configuration.h"
#include "visus/pwrowg/rtx_label.h"
#include "visus/pwrowg/rtx_quantity.h"
#include "visus/pwrowg/rtx_trigger.h"

#include "json_serialiser.h"


#define _PWROWG_DESERIALISE_FIELD(member) auto member = json_deserialise<\
    typename std::decay<decltype(std::declval<value_type>().member())>::type\
    >(json[#member])

#define _PWOWG_SERIALISE_FIELD(field) json_serialise(#field, value.field())


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Specialisation for <see cref="rtx_acquisition" />.
/// </summary>
template<> struct json_serialiser<rtx_acquisition, false, false> final {
    typedef rtx_acquisition value_type;

    static inline value_type deserialise(_In_ const nlohmann::json& json) {
        _PWROWG_DESERIALISE_FIELD(count);
        _PWROWG_DESERIALISE_FIELD(points);
        _PWROWG_DESERIALISE_FIELD(segmented);
        _PWROWG_DESERIALISE_FIELD(state);
        return value_type()
            .count(count)
            .points(points)
            .segmented(segmented)
            .state(state);
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        return nlohmann::json::object({
            _PWOWG_SERIALISE_FIELD(count),
            _PWOWG_SERIALISE_FIELD(points),
            _PWOWG_SERIALISE_FIELD(segmented),
            _PWOWG_SERIALISE_FIELD(state)
        });
    }
};

/// <summary>
/// Specialisation for <see cref="rtx_label" />.
/// </summary>
template<> struct json_serialiser<rtx_label, false, false> final {
    typedef rtx_label value_type;

    static inline value_type deserialise(_In_ const nlohmann::json& json) {
        _PWROWG_DESERIALISE_FIELD(text);
        _PWROWG_DESERIALISE_FIELD(visible);
        return value_type(text.c_str(), visible);
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        return nlohmann::json::object({
            _PWOWG_SERIALISE_FIELD(text),
            _PWOWG_SERIALISE_FIELD(visible),
        });
    }
};

/// <summary>
/// Specialisation for <see cref="rtx_quantity" />.
/// </summary>
template<> struct json_serialiser<rtx_quantity, false, false> final {
    typedef rtx_quantity value_type;

    static inline value_type deserialise(_In_ const nlohmann::json& json) {
        _PWROWG_DESERIALISE_FIELD(value);
        _PWROWG_DESERIALISE_FIELD(unit);
        return value_type(value, unit.c_str());
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        return nlohmann::json::object({
            _PWOWG_SERIALISE_FIELD(value),
            _PWOWG_SERIALISE_FIELD(unit)
        });
    }
};

/// <summary>
/// Specialisation for <see cref="rtx_channel" />.
/// </summary>
template<> struct json_serialiser<rtx_channel, false, false> final {
    typedef rtx_channel value_type;

    static inline value_type deserialise(_In_ const nlohmann::json& json) {
        _PWROWG_DESERIALISE_FIELD(attenuation);
        _PWROWG_DESERIALISE_FIELD(bandwidth);
        _PWROWG_DESERIALISE_FIELD(channel);
        _PWROWG_DESERIALISE_FIELD(coupling);
        _PWROWG_DESERIALISE_FIELD(decimation_mode);
        _PWROWG_DESERIALISE_FIELD(label);
        _PWROWG_DESERIALISE_FIELD(offset);
        _PWROWG_DESERIALISE_FIELD(polarity);
        _PWROWG_DESERIALISE_FIELD(range);
        _PWROWG_DESERIALISE_FIELD(skew);
        _PWROWG_DESERIALISE_FIELD(state);
        _PWROWG_DESERIALISE_FIELD(zero_adjust);
        _PWROWG_DESERIALISE_FIELD(zero_adjust_offset);
        _PWROWG_DESERIALISE_FIELD(zero_offset);

        return value_type(channel)
            .attenuation(attenuation)
            .bandwidth(bandwidth)
            .coupling(coupling)
            .decimation_mode(decimation_mode)
            .label(label)
            .offset(offset)
            .polarity(polarity)
            .range(range)
            .skew(skew)
            .state(state)
            .zero_adjust(zero_adjust)
            .zero_adjust_offset(zero_adjust_offset)
            .zero_offset(zero_offset);
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        return nlohmann::json::object({
            _PWOWG_SERIALISE_FIELD(attenuation),
            _PWOWG_SERIALISE_FIELD(bandwidth),
            _PWOWG_SERIALISE_FIELD(channel),
            _PWOWG_SERIALISE_FIELD(coupling),
            _PWOWG_SERIALISE_FIELD(decimation_mode),
            _PWOWG_SERIALISE_FIELD(label),
            _PWOWG_SERIALISE_FIELD(offset),
            _PWOWG_SERIALISE_FIELD(polarity),
            _PWOWG_SERIALISE_FIELD(range),
            _PWOWG_SERIALISE_FIELD(skew),
            _PWOWG_SERIALISE_FIELD(state),
            _PWOWG_SERIALISE_FIELD(zero_adjust),
            _PWOWG_SERIALISE_FIELD(zero_adjust_offset),
            _PWOWG_SERIALISE_FIELD(zero_offset)
        });
    }
};

/// <summary>
/// Specialisation for <see cref="rtx_trigger" />.
/// </summary>
template<> struct json_serialiser<rtx_trigger, false, false> final {
    typedef rtx_trigger value_type;

    static inline value_type deserialise(_In_ const nlohmann::json& json) {
        _PWROWG_DESERIALISE_FIELD(coupling);
        _PWROWG_DESERIALISE_FIELD(hold_off);
        _PWROWG_DESERIALISE_FIELD(hysteresis);
        _PWROWG_DESERIALISE_FIELD(input);
        _PWROWG_DESERIALISE_FIELD(level);
        _PWROWG_DESERIALISE_FIELD(mode);
        _PWROWG_DESERIALISE_FIELD(slope);
        _PWROWG_DESERIALISE_FIELD(source);
        _PWROWG_DESERIALISE_FIELD(type);

        return value_type(source.c_str(), type.c_str())
            .coupling(coupling)
            .level(input, level)
            .slope(slope)
            .hysteresis(hysteresis)
            .mode(mode)
            .hold_off(hold_off.c_str());
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        return nlohmann::json::object({
            _PWOWG_SERIALISE_FIELD(coupling),
            _PWOWG_SERIALISE_FIELD(hold_off),
            _PWOWG_SERIALISE_FIELD(hysteresis),
            _PWOWG_SERIALISE_FIELD(input),
            _PWOWG_SERIALISE_FIELD(level),
            _PWOWG_SERIALISE_FIELD(mode),
            _PWOWG_SERIALISE_FIELD(slope),
            _PWOWG_SERIALISE_FIELD(source),
            _PWOWG_SERIALISE_FIELD(type)
            });
    }
};

/// <summary>
/// Specialisation for <see cref="rtx_instrument_configuration" />.
/// </summary>
template<> struct json_serialiser<rtx_instrument_configuration, false,
        false> final {
    typedef rtx_instrument_configuration value_type;

    static inline value_type deserialise(_In_ const nlohmann::json& json) {
        _PWROWG_DESERIALISE_FIELD(acquisition);
        _PWROWG_DESERIALISE_FIELD(beep_on_apply);
        _PWROWG_DESERIALISE_FIELD(beep_on_error);
        _PWROWG_DESERIALISE_FIELD(beep_on_trigger);
        _PWROWG_DESERIALISE_FIELD(reference_position);
        _PWROWG_DESERIALISE_FIELD(timeout);
        _PWROWG_DESERIALISE_FIELD(time_range);
        _PWROWG_DESERIALISE_FIELD(trigger);
        _PWROWG_DESERIALISE_FIELD(trigger_position);

        value_type retval(time_range, acquisition, trigger, timeout);

        // The channels are special and need to be added one by one.
        auto channels = json["channels"];
        if (channels.type() == nlohmann::json::value_t::array) {
            for (auto& c : channels) {
                retval.channel(json_deserialise<rtx_channel>(c));
            }
        }

        return retval
            .beep_on_apply(beep_on_apply)
            .beep_on_error(beep_on_error)
            .beep_on_trigger(beep_on_trigger);
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        // Obtain the channel array manually and convert it to JSON  one by
        // one. This is too special for automating it.
        std::vector<rtx_channel> channels(value.channels());
        value.channels(channels.data(), channels.size());

        auto channels_json = nlohmann::json::array();
        for (auto& c: channels) {
            channels_json.push_back(json_serialise(c));
        }

        return nlohmann::json::object({
            _PWOWG_SERIALISE_FIELD(acquisition),
            _PWOWG_SERIALISE_FIELD(beep_on_apply),
            _PWOWG_SERIALISE_FIELD(beep_on_error),
            _PWOWG_SERIALISE_FIELD(beep_on_trigger),
            { "channels", channels_json },
            _PWOWG_SERIALISE_FIELD(reference_position),
            _PWOWG_SERIALISE_FIELD(timeout),
            _PWOWG_SERIALISE_FIELD(time_range),
            _PWOWG_SERIALISE_FIELD(trigger),
            _PWOWG_SERIALISE_FIELD(trigger_position)
        });
    }
};

#undef _PWROWG_DESERIALISE_FIELD
#undef _PWOWG_SERIALISE_FIELD

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_SERIALISATION_H) */
