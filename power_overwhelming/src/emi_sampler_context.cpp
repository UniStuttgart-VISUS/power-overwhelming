// <copyright file="emi_sampler_context.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "emi_sampler_context.h"

#include "emi_sensor_impl.h"


/*
 * visus::power_overwhelming::detail::emi_sampler_context::add
 */
bool visus::power_overwhelming::detail::emi_sampler_context::add(
        sensor_type sensor, const measurement_callback callback, void *context) {
#if defined(_WIN32)
    assert(sensor != nullptr);
    assert(callback != nullptr);
    std::lock_guard<decltype(this->lock)> l(this->lock);

    auto it = this->sensors.find(sensor->device);
    if (it != this->sensors.end()) {
        // We already know the EMI device, but do not know yet whether we
        // already know the sensor, too.
        if (it->second.find(sensor) != it->second.end()) {
            // Sensor is already being sampled, so there is nothing to do.
            return false;

        } else {
            // Add the sensor to the existing device.
            it->second.emplace(sensor, std::make_pair(callback, context));
        }

    } else {
        // Need to sample a previously unknown device, so add it and its first
        // sensor.
        this->sensors[sensor->device].emplace(sensor,
            std::make_pair(callback, context));
    }

    if ((this->sensors.size() == 1) && !this->thread.joinable()) {
        // If this is the first sensor, we need to start a worker thread.
        this->thread = std::thread(&emi_sampler_context::sample, this);
    }

    return true;
#else /* defined(_WIN32) */
    return false;
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::detail::emi_sampler_context::remove
 */
bool visus::power_overwhelming::detail::emi_sampler_context::remove(
        sensor_type sensor) {
    assert(sensor != nullptr);
    std::lock_guard<decltype(this->lock)> l(this->lock);

    auto dit = this->sensors.find(sensor->device);
    auto retval = (dit != this->sensors.end());

    if (retval) {
        retval = (dit->second.erase(sensor) > 0);

        if (dit->second.empty()) {
            // If this was the last sensor on the given device, remove the
            // device itself from the list, which makes it cheaper to determine
            // whether the sampler should be stopped.
            this->sensors.erase(dit);
        }
    }

    return retval;
}


/*
 * visus::power_overwhelming::detail::emi_sampler_context::sample
 */
void visus::power_overwhelming::detail::emi_sampler_context::sample(void) {
#if defined(_WIN32)
    auto have_sensors = true;
    std::vector<std::uint8_t> sample;

    set_thread_name("PwrOwg Energy Meter Interface Sampler Thread");

    while (have_sensors) {
        auto now = std::chrono::high_resolution_clock::now();

        {
            std::lock_guard<decltype(this->lock)> l(this->lock);
            for (auto& d : this->sensors) {
                auto device = d.first;
                auto& sensors = d.second;
                auto version = device->version().EmiVersion;

                for (auto s : sensors) {
                    auto sensor = s.first;
                    auto callback = s.second.first;
                    auto context = s.second.second;

                    if (sample.empty()) {
                        sample = sensor->sample();
                    }

                    callback(sensor->evaluate(sample, version,
                        timestamp_resolution::milliseconds), context);
                }

                sample.clear();
            }

            have_sensors = !this->sensors.empty();
        }

        if (have_sensors) {
            std::this_thread::sleep_until(now + this->interval);
        }
    }
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::detail::emi_sampler_context::samples
 */
bool visus::power_overwhelming::detail::emi_sampler_context::samples(
        const sensor_type sensor) {
    assert(sensor != nullptr);
    std::lock_guard<decltype(this->lock)> l(this->lock);
    auto it = this->sensors.find(sensor->device);
    return (it != this->sensors.end())
        && (it->second.find(sensor) != it->second.end());
}
