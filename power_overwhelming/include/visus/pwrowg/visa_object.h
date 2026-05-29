// <copyright file="visa_object.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_VISA_OBJECT_H)
#define _PWROWG_VISA_OBJECT_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_VISA)

#include <visa.h>

#include <memory>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A RAII wrapper for a VISA object handle, typically an event.
/// </summary>
class POWER_OVERWHELMING_API visa_object final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    visa_object(void) noexcept;

    /// <summary>
    /// Initialise from move.
    /// </summary>
    /// <param name="other">The object to be moved.</param>
    visa_object(_Inout_ visa_object&& other) noexcept;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    inline ~visa_object(void) noexcept {
        this->reset();
    }

    /// <summary>
    /// Resets any existing instance and returns a pointer to the object
    /// handle for the VISA API to fill.
    /// </summary>
    /// <returns>A pointer to an object handle that is guaranteed to be invalid
    /// and ready to be overwritten.</returns>
    inline ViObject *put(void) noexcept {
        this->reset();
        return std::addressof(this->_object);
    }

    /// <summary>
    /// Releases the VISA object contained in the instance.
    /// </summary>
    void reset(void) noexcept;

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    visa_object& operator =(_Inout_ visa_object&& rhs) noexcept;

private:

    ViObject _object;
};


PWROWG_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
#endif /* !defined(_PWROWG_VISA_OBJECT_H) */
