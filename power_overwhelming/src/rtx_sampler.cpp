// <copyright file="rtx_sampler.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "rtx_sampler.h"

#include <cassert>
#include <chrono>
#include <sstream>

#if defined(_WIN32)
#include <Windows.h>
#include <tchar.h>
#endif /* defined(_WIN32) */

#include "power_overwhelming/measurement_data_series.h"
#include "power_overwhelming/timestamp.h"

#include "thread_name.h"


/*
 * visus::power_overwhelming::detail::rtx_sampler::sample
 */
void visus::power_overwhelming::detail::rtx_sampler::sample(
        _In_ std::string path, _In_ sensor_group *group) {
    using namespace std::chrono;
    assert(group != nullptr);
    std::vector<measurement_data> data;
    auto have_sensors = true;

    {
        std::stringstream stream;
        stream << "PwrOwg Sampler for " << path;
        auto name = stream.str();
        set_thread_name(name.c_str());

#if (defined(_WIN32) && (defined(DEBUG) || defined(_DEBUG)))
        name += " is starting.\r\n";
        ::OutputDebugStringA(name.c_str());
#endif /* (defined(_WIN32) && (defined(DEBUG) || defined(_DEBUG))) */
    }

    while (have_sensors) {
        async_sampling::microseconds_type min_sleep = 0;
        auto now = high_resolution_clock::now();

        {
            std::lock_guard<decltype(group->lock)> l(group->lock);
            if (!(have_sensors = !group->sensors.empty())) {
                // We need to re-check this while holding the lock as we next
                // want to access the front sensor in order to gain access to
                // the instrument.
                continue;
            }

            // Run the acquisition. It depends on the user settings whether this
            // will auto-trigger or wait for a real trigger.
            auto& dev = group->sensors.front()->instrument;
            dev.acquisition(oscilloscope_acquisition_state::single, true);

            // Get all the data we have.
            auto waveforms = dev.data(oscilloscope_waveform_points::maximum);

            // Construct the measurement_data from the sample data. Asynchronous
            // sampling can deliver batches of measurement_data, so we will
            // deliver all of the waveform points.
            for (auto& s : group->sensors) {
                if (s->async_sampling.minimum_sleep() > min_sleep) {
                    min_sleep = s->async_sampling.minimum_sleep();
                }

                const oscilloscope_sample::channel_waveform *current = nullptr;
                const oscilloscope_sample::channel_waveform *voltage = nullptr;

                for (auto& w : waveforms) {
                    if (s->channel_current == w.channel()) {
                        current = &w;
                    } else if (s->channel_voltage == w.channel()) {
                        voltage = &w;
                    }
                }

                if ((current != nullptr) && (voltage != nullptr)) {
                    const auto& current_waveform = current->waveform();
                    assert(current_waveform.size()
                        == voltage->waveform().size());

                    data.clear();
                    data.reserve(current_waveform.size());

                    for (std::size_t i = 0; i < current_waveform.size(); ++i) {
                        auto timestamp = current_waveform.sample_timestamp(i);
                        data.emplace_back(timestamp,
                            voltage->waveform().sample(i),
                            current->waveform().sample(i));
                    }

                    s->async_sampling.deliver(s->sensor_name.c_str(),
                        data.data(), data.size());
                }
            }

            // Check again as the stuff before might have taken quite some time
            // to complete (mostly the download of the data).
            have_sensors = !group->sensors.empty();
        }

        if (have_sensors) {
            const auto until = now + group->interval;
            now = high_resolution_clock::now();

            if ((min_sleep == 0) || (now < until)) {
                std::this_thread::sleep_until(until);
            } else {
                // Allow other threads access to the sensor list.
                std::this_thread::sleep_for(microseconds(min_sleep));
            }
        }
    }

#if (defined(_WIN32) && (defined(DEBUG) || defined(_DEBUG)))
    ::OutputDebugString(_T("PWROWG RTX sampler thread is exiting\r\n"));
#endif /* (defined(_WIN32) && (defined(DEBUG) || defined(_DEBUG))) */
}
