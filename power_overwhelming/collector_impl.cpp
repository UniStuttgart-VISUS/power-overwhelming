// <copyright file="collector_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "collector_impl.h"

#include "power_overwhelming/adl_sensor.h"
#include "power_overwhelming/collector.h"
#include "power_overwhelming/nvml_sensor.h"
#include "power_overwhelming/hmc8015_sensor.h"
#include "power_overwhelming/tinkerforge_sensor.h"


/*
 * visus::power_overwhelming::detail::collector_impl::on_measurement
 */
void visus::power_overwhelming::detail::collector_impl::on_measurement(
        const measurement& m, void *context) {
    auto that = static_cast<collector_impl *>(context);

    if (that->can_buffer()) {
        std::lock_guard<decltype(that->lock)> l(that->lock);
        that->buffer.push_back(m);

    }

    if (!that->require_marker) {
        that->flush_buffer();
    }
}


/*
 * visus::power_overwhelming::detail::collector_impl::collector_impl
 */
visus::power_overwhelming::detail::collector_impl::collector_impl(void)
        : have_marker(false), running(false), sampling_interval(0),
        require_marker(false),
        timestamp_resolution(timestamp_resolution::milliseconds) { }


/*
 * visus::power_overwhelming::detail::collector_impl::~collector_impl
 */
visus::power_overwhelming::detail::collector_impl::~collector_impl(void) {
}


/*
 * visus::power_overwhelming::detail::collector_impl::can_buffer
 */
bool visus::power_overwhelming::detail::collector_impl::can_buffer(void) const {
    return (!this->require_marker
        || this->have_marker.load(std::memory_order::memory_order_acquire));
}

/*
 * visus::power_overwhelming::detail::collector_impl::collect
 */
void visus::power_overwhelming::detail::collector_impl::collect(void) {
    while (this->running.load()) {
        auto now = std::chrono::high_resolution_clock::now();

        if (this->can_buffer()) {
            std::lock_guard<decltype(this->lock)> l(this->lock);

            for (auto&s : this->sensors) {
                {
                    // ADL sensor is weird: It is asynchronous, but we need to
                    // get the samples from their buffer.
                    auto ss = dynamic_cast<adl_sensor *>(s.get());
                    if (ss != nullptr) {
                        this->buffer.push_back(ss->sample(
                            this->timestamp_resolution));
                        continue;
                    }
                }

                {
                    // NVIDIA ist synchronous, so retrieve it manually.
                    auto ss = dynamic_cast<nvml_sensor *>(s.get());
                    if (ss != nullptr) {
                        this->buffer.push_back(ss->sample(
                            this->timestamp_resolution));
                        continue;
                    }
                }
            }

            if (!this->require_marker) {
                this->flush_buffer();
            }
        }
        // Note: we must not hold 'lock' while sleeping!

        std::this_thread::sleep_until(now + this->sampling_interval);
    }
}


/*
 * visus::power_overwhelming::detail::collector_impl::flush_buffer
 */
void visus::power_overwhelming::detail::collector_impl::flush_buffer(void) {
    const auto delimiter = getcsvdelimiter(this->stream);

    if ((this->stream.tellp() == 0) && !this->buffer.empty()) {
        // If this is the first line, print the CSV header.
        this->stream << csvheader
            << this->buffer.front() << delimiter
            << L"marker" << std::endl
            << csvdata;
    }

    for (auto& m : this->buffer) {
        this->stream << m << delimiter << this->marker << std::endl;
    }

    this->buffer.clear();
    this->stream.flush();
}


/*
 * visus::power_overwhelming::detail::collector_impl::start
 */
void visus::power_overwhelming::detail::collector_impl::start(void) {
    using namespace std::chrono;

    {
        auto expected = false;
        if (!this->running.compare_exchange_strong(expected, true)) {
            throw std::runtime_error("The power sample collector is already "
                "running and cannot be restarted.");
        }
    }

    try {
        for (auto& s : this->sensors) {
            {
                // ADL is reasonably simple: just start the sensor.
                auto ss = dynamic_cast<adl_sensor *>(s.get());
                if (ss != nullptr) {
                    ss->start(this->sampling_interval.count());
                    continue;
                }
            }

            {
                // HMC8015 logs externally, so just start it.
                auto ss = dynamic_cast<hmc8015_sensor *>(s.get());
                if (ss != nullptr) {
                    ss->display("The way you're meant to be trrolled.");
                    ss->log(true);
                    continue;
                }
            }

            {
                // Nothing to do for NVML, we need to poll this sensor.
                auto ss = dynamic_cast<nvml_sensor *>(s.get());
                if (ss != nullptr) {
                    continue;
                }
            }

            {
                // Tinkerforge is truly asynchronous, so we need to register
                // a callback to receive the samples.
                auto ss = dynamic_cast<tinkerforge_sensor *>(s.get());
                if (ss != nullptr) {
                    const auto si = duration_cast<microseconds>(
                        this->sampling_interval).count();
                    ss->sample(on_measurement, tinkerforge_sensor_source::power,    // TODO: Allow other config here.
                        si, this);
                    continue;
                }
            }
        }

        // Finally, start the collector thread.
        this->thread = std::thread(&collector_impl::collect, this);
    } catch (...) {
        this->running = false;
        throw;
    }
}


/*
 * visus::power_overwhelming::detail::collector_impl::stop
 */
void visus::power_overwhelming::detail::collector_impl::stop(void) {
    // Tell the thread to exit if it is running.
    this->running.store(false, std::memory_order::memory_order_release);

    for (auto& s : this->sensors) {
        try {
            // Stop delivery of ADL samples.
            auto ss = dynamic_cast<adl_sensor *>(s.get());
            if (ss != nullptr) {
                ss->stop();
                continue;
            }
        } catch (...) { /* Ignore this, we need to stop all.*/ }

        try {
            // Stop on-device logging of HMC8015.
            auto ss = dynamic_cast<hmc8015_sensor *>(s.get());
            if (ss != nullptr) {
                ss->log(false);
                continue;
            }
        } catch (...) { /* Ignore this, we need to stop all.*/ }

        // Nothing to do for NVIDIA.

        try {
            // Unregister callback from Tinkerforge, which will stop it.
            auto ss = dynamic_cast<tinkerforge_sensor *>(s.get());
            if (ss != nullptr) {
                ss->sample(nullptr, tinkerforge_sensor_source::all);
                continue;
            }
        } catch (...) { /* Ignore this, we need to stop all.*/ }
    }

    // Wait for the thread to exit such that we do not receive anything else.
    if (this->thread.joinable()) {
        this->thread.join();
    }

    // Log all remaining data in the buffer.
    this->flush_buffer();
    this->stream.close();
}
