// <copyright file="sensor_array_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_ARRAY_CONFIGURATION_H)
#define _PWROWG_SENSOR_ARRAY_CONFIGURATION_H
#pragma once

#include <functional>

#include "visus/pwrowg/adl_configuration.h"
#include "visus/pwrowg/sensor_description.h"
#include "visus/pwrowg/tinkerforge_configuration.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// The configuration object used to contruct a <see cref="sensor_array" />.
/// </summary>
class sensor_array_configuration final {

public:

    /// <summary>
    /// Defines the interface of a filter that can be applied when creating a
    /// sensor array to select the sensors included in the array based on their
    /// description.
    /// </summary>
    typedef bool (*filter_func)(const sensor_description&, void *);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    sensor_array_configuration(void);

    /// <summary>
    /// Configures the ADL sensors.
    /// </summary>
    /// <param name="configure"></param>
    /// <returns></returns>
    inline sensor_array_configuration& configure(
            _In_ std::function<void(adl_configuration&)> configure) {
        configure(this->_adl_configuration);
        return *this;
    }

    /// <summary>
    /// Configures the Tinkerforge sensors.
    /// </summary>
    /// <param name="configure"></param>
    /// <returns></returns>
    inline sensor_array_configuration& configure(
            _In_ std::function<void(tinkerforge_configuration&)> configure) {
        configure(this->_tinkerforge_configuration);
        return *this;
    }

    /// <summary>
    /// Gets the filter that is used to determine which sensors are included in
    /// the array.
    /// </summary>
    /// <returns>The filter determining the active sensors.</returns>
    inline _Ret_valid_ filter_func filter(void) const noexcept {
        return this->_filter;
    }

    /// <summary>
    /// Sets a new filter to determine which sensors are included in the array.
    /// </summary>
    /// <param name="filter">The filter function to be called for each sensor to
    /// check whether it is included. If <c>nullptr</c>, a filter accepting all
    /// sensors will be installed.</param>
    /// <param name="context">An optional context pointer that is passed to the
    /// <paramref name="filter" /> callback.
    /// <returns><c>*this</c>.</returns>
    sensor_array_configuration& filter(
        _In_opt_ const filter_func filter,
        _In_opt_ void *context) noexcept;

    /// <summary>
    /// Applies the filter to the given <see cref="sensor_description" />.
    /// </summary>
    /// <param name="desc">The sensor description to be tested.</param>
    /// <returns>The return value of the current filter</returns>
    bool filter(_In_ const sensor_description& desc) const;

private:

    adl_configuration _adl_configuration;
    filter_func _filter;
    void *_filter_context;
    tinkerforge_configuration _tinkerforge_configuration;

};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_ARRAY_CONFIGURATION_H) */
