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
        emi_sensor *out_sensors, std::size_t cnt_sensors) {
    std::size_t retval = 0;

#if defined(_WIN32)
    if (out_sensors == nullptr) {
        cnt_sensors = 0;
    }

    detail::enumerate_device_interface(::GUID_DEVICE_ENERGY_METER,
            [out_sensors, &retval, cnt_sensors](HDEVINFO h,
            SP_DEVICE_INTERFACE_DATA& d) {
        auto path = detail::get_device_path(h, d);
        auto dev = std::make_shared<detail::emi_device>(path);

        switch (dev->version().EmiVersion) {
            case EMI_VERSION_V1:
                if (retval < cnt_sensors) {
                    out_sensors[retval]._impl->set(dev, path, 0);
                }
                ++retval;
                break;

            case EMI_VERSION_V2: {
                const auto md = dev->metadata_as<EMI_METADATA_V2>();
                const auto cnt = md->ChannelCount;
                for (auto i = 0; i < cnt; ++i, ++retval) {
                    if (retval < cnt_sensors) {
                        out_sensors[retval]._impl->set(dev, path, i);
                    }
                }
                } break;
        }

        return true;
    });
#endif /* defined(_WIN32) */

    return retval;
}


#if 0
/*
 * visus::power_overwhelming::emi_sensor::from_bus_id
 */
visus::power_overwhelming::emi_sensor
visus::power_overwhelming::emi_sensor::from_bus_id(
        const char *pciBusId) {
    emi_sensor retval;

    auto status = detail::nvidia_management_library::instance()
        .nvmlDeviceGetHandleByPciBusId(pciBusId, &retval._impl->device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    retval._impl->load_device_name();

    return retval;
}


/*
 * visus::power_overwhelming::emi_sensor::from_guid
 */
visus::power_overwhelming::emi_sensor
visus::power_overwhelming::emi_sensor::from_guid(
        const char *guid) {
    emi_sensor retval;

    auto status = detail::nvidia_management_library::instance()
        .nvmlDeviceGetHandleByUUID(guid, &retval._impl->device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    retval._impl->load_device_name();

    return retval;
}


/*
 * visus::power_overwhelming::emi_sensor::from_index
 */
visus::power_overwhelming::emi_sensor
visus::power_overwhelming::emi_sensor::from_index(
        const unsigned int index) {
    emi_sensor retval;

    auto status = detail::nvidia_management_library::instance()
        .nvmlDeviceGetHandleByIndex(index, &retval._impl->device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    retval._impl->load_device_name();

    return retval;
}


/*
 * visus::power_overwhelming::emi_sensor::from_serial
 */
visus::power_overwhelming::emi_sensor
visus::power_overwhelming::emi_sensor::from_serial(
        const char *serial) {
    emi_sensor retval;

    auto status = detail::nvidia_management_library::instance()
        .nvmlDeviceGetHandleBySerial(serial, &retval._impl->device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    retval._impl->load_device_name();

    return retval;
}
#endif


/*
 * visus::power_overwhelming::emi_sensor::emi_sensor
 */
visus::power_overwhelming::emi_sensor::emi_sensor(void)
    : _impl(new detail::emi_sensor_impl()) { }


/*
 * visus::power_overwhelming::emi_sensor::~emi_sensor
 */
visus::power_overwhelming::emi_sensor::~emi_sensor(void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::emi_sensor::channel
 */
decltype(EMI_METADATA_V2::ChannelCount)
visus::power_overwhelming::emi_sensor::channel(void) const {
    return (*this)
        ? this->_impl->channel
        : static_cast<decltype(this->channel())>(0);
}


/*
 * visus::power_overwhelming::emi_sensor::channels
 */
decltype(EMI_METADATA_V2::ChannelCount)
visus::power_overwhelming::emi_sensor::channels(void) const {
    return (*this)
        ? this->_impl->device->channels()
        : static_cast<decltype(this->channels())>(0);
}


/*
 * visus::power_overwhelming::emi_sensor::name
 */
const wchar_t *visus::power_overwhelming::emi_sensor::name(
        void) const noexcept {
    return (this->_impl != nullptr)
        ? this->_impl->sensor_name.c_str()
        : nullptr;
}


/*
 * visus::power_overwhelming::emi_sensor::sample
 */
visus::power_overwhelming::measurement
visus::power_overwhelming::emi_sensor::sample(
        const timestamp_resolution resolution) const {
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
}


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
decltype(EMI_VERSION::EmiVersion)
visus::power_overwhelming::emi_sensor::version(void) const noexcept {
    return (*this)
        ? this->_impl->device->version().EmiVersion
        : static_cast<decltype(EMI_VERSION::EmiVersion)>(0);
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
    return ((this->_impl != nullptr) && (this->_impl->device != nullptr));
}
