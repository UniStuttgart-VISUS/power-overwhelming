// <copyright file="oscilloscope_label.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Represents a label that can be optionally attached to items on the
    /// oscilloscope, eg to a channel.
    /// </summary>
    class POWER_OVERWHELMING_API oscilloscope_label final {

    public:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline oscilloscope_label(void) : _text(nullptr), _visible(false) { }

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <remarks>
        /// This constructor allows for implicit conversion from strings to
        /// labels.
        /// </remarks>
        /// <param name="text">The text to be displayed.</param>
        /// <param name="visible">Indicates whether the label is visible or
        /// hidden. This parameter defaults to <c>true</c>.</param>
        oscilloscope_label(_In_opt_z_ const wchar_t *text,
            _In_ const bool visible = true);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <remarks>
        /// This constructor allows for implicit conversion from strings to
        /// labels.
        /// </remarks>
        /// <param name="text">The text to be displayed.</param>
        /// <param name="visible">Indicates whether the label is visible or
        /// hidden. This parameter defaults to <c>false</c>.</param>
        oscilloscope_label(_In_opt_z_ const char *text,
            _In_ const bool visible = true);

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~oscilloscope_label(void);

        /// <summary>
        /// Clone <paramref name="rhs" />.
        /// </summary>
        /// <param name="rhs">The object to be cloned.</param>
        oscilloscope_label(_In_ const oscilloscope_label& rhs);

        /// <summary>
        /// Move <paramref name="rhs" />.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        oscilloscope_label(_Inout_ oscilloscope_label&& rhs) noexcept;

        /// <summary>
        /// Gets the text to be displayed.
        /// </summary>
        /// <returns>The label to be shown.</returns>
        _Ret_z_ const char *text(void) const noexcept;

        /// <summary>
        /// Sets the text to be displayed.
        /// </summary>
        /// <param name="text">The text to be displayed.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_label& text(_In_opt_z_ const wchar_t *text);

        /// <summary>
        /// Sets the text to be displayed.
        /// </summary>
        /// <param name="text">The text to be displayed.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_label& text(_In_opt_z_ const char *text);

        /// <summary>
        /// Indicates whether the label should be shown or hidden.
        /// </summary>
        /// <returns><c>true</c> if the label should be shown, <c>false</c>
        /// otherwise..</returns>
        inline bool visible(void) const noexcept {
            return this->_visible;
        }

        /// <summary>
        /// Changes the visibility of the label.
        /// </summary>
        /// <param name="visible"><c>true</c> for showing the label,
        /// <c>false</c> for hiding it.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_label& visible(_In_ const bool visible) noexcept {
            this->_visible = visible;
            return *this;
        }

        /// <summary>
        /// Assignment.
        /// </summary>
        /// <param name="rhs">The right hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_label& operator =(_In_ const oscilloscope_label& rhs);

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        oscilloscope_label& operator =(
            _Inout_ oscilloscope_label&& rhs) noexcept;

    private:

        char *_text;
        bool _visible;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
