// <copyright file="rtx_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_CONFIGURATION_H)
#define _PWROWG_RTX_CONFIGURATION_H
#pragma once

#include "visus/pwrowg/guid.h"
#include "visus/pwrowg/rtx_instrument.h"
#include "visus/pwrowg/rtx_sensor_definition.h"
#include "visus/pwrowg/rtx_instrument_configuration.h"
#include "visus/pwrowg/sensor_configuration.h"
#include "visus/pwrowg/type_erased_storage.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// The configuration for a sensor based on Rohde &amp; Schwarz RTA/RTB
/// oscilloscopes. As an oscilloscope only measures voltage over time, its
/// channel have no inherent meaning attached to them. Therefore, the sensor
/// will not work without manually configuring pairs of channel that measure
/// voltage and current for one rail. This is achieved by adding
/// <see cref="rtx_sensor_definition" />s to a configuration.
/// </summary>
class POWER_OVERWHELMING_API rtx_configuration final
        : public sensor_configuration {

public:

    /// <summary>
    /// A unique identifier for the <see cref="rtx_configuration" /> type.
    /// </summary>
    static const guid id;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    rtx_configuration(void);

    rtx_configuration(_Inout_ rtx_configuration&& rhs) noexcept = default;

    /// <summary>
    /// Answer the number of sensors (voltage/current pairs) that have been
    /// configured.
    /// </summary>
    /// <returns>The number of configured sensors.</returns>
    std::size_t count_sensors(void) const noexcept;

    /// <summary>
    /// Gets the configuration that will be applied to the oscilloscopes on
    /// startup.
    /// </summary>
    /// <returns>The instrument configuration.</returns>
    inline const rtx_instrument_configuration& instrument_configuration(
            void) const noexcept {
        return this->_instrument_configuration;
    }

    /// <summary>
    /// Gets the configuration that will be applied to the oscilloscopes on
    /// startup.
    /// </summary>
    /// <returns>The instrument configuration.</returns>
    inline rtx_instrument_configuration& instrument_configuration(
            void) noexcept {
        return this->_instrument_configuration;
    }

    /// <summary>
    /// Answer the array of registered <see cref="rtx_sensor_definition" />s.
    /// </summary>
    /// <remarks>
    /// The size of the array can be obtained from
    /// <see cref="count_sensors" />.
    /// </remarks>
    /// <returns>The configured sensors.</returns>
    _Ret_valid_ const rtx_sensor_definition *sensors(void) const noexcept;

    /// <summary>
    /// Replaces any existing <see cref="rtx_sensor_definition" />s with the given
    /// array of new sensors.
    /// </summary>
    /// <param name="sensors">An array of at least <paramref name="cnt" /> sensor
    /// definitions.</param>
    /// <param name="cnt">The number of sensor definitions provided.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    rtx_configuration& sensors(
        _In_reads_opt_(cnt) rtx_sensor_definition *sensors,
        _In_ const std::size_t cnt);

    rtx_configuration& operator =(
        _Inout_ rtx_configuration&& rhs) noexcept = default;

private:

    rtx_instrument_configuration _instrument_configuration;
    type_erased_storage _instruments;
    type_erased_storage _sensors;
    type_erased_storage _trigger_callback;
};

PWROWG_NAMESPACE_END

#endif /*!defined(_PWROWG_RTX_CONFIGURATION_H) */
