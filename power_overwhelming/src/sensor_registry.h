// <copyright file="sensor_registry.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_REGISTRY_H)
#define _PWROWG_SENSOR_REGISTRY_H
#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <list>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

#include "visus/pwrowg/guid.h"
#include "visus/pwrowg/sensor_array_configuration.h"
#include "visus/pwrowg/sensor_description.h"

#include "adl_sensor.h"
#include "detect_sample.h"
#include "emi_sensor.h"
#include "hmc8015_sensor.h"
#include "marker_sensor.h"
#include "msr_sensor.h"
#include "nvapi_sensor.h"
#include "nvml_sensor.h"
#include "powenetics_sensor.h"
#include "sensor_array_configuration_impl.h"
#include "string_functions.h"
#include "tinkerforge_sensor.h"
#include "type_list.h"
#include "usb_pd_sensor.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/* Forward declarations */
struct sensor_array_impl;


/// <summary>
/// The type of a sensor registry, which is the central location where all
/// sensors need to be registered in order to be available for use in a
/// sensor array.
/// </summary>
/// <remarks>
/// Implementors should add all their sensors in the <c>typedef</c>
/// <see cref="sensor_registry" /> below, which is used by the
/// <see cref="sensor_array" /> to enumerate all sensors.
/// </remarks>
/// <typeparam name="TSensors">The types of the sensors to be registered.
/// </typeparam>
template<class... TSensors> class basic_sensor_registry final {

public:

    /// <summary>
    /// The signature of a (synchronous) sampler function that retrieves one or
    /// more samples from a sensor to be delivered to the given callback.
    /// </summary>
    typedef std::function<void(const sensor_array_callback callback,
        const sensor_description *, void *context)> sampler_func;

    /// <summary>
    /// The type of sensors created by the registry.
    /// </summary>
    /// <remarks>
    /// A list is used here, because sensors do not have to be copyable or
    /// movable for this container to work.
    /// </remarks>
    typedef std::tuple<typename TSensors::list_type...> sensor_list_type;

    /// <summary>
    /// Adds the default configurations for all of
    /// <typeparamref name="TSensors" /> to the given <paramref name="config" />.
    /// </summary>
    /// <param name="config">An array configuration that should receive the
    /// sensor configuration instances. Not configurations must have been added
    /// to the array configuration before as it is a fatal error if a
    /// configuration ID is used multiple times.</param>
    /// <exception cref="std::logic_error">If a duplicate configuration ID was
    /// found. This can either be caused by passing a <paramref name="config" />
    /// that has already been configured, or by having sensor descriptions with
    /// conflicting ID values. Furthermore, it could be caused by adding the
    /// same sensor multiple times in the instantiation of the
    /// <see cref="basic_sensor_registry" />.</exception>
    static inline void configure(_In_ sensor_array_configuration_impl& config) {
        configure0(type_list<TSensors...>(), config);
    }

    /// <summary>
    /// Creates shared instances of all sensors configured in the range
    /// <paramref name="begin" /> to <paramref name="end" />.
    /// </summary>
    /// <typeparam name="TOutput">An output iterator over <c>shared_ptr</c> of
    /// <see cref="sensor"/>. The caller must not make any assumption on how
    /// many items will be written based on the input, so this must be
    /// something like a <c>back_insert_iterator</c>.</typeparam>
    /// <typeparam name="TInput">An iterator over
    /// <see cref="sensor_description" />s.</typeparam>
    /// <param name="oit">An output iterator to receive the sensors.</param>
    /// <param name="begin">The start of the range of sensor descriptions to
    /// create sensors for.</param>
    /// <param name="end">The end of the range of sensor descriptions.</param>
    /// <param name="owner">The sensor array owning the sensors to be created.
    /// This pointer is required to gain access to the callback pointers and
    /// the context data. It can also be used to access the per-sensor class
    /// configuration contained  in <paramref name="config" /> later on.</param>
    /// <param name="config">The array configuration, which holds the
    /// configuration data for the sensor classes. Note that this could be
    /// obtained from <paramref name="owner" /> in principle, but that would
    /// result in a cyclic dependency of includes, so we force the caller to
    /// perform the lookup for the call. The caller is the sensor array, which
    /// is not a template and therefore can resolve the cycle by making forward
    /// declarations and including only in its compilation unit.</param>
    /// <returns>The position of the first configuration that has not been used
    /// to create a sensor. If this is equal to <paramref name="end" />, all
    /// sensors have been successfully created.</returns>
    template<class TInput>
    static inline TInput create(_In_ sensor_list_type& dst,
            _In_ const TInput begin,
            _In_ const TInput end,
            _In_ const sensor_array_impl *owner,
            _In_ const sensor_array_configuration_impl& config) {
        return create0<0>(dst, type_list<TSensors...>(), 0, begin, end, owner,
            config);
    }

    /// <summary>
    /// Adds sensor descriptions for all registered sensors to
    /// <paramref name="oit" />.
    /// </summary>
    /// <typeparam name="TOutput"></typeparam>
    /// <param name="oit"></param>
    static std::size_t descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const sensor_array_configuration_impl& config);

    /// <summary>
    /// Starts (or stops) all of the <paramref name="sensors" /> that support
    /// asynchronous sampling and writes
    /// <see cref="sensor_array_impl::sampler_func" />s for all other ones to
    /// <paramref name="oit" />.
    /// </summary>
    /// <typeparam name="TOutput"></typeparam>
    /// <param name="oit"></param>
    /// <param name="sensors"></param>
    /// <param name="enable"></param>
    template<class TOutput> inline static void sample(_In_ TOutput oit,
            _In_ sensor_list_type& sensors,
            _In_ const bool enable) {
        sample0(oit,
            std::make_index_sequence<sizeof...(TSensors)>(),
            sensors,
            enable);
    }

    /// <summary>
    /// Answer the number of sensor types in the registry.
    /// </summary>
    /// <returns>The number of sensors in the registry.</returns>
    static inline constexpr std::size_t size(void) noexcept {
        return sizeof...(TSensors);
    }

    basic_sensor_registry(void) = delete;

private:

    /// <summary>
    /// Adds the per-sensor configurations to <paramref name="config" />.
    /// </summary>
    template<class T, class... Ts>
    static void configure0(_In_ type_list<T, Ts...>,
        _In_ sensor_array_configuration_impl& config);

    /// <summary>
    /// Recursion stop.
    /// </summary>
    inline static void configure0(_In_ type_list<>,
        _In_ sensor_array_configuration_impl &) { }

    /// <summary>
    /// Creates sensors for the description in range <paramref name="begin" />
    /// to <paramref name="end" /> and stores them in <paramref name="dst" />.
    /// </summary>
    template<std::size_t I, class TInput, class T, class... Ts>
    static TInput create0(_In_ sensor_list_type& dst,
        _In_ type_list<T, Ts...>,
        _In_ const sample::source_type index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const sensor_array_impl *owner,
        _In_ const sensor_array_configuration_impl& config);

    /// <summary>
    /// Recursion stop.
    /// </summary>
    template<std::size_t I, class TInput>
    static inline TInput create0(_In_ sensor_list_type& dst,
            _In_ type_list<>,
            _In_ const sample::source_type index,
            _In_ const TInput begin,
            _In_ const TInput end,
            _In_ const sensor_array_impl *owner,
            _In_ const sensor_array_configuration_impl& config) {
        return begin;
    }

    /// <summary>
    /// Counts the sensor descriptions for the known sensor classes and stores
    /// them to <paramref name="dst" /> if the buffer is large enough.
    /// </summary>
    template<class T, class... Ts>
    static std::size_t descriptions0(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ type_list<T, Ts...>,
        _In_ const sensor_array_configuration_impl& config);

    /// <summary>
    /// Recursion stop.
    /// </summary>
    static std::size_t descriptions0(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ type_list<>,
        _In_ const sensor_array_configuration_impl&);

    /// <summary>
    /// Creates a synchronous <see cref="sampler_func" /> for
    /// <paramref name="sensor" />.
    /// </summary>
    template<class T>
    static std::enable_if_t<detail::has_sync_sample<T>::type::value,
        sampler_func>
    make_sampler(_In_ T& sensor) {
        return [&sensor](_In_ const sensor_array_callback cb,
                _In_ const sensor_description *sensors,
                _In_opt_ void *ctx) {
            sensor.sample(cb, sensors, ctx);
        };
    }

    /// <summary>
    /// Creates an empty synchronous <see cref="sampler_func" />.
    /// </summary>
    template<class T>
    static std::enable_if_t<!detail::has_sync_sample<T>::type::value,
        sampler_func>
    make_sampler(_In_ T &sensor) {
        return [](_In_opt_ const sensor_array_callback cb,
                _In_opt_ const sensor_description *sensors,
                _In_opt_ void *ctx) {
            assert(false);
        };
    }

    template<class TOutput, std::size_t Index, std::size_t... Indices>
    static void sample0(_In_ TOutput oit,
        _In_ std::index_sequence<Index, Indices...>,
        _In_ sensor_list_type& sensor_lists,
        _In_ const bool enable);

    template<class TOutput>
    inline static void sample0(_In_ TOutput oit,
        _In_ std::index_sequence<>,
        _In_ sensor_list_type& sensor_lists,
        _In_ const bool enable) { }

    /// <summary>
    /// Tries to enable or disable asynchronously sampling
    /// <paramref name="begin" /> to <paramref name="end" /> or returns
    /// <c>false</c> if <typepararamref name="T"/> is a synchronous sensor.
    /// </summary>
    template<class T, class TInput>
    static std::enable_if_t<detail::has_async_sample<T>::type::value, bool>
    sample1(_In_ const TInput begin,
        _In_ const TInput end,
        _In_ const bool enable);

    /// <summary>
    /// Recursion stop.
    /// </summary>
    template<class T, class TInput>
    static std::enable_if_t<!detail::has_async_sample<T>::type::value, bool>
    sample1(_In_ const TInput begin,
            _In_ const TInput end,
            _In_ const bool enable) {
        return false;
    }
};


/// <summary>
/// The one and only sensor registry where all known sensors are registered.
/// </summary>
/// <remarks>
/// New sensor types must be added here in order to be supported by the
/// <see cref="sensor_array" />.
/// </remarks>
typedef basic_sensor_registry<
#if defined(_WIN32)
    // Windows-specific sensors
    emi_sensor,
    //nvapi_sensor,
    usb_pd_sensor,
#endif  /* defined(_WIN32) */

#if defined(POWER_OVERWHELMING_WITH_ADL)
    adl_sensor,
#endif /* defined(POWER_OVERWHELMING_WITH_ADL) */
    hmc8015_sensor,
    marker_sensor,
    msr_sensor,
#if defined(POWER_OVERWHELMING_WITH_NVML)
    nvml_sensor,
#endif /* defined(POWER_OVERWHELMING_WITH_NVML) */
#if defined(POWER_OVERWHELMING_WITH_POWENETICS)
    powenetics_sensor,
#endif /* defined(POWER_OVERWHELMING_WITH_POWENETICS) */
    //rtx_sensor,
    tinkerforge_sensor>
    sensor_registry;

PWROWG_DETAIL_NAMESPACE_END

#include "sensor_registry.inl"

#endif /* !defined(_PWROWG_SENSOR_REGISTRY_H) */
