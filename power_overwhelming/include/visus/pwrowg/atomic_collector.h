// <copyright file="atomic_collector.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_ATOMIC_COLLECTOR_H)
#define _PWROWG_ATOMIC_COLLECTOR_H
#pragma once

#include <atomic>
#include <memory>
#include <utility>

#include "visus/pwrowg/collector_result.h"


#if (defined(DEBUG) || defined(_DEBUG) || defined(PROFILE) || defined(_PROFILE))
#if !defined(PWROWG_PROFILE_ATOMIC_COLLECTOR)
#define PWROWG_PROFILE_ATOMIC_COLLECTOR
#endif /* PWROWG_PROFILE_ATOMIC_COLLECTOR */
#endif /* (defined(DEBUG) || defined(_DEBUG) || defined(PROFILE) || */


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A container for accumulating data produced by multiple threads concurrently.
/// </summary>
/// <remarks>
/// <para>Implementation note: Do not use <c>shared_ptr</c> for the pages here,
/// because atomics on these are not lock-free (at least in MSVC)!</para>
/// </remarks>
/// <typeparam name="TValue">The type of values in the collection.</typeparam>
/// <typeparam name="PageSize">The number of elements in a page that is
/// allocated in one piece. Large pages are advantageous in that they require
/// less reallocations and less spinning, but they potentially waste more
/// memory.</typeparam>
template<class TValue, std::size_t PageSize = 16>
class atomic_collector final {

public:

    static_assert(PageSize >= 1, "A page must contain at least one element.");

    /// <summary>
    /// The type of the result object that can be retrieved from the
    /// collector.
    /// </summary>
    typedef collector_result<TValue, PageSize> result_type;

    /// <summary>
    /// The type of values in the collection.
    /// </summary>
    typedef TValue value_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline atomic_collector(void) : _pages(new page_type()) { }

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    /// <param name=""></param>
    ~atomic_collector(void) noexcept;

#if defined(PWROWG_PROFILE_ATOMIC_COLLECTOR)
    /// <summary>
    /// Answer the number of allocations that have been discarded due to a race.
    /// </summary>
    /// <returns>The number of allocations that have not been used.</returns>
    inline std::size_t alloc_discarded(void) const noexcept {
        return this->_alloc_discarded.load();
    }
#endif /* defined(PWROWG_PROFILE_ATOMIC_COLLECTOR) */

    /// <summary>
    /// Append a new item to the collection.
    /// </summary>
    /// <typeparam name="TArgs">The types of the arguments passed to the
    /// constructor of <see cref="value_type" />.</typeparam>
    /// <param name="args">The arguments passed to the constructor of
    /// <see cref="value_type" />.</param>
    template<class... TArgs>
    inline void emplace(TArgs... args) {
        page_type *page;
        std::size_t index;
        this->reserve(page, index);
        assert(page->ready < page->used);
        assert(index < PageSize);
        auto location = page->values() + index;
        new (location) value_type(std::forward<TArgs>(args)...);
        page->ready.fetch_add(1);
    }

    /// <summary>
    /// Append a new item to the collection.
    /// </summary>
    /// <param name="item">The item to be added.</param>
    inline void push(_In_ const value_type& item) {
        page_type *page;
        std::size_t index;
        this->reserve(page, index);
        assert(page->ready < page->used);
        assert(index < PageSize);
        auto location = page->values() + index;
        *location = item;
        page->ready.fetch_add(1);
    }

    /// <summary>
    /// Append a new item to the collection.
    /// </summary>
    /// <param name="item">The item to be added.</param>
    inline void push(_Inout_ value_type&& item) {
        page_type *page;
        std::size_t index;
        this->reserve(page, index);
        assert(page->ready < page->used);
        assert(index < PageSize);
        auto location = page->values() + index;
        *location = std::move(item);
        page->ready.fetch_add(1);
    }

    /// <summary>
    /// Reset the collector and return its current results.
    /// </summary>
    /// <returns>The data accumulated since the last reset.</returns>
    result_type reset(void);

private:

    /// <summary>
    /// Represents a page in the linked list of collected elements.
    /// </summary>
    typedef typename result_type::page page_type;

    /// <summary>
    /// Reserves an element for writing by the calling thread.
    /// </summary>
    void reserve(_Out_ page_type *& page, _Out_ std::size_t& index);

#if defined(PWROWG_PROFILE_ATOMIC_COLLECTOR)
    alignas(false_sharing_range) std::atomic<std::size_t> _alloc_discarded;
#endif /* defined(PWROWG_PROFILE_ATOMIC_COLLECTOR) */
    alignas(false_sharing_range) std::atomic<page_type *> _pages;
    std::uint8_t _padding[false_sharing_range - sizeof(_pages)];
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/atomic_collector.inl"

#endif /* !defined(_PWROWG_ATOMIC_COLLECTOR_H) */
