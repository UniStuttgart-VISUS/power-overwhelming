// <copyright file="emi_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/emi_sensor.h"

#include <stdexcept>
#include <system_error>

#include "emi_sensor_impl.h"


/*
 * visus::power_overwhelming::emi_sensor::for_all
 */
std::size_t visus::power_overwhelming::emi_sensor::for_all(
        emi_sensor *out_sensors, const std::size_t cnt_sensors) {
    auto hDev = SetupDiGetClassDevs(&::GUID_DEVICE_ENERGY_METER, nullptr, NULL,
        DIGCF_DEVICEINTERFACE);
    if (hDev == INVALID_HANDLE_VALUE) {
        return 0;
    }

    SP_DEVICE_INTERFACE_DATA data;
    ::ZeroMemory(&data, sizeof(data));
    data.cbSize = sizeof(data);

    for (DWORD i = 0;  ::SetupDiEnumDeviceInterfaces(hDev, nullptr,
            &::GUID_DEVICE_ENERGY_METER, i, &data); ++i) {
        auto x = i;
    }

    auto status = ::GetLastError();

    return 0;
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
 * visus::power_overwhelming::emi_sensor::sample
 */
visus::power_overwhelming::measurement
visus::power_overwhelming::emi_sensor::sample(
        const timestamp_resolution resolution) const {
    this->check_not_disposed();
    return this->_impl->sample(resolution);
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
    return (this->_impl != nullptr);
}
