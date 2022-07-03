// <copyright file="default_sampler_context.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::detail::default_sampler_context<TSensorImpl>::add
 */
template<class TSensorImpl>
bool visus::power_overwhelming::detail::default_sampler_context<TSensorImpl>
::add(sensor_type sensor, const measurement_callback callback, void *context) {
    assert(sensor != nullptr);
    assert(callback != nullptr);
    std::lock_guard<decltype(this->lock)> l(this->lock);

    if (this->sensors.find(sensor) != this->sensors.end()) {
        // Sensor is already being sampled, so there is nothing to do.
        return false;
    }

    this->sensors.emplace(sensor, std::make_pair(callback, context));

    if ((this->sensors.size() == 1) && !this->thread.joinable()) {
        // If this is the first sensor, we need to start a worker thread.
        this->thread = std::thread(&default_sampler_context::sample, this);
    }

    return true;
}


/*
 * ...::detail::default_sampler_context<TSensorImpl>::sample
 */
template<class TSensorImpl>
void visus::power_overwhelming::detail::default_sampler_context<TSensorImpl>
::sample(void) {
    auto have_sensors = true;

    while (have_sensors) {
        auto now = std::chrono::high_resolution_clock::now();

        {
            std::lock_guard<decltype(this->lock)> l(this->lock);
            for (auto& s : this->sensors) {
                s.second.first(s.first->sample(), s.second.second);
            }

            have_sensors = !this->sensors.empty();
        }

        if (have_sensors) {
            std::this_thread::sleep_until(now + this->interval);
        }
    }
}
