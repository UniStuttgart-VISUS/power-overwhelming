// <copyright file="collector_result.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_COLLECTOR_RESULT_H)
#define _PWROWG_COLLECTOR_RESULT_H
#pragma once

#include <array>
#include <cassert>
#include <cinttypes>
#include <cstdlib>
#include <iterator>
#include <memory>
#include <new>
#include <stdexcept>
#include <thread>
#include <vector>

#include <malloc.h>

#include "visus/pwrowg/atomic_utilities.h"
#include "visus/pwrowg/on_exit.h"


PWROWG_NAMESPACE_BEGIN

/* Forward declarations. */
template<class, std::size_t> class atomic_collector;


/// <summary>
/// A container for the results of a <see cref="atomic_collector" />.
/// </summary>
/// <remarks>
/// <para>While the <see cref="atomic_collector" /> allows for multiple threads
/// adding data concurrently, this results class is not thread-safe and intended
/// for use by a single thread only.</para>
/// </remarks>
/// <typeparam name="TValue">The type of values in the collection.</typeparam>
/// <typeparam name="PageSize">The number of elements in a page that is
/// allocated in one piece. Large pages are advantageous in that they require
/// less reallocations and less spinning, but they potentially waste more
/// memory.</typeparam>
template<class TValue, std::size_t PageSize>
class collector_result final {

private:

    /// <summary>
    /// The size of a page in the linked list in bytes.
    /// </summary>
    static constexpr std::size_t page_size = PageSize * sizeof(TValue);

    /// <summary>
    /// Represents a page in the linked list of collected elements.
    /// </summary>
    struct page {

        /// <summary>
        /// Type of atomic indices.
        /// </summary>
        typedef std::atomic<std::size_t> index_type;

        /// <summary>
        /// Allocates aligned memory for a page.
        /// </summary>
        /// <param name="size">The size of the block to align.</param>
        /// <returns>A pointer to the newly allocated block.</returns>
        /// <exception cref="std::bad_alloc">If the allocation fails.
        /// </exception>
        static void *operator new(_In_ const std::size_t size);

        /// <summary>
        /// Frees the allocation of a page.
        /// </summary>
        static inline void operator delete(_In_ void *ptr) noexcept {
            free_for_atomic(ptr);
        }

        /// <summary>
        /// Pointer to the next page.
        /// </summary>
        page *next;

        /// <summary>
        /// The untyped memory for the data.
        /// </summary>
        std::array<std::uint8_t, page_size> data;

        /// <summary>
        /// The number of valid elements in <see cref="data" />.
        /// </summary>
        alignas(false_sharing_range) index_type ready;

        /// <summary>
        /// The number of used elements that can be stored in
        /// <see cref="data" />, which must be at least <see cref="ready" />,
        /// but can be more while a thread is writing.
        /// </summary>
        alignas(false_sharing_range) index_type used;

        std::uint8_t _padding[false_sharing_range - sizeof(used)];

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline page(void) : next(nullptr), ready(0), used(0) { }

        /// <summary>
        /// Finalises the instance by calling the dtor on all allocated objects.
        /// </summary>
        ~page(void);

        /// <summary>
        /// Gets the <paramref name="data" /> at the specified index
        /// <paramref name="i" />.
        /// </summary>
        inline TValue& value(_In_ const std::size_t i) noexcept {
            return this->values()[i];
        }

        /// <summary>
        /// Gets the <paramref name="data" /> at the specified index
        /// <paramref name="i" />.
        /// </summary>
        inline const TValue& value(_In_ const std::size_t i) const noexcept {
            return this->values()[i];
        }

        /// <summary>
        /// Gets <see cref="data" /> as pointer to <see cref="value_type" />.
        /// </summary>
        inline TValue *values(void) noexcept {
            return reinterpret_cast<TValue *>(this->data.data());
        }

        /// <summary>
        /// Gets <see cref="data" /> as pointer to <see cref="value_type" />.
        /// </summary>
        inline const TValue *values(void) const noexcept {
            return reinterpret_cast<const TValue *>(this->data.data());
        }

        /// <summary>
        /// Spin until all pending writes on the page have completed.
        /// </summary>
        void wait(void) const noexcept;
    };

public:

    /// <summary>
    /// The type of an iterator over the results.
    /// </summary>
    class iterator : public std::iterator<std::forward_iterator_tag, TValue> {

    public:

        /// <summary>
        /// Access the current value.
        /// </summary>
        /// <returns></returns>
        inline const TValue& operator *(void) const noexcept {
            assert(this->_page != nullptr);
            return this->_page->values()[this->_index];
        }

        /// <summary>
        /// Access a pointer to the current value.
        /// </summary>
        /// <param name=""></param>
        /// <returns></returns>
        inline const TValue *operator ->(void) noexcept {
            assert(this->_page != nullptr);
            return this->_page->values() + this->_index;
        }

        /// <summary>
        /// Prefix increment.
        /// </summary>
        /// <returns><c>*this</c>.</returns>
        iterator& operator++ (void) noexcept;

        /// <summary>
        /// Postfix increment.
        /// </summary>
        /// <returns><c>*this</c> before the increment.</returns>
        inline iterator operator ++(int) noexcept {
            auto retval = *this;
            ++(*this);
            return retval;
        }

        /// <summary>
        /// Test for equality.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>true</c> if this iterator an <paramref name="rhs" />
        /// are equal, <c>false</c> otherwise.</returns>
        inline bool operator ==(const iterator& rhs) const noexcept {
            return ((this->_index == rhs._index)
                && (this->_page == rhs._page));
        }

        /// <summary>
        /// Test for inequality.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>true</c> if this iterator an <paramref name="rhs" />
        /// are not equal, <c>false</c> otherwise.</returns>
        inline bool operator !=(const iterator& rhs) const noexcept {
            return !(*this == rhs);
        }

    private:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline iterator(void) noexcept : _index(0) { }

        std::size_t _index;
        page *_page;

        friend class collector_result;
    };

    /// <summary>
    /// The type of values in the collection.
    /// </summary>
    typedef TValue value_type;

    /// <summary>
    /// Move construction.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    inline collector_result(_Inout_ collector_result&& rhs) noexcept
            : _end(std::move(rhs._end)),
            _pages(std::move(rhs._pages)),
            _size(rhs.size()) {
        rhs._size = 0;
    }

    /// <summary>
    /// Gets an iterator over the collected items.
    /// </summary>
    /// <returns>The iterator designating the begin of the collection.</returns>
    inline iterator begin(void) const noexcept {
        iterator retval;
        retval._page = this->_pages.get();
        return retval;
    }

    /// <summary>
    /// Gets an iterator past the last element in the result collection.
    /// </summary>
    /// <returns>The iterator designating the end of the collection.</returns>
    inline iterator end(void) const noexcept {
        return this->_end;
    }

#if (defined(DEBUG) || defined(_DEBUG))
    /// <summary>
    /// Counts the pages that have been allocated for the result.
    /// </summary>
    /// <returns>The number of pages in the result set.</returns>
    std::size_t pages(void) const noexcept;
#endif /* (defined(DEBUG) || defined(_DEBUG)) */

    /// <summary>
    /// Answer the number of elements in the collection.
    /// </summary>
    /// <returns>The number of elements in the collection.</returns>
    inline const std::size_t size(void) const noexcept {
        return this->_size;
    }

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    collector_result& operator =(_Inout_ collector_result&& rhs) noexcept;

private:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="pages">The list of pages collected until construction time.
    /// The callee takes ownership of the memory and will release it when
    /// destructed. The caller must make sure that the list is not dirty, i.e.
    /// that it does not have any in-flight writes.</para>
    collector_result(_In_ page *pages);

    iterator _end;
    std::unique_ptr<page> _pages;
    std::size_t _size;

    friend class atomic_collector<TValue, PageSize>;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/collector_result.inl"

#endif /* !defined(_PWROWG_COLLECTOR_RESULT_H) */
