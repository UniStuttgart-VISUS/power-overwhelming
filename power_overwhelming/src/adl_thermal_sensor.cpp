// <copyright file="adl_thermal_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/adl_thermal_sensor.h"

#include <cassert>

#include "adl_sensor_impl.h"
#include "adl_utils.h"
#include "timestamp.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// The list of known thermal sensors on AMD.
    /// </summary>
    static const std::vector<ADL_PMLOG_SENSORS> thermal_sensors = {
        ADL_PMLOG_TEMPERATURE_EDGE,
        ADL_PMLOG_TEMPERATURE_MEM,
        ADL_PMLOG_TEMPERATURE_VRVDDC,
        ADL_PMLOG_TEMPERATURE_VRMVDD,
        ADL_PMLOG_TEMPERATURE_LIQUID,
        ADL_PMLOG_TEMPERATURE_PLX,
        ADL_PMLOG_TEMPERATURE_VRSOC,
        ADL_PMLOG_TEMPERATURE_VRMVDD0,
        ADL_PMLOG_TEMPERATURE_VRMVDD1,
        ADL_PMLOG_TEMPERATURE_HOTSPOT,
        ADL_PMLOG_TEMPERATURE_GFX,
        ADL_PMLOG_TEMPERATURE_SOC,
        ADL_PMLOG_TEMPERATURE_CPU,
        ADL_PMLOG_TEMPERATURE_LIQUID0,
        ADL_PMLOG_TEMPERATURE_LIQUID1,
        ADL_PMLOG_TEMPERATURE_HOTSPOT_GCD,
        ADL_PMLOG_TEMPERATURE_HOTSPOT_MCD
    };

} /* namespace detail */
} /* namespace detail */
} /* namespace visus */


/*
 * visus::power_overwhelming::adl_thermal_sensor::for_all
 */
std::size_t visus::power_overwhelming::adl_thermal_sensor::for_all(
        _Out_writes_opt_(cnt) adl_thermal_sensor *dst,
        _In_ const std::size_t cnt) {
    try {
        std::vector<AdapterInfo> adapters;
        detail::adl_scope scope;

        // Get all adapters that support any of the temperature sensors.
        detail::get_adapters_if(std::back_inserter(adapters), scope,
                [](detail::adl_scope& scope, const AdapterInfo& a) {
            return detail::supports_any_sensor(scope, a,
                detail::thermal_sensors.begin(),
                detail::thermal_sensors.end());
        });

        // Create a sensor for each adapter.
        std::size_t retval = 0;
        for (auto& a : adapters) {
            for (auto s : detail::thermal_sensors) {
                if (detail::supports_sensor(scope, a, s)) {
                    if (retval < cnt) {
                        dst[retval] = adl_thermal_sensor(
                            new detail::adl_sensor_impl(a));
                        dst[retval++]._impl->configure_source(s);
                    } else {
                        // If we do not have enough space, just count as we want
                        // to report the total number of sensors available even
                        // if the buffer is too small.
                        ++retval;
                    }
                }
            }
        }

        return adapters.size();
    } catch (...) {
        return 0;
    }
}


/*
 * visus::power_overwhelming::adl_thermal_sensor::for_udid
 */
std::size_t visus::power_overwhelming::adl_thermal_sensor::for_udid(
        _Out_writes_opt_(cnt) adl_thermal_sensor *dst,
        _In_ const std::size_t cnt,
        _In_z_ const char *udid) {
    if (udid == nullptr) {
        throw std::invalid_argument("The unique device identifier cannot be "
            "null.");
    }

    throw "TODO";

    try {
        std::vector<AdapterInfo> adapters;
        detail::adl_scope scope;

        // Get all adapters that support throttling info.
        // Get all adapters that support any of the temperature sensors.
        for (auto s : detail::thermal_sensors) {
            detail::get_adapters_if(std::back_inserter(adapters), scope,
                    [s, udid](detail::adl_scope& scope, const AdapterInfo& a) {
                return detail::supports_sensor(scope, a, s)
                    && (::strcmp(udid, a.strUDID) == 0);
            });
        }

        // Create a sensor for each adapter.
        auto cur = dst;
        const auto end = (cur != nullptr) ? cur + cnt : nullptr;
        for (auto &a : adapters) {
            if (cur < end) {
            //    *cur++ = adl_thermal_sensor(new detail::adl_sensor_impl(a));
            }
        }

        return adapters.size();
    } catch (...) {
        return 0;
    }
}


 /*
  * visus::power_overwhelming::adl_thermal_sensor::for_udid
  */
std::size_t visus::power_overwhelming::adl_thermal_sensor::for_udid(
        _Out_writes_opt_(cnt) adl_thermal_sensor *dst,
        _In_ const std::size_t cnt,
        _In_z_ const wchar_t *udid) {
    auto u = convert_string<char>(udid);
    return for_udid(dst, cnt, u.c_str());
}


/*
 * visus::power_overwhelming::adl_thermal_sensor::adl_thermal_sensor
 */
visus::power_overwhelming::adl_thermal_sensor::adl_thermal_sensor(
    void) noexcept : _impl(nullptr) { } //_impl(new detail::adl_sensor_impl()) { }


/*
 * visus::power_overwhelming::adl_thermal_sensor::~adl_thermal_sensor
 */
visus::power_overwhelming::adl_thermal_sensor::~adl_thermal_sensor(void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::adl_thermal_sensor::metering_point
 */
visus::power_overwhelming::temperature_metering_point
visus::power_overwhelming::adl_thermal_sensor::metering_point(
        void) const noexcept {
    if (this->_impl == nullptr) {
        return temperature_metering_point::unknown;
    }

    switch (this->_impl->start_input.usSensors[0]) {
        case ADL_PMLOG_TEMPERATURE_MEM:
            return temperature_metering_point::memory;

        case ADL_PMLOG_TEMPERATURE_HOTSPOT:
            return temperature_metering_point::hotspot;

        default:
            return temperature_metering_point::unknown;
    }
}


/*
 * visus::power_overwhelming::adl_thermal_sensor::name
 */
_Ret_maybenull_z_ const wchar_t *
visus::power_overwhelming::adl_thermal_sensor::name(void) const noexcept {
    return (this->_impl != nullptr)
        ? this->_impl->sensor_name.c_str()
        : nullptr;
}


/*
 * visus::power_overwhelming::adl_thermal_sensor::sample
 */
void visus::power_overwhelming::adl_thermal_sensor::sample(
        _Inout_ async_sampling&& async_sampling) {
    using std::chrono::duration;
    using std::chrono::duration_cast;
    typedef decltype(async_sampling.interval()) interval_ticks;
    typedef duration<interval_ticks, std::micro> interval_type;

    if ((this->_impl->async_sampling = std::move(async_sampling))) {
        auto sampler_rate = interval_type(this->_impl->async_sampling.interval());
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
 * visus::power_overwhelming::adl_thermal_sensor::operator =
 */
visus::power_overwhelming::adl_thermal_sensor&
visus::power_overwhelming::adl_thermal_sensor::operator =(
        _Inout_ adl_thermal_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        delete this->_impl;
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::adl_thermal_sensor::operator bool
 */
visus::power_overwhelming::adl_thermal_sensor::operator bool(
        void) const noexcept {
    return (this->_impl != nullptr);
}


/*
 * visus::power_overwhelming::adl_thermal_sensor::adl_thermal_sensor
 */
visus::power_overwhelming::adl_thermal_sensor::adl_thermal_sensor(
    _In_ detail::adl_sensor_impl *impl) noexcept : _impl(impl) { }
