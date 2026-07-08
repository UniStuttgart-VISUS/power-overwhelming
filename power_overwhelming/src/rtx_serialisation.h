// <copyright file="rtx_serialisation.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_SERIALISATION_H)
#define _PWROWG_RTX_SERIALISATION_H
#pragma once

#include <type_traits>

#include "visus/pwrowg/macro_concat.h"
#include "visus/pwrowg/rtx_acquisition.h"
#include "visus/pwrowg/rtx_channel.h"
#include "visus/pwrowg/rtx_configuration.h"
#include "visus/pwrowg/rtx_instrument_configuration.h"
#include "visus/pwrowg/rtx_label.h"
#include "visus/pwrowg/rtx_quantity.h"
#include "visus/pwrowg/rtx_sensor_definition.h"
#include "visus/pwrowg/rtx_sensor_trigger_builder.h"
#include "visus/pwrowg/rtx_trigger.h"

#include "json_serialiser.h"


#define _PWROWG_DESERIALISE_FIELD(member) auto member = json_deserialise<\
    typename std::decay<decltype(std::declval<value_type>().member())>::type>\
    (json[PWROWG_CONCAT(u8, #member)])

#define _PWROWG_SERIALISE_FIELD(field) json_serialise(\
    PWROWG_CONCAT(u8, #field), value.field())


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
            _PWROWG_SERIALISE_FIELD(count),
            _PWROWG_SERIALISE_FIELD(points),
            _PWROWG_SERIALISE_FIELD(segmented),
            _PWROWG_SERIALISE_FIELD(state)
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
            _PWROWG_SERIALISE_FIELD(text),
            _PWROWG_SERIALISE_FIELD(visible),
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
            _PWROWG_SERIALISE_FIELD(value),
            _PWROWG_SERIALISE_FIELD(unit)
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
            _PWROWG_SERIALISE_FIELD(attenuation),
            _PWROWG_SERIALISE_FIELD(bandwidth),
            _PWROWG_SERIALISE_FIELD(channel),
            _PWROWG_SERIALISE_FIELD(coupling),
            _PWROWG_SERIALISE_FIELD(decimation_mode),
            _PWROWG_SERIALISE_FIELD(label),
            _PWROWG_SERIALISE_FIELD(offset),
            _PWROWG_SERIALISE_FIELD(polarity),
            _PWROWG_SERIALISE_FIELD(range),
            _PWROWG_SERIALISE_FIELD(skew),
            _PWROWG_SERIALISE_FIELD(state),
            _PWROWG_SERIALISE_FIELD(zero_adjust),
            _PWROWG_SERIALISE_FIELD(zero_adjust_offset),
            _PWROWG_SERIALISE_FIELD(zero_offset)
        });
    }
};


/// <summary>
/// Specialisation for <see cref="rtx_sensor_definition" />.
/// </summary>
template<> struct json_serialiser<rtx_sensor_definition, false, false> final {
    typedef rtx_sensor_definition value_type;

    static inline value_type deserialise(_In_ const nlohmann::json& json) {
        _PWROWG_DESERIALISE_FIELD(current_channel);
        _PWROWG_DESERIALISE_FIELD(description);
        _PWROWG_DESERIALISE_FIELD(path);
        _PWROWG_DESERIALISE_FIELD(voltage_channel);
        _PWROWG_DESERIALISE_FIELD(waveform_points);

        return value_type(path.c_str(),
            voltage_channel,
            current_channel,
            description.c_str(),
            waveform_points);
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        return nlohmann::json::object({
            _PWROWG_SERIALISE_FIELD(current_channel),
            _PWROWG_SERIALISE_FIELD(description),
            _PWROWG_SERIALISE_FIELD(path),
            _PWROWG_SERIALISE_FIELD(voltage_channel),
            _PWROWG_SERIALISE_FIELD(waveform_points)
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

        return value_type(source.c_str(), type)
            .coupling(coupling)
            .level(input, level)
            .slope(slope)
            .hysteresis(hysteresis)
            .mode(mode)
            .hold_off(hold_off.c_str());
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        return nlohmann::json::object({
            _PWROWG_SERIALISE_FIELD(coupling),
            _PWROWG_SERIALISE_FIELD(hold_off),
            _PWROWG_SERIALISE_FIELD(hysteresis),
            _PWROWG_SERIALISE_FIELD(input),
            _PWROWG_SERIALISE_FIELD(level),
            _PWROWG_SERIALISE_FIELD(mode),
            _PWROWG_SERIALISE_FIELD(slope),
            _PWROWG_SERIALISE_FIELD(source),
            _PWROWG_SERIALISE_FIELD(type)
            });
    }
};


/// <summary>
/// Specialisation for <see cref="rtx_sensor_trigger" />.
/// </summary>
template<> struct json_serialiser<rtx_sensor_trigger, false, false> final {
    typedef rtx_sensor_trigger value_type;

    static inline value_type deserialise(_In_ const nlohmann::json& json) {
        auto it = json.find(u8"path");
        auto builder = ((it != json.end()) && it->is_string())
            ? rtx_sensor_trigger_builder::for_path(it->get<std::string>())
            : rtx_sensor_trigger_builder::for_all();

        it = json.find(u8"trigger");
        if ((it != json.end()) && it->is_object()) {
            auto trigger = json_deserialise<rtx_trigger>(*it);
            return builder.with_trigger(trigger).build();
        } else {
            return builder.when_software_triggered().build();
        }
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        auto path = (value.path() != nullptr)
            ? json_serialise(value.path())
            : nlohmann::json(nullptr);
        auto trigger = (value.trigger() != nullptr)
            ? json_serialise(*value.trigger())
            : nlohmann::json(nullptr);

        return nlohmann::json::object({
            { u8"path", path },
            { u8"trigger", trigger },
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
            .beep_on_trigger(beep_on_trigger)
            .reference_position(reference_position)
            .trigger_position(trigger_position);
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
            _PWROWG_SERIALISE_FIELD(acquisition),
            _PWROWG_SERIALISE_FIELD(beep_on_apply),
            _PWROWG_SERIALISE_FIELD(beep_on_error),
            _PWROWG_SERIALISE_FIELD(beep_on_trigger),
            { "channels", channels_json },
            _PWROWG_SERIALISE_FIELD(reference_position),
            _PWROWG_SERIALISE_FIELD(timeout),
            _PWROWG_SERIALISE_FIELD(time_range),
            _PWROWG_SERIALISE_FIELD(trigger),
            _PWROWG_SERIALISE_FIELD(trigger_position)
        });
    }
};


/// <summary>
/// Specialisation for <see cref="rtx_configuration" />.
/// </summary>
template<> struct json_serialiser<rtx_configuration, false, false> final {
    typedef rtx_configuration value_type;

    static inline value_type deserialise(_In_ const nlohmann::json& json) {
        _PWROWG_DESERIALISE_FIELD(base_configuration);
        _PWROWG_DESERIALISE_FIELD(download_retries);
        _PWROWG_DESERIALISE_FIELD(download_timeout);
        _PWROWG_DESERIALISE_FIELD(reset_on_enumerate);
        _PWROWG_DESERIALISE_FIELD(reset_flags);
        _PWROWG_DESERIALISE_FIELD(trigger);

        std::vector<rtx_sensor_definition> sensors;
        auto it = json.find(u8"sensors");
        if ((it != json.end()) && it->is_array()) {
            for (auto& s : *it) {
                sensors.push_back(json_deserialise<rtx_sensor_definition>(s));
            }
        }

        return rtx_configuration()
            .base_configuration(std::move(base_configuration))
            .download_retries(download_retries)
            .download_timeout(download_timeout)
            .reset_on_enumerate(reset_on_enumerate)
            .reset_flags(reset_flags)
            .sensors(sensors.data(), sensors.size())
            .trigger(trigger);
    }

    static inline nlohmann::json serialise(_In_ const value_type& value) {
        auto sensors = nlohmann::json::array();
        for (std::size_t i = 0; i < value.count_sensors(); ++i) {
            sensors.push_back(json_serialise(value.sensor(i)));
        }

        return nlohmann::json::object({
            _PWROWG_SERIALISE_FIELD(base_configuration),
            _PWROWG_SERIALISE_FIELD(download_retries),
            _PWROWG_SERIALISE_FIELD(download_timeout),
            _PWROWG_SERIALISE_FIELD(reset_on_enumerate),
            _PWROWG_SERIALISE_FIELD(reset_flags),
            { "sensors", sensors },
            _PWROWG_SERIALISE_FIELD(trigger),
        });
    }
};

#undef _PWROWG_DESERIALISE_FIELD
#undef _PWROWG_SERIALISE_FIELD

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_SERIALISATION_H) */
