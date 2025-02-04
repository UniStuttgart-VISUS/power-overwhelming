//// <copyright file="adl_throttling_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
//// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
//// Licensed under the MIT licence. See LICENCE file for details.
//// </copyright>
//// <author>Christoph Müller</author>
//
//#include "visus/pwrowg/adl_throttling_sensor.h"
//
//#include <cassert>
//
//#include "adl_sensor_impl.h"
//#include "adl_utils.h"
//
//
///*
// * visus::power_overwhelming::adl_throttling_sensor::for_all
// */
//std::size_t visus::power_overwhelming::adl_throttling_sensor::for_all(
//        _Out_writes_opt_(cnt) adl_throttling_sensor *dst,
//        _In_ const std::size_t cnt) {
//    try {
//        detail::adl_scope scope;
//
//        // Get all adapters that support throttling info.
//        auto adapters = detail::get_adapters_if(scope,
//                [](detail::adl_scope& s, const AdapterInfo& a) {
//            return detail::supports_sensor(s, a, ADL_PMLOG_THROTTLER_STATUS);
//        });
//
//        // Create a sensor for each adapter we can return.
//        auto cur = dst;
//        const auto end = (cur != nullptr) ? cur + cnt : nullptr;
//        for (auto& a : adapters) {
//            if (cur < end) {
//                *cur++ = adl_throttling_sensor(new detail::adl_sensor_impl(a));
//            }
//        }
//
//        // Always return the number of sensors we *could* return.
//        return adapters.size();
//    } catch (...) {
//        return 0;
//    }
//}
//
//
///*
// * visus::power_overwhelming::adl_throttling_sensor::from_udid
// */
//visus::power_overwhelming::adl_throttling_sensor
//visus::power_overwhelming::adl_throttling_sensor::from_udid(
//        _In_z_ const char *udid) {
//    if (udid == nullptr) {
//        throw std::invalid_argument("The unique device identifier cannot be "
//            "null.");
//    }
//
//    detail::adl_scope scope;
//
//    // Search all adapters for the specified UDID.
//    auto adapters = detail::get_adapters_if(scope,
//        [udid](const detail::adl_scope&, const AdapterInfo& a) {
//            return (::strcmp(udid, a.strUDID) == 0);
//    });
//    if (adapters.size() != 1) {
//        throw std::invalid_argument("The unique device identifier did not "
//            "match a single device.");
//    }
//
//    // Check whether the adapter supports retrieving the throttling status.
//    if (!detail::supports_sensor(scope, adapters.front(),
//            ADL_PMLOG_THROTTLER_STATUS)) {
//        throw std::invalid_argument("The adapter for the specified UDID was "
//            "found, but does not allow for retrieving the throttling state.");
//    }
//
//    return adl_throttling_sensor(new detail::adl_sensor_impl(adapters.front()));
//}
//
//
///*
// * visus::power_overwhelming::adl_throttling_sensor::from_udid
// */
//visus::power_overwhelming::adl_throttling_sensor
//visus::power_overwhelming::adl_throttling_sensor::from_udid(
//        _In_z_ const wchar_t *udid) {
//    auto u = convert_string<char>(udid);
//    return from_udid(u.c_str());
//}
//
//
///*
// * visus::power_overwhelming::adl_throttling_sensor::adl_throttling_sensor
// */
//visus::power_overwhelming::adl_throttling_sensor::adl_throttling_sensor(
//    void) noexcept : _impl(nullptr) { } //_impl(new detail::adl_sensor_impl()) { }
//
//
///*
// * visus::power_overwhelming::adl_throttling_sensor::~adl_throttling_sensor
// */
//visus::power_overwhelming::adl_throttling_sensor::~adl_throttling_sensor(void) {
//    delete this->_impl;
//}
//
//
///*
// * visus::power_overwhelming::adl_throttling_sensor::name
// */
//_Ret_maybenull_z_ const wchar_t *
//visus::power_overwhelming::adl_throttling_sensor::name(void) const noexcept {
//    return (this->_impl != nullptr)
//        ? this->_impl->sensor_name.c_str()
//        : nullptr;
//}
//
//
///*
// * visus::power_overwhelming::adl_throttling_sensor::sample
// */
//void visus::power_overwhelming::adl_throttling_sensor::sample(
//        _Inout_ async_sampling&& async_sampling) {
//    using std::chrono::duration;
//    using std::chrono::duration_cast;
//    typedef decltype(async_sampling.interval()) interval_ticks;
//    typedef duration<interval_ticks, std::micro> interval_type;
//
//    if ((this->_impl->async_sampling = std::move(async_sampling))) {
//        auto sampler_rate = interval_type(this->_impl->async_sampling.interval());
//        auto adl_rate = duration_cast<std::chrono::milliseconds>(sampler_rate);
//
//        // Make sure that the sensor is running before queuing to the thread.
//        if (!this->_impl->running()) {
//            this->_impl->start(static_cast<unsigned long>(adl_rate.count()));
//        }
//
//        // Register in the sampler collection dedicated to ADL. This is required
//        // as we need to be able to find out when the last ADL sampler was
//        // removed from the collection. We therefore cannot share the samplers
//        // with other sensors.
//        detail::adl_sensor_impl::sampler += this->_impl;
//
//    } else {
//        detail::adl_sensor_impl::sampler -= this->_impl;
//
//        if (!detail::adl_sensor_impl::sampler) {
//            // If there is no sensor left to sample, stop the sensor. This
//            // condition is the reason for having a dedicated ADL sampler
//            // collection.
//            this->_impl->stop();
//        }
//    }
//}
//
//
///*
// * visus::power_overwhelming::adl_throttling_sensor::operator =
// */
//visus::power_overwhelming::adl_throttling_sensor&
//visus::power_overwhelming::adl_throttling_sensor::operator =(
//        _Inout_ adl_throttling_sensor&& rhs) noexcept {
//    if (this != std::addressof(rhs)) {
//        delete this->_impl;
//        this->_impl = rhs._impl;
//        rhs._impl = nullptr;
//    }
//
//    return *this;
//}
//
//
///*
// * visus::power_overwhelming::adl_throttling_sensor::operator bool
// */
//visus::power_overwhelming::adl_throttling_sensor::operator bool(
//        void) const noexcept {
//    return (this->_impl != nullptr);
//}
//
//
///*
// * visus::power_overwhelming::adl_throttling_sensor::adl_throttling_sensor
// */
//visus::power_overwhelming::adl_throttling_sensor::adl_throttling_sensor(
//        _In_ detail::adl_sensor_impl *impl) noexcept : _impl(impl) {
//    assert(this->_impl != nullptr);
//    this->_impl->configure_source(ADL_PMLOG_THROTTLER_STATUS);
//}
