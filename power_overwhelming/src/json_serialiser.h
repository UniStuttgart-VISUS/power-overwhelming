// <copyright file="json_serialiser.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <type_traits>

#include <nlohmann/json.hpp>

#include "power_overwhelming/convert_string.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// (Empty) JSON serialiser for <see cref="TType" />.
    /// </summary>
    /// <typeparam name="TType">The type to be serialised.</typeparam>
    /// <typeparam name="IsArithmetic">Indicates whether the type can be treated
    /// as built-in arithmetic type.</typeparam>
    /// <typeparam name="IsEnum">Indicates whether the type is an enumeration
    /// that needs to be serialised by means of its underlying numeric type.
    /// </typeparam>
    template<class TType,
        bool IsArithmetic = std::is_arithmetic<TType>::value,
        bool IsEnum = std::is_enum<TType>::value>
    struct json_serialiser final {
        //static_assert(false, "A type that requires a specialisation for JSON "
        //    "serialisation is being serialised, but the specialisation of "
        //    "json_serialiser is missing.");
    };

    /// <summary>
    /// Specialisation for serialising arithmetic types.
    /// </summary>
    /// <typeparam name="TType"></typeparam>
    template<class TType>
    struct json_serialiser<TType, true, false> final {
        typedef TType value_type;

        static inline value_type deserialise(_In_ const nlohmann::json& json) {
            return json.get<value_type>();
        }

        static inline value_type serialise(_In_ const value_type value) {
            return value;
        }
    };

    /// <summary>
    /// Specialisation for serialising enum values to JSON.
    /// </summary>
    /// <typeparam name="TEnum">The type of the enum.</typeparam>
    template<class TEnum>
    struct json_serialiser<TEnum, false, true> final {
        typedef typename std::underlying_type<TEnum>::type integral_type;
        typedef TEnum value_type;

        static inline value_type deserialise(_In_ const nlohmann::json& json) {
            return static_cast<value_type>(json.get<integral_type>());
        }

        static inline integral_type serialise(_In_ const value_type value) {
            return static_cast<integral_type>(value);
        }
    };

    /// <summary>
    /// Specialisation for strings.
    /// </summary>
    template<> struct json_serialiser<std::string, false, false> final {
        typedef std::string value_type;

        static inline value_type deserialise(_In_ const nlohmann::json& json) {
            return json.get<value_type>();
        }

        static inline const value_type& serialise(
                _In_ const value_type& value) {
            return value;
        }
    };

    /// <summary>
    /// Specialisation for strings.
    /// </summary>
    template<> struct json_serialiser<std::wstring, false, false> final {
        static inline std::wstring deserialise(
                _In_ const nlohmann::json& json) {
            auto retval = json.get<std::string>();
            return power_overwhelming::convert_string<wchar_t>(retval);
        }

        static inline const std::string serialise(
                _In_ const std::wstring& value) {
            return power_overwhelming::convert_string<char>(value);
        }
    };

    /// <summary>
    /// Specialisation for C-style strings.
    /// </summary>
    template<> struct json_serialiser<const char *, false, false> final {
        typedef std::string value_type;

        static inline value_type deserialise(_In_ const nlohmann::json& json) {
            return json.get<value_type>();
        }

        static inline value_type serialise(_In_z_ const char *value) {
            return (value != nullptr) ? value : "";
        }
    };

    /// <summary>
    /// Specialisation for C-style strings.
    /// </summary>
    template<> struct json_serialiser<const wchar_t *, false, false> final {
        static inline std::wstring deserialise(
                _In_ const nlohmann::json& json) {
            auto retval = json.get<std::string>();
            return power_overwhelming::convert_string<wchar_t>(retval);
        }

        static inline std::string serialise(_In_z_ const wchar_t *value) {
            return power_overwhelming::convert_string<char>(value);
        }
    };

    /// <summary>
    /// Specialisation for statically sized C-style strings of length
    /// <typeparamref name="Length" />.
    /// </summary>
    template<std::size_t Length>
    struct json_serialiser<char (&)[Length], false, false> final {
        typedef std::string value_type;

        static inline value_type deserialise(_In_ const nlohmann::json &json) {
            return json.get<value_type>();
        }

        static inline value_type serialise(_In_ const char (&value)[Length]) {
            return std::string(value, value + Length);
        }
    };

    /// <summary>
    /// Redirect references to <see cref="json_serialiser" /> for
    /// <typeparamref name="TType" />.
    /// </summary>
    template<class TType, bool IsArithmetic, bool IsEnum>
    struct json_serialiser<TType&, IsArithmetic, IsEnum> final {
        typedef json_serialiser<typename std::decay<TType>::type> serialiser;

        static inline auto deserialise(_In_ const nlohmann::json& json)
                -> decltype(serialiser::deserialise(json)) {
            return serialiser::deserialise(json);
        }

        static inline auto serialise(_In_ TType& value)
                -> decltype(serialiser::serialise(value)) {
            return serialiser::serialise(value);
        }
    };

    /// <summary>
    /// Deserialise the contents of a JSON field as
    ///  <typeparamref name="TType" />.
    /// </summary>
    /// <typeparam name="TType"></typeparam>
    /// <param name="json"></param>
    /// <returns></returns>
    template<class TType>
    inline auto json_deserialise(_In_ const nlohmann::json& json)
            -> decltype(json_serialiser<TType>::deserialise(json)) {
        typedef json_serialiser<TType> serialiser_type;
        return serialiser_type::deserialise(json);
    }

    /// <summary>
    /// Convert <typeparamref name="TType" /> to its JSON representation.
    /// </summary>
    template<class TType>
    inline nlohmann::json json_serialise(_In_ TType&& value) {
        typedef json_serialiser<TType> serialiser_type;
        return serialiser_type::serialise(std::forward<TType>(value));
    }

    /// <summary>
    /// Serialise <paramref name="value" /> into a field with the specified
    /// <paramef name="name" />.
    /// </summary>
    /// <typeparam name="TType"></typeparam>
    /// <param name="name"></param>
    /// <param name="value"></param>
    /// <returns></returns>
    template<class TType> inline nlohmann::json json_serialise(
            _In_z_ const char *name, _In_ TType&& value) {
        return { name, json_serialise(std::forward<TType>(value)) };
    }

    /// <summary>
    /// Loads JSON from the file at the specified location.
    /// </summary>
    /// <param name="path"></param>
    extern nlohmann::json load_json(_In_z_ const wchar_t *path);

    /// <summary>
    /// Saves the given JSON to the file at the specified location.
    /// </summary>
    /// <param name="json"></param>
    /// <param name="path"></param>
    extern void save_json(_In_ const nlohmann::json& json,
        _In_z_ const wchar_t *path);

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
