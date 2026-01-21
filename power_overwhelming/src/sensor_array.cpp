// <copyright file="sensor_array.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/sensor_array.h"

#include <memory>
#include <stdexcept>

#include "visus/pwrowg/thread_name.h"

#include "sensor_array_configuration_impl.h"
#include "sensor_array_impl.h"
#include "sensor_registry.h"


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
    // Similarly, additional sensors could have become available in the
    // meantime.
    cnt = (std::min)(cnt, descs.size());

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
            this->_impl,
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
 * PWROWG_NAMESPACE::sensor_array::begin
 */
_Ret_maybenull_ PWROWG_NAMESPACE::sensor_description *
PWROWG_NAMESPACE::sensor_array::begin(void) noexcept {
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
 * PWROWG_NAMESPACE::sensor_array::end
 */
_Ret_maybenull_ PWROWG_NAMESPACE::sensor_description *
PWROWG_NAMESPACE::sensor_array::end(void) noexcept {
    volatile auto impl = this->_impl;  // sic!
    return (impl != nullptr)
        ? impl->descriptions.data() + impl->descriptions.size()
        : nullptr;
}


/*
 * PWROWG_NAMESPACE::sensor_array::marker
 */
bool PWROWG_NAMESPACE::sensor_array::marker(_In_ const timestamp timestamp,
        _In_ const int id) const {
    typedef detail::marker_sensor::list_type type;
    typedef detail::tuple_types_t<decltype(this->_impl->sensors)> types;
    typedef detail::type_list_index_of<type, types> index;

    volatile auto impl = this->_impl;  // sic!
    auto& list = std::get<index::value>(this->_impl->sensors);
    auto retval = ((impl != nullptr) && !list.empty());

    if (retval) {
        retval = list.begin()->emit(timestamp, id);
    }

    return retval;
}


/*
 * PWROWG_NAMESPACE::sensor_array::marker
 */
std::size_t PWROWG_NAMESPACE::sensor_array::marker(
        _Out_writes_opt_z_(cnt) wchar_t *dst,
        _In_ const std::size_t cnt,
        _In_ const unsigned int marker) const {
    typedef detail::marker_sensor::list_type type;
    typedef detail::tuple_types_t<decltype(this->_impl->sensors)> types;
    typedef detail::type_list_index_of<type, types> index;

    volatile auto impl = this->_impl;  // sic!
    auto& list = std::get<index::value>(this->_impl->sensors);

    return ((impl != nullptr) && !list.empty())
        ? list.begin()->marker(dst, cnt, marker)
        : 0;
}


/*
 * PWROWG_NAMESPACE::sensor_array::marker
 */
std::size_t PWROWG_NAMESPACE::sensor_array::marker(
        _Out_writes_opt_z_(cnt) char *dst,
        _In_ const std::size_t cnt,
        _In_ const unsigned int marker) const {
    auto retval = this->marker(static_cast<wchar_t *>(nullptr), 0, marker);

    if (retval == 0) {
        // If the marker does not exist, we can bail out.
        return retval;
    }

    // Get the marker and measure the required UTF-8 code units.
    std::vector<wchar_t> buffer(retval);
    this->marker(buffer.data(), buffer.size(), marker);
    retval = detail::convert_string(dst, cnt, buffer.data(), retval);

    return retval;
}


/*
 * PWROWG_NAMESPACE::sensor_array::markers
 */
std::size_t PWROWG_NAMESPACE::sensor_array::markers(void) const noexcept {
    typedef detail::marker_sensor::list_type type;
    typedef detail::tuple_types_t<decltype(this->_impl->sensors)> types;
    typedef detail::type_list_index_of<type, types> index;

    volatile auto impl = this->_impl;  // sic!
    auto& list = std::get<index::value>(this->_impl->sensors);

    return ((impl != nullptr) && !list.empty()) ? list.begin()->size() : 0;
}


/*
 * PWROWG_NAMESPACE::sensor_array::start
 */
void PWROWG_NAMESPACE::sensor_array::start(void) {
    volatile auto impl = this->check_not_disposed();
    impl->state.begin_start();
    start(impl);
    impl->state.end_start();
}


/*
 * PWROWG_NAMESPACE::sensor_array::start
 */
void PWROWG_NAMESPACE::sensor_array::start(
        _In_ const sensor_array_callback callback,
        _In_opt_ void *context) {
    if (callback == nullptr) {
        throw std::invalid_argument("A valid callback must be provided.");
    }

    volatile auto impl = this->check_not_disposed();
    impl->state.begin_start();
    impl->configuration->callback = callback;
    impl->configuration->context = context;
    start(impl);
    impl->state.end_start();
}


/*
 * PWROWG_NAMESPACE::sensor_array::sensor_array::stop
 */
void PWROWG_NAMESPACE::sensor_array::sensor_array::stop(void) {
    volatile auto impl = this->check_not_disposed();

    impl->state.begin_stop();

    // Stop the asynchronous sensors.
    detail::sensor_registry::sample(impl->samplers.begin(), impl->sensors,
        false);

    // Wait for the sampler threads, which should exit now as the state signals
    // that we are stopping.
    for (auto& t : impl->sampler_threads) {
        assert(t.joinable());
        t.join();
    }
    impl->sampler_threads.clear();

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
        set_thread_name(name.c_str());
    }

    while (impl->state) {
        const auto now = std::chrono::steady_clock::now();
        const auto then = now + config->interval;

        for (std::size_t i = offset; i < end; ++i) {
            impl->samplers[i](config->callback,
                impl->descriptions.data(),
                config->context);
        }

        std::this_thread::sleep_until(then);
    }
}


/*
 * PWROWG_NAMESPACE::sensor_array::start
 */
void PWROWG_NAMESPACE::sensor_array::start(
        _In_ detail::sensor_array_impl *impl) {
    assert(impl != nullptr);
    assert(impl->state == detail::sensor_state::value_type::starting);

    // Start the asynchronous sensors and get samples for synchronous ones.
    impl->samplers.clear();
    detail::sensor_registry::sample(std::back_inserter(impl->samplers),
        impl->sensors,
        true);

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
            sampler(detail::sensor_array_configuration_impl::sample_nothing,
                nullptr, nullptr);
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
