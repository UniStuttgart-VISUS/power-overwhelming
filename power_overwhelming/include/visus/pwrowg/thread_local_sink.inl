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

    {
        // The first sample callback must store the sensor list such that
        // the writer can use it.
        const sensor_description *expected = nullptr;
        that->_sensors.compare_exchange_strong(expected, sensors);
    }

    if (!that->_running.load(std::memory_order_acquire)) {
        // If we are not running, we do not have to care about the samples.
        return;
    }

    // Find out the buffer index for the current thread and instance.
    auto& tlb = thread_local_sink::buffer[that];
    PWROWG_TRACE(_T("Sample callback is using sink %zu in 0x%p."), tlb, that);

    if (tlb >= that->_buffers.size()) {
        // If we do not have a page for the calling thread, search one that is
        // empty.
        std::unique_lock<decltype(that->_lock)> lock(that->_lock);
        for (std::size_t i = 0; i < that->_buffers.size(); ++i) {
            if (that->_buffers[i].empty()) {
                tlb = i;
                break;
            }
        }

        // If we did not find a page, create one.
        if (tlb >= that->_buffers.size()) {
            that->_buffers.emplace_back();
            PWROWG_TRACE(_T("Allocated a new buffer for 0x%p. There are now ")
                _T("%zu buffers."), that, that->_buffers.size());
            tlb = that->_buffers.size() - 1;
        }

        PWROWG_TRACE(_T("Make sure that sink %zu in 0x%p has at least %zu ")
            _T("reserved."), tlb, that, that->_page_size);
        that->_buffers[tlb].reserve(that->_page_size);
    }

    assert(tlb < that->_buffers.size());
    auto& buffer = that->_buffers[tlb];

    // Copy the samples to the page.
    std::copy_n(samples, cnt, std::back_inserter(buffer));

    if (buffer.size() >= that->_page_size) {
        PWROWG_TRACE(_T("Publish page %zu in 0x%p as it contains %zu ")
            _T("elements."), tlb, that, buffer.size());
        std::unique_lock<decltype(that->_lock)> lock(that->_lock);
        that->_ready.push_back(tlb);
        tlb = (std::numeric_limits<std::size_t>::max)();
        PWROWG_TRACE(_T("Waking writer to read page %zu in 0x%p. Next index ")
            _T("for sample callback in this thread is %zu."),
            that->_ready.back(), that, tlb);
        lock.unlock();
        that->_condition.notify_one();
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
    this->dispose();
}


/*
 * PWROWG_NAMESPACE::thread_local_sink<TSink>::dispose
 */
template<class TSink>
void PWROWG_NAMESPACE::thread_local_sink<TSink>::dispose(void) noexcept {
    this->_running.store(false, std::memory_order_release);
    this->_condition.notify_all();
    if (this->_writer.joinable()) {
        this->_writer.join();
    }
}


/*
 * PWROWG_NAMESPACE::thread_local_sink<TSink>::buffer
 */
template<class TSink>
thread_local std::map<PWROWG_NAMESPACE::thread_local_sink<TSink> *, std::size_t>
PWROWG_NAMESPACE::thread_local_sink<TSink>::buffer;


/*
 * PWROWG_NAMESPACE::thread_local_sink<TSink>::write
 */
template<class TSink> void PWROWG_NAMESPACE::thread_local_sink<TSink>::write(
        void) {
    PWROWG_THREAD_STATS(_T("thread_local_sink_write.json"));
    set_thread_name("PwrOwg Writer");

    while (this->_running.load(std::memory_order_acquire)) {
        std::unique_lock<decltype(this->_lock)> lock(this->_lock);
        this->_condition.wait(lock, [this](void) {
            const auto running = this->_running.load(std::memory_order_acquire);
            return (!this->_ready.empty() || !running);
        });
        PWROWG_TRACE(_T("TLS writer is awake."));

        if (this->_sensors.load(std::memory_order_acquire) == nullptr) {
            // This should only happen when an exit was requested, so we
            // skip the loop and check again.
            continue;
        }

        for (auto& r : this->_ready) {
            assert(this->_sensors.load() != nullptr);
            PWROWG_TRACE(_T("TLS writer writes buffer %zu containing %zu ")
                _T("elements."), r, this->_buffers[r].size());
            auto buffer = std::move(this->_buffers[r]);
            TSink::write_samples(buffer.begin(), buffer.end(),
                this->_sensors.load(std::memory_order_acquire));
            buffer.clear();
            std::swap(buffer, this->_buffers[r]);
        }

        this->_ready.clear();
    }
    PWROWG_TRACE(_T("TLS writer is finalising the output."));

    if (this->_sensors.load(std::memory_order_acquire) != nullptr) {
        // There might be something left that has not yet been written. We must
        // hold the lock here, because a callback might have already started to
        // write when the exit request was received.
        std::unique_lock<decltype(this->_lock)> lock(this->_lock);
        PWROWG_TRACE(_T("TLS writer flushes buffers."));
        for (auto& b : this->_buffers) {
            TSink::write_samples(
                b.begin(),
                b.end(),
                this->_sensors.load(std::memory_order_acquire));
        }
    }

    PWROWG_TRACE(_T("TLS writer is exiting."));
}
