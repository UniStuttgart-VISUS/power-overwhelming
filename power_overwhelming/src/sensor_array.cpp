// <copyright file="sensor_array.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/sensor_array.h"

#include <memory>
#include <stdexcept>

#include "sensor_array_configuration_impl.h"
#include "sensor_array_impl.h"
#include "sensor_registry.h"
#include "thread_name.h"


/*
 * PWROWG_NAMESPACE::sensor_array::all_descriptions
 */
std::size_t PWROWG_NAMESPACE::sensor_array::all_descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const sensor_array_configuration& config) {
    if (!config) {
        throw std::invalid_argument("A valid array configuration object must "
            "be provided.");
    }

    return detail::sensor_registry::descriptions(dst, cnt, *config._impl);
}


/*
 * PWROWG_NAMESPACE::sensor_array::for_all
 */
PWROWG_NAMESPACE::sensor_array PWROWG_NAMESPACE::sensor_array::for_all(
        _Inout_ sensor_array_configuration&& config) {
    std::vector<sensor_description> descs;
    descs.resize(all_descriptions(nullptr, 0, config));

    // Count sensors, but account for dynamic sensors being detached
    // betweeen the calls.
    auto cnt = all_descriptions(descs.data(), descs.size(), config);

    return sensor_array(std::move(config), descs.data(), cnt);
}


/*
 * PWROWG_NAMESPACE::sensor_array::sensor_array
 */
PWROWG_NAMESPACE::sensor_array::sensor_array(
        _Inout_ sensor_array_configuration&& config,
        _In_reads_(cnt) const sensor_description *descs,
        _In_ const std::size_t cnt)
        : _impl(new PWROWG_DETAIL_NAMESPACE::sensor_array_impl()) {
    this->_impl->configuration.reset(config._impl);
    config._impl = nullptr;

    if (descs != nullptr) {
        std::copy(descs,
            descs + cnt,
            std::back_inserter(this->_impl->descriptions));
        auto end = detail::sensor_registry::create(this->_impl->sensors,
            this->_impl->descriptions.begin(),
            this->_impl->descriptions.end(),
            *this->_impl->configuration);
        this->_impl->descriptions.erase(end, this->_impl->descriptions.end());
    }
}


/*
 * PWROWG_NAMESPACE::sensor_array::~sensor_array
 */
PWROWG_NAMESPACE::sensor_array::~sensor_array(void) noexcept {
    delete this->_impl;
}


/*
 * PWROWG_NAMESPACE::sensor_array::descriptions
 */
std::size_t PWROWG_NAMESPACE::sensor_array::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt) {
    volatile auto impl = this->_impl;  // sic!

    if (impl != nullptr) {
        if (dst != nullptr) {
            for (std::size_t i = 0; (i < this->size()) && (i < cnt); ++i) {
                dst[i] = impl->descriptions[i];
            }
        }

        return this->size();

    } else {
        return 0;
    }
}


/*
 * PWROWG_NAMESPACE::sensor_array::start
 */
void PWROWG_NAMESPACE::sensor_array::start(void) {
    volatile auto impl = this->check_not_disposed();

    impl->state.begin_start();

    // Start the asynchronous sensors and get samples for synchronous ones.
    impl->samplers.clear();
    detail::sensor_registry::sample(std::back_inserter(impl->samplers),
        impl->sensors,
        impl->configuration->callback,
        impl->configuration->interval,
        impl->configuration->context);

    // Start sampler threads for the synchronous sensors.
    impl->sampler_threads.emplace_back(sensor_array::sample, impl);

    impl->state.end_start();
}


/*
 * PWROWG_NAMESPACE::sensor_array::sensor_array::stop
 */
void PWROWG_NAMESPACE::sensor_array::sensor_array::stop(void) {
    volatile auto impl = this->check_not_disposed();

    impl->state.begin_stop();

    // Stop the asynchronous sensors.
    detail::sensor_registry::sample(std::back_inserter(impl->samplers),
        impl->sensors,
        nullptr,
        impl->configuration->interval,
        impl->configuration->context);

    // Wait for the sampler threads, which should exit now as the state signals
    // that we are stopping.
    for (auto& t : impl->sampler_threads) {
        t.join();
    }

    impl->state.end_stop();
}


/*
 * PWROWG_NAMESPACE::sensor_array::size
 */
std::size_t PWROWG_NAMESPACE::sensor_array::size(void) const noexcept {
    volatile auto impl = this->_impl;  // sic!
    return (impl != nullptr) ? impl->descriptions.size() : 0;
}


/*
 * PWROWG_NAMESPACE::sensor_array::operator =
 */
PWROWG_NAMESPACE::sensor_array& PWROWG_NAMESPACE::sensor_array::operator =(
        _Inout_ sensor_array&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::sensor_array::operator []
 */
const PWROWG_NAMESPACE::sensor_description&
PWROWG_NAMESPACE::sensor_array::operator [](_In_ int idx) const {
    volatile auto impl = this->check_not_disposed();

    if ((idx < 0) && (idx >= impl->descriptions.size())) {
        throw std::range_error("The specified index is out of range.");
    }

    return impl->descriptions[idx];
}


/*
 * PWROWG_NAMESPACE::sensor_array::operator []
 */
PWROWG_NAMESPACE::sensor_description&
PWROWG_NAMESPACE::sensor_array::operator [](_In_ int idx) {
    volatile auto impl = this->check_not_disposed();

    if ((idx < 0) && (idx >= impl->descriptions.size())) {
        throw std::range_error("The specified index is out of range.");
    }

    return impl->descriptions[idx];
}


/*
 * PWROWG_NAMESPACE::sensor_array::check_not_disposed
 */
PWROWG_DETAIL_NAMESPACE::sensor_array_impl *
PWROWG_NAMESPACE::sensor_array::check_not_disposed(void) {
    volatile auto retval = this->_impl;

    if (retval == nullptr) {
        throw std::runtime_error("A sensor array which has been disposed by "
            "a move operation cannot be used anymore.");
    }

    return retval;
}



/*
 * PWROWG_NAMESPACE::sensor_array::check_not_disposed
 */
const PWROWG_DETAIL_NAMESPACE::sensor_array_impl *
PWROWG_NAMESPACE::sensor_array::check_not_disposed(void) const {
    volatile auto retval = this->_impl;

    if (retval == nullptr) {
        throw std::runtime_error("A sensor array which has been disposed by "
            "a move operation cannot be used anymore.");
    }

    return retval;
}


/*
 * PWROWG_NAMESPACE::sensor_array::sample
 */
void PWROWG_NAMESPACE::sensor_array::sample(
        _In_ detail::sensor_array_impl *impl) {
    detail::set_thread_name("PwrOwg Sampler Thread");
    assert(impl != nullptr);

    //auto state = impl->state.
    while (impl->state) {
        std::this_thread::sleep_for(std::chrono::milliseconds(42));
    }

    ////    auto have_sources = true;
    ////
    ////    {
    ////        std::stringstream stream;
    ////        stream << "PwrOwg Sampler Thread @" << this->_interval.count() << "us";
    ////        auto name = stream.str();
    ////        set_thread_name(name.c_str());
    ////    }
    ////
    ////    while (have_sources) {
    ////        auto now = std::chrono::high_resolution_clock::now();
    ////
    ////        {
    ////            std::lock_guard<decltype(this->_lock)> l(this->_lock);
    ////            for (auto it = this->_sources.begin();
    ////                    it != this->_sources.end();) {
    ////                if ((**it).deliver()) {
    ////                    ++it;
    ////                } else {
    ////                    // If the source did not deliver a sample, remove it from
    ////                    // the thread.
    ////                    it = this->_sources.erase(it);
    ////                }
    ////            }
    ////
    ////            have_sources = !this->_sources.empty();
    ////        }
    ////
    ////        if (have_sources) {
    ////            std::this_thread::sleep_until(now + this->_interval);
    ////        }
    ////    }
}
