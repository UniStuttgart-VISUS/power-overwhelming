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
#include <cassert>
#include <functional>
#include <limits>
#include <type_traits>
#include <vector>

#include "visus/pwrowg/sensor_type.h"

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
/// Creates a telemetry callback type using the given context parameters, which
/// is used to wrap user defined callbacks (typically lambdas) to be invoked
/// for telemetry items.
/// </summary>
/// <typeparam name="TCtxs">An optional set of context types passed to the
/// callback following the telemetry item.</typeparam>
template<class... TCtxs> using igctl_telemetry_disp
    = std::function<void(const ctl_oc_telemetry_item_t&, TCtxs&&...)>;


/// <summary>
/// Searches the position of the data type of the given telemetry
/// <paramref name="item" /> in the given dispatcher list
/// <paramref name="disps" />.
/// </summary>
/// <typeparam name="TContainer">The type of the container holding the
/// dispatchers, which must be a vector or an array of the same size as the
/// LUT created by <see cref="make_igcl_data_type_list" />.</typeparam>
/// <param name="lut"></param>
/// <param name="item"></param>
/// <returns></returns>
/// <exception cref="std::invalid_argument">If the data type of the given
/// telemetry item is unsupported.</exception>
template<class TContainer>
typename const TContainer::value_type& find_igcl_telemetry_disp(
    _In_ const TContainer& disps,
    _In_ const ctl_oc_telemetry_item_t& item);


/// <summary>
/// Creates a vector of dispatcher functions invoking the given
/// <paramref name="callback" /> for each of the given data
/// <paramref name="Types" />.
/// </summary>
/// <typeparam name="TCallback">The type of the callback to be invoked. This
/// callback must accept an <see langword="auto" /> parameter as its first
/// parameter and <see cref="ctl_units_t" /> as its second one. If any
/// <typeparamref nmae="TCtxs" /> is specified, these context parameters follow
/// in that order.</typeparam>
/// <typeparam name="TCtxs">The types of a set of optional parameters passed to
/// the callback.</typeparam>
/// <typeparam name="Types">The types to consider when dispatching.</typeparam>
/// <param name="callback">The callback (template) to be invoked.</param>
/// <returns>The list of dispatchers in order of <typeparamref name="Types" />.
/// </returns>
template<class... TCtxs, class TCallback, ctl_data_type_t... Types>
inline std::vector<igctl_telemetry_disp<TCtxs...>> make_igcl_telemetry_disps(
        _In_ const TCallback callback,
        const igcl_data_type_dispatch_list<Types...>) {
    return std::vector<igctl_telemetry_disp<TCtxs...>> {
        ([callback](const ctl_oc_telemetry_item_t& item, TCtxs&&... ctxs) {
            callback(igcl_data_type_traits<Types>::get(item),
                item.units,
                std::forward<TCtxs>(ctxs)...);
        })...
    };
}


/// <summary>
/// Creates a vector of dispatcher functions for all data types in
/// <see cref="igcl_telemetry_data_type_dispatch_list" />.
/// </summary>
/// <typeparam name="TCallback"></typeparam>
/// <typeparam name="TCtxs"></typeparam>
/// <param name="callback"></param>
/// <returns></returns>
template<class... TCtxs, class TCallback>
inline std::vector<igctl_telemetry_disp<TCtxs...>> make_igcl_telemetry_disps(
        _In_ TCallback&& callback) {
    return make_igcl_telemetry_disps<TCtxs...>(
        std::forward<TCallback>(callback),
        igcl_telemetry_data_type_dispatch_list());
}


/// <summary>
/// Create a LUT indexing <typeparamref name="Types" /> by the order they are
/// given.
/// </summary>
template<ctl_data_type_t... Types>
inline constexpr std::array<ctl_data_type_t, sizeof...(Types)>
make_igcl_data_type_list(const igcl_data_type_dispatch_list<Types...>) {
    return std::array<ctl_data_type_t, sizeof...(Types)> { Types... };
}


/// <summary>
/// Creates a LUT indexing all data types in
/// <see cref="igcl_telemetry_data_type_dispatch_list" />.
/// </summary>
/// <returns></returns>
inline constexpr auto make_igcl_data_type_list(void)
        -> decltype(make_igcl_data_type_list(
        igcl_telemetry_data_type_dispatch_list())) {
    return make_igcl_data_type_list(igcl_telemetry_data_type_dispatch_list());
}


/// <summary>
/// A traits type that allows for dispatching IGCL units. All units without a
/// template specialisation are unsupported by Power Overwhelming.
/// </summary>
/// <typeparam name="Unit">The unit being described.</typeparam>
template<ctl_units_t Unit> struct igcl_unit_traits final { 
    static constexpr auto supported = false;
    static constexpr auto type = sensor_type::unknown;
    static constexpr auto unit = Unit;

    template<class TType>
    static constexpr TType convert(_In_ const TType value) noexcept {
        return value;
    }
};

/// <summary>
/// Specialisation for <see cref="CTL_UNITS_VOLTAGE_VOLTS" />.
/// </summary>
template<> struct igcl_unit_traits<CTL_UNITS_VOLTAGE_VOLTS> final {
    static constexpr auto supported = true;
    static constexpr auto type = sensor_type::voltage;
    static constexpr auto unit = CTL_UNITS_VOLTAGE_VOLTS;

    template<class TType>
    static constexpr TType convert(_In_ const TType value) noexcept {
        return value;
    }
};

/// <summary>
/// Specialisation for <see cref="CTL_UNITS_VOLTAGE_MILLIVOLTS" />.
/// </summary>
template<> struct igcl_unit_traits<CTL_UNITS_VOLTAGE_MILLIVOLTS> final {
    static constexpr auto supported = true;
    static constexpr auto type = sensor_type::voltage;
    static constexpr auto unit = CTL_UNITS_VOLTAGE_MILLIVOLTS;

    template<class TType>
    static constexpr TType convert(_In_ const TType value) noexcept {
        return value / static_cast<TType>(1000);
    }
};

/// <summary>
/// Specialisation for <see cref="CTL_UNITS_POWER_WATTS" />.
/// </summary>
template<> struct igcl_unit_traits<CTL_UNITS_POWER_WATTS> final {
    static constexpr auto supported = true;
    static constexpr auto type = sensor_type::power;
    static constexpr auto unit = CTL_UNITS_POWER_WATTS;

    template<class TType>
    static constexpr TType convert(_In_ const TType value) noexcept {
        return value;
    }
};

/// <summary>
/// Specialisation for <see cref="CTL_UNITS_POWER_MILLIWATTS" />.
/// </summary>
template<> struct igcl_unit_traits<CTL_UNITS_POWER_MILLIWATTS> final {
    static constexpr auto supported = true;
    static constexpr auto type = sensor_type::power;
    static constexpr auto unit = CTL_UNITS_POWER_MILLIWATTS;

    template<class TType>
    static constexpr TType convert(_In_ const TType value) noexcept {
        return value / static_cast<TType>(1000);
    }
};

/// <summary>
/// Specialisation for <see cref="CTL_UNITS_ENERGY_JOULES" />.
/// </summary>
template<> struct igcl_unit_traits<CTL_UNITS_ENERGY_JOULES> final {
    static constexpr auto supported = true;
    static constexpr auto type = sensor_type::energy;
    static constexpr auto unit = CTL_UNITS_ENERGY_JOULES;

    template<class TType>
    static constexpr TType convert(_In_ const TType value) noexcept {
        return value;
    }
};

/// <summary>
/// Specialisation for <see cref="CTL_UNITS_TEMPERATURE_CELSIUS" />.
/// </summary>
template<> struct igcl_unit_traits<CTL_UNITS_TEMPERATURE_CELSIUS> final {
    static constexpr auto supported = true;
    static constexpr auto type = sensor_type::temperature;
    static constexpr auto unit = CTL_UNITS_TEMPERATURE_CELSIUS;

    template<class TType>
    static constexpr TType convert(_In_ const TType value) noexcept {
        return value;
    }
};


/// <summary>
/// A dispatch list for IGCL units.
/// </summary>
/// <typeparam name="Units">The unitsto be dispatched.</typeparam>
template<ctl_units_t... Units>
using igcl_unit_dispatch_list = dispatch_list<ctl_units_t, Units...>;


/// <summary>
/// A dispatch list for all units used in IGCL telemetry items.
/// </summary>
typedef igcl_unit_dispatch_list <
    CTL_UNITS_FREQUENCY_MHZ,
    CTL_UNITS_OPERATIONS_GTS,
    CTL_UNITS_OPERATIONS_MTS,
    CTL_UNITS_VOLTAGE_VOLTS,
    CTL_UNITS_POWER_WATTS,
    CTL_UNITS_TEMPERATURE_CELSIUS,
    CTL_UNITS_ENERGY_JOULES,
    CTL_UNITS_TIME_SECONDS,
    CTL_UNITS_MEMORY_BYTES,
    CTL_UNITS_ANGULAR_SPEED_RPM,
    CTL_UNITS_POWER_MILLIWATTS,
    CTL_UNITS_PERCENT,
    CTL_UNITS_MEM_SPEED_GBPS,
    CTL_UNITS_VOLTAGE_MILLIVOLTS,
    CTL_UNITS_BANDWIDTH_MBPS,
    CTL_UNITS_UNKNOWN>
    igcl_units_dispatch_list;


/// <summary>
/// Dispatches a traits pointer for the given <paramref name="unit" /> to the
/// given <typeparamref name="TCallback" /> template.
/// </summary>
template<class TCallback, ctl_units_t... Units>
bool dispatch_igcl_unit_traits(_In_ const ctl_units_t unit,
    _In_ const TCallback callback,
    igcl_unit_dispatch_list<Units...>);


/// <summary>
/// Dispatches a traits pointer for the given <paramref name="unit" /> to the
/// given <typeparamref name="TCallback" /> template.
/// </summary>
template<class TCallback> bool dispatch_igcl_unit_traits(
        _In_ const ctl_units_t unit,
        _In_ const TCallback callback) {
    return dispatch_igcl_unit_traits(unit, callback,
        igcl_units_dispatch_list());
}

/// <summary>
/// Dispatches a traits pointer for the unit of the given
///  <paramref name="telemetry" /> data to the given
///  <typeparamref name="TCllback" /> template.
/// </summary>
/// <typeparam name="TCallback"></typeparam>
/// <param name="telemetry"></param>
/// <param name="callback"></param>
/// <returns></returns>
template<class TCallback> bool dispatch_igcl_unit_traits(
        _In_ const ctl_oc_telemetry_item_t& telemetry,
        _In_ const TCallback callback) {
    return dispatch_igcl_unit_traits(telemetry.units, callback,
        igcl_units_dispatch_list());
}

PWROWG_DETAIL_NAMESPACE_END

#include "igcl_telemetry.inl"

#endif /* defined(POWER_OVERWHELMING_WITH_IGCL) */
#endif /* defined(_PWROWG_IGCL_TELEMETRY_H) */
