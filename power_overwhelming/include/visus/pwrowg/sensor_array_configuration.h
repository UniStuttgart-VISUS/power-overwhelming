// <copyright file="sensor_array_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_ARRAY_CONFIGURATION_H)
#define _PWROWG_SENSOR_ARRAY_CONFIGURATION_H
#pragma once

#include <functional>
#include <stdexcept>

#include "visus/pwrowg/api.h"

#include "visus/pwrowg/adl_configuration.h"


/* Forward declarations*/
PWROWG_DETAIL_NAMESPACE_BEGIN
template<class...> class basic_sensor_registry;
struct sensor_array_configuration_impl;
PWROWG_DETAIL_NAMESPACE_END


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// The configuration object used to contruct a <see cref="sensor_array" />.
/// </summary>
class POWER_OVERWHELMING_API sensor_array_configuration final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    sensor_array_configuration(void);

    /// <summary>
    /// Initialise a new instance from moving <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    inline sensor_array_configuration(
            _Inout_ sensor_array_configuration&& rhs) noexcept
            : _impl(rhs._impl) {
        rhs._impl = nullptr;
    }

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~sensor_array_configuration(void) noexcept;

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    sensor_array_configuration& operator =(
        _Inout_ sensor_array_configuration&& rhs) noexcept;

    /// <summary>
    /// Invokes <paramref name="config" /> for a configuration of type
    /// <typeparamref name="TConfig" /> if such a configuration is registered
    /// for any of the sensors.
    /// </summary>
    /// <typeparam name="TConfig">The type of the sensor configuration that is to
    /// be modified.</typeparam>
    /// <param name="configure">A callback that modifies the sensor
    /// configuration.</param>
    /// <param name="context">A user-defined context pointer passed to the
    /// <see cref="configure" /> callback if it is invoked.</param>
    /// <returns><c>*this</c>.</returns>
    template<class TConfig> sensor_array_configuration& configure(
        _In_ void (*configure)(_In_ TConfig&, _In_opt_ void *),
        _In_opt_ void *context);

    /// <summary>
    /// Invokes <paramref name="config" /> for a configuration of type
    /// <typeparamref name="TConfig" /> if such a configuration is registered
    /// for any of the sensors.
    /// </summary>
    /// <typeparam name="TConfig">The type of the sensor configuration that is to
    /// be modified.</typeparam>
    /// <param name="configure">A callback that modifies the sensor
    /// configuration.</param>
    /// <returns><c>*this</c>.</returns>
    template<class TConfig> sensor_array_configuration& configure(
        _In_ std::function<void(_In_ TConfig&)> configure);

    /// <summary>
    /// Gets, if available, the configuration of the specified type.
    /// </summary>
    /// <typeparam name="TConfig">The type of the sensor configuration to
    /// retrieve.</typeparam>
    /// <returns>The requested sensor configuration or <c>nullptr</c> if such a
    /// configuration is not registered.</returns>
    template<class TConfig>
    _Ret_maybenull_ const TConfig *configuration(void) const noexcept {
        return static_cast<const TConfig *>(this->find_config(TConfig::id));
    }

    /// <summary>
    /// Answer whether the configuration is valid.
    /// </summary>
    /// <returns><c>true</c> if the configuration is valid, <c>false</c> if it
    /// has been moved.</returns>
    inline operator bool(void) const noexcept {
        return (this->_impl != nullptr);
    }

private:

    typedef PWROWG_DETAIL_NAMESPACE::sensor_array_configuration_impl *impl_type;

    /// <summary>
    /// Check whether <see cref="_impl" /> is valid or throw
    /// <see cref="std::runtime_error" />.
    /// </summary>
    _Ret_valid_ impl_type check_not_disposed(void);

    /// <summary>
    /// Check whether <see cref="_impl" /> is valid or throw
    /// <see cref="std::runtime_error" />.
    /// </summary>
    _Ret_valid_ const impl_type check_not_disposed(void) const;

    /// <summary>
    /// Find the configuration object registered with the given
    /// <paramref name="id" />.
    /// </summary>
    void *find_config(_In_ const guid& id);

    /// <summary>
    /// Find the configuration object registered with the given
    /// <paramref name="id" />.
    /// </summary>
    const void *find_config(_In_ const guid& id) const;

    impl_type _impl;

    template<class...> friend class basic_sensor_registry;
    friend class sensor_array;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/sensor_array_configuration.inl"

#endif /* !defined(_PWROWG_SENSOR_ARRAY_CONFIGURATION_H) */

