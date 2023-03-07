// <copyright file="emi_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/emi_sensor.h"

#include <cinttypes>
#include <memory>
#include <regex>
#include <system_error>
#include <stdexcept>
#include <vector>

#include "emi_sensor_impl.h"
#include "setup_api.h"


/*
 * visus::power_overwhelming::emi_sensor::for_all
 */
std::size_t visus::power_overwhelming::emi_sensor::for_all(
        emi_sensor *out_sensors, const std::size_t cnt_sensors) {
#if defined(_WIN32)
    typedef detail::emi_sensor_impl::string_type string_type;
    return detail::emi_sensor_impl::create(out_sensors, cnt_sensors,
        [](const string_type&, const EMI_CHANNEL_V2 *) { return true; });
#else /* defined(_WIN32) */
    return 0;
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::emi_sensor::for_channel
 */
std::size_t visus::power_overwhelming::emi_sensor::for_channel(
        emi_sensor *out_sensors, const std::size_t cnt_sensors,
        const wchar_t *channel) {
    if (channel == nullptr) {
        throw std::invalid_argument("The regular expression selecting the "
            "device must not be null.");
    }

#if defined(_WIN32)
    typedef detail::emi_sensor_impl::string_type string_type;
    std::basic_regex<wchar_t> rx(channel);
    return detail::emi_sensor_impl::create(out_sensors, cnt_sensors,
            [&rx](const string_type&, const EMI_CHANNEL_V2 *c) {
        return std::regex_match(c->ChannelName, rx);
    });
#else /* defined(_WIN32) */
    return 0;
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::emi_sensor::for_device
 */
std::size_t visus::power_overwhelming::emi_sensor::for_device(
        emi_sensor *out_sensors, const std::size_t cnt_sensors,
        const char_type *device) {
    if (device == nullptr) {
        throw std::invalid_argument("The regular expression selecting the "
            "device must not be null.");
    }

#if defined(_WIN32)
    typedef detail::emi_sensor_impl::string_type string_type;
    std::basic_regex<char_type> rx(device);
    return detail::emi_sensor_impl::create(out_sensors, cnt_sensors,
            [&rx](const string_type& n, const EMI_CHANNEL_V2 *) {
        return std::regex_match(n, rx);
    });
#else /* defined(_WIN32) */
    return 0;
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::emi_sensor::emi_sensor
 */
visus::power_overwhelming::emi_sensor::emi_sensor(void)
        : _impl(new detail::emi_sensor_impl()) {
    // Note: EMI sensor must initialise here in order to allow for the sensor
    // implementation create the instances in-place.
}


/*
 * visus::power_overwhelming::emi_sensor::~emi_sensor
 */
visus::power_overwhelming::emi_sensor::~emi_sensor(void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::emi_sensor::channel
 */
visus::power_overwhelming::emi_sensor::channel_type
visus::power_overwhelming::emi_sensor::channel(void) const {
#if defined(_WIN32)
    return (*this)
        ? this->_impl->channel
        : static_cast<decltype(this->channel())>(0);
#else /* defined(_WIN32) */
    return 0;
#endif /* defined(_WIN3) */
}


/*
 * visus::power_overwhelming::emi_sensor::channels
 */
visus::power_overwhelming::emi_sensor::channel_type
visus::power_overwhelming::emi_sensor::channels(void) const {
#if defined(_WIN32)
    return (*this)
        ? this->_impl->device->channels()
        : static_cast<decltype(this->channels())>(0);
#else /* defined(_WIN32) */
    return 0;
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::emi_sensor::name
 */
const wchar_t *visus::power_overwhelming::emi_sensor::name(
        void) const noexcept {
#if defined(_WIN32)
    return (this->_impl != nullptr)
        ? this->_impl->sensor_name.c_str()
        : nullptr;
#else /* defined(_WIN32) */
    return nullptr;
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::emi_sensor::path
 */
const visus::power_overwhelming::emi_sensor::char_type *
visus::power_overwhelming::emi_sensor::path(void) const noexcept {
#if defined(_WIN32)
    return (this->_impl != nullptr)
        ? this->_impl->path.c_str()
        : nullptr;
#else /* defined(_WIN32) */
    return nullptr;
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::emi_sensor::sample
 */
visus::power_overwhelming::measurement
visus::power_overwhelming::emi_sensor::sample(
        const timestamp_resolution resolution) const {
#if defined(_WIN32)
    this->check_not_disposed();

    switch (this->version()) {
        case EMI_VERSION_V1: {
            EMI_MEASUREMENT_DATA_V1 s;
            this->_impl->sample(&s, sizeof(s));
            return this->_impl->evaluate(s, resolution);
            }

        case EMI_VERSION_V2: {
            auto m = this->_impl->sample();
            auto s = reinterpret_cast<EMI_MEASUREMENT_DATA_V2 *>(m.data());
            return this->_impl->evaluate(*s, resolution);
            }

        default:
            throw std::logic_error("The specified version of the Energy "
                "Meter Interface is not supported by the implementation.");
    }
#else /* defined(_WIN32) */
    throw std::logic_error("The EMI sensor is not supported on this platform.");
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::emi_sensor::sample
 */
void visus::power_overwhelming::emi_sensor::sample(
        const measurement_callback on_measurement,
        const microseconds_type sampling_period,
        void *context) {
    typedef decltype(detail::emi_sensor_impl::sampler)::interval_type
        interval_type;

    this->check_not_disposed();

    if (on_measurement != nullptr) {
        if (!detail::emi_sensor_impl::sampler.add(this->_impl, on_measurement,
                context, interval_type(sampling_period))) {
            throw std::logic_error("Asynchronous sampling cannot be started "
                "while it is already running.");
        }

    } else {
        detail::emi_sensor_impl::sampler.remove(this->_impl);
    }
}


#if defined(_WIN32)
/*
 * visus::power_overwhelming::emi_sensor::sample
 */
EMI_MEASUREMENT_DATA_V1 *visus::power_overwhelming::emi_sensor::sample(
        EMI_MEASUREMENT_DATA_V1& measurement) const {
    this->check_not_disposed();

    if (this->version() != EMI_VERSION_V1) {
        throw std::invalid_argument("The given sensor does not use an EMIv1 "
            "device.");
    }

    this->_impl->sample(&measurement, sizeof(measurement));
    return &measurement;
}
#endif /* defined(_WIN32) */


#if defined(_WIN32)
/*
 * visus::power_overwhelming::emi_sensor::sample
 */
EMI_MEASUREMENT_DATA_V2 *visus::power_overwhelming::emi_sensor::sample(
        EMI_MEASUREMENT_DATA_V2 *measurement, const std::size_t size) const {
    this->check_not_disposed();

    if (this->version() != EMI_VERSION_V2) {
        throw std::invalid_argument("The given sensor does not use an EMIv2 "
            "device.");
    }
    if (size < sizeof(EMI_MEASUREMENT_DATA_V2)) {
        throw std::invalid_argument("The output buffer must be able to hold at "
            "least the EMI_MEASUREMENT_DATA_V2 structure.");
    }

    this->_impl->sample(measurement, size);
    return measurement;
}
#endif /* defined(_WIN32) */


#if 0
/*
 * visus::power_overwhelming::emi_sensor::sample
 */
void visus::power_overwhelming::emi_sensor::sample(
        const measurement_callback on_measurement,
        const microseconds_type sampling_period,
        void *context) {
    typedef decltype(detail::emi_sensor_impl::sampler)::interval_type
        interval_type;

    this->check_not_disposed();

    if (on_measurement != nullptr) {
        if (!detail::emi_sensor_impl::sampler.add(this->_impl, on_measurement,
                context, interval_type(sampling_period))) {
            throw std::logic_error("Asynchronous sampling cannot be started "
                "while it is already running.");
        }

    } else {
        detail::emi_sensor_impl::sampler.remove(this->_impl);
    }
}
#endif


/*
 * visus::power_overwhelming::emi_sensor::version
 */
visus::power_overwhelming::emi_sensor::version_type
visus::power_overwhelming::emi_sensor::version(void) const noexcept {
#if defined(_WIN32)
    return (*this)
        ? this->_impl->device->version().EmiVersion
        : static_cast<decltype(EMI_VERSION::EmiVersion)>(0);
#else /* defined(_WIN32) */
    return 0;
#endif /* defined(_WIN32) */
}

/*
 * visus::power_overwhelming::emi_sensor::operator =
 */
visus::power_overwhelming::emi_sensor&
visus::power_overwhelming::emi_sensor::operator =(emi_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::emi_sensor::operator bool
 */
visus::power_overwhelming::emi_sensor::operator bool(void) const noexcept {
#if defined(_WIN32)
    return ((this->_impl != nullptr) && (this->_impl->device != nullptr));
#else /* defined(_WIN32) */
    return false;
#endif /* defined(_WIN32) */
}
