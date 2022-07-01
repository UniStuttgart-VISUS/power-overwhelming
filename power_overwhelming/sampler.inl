// <copyright file="sampler.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::detail::sampler<TContext>::~sampler
 */
template<class TContext>
visus::power_overwhelming::detail::sampler<TContext>::~sampler(void) {
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
 * visus::power_overwhelming::detail::sampler<TContext>::add
 */
template<class TContext>
bool visus::power_overwhelming::detail::sampler<TContext>::add(
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
        return this->_contexts.back()->add(sensor, callback, user_context);

    } else {
        // Otherwise, add the sensor to the existing context.
        return (**it).add(sensor, callback, user_context);
    }
}


/*
 * visus::power_overwhelming::detail::sampler<TContext>::remove
 */
template<class TContext>
bool visus::power_overwhelming::detail::sampler<TContext>::remove(
        sensor_type sensor) {
    if (sensor == nullptr) {
        // Trivial reject: we never sample nullptrs.
        return false;
    }

    auto retval = false;

    std::lock_guard<decltype(this->_lock)> l(this->_lock);
    for (auto& c : this->_contexts) {
        assert(c != nullptr);
        std::lock_guard<decltype(c->lock)> ll(c->lock);
        if (c->sensors.erase(sensor) > 0) {
            // Erase the sensor, but continue searching the other contexts.
            retval = true;
        }
    }

    return retval;
}


/*
 * visus::power_overwhelming::detail::sampler<TContext>::samples
 */
template<class TContext>
bool visus::power_overwhelming::detail::sampler<TContext>::samples(
        sensor_type sensor) const {
    if (sensor == nullptr) {
        // Trivial reject: we never sample nullptrs.
        return false;
    }

    std::lock_guard<decltype(this->_lock)> l(this->_lock);
    for (auto& c : this->_contexts) {
        assert(c != nullptr);
        std::lock_guard<decltype(c->lock)> ll(c->lock);
        if (c->sensors.find(sensor) != c->sensors.end()) {
            // It is sufficient if we find one.
            return true;
        }
    }
    // Not found in any context at this point.

    return false;
}


/*
 * visus::power_overwhelming::detail::sampler<TContext>::samples
 */
template<class TContext>
bool visus::power_overwhelming::detail::sampler<TContext>::samples(
        void) const {
    std::lock_guard<decltype(this->_lock)> l(this->_lock);
    for (auto& c : this->_contexts) {
        if (!c->sensors.empty()) {
            return true;
        }
    }
    // No non-empty context found at this point.

    return false;
}
