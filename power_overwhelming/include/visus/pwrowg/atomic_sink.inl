// <copyright file="atomic_sink.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::atomic_sink<TSink, PageSize>::sample_callback
 */
template<class TSink, std::size_t PageSize>
void PWROWG_NAMESPACE::atomic_sink<TSink, PageSize>::sample_callback(
        _In_reads_(cnt) const sample *samples,
        _In_ const std::size_t cnt,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context) {
    assert(context != nullptr);
    auto that = static_cast<atomic_sink *>(context);

    {
        const sensor_description *expected = nullptr;
        that->_sensors.compare_exchange_strong(expected, sensors);
    }

    for (std::size_t i = 0; i < cnt; ++i) {
        that->_collector.push(samples[i]);
    }
}


/*
 * PWROWG_NAMESPACE::atomic_sink<TSink, PageSize>::atomic_sink
 */
template<class TSink, std::size_t PageSize>
template<class TRep, class TPeriod, class... TArgs>
PWROWG_NAMESPACE::atomic_sink<TSink, PageSize>::atomic_sink(
        _In_ const std::chrono::duration<TRep, TPeriod> interval,
        TArgs&&... args)
    : TSink(std::forward<TArgs>(args)...), 
        _interval(std::chrono::duration_cast<decltype(_interval)>(interval)),
        _running(true),
        _sensors(nullptr) {
    this->_writer = std::thread(&atomic_sink::write, this);
}


/*
 * PWROWG_NAMESPACE::atomic_sink<TSink, PageSize>::~atomic_sink
 */
template<class TSink, std::size_t PageSize>
PWROWG_NAMESPACE::atomic_sink<TSink, PageSize>::~atomic_sink(void) noexcept {
    this->_running.store(false, std::memory_order_release);

    if (this->_writer.joinable()) {
        this->_writer.join();
    }
}


/*
 * PWROWG_NAMESPACE::atomic_sink<TSink, PageSize>::write
 */
template<class TSink, std::size_t PageSize>
void PWROWG_NAMESPACE::atomic_sink<TSink, PageSize>::write(void) {
    set_thread_name("PwrOwg Writer");

    while (this->_running.load(std::memory_order_acquire)) {
        std::this_thread::sleep_for(this->_interval);
        if (this->_sensors == nullptr) {
            continue;
        }

        auto samples = this->_collector.reset();
        TSink::write_samples(samples.begin(), samples.end(), this->_sensors);
    }

    // There might be dangling stuff in the collector.
    if (this->_sensors != nullptr) {
        auto samples = this->_collector.reset();
        TSink::write_samples(samples.begin(), samples.end(), this->_sensors);
    }
}
