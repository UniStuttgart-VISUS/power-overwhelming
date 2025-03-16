// <copyright file="atomic_collector.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE:::atomic_collector<TValue, PageSize>::~atomic_collector
 */
template<class TValue, std::size_t PageSize>
PWROWG_NAMESPACE::atomic_collector<TValue, PageSize>::~atomic_collector(
        void) noexcept {
    auto p = this->_pages.exchange(nullptr, std::memory_order_acq_rel);

    if (p != nullptr) {
        delete p;
    }
}


/*
 * PWROWG_NAMESPACE::atomic_collector<TValue, PageSize>::reset
 */
template<class TValue, std::size_t PageSize>
typename PWROWG_NAMESPACE::atomic_collector<TValue, PageSize>::result_type
PWROWG_NAMESPACE::atomic_collector<TValue, PageSize>::reset(void) {
    auto head = new page_type();

    // Swap the current head of the list we want to return with our new one.
    auto retval = this->_pages.load(std::memory_order_acquire);
    while (!this->_pages.compare_exchange_weak(retval, head));

    // There might be a producer still writing on the pages we just took over, so
    // we spin until all pending writes have completed.
    for (auto p = retval; p != nullptr; p = p->next) {
        p->wait();
    }

    return result_type(retval);
}


/*
 * PWROWG_NAMESPACE::atomic_collector<TValue, PageSize>::reserve
 */
template<class TValue, std::size_t PageSize>
void PWROWG_NAMESPACE::atomic_collector<TValue, PageSize>::reserve(
        _Out_ page_type *& page,
        _Out_ std::size_t& index) {
    static const std::hash<std::thread::id> thread_hash;
    bool second_chance = true;

    page = this->_pages.load(std::memory_order_acquire);

    while (true) {
        // Optimistically reserve a slot by incrementing the 'used' counter.
        index = page->used.fetch_add(1);
        if (index < PageSize) {
            return;
        }

        // Undo the increment, because the page would be dirty forever otherwise.
        page->used.fetch_sub(1);

        // Under heavy load, there is a high chance that someone else has
        // allocated a new head already at this point, so we give it a second
        // chance to reduce the amount of discarded pages below. In the test,
        // this reduces the number of discarded pages by around 20%.
        if (second_chance) {
            second_chance = false;
            std::this_thread::yield();

            page = this->_pages.load(std::memory_order_acquire);
            if (page->used.load(std::memory_order_acquire) < PageSize) {
                continue;
            }
        }

        // Try adding a new page as the current head is full. If we fail here,
        // someone else has updated the head and we therefore do not try again,
        // but check whether we can use their page (remember that the CAS will
        // give us the page the other thread has added as output in 'page').
        auto head = std::make_unique<page_type>();
        head->next = page;
        if (this->_pages.compare_exchange_strong(page, head.get())) {
            // If we succeeded, our new 'head' is the new 'page' to test.
            page = head.release();

        } else {
            // Erase the previous head from the 'next' pointer to prevent
            // deletion of the list if we release 'head' now.
            head->next = nullptr;
#if defined(PWROWG_PROFILE_ATOMIC_COLLECTOR)
            ++this->_alloc_discarded;
#endif /* defined(PWROWG_PROFILE_ATOMIC_COLLECTOR) */
        }
    }
}
