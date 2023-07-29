// <copyright file="oscilloscope_edge_trigger.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>

#include "power_overwhelming/oscilloscope_trigger.h"
#include "power_overwhelming/oscilloscope_trigger_coupling.h"
#include "power_overwhelming/oscilloscope_trigger_hysteresis.h"
#include "power_overwhelming/oscilloscope_trigger_slope.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines the interface of possible triggers for oscilloscopes.
    /// </summary>
    class POWER_OVERWHELMING_API oscilloscope_edge_trigger final
            : public oscilloscope_trigger {

    public:

        /// <summary>
        /// The type used to index the trigger input.
        /// </summary>
        typedef std::uint16_t input_type;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="source">The name of the trigger source.</param>
        explicit oscilloscope_edge_trigger(_In_ const char *source);

        /// <summary>
        /// Clone <paramref name="rhs" />.
        /// </summary>
        /// <param name="rhs">The object to be cloned.</param>
        oscilloscope_edge_trigger(
            _In_ const oscilloscope_edge_trigger& rhs) = default;

        /// <summary>
        /// Move <paramref name="rhs" />.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        oscilloscope_edge_trigger(
            _Inout_ oscilloscope_edge_trigger&& rhs) noexcept = default;

        /// <summary>
        /// Gets the coupling for the trigger source.
        /// </summary>
        /// <returns>The coupling for the trigger source.</returns>
        inline oscilloscope_trigger_coupling coupling(void) const noexcept {
            return this->_coupling;
        }

        /// <summary>
        /// Sets the coupling for the trigger source.
        /// </summary>
        /// <param name="coupling">The coupling for the trigger source.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_edge_trigger& coupling(
                _In_ oscilloscope_trigger_coupling coupling) noexcept {
            this->_coupling = coupling;
            return *this;
        }

        /// <summary>
        /// Configues the trigger as an external trigger on the given level.
        /// </summary>
        /// <param name="level">The trigger level.</param>
        /// <param name="slope">The slope on which to trigger. This parameter
        /// defaults to <see cref="oscilloscope_trigger_slope::rising" />.
        /// </param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_edge_trigger& external(
            _In_ const oscilloscope_quantity& level,
            _In_ const oscilloscope_trigger_slope slope
            = oscilloscope_trigger_slope::rising);

        /// <summary>
        /// Configues the trigger as an external trigger on the given level.
        /// </summary>
        /// <param name="level">The trigger level in Volts. This parameter
        /// defaults to 2.5 V.</param>
        /// <param name="slope">The slope on which to trigger. This parameter
        /// defaults to <see cref="oscilloscope_trigger_slope::rising" />.
        /// </param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_edge_trigger& external(_In_ const float level = 2.5f,
            _In_ const oscilloscope_trigger_slope slope
            = oscilloscope_trigger_slope::rising);

        /// <summary>
        /// Gets the hysteresis range around the trigger level.
        /// </summary>
        /// <returns>The enumerated hysteresis range.</returns>
        inline oscilloscope_trigger_hysteresis hysteresis(void) const noexcept {
            return this->_hysteresis;
        }

        /// <summary>
        /// Sets the hysteresis range around the trigger level.
        /// </summary>
        /// <param name="hysteresis">The hysteresis range.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_edge_trigger& hysteresis(
            _In_ oscilloscope_trigger_hysteresis hysteresis) noexcept {
            this->_hysteresis = hysteresis;
            return *this;
        }

        /// <summary>
        /// Gets the one-based index of the trigger input.
        /// </summary>
        /// <remarks>
        /// Use <see cref="level" /> to set this property.
        /// </remarks>
        /// <returns>The index of the trigger input.</returns>
        inline input_type input(void) const noexcept {
            return this->_input;
        }

        /// <summary>
        /// Gets the trigger level.
        /// </summary>
        /// <remarks>
        /// If the unit is <c>nullptr</c> or empty, the default unit of the
        /// instrument should be used.
        /// </remarks>
        /// <returns>The unit.</returns>
        inline const oscilloscope_quantity& level(void) const noexcept {
            return this->_level;
        }

        /// <summary>
        /// Configures the trigger level.
        /// </summary>
        /// <param name="input">Selects the trigger input within [1, 5]. Valid
        /// values depend on the hardware. Channel 5 is the external trigger
        /// input.</param>
        /// <param name="level">The trigger level.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_edge_trigger& level(_In_ const input_type input,
                _In_ const oscilloscope_quantity& level) {
            this->_input = input;
            this->_level = level;
            return *this;
        }

        /// <summary>
        /// Configures the trigger level for all channels.
        /// </summary>
        /// <param name="level">The trigger level.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_edge_trigger& level(
                _In_ const oscilloscope_quantity& level) {
            return this->level(0, level);
        }

        /// <summary>
        /// Gets the slope on which the trigger becomes active.
        /// </summary>
        /// <returns>The slope for the edge trigger.</returns>
        inline oscilloscope_trigger_slope slope(void) const noexcept {
            return this->_slope;
        }

        /// <summary>
        /// Sets the slop on which the trigger becomes active.
        /// </summary>
        /// <param name="slope">The slope for the edge trigger.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_edge_trigger& slope(
                _In_ const oscilloscope_trigger_slope slope) noexcept {
            this->_slope = slope;
            return *this;
        }

        /// <inheritdoc />
        _Ret_z_ const char *type(void) const noexcept override;

        /// <summary>
        /// Assignment.
        /// </summary>
        /// <param name="rhs">The right hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_edge_trigger& operator =(
            _In_ const oscilloscope_edge_trigger& rhs) = default;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_edge_trigger& operator =(
            _Inout_ oscilloscope_edge_trigger&& rhs) noexcept = default;

    private:

        oscilloscope_trigger_coupling _coupling;
        oscilloscope_trigger_hysteresis _hysteresis;
        input_type _input;
        oscilloscope_quantity _level;
        oscilloscope_trigger_slope _slope;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
