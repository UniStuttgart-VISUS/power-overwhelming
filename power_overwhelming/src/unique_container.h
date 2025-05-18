// <copyright file="unique_container.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_UNIQUE_CONTAINER_H)
#define _PWROWG_UNIQUE_CONTAINER_H
#pragma once

#include <cassert>
#include <cstdlib>
#include <memory>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A container that can hold zero or one elements of type
/// <typeparamref name="TValue" />.
/// </summary>
/// <typeparam name="TValue">The type of the element to be stored.</typeparam>
template<class TValue> class unique_container final {

public:

    /// <summary>
    /// The type of the element to be stored.
    /// </summary>
    typedef TValue value_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline unique_container(void) noexcept = default;

    /// <summary>
    /// Answer an iterator for the first element in the container.
    /// </summary>
    /// <returns>An iterator for the begin of the elements.</returns>
    inline const value_type *begin(void) const noexcept {
        return this->_value.get();
    }

    /// <summary>
    /// Answer an iterator for the first element in the container.
    /// </summary>
    /// <returns>An iterator for the begin of the elements.</returns>
    inline value_type *begin(void) noexcept {
        return this->_value.get();
    }

    /// <summary>
    /// Emplaces a new element in the container.
    /// </summary>
    /// <remarks>
    /// This should be called only once, but we do not check this at runtime
    /// except for an assertion.
    /// </remarks>
    /// <typeparam name="TArgs">The arguments passed to the constructor of
    /// <see cref="value_type" />.</typeparam>
    /// <param name="args">The arguments for the constructor.</param>
    template<class... TArgs> inline void emplace(TArgs&&... args) {
        assert(this->empty());
        this->_value.reset(new value_type(std::forward<TArgs>(args)...));
    }

    /// <summary>
    /// Answer whether the container is empty.
    /// </summary>
    /// <returns><c>true</c> if the container is empty, <c>false</c> if it
    /// contains an element.</returns>
    inline bool empty(void) const noexcept {
        return (this->_value == nullptr);
    }

    /// <summary>
    /// Answer an iterator past the last element in the container.
    /// </summary>
    /// <returns>An iterator for the end of the elements.</returns>
    inline const value_type *end(void) const noexcept {
        return this->empty() ? nullptr : (this->begin() + 1);
    }

    /// <summary>
    /// Answer an iterator past the last element in the container.
    /// </summary>
    /// <returns>An iterator for the end of the elements.</returns>
    inline value_type *end(void) noexcept {
        return this->empty() ? nullptr : (this->begin() + 1);
    }

    /// <summary>
    /// Answer the size of the container.
    /// </summary>
    /// <returns>The number of elements in the container, which is either zero
    /// or one.</returns>
    inline std::size_t size(void) const noexcept {
        return this->empty() ? 0 : 1;
    }

private:

    std::unique_ptr<value_type> _value;
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* defined(_PWROWG_UNIQUE_CONTAINER_H) */
