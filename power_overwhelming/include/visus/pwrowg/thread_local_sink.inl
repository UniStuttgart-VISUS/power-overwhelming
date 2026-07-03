// <copyright file="thread_local_sink.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::thread_local_sink<TSink>::sample_callback
 */
template<class TSink>
void PWROWG_NAMESPACE::thread_local_sink<TSink>::sample_callback(
        _In_reads_(cnt) const sample *samples,
        _In_ const std::size_t cnt,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context) {
    assert(context != nullptr);
    auto that = static_cast<thread_local_sink *>(context);

    if (!that->_running.load(std::memory_order_acquire)) {
        PWROWG_TRACE(_T("Discarding samples because the sink 0x%p is in the ")
            _T("process of shutting down."), that);
        return;
    }

    {
        // The first sample callback must store the sensor list such that
        // the writer can use it.
        const sensor_description *expected = nullptr;
        that->_sensors.compare_exchange_strong(expected, sensors,
            std::memory_order_acq_rel, std::memory_order_relaxed);
    }

    // Find out whether we already have a page assigned to this thread.
    auto it = thread_local_sink::buffer.find(that);
    if (it == thread_local_sink::buffer.end()) {
        thread_local_sink::buffer[that] = nullptr;
    }
    auto& p = thread_local_sink::buffer[that];
    PWROWG_TRACE(_T("Sample callback is using page 0x%p in 0x%p."), p, that);

    // If the page was already assigned to this thread, mark it as receiving
    // data from us. As the state of the sink and the state of the page are
    // independent, we must make sure that the writer has not received a
    // shutdown request in the meantime and marked the page as revoked.
    if (p != nullptr) {
        auto e = p->state.load(std::memory_order_acquire);
        if ((e & page_state::assigned) != page_state::assigned) {
            PWROWG_TRACE(_T("Page 0x%p in 0x%p is not assigned to a thread ")
                _T("anymore, which means that the sink is shutting down."),
                p, that);
            assert(!that->_running.load(std::memory_order_acquire));
            return;
        }
        if (!p->state.compare_exchange_strong(e, page_state::assigned_callback,
                std::memory_order_acq_rel, std::memory_order_relaxed)) {
            PWROWG_TRACE(_T("Page 0x%p in 0x%p has been removed from a this ")
                _T("thread, which means that the sink has started shutting ")
                _T("down."), p, that);
            assert(!that->_running.load(std::memory_order_acquire));
            return;
        }
    }
    assert((p == nullptr) || (p->is_state(page_state::assigned_callback)));

    // If we do not have a page, check the page list for one to reuse and put it
    // into the assigned and callback writing state directly.
    if (p == nullptr) {
        p = that->_pages.load(std::memory_order_acquire);
        while (p != nullptr) {
            auto e = page_state::reusable;
            if (p->state.compare_exchange_strong(e,
                    page_state::assigned_callback,
                    std::memory_order_acq_rel,
                    std::memory_order_relaxed)) {
                PWROWG_TRACE(_T("Reusing page 0x%p for sink 0x%p."), p, that);
                thread_local_sink::buffer[that] = p;
                assert(p->buffer.empty());
                assert(p->buffer.capacity() >= that->_page_size);
                break;
            }

            p = p->next;
        }
    }
    assert((p == nullptr) || (p->is_state(page_state::assigned_callback)));

    // If we still do not have a page, create a new one.
    if (p == nullptr) {
        p = thread_local_sink::buffer[that] = new page(that->_page_size);
        assert(p->is_state(page_state::assigned));
        assert(p->is_state(page_state::callback));
        assert(p->buffer.empty());
        assert(p->buffer.capacity() >= that->_page_size);
        PWROWG_TRACE(_T("Allocated a new page 0x%p for sink 0x%p."), p, that);

        // Swap the root node until we succeed to store our page.
        auto e = p->next = that->_pages.load(std::memory_order_acquire);
        while (!that->_pages.compare_exchange_weak(e, p,
                std::memory_order_acq_rel,
                std::memory_order_acquire)) {
            p->next = e;
        }
    }

    // Copy the samples to the page.
    assert((p != nullptr) && (p->is_state(page_state::callback)));
    std::copy_n(samples, cnt, std::back_inserter(p->buffer));

    // Notify the writer if the page is now full.
    if (p->buffer.size() >= that->_page_size) {
        PWROWG_TRACE(_T("Publish page 0x%p to sink 0x%p as it contains %zu ")
            _T("elements."), p, that, p->buffer.size());
        assert(p->is_state(page_state::callback));
        assert(p->is_state(page_state::assigned));
        p->state.store(page_state::writing,
            std::memory_order::memory_order_release);
        set_event(that->_event);
        p = nullptr;

    } else {
        auto e = page_state::assigned_callback;
        p->state.compare_exchange_strong(e,
            page_state::assigned,
            std::memory_order_acq_rel,
            std::memory_order_relaxed);
    }
}


/*
 * PWROWG_NAMESPACE::thread_local_sink<TSink>::atomic_sink
 */
template<class TSink>
template<class... TArgs>
PWROWG_NAMESPACE::thread_local_sink<TSink>::thread_local_sink(
        _In_ const std::size_t page_size, TArgs&&... args)
    : TSink(std::forward<TArgs>(args)...),
        _event(create_event()),
        _pages(nullptr),
        _page_size(page_size),
        _running(true),
        _sensors(nullptr) {
    this->_writer = std::thread(&thread_local_sink::write, this);
}


/*
 * PWROWG_NAMESPACE::thread_local_sink<TSink>::~thread_local_sink
 */
template<class TSink>
PWROWG_NAMESPACE::thread_local_sink<TSink>::~thread_local_sink(void) noexcept {
    pwrowg_on_exit([this]() { destroy_event(this->_event); });
    this->dispose();
}


/*
 * PWROWG_NAMESPACE::thread_local_sink<TSink>::dispose
 */
template<class TSink>
void PWROWG_NAMESPACE::thread_local_sink<TSink>::dispose(void) noexcept {
    // Signal the writer to exit and wake it.
    this->_running.store(false, std::memory_order_release);
    set_event(this->_event);
    if (this->_writer.joinable()) {
        this->_writer.join();
    }

    // Delete all the pages. No one should be writing to them anymore as the
    // writer will block on pages that are still in use when exiting.
    auto p = this->_pages.load(std::memory_order_acquire);
    while (p != nullptr) {
        assert(!p->is_state(page_state::callback));
        assert(!p->is_state(page_state::writing));
        auto n = p->next;
        delete p;
        p = n;
    }

    this->_pages.store(nullptr, std::memory_order_release);
}


/*
 * PWROWG_NAMESPACE::thread_local_sink<TSink>::buffer
 */
template<class TSink>
thread_local std::map<PWROWG_NAMESPACE::thread_local_sink<TSink> *,
    typename PWROWG_NAMESPACE::thread_local_sink<TSink>::page *>
PWROWG_NAMESPACE::thread_local_sink<TSink>::buffer;


/*
 * PWROWG_NAMESPACE::thread_local_sink<TSink>::write
 */
template<class TSink> void PWROWG_NAMESPACE::thread_local_sink<TSink>::write(
        void) {
    PWROWG_THREAD_STATS(_T("thread_local_sink_write.json"));
    set_thread_name("PwrOwg Writer");

    while (this->_running.load(std::memory_order_acquire)) {
        wait_event(this->_event);
        PWROWG_TRACE(_T("TLS writer is awake."));

        if (this->_sensors.load(std::memory_order_acquire) == nullptr) {
            // This should only happen when an exit was requested before
            // anything has been written, so we skip the loop and check again.
            assert(!this->_running.load(std::memory_order_acquire));
            continue;
        }

        // Check all pages for those that are ready to be written.
        auto p = this->_pages.load(std::memory_order_acquire);
        while (p != nullptr) {
            if (p->is_state(page_state::writing)) {
                this->write_samples(p);
            }
            p = p->next;
        }
    }
    PWROWG_TRACE(_T("TLS writer is finalising the output."));

    if (this->_sensors.load(std::memory_order_acquire) != nullptr) {
        // Move out all pending data in the buffers.
        auto p = this->_pages.load(std::memory_order_acquire);
        while (p != nullptr) {
            auto e = page_state::assigned;

            // First of all, make sure that the page is removed from any thread
            // by transitioning from the 'assigned' state to the 'writing'
            // state. If that fails, we need to check whether the page was not
            // assigned in the first place or whether it was being written to
            // by the callback.
            while (!p->state.compare_exchange_weak(e, page_state::writing,
                    std::memory_order_acq_rel, std::memory_order_acquire)) {
                if ((e & page_state::callback) == page_state::callback) {
                    PWROWG_TRACE(_T("Page 0x%p is still in use."), p);
                    wait_event(this->_event);

                } else if ((e & page_state::writing) == page_state::writing) {
                    PWROWG_TRACE(_T("Page 0x%p happened to be finished."), p);
                    break;

                } else if (e == page_state::reusable) {
                    PWROWG_TRACE(_T("Page 0x%p was empty."), p);
                    break;
                }

                e = page_state::assigned;
            }

            if (p->is_state(page_state::writing)) {
                this->write_samples(p);
            }

            p = p->next;
        }
    }

    PWROWG_TRACE(_T("TLS writer is exiting."));
}


/*
 * PWROWG_NAMESPACE::thread_local_sink<TSink>::write_samples
 */
template<class TSink>
void PWROWG_NAMESPACE::thread_local_sink<TSink>::write_samples(_In_ page *p) {
    assert(p != nullptr);
    assert(p->is_state(page_state::writing));
    PWROWG_TRACE(_T("TLS writer writes buffer 0x%p containing %zu elements."),
        p, p->buffer.size());
    const auto sensors = this->_sensors.load(std::memory_order_acquire);
    assert(sensors != nullptr);
    TSink::write_samples(p->buffer.begin(), p->buffer.end(), sensors);
    p->buffer.clear();
    p->buffer.reserve(this->_page_size);
    p->state.store(page_state::reusable, std::memory_order_release);
}
