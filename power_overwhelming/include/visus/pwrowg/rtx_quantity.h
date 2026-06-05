// <copyright file="rtx_quantity.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_QUANTITY_H)
#define _PWROWG_RTX_QUANTITY_H
#pragma once

#include <chrono>
#include <cinttypes>
#include <type_traits>

#include "visus/pwrowg/string_functions.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Represents a quantity for configuring oscilloscope parameters.
/// </summary>
class POWER_OVERWHELMING_API rtx_quantity final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="value">The value of the quantity.</param>
    /// <param name="unit">The unit of the quantity. It is safe to pass
    /// <c>nullptr</c>, in which case the instrument should assume its
    /// default unit for the parameter in question.</param>
    rtx_quantity(_In_ const float value,
        _In_opt_z_ const wchar_t *unit);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <remarks>
    /// This constructor allows for implicit conversion of <c>float</c> to
    /// a quantity of the default unit of the variable the instance is used
    /// for.
    /// </remarks>
    /// <param name="value">The value of the quantity.</param>
    /// <param name="unit">The unit of the quantity. It is safe to pass
    /// <c>nullptr</c>, in which case the instrument should assume its
    /// default unit for the parameter in question.</param>
    rtx_quantity(_In_ const float value = 0.0f,
        _In_opt_z_ const char *unit = nullptr);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <remarks>
    /// This constructor allows for implicit conversion of STL durations.
    /// </remarks>
    /// <typeparam name="TRep"></typeparam>
    /// <typeparam name="TPeriod"></typeparam>
    /// <param name="value"></param>
    template<class TRep, class TPeriod>
    rtx_quantity(_In_ const std::chrono::duration<TRep, TPeriod> value);

    /// <summary>
    /// Clone <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The object to be cloned.</param>
    rtx_quantity(_In_ const rtx_quantity& rhs);

    /// <summary>
    /// Move <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    rtx_quantity(_Inout_ rtx_quantity&& rhs) noexcept;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~rtx_quantity(void);

    /// <summary>
    /// Gets the unit of the quantity.
    /// </summary>
    /// <returns>The unit of the quantity. If this is an empty string, the
    /// instrument should use the default unit for the quantity.</returns>
    _Ret_z_ const char *unit(void) const noexcept;

    /// <summary>
    /// The value of the quantity.
    /// </summary>
    /// <returns>The value of the quantity.</returns>
    inline float value(void) const noexcept {
        return this->_value;
    }

    /// <summary>
    /// Assignment.
    /// </summary>
    /// <param name="rhs">The right hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    rtx_quantity& operator =(_In_ const rtx_quantity& rhs);

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The right hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    rtx_quantity& operator =(_Inout_ rtx_quantity&& rhs) noexcept;

    /// <summary>
    /// Test for equality.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><see langword="true "/> if this object and
    /// <paramref name="rhs" /> are equal, <see langword="false" /> otherwise.
    /// </returns>
    bool operator ==(_In_ const rtx_quantity& rhs) const noexcept;

    /// <summary>
    /// Test for inequality.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><see langword="true "/> if this object and
    /// <paramref name="rhs" /> are not equal, <see langword="false" />
    /// otherwise.</returns>
    inline bool operator !=(_In_ const rtx_quantity& rhs) const noexcept {
        return !(*this == rhs);
    }

    /// <summary>
    /// Allows for implicit conversion of the quantity into its numeric
    /// value.
    /// </summary>
    /// <returns>The value of the quantity.</returns>
    inline operator float(void) const noexcept {
        return this->_value;
    }

private:

    char *_unit;
    float _value;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/rtx_quantity.inl"

#endif /* !defined(_PWROWG_RTX_QUANTITY_H) */
