// <copyright file="igcl_telemetry.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_IGCL_TELEMETRY_H)
#define _PWROWG_IGCL_TELEMETRY_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_IGCL)

#include <array>
#include <functional>
#include <type_traits>
#include <vector>

#include "dispatch_list.h"
#include "igcl_library.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A traits type that allows for dispatching IGCL telemetry to strongly typed
/// callback templates.
/// </summary>
/// <typeparam name="Type">The type of the telemetry data.</typeparam>
template<ctl_data_type_t Type> struct igcl_data_type_traits;

/// <summary>
/// Specialisation for <see cref="CTL_DATA_TYPE_INT8" />.
/// </summary>
template<> struct igcl_data_type_traits<CTL_DATA_TYPE_INT8> final {
    typedef std::int8_t type;

    static inline type get(_In_ const ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.data8;
    }

    static inline type& get(_In_ ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.data8;
    }
};

/// <summary>
/// Specialisation for <see cref="CTL_DATA_TYPE_UINT8" />.
/// </summary>
template<> struct igcl_data_type_traits<CTL_DATA_TYPE_UINT8> final {
    typedef std::uint8_t type;

    static inline type get(_In_ const ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.datau8;
    }

    static inline type& get(_In_ ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.datau8;
    }
};

/// <summary>
/// Specialisation for <see cref="CTL_DATA_TYPE_INT16" />.
/// </summary>
template<> struct igcl_data_type_traits<CTL_DATA_TYPE_INT16> final {
    typedef std::int16_t type;

    static inline type get(_In_ const ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.data16;
    }

    static inline type& get(_In_ ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.data16;
    }
};

/// <summary>
/// Specialisation for <see cref="CTL_DATA_TYPE_UINT16" />.
/// </summary>
template<> struct igcl_data_type_traits<CTL_DATA_TYPE_UINT16> final {
    typedef std::uint16_t type;

    static inline type get(_In_ const ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.datau16;
    }

    static inline type& get(_In_ ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.datau16;
    }
};

/// <summary>
/// Specialisation for <see cref="CTL_DATA_TYPE_INT32" />.
/// </summary>
template<> struct igcl_data_type_traits<CTL_DATA_TYPE_INT32> final {
    typedef std::int32_t type;

    static inline type get(_In_ const ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.data32;
    }

    static inline type& get(_In_ ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.data32;
    }
};

/// <summary>
/// Specialisation for <see cref="CTL_DATA_TYPE_UINT32" />.
/// </summary>
template<> struct igcl_data_type_traits<CTL_DATA_TYPE_UINT32> final {
    typedef std::uint32_t type;

    static inline type get(_In_ const ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.datau32;
    }

    static inline type& get(_In_ ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.datau32;
    }
};

/// <summary>
/// Specialisation for <see cref="CTL_DATA_TYPE_INT64" />.
/// </summary>
template<> struct igcl_data_type_traits<CTL_DATA_TYPE_INT64> final {
    typedef std::int64_t type;

    static inline type get(_In_ const ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.data64;
    }

    static inline type& get(_In_ ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.data64;
    }
};

/// <summary>
/// Specialisation for <see cref="CTL_DATA_TYPE_UINT64" />.
/// </summary>
template<> struct igcl_data_type_traits<CTL_DATA_TYPE_UINT64> final {
    typedef std::uint64_t type;

    static inline type get(_In_ const ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.datau64;
    }

    static inline type& get(_In_ ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.datau64;
    }
};

/// <summary>
/// Specialisation for <see cref="CTL_DATA_TYPE_FLOAT" />.
/// </summary>
template<> struct igcl_data_type_traits<CTL_DATA_TYPE_FLOAT> final {
    typedef float type;

    static inline type get(_In_ const ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.datafloat;
    }

    static inline type& get(_In_ ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.datafloat;
    }
};

/// <summary>
/// Specialisation for <see cref="CTL_DATA_TYPE_DOUBLE" />.
/// </summary>
template<> struct igcl_data_type_traits<CTL_DATA_TYPE_DOUBLE> final {
    typedef double type;

    static inline type get(_In_ const ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.datadouble;
    }

    static inline type& get(_In_ ctl_oc_telemetry_item_t& item) noexcept {
        return item.value.datadouble;
    }
};

/// <summary>
/// Specialisation for <see cref="CTL_DATA_TYPE_STRING_ASCII" />.
/// </summary>
template<> struct igcl_data_type_traits<CTL_DATA_TYPE_STRING_ASCII> final {
    typedef char type;
};

/// <summary>
/// Specialisation for <see cref="CTL_DATA_TYPE_STRING_UTF16" />.
/// </summary>
template<> struct igcl_data_type_traits<CTL_DATA_TYPE_STRING_UTF16> final {
    typedef char16_t type;
};

/// <summary>
/// Specialisation for <see cref="CTL_DATA_TYPE_STRING_UTF132" />.
/// </summary>
template<> struct igcl_data_type_traits<CTL_DATA_TYPE_STRING_UTF132> final {
    typedef char32_t type;
};


/// <summary>
/// A dispatch list for IGCL data types.
/// </summary>
/// <typeparam name="Types">The types to be dispatched.</typeparam>
template<ctl_data_type_t... Types>
using igcl_data_type_dispatch_list = dispatch_list<ctl_data_type_t, Types...>;


/// <summary>
/// A dispatch list for all data types used in IGCL telemetry items. Types that
/// cannot be retrieved from <see cref="ctl_oc_telemetry_item_t" /> must not be
/// included in this list.
/// </summary>
typedef igcl_data_type_dispatch_list<
    CTL_DATA_TYPE_INT8,
    CTL_DATA_TYPE_UINT8,
    CTL_DATA_TYPE_INT16,
    CTL_DATA_TYPE_UINT16,
    CTL_DATA_TYPE_INT32,
    CTL_DATA_TYPE_UINT32,
    CTL_DATA_TYPE_INT64,
    CTL_DATA_TYPE_UINT64,
    CTL_DATA_TYPE_FLOAT,
    CTL_DATA_TYPE_DOUBLE>
    igcl_telemetry_data_type_dispatch_list;


/// <summary>
/// Creates a vector of dispatcher functions invoking the given
/// <paramref name="callback" /> for each of the given data
/// <paramref name="Types" />.
/// </summary>
/// <typeparam name="TCallback">The type of the callback to be invoked. This
/// callback must accept an <see langword="auto" /> parameter as its first
/// parameter and <see cref="ctl_units_t" /> as its second one.</typeparam>
/// <typeparam name="Types">The types to consider when dispatching.</typeparam>
/// <param name="callback">The callback (template) to be invoked.</param>
/// <returns>The list of dispatchers in order of <typeparamref name="Types" />.
/// </returns>
template<class TCallback, ctl_data_type_t... Types>
inline std::vector<std::function<void(const ctl_oc_telemetry_item_t&)>>
make_igcl_data_type_dispatchers(
        _In_ const TCallback callback,
        const igcl_data_type_dispatch_list<Types...>) {
    return std::vector<std::function<void(const ctl_oc_telemetry_item_t&)>> {
        ([callback](const ctl_oc_telemetry_item_t& item) {
            callback(igcl_data_type_traits<Types>::get(item), item.units);
        })...
    };
}


/// <summary>
/// Checks whether <paramref name="item" /> is supported and if it contains
/// any of the <typeparamref name="Types" />, invoke
/// <paramref name="callback" /> for that type.
/// </summary>
/// <typeparam name="TCallback"></typeparam>
/// <typeparam name="Types"></typeparam>
/// <param name="item"></param>
/// <param name="callback"></param>
/// <returns></returns>
template<class TCallback, ctl_data_type_t... Types>
bool visit(_In_ const ctl_oc_telemetry_item_t& item,
    _In_ const TCallback callback,
    const igcl_data_type_dispatch_list<Types...>);

/// <summary>
/// Invokes <paramref name="callback" /> for the data type in
/// <paramref name="item" /> if it contains valid data.
/// </summary>
/// <typeparam name="TCallback"></typeparam>
/// <param name="item"></param>
/// <param name="callback"></param>
/// <returns></returns>
template<class TCallback> inline bool visit(
        _In_ const ctl_oc_telemetry_item_t& item,
        _In_ const TCallback callback) {
    return visit(item, callback, igcl_telemetry_data_type_dispatch_list());
}

PWROWG_DETAIL_NAMESPACE_END

#include "igcl_telemetry.inl"

#endif /* defined(POWER_OVERWHELMING_WITH_IGCL) */
#endif /* defined(_PWROWG_IGCL_TELEMETRY_H) */
