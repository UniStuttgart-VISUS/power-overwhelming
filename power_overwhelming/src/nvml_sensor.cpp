// <copyright file="nvml_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "nvml_sensor.h"

#include <array>
#include <cassert>
#include <stdexcept>

#include "visus/pwrowg/sample.h"

#include "nvidia_management_library.h"
#include "nvml_exception.h"


/*
 * PWROWG_DETAIL_NAMESPACE_BEGIN::nvml_sensor::descriptions
 */
std::vector<PWROWG_NAMESPACE::sensor_description>
PWROWG_DETAIL_NAMESPACE::nvml_sensor::descriptions(
        _In_ configuration_type& config) {
    auto builder = sensor_description_builder::create()
        .with_vendor(L"NVIDIA")
        .with_type(sensor_type::gpu | sensor_type::power | sensor_type::software)
        .produces(reading_type::floating_point)
        .measured_in(reading_unit::watt);
    std::vector<sensor_description> retval;

    try {
        unsigned int cnt_devices = 0;
        nvml_scope scope;

        // Find out the number of NVIDIA devices on the machine.
        {
            auto status = nvidia_management_library::instance()
                .nvmlDeviceGetCount(&cnt_devices);
            if (status != NVML_SUCCESS) {
                throw nvml_exception(status);
            }
        }

        // Create descriptors for each device.
        for (unsigned int i = 0; (i < cnt_devices); ++i) {
            nvmlDevice_t device;
            std::array<char, NVML_DEVICE_UUID_BUFFER_SIZE> guid;
            std::array<char, NVML_DEVICE_NAME_BUFFER_SIZE> name;
            nvmlPciInfo_t pci_info;

            {
                auto status = nvidia_management_library::instance()
                    .nvmlDeviceGetHandleByIndex(i, &device);
                if (status != NVML_SUCCESS) {
                    throw nvml_exception(status);
                }

                builder.with_private_data(device);
            }

            {
                auto status = nvidia_management_library::instance()
                    .nvmlDeviceGetName(device, name.data(),
                        static_cast<unsigned int>(name.size()));
                if (status != NVML_SUCCESS) {
                    throw nvml_exception(status);
                }
            }

            {
                auto status = nvidia_management_library::instance()
                    .nvmlDeviceGetUUID(device, guid.data(),
                        static_cast<unsigned int>(guid.size()));
                if (status != NVML_SUCCESS) {
                    throw nvml_exception(status);
                }

                builder.with_id(guid.data());
            }

            {
                auto status = nvidia_management_library::instance()
                    .nvmlDeviceGetPciInfo(device, &pci_info);
                if (status != NVML_SUCCESS) {
                    throw nvml_exception(status);
                }

                builder.with_path(pci_info.busId);
            }

            builder.with_name("NVML/%s/%s", name.data(), pci_info.busId);
        }

        retval.push_back(builder.build());
    } catch (...) { /* Probably no NVIDIA GPU, ignore it.*/ }

    return retval;
}


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
 * PWROWG_DETAIL_NAMESPACE::nvml_sensor
 */
PWROWG_DETAIL_NAMESPACE::nvml_sensor::nvml_sensor(
        _In_ const nvmlDevice_t device,
        _In_ const std::size_t index) 
        : sensor(index), _device(device) {
    //if (!starts_with(desc.name(), L"NVML/")) {
    //    throw std::invalid_argument("An NVML sensor can only be created from "
    //        "the description of an NVML sensor.");
    //}

    //this->_device = *sensor_description_builder::private_data< nvmlDevice_t>(
    //    desc);
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
