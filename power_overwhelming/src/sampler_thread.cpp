// <copyright file="sampler_thread.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "sampler_thread.h"


/*
 * visus::power_overwhelming::detail::sampler_thread::sampler_thread
 */
visus::power_overwhelming::detail::sampler_thread::sampler_thread(
        _In_ sampler_source *source) {
    if (source == nullptr) {
        throw std::invalid_argument("A sampler_thread can only be constructed "
            "if its initial source is valid");
    }

    this->_interval = source->interval();
    this->_sources.push_back(source);
    this->_thread = std::thread(&sampler_thread::sample, this);
}


/*
 * visus::power_overwhelming::detail::sampler_thread::~sampler_thread
 */
visus::power_overwhelming::detail::sampler_thread::~sampler_thread(
        void) noexcept {
    {
        std::lock_guard<decltype(this->_lock)> l(this->_lock);
        this->_sources.clear();
    }
    this->_thread.join();
}


/*
 * visus::power_overwhelming::detail::sampler_thread::add
 */
void visus::power_overwhelming::detail::sampler_thread::add(
        _In_ sampler_source *source) {
    if (source != nullptr) {
        if (source->interval() != this->_interval) {
            throw std::invalid_argument("The specified source does not match "
                "the sampling interval of the sampler thread.");
        }

        std::lock_guard<decltype(this->_lock)> l(this->_lock);
        this->_sources.push_back(source);
    }
}


/*
 * visus::power_overwhelming::detail::sampler_thread::samples
 */
bool visus::power_overwhelming::detail::sampler_thread::samples(
        _In_ const sampler_source *source) const {
    std::lock_guard<decltype(this->_lock)> l(this->_lock);
    return (std::find(this->_sources.begin(), this->_sources.end(),
        source) != this->_sources.end());
}


/*
 * visus::power_overwhelming::detail::sampler_thread::sample
 */
void visus::power_overwhelming::detail::sampler_thread::sample(void) {
    auto have_sources = true;

    {
        std::stringstream stream;
        stream << "PwrOwg Sampler Thread @" << this->_interval.count() << "us";
        auto name = stream.str();
        set_thread_name(name.c_str());
    }

    while (have_sources) {
        auto now = std::chrono::high_resolution_clock::now();

        {
            std::lock_guard<decltype(this->_lock)> l(this->_lock);
            for (auto it = this->_sources.begin();
                    it != this->_sources.end();) {
                if ((**it).deliver()) {
                    ++it;
                } else {
                    // If the source did not deliver a sample, remove it from
                    // the thread.
                    it = this->_sources.erase(it);
                }
            }

            have_sources = !this->_sources.empty();
        }

        if (have_sources) {
            std::this_thread::sleep_until(now + this->_interval);
        }
    }
}
