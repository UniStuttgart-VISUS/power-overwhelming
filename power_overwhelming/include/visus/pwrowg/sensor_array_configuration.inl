// <copyright file="sensor_array_configuration.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::sensor_array_configuration::configure
 */
template<class TConfig>
inline PWROWG_NAMESPACE::sensor_array_configuration&
PWROWG_NAMESPACE::sensor_array_configuration::configure(
        _In_ void (*configure)(_In_ TConfig&, _In_opt_ void *),
        _In_opt_ void *context) {
    if (configure == nullptr) {
        throw std::invalid_argument("A valid configuration callback must be "
            "provided.");
    }

    auto config = this->find_config(TConfig::id);

    if (config != nullptr) {
        configure(*static_cast<TConfig *>(config), context);
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::sensor_array_configuration::configure
 */
template<class TConfig>
inline PWROWG_NAMESPACE::sensor_array_configuration&
PWROWG_NAMESPACE::sensor_array_configuration::configure(
        _In_ std::function<void(_In_ TConfig &)> configure) {
    if (!configure) {
        throw std::invalid_argument("A valid configuration callback must be "
            "provided.");
    }

    auto config = this->find_config(TConfig::id);

    if (config != nullptr) {
        configure(*static_cast<TConfig *>(config));
    }

    return *this;
}
