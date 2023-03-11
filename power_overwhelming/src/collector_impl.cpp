// <copyright file="collector_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "collector_impl.h"

#include <cassert>
#include <system_error>

#include "power_overwhelming/adl_sensor.h"
#include "power_overwhelming/emi_sensor.h"
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
}


/*
 * visus::power_overwhelming::detail::collector_impl::collector_impl
 */
visus::power_overwhelming::detail::collector_impl::collector_impl(void)
        : evt_write(create_event(false, false)),
        have_marker(false), running(false), sampling_interval(0),
        require_marker(false),
        timestamp_resolution(timestamp_resolution::milliseconds) { }


/*
 * visus::power_overwhelming::detail::collector_impl::~collector_impl
 */
visus::power_overwhelming::detail::collector_impl::~collector_impl(void) {
    destroy_event(this->evt_write);
}


/*
 * visus::power_overwhelming::detail::collector_impl::apply
 */
void visus::power_overwhelming::detail::collector_impl::apply(
        const collector_settings& settings) {
    assert(settings.output_path() != nullptr);
    auto output_path = settings.output_path();

#if defined(_WIN32)
    this->stream = std::wofstream(output_path, std::ofstream::trunc);
#else /* defined(_WIN32) */
    auto p = convert_string<char>(output_path);
    this->stream = std::wofstream(p, std::ofstream::trunc);
#endif /* defined(_WIN32) */

    this->sampling_interval = std::chrono::microseconds(
        settings.sampling_interval());
}


/*
 * visus::power_overwhelming::detail::collector_impl::can_buffer
 */
bool visus::power_overwhelming::detail::collector_impl::can_buffer(void) const {
    return (!this->require_marker
        || this->have_marker.load(std::memory_order::memory_order_acquire));
}


/*
 * visus::power_overwhelming::detail::collector_impl::marker
 */
void visus::power_overwhelming::detail::collector_impl::marker(
        const wchar_t *marker) {
    const auto have_marker = (marker != nullptr);

    // Enable/disable collection of samples by other threads.
    this->have_marker.store(have_marker,
        std::memory_order::memory_order_release);

    if (have_marker) {
        // If we now have a marker, store it for the I/O thread to process.
        std::lock_guard<decltype(this->lock)> l(this->lock);
        this->markers.emplace_back(marker, this->buffer.size());

        // Wake the I/O thread, because if we start a new phase, it is typically
        // a good idea to make sure that what we already have is persisted.
        set_event(this->evt_write);
    }
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
                // Start ADL sampler. ADL is asynchronous, but we start a
                // separate thread to collect the data at regular intervals.
                // Registering a callback with the sensor implementation will
                // start the ADL sampling and our collector thread.
                auto ss = dynamic_cast<adl_sensor *>(s.get());
                if (ss != nullptr) {
                    //ss->start(this->sampling_interval.count());
                    const auto si = duration_cast<microseconds>(
                        this->sampling_interval).count();
                    ss->sample(on_measurement, si, this);
                    continue;
                }
            }

            {
                // EMI is in principle synchronous, but we built a specialised
                // sampling thread that minimises the number of reads of the EMI
                // registers.
                auto ss = dynamic_cast<emi_sensor *>(s.get());
                if (ss != nullptr) {
                    const auto si = duration_cast<microseconds>(
                        this->sampling_interval).count();
                    ss->sample(on_measurement, si, this);
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
                // Start NVML sampler. NVML is in principle synchronous, but we
                // built our own sampling thread around it.
                auto ss = dynamic_cast<nvml_sensor *>(s.get());
                if (ss != nullptr) {
                    const auto si = duration_cast<microseconds>(
                        this->sampling_interval).count();
                    ss->sample(on_measurement, si, this);
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

        // Finally, start the I/O thread.
        this->writer_thread = std::thread(&collector_impl::write, this);
    } catch (...) {
        this->running = false;
        throw;
    }
}


/*
 * visus::power_overwhelming::detail::collector_impl::stop
 */
void visus::power_overwhelming::detail::collector_impl::stop(void) {
    // Tell the threads to exit if they are running.
    this->running.store(false, std::memory_order::memory_order_release);

    for (auto& s : this->sensors) {
        try {
            // Stop ADL sampler.
            auto ss = dynamic_cast<adl_sensor *>(s.get());
            if (ss != nullptr) {
                ss->sample(nullptr);
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

        try {
            // Stop delivery of NVML sampler thread.
            auto ss = dynamic_cast<nvml_sensor *>(s.get());
            if (ss != nullptr) {
                ss->sample(nullptr);
                continue;
            }
        } catch (...) { /* Ignore this, we need to stop all.*/ }

        try {
            // Unregister callback from Tinkerforge, which will stop it.
            auto ss = dynamic_cast<tinkerforge_sensor *>(s.get());
            if (ss != nullptr) {
                ss->sample(nullptr, tinkerforge_sensor_source::all);
                continue;
            }
        } catch (...) { /* Ignore this, we need to stop all.*/ }
    }

    // Then, wake the I/O thread for a last time to make sure it exits.
    set_event(this->evt_write);
    if (this->writer_thread.joinable()) {
        this->writer_thread.join();
    }
}


/*
 * visus::power_overwhelming::detail::collector_impl::write
 */
void visus::power_overwhelming::detail::collector_impl::write(void) {
    using namespace std::chrono;
    buffer_type buffer;
    const auto delimiter = getcsvdelimiter(this->stream);
    marker_list_type markers;
    const auto timeout = static_cast<unsigned int>(duration_cast<milliseconds>(
        this->sampling_interval).count()) * 8;

    while (this->running.load()) {
        wait_event(this->evt_write, timeout);

        {
            std::lock_guard<decltype(this->lock)> l(this->lock);
            buffer = std::move(this->buffer);
            markers = std::move(this->markers);

            if (!markers.empty() && this->have_marker.load()) {
                // Remember the last marker if it is still active. This is
                // relevant in cases when we were invoked because of a timeout.
                this->markers.push_back(markers.back());
            }
        }

        if ((this->stream.tellp() == 0) && !buffer.empty()) {
            // If this is the first line, print the CSV header.
            this->stream << csvheader
                << buffer.front() << delimiter
                << L"marker" << std::endl
                << csvdata;
        }

        for (std::size_t i = 0, m = 0; i < buffer.size(); ++i) {
            if ((m + 1 < markers.size()) && (i >= markers[m + 1].second)) {
                ++m;
            }

            if (m < markers.size()) {
                this->stream << buffer[i] << delimiter
                    << markers[m].first << std::endl;
            } else {
                this->stream << buffer[i] << delimiter << std::endl;
            }
        }

        this->stream.flush();
    }

    this->stream.close();
}
