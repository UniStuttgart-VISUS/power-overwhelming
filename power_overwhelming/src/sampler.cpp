// <copyright file="sampler.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "sampler.h"

#include <algorithm>
#include <stdexcept>


/*
 * visus::power_overwhelming::detail::sampler::default_sampler
 */
visus::power_overwhelming::detail::sampler
visus::power_overwhelming::detail::sampler::default_sampler;


/*
 * visus::power_overwhelming::detail::sampler::~sampler
 */
visus::power_overwhelming::detail::sampler::~sampler(void) noexcept {
    std::lock_guard<decltype(this->_lock)> l(this->_lock);
    this->_threads.clear();
}


/*
 * visus::power_overwhelming::detail::sampler::operator +=
 */
visus::power_overwhelming::detail::sampler&
visus::power_overwhelming::detail::sampler::operator +=(
        _In_ source_type source) {
    if ((source != nullptr) && (source->interval() > 0)) {
        std::lock_guard<decltype(this->_lock)> l(this->_lock);

        // Make sure that 'source' is not being sampled at the moment.
        {
            auto duplicate = std::any_of(this->_threads.begin(),
                    this->_threads.end(),
                    [source](const decltype(this->_threads)::value_type& t) {
                return t.second.samples(source);
            });

            if (duplicate) {
                throw std::invalid_argument("Asynchronous sampling cannot be "
                    "started on a source that is already being sampled.");
            }
        }

        auto thread = this->_threads.find(source->interval());
        if (thread == this->_threads.end()) {
            // Create a new thread using the input as its first source.
            this->_threads.emplace(source->interval(), source);
        } else {
            // Add the source.
            thread->second.add(source);
        }

    }

    return *this;
}


/*
 * visus::power_overwhelming::detail::sampler::operator -=
 */
visus::power_overwhelming::detail::sampler&
visus::power_overwhelming::detail::sampler::operator -=(
        _In_ source_type source) {
    if (source != nullptr) {
        std::lock_guard<decltype(this->_lock)> l(this->_lock);
        auto wait_thread = false;

        for (auto it = this->_threads.begin(); it != this->_threads.end(); ) {
            if (it->second.remove(source)) {
                // This thread is done, so remove it.
                it = this->_threads.erase(it);
            } else {
                ++it;
            }
        }
    }

    return *this;
}


/*
 * visus::power_overwhelming::detail::sampler::operator bool
 */
visus::power_overwhelming::detail::sampler::operator bool(void) const {
    std::lock_guard<decltype(this->_lock)> l(this->_lock);
    return !this->_threads.empty();
}
