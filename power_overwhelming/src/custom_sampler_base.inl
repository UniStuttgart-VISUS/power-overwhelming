// <copyright file="custom_sampler_base.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * ...::detail::custom_sampler_base<TDerived, TKey, TSensor>::default
 */
template<class TDerived, class TKey, class TSensor>
visus::power_overwhelming::detail::custom_sampler_base<TDerived, TKey, TSensor>
visus::power_overwhelming::detail::custom_sampler_base<TDerived, TKey,
    TSensor>::default_sampler;


/*
 * ...::custom_sampler_base<TDerived, TKey, TSensor>::~custom_sampler_base
 */
template<class TDerived, class TKey, class TSensor>
visus::power_overwhelming::detail::custom_sampler_base<TDerived, TKey,
        TSensor>::~custom_sampler_base(void) noexcept {
    std::lock_guard<decltype(this->_lock)> l(this->_lock);
    for (auto& g : this->_sensor_groups) {
        if (g.second->thread.joinable()) {
#if (defined(_WIN32) && (defined(DEBUG) || defined(_DEBUG)))
            {
                auto msg = "Terminating sampler for " + g.first + "\r\n";
                 ::OutputDebugStringA(msg.c_str());
            }
#endif /* (defined(_WIN32) && (defined(DEBUG) || defined(_DEBUG))) */

            {
                std::lock_guard<decltype(g.second->lock)> l(g.second->lock);
                g.second->sensors.clear();
            }

            g.second->thread.join();

#if (defined(_WIN32) && (defined(DEBUG) || defined(_DEBUG)))
            {
                auto msg = "Sampler for " + g.first + " joined.\r\n";
                ::OutputDebugStringA(msg.c_str());
            }
#endif /* (defined(_WIN32) && (defined(DEBUG) || defined(_DEBUG))) */
        }
    }
}


/*
 * ...::detail::custom_sampler_base<TDerived, TKey, TSensor>::add
 */
template<class TDerived, class TKey, class TSensor>
void visus::power_overwhelming::detail::custom_sampler_base<TDerived, TKey,
        TSensor>::add(_In_ const key_type& key, _In_ sensor_type sensor) {
    if (sensor == nullptr) {
        // Never sample invalid sensors.
        return;
    }

    std::lock_guard<decltype(this->_lock)> l(this->_lock);
    auto& group = this->_sensor_groups[key];

    if (group == nullptr) {
        // This is a new group without a running thread.
        auto that = static_cast<TDerived *>(this);
        group.reset(new sensor_group());
        group->interval = interval_type(sensor->async_sampling.interval());
        group->sensors.push_back(sensor);
        group->thread = std::thread(&TDerived::sample, that, key, group.get());

    } else {
        // This is an existing group, so the sampling interval must match.
        if (group->interval.count() != sensor->async_sampling.interval()) {
            throw std::invalid_argument("All sensors using the same RTA/RB "
                "instrument must be sampled at the same rate.");
        }

        std::lock_guard<decltype(group->lock)> l(group->lock);
        auto it = std::find(group->sensors.begin(), group->sensors.end(),
            sensor);
        if (it != group->sensors.end()) {
            throw std::invalid_argument("Asynchronous sampling cannot be "
                "started on a source that is already being sampled.");
        }

        group->sensors.push_back(sensor);
    }
}


/*
 * ..::detail::custom_sampler_base<TDerived, TKey, TSensor>::remove
 */
template<class TDerived, class TKey, class TSensor>
bool visus::power_overwhelming::detail::custom_sampler_base<TDerived, TKey,
        TSensor>::remove(_In_ const sensor_type sensor) {
    std::lock_guard<decltype(this->_lock)> l(this->_lock);

    if (sensor == nullptr) {
        // A nullptr could never have been added.
        return this->_sensor_groups.empty();
    }

    // 'wait' will designate the group to delete once we removed the sensor.
    // Assuming that this was not the last sensor, initialise this variable
    // with the end iterator.
    auto wait = this->_sensor_groups.end();

    for (auto git = this->_sensor_groups.begin();
            git != this->_sensor_groups.end(); ++git) {
        auto& group = git->second;

        std::lock_guard<decltype(group->lock)> l(group->lock);
        auto sit = std::remove(group->sensors.begin(), group->sensors.end(),
            sensor);

        if (sit != group->sensors.end()) {
            group->sensors.erase(sit, group->sensors.end());

            if (group->sensors.empty()) {
                // If the group is now empty, remember this in order to wait for
                // the thread to exit when outside the critical section of the
                // sensor list.
                wait = git;
            }

            // When adding sensors, we enforce that there can be only one, so if
            // we found it, we can stop searching other instances.
            break;
        }
    }

    if (wait != this->_sensor_groups.end()) {
        // If we removed the last sensor from a group, wait for this group's
        // thread to exit.
        wait->second->thread.join();
        this->_sensor_groups.erase(wait);
    }

    return this->_sensor_groups.empty();
}
