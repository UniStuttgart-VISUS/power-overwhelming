// <copyright file="collector_result.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::collector_result<TValue, PageSize>::::page::operator new
 */
template<class TValue, std::size_t PageSize>
void *PWROWG_NAMESPACE::collector_result<TValue, PageSize>::page
::operator new(const std::size_t size) {
    auto retval = allocate_for_atomic(size);
    assert(reinterpret_cast<std::uintptr_t>(retval) % false_sharing_range == 0);
    return retval;
}


/*
 * PWROWG_NAMESPACE::collector_result<TValue, PageSize>::page::~page
 */
template<class TValue, std::size_t PageSize>
PWROWG_NAMESPACE::collector_result<TValue, PageSize>::page::~page(
        void) {
    // The following must hold here, because we must never free a page that is
    // still written to. If this assertion triggers, this is not a bug here, but
    // in the management of the page's life time.
    assert(this->ready == this->used);

    for (std::size_t i = 0; i < this->ready; ++i) {
        this->value(i).~TValue();
    }

    // Transform the deletion of linked list to iterative algorithm as the
    // recursive delete may cause a stack overflow if the list is long.
    for (auto p = this->next; p != nullptr;) {
        auto q = p->next;
        p->next = nullptr;
        delete p;
        p = q;
    }
}


/*
 * PWROWG_NAMESPACE::collector_result<TValue, PageSize>::page::wait
 */
template<class TValue, std::size_t PageSize>
void PWROWG_NAMESPACE::collector_result<TValue, PageSize>::page::wait(
        void) const noexcept {
    while (this->ready.load(std::memory_order_acquire)
            != this->used.load(std::memory_order_acquire)) {
        std::this_thread::yield();
    }
}


/*
 * PWROWG_NAMESPACE::collector_result<TValue, PageSize>::operator ++
 */
template<class TValue, std::size_t PageSize>
typename PWROWG_NAMESPACE::collector_result<TValue, PageSize>::iterator&
PWROWG_NAMESPACE::collector_result<TValue, PageSize>::iterator::operator ++(
        void) noexcept {
    assert(this->_page != nullptr);
    assert(this->_index <= this->_page->ready);

    if (++this->_index == this->_page->ready) {
        if (this->_page->next != nullptr) {
            this->_page = this->_page->next;
            this->_index = 0;
        }
    }

    return *this;
}


#if (defined(DEBUG) || defined(_DEBUG))
/*
 * PWROWG_NAMESPACE::collector_result<TValue, PageSize>:pages
 */
template<class TValue, std::size_t PageSize>
std::size_t PWROWG_NAMESPACE::collector_result<TValue, PageSize>::pages(
        void) const noexcept {
    std::size_t retval = 0;

    for (auto p = this->_pages.get(); p != nullptr; p = p->next) {
        ++retval;
    }

    return retval;
}
#endif /* (defined(DEBUG) || defined(_DEBUG)) */


/*
 * PWROWG_NAMESPACE::collector_result<TValue, PageSize>::operator =
 */
template<class TValue, std::size_t PageSize>
PWROWG_NAMESPACE::collector_result<TValue, PageSize>&
PWROWG_NAMESPACE::collector_result<TValue, PageSize>::operator =(
        _Inout_ collector_result&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_end = std::move(rhs._end);
        this->_pages = std::move(rhs._pages);
        this->_size = rhs._size;
        rhs._size = 0;
    }
}


/*
 * PWROWG_NAMESPACE::collector_result<TValue, PageSize>::collector_result
 */
template<class TValue, std::size_t PageSize>
PWROWG_NAMESPACE::collector_result<TValue, PageSize>::collector_result(
        _In_ page *pages) : _pages(pages), _size(0) {
    assert(pages != nullptr);

    for (auto p = pages; p != nullptr; p = p->next) {
        // The atomic_collector should only construct the result from pages
        // that are not dirty.
        assert(p->ready == p->used);

        this->_size += p->ready;

        // As the result collection is immutable, we can construct the end
        // iterator here and keep it forever.
        this->_end._page = p;
    }

    this->_end._index = this->_end._page->ready;
}
