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
        oscilloscope_edge_trigger(_In_ const oscilloscope_edge_trigger& rhs);

        /// <summary>
        /// Move <paramref name="rhs" />.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        oscilloscope_edge_trigger(
            _Inout_ oscilloscope_edge_trigger&& rhs) noexcept;

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~oscilloscope_edge_trigger(void);

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
        /// Gets the one-based intex of the trigger input.
        /// </summary>
        /// <returns>The index of the trigger input.</returns>
        inline input_type input(void) const noexcept {
            return this->_input;
        }

        /// <summary>
        /// Configuret the trigger level.
        /// </summary>
        /// <param name="input">Selects the trigger input within [1, 5]. Valid
        /// values depend on the hardware. Channel 5 is the external trigger
        /// input.</param>
        /// <param name="value">The trigger value.</param>
        /// <param name="unit">The unit of the trigger value, which defaults to
        /// Volts.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::invalid_argument">If <paramref name="unit" />
        /// is <c>nullptr</c>.</exception>
        oscilloscope_edge_trigger& level(_In_ const input_type input,
            _In_ const float value, _In_z_ const wchar_t *unit);

        /// <summary>
        /// Configuret the trigger level.
        /// </summary>
        /// <param name="input">Selects the trigger input within [1, 5]. Valid
        /// values depend on the hardware. Channel 5 is the external trigger
        /// input.</param>
        /// <param name="value">The trigger value.</param>
        /// <param name="unit">The unit of the trigger value, which defaults to
        /// Volts.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::invalid_argument">If <paramref name="unit" />
        /// is <c>nullptr</c>.</exception>
        oscilloscope_edge_trigger& level(_In_ const input_type input,
            _In_ const float value, _In_z_ const char *unit = "V");

        /// <summary>
        /// Gets the unit for the trigger level.
        /// </summary>
        /// <remarks>
        /// If the unit is <c>nullptr</c> or empty, the default unit of the
        /// instrument should be used.
        /// </remarks>
        /// <returns>The unit.</returns>
        inline _Ret_z_ const char *level_unit(void) const noexcept {
            return (this->_level_unit != nullptr) ? this->_level_unit : "";
        }

        /// <summary>
        /// Gets the trigger level.
        /// </summary>
        /// <returns>The trigger level.</returns>
        inline float level_value(void) const noexcept {
            return this->_level_value;
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
            _In_ const oscilloscope_edge_trigger& rhs);

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_edge_trigger& operator =(
            _Inout_ oscilloscope_edge_trigger&& rhs) noexcept;

    private:

        oscilloscope_trigger_coupling _coupling;
        oscilloscope_trigger_hysteresis _hysteresis;
        input_type _input;
        char *_level_unit;
        float _level_value;
        oscilloscope_trigger_slope _slope;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
