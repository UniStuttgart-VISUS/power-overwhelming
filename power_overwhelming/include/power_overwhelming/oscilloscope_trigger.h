// <copyright file="oscilloscope_trigger.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/oscilloscope_quantity.h"
#include "power_overwhelming/oscilloscope_trigger_mode.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines the interface of possible triggers for oscilloscopes.
    /// </summary>
    /// <remarks>
    /// This base class cannot be used directly. It only defines the minimum
    /// parameters shared by all types of triggers.
    /// </remarks>
    class POWER_OVERWHELMING_API oscilloscope_trigger {

    public:

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        virtual ~oscilloscope_trigger(void);

        /// <summary>
        /// Gets the hold-off time for which a trigger cannot trigger again
        /// after it has triggered.
        /// </summary>
        /// <returns>The hold-off time as a string or <c>nullptr</c> if no
        /// hold-off is configured.</returns>
        inline _Ret_maybenull_z_ const char *hold_off(void) const noexcept {
            return this->_hold_off;
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
        /// Gets the name of the source to trigger on.
        /// </summary>
        /// <returns>The name of the trigger source.</returns>
        inline _Ret_maybenull_z_ const char *source(void) const noexcept {
            return this->_source;
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
        virtual _Ret_z_ const char *type(void) const noexcept = 0;

    protected:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="source">The name of the trigger source.</param>
        explicit oscilloscope_trigger(_In_z_ const char *source);

        /// <summary>
        /// Clone <paramref name="rhs" />.
        /// </summary>
        /// <param name="rhs">The object to be cloned.</param>
        oscilloscope_trigger(_In_ const oscilloscope_trigger& rhs);

        /// <summary>
        /// Move <paramref name="rhs" />.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        oscilloscope_trigger(_Inout_ oscilloscope_trigger&& rhs) noexcept;

        /// <summary>
        /// Assignment.
        /// </summary>
        /// <param name="rhs">The right hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_trigger& operator =(_In_ const oscilloscope_trigger& rhs);

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_trigger& operator =(
            _Inout_ oscilloscope_trigger&& rhs) noexcept;

    private:

        char *_hold_off;
        oscilloscope_trigger_mode _mode;
        char *_source;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
