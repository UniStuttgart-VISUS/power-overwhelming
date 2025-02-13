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

#include "visus/pwrowg/sensor_array_configuration.h"
#include "visus/pwrowg/sensor_description.h"

#include "adl_sensor.h"
#include "emi_sensor.h"
#include "msr_sensor.h"
#include "nvml_sensor.h"
#include "sensor_array_configuration_impl.h"
#include "sensor_list.h"
#include "string_functions.h"
#include "tinkerforge_sensor.h"
#include "type_list.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

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
    /// The signature of a sampler function.
    /// </summary>
    typedef std::function<void(const sensor_array_callback callback,
        void *context)> sampler_func;

    /// <summary>
    /// The type of sensors created by the registry.
    /// </summary>
    /// <remarks>
    /// A list is used here, because sensors do not have to be copyable or
    /// movable for this container to work.
    /// </remarks>
    typedef std::tuple<std::list<TSensors>...> sensor_list_type;

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
    /// <param name="config">The array configuration, which holds the
    /// configuration data for the sensor classes.</param>
    /// <returns>The position of the first configuration that has not been used
    /// to create a sensor. If this is equal to <paramref name="end" />, all
    /// sensors have been successfully created.</returns>
    template<class TInput>
    static inline TInput create(_In_ sensor_list_type& dst,
            _In_ const TInput begin,
            _In_ const TInput end,
            _In_ const sensor_array_configuration_impl& config) {
        return create0<0>(dst, type_list<TSensors...>(), 0, begin, end, config);
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
    /// Starts all of the <paramref name="sensors" /> that support asynchronous
    /// sampling and writes <see cref="sensor_array_impl::sampler_func" />s for
    /// all other ones to <paramref name="oit" />.
    /// </summary>
    /// <typeparam name="TOutput"></typeparam>
    /// <param name="oit"></param>
    /// <param name="sensors"></param>
    /// <param name="callback"></param>
    /// <param name="interval"></param>
    /// <param name="context"></param>
    template<class TOutput> static void sample(_In_ TOutput oit,
        _In_ sensor_list_type& sensors,
        _In_opt_ const sensor_array_callback callback,
        _In_ const std::chrono::milliseconds interval,
        _In_opt_ void *context);

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
        _In_ const std::size_t index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const sensor_array_configuration_impl& config);

    /// <summary>
    /// Recursion stop.
    /// </summary>
    template<std::size_t I, class TInput>
    static inline TInput create0(_In_ sensor_list_type& dst,
            _In_ type_list<>,
            _In_ const std::size_t index,
            _In_ const TInput begin,
            _In_ const TInput end,
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
        return [&sensor](const sensor_array_callback cb, void *ctx) {
            sensor.sample(cb, ctx);
        };
    }

    /// <summary>
    /// Creates an empty synchronous <see cref="sampler_func" />.
    /// </summary>
    template<class T>
    static std::enable_if_t<!detail::has_sync_sample<T>::type::value,
        sampler_func>
    make_sampler(_In_ T &sensor) {
        return [](const sensor_array_callback cb, void *ctx) {
            assert(false);
        };
    }

    template<class TOutput, std::size_t Index, std::size_t... Indices>
    static void sample0(_In_ TOutput oit,
        _In_ std::index_sequence<Index, Indices...>,
        _In_ sensor_list_type& sensor_lists,
        _In_opt_ const sensor_array_callback callback,
        _In_ const std::chrono::milliseconds interval,
        _In_opt_ void *context);

    template<class TOutput>
    inline static void sample0(_In_ TOutput oit,
        _In_ std::index_sequence<>,
        _In_ sensor_list_type& sensor_lists,
        _In_opt_ const sensor_array_callback callback,
        _In_ const std::chrono::milliseconds interval,
        _In_opt_ void *context) { }

    /// <summary>
    /// Tries asynchronously sampling <paramref name="begin" /> to
    /// <paramref name="end" /> or returns <c>false</c> if
    /// <typepararamref name="T"/> is a synchronous sensor.
    /// </summary>
    template<class T, class TInput>
    static std::enable_if_t<detail::has_async_sample<T>::type::value, bool>
    sample1(_In_ const TInput begin,
        _In_ const TInput end,
        _In_opt_ const sensor_array_callback callback,
        _In_ const std::chrono::milliseconds interval,
        _In_opt_ void *context);

    /// <summary>
    /// Recursion stop.
    /// </summary>
    template<class T, class TInput>
    static std::enable_if_t<!detail::has_async_sample<T>::type::value, bool>
    sample1(_In_ const TInput begin,
            _In_ const TInput end,
            _In_opt_ const sensor_array_callback callback,
            _In_ const std::chrono::milliseconds interval,
            _In_opt_ void *context) {
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
    //adl_sensor,
    //emi_sensor
    //hmc8015_sensor,
    //msr_sensor,
    //nvapi_sensor,
    nvml_sensor,
    //rtx_sensor,
    tinkerforge_sensor>
    //usb_pd_sensor>
    sensor_registry;

PWROWG_DETAIL_NAMESPACE_END

#include "sensor_registry.inl"

#endif /* !defined(_PWROWG_SENSOR_REGISTRY_H) */
