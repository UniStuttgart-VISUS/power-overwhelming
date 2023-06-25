// <copyright file="msr_sampler_context.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "msr_sampler_context.h"

#include "msr_sensor_impl.h"


/*
 * visus::power_overwhelming::detail::msr_sampler_context::add
 */
bool visus::power_overwhelming::detail::msr_sampler_context::add(
        _In_ sensor_type sensor,
        _In_ const timestamp_resolution timestamp_resolution,
        _In_ const measurement_callback callback,
        _In_opt_ void *context) {
    assert(sensor != nullptr);
    assert(callback != nullptr);
    std::lock_guard<decltype(this->lock)> l(this->lock);

    auto it = this->sensors.find(sensor->device);
    if (it != this->sensors.end()) {
        // We already know the device file, but do not know yet whether we
        // already know the sensor (for a specific register), too.
        if (it->second.find(sensor) != it->second.end()) {
            // Sensor is already being sampled, so there is nothing to do.
            return false;

        } else {
            // Add the sensor to the existing device.
            it->second.emplace(sensor, sensor_config(timestamp_resolution,
                callback, context));
        }

    } else {
        // Need to sample a previously unknown device, so add it and its first
        // sensor.
        this->sensors[sensor->device].emplace(sensor, sensor_config(
            timestamp_resolution, callback, context));
    }

    if ((this->sensors.size() == 1) && !this->thread.joinable()) {
        // If this is the first sensor, we need to start a worker thread.
        this->thread = std::thread(&msr_sampler_context::sample, this);
    }

    return true;
}


/*
 * visus::power_overwhelming::detail::msr_sampler_context::remove
 */
bool visus::power_overwhelming::detail::msr_sampler_context::remove(
        _In_ sensor_type sensor) {
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
 * visus::power_overwhelming::detail::msr_sampler_context::sample
 */
void visus::power_overwhelming::detail::msr_sampler_context::sample(void) {
    auto have_sensors = true;
    std::vector<std::uint8_t> sample;

    set_thread_name("PwrOwg Machine-Specific Register Sampler Thread");

    while (have_sensors) {
        auto now = std::chrono::high_resolution_clock::now();

        {
            std::lock_guard<decltype(this->lock)> l(this->lock);
            for (auto& d : this->sensors) {
                auto device = d.first;
                auto& sensors = d.second;

                for (auto s : sensors) {
                    auto sensor = s.first;

                    // TODO
                    s.second.callback(measurement(s.first->sensor_name.c_str(),
                        sensor->sample(s.second.resolution)),
                        s.second.context);
                }

                sample.clear();
            }

            have_sensors = !this->sensors.empty();
        }

        if (have_sensors) {
            std::this_thread::sleep_until(now + this->interval);
        }
    }
}


/*
 * visus::power_overwhelming::detail::msr_sampler_context::samples
 */
bool visus::power_overwhelming::detail::msr_sampler_context::samples(
        _In_ const sensor_type sensor) {
    assert(sensor != nullptr);
    std::lock_guard<decltype(this->lock)> l(this->lock);
    auto it = this->sensors.find(sensor->device);
    return (it != this->sensors.end())
        && (it->second.find(sensor) != it->second.end());
}
