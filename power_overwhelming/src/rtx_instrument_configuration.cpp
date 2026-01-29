// <copyright file="rtx_instrument_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_instrument_configuration.h"

#include <cstring>
#include <fstream>
#include <limits>
#include <map>
#include <memory>
#include <stdexcept>
#include <vector>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/rtx_instrument.h"

#include "rtx_serialisation.h"
#include "string_functions.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

static constexpr const char *json_field_config = "configuration";
static constexpr const char *json_field_name = "name";
static constexpr const char *json_field_path = "path";

/// <summary>
/// Parse an instrument configuration from the given JSON object.
/// </summary>
static void parse_rtx_instument_conf(_In_ const nlohmann::json obj,
        _Inout_ std::vector<rtx_instrument_configuration>& configs,
        _Inout_ std::map<std::string, std::size_t>& by_path,
        _Inout_ std::map<std::string, std::size_t>& by_name) {
    if (obj.contains(json_field_config)) {
        // This is a compound object that potentially ties the
        // configuration to a specific device.
        const auto idx = configs.size();
        configs.push_back(PWROWG_DETAIL_NAMESPACE::json_deserialise<
            rtx_instrument_configuration>(obj[json_field_config]));

        const auto name = obj[json_field_name].get<std::string>();
        if (!name.empty()) {
            by_name[name] = idx;
        }

        const auto path = obj[json_field_path].get<std::string>();
        if (!path.empty()) {
            by_path[path] = idx;
        }

    } else {
        // This must be the configuration object itself, so just add it.
        configs.push_back(PWROWG_DETAIL_NAMESPACE::json_deserialise<
            rtx_instrument_configuration>(obj));
    }
}

/// <summary>
/// Parse the (first) instument configuration from the given JSON object or
/// array.
/// </summary>
static rtx_instrument_configuration parse_rtx_instrument_conf(
        _In_ nlohmann::json json) {
    switch (json.type()) {
        case nlohmann::json::value_t::array:
            if (json.size() == 0) {
                throw std::invalid_argument("The configuration array provided "
                    "must not be empty.");
            }

            json = json[0];
            break;

        case nlohmann::json::value_t::object:
            break;

        default:
            throw std::invalid_argument("The JSON file provided must contain "
                "an object or a non-emtpy array of objects.");
    }

    return PWROWG_DETAIL_NAMESPACE::json_deserialise<
        rtx_instrument_configuration>(json);
}

/// <summary>
/// Deserialises one or more configurations.
/// </summary>
static std::size_t parse_rtx_instrument_confs(
        _When_(dst != nullptr, _Out_writes_opt_(cnt))
        rtx_instrument_configuration *dst,
        _In_ std::size_t cnt,
        _In_ const nlohmann::json& json) {
    if ((cnt > 0) && (dst == nullptr)) {
        throw std::invalid_argument("The configuration array to store "
            "the configurations to must be valid unless the number of "
            "configurations to configure is zero.");
    }

    // Determine the required memory.
    std::size_t retval = 0;
    switch (json.type()) {
        case nlohmann::json::value_t::array:
            retval = json.size();
            break;

        case nlohmann::json::value_t::object:
            retval = 1;
            break;

        default:
            retval = 0;
            break;
    }

    // There is no space if the array is invalid.
    if (dst == nullptr) {
        cnt = 0;
    }

    // Load as many configurations as possible.
    for (std::size_t i = 0; (i < cnt) && (i < retval); ++i) {
        const auto &j = json[i];
        dst[i] = PWROWG_DETAIL_NAMESPACE::json_deserialise<
            rtx_instrument_configuration>(j);
    }

    return retval;
}

#if defined(POWER_OVERWHELMING_WITH_VISA)
/// <summary>
/// Apply the configurations from the given JSON array to the given
/// instruments if they can be matched by path or name. If there is no
/// match, the first configuration in <paramref name="json" /> will be
/// used.
/// </summary>
static void apply(_In_reads_(cnt) rtx_instrument *instruments,
        _In_ const std::size_t cnt,
        _In_ const nlohmann::json& json) {
    if ((cnt > 0) && (instruments == nullptr)) {
        throw std::invalid_argument("The instrument array to apply the "
            "configurations to must be valid unless the number of "
            "instruments to configure is zero.");
    }

    std::vector<rtx_instrument_configuration> configs;
    std::map<std::string, std::size_t> by_name;
    std::map<std::string, std::size_t> by_path;

    // Find out what kind of data we have. If we have an array, add all of its
    // members. If we have a single object, just add this one. Any other type
    // of data indicates an invalid file.
    switch (json.type()) {
        case nlohmann::json::value_t::array:
            for (auto j : json) {
                detail::parse_rtx_instument_conf(j, configs, by_path, by_name);
            }
            break;

        case nlohmann::json::value_t::object:
            detail::parse_rtx_instument_conf(json, configs, by_path, by_name);
            break;

        default:
            throw std::invalid_argument("The specified file did not contain "
                "a configuration object or an array thereof.");
    }

    if (configs.size() < 1) {
        throw std::invalid_argument("The specified file did not contain any "
            "valid configuration objects.");
    }

    for (std::size_t i = 0; i < cnt; ++i) {
        auto& instrument = instruments[i];

        {
            auto it = by_path.find(instrument.path());
            if (it != by_path.end()) {
                configs[it->second].apply(instrument);
                continue;
            }
        }

        {
            std::vector<char> name(instrument.name(nullptr, 0));
            instrument.name(name.data(), name.size());

            auto it = by_name.find(name.data());
            if (it != by_name.end()) {
                configs[it->second].apply(instrument);
                continue;
            }
        }

        configs.front().apply(instrument);
    }
}
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

/// <summary>
/// Convert the given array of instrument configuration into an array of
/// JSON objects.
/// </summary>
static nlohmann::json to_json(
        _In_reads_(cnt) const rtx_instrument_configuration *configs,
        _In_ const std::size_t cnt) {
    if ((cnt > 0) && (configs == nullptr)) {
        throw std::invalid_argument("The instrument configurations array "
            "to be serialised must be valid unless their number is zero.");
    }

    auto retval = nlohmann::json::array();

    for (std::size_t i = 0; i < cnt; ++i) {
        retval.push_back(detail::json_serialise(configs[i]));
    }

    return retval;
}

#if defined(POWER_OVERWHELMING_WITH_VISA)
/// <summary>
/// Convert the given instruments into an array of JSON configuration
/// objects.
/// </summary>
static nlohmann::json to_json(
        _In_reads_(cnt) const rtx_instrument *instruments,
        _In_ const std::size_t cnt) {
    if ((cnt > 0) && (instruments == nullptr)) {
        throw std::invalid_argument("The instrument array to serialise "
            "the configuration of must be valid unless their number is "
            "zero.");
    }

    auto retval = nlohmann::json::array();

    for (std::size_t i = 0; i < cnt; ++i) {
        rtx_instrument_configuration config(instruments[i]);
        std::vector<char> name(instruments[i].name(nullptr, 0));
        instruments[i].name(name.data(), name.size());

        retval.push_back(nlohmann::json::object({
            detail::json_serialise(detail::json_field_path,
                instruments[i].path()),
            detail::json_serialise(detail::json_field_name,
                std::string(name.data())),
            detail::json_serialise(detail::json_field_config, config)
            }));
    }

    return retval;
}
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

PWROWG_DETAIL_NAMESPACE_END


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::apply
 */
void PWROWG_NAMESPACE::rtx_instrument_configuration::apply(
        _In_reads_(cnt) rtx_instrument *instruments,
        _In_ const std::size_t cnt,
        _In_ const rtx_instrument_configuration& configuration,
        _In_ const bool master_slave,
        _In_ const rtx_quantity& level,
        _In_ const rtx_trigger_slope slope) {
    if ((instruments == nullptr) || (cnt < 1)) {
        // Bail out if there is nothing to configure.
        return;
    }

    // If the first instrument was requested to beep, remember this as we want
    // to beep all subsequent instruments once more.
    const auto beep = (configuration.beep_on_apply() > 0);

    if (master_slave || beep) {
        // If we have a master-slave configurations or the instruments should
        // beep, each configuration is individual, so we need to adjust them in
        // the loop.
        auto config = configuration;

        for (std::size_t i = 0; i < cnt; ++i) {
            if (master_slave && (i == 1)) {
                config = config.as_slave(0, level, slope);
            }
            if (beep) {
                config.beep_on_apply(configuration.beep_on_apply() + i);
            }

            configuration.apply(instruments[i]);
        }

    } else {
        // In the trivial case, just apply the same stuff to all instruments.
        for (std::size_t i = 0; i < cnt; ++i) {
            configuration.apply(instruments[i]);
        }
    }
}
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::apply
 */
std::size_t PWROWG_NAMESPACE::rtx_instrument_configuration::apply(
        _In_reads_(cnt) rtx_instrument *instruments,
        _In_ const std::size_t cnt,
        _In_ const rtx_instrument_configuration& configuration,
        _In_z_ const wchar_t *master,
        _In_ const rtx_quantity& level,
        _In_ const rtx_trigger_slope slope) {
    if (master == nullptr) {
        throw std::invalid_argument("A valid name for the master instrument "
            "must be supplied.");
    }

    auto m = convert_string<char>(master);
    return apply(instruments, cnt, configuration, m.c_str(), level, slope);
}
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::apply
 */
std::size_t PWROWG_NAMESPACE::rtx_instrument_configuration::apply(
        _In_reads_(cnt) rtx_instrument *instruments,
        _In_ const std::size_t cnt,
        _In_ const rtx_instrument_configuration& configuration,
        _In_z_ const char *master,
        _In_ const rtx_quantity& level,
        _In_ const rtx_trigger_slope slope) {
    auto retval = cnt;

    if (master == nullptr) {
        throw std::invalid_argument("A valid name for the master instrument "
            "must be supplied.");
    }

    if ((instruments == nullptr) || (cnt < 1)) {
        // Bail out if there is nothing to configure.
        return retval;
    }

    auto beeps = configuration.beep_on_apply();
    auto slave_configuration = configuration.as_slave(beeps, level, slope);

    for (std::size_t i = 0; i < cnt; ++i) {
        std::vector<char> name(instruments[i].name(nullptr, 0));
        instruments[i].name(name.data(), name.size());

        if (::strcmp(name.data(), master) == 0) {
            configuration.apply(instruments[i]);
            retval = i;
        } else {
            if (beeps > 0) {
                slave_configuration.beep_on_apply(++beeps);
            }

            slave_configuration.apply(instruments[i]);
        }
    }

    return retval;
}
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::apply
 */
void PWROWG_NAMESPACE::rtx_instrument_configuration::apply(
        _In_reads_(cnt) rtx_instrument *instruments,
        _In_ const std::size_t cnt,
        _In_z_ const wchar_t *path) {
    auto json = detail::load_json(path);
    detail::apply(instruments, cnt, json);
}
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::apply_from_json
 */
void PWROWG_NAMESPACE::rtx_instrument_configuration::apply_from_json(
        _In_reads_(cnt) rtx_instrument *instruments,
        _In_ const std::size_t cnt,
        _In_z_ const char *str) {
    if (str == nullptr) {
        throw std::invalid_argument("A valid UTF-8-encoded JSON string must be "
            "provided.");
    }

    const auto json = nlohmann::json::parse(str);
    detail::apply(instruments, cnt, json);
}
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::deserialise
 */
PWROWG_NAMESPACE::rtx_instrument_configuration
PWROWG_NAMESPACE::rtx_instrument_configuration::deserialise(
        _In_z_ const char *str) {
    if (str == nullptr) {
        throw std::invalid_argument("A valid UTF-8-encoded JSON string must be "
            "provided.");
    }

    const auto json = nlohmann::json::parse(str);
    return PWROWG_DETAIL_NAMESPACE::json_deserialise<
        rtx_instrument_configuration>(json);
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::deserialise
 */
std::size_t
PWROWG_NAMESPACE::rtx_instrument_configuration::deserialise(
        _When_(dst != nullptr, _Out_writes_opt_(cnt))
        rtx_instrument_configuration *dst,
        _In_ std::size_t cnt,
        _In_z_ const char *str) {
    if (str == nullptr) {
        throw std::invalid_argument("A valid UTF-8-encoded JSON string must be "
            "provided.");
    }

    const auto json = nlohmann::json::parse(str);
    return detail::parse_rtx_instrument_confs(dst, cnt, json);
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::load
 */
std::size_t PWROWG_NAMESPACE::rtx_instrument_configuration::load(
        _When_(dst != nullptr, _Out_writes_opt_(cnt))
        rtx_instrument_configuration *dst,
        _In_ std::size_t cnt,
        _In_z_ const wchar_t *path) {
    auto json = detail::load_json(path);
    return detail::parse_rtx_instrument_confs(dst, cnt, json);
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::load
 */
PWROWG_NAMESPACE::rtx_instrument_configuration
PWROWG_NAMESPACE::rtx_instrument_configuration::load(
        _In_z_ const wchar_t *path) {
    return detail::parse_rtx_instrument_conf(detail::load_json(path));
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::save
 */
void PWROWG_NAMESPACE::rtx_instrument_configuration::save(
        _In_reads_(cnt) const rtx_instrument_configuration *configs,
        _In_ const std::size_t cnt,
        _In_z_ const wchar_t *path) {
    detail::save_json(detail::to_json(configs, cnt), path);
}


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::save
 */
void PWROWG_NAMESPACE::rtx_instrument_configuration::save(
        _In_reads_(cnt) const rtx_instrument *instruments,
        _In_ const std::size_t cnt,
        _In_z_ const wchar_t *path) {
    detail::save_json(detail::to_json(instruments, cnt), path);
}
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::save
 */
void PWROWG_NAMESPACE::rtx_instrument_configuration::save(
        _In_ const rtx_instrument_configuration& configuration,
        _In_z_ const wchar_t *path) {
    detail::save_json(detail::json_serialise(configuration), path);
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::serialise
 */
std::size_t PWROWG_NAMESPACE::rtx_instrument_configuration::serialise(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) char *dst,
        _In_ const std::size_t cnt,
        _In_ const rtx_instrument_configuration& configuration) {
    const auto json = detail::json_serialise(configuration);
    const auto str = json.dump();
    const auto retval = str.size() + 1;
    detail::copy_string(dst, cnt, str);
    return retval;
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::serialise
 */
std::size_t PWROWG_NAMESPACE::rtx_instrument_configuration::serialise(
        _When_(dst != nullptr, _Out_writes_opt_(cnt_dst)) char *dst,
        _In_ const std::size_t cnt_dst,
        _In_reads_(cnt_configs) const rtx_instrument_configuration *configs,
        _In_ const std::size_t cnt_configs) {
    const auto json = detail::to_json(configs, cnt_configs);
    const auto str = json.dump();
    const auto retval = str.size() + 1;
    detail::copy_string(dst, cnt_dst, str);
    return retval;
}


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::serialise
 */
std::size_t PWROWG_NAMESPACE::rtx_instrument_configuration::serialise(
        _When_(dst != nullptr, _Out_writes_opt_(cnt_dst)) char *dst,
        _In_ const std::size_t cnt_dst,
        _In_reads_(cnt_instruments) const rtx_instrument *instruments,
        _In_ const std::size_t cnt_instruments) {
    const auto json = detail::to_json(instruments, cnt_instruments);
    const auto str = json.dump();
    const auto retval = str.size() + 1;
    detail::copy_string(dst, cnt_dst, str);
    return retval;
}
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::id
 */
const PWROWG_NAMESPACE::guid PWROWG_NAMESPACE::rtx_instrument_configuration::id(
    0x4dba2660, 0x1e1, 0x43e6, 0x93, 0x43, 0xd, 0x6e, 0xdc, 0xa7, 0xf4, 0xfb);


/*
 * ...::rtx_instrument_configuration::rtx_instrument_configuration
 */
PWROWG_NAMESPACE::rtx_instrument_configuration::rtx_instrument_configuration(
        void)
    : _beep_on_apply(0),
        _beep_on_error(false),
        _beep_on_trigger(false),
        _channels(nullptr),
        _cnt_channels(0),
        _min_time_base(0.0f),
        _reference_position(rtx_reference_point::middle),
        _slave(false),
        _timeout(0),
        _time_range(0.0f),
        _trigger("EXT", "EDGE"),
        _trigger_position(0.0f) { }


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::rtx_instrument_configuration
 */
PWROWG_NAMESPACE::rtx_instrument_configuration::rtx_instrument_configuration(
        _In_ const rtx_instrument_configuration& rhs)
    : _acquisition(rhs._acquisition),
        _beep_on_apply(rhs._beep_on_apply),
        _beep_on_error(rhs._beep_on_error),
        _beep_on_trigger(rhs._beep_on_trigger),
        _channels(nullptr),
        _cnt_channels(rhs._cnt_channels),
        _min_time_base(0.0f),
        _reference_position(rhs._reference_position),
        _slave(rhs._slave),
        _timeout(rhs._timeout),
        _time_range(rhs._time_range),
        _trigger(rhs._trigger),
        _trigger_position(rhs._trigger_position) {
    typedef rtx_channel chan_t;
    // Create a unique_ptr for safety reasons: If any of the assignment
    // operators of the channels fails, we must release this memory.
    auto channels = std::unique_ptr<chan_t[]>(new chan_t[this->_cnt_channels]);
    std::copy(rhs._channels, rhs._channels + rhs._cnt_channels, channels.get());
    this->_channels = channels.release();
}


/*
 * ...::rtx_instrument_configuration::rtx_instrument_configuration
 */
PWROWG_NAMESPACE::rtx_instrument_configuration::rtx_instrument_configuration(
        _Inout_ rtx_instrument_configuration&& rhs) noexcept
    : _acquisition(std::move(rhs._acquisition)),
        _beep_on_apply(rhs._beep_on_apply),
        _beep_on_error(rhs._beep_on_error),
        _beep_on_trigger(rhs._beep_on_trigger),
        _channels(rhs._channels),
        _cnt_channels(rhs._cnt_channels),
        _min_time_base(rhs._min_time_base),
        _reference_position(rhs._reference_position),
        _slave(rhs._slave),
        _timeout(rhs._timeout),
        _time_range(std::move(rhs._time_range)),
        _trigger(std::move(rhs._trigger)),
        _trigger_position(std::move(rhs._trigger_position)){
    rhs._channels = nullptr;
    rhs._cnt_channels = 0;
}


/*
 * ...::rtx_instrument_configuration::rtx_instrument_configuration
 */
PWROWG_NAMESPACE::rtx_instrument_configuration::rtx_instrument_configuration(
        _In_ const rtx_quantity time_range,
        _In_ const unsigned int samples,
        _In_ timeout_type timeout)
    : _beep_on_apply(0),
        _beep_on_error(false),
        _beep_on_trigger(false),
        _channels(nullptr),
        _cnt_channels(0),
        _min_time_base(0.0f),
        _reference_position(rtx_reference_point::middle),
        _slave(false),
        _timeout(0),
        _time_range(time_range),
        _trigger("EXT", "EDGE"),
        _trigger_position(0.0f) {
    this->_acquisition.points(samples).segmented(true);
    this->_trigger.external().mode(rtx_trigger_mode::automatic);
}


/*
 * ...::rtx_instrument_configuration::rtx_instrument_configuration
 */
PWROWG_NAMESPACE::rtx_instrument_configuration::rtx_instrument_configuration(
        _In_ const rtx_quantity time_range,
        _In_ const rtx_acquisition& acquisition,
        _In_ const rtx_trigger& trigger,
        _In_ timeout_type timeout)
    : _acquisition(acquisition),
        _beep_on_apply(0),
        _beep_on_error(false),
        _beep_on_trigger(false),
        _channels(nullptr),
        _cnt_channels(0),
        _min_time_base(0.0f),
        _reference_position(rtx_reference_point::middle),
        _slave(false),
        _timeout(timeout),
        _time_range(time_range),
        _trigger(trigger),
        _trigger_position(0.0f) {
    this->_acquisition.state(rtx_acquisition_state::unknown);
}


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * ...::rtx_instrument_configuration::rtx_instrument_configuration
 */
PWROWG_NAMESPACE::rtx_instrument_configuration::rtx_instrument_configuration(
        _In_ const rtx_instrument& instrument,
        _In_ const bool ignore_channels)
    : _acquisition(instrument.acquisition()),
        _beep_on_apply(0),
        _beep_on_error(false),
        _beep_on_trigger(false),
        _channels(nullptr),
        _cnt_channels(0),
        _min_time_base(instrument.automatic_roll_time()),
        _reference_position(instrument.reference_position()),
        _slave(false),
        _timeout(instrument.timeout()),
        _time_range(instrument.time_range()),
        _trigger(instrument.trigger()),
        _trigger_position(instrument.trigger_position()){
    typedef rtx_channel chan_t;
    std::vector<chan_t> channels;

    if (!instrument.automatic_roll()) {
        // We indicate automatic roll being disabled by negative numbers.
        this->_min_time_base *= -1.0f;
    }

    if (!ignore_channels) {
        // Probe the channels as there is no other way to find the number of
        // channels. The instrument does the counting the same way, but as we
        // would need to do the same queries anyway, we can fail here instread
        // of enumerating everything twice.
        for (std::size_t i = 1; true; ++i) {
            try {
                channels.push_back(instrument.channel(i));
            } catch (...) {
                // Clear any error state from the failed call before.
                instrument.query("*CLS; *OPC?\n");
                break;
            }
        }
    }

    if (!channels.empty()) {
        // As the copy of a single channel might throw, protect the memory
        // via a unqiue_ptr until done.
        std::unique_ptr<chan_t[]> channels1(new chan_t[channels.size()]);
        std::copy(channels.begin(), channels.end(), channels1.get());
        this->_channels = channels1.release();
        this->_cnt_channels = channels.size();
    }
}
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */


/*
 * ...::rtx_instrument_configuration::~rtx_instrument_configuration
 */
PWROWG_NAMESPACE::rtx_instrument_configuration::~rtx_instrument_configuration(
        void) {
    delete[] this->_channels;
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::acquisition
 */
const PWROWG_NAMESPACE::rtx_acquisition&
PWROWG_NAMESPACE::rtx_instrument_configuration::acquisition(
        void) const noexcept {
    return this->_acquisition;
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::as_slave
 */
PWROWG_NAMESPACE::rtx_instrument_configuration
PWROWG_NAMESPACE::rtx_instrument_configuration::as_slave(
        _In_ const std::size_t beep,
        _In_ const rtx_quantity& level,
        _In_ const rtx_trigger_slope slope) const {
    rtx_instrument_configuration retval(*this);
    retval._slave = true;
    retval._trigger.external(level, slope);
    retval._beep_on_apply = beep;
    return retval;
}


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::apply
 */
void PWROWG_NAMESPACE::rtx_instrument_configuration::apply(
        _Inout_ rtx_instrument& instrument) const {
    // Change the timeout before perfoming any operations that might time out.
    if (this->_timeout > 0) {
        instrument.timeout(this->_timeout);
    }

    // The effective TIM:ROLL:MTIM to set. If automatic roll is enabled, we use
    // the instrument default of half a second.
    const auto roll = (this->_min_time_base > 0.0f);
    const auto mtim = (this->_min_time_base == 0.0f)
        ? (std::numeric_limits<float>::max)()
        : std::abs(this->_min_time_base);

    // If there are per-channel settings, apply them as well. Note that the
    // pointer may be non-null while there are zero channels. This is perfectly
    // legal and all data in '_channels' should be ignored in this case.
    if (this->_channels != nullptr) {
        for (std::size_t i = 0; i < this->_cnt_channels; ++i) {
            instrument.channel(this->_channels[i]);
        }
    }

    // Note that the triggers must be configured *after* the channels, because
    // the trigger level can only be within the configured vertical range of the
    // respective channel.
    instrument.time_range(this->_time_range)
        .trigger_output(rtx_trigger_output::pulse)
        .reference_position(this->_reference_position)
        .automatic_roll(roll)
        .automatic_roll_time(mtim)
        .trigger(this->_trigger)
        .trigger_position(this->_trigger_position)
        .acquisition(this->_acquisition, false);

    // Wait until the instrument has applied all of the before settings.
    instrument.operation_complete();

    // Note: Beep will do nothing if the count is zero.
    instrument.beep(this->_beep_on_apply);
}
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::beep_on_apply
 */
PWROWG_NAMESPACE::rtx_instrument_configuration&
PWROWG_NAMESPACE::rtx_instrument_configuration::beep_on_apply(
        _In_ const std::size_t count) noexcept {
    this->_beep_on_apply = count;
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::beep_on_error
 */
PWROWG_NAMESPACE::rtx_instrument_configuration&
PWROWG_NAMESPACE::rtx_instrument_configuration::beep_on_error(
        _In_ const bool enable) noexcept {
    this->_beep_on_error = enable;
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::beep_on_trigger
 */
PWROWG_NAMESPACE::rtx_instrument_configuration&
PWROWG_NAMESPACE::rtx_instrument_configuration::beep_on_trigger(
        _In_ const bool enable) noexcept {
    this->_beep_on_trigger = enable;
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::channel
 */
PWROWG_NAMESPACE::rtx_instrument_configuration&
PWROWG_NAMESPACE::rtx_instrument_configuration::channel(
        _In_ const rtx_channel& channel) {
    // If we already have channels, make sure that each channel is configured
    // only once and overwrite any existing configuration for the same channel.
    if (this->_channels != nullptr) {
        for (std::size_t i = 0; i < this->_cnt_channels; ++i) {
            if (this->_channels[i].channel() == channel.channel()) {
                this->_channels[i] = channel;
                return *this;
            }
        }
    }
    // At this point, we know that we do not know 'channel'.

    auto old = this->_channels;
    this->_channels = new rtx_channel[this->_cnt_channels + 1];

    // Copy the existing channels and delete them.
    std::copy(old, old + this->_cnt_channels, this->_channels);
    delete[] old;

    // Append the new one.
    this->_channels[this->_cnt_channels++] = channel;

    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::channels
 */
std::size_t PWROWG_NAMESPACE::rtx_instrument_configuration::channels(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) rtx_channel *dst,
        _In_ const std::size_t cnt) const {
    if (dst != nullptr) {
        std::copy(this->_channels,
            this->_channels + (std::min)(cnt, this->_cnt_channels),
            dst);
    }

    return this->_cnt_channels;
}


/*
 * ...::rtx_instrument_configuration::disable_automatic_roll
 */
PWROWG_NAMESPACE::rtx_instrument_configuration&
PWROWG_NAMESPACE::rtx_instrument_configuration::disable_automatic_roll(
        void) noexcept {
    this->_min_time_base = -std::abs(this->_min_time_base);
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::enable_automatic_roll
 */
PWROWG_NAMESPACE::rtx_instrument_configuration&
PWROWG_NAMESPACE::rtx_instrument_configuration::enable_automatic_roll(
        void) noexcept {
    this->_min_time_base = std::abs(this->_min_time_base);

    if (this->_min_time_base == 0.0f) {
        // If force disable was selected before, apply the default value for
        // RTA/RTB instruments as we cannot discover that roll should be enabled
        // otherwise.
        this->_min_time_base = 0.5f;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::ignore_channel
 */
PWROWG_NAMESPACE::rtx_instrument_configuration&
PWROWG_NAMESPACE::rtx_instrument_configuration::ignore_channel(
        _In_ const std::uint32_t channel) {
    auto end = this->_channels + this->_cnt_channels;
    auto it = std::remove_if(this->_channels, end,
            [channel](const rtx_channel& c) {
        return (c.channel() == channel);
    });

    if (it != end) {
        // Something has been removed. Note that we do not reallocate in this
        // case as this is a rare use case and the amount of rubbish that we
        // will keep unti something is added or everything is erased is small.
        --this->_cnt_channels;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::ignore_all_channels
 */
PWROWG_NAMESPACE::rtx_instrument_configuration&
PWROWG_NAMESPACE::rtx_instrument_configuration::ignore_all_channels(
        void) noexcept {
    delete[] this->_channels;
    this->_channels = nullptr;
    this->_cnt_channels = 0;
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::operator =
 */
PWROWG_NAMESPACE::rtx_instrument_configuration&
PWROWG_NAMESPACE::rtx_instrument_configuration::operator =(
        _In_ const rtx_instrument_configuration& rhs) {
    if (this != std::addressof(rhs)) {
        this->_acquisition = rhs._acquisition;
        this->_beep_on_apply = rhs._beep_on_apply;
        this->_beep_on_error = rhs._beep_on_error;
        this->_beep_on_trigger = rhs._beep_on_trigger;

        delete[] this->_channels;
        this->_channels = new rtx_channel[rhs._cnt_channels];
        std::copy(rhs._channels,
            rhs._channels + rhs._cnt_channels,
            this->_channels);

        this->_cnt_channels = rhs._cnt_channels;
        this->_min_time_base = rhs._min_time_base;
        this->_reference_position = rhs._reference_position;
        this->_slave = rhs._slave;
        this->_timeout = rhs._timeout;
        this->_time_range = rhs._time_range;
        this->_trigger = rhs._trigger;
        this->_trigger_position = rhs._trigger_position;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_instrument_configuration::operator =
 */
PWROWG_NAMESPACE::rtx_instrument_configuration&
PWROWG_NAMESPACE::rtx_instrument_configuration::operator =(
        _Inout_ rtx_instrument_configuration&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_acquisition = std::move(rhs._acquisition);
        this->_beep_on_apply = rhs._beep_on_apply;
        this->_beep_on_error = rhs._beep_on_error;
        this->_beep_on_trigger = rhs._beep_on_trigger;

        delete[] this->_channels;
        this->_channels = rhs._channels;
        rhs._channels = nullptr;

        this->_cnt_channels = rhs._cnt_channels;
        rhs._cnt_channels = 0;

        this->_min_time_base = rhs._min_time_base;
        this->_reference_position = rhs._reference_position;
        this->_slave = rhs._slave;
        this->_timeout = rhs._timeout;
        this->_time_range = std::move(rhs._time_range);
        this->_trigger = std::move(rhs._trigger);
        this->_trigger_position = std::move(rhs._trigger_position);
    }

    return *this;
}
