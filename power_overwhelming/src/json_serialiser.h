// <copyright file="json_serialiser.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
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
    struct json_serialiser { };

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
        typedef typename TEnum value_type;

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

        static inline const std::string& serialise(
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
        typedef typename std::decay<TType>::type value_type;
        typedef json_serialiser<value_type> serialiser_type;
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

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
