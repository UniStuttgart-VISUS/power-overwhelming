// <copyright file="marker_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_MARKER_CONFIGURATION_H)
#define _PWROWG_MARKER_CONFIGURATION_H
#pragma once

#include <string>

#include "visus/pwrowg/sensor_configuration.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Allows for configuring a sensor that emits user-defined markers in to the
/// stream of samples.
/// </summary>
class POWER_OVERWHELMING_API marker_configuration final
        : public sensor_configuration {

public:

    /// <summary>
    /// A unique identifer for the <see cref="marker_configuration" /> type.
    /// </summary>
    static const guid id;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline marker_configuration(void) : _names(nullptr) { }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="rhs">The instance to be cloned.</param>
    marker_configuration(_In_ const marker_configuration& rhs)
            : _names(nullptr) {
        *this = rhs;
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    marker_configuration(_Inout_ marker_configuration&& rhs) noexcept
            : _names(rhs._names) {
        rhs._names = nullptr;
    }

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    virtual ~marker_configuration(void) noexcept;

    /// <summary>
    /// Clears all marker names.
    /// </summary>
    inline void clear(void) noexcept {
        delete[] this->_names;
        this->_names = nullptr;
    }

    /// <summary>
    /// Answer the number of configured markers.
    /// </summary>
    std::size_t size(void) const noexcept;

    /// <summary>
    /// Assignment.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>*this</c>.</returns>
    marker_configuration& operator =(_In_ const marker_configuration& rhs);

    /// <summary>
    /// Assignment.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>*this</c>.</returns>
    marker_configuration& operator =(
        _Inout_ marker_configuration&& rhs) noexcept;

    /// <summary>
    /// Answer the name of the <param name="index" />th marker.
    /// </summary>
    /// <param name="index">The zero-based index of the marker to
    /// retrieve.</param>
    /// <returns>The name of the requested marker, or <c>nullptr</c> if said
    /// marker does not exist.</returns>
    _Ret_maybenull_z_ const wchar_t *operator [](
        _In_ const int index) const noexcept;

    /// <summary>
    /// Adds a marker with the specified name.
    /// </summary>
    /// <param name="name">The name of the marker to be added.</param>
    /// <returns>The zero-based index of the marker.</returns>
    int operator +=(_In_z_ const wchar_t *name);

    /// <summary>
    /// Adds a marker with the specified name.
    /// </summary>
    /// <param name="name">The name of the marker to be added.</param>
    /// <returns>The zero-based index of the marker.</returns>
    inline int operator +=(_In_ const std::wstring& name) {
        return *this += name.c_str();
    }

private:

    wchar_t *_names;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_MARKER_CONFIGURATION_H) */
