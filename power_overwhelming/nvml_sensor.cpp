// <copyright file="nvml_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "nvml_sensor.h"

#include <stdexcept>

#include "nvidia_management_library.h"
#include "nvml_exception.h"
#include "nvml_sensor_impl.h"

#if 0
/*
 * visus::power_overwhelming::nvml_sensor::for_all
 */
template<class TMeasurement>
std::vector<visus::power_overwhelming::nvml_sensor>
visus::power_overwhelming::nvml_sensor::for_all(void) {
    unsigned int cnt = 0;
    nvml_scope scope;

    {
        auto status = ::nvmlDeviceGetCount(&cnt);
        if (status != NVML_SUCCESS) {
            throw nvml_exception(status);
        }
    }

    std::vector<nvml_sensor> retval;
    retval.resize(cnt);

    for (unsigned int i = 0; i < cnt; ++i) {
        auto status = ::nvmlDeviceGetHandleByIndex(i, &retval[i]._device);
        if (status != NVML_SUCCESS) {
            throw nvml_exception(status);
        }
    }

    return retval;
}
#endif


/*
 * visus::power_overwhelming::nvml_sensor::from_bus_id
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_bus_id(
        const char *pciBusId) {
    nvml_sensor retval;

    auto status = detail::nvidia_management_library::instance()
        .nvmlDeviceGetHandleByPciBusId(pciBusId, &retval._impl->device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    retval._impl->load_device_name();

    return retval;
}


/*
 * visus::power_overwhelming::nvml_sensor::from_guid
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_guid(
        const char *guid) {
    nvml_sensor retval;

    auto status = detail::nvidia_management_library::instance()
        .nvmlDeviceGetHandleByUUID(guid, &retval._impl->device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    retval._impl->load_device_name();

    return retval;
}


/*
 * visus::power_overwhelming::nvml_sensor::from_index
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_index(
        const unsigned int index) {
    nvml_sensor retval;

    auto status = detail::nvidia_management_library::instance()
        .nvmlDeviceGetHandleByIndex(index, &retval._impl->device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    retval._impl->load_device_name();

    return retval;
}


/*
 * visus::power_overwhelming::nvml_sensor::from_serial
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_serial(
        const char *serial) {
    nvml_sensor retval;

    auto status = detail::nvidia_management_library::instance()
        .nvmlDeviceGetHandleBySerial(serial, &retval._impl->device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    retval._impl->load_device_name();

    return retval;
}

/*
 * visus::power_overwhelming::nvml_sensor::nvml_sensor
 */
visus::power_overwhelming::nvml_sensor::nvml_sensor(void) noexcept
    : _impl(new detail::nvml_sensor_impl()) { }


/*
 * visus::power_overwhelming::nvml_sensor::~nvml_sensor
 */
visus::power_overwhelming::nvml_sensor::~nvml_sensor(void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::nvml_sensor::operator =
 */
visus::power_overwhelming::nvml_sensor&
visus::power_overwhelming::nvml_sensor::operator =(nvml_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::nvml_sensor::operator bool
 */
visus::power_overwhelming::nvml_sensor::operator bool(void) const noexcept {
    return (this->_impl != nullptr);
}



/*
 * ::power_overwhelming::nvml_sensor::sample
 */
visus::power_overwhelming::measurement
visus::power_overwhelming::nvml_sensor::sample(
        const measurement::timestamp_type timestamp) const {
    if (!*this) {
        throw std::runtime_error("A disposed instance of nvml_sensor cannot be "
            "sampled.");
    }

    // Get the power usage in milliwatts.
    unsigned int mw = 0;
    auto status = detail::nvidia_management_library::instance()
        .nvmlDeviceGetPowerUsage(this->_impl->device, &mw);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    return measurement(this->_impl->sensor_name.c_str(), timestamp,
        static_cast<measurement::value_type>(mw)
        / static_cast<measurement::value_type>(1000));
}
