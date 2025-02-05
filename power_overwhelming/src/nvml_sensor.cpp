// <copyright file="nvml_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "nvml_sensor.h"

#include <array>
#include <cassert>
#include <stdexcept>


/*
 * PWROWG_DETAIL_NAMESPACE::nvml_sensor::from_bus_id
 */
std::shared_ptr<PWROWG_DETAIL_NAMESPACE::nvml_sensor>
PWROWG_DETAIL_NAMESPACE::nvml_sensor::from_bus_id(
        _In_z_ const char *pciBusId,
        _In_ const std::size_t index) {
    nvmlDevice_t device;

    auto status = nvidia_management_library::instance()
        .nvmlDeviceGetHandleByPciBusId(pciBusId, &device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    return std::make_shared<nvml_sensor>(device, index);
}


/*
 * PWROWG_DETAIL_NAMESPACE::nvml_sensor::from_guid
 */
std::shared_ptr<PWROWG_DETAIL_NAMESPACE::nvml_sensor>
PWROWG_DETAIL_NAMESPACE::nvml_sensor::from_guid(_In_z_ const char *guid,
        _In_ const std::size_t index) {
    nvmlDevice_t device;

    auto status = nvidia_management_library::instance()
        .nvmlDeviceGetHandleByUUID(guid, &device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    return std::make_shared<nvml_sensor>(device, index);
}


/*
 * PWROWG_DETAIL_NAMESPACE::nvml_sensor::from_index
 */
std::shared_ptr<PWROWG_DETAIL_NAMESPACE::nvml_sensor>
PWROWG_DETAIL_NAMESPACE::nvml_sensor::from_index(
        _In_ const unsigned int idx,
        _In_ const std::size_t index) {
    nvmlDevice_t device;

    auto status = nvidia_management_library::instance()
        .nvmlDeviceGetHandleByIndex(idx, &device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    return std::make_shared<nvml_sensor>(device, index);
}


/*
 * PWROWG_DETAIL_NAMESPACE::nvml_sensor::from_serial
 */
std::shared_ptr<PWROWG_DETAIL_NAMESPACE::nvml_sensor>
PWROWG_DETAIL_NAMESPACE::nvml_sensor::from_serial(
        _In_z_ const char *serial,
        _In_ const std::size_t index) {
    nvmlDevice_t device;

    auto status = nvidia_management_library::instance()
        .nvmlDeviceGetHandleBySerial(serial, &device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    return std::make_shared<nvml_sensor>(device, index);
}


/*
 * PWROWG_DETAIL_NAMESPACE::nvml_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::nvml_sensor::sample(
        _In_ const sensor_array_callback callback,
        _In_opt_ void *context) {
    typedef decltype(reading::floating_point) value_type;
    static constexpr auto thousand = static_cast<value_type>(1000);
    assert(callback != nullptr);

    // Create the sample with the current timestamp.
    PWROWG_NAMESPACE::sample s;

    // Get the power usage in milliwatts.
    unsigned int mw = 0;
    auto status = nvidia_management_library::instance()
        .nvmlDeviceGetPowerUsage(this->_device, &mw);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    // Convert to Watts.
    s.reading.floating_point = static_cast<value_type>(mw) / thousand;

    callback(this->_index, &s, 1, context);
}
