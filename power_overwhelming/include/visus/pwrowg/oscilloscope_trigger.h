// <copyright file="oscilloscope_trigger.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>

#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/oscilloscope_quantity.h"
#include "visus/pwrowg/oscilloscope_trigger_coupling.h"
#include "visus/pwrowg/oscilloscope_trigger_hysteresis.h"
#include "visus/pwrowg/oscilloscope_trigger_mode.h"
#include "visus/pwrowg/oscilloscope_trigger_slope.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Holds the configuration of a trigger.
    /// </summary>
    class POWER_OVERWHELMING_API oscilloscope_trigger final {

    public:

        /// <summary>
        /// The type used to index the trigger input.
        /// </summary>
        typedef std::uint8_t input_type;

        /// <summary>
        /// Configures an edge trigger on the specified source.
        /// </summary>
        /// <param name="source">The name of the trigger source.</param>
        /// <returns>An edge trigger.</returns>
        static oscilloscope_trigger edge(_In_z_ const wchar_t *source);

        /// <summary>
        /// Configures an edge trigger on the specified source.
        /// </summary>
        /// <param name="source">The name of the trigger source.</param>
        /// <returns>An edge trigger.</returns>
        static oscilloscope_trigger edge(_In_z_ const char *source);

        /// <summary>
        /// Configures an edge trigger on the specified analog source.
        /// </summary>
        /// <param name="source">The one-based index of the analog source
        /// to configure.</param>
        /// <returns>An edge trigger.</returns>
        static oscilloscope_trigger edge(_In_ const input_type source);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="source">The name of the trigger source.</param>
        /// <param name="type">The type of the trigger.</param>
        oscilloscope_trigger(_In_z_ const wchar_t *source,
            _In_z_ const wchar_t *type);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="source">The name of the trigger source.</param>
        /// <param name="type">The type of the trigger.</param>
        oscilloscope_trigger(_In_z_ const char *source,
            _In_z_ const char *type);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="source">The one-based index of the analog source
        /// to configure.</param>
        /// <param name="type">The type of the trigger.</param>
        oscilloscope_trigger(_In_ const input_type source,
            _In_z_ const wchar_t *type);

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
        oscilloscope_trigger& coupling(
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
        oscilloscope_trigger& external(
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
        oscilloscope_trigger& external(_In_ const float level = 2.5f,
            _In_ const oscilloscope_trigger_slope slope
            = oscilloscope_trigger_slope::rising);

        /// <summary>
        /// Gets the hold-off time for which a trigger cannot trigger again
        /// after it has triggered.
        /// </summary>
        /// <returns>The hold-off time as a string or <c>nullptr</c> if no
        /// hold-off is configured.</returns>
        inline _Ret_maybenull_z_ const char *hold_off(void) const noexcept {
            return this->_hold_off.as<char>();
        }

        /// <summary>
        /// Sets the hold-off time for which a tigger cannot trigger again after
        /// it has triggered.
        /// </summary>
        /// <param name="hold_off_time">The hold-off time or <c>nullptr</c> to
        /// disable hold off</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_trigger& hold_off(_In_opt_z_ const wchar_t *hold_off);

        /// <summary>
        /// Sets the hold-off time for which a tigger cannot trigger again after
        /// it has triggered.
        /// </summary>
        /// <param name="hold_off_time">The hold-off time or <c>nullptr</c> to
        /// disable hold off</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_trigger& hold_off(_In_opt_z_ const char *hold_off);

        /// <summary>
        /// Disables the hold-off for the trigger.
        /// </summary>
        /// <param name="n"><c>nullptr</c>.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_trigger& hold_off(_In_opt_z_ const std::nullptr_t n);

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
        oscilloscope_trigger& hysteresis(
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
        inline oscilloscope_trigger& level(_In_ const input_type input,
                _In_ const oscilloscope_quantity& level) {
            this->_input = input;
            this->_level = level;
            return *this;
        }

        /// <summary>
        /// Configures the trigger level for the current input.
        /// </summary>
        /// <param name="level">The trigger level.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_trigger& level(
                _In_ const oscilloscope_quantity& level) {
            return this->level(this->_input, level);
        }

        /// <summary>
        /// Gets the trigger mode.
        /// </summary>
        /// <returns>The trigger mode.</returns>
        inline oscilloscope_trigger_mode mode(void) const noexcept {
            return this->_mode;
        }

        /// <summary>
        /// Sets a new trigger mode, which determines whether the oscilloscope
        /// only triggers on a real trigger in the data or whether it times out
        /// and triggers automatically if no real trigger happens.
        /// </summary>
        /// <param name="mode">The new mode.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_trigger& mode(
            _In_ const oscilloscope_trigger_mode mode) noexcept;

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
        inline oscilloscope_trigger& slope(
                _In_ const oscilloscope_trigger_slope slope) noexcept {
            this->_slope = slope;
            return *this;
        }

        /// <summary>
        /// Gets the name of the source to trigger on.
        /// </summary>
        /// <returns>The name of the trigger source.</returns>
        inline _Ret_maybenull_z_ const char *source(void) const noexcept {
            return this->_source.as<char>();
        }

        /// <summary>
        /// Sets the source on which to trigger.
        /// </summary>
        /// <param name="source">The source on which to trigger. On RTx series
        /// oscilloscopes, this can be &quot;CH1&quot; to &quot;CH4&quot;,
        /// &quot;EXT&quot; for the external analogue trigger and several other
        /// modes which you can find in the manual.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_trigger& source(_In_z_ const wchar_t *source);

        /// <summary>
        /// Sets the source on which to trigger.
        /// </summary>
        /// <param name="source">The source on which to trigger. On RTx series
        /// oscilloscopes, this can be &quot;CH1&quot; to &quot;CH4&quot;,
        /// &quot;EXT&quot; for the external analogue trigger and several other
        /// modes which you can find in the manual.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_trigger& source(_In_z_ const char *source);

        /// <summary>
        /// Gets the type of the trigger.
        /// </summary>
        /// <remarks>
        /// Trigger classes must implement this method and return the type of
        /// the trigger, which is passed directly VISA API.
        /// </remarks>
        /// <returns>The string representation of the type of the trigger.
        /// </returns>
        inline _Ret_maybenull_z_ const char *type(void) const noexcept {
            return this->_type.as<char>();
        }

        /// <summary>
        /// Sets the type of the trigger.
        /// </summary>
        /// <param name="type">The type of the trigger.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_trigger& type(_In_z_ const wchar_t *type);

        /// <summary>
        /// Sets the type of the trigger.
        /// </summary>
        /// <param name="type">The type of the trigger.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_trigger& type(_In_z_ const char *type);

    private:

        oscilloscope_trigger_coupling _coupling;
        blob _hold_off;
        oscilloscope_trigger_hysteresis _hysteresis;
        input_type _input;
        oscilloscope_quantity _level;
        oscilloscope_trigger_mode _mode;
        oscilloscope_trigger_slope _slope;
        blob _source;
        blob _type;

    };

} /* namespace power_overwhelming */
} /* namespace visus */
