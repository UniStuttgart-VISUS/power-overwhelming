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
 * PWROWG_NAMESPACE::sensor_array::sensor_array
 */
PWROWG_NAMESPACE::sensor_array::sensor_array(
        _Inout_ sensor_array&& rhs) noexcept
        : _impl(rhs._impl) {
    rhs._impl = nullptr;
    this->sync_context();
}


/*
 * PWROWG_NAMESPACE::sensor_array::~sensor_array
 */
PWROWG_NAMESPACE::sensor_array::~sensor_array(void) noexcept {
    delete this->_impl;
}


/*
 * PWROWG_NAMESPACE::sensor_array::begin
 */
_Ret_maybenull_ const PWROWG_NAMESPACE::sensor_description *
PWROWG_NAMESPACE::sensor_array::begin(void) const noexcept {
    volatile auto impl = this->_impl;  // sic!
    return (impl != nullptr) ? impl->descriptions.data() : nullptr;
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
 * PWROWG_NAMESPACE::sensor_array::end
 */
_Ret_maybenull_ const PWROWG_NAMESPACE::sensor_description *
PWROWG_NAMESPACE::sensor_array::end(void) const noexcept {
    volatile auto impl = this->_impl;  // sic!
    return (impl != nullptr)
        ? impl->descriptions.data() + impl->descriptions.size()
        : nullptr;
}


/*
 * PWROWG_NAMESPACE::sensor_array::start
 */
void PWROWG_NAMESPACE::sensor_array::start(void) {
    using std::chrono::duration_cast;
    typedef PWROWG_NAMESPACE::sample sample_type;

    // A callback that does nothing which serves for detecting samplers
    // that are inherently slow.
    static const auto sample_nothing = [](const std::size_t,
        const sample_type *, const std::size_t, void *) { };

    volatile auto impl = this->check_not_disposed();

    impl->state.begin_start();

    // Make sure that auto-context is lazily initialised.
    this->sync_context();

    // Start the asynchronous sensors and get samples for synchronous ones.
    impl->samplers.clear();
    detail::sensor_registry::sample(std::back_inserter(impl->samplers),
        impl->sensors,
        impl->configuration->callback,
        impl->configuration->interval,
        impl->configuration->context);

    // Start sampler threads for the synchronous sensors.
    {
        std::size_t first = 0;
        std::chrono::nanoseconds sum(0);

        for (std::size_t i = 0; i < impl->samplers.size(); ++i) {
            const auto sampler = impl->samplers[i];

            // Note: it is sufficient to sample only once at this point, because
            // if the time to call the sampler is negligible, we can safely group
            // it with others. The purpose here is finding APIs that are blocking
            // and would cause others to generate less samples than requested.
            const auto b = std::chrono::steady_clock::now();
            sampler(sample_nothing, nullptr);
            const auto dt = std::chrono::steady_clock::now() - b;

            if ((sum += dt) > impl->configuration->interval) {
                impl->sampler_threads.emplace_back(sensor_array::sample,
                    impl,
                    first,
                    i + 1 - first);
                first = i + 1;
                sum = decltype(sum)::zero();
            }
        }

        if (first < impl->samplers.size()) {
            impl->sampler_threads.emplace_back(sensor_array::sample,
                impl,
                first,
                (std::numeric_limits<std::size_t>::max)());
        }
    }

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
        this->sync_context();
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
 * PWROWG_NAMESPACE::sensor_array::sample
 */
void PWROWG_NAMESPACE::sensor_array::sample(
        _In_ detail::sensor_array_impl *impl,
        _In_ const std::size_t offset,
        _In_ const std::size_t limit) {
    assert(impl != nullptr);
    const auto config = impl->configuration.get();
    const auto end = (std::min)(impl->samplers.size(), limit);

    {
        std::string name = "PwrOwg Sampler Thread ";
        name += std::to_string(offset);
        name += " - ";
        name += std::to_string(offset + end);
        detail::set_thread_name(name.c_str());
    }

    while (impl->state) {
        const auto now = std::chrono::steady_clock::now();
        const auto then = now + config->interval;

        for (std::size_t i = offset; i < end; ++i) {
            impl->samplers[i](config->callback, config->context);
        }

        std::this_thread::sleep_until(then);
    }
}


/*
 * PWROWG_NAMESPACE::sensor_array::check_not_disposed
 */
_Ret_valid_ PWROWG_DETAIL_NAMESPACE::sensor_array_impl *
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
_Ret_valid_ const PWROWG_DETAIL_NAMESPACE::sensor_array_impl *
PWROWG_NAMESPACE::sensor_array::check_not_disposed(void) const {
    volatile auto retval = this->_impl;

    if (retval == nullptr) {
        throw std::runtime_error("A sensor array which has been disposed by "
            "a move operation cannot be used anymore.");
    }

    return retval;
}


/*
 * PWROWG_NAMESPACE::sensor_array::sync_context
 */
void PWROWG_NAMESPACE::sensor_array::sync_context(void) {
    using context_type = detail::sensor_array_context_type;
    volatile auto impl = this->_impl;

    if ((impl != nullptr) && (impl->configuration != nullptr)) {
        switch (impl->configuration->context_type) {
            case context_type::sensor_array:
                impl->configuration->context = this;
                break;

            case context_type::sensor_descs:
                impl->configuration->context = impl->descriptions.data();
                break;
        }
    }
}
