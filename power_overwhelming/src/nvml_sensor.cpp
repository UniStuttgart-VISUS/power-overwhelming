﻿// <copyright file="nvml_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/nvml_sensor.h"

#include <stdexcept>

#include "nvidia_management_library.h"
#include "nvml_exception.h"
#include "nvml_sensor_impl.h"


/*
 * visus::power_overwhelming::nvml_sensor::for_all
 */
std::size_t visus::power_overwhelming::nvml_sensor::for_all(
        _Out_writes_opt_(cntSensors) nvml_sensor *outSensors,
        _In_ const std::size_t cntSensors) {
    try {
        unsigned int retval = 0;
        detail::nvml_scope scope;

        {
            auto status = detail::nvidia_management_library::instance()
                .nvmlDeviceGetCount(&retval);
            if (status != NVML_SUCCESS) {
                throw nvml_exception(status);
            }
        }

        for (unsigned int i = 0; (outSensors != nullptr) && (i < retval)
                && (i < cntSensors); ++i) {
            auto& sensor = outSensors[i]._impl;

            auto status = detail::nvidia_management_library::instance()
                .nvmlDeviceGetHandleByIndex(i, &sensor->device);
            if (status != NVML_SUCCESS) {
                throw nvml_exception(status);
            }

            sensor->load_device_name();
        }

        return retval;
    } catch (...) {
        return 0;
    }
}


/*
 * visus::power_overwhelming::nvml_sensor::from_bus_id
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_bus_id(
        _In_z_ const char *pciBusId) {
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
 * visus::power_overwhelming::nvml_sensor::from_bus_id
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_bus_id(
        _In_z_ const wchar_t *pciBusId) {
    auto b = convert_string<char>(pciBusId);
    return from_bus_id(b.c_str());
}


/*
 * visus::power_overwhelming::nvml_sensor::from_guid
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_guid(_In_z_ const char *guid) {
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
 * visus::power_overwhelming::nvml_sensor::from_guid
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_guid(_In_z_ const wchar_t *guid) {
    auto g = convert_string<char>(guid);
    return from_guid(g.c_str());
}


/*
 * visus::power_overwhelming::nvml_sensor::from_index
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_index(
        _In_ const unsigned int index) {
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
        _In_z_ const char *serial) {
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
 * visus::power_overwhelming::nvml_sensor::from_serial
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_serial(
        const _In_z_ wchar_t *serial) {
    auto s = convert_string<char>(serial);
    return from_serial(s.c_str());
}


/*
 * visus::power_overwhelming::nvml_sensor::nvml_sensor
 */
visus::power_overwhelming::nvml_sensor::nvml_sensor(void)
    : _impl(new detail::nvml_sensor_impl()) { }


/*
 * visus::power_overwhelming::nvml_sensor::~nvml_sensor
 */
visus::power_overwhelming::nvml_sensor::~nvml_sensor(void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::nvml_sensor::device_guid
 */
_Ret_maybenull_z_ const char *
visus::power_overwhelming::nvml_sensor::device_guid(void) const noexcept {
    if (this->_impl == nullptr) {
        return nullptr;
    } else {
        return this->_impl->device_guid.c_str();
    }
}


/*
 * visus::power_overwhelming::nvml_sensor::name
 */
_Ret_maybenull_z_ const wchar_t *visus::power_overwhelming::nvml_sensor::name(
        void) const noexcept {
    if (this->_impl == nullptr) {
        return nullptr;
    } else {
        return this->_impl->sensor_name.c_str();
    }
}


/*
 * visus::power_overwhelming::nvml_sensor::sample
 */
visus::power_overwhelming::measurement
visus::power_overwhelming::nvml_sensor::sample(
        _In_ const timestamp_resolution resolution) const {
    this->check_not_disposed();
    return this->_impl->sample(resolution);
}


/*
 * visus::power_overwhelming::nvml_sensor::sample
 */
void visus::power_overwhelming::nvml_sensor::sample(
        _In_opt_ const measurement_callback on_measurement,
        _In_ const microseconds_type period,
        _In_opt_ void *context) {
    typedef decltype(detail::nvml_sensor_impl::sampler)::interval_type
        interval_type;

    this->check_not_disposed();

    if (on_measurement != nullptr) {
        if (!detail::nvml_sensor_impl::sampler.add(this->_impl, on_measurement,
                context, interval_type(period))) {
            throw std::logic_error("Asynchronous sampling cannot be started "
                "while it is already running.");
        }

    } else {
        detail::nvml_sensor_impl::sampler.remove(this->_impl);
    }
}


/*
 * visus::power_overwhelming::nvml_sensor::operator =
 */
visus::power_overwhelming::nvml_sensor&
visus::power_overwhelming::nvml_sensor::operator =(
        _In_ nvml_sensor&& rhs) noexcept {
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
