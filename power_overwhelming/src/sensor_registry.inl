// <copyright file="sensor_registry.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::detail::basic_sensor_registry<TSensors...>::configure
 */
template<class ...TSensors>
void PWROWG_NAMESPACE::detail::basic_sensor_registry<TSensors...>::configure(
        _In_ sensor_array_configuration_impl& config) {
    configure0<TSensors...>(config);
}


/*
 * PWROWG_NAMESPACE::detail::basic_sensor_registry<TSensors...>::descriptions
 */
template<class ...TSensors>
std::vector<PWROWG_NAMESPACE::sensor_description>
PWROWG_NAMESPACE::detail::basic_sensor_registry<TSensors...>::descriptions(
        _In_ const sensor_array_configuration& config) {
    return std::vector<sensor_description>();
}


/*
 * PWROWG_NAMESPACE::detail::basic_sensor_registry<TSensors...>::configure0
 */
template<class ...TSensors>
template<class T, class... Ts>
void PWROWG_NAMESPACE::detail::basic_sensor_registry<TSensors...>::configure0(
        _In_ sensor_array_configuration_impl& config) {
    typedef typename T::configuration_type config_type;

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

    config.sensor_configs[config_type::id] = std::make_unique<config_type>();
}
