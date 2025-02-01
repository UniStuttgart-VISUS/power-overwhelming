// <copyright file="sensor_array_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_ARRAY_CONFIGURATION_H)
#define _PWROWG_SENSOR_ARRAY_CONFIGURATION_H
#pragma once

#include "visus/pwrowg/api.h"

#include "visus/pwrowg/adl_configuration.h"


/* Forward declarations*/
PWROWG_DETAIL_NAMESPACE_BEGIN
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

    sensor_array_configuration& configure(
        _In_ void (*configure)(_In_ adl_configuration&, _In_opt_ void *),
        _In_opt_ void *context);

    ///// <summary>
    ///// Configures the ADL sensors.
    ///// </summary>
    ///// <param name="configure"></param>
    ///// <returns></returns>
    //inline sensor_array_configuration& configure(
    //        _In_ std::function<void(adl_configuration&)> configure) {
    //    configure(this->_adl_configuration);
    //    return *this;
    //}

    ///// <summary>
    ///// Configures the Tinkerforge sensors.
    ///// </summary>
    ///// <param name="configure"></param>
    ///// <returns></returns>
    //inline sensor_array_configuration& configure(
    //        _In_ std::function<void(tinkerforge_configuration&)> configure) {
    //    configure(this->_tinkerforge_configuration);
    //    return *this;
    //}

private:

    typedef PWROWG_DETAIL_NAMESPACE::sensor_array_configuration_impl impl_type;

    impl_type& check_not_disposed(void);

    //const rtx_instrument &check_not_disposed(void) const;

    impl_type *_impl;

};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_ARRAY_CONFIGURATION_H) */
