﻿// <copyright file="sampler.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "sampler.h"

#include <algorithm>
#include <stdexcept>


/*
 * visus::power_overwhelming::detail::sampler::default
 */
visus::power_overwhelming::detail::sampler
visus::power_overwhelming::detail::sampler::default;


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
    if ((source != nullptr) && (source->interval() > interval_type::zero())) {
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
    auto wait_thread = false;

    throw "TODO";

    //if (source != nullptr) {
    //    std::lock_guard<decltype(this->_lock)> l(this->lock);
    //    auto it = std::remove(this->_sources.begin(),
    //        this->_sources.end(),
    //        source);
    //    this->_sources.erase(it, this->_sources.end());
    //    wait_thread = this->_sources.empty();
    //}

    //if (wait_thread) {
    //    this->_thread.join();
    //}

    return *this;
}


/*
 * visus::power_overwhelming::detail::sampler::operator bool
 */
visus::power_overwhelming::detail::sampler::operator bool(void) const {
    std::lock_guard<decltype(this->_lock)> l(this->_lock);
    return !this->_threads.empty();
}
