// <copyright file="sensor_registry.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::basic_sensor_registry<TSensors...>::descriptions
 */
template<class... TSensors>
std::size_t
PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const sensor_array_configuration_impl& config) {
    return descriptions0(dst, cnt, type_list<TSensors...>(), config);
}


/*
 * PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::configure0
 */
template<class ...TSensors>
template<class T, class... Ts>
void PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::configure0(
        _In_ type_list<T, Ts...>,
        _In_ sensor_array_configuration_impl& config) {
    typedef T sensor_type;
    typedef typename sensor_type::configuration_type config_type;

    // Sanity check. This is really important as there is a high probability that
    // people copy & paste sensors configurations.
    auto it = config.sensor_configs.find(config_type::id);
    if (it != config.sensor_configs.end()) {
        auto id = config_type::id.to_string<char>();
        auto msg = format_string("A configuration with ID %s has already been "
            "registered. This is a bug in the definition of a sensor "
            "configuration which needs to be fixed by assigning unique GUIDs "
            "to all sensor configuration types.", id.c_str());
        throw std::logic_error(msg);
    }

    // Create the configuration object to 'T'.
    config.sensor_configs[config_type::id] = std::make_unique<config_type>();

    // Configure the rest.
    configure0(type_list<Ts...>(), config);
}


/*
 * PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::create0
 */
template<class ...TSensors>
template<std::size_t I, class TInput, class T, class... Ts>
TInput PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::create0(
        _In_ sensor_list_type& dst,
        _In_ type_list<T, Ts...>,
        _In_ const std::size_t index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const sensor_array_impl *owner,
        _In_ const sensor_array_configuration_impl& config) {
    typedef typename T::configuration_type config_type;
    typedef T sensor_type;

    if (owner == nullptr) {
        throw std::invalid_argument("A valid owner must be provided for all "
            "sensors.");
    }

    auto c = config.find_sensor_config(config_type::id);
    if (c == nullptr) {
        throw std::invalid_argument("The configuration for the sensor class to "
            "create was not found. Make sure to pass the same array "
            "configuration for all calls.");
    }

    auto& sensors = std::get<I>(dst);
    const auto it = sensor_type::from_descriptions(sensors,
        index,
        begin,
        end,
        owner,
        *static_cast<const config_type *>(c));
    const auto i = std::distance(begin, it);

    return create0<I + 1>(dst, type_list<Ts...>(), index + i, it, end, owner,
        config);
}


/*
 * PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::descriptions0
 */
template<class ...TSensors>
template<class T, class... Ts>
std::size_t
PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::descriptions0(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ type_list<T, Ts...>,
        _In_ const sensor_array_configuration_impl& config) {
    static_assert(has_async_sample<T>::value || has_sync_sample<T>::value,
        "A sensor must either have a synchronous or asynchronous method for "
        "sampling.");
    typedef T sensor_type;
    typedef typename sensor_type::configuration_type config_type;
    std::size_t retval = 0;

    // If we have the configuration, create the descriptions for 'T'.
    auto it = config.sensor_configs.find(config_type::id);
    if (it != config.sensor_configs.end()) {
        auto c = static_cast<const config_type *>(it->second.get());
        retval = sensor_type::descriptions(dst, cnt, *c);

        if (retval < cnt) {
            dst += retval;
            cnt -= retval;
        } else {
            cnt = 0;
        }
    }

    // Create the descriptions for the rest.
    retval += descriptions0(dst, cnt, type_list<Ts...>(), config);

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::descriptions0
 */
template<class... TSensors>
std::size_t
PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::descriptions0(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ type_list<>,
        _In_ const sensor_array_configuration_impl& config) {
    return 0;
}


/*
 * PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::sample0
 */
template<class... TSensors>
template<class TOutput, std::size_t Index, std::size_t... Indices>
void PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::sample0(
        _In_ TOutput oit,
        _In_ std::index_sequence<Index, Indices...>,
        _In_ sensor_list_type& sensor_lists,
        _In_ const bool enable) {
    auto& list = std::get<Index>(sensor_lists);

    // Derive which type of sensor we are processing.
    typedef std::decay_t<decltype(list)>::value_type sensor_type;

    // Try to sample the sensors of type 'sensor_type' asynchronously. If that
    // fails, create a sampler function to 'oit'.
    const auto async = sample1<sensor_type>(list.begin(), list.end(), enable);

    if (!async) {
        std::transform(list.begin(),
            list.end(),
            oit,
            make_sampler<sensor_type>);
    }

    // Process the remaining sensors.
    sample0(oit, std::index_sequence<Indices...>(), sensor_lists, enable);
}


/*
 * PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::sample1
 */
template<class... TSensors>
template<class T, class TInput>
std::enable_if_t<PWROWG_DETAIL_NAMESPACE::has_async_sample<T>::type::value,
    bool>
PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::sample1(
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const bool enable) {
    for (auto it = begin; it != end; ++it) {
        it->sample(enable);
    }

    return true;
}
