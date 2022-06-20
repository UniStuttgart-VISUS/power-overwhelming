// <copyright file="adl_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/adl_sensor.h"

#include <algorithm>
#include <vector>

#include "power_overwhelming/adl_sensor_source.h"

#include "adl_exception.h"
#include "adl_scope.h"
#include "adl_sensor_impl.h"



namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Creates sensors for all adapters matching <paramref name="predicate" />.
    /// </summary>
    /// <typeparam name="TPredicate"></typeparam>
    /// <param name="predicate"></param>
    /// <returns></returns>
    template<class TPredicate>
    static std::vector<adl_sensor> for_predicate(const TPredicate& predicate) {
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

        for (auto& a : adapters) {
            if (predicate(a)) {
                retval.emplace_back(new detail::adl_sensor_impl(a));
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
        adl_sensor *outSensors, const std::size_t cntSensors) {
    try {
        int cnt = 0;
        std::size_t retval = 0;
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
        {
            auto status = detail::amd_display_library::instance()
                .ADL2_Adapter_AdapterInfo_Get(scope, adapters.data(),
                static_cast<int>(adapters.size() * sizeof(AdapterInfo)));
            if (status != ADL_OK) {
                throw adl_exception(status);
            }
        }

        // For each adapter, check which sensors are supported.
        for (auto& a : adapters) {
            int isActive = 0;
            ADLPMLogSupportInfo supportInfo;

            {
                auto status = detail::amd_display_library::instance()
                    .ADL2_Adapter_PMLog_Support_Get(scope, a.iAdapterIndex,
                    &supportInfo);
                if (status != ADL_OK) {
                    throw adl_exception(status);
                }
            }

            {
                auto status = detail::amd_display_library::instance()
                    .ADL2_Adapter_Active_Get(scope, a.iAdapterIndex, &isActive);
                if (status != ADL_OK) {
                    throw adl_exception(status);
                }
            }

            {
                auto source = adl_sensor_source::asic;
                auto ids = detail::adl_sensor_impl::get_sensor_ids(source,
                    supportInfo);

                if (!ids.empty()) {
                    if ((outSensors != nullptr) && (retval < cntSensors)) {
                        auto impl = new detail::adl_sensor_impl(a);
                        impl->configure_source(source, std::move(ids));
                        outSensors[retval] = adl_sensor(std::move(impl));
                    }
                    ++retval;
                }
            }

            {
                auto source = adl_sensor_source::cpu;
                auto ids = detail::adl_sensor_impl::get_sensor_ids(source,
                    supportInfo);

                if (!ids.empty()) {
                    if ((outSensors != nullptr) && (retval < cntSensors)) {
                        auto impl = new detail::adl_sensor_impl(a);
                        impl->configure_source(source, std::move(ids));
                        outSensors[retval] = adl_sensor(std::move(impl));
                    }
                    ++retval;
                }
            }

            {
                auto source = adl_sensor_source::graphics;
                auto ids = detail::adl_sensor_impl::get_sensor_ids(source,
                    supportInfo);

                if (!ids.empty()) {
                    if ((outSensors != nullptr) && (retval < cntSensors)) {
                        auto impl = new detail::adl_sensor_impl(a);
                        impl->configure_source(source, std::move(ids));
                        outSensors[retval] = adl_sensor(std::move(impl));
                    }
                    ++retval;
                }
            }

            {
                auto source = adl_sensor_source::soc;
                auto ids = detail::adl_sensor_impl::get_sensor_ids(source,
                    supportInfo);

                if (!ids.empty()) {
                    if ((outSensors != nullptr) && (retval < cntSensors)) {
                        auto impl = new detail::adl_sensor_impl(a);
                        impl->configure_source(source, std::move(ids));
                        outSensors[retval] = adl_sensor(std::move(impl));
                    }
                    ++retval;
                }
            }
        }

        return retval;
    } catch (...) {
        return 0;
    }
}


/*
 * visus::power_overwhelming::adl_sensor::from_index
 */
visus::power_overwhelming::adl_sensor
visus::power_overwhelming::adl_sensor::from_index(const int index,
        const adl_sensor_source source) {
    adl_sensor retval;

    auto status = detail::amd_display_library::instance()
        .ADL2_Device_PMLog_Device_Create(nullptr, index, &retval._impl->device);
    if (status != ADL_OK) {
        throw adl_exception(status);
    }

    return retval;
}


/*
 * visus::power_overwhelming::adl_sensor::from_udid
 */
visus::power_overwhelming::adl_sensor
visus::power_overwhelming::adl_sensor::from_udid(const char *udid,
        const adl_sensor_source source) {
    if (udid == nullptr) {
        throw std::invalid_argument("The unique device identifier cannot be "
            "null.");
    }

    auto retval = detail::for_predicate([&](const AdapterInfo &a) {
        return (::strcmp(udid, a.strUDID) == 0);
    });

    if (retval.size() != 1) {
        throw std::invalid_argument("The unique device identifier did not "
            "match a single device.");
    }

    return std::move(retval.front());
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
const wchar_t *visus::power_overwhelming::adl_sensor::name(
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
visus::power_overwhelming::measurement
visus::power_overwhelming::adl_sensor::sample(
        const timestamp_resolution resolution) const {
    this->check_not_disposed();
    const auto is_running = this->_impl->running();

    if (!is_running) {
        // If the sensor is not running asynchronously, start it for obtaining
        // a single sample.
        this->_impl->start(0);
    }

    auto retval = this->_impl->sample(resolution);

    if (!is_running) {
        // If we started the sensor here, stop it.
        this->_impl->stop();
    }

    return retval;
}


/*
 * visus::power_overwhelming::adl_sensor::sample
 */
void visus::power_overwhelming::adl_sensor::sample(
        const measurement_callback on_measurement,
        const microseconds_type sampling_period) {
    using std::chrono::duration_cast;
    typedef decltype(detail::adl_sensor_impl::sampler)::interval_type
        interval_type;

    this->check_not_disposed();

    if (on_measurement != nullptr) {
        auto sampler_rate = interval_type(sampling_period);
        auto adl_rate = duration_cast<std::chrono::milliseconds>(sampler_rate);

        // Make sure that the sensor is running before queuing to the thread.
        if (!this->_impl->running()) {
            this->_impl->start(static_cast<unsigned long>(adl_rate.count()));
        }

        if (!detail::adl_sensor_impl::sampler.add(this->_impl, on_measurement,
                sampler_rate)) {
            throw std::logic_error("Asynchronous sampling cannot be started "
                "while it is already running.");
        }

    } else {
        detail::adl_sensor_impl::sampler.remove(this->_impl);

        if (!detail::adl_sensor_impl::sampler.samples()) {
            // If there is no sensor left to sample, stop the sensor.
            assert(this->_impl->running());
            this->_impl->stop();
        }
    }
}


/*
 * visus::power_overwhelming::adl_sensor::operator =
 */
visus::power_overwhelming::adl_sensor&
visus::power_overwhelming::adl_sensor::operator =(adl_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
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
