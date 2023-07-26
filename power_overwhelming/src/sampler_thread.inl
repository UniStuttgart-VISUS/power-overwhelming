// <copyright file="sampler_thread.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * ...::basic_sampler_thread<TContext>::~basic_sampler_thread
 */
template<class TContext>
visus::power_overwhelming::detail::basic_sampler_thread<TContext>
::~basic_sampler_thread(void) {
    std::lock_guard<decltype(this->_lock)> l(this->_lock);

    for (auto& c : this->_contexts) {
        // Clear all sensors, which makes the threads exit.
        {
            std::lock_guard<decltype(c->lock)> ll(c->lock);
            c->sensors.clear();
        }

        // Detach thread and let it exit asynchronously.
        if (c->thread.joinable()) {
            c->thread.detach();
        }
    }
}


/*
 * visus::power_overwhelming::detail::basic_sampler_thread<TContext>::add
 */
template<class TContext>
bool visus::power_overwhelming::detail::basic_sampler_thread<TContext>::add(
        sensor_type sensor, const measurement_callback callback,
        void *user_context, const interval_type interval) {
    if (sensor == nullptr) {
        throw std::invalid_argument("Sensors to be sampled must be a valid "
            "pointer.");
    }
    if (callback == nullptr) {
        throw std::invalid_argument("A valid callback must be provided to "
            "sample a sensor.");
    }

    std::lock_guard<decltype(this->_lock)> l(this->_lock);
    // Search a context with the same sampling interval as the requested one.
    auto it = this->_contexts.begin();
    for (; it != this->_contexts.end(); ++it) {
        assert(*it != nullptr);
        if ((**it).interval == interval) {
            break;
        }
    }

    if (it == this->_contexts.end()) {
        // If we have reached the end of the context list, we have no context
        // for the requested interval, so we need to create a new one.
        this->_contexts.emplace_back(new context_type());
        this->_contexts.back()->interval = interval;
        return this->_contexts.back()->add(sensor, callback, user_context);

    } else {
        // Otherwise, add the sensor to the existing context.
        return (**it).add(sensor, callback, user_context);
    }
}


/*
 * visus::power_overwhelming::detail::basic_sampler_thread<TContext>::remove
 */
template<class TContext>
bool visus::power_overwhelming::detail::basic_sampler_thread<TContext>::remove(
        sensor_type sensor) {
    if (sensor == nullptr) {
        // Trivial reject: we never sample nullptrs.
        return false;
    }

    auto retval = false;

    std::lock_guard<decltype(this->_lock)> l(this->_lock);
    for (auto& c : this->_contexts) {
        assert(c != nullptr);
        if (c->remove(sensor)) {
            // Continue searching the other contexts, but remember result.
            retval = true;
        }
    }

    return retval;
}


/*
 * visus::power_overwhelming::detail::basic_sampler_thread<TContext>::samples
 */
template<class TContext>
bool visus::power_overwhelming::detail::basic_sampler_thread<TContext>::samples(
        sensor_type sensor) const {
    if (sensor == nullptr) {
        // Trivial reject: we never sample nullptrs.
        return false;
    }

    std::lock_guard<decltype(this->_lock)> l(this->_lock);
    for (auto& c : this->_contexts) {
        assert(c != nullptr);
        if (c->samples(sensor)) {
            // It is sufficient if we find one context with the sensor.
            return true;
        }
    }
    // Not found in any context at this point.

    return false;
}


/*
 * visus::power_overwhelming::detail::basic_sampler_thread<TContext>::samples
 */
template<class TContext>
bool visus::power_overwhelming::detail::basic_sampler_thread<TContext>::samples(
        void) const {
    std::lock_guard<decltype(this->_lock)> l(this->_lock);
    return !this->_contexts.empty();
}


/*
 * visus::power_overwhelming::detail::basic_sampler_thread<TContext>::sample
 */
template<class TContext>
void visus::power_overwhelming::detail::basic_sampler_thread<TContext>::sample(
        void) {
    auto have_sensors = true;

    {
        std::stringstream stream;
        stream << "PwrOwg " << typeid(TContext).name() << " "
            << this->_interval.count() << "us";
        auto name = stream.str();
        set_thread_name(name.c_str());
    }

    while (have_sensors) {
        auto now = std::chrono::high_resolution_clock::now();

        {
            std::lock_guard<decltype(this->lock)> l(this->lock);
            for (auto& c : this->_contexts) {
                c.source->sample(c.configuration);
            }

            have_sensors = !this->_contexts.empty();
        }

        if (have_sensors) {
            std::this_thread::sleep_until(now + this->_interval);
        }
    }
}
