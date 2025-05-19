// <copyright file="nvml_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_NVML)
#include "nvml_sensor.h"

#include <array>
#include <stdexcept>

#include "nvml_error_category.h"


/*
 * PWROWG_DETAIL_NAMESPACE_BEGIN::nvml_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::nvml_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    auto builder = sensor_description_builder::create()
        .with_vendor(L"NVIDIA")
        .with_type(sensor_type::gpu | sensor_type::power | sensor_type::software)
        .produces(reading_type::floating_point)
        .measured_in(reading_unit::watt);

    try {
        unsigned int cnt_devices = 0;
        unsigned int retval = 0;
        nvml_scope scope;

        // Find out the number of NVIDIA devices on the machine.
        {
            auto status = nvidia_management_library::instance()
                .nvmlDeviceGetCount(&cnt_devices);
            throw_if_nvml_failed(status);
        }

        // Create descriptors for each device.
        for (retval = 0; (retval < cnt_devices); ++retval) {
            nvmlDevice_t device;
            std::array<char, NVML_DEVICE_UUID_BUFFER_SIZE> guid;
            std::array<char, NVML_DEVICE_NAME_BUFFER_SIZE> name;
            nvmlPciInfo_t pci_info;

            {
                auto status = nvidia_management_library::instance()
                    .nvmlDeviceGetHandleByIndex(retval, &device);
                throw_if_nvml_failed(status);

                builder.with_private_data(device);
            }

            {
                auto status = nvidia_management_library::instance()
                    .nvmlDeviceGetName(device, name.data(),
                        static_cast<unsigned int>(name.size()));
                throw_if_nvml_failed(status);
            }

            //{
            //    auto status = nvidia_management_library::instance()
            //        .nvmlDeviceGetUUID(device, guid.data(),
            //            static_cast<unsigned int>(guid.size()));
            //    if (status != NVML_SUCCESS) {
            //        throw nvml_exception(status);
            //    }
            //}

            {
                auto status = nvidia_management_library::instance()
                    .nvmlDeviceGetPciInfo(device, &pci_info);
                throw_if_nvml_failed(status);

                builder.with_path(pci_info.busId);
                builder.with_id("NVML/%s", pci_info.busId);
            }

            builder.with_name("%s (NVML)", name.data());

            if ((dst != nullptr) && (retval < cnt)) {
                dst[retval] = builder.build();
            }
        }

        return retval;
    } catch (...) {
        // Probably no NVIDIA GPU, ignore it.
        return 0;
    }
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
    throw_if_nvml_failed(status);

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
    throw_if_nvml_failed(status);

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
    throw_if_nvml_failed(status);

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
    throw_if_nvml_failed(status);

    return std::make_shared<nvml_sensor>(device, index);
}


/*
 * PWROWG_DETAIL_NAMESPACE::nvml_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::nvml_sensor::sample(
        _In_ const sensor_array_callback callback,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context) {
    typedef decltype(reading::floating_point) value_type;
    static constexpr auto thousand = static_cast<value_type>(1000);
    assert(callback != nullptr);

    // Create the sample with the current timestamp.
    PWROWG_NAMESPACE::sample s(this->_index);

    // Get the power usage in milliwatts.
    unsigned int mw = 0;
    auto status = nvidia_management_library::instance()
        .nvmlDeviceGetPowerUsage(this->_device, &mw);
    throw_if_nvml_failed(status);

    // Convert to Watts.
    s.reading.floating_point = static_cast<value_type>(mw) / thousand;

    callback(&s, 1, sensors, context);
}

#endif /* defined(POWER_OVERWHELMING_WITH_NVML) */
