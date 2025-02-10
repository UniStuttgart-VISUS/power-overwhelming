// <copyright file="sensor_registry.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::configure
 */
template<class ...TSensors>
void PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::configure(
        _In_ sensor_array_configuration_impl& config) {
    configure0(type_list<TSensors...>(), config);
}


/*
 * PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::create
 */
template<class ...TSensors>
template<class TOutput, class TInput>
static TInput PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::create(
        _In_ TOutput oit, _In_ const TInput begin, _In_ const TInput end) {
    return create0(oit, type_list<TSensors...>(), 0, begin, end);
}


/*
 * PWROWG_NAMESPACE::basic_sensor_registry<TSensors...>::descriptions
 */
template<class... TSensors>
std::size_t PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::descriptions(
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
template<class TOutput, class TInput, class T, class... Ts>
TInput PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::create0(
        _In_ TOutput oit,
        _In_ type_list<T, Ts...>,
        _In_ const std::size_t index,
        _In_ const TInput begin,
        _In_ const TInput end) {
    typedef T sensor_type;

    const auto it = sensor_type::from_descriptions(oit, index, begin, end);
    const auto i = std::distance(begin, it);

    return create0(oit, type_list<Ts...>(), index + i, it, end);
}


/*
 * PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::descriptions0
 */
template<class ...TSensors>
template<class T, class... Ts>
std::size_t PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>
::descriptions0(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ type_list<T, Ts...>,
        _In_ const sensor_array_configuration_impl& config) {
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
std::size_t PWROWG_DETAIL_NAMESPACE::basic_sensor_registry<TSensors...>::descriptions0(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ type_list<>,
        _In_ const sensor_array_configuration_impl &config) {
    return 0;
}
