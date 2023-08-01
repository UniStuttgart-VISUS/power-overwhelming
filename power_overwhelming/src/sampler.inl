// <copyright file="sampler.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::detail::basic_sampler<TSource>::basic_sampler
 */
template<class TSource>
visus::power_overwhelming::detail::basic_sampler<TSource>::basic_sampler(
    _In_ const interval_type interval) : _interval(interval) { }


/*
 * visus::power_overwhelming::detail::basic_sampler<TSource>::~basic_sampler
 */
template<class TSource>
visus::power_overwhelming::detail::basic_sampler<TSource>::~basic_sampler(
        void) noexcept {
    {
        std::lock_guard<decltype(this->_lock)> l(this->_lock);
        this->_sources.clear();
    }
    this->_thread.join();
}


/*
 * visus::power_overwhelming::detail::basic_sampler<TSource>::samples
 */
template<class TSource>
bool visus::power_overwhelming::detail::basic_sampler<TSource>::samples(
        _In_opt_ const source_type source) const {
    if (sensor == nullptr) {
        // Trivial reject: we never sample nullptr.
        return false;
    }

    std::lock_guard<decltype(this->_lock)> l(this->_lock);
    return (this->_sources.find(source) != this->_sources.end());
}


/*
 * visus::power_overwhelming::detail::basic_sampler<TSource>::operator +=
 */
template<class TSource>
visus::power_overwhelming::detail::basic_sampler<TSource>&
visus::power_overwhelming::detail::basic_sampler<TSource>::operator +=(
        _In_ source_type source) {
    if (source != nullptr) {
        std::lock_guard<decltype(this->_lock)> l(this->lock);
        this->_sources.insert(source);

        if (!this->_thread.joinable()) {
            this->_thread = std::thread(&sampler::sample, this);
        }
    }

    return *this;
}


/*
 * visus::power_overwhelming::detail::basic_sampler<TSource>::operator -=
 */
template<class TSource>
visus::power_overwhelming::detail::basic_sampler<TSource>&
visus::power_overwhelming::detail::basic_sampler<TSource>::operator -=(
        _In_ source_type source) {
    auto wait_thread = false;

    if (source != nullptr) {
        std::lock_guard<decltype(this->_lock)> l(this->lock);
        auto it = std::remove(this->_sources.begin(),
            this->_sources.end(),
            source);
        this->_sources.erase(it, this->_sources.end());
        wait_thread = this->_sources.empty();
    }

    if (wait_thread) {
        this->_thread.join();
    }

    return *this;
}


/*
 * visus::power_overwhelming::detail::basic_sampler<TSource>::operator bool
 */
template<class TSource>
visus::power_overwhelming::detail::basic_sampler<TSource>::operator bool(
        void) const {
    std::lock_guard<decltype(this->_lock)> l(this->_lock);
    return !this->_sources.empty();
}


/*
 * visus::power_overwhelming::detail::basic_sampler<TSource>::sample
 */
template<class TSource>
void visus::power_overwhelming::detail::basic_sampler<TSource>::sample(void) {
    auto have_sensors = true;

    {
        std::stringstream stream;
        stream << "PwrOwg " << typeid(TContext).name()
            << " @" << this->_interval.count() << "us";
        auto name = stream.str();
        set_thread_name(name.c_str());
    }

    while (have_sensors) {
        auto now = std::chrono::high_resolution_clock::now();

        {
            std::lock_guard<decltype(this->lock)> l(this->lock);
            for (auto& s : this->_sources) {
                s->deliver_async();
            }

            have_sensors = !this->_sources.empty();
        }

        if (have_sensors) {
            std::this_thread::sleep_until(now + this->_interval);
        }
    }
}
