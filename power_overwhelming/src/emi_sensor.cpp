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


#define ERROR_MSG_NOT_SUPPORTED ("The EMI sensor is not supported on this " \
    "platform.")


/*
 * visus::power_overwhelming::emi_sensor::for_all
 */
std::size_t visus::power_overwhelming::emi_sensor::for_all(
        _Out_writes_opt_(cnt_sensors) emi_sensor *out_sensors,
        _In_ const std::size_t cnt_sensors) {
#if defined(_WIN32)
    typedef detail::emi_sensor_impl::string_type string_type;
    return detail::emi_sensor_impl::create(out_sensors, cnt_sensors,
            [](const string_type&, const EMI_CHANNEL_V2 *, const std::size_t) {
        return true;
    });
#else /* defined(_WIN32) */
    return 0;
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::emi_sensor::for_channel
 */
std::size_t visus::power_overwhelming::emi_sensor::for_channel(
        _Out_writes_opt_(cnt_sensors) emi_sensor *out_sensors,
        _In_ const std::size_t cnt_sensors,
        _In_z_ const wchar_t *channel) {
    if (channel == nullptr) {
        throw std::invalid_argument("The regular expression selecting the "
            "channel must not be null.");
    }

#if defined(_WIN32)
    typedef detail::emi_sensor_impl::string_type string_type;
    std::basic_regex<wchar_t> rx(channel);
    return detail::emi_sensor_impl::create(out_sensors, cnt_sensors,
            [&rx](const string_type&, const EMI_CHANNEL_V2 *c,
            const std::size_t) {
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
        _Out_writes_opt_(cnt_sensors) emi_sensor *out_sensors,
        _In_ const std::size_t cnt_sensors,
        _In_z_ const char_type *device) {
    if (device == nullptr) {
        throw std::invalid_argument("The regular expression selecting the "
            "device must not be null.");
    }

#if defined(_WIN32)
    typedef detail::emi_sensor_impl::string_type string_type;
    std::basic_regex<char_type> rx(device);
    return detail::emi_sensor_impl::create(out_sensors, cnt_sensors,
            [&rx](const string_type& d, const EMI_CHANNEL_V2 *,
            const std::size_t) {
        return std::regex_match(d, rx);
    });
#else /* defined(_WIN32) */
    return 0;
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::emi_sensor::for_device_and_channel
 */
std::size_t visus::power_overwhelming::emi_sensor::for_device_and_channel(
        _Out_writes_opt_(cnt_sensors) emi_sensor *out_sensors,
        _In_ const std::size_t cnt_sensors,
        _In_z_ const char_type *device,
        _In_z_ const char_type *channel) {
    if (device == nullptr) {
        throw std::invalid_argument("The regular expression selecting the "
            "device must not be null.");
    }
    if (channel == nullptr) {
        throw std::invalid_argument("The regular expression selecting the "
            "channel must not be null.");
    }

#if defined(_WIN32)
    typedef detail::emi_sensor_impl::string_type string_type;
    std::basic_regex<char_type> rxc(channel);
    std::basic_regex<char_type> rxd(device);
    return detail::emi_sensor_impl::create(out_sensors, cnt_sensors,
            [&rxc, &rxd](const string_type& d, const EMI_CHANNEL_V2 *c,
            const std::size_t) {
        return (std::regex_match(d, rxd)
            && std::regex_match(c->ChannelName, rxc));
    });
#else /* defined(_WIN32) */
    return 0;
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::emi_sensor::for_device_and_channel
 */
std::size_t visus::power_overwhelming::emi_sensor::for_device_and_channel(
        _Out_writes_opt_(cnt_sensors) emi_sensor *out_sensors,
        _In_ const std::size_t cnt_sensors,
        _In_z_ const char_type *device,
        _In_ const channel_type channel) {
    if (device == nullptr) {
        throw std::invalid_argument("The regular expression selecting the "
            "device must not be null.");
    }

#if defined(_WIN32)
    typedef detail::emi_sensor_impl::string_type string_type;
    std::basic_regex<char_type> rx(device);
    return detail::emi_sensor_impl::create(out_sensors, cnt_sensors,
            [channel, &rx](const string_type &d, const EMI_CHANNEL_V2 *,
            const std::size_t c) {
        return ((channel == c) && std::regex_match(d, rx));
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
_Ret_maybenull_z_ const wchar_t *visus::power_overwhelming::emi_sensor::name(
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
_Ret_maybenull_z_ const visus::power_overwhelming::emi_sensor::char_type *
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
void visus::power_overwhelming::emi_sensor::sample(
        _In_opt_ const measurement_callback on_measurement,
        _In_ const microseconds_type period,
        _In_opt_ void *context) {
#if defined(_WIN32)
    ::OutputDebugStringW(L"PWROWG DEPRECATION WARNING: This method is only "
        L"provided for backwards compatibility and might be removed in "
        L"future versions of the library. Use async_sampling to configure"
        L"asynchronous sampling.\r\n");
#endif /* defined(_WIN32) */
    this->check_not_disposed();
    this->sample_async(std::move(async_sampling()
        .samples_every(period)
        .delivers_measurements_to(on_measurement)
        .passes_context(context)));
}


#if defined(_WIN32)
/*
 * visus::power_overwhelming::emi_sensor::sample
 */
_Ret_ EMI_MEASUREMENT_DATA_V1 *visus::power_overwhelming::emi_sensor::sample(
        _In_ EMI_MEASUREMENT_DATA_V1& measurement) const {
    this->check_not_disposed();

    if (this->version() != EMI_VERSION_V1) {
        throw std::invalid_argument("The given sensor does not use an EMIv1 "
            "device.");
    }

    detail::emi_sensor_impl::sample(this->_impl->device, &measurement,
        sizeof(measurement));
    return &measurement;
}
#endif /* defined(_WIN32) */


#if defined(_WIN32)
/*
 * visus::power_overwhelming::emi_sensor::sample
 */
_Ret_ EMI_MEASUREMENT_DATA_V2 *visus::power_overwhelming::emi_sensor::sample(
        _Inout_updates_bytes_(size) EMI_MEASUREMENT_DATA_V2 *measurement,
        _In_ const std::size_t size) const {
    this->check_not_disposed();

    if (this->version() != EMI_VERSION_V2) {
        throw std::invalid_argument("The given sensor does not use an EMIv2 "
            "device.");
    }
    if (size < sizeof(EMI_MEASUREMENT_DATA_V2)) {
        throw std::invalid_argument("The output buffer must be able to hold at "
            "least the EMI_MEASUREMENT_DATA_V2 structure.");
    }

    detail::emi_sensor_impl::sample(this->_impl->device, measurement, size);
    return measurement;
}
#endif /* defined(_WIN32) */


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
visus::power_overwhelming::emi_sensor::operator =(_In_ emi_sensor&& rhs) noexcept {
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


/*
 * visus::power_overwhelming::emi_sensor::sample_async
 */
void visus::power_overwhelming::emi_sensor::sample_async(
        _Inout_ async_sampling&& sampling) {
#if defined(_WIN32)
    assert(this->_impl != nullptr);

    if ((this->_impl->async_sampling = std::move(sampling))) {
        auto source = detail::emi_sensor_impl::sampler_source_type::create(
            this->_impl);
        detail::sampler::default += source;

    } else {
        detail::emi_sensor_impl::sampler_source_type::release(this->_impl);
    }

#else /* defined(_WIN32) */
    throw std::logic_error(ERROR_MSG_NOT_SUPPORTED);
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::emi_sensor::sample_sync
 */
visus::power_overwhelming::measurement_data
visus::power_overwhelming::emi_sensor::sample_sync(
        _In_ const timestamp_resolution resolution) const {
#if defined(_WIN32)
    this->check_not_disposed();

    switch (this->version()) {
        case EMI_VERSION_V1: {
            EMI_MEASUREMENT_DATA_V1 s;
            detail::emi_sensor_impl::sample(this->_impl->device, &s, sizeof(s));
            return this->_impl->evaluate(s, resolution);
            }

        case EMI_VERSION_V2: {
            auto m = detail::emi_sensor_impl::sample(this->_impl->device);
            auto s = reinterpret_cast<EMI_MEASUREMENT_DATA_V2 *>(m.data());
            return this->_impl->evaluate(*s, resolution);
            }

        default:
            throw std::logic_error("The specified version of the Energy "
                "Meter Interface is not supported by the implementation.");
    }
#else /* defined(_WIN32) */
    throw std::logic_error(ERROR_MSG_NOT_SUPPORTED);
#endif /* defined(_WIN32) */
}
