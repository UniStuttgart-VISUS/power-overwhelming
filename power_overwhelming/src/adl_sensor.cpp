// <copyright file="adl_sensor.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2021 - 2024 Visualisierungsinstitut der Universit�t Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph M�ller</author>

#include "power_overwhelming/adl_sensor.h"

#include <algorithm>
#include <cstring>
#include <vector>

#include "power_overwhelming/adl_sensor_source.h"
#include "power_overwhelming/convert_string.h"

#include "adl_exception.h"
#include "adl_scope.h"
#include "adl_sensor_impl.h"
#include "zero_memory.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Add all supported sensors of <paramref name="adapter" /> to the
    /// specified output iterator.
    /// </summary>
    /// <typeparam name="TIterator"></typeparam>
    /// <param name="oit"></param>
    /// <param name="scope"></param>
    /// <param name="adapter"></param>
    /// <param name="source"></param>
    /// <returns></returns>
    template<class TIterator>
    std::size_t for_adapter(TIterator oit, adl_scope& scope,
            const AdapterInfo& adapter, const adl_sensor_source source) {
#define _PWROWG_ENABLED(haystack, needle) ((haystack & needle) == needle)

        int isActive = 0;
        std::size_t retval = 0;
        ADLPMLogSupportInfo supportInfo;

        // First, find out whether the adapter supports PMLlog.
        {
            auto status = detail::amd_display_library::instance()
                .ADL2_Adapter_PMLog_Support_Get(scope, adapter.iAdapterIndex,
                &supportInfo);
            if (status != ADL_OK) {
                throw adl_exception(status);
            }
        }

        // Second, find out whether the adapter is active.
        {
            auto status = detail::amd_display_library::instance()
                .ADL2_Adapter_Active_Get(scope, adapter.iAdapterIndex,
                &isActive);
            if (status != ADL_OK) {
                throw adl_exception(status);
            }
        }

        // Now, check all of the supported sensor sources.
        if (_PWROWG_ENABLED(source, adl_sensor_source::asic)) {
            auto source = adl_sensor_source::asic;
            auto ids = detail::adl_sensor_impl::get_sensor_ids(source,
                supportInfo);

            if (!ids.empty()) {
                auto impl = new detail::adl_sensor_impl(adapter);
                impl->configure_source(source, std::move(ids));
                *oit++ = adl_sensor(std::move(impl));
                ++retval;
            }
        }

        if (_PWROWG_ENABLED(source, adl_sensor_source::cpu)) {
            auto source = adl_sensor_source::cpu;
            auto ids = detail::adl_sensor_impl::get_sensor_ids(source,
                supportInfo);

            if (!ids.empty()) {
                auto impl = new detail::adl_sensor_impl(adapter);
                impl->configure_source(source, std::move(ids));
                *oit++ = adl_sensor(std::move(impl));
                ++retval;
            }
        }

        if (_PWROWG_ENABLED(source, adl_sensor_source::graphics)) {
            auto source = adl_sensor_source::graphics;
            auto ids = detail::adl_sensor_impl::get_sensor_ids(source,
                supportInfo);

            if (!ids.empty()) {
                auto impl = new detail::adl_sensor_impl(adapter);
                impl->configure_source(source, std::move(ids));
                *oit++ = adl_sensor(std::move(impl));
                ++retval;
            }
        }

        if (_PWROWG_ENABLED(source, adl_sensor_source::soc)) {
            auto source = adl_sensor_source::soc;
            auto ids = detail::adl_sensor_impl::get_sensor_ids(source,
                supportInfo);

            if (!ids.empty()) {
                auto impl = new detail::adl_sensor_impl(adapter);
                impl->configure_source(source, std::move(ids));
                *oit++ = adl_sensor(std::move(impl));
                ++retval;
            }
        }

        if (_PWROWG_ENABLED(source, adl_sensor_source::board)) {
            auto source = adl_sensor_source::board;
            auto ids = detail::adl_sensor_impl::get_sensor_ids(source,
                supportInfo);

            if (!ids.empty()) {
                auto impl = new detail::adl_sensor_impl(adapter);
                impl->configure_source(source, std::move(ids));
                *oit++ = adl_sensor(std::move(impl));
                ++retval;
            }
        }

        return retval;
#undef _PWROWG_ENABLED
    }

    /// <summary>
    /// Creates sensors for all adapters matching <paramref name="predicate" />.
    /// </summary>
    /// <typeparam name="TPredicate"></typeparam>
    /// <param name="predicate"></param>
    /// <param name="source"></param>
    /// <returns></returns>
    template<class TPredicate>
    static std::vector<adl_sensor> for_predicate(const TPredicate& predicate,
            const adl_sensor_source source) {
        std::vector<AdapterInfo> adapters;
        std::vector<adl_sensor> retval;
        adl_scope scope;

        {
            int cnt;

            auto status = detail::amd_display_library::instance()
                .ADL2_Adapter_NumberOfAdapters_Get(scope, &cnt);
            if (status != ADL_OK) {
                throw adl_exception(status);
            }

            adapters.resize(cnt);
            retval.reserve(cnt);
        }

        ::ZeroMemory(adapters.data(), adapters.size() * sizeof(AdapterInfo));
        {
            auto status = detail::amd_display_library::instance()
                .ADL2_Adapter_AdapterInfo_Get(scope, adapters.data(),
                    static_cast<int>(adapters.size() * sizeof(AdapterInfo)));
            if (status != ADL_OK) {
                throw adl_exception(status);
            }
        }

        for (auto& a : adapters) {
            if (predicate(a)) {
                for_adapter(std::back_inserter(retval), scope, a, source);
            }
        }

        return retval;
    }

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */


/*
 * visus::power_overwhelming::adl_sensor::for_all
 */
std::size_t visus::power_overwhelming::adl_sensor::for_all(
        _Out_writes_opt_(cntSensors) adl_sensor *outSensors,
        _In_ const std::size_t cntSensors) {
    try {
        int cnt = 0;
        std::vector<adl_sensor> retval;
        detail::adl_scope scope;

        // Find out how many adapters we know.
        {
            auto status = detail::amd_display_library::instance()
                .ADL2_Adapter_NumberOfAdapters_Get(scope, &cnt);
            if (status != ADL_OK) {
                throw adl_exception(status);
            }
        }

        // Get the descriptors for all the adapters.
        std::vector<AdapterInfo> adapters(cnt);
        ::ZeroMemory(adapters.data(), adapters.size() * sizeof(AdapterInfo));

        {
            auto status = detail::amd_display_library::instance()
                .ADL2_Adapter_AdapterInfo_Get(scope, adapters.data(),
                static_cast<int>(adapters.size() * sizeof(AdapterInfo)));
            if (status != ADL_OK) {
                throw adl_exception(status);
            }
        }

        // For each adapter, get all supported sensors.
        for (auto& a : adapters) {
            detail::for_adapter(std::back_inserter(retval), scope, a,
                adl_sensor_source::all);
        }

        // Move as many sensors as possible to the output buffer.
        if (outSensors != nullptr) {
            for (std::size_t i = 0; i < (std::min)(retval.size(), cntSensors);
                    ++i) {
                outSensors[i] = std::move(retval[i]);
            }

        }

        return retval.size();
    } catch (...) {
        return 0;
    }
}


/*
 * visus::power_overwhelming::adl_sensor::from_index
 */
visus::power_overwhelming::adl_sensor
visus::power_overwhelming::adl_sensor::from_index(_In_ const int index,
        _In_ const adl_sensor_source source) {
    adl_sensor retval;

    auto status = detail::amd_display_library::instance()
        .ADL2_Device_PMLog_Device_Create(nullptr, index, &retval._impl->device);
    if (status != ADL_OK) {
        throw adl_exception(status);
    }

    throw "TODO: Implement retrieval from index.";

    return retval;
}


/*
 * visus::power_overwhelming::adl_sensor::from_udid
 */
visus::power_overwhelming::adl_sensor
visus::power_overwhelming::adl_sensor::from_udid(_In_z_ const char *udid,
        _In_ const adl_sensor_source source) {
    if (udid == nullptr) {
        throw std::invalid_argument("The unique device identifier cannot be "
            "null.");
    }

    auto retval = detail::for_predicate([&](const AdapterInfo &a) {
        return (::strcmp(udid, a.strUDID) == 0);
    }, source);

    if (retval.size() != 1) {
        throw std::invalid_argument("The unique device identifier did not "
            "match a single device.");
    }

    return std::move(retval.front());
}


/*
 * visus::power_overwhelming::adl_sensor::from_udid
 */
visus::power_overwhelming::adl_sensor
visus::power_overwhelming::adl_sensor::from_udid(_In_z_ const wchar_t *udid,
        _In_ const adl_sensor_source source) {
    auto u = convert_string<char>(udid);
    return from_udid(u.c_str(), source);
}


/*
 * visus::power_overwhelming::adl_sensor::adl_sensor
 */
visus::power_overwhelming::adl_sensor::adl_sensor(void)
    : _impl(new detail::adl_sensor_impl()) { }


/*
 * visus::power_overwhelming::adl_sensor::~adl_sensor
 */
visus::power_overwhelming::adl_sensor::~adl_sensor(void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::adl_sensor::name
 */
_Ret_maybenull_z_ const wchar_t *visus::power_overwhelming::adl_sensor::name(
        void) const noexcept {
    if (this->_impl == nullptr) {
        return nullptr;
    } else {
        return this->_impl->sensor_name.c_str();
    }
}


/*
 * visus::power_overwhelming::adl_sensor::sample
 */
void visus::power_overwhelming::adl_sensor::sample(
        _In_opt_ const measurement_callback on_measurement,
        _In_ const microseconds_type period,
        _In_opt_ void *context) {
#if defined(_WIN32)
    ::OutputDebugStringW(L"PWROWG DEPRECATION WARNING: This method is only "
        L"provided for backwards compatibility and might be removed in "
        L"future versions of the library. Use async_sampling to configure "
        L"asynchronous sampling.\r\n");
#endif /* defined(_WIN32) */
    this->check_not_disposed();
    this->sample_async(std::move(async_sampling()
        .samples_every(period)
        .delivers_measurements_to(on_measurement)
        .passes_context(context)));
}


/*
 * visus::power_overwhelming::adl_sensor::start
 */
void visus::power_overwhelming::adl_sensor::start(
        _In_ const microseconds_type sampling_period) {
    using std::chrono::duration;
    using std::chrono::duration_cast;
    typedef duration<microseconds_type, std::micro> interval_type;

    this->check_not_disposed();

    auto sampler_rate = interval_type(sampling_period);
    auto adl_rate = duration_cast<std::chrono::milliseconds>(sampler_rate);
    this->_impl->start(static_cast<unsigned long>(adl_rate.count()));
}


/*
 * visus::power_overwhelming::adl_sensor::stop
 */
void visus::power_overwhelming::adl_sensor::stop(void) {
    if (this->_impl != nullptr) {
        this->_impl->stop();
    }
}


/*
 * visus::power_overwhelming::adl_sensor::source
 */
visus::power_overwhelming::adl_sensor_source
visus::power_overwhelming::adl_sensor::source(void) const {
    this->check_not_disposed();
    return this->_impl->source;
}


/*
 * visus::power_overwhelming::adl_sensor::udid
 */
_Ret_maybenull_z_ const char *visus::power_overwhelming::adl_sensor::udid(
        void) const noexcept {
    if (this->_impl == nullptr) {
        return nullptr;
    } else {
        return this->_impl->udid.c_str();
    }
}


/*
 * visus::power_overwhelming::adl_sensor::operator =
 */
visus::power_overwhelming::adl_sensor&
visus::power_overwhelming::adl_sensor::operator =(
        _In_ adl_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        delete this->_impl;
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::adl_sensor::operator bool
 */
visus::power_overwhelming::adl_sensor::operator bool(void) const noexcept {
    return (this->_impl != nullptr);
}


/*
 * visus::power_overwhelming::adl_sensor::sample_async
 */
void visus::power_overwhelming::adl_sensor::sample_async(
        _Inout_ async_sampling&& sampling) {
    using std::chrono::duration;
    using std::chrono::duration_cast;
    typedef duration<microseconds_type, std::micro> interval_type;

    if ((this->_impl->async_sampling = std::move(sampling))) {
        auto sampler_rate = interval_type(sampling.interval());
        auto adl_rate = duration_cast<std::chrono::milliseconds>(sampler_rate);

        // Make sure that the sensor is running before queuing to the thread.
        if (!this->_impl->running()) {
            this->_impl->start(static_cast<unsigned long>(adl_rate.count()));
        }

        // Register in the sampler collection dedicated to ADL. This is required
        // as we need to be able to find out when the last ADL sampler was
        // removed from the collection. We therefore cannot share the samplers
        // with other sensors.
        detail::adl_sensor_impl::sampler += this->_impl;

    } else {
        detail::adl_sensor_impl::sampler -= this->_impl;

        if (!detail::adl_sensor_impl::sampler) {
            // If there is no sensor left to sample, stop the sensor. This
            // condition is the reason for having a dedicated ADL sampler
            // collection.
            this->_impl->stop();
        }
    }
}


/*
 * visus::power_overwhelming::adl_sensor::sample_sync
 */
visus::power_overwhelming::measurement_data
visus::power_overwhelming::adl_sensor::sample_sync(void) const {
    this->check_not_disposed();
    const auto is_running = this->_impl->running();

    if (!is_running) {
        // If the sensor is not running asynchronously, start it for obtaining
        // a single sample.
        this->_impl->start(0);
    }

    auto retval = this->_impl->sample();

    if (!is_running) {
        // If we started the sensor here, stop it.
        this->_impl->stop();
    }

    return retval;
}
