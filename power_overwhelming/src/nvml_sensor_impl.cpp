// <copyright file="nvml_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "nvml_sensor_impl.h"

#include <vector>

#include "power_overwhelming/convert_string.h"

#include "nvidia_management_library.h"
#include "nvml_exception.h"
#include "sampler.h"


/*
 * visus::power_overwhelming::detail::nvml_sensor_impl::~nvml_sensor_impl
 */
visus::power_overwhelming::detail::nvml_sensor_impl::~nvml_sensor_impl(void) {
    // Make sure that a sensor that is being destroyed is removed from all
    // asynchronous sampling threads.
    sampler::default -= this;
}


/*
 * visus::power_overwhelming::detail::nvml_sensor_impl::load_device_name
 */
void visus::power_overwhelming::detail::nvml_sensor_impl::load_device_name(
        void) {
    {
        std::array<char, NVML_DEVICE_NAME_BUFFER_SIZE> name;

        auto status = nvidia_management_library::instance().nvmlDeviceGetName(
            this->device, name.data(), static_cast<unsigned int>(name.size()));
        if (status != NVML_SUCCESS) {
            throw nvml_exception(status);
        }

        this->device_name = power_overwhelming::convert_string<wchar_t>(
            name.data());
    }

    {
        std::array<char, NVML_DEVICE_UUID_BUFFER_SIZE> guid;

        auto status = nvidia_management_library::instance().nvmlDeviceGetUUID(
            this->device, guid.data(), static_cast<unsigned int>(guid.size()));
        if (status != NVML_SUCCESS) {
            throw nvml_exception(status);
        }

        this->device_guid = guid.data();
    }

    {
        nvmlPciInfo_t pciInfo;

        auto status = nvidia_management_library::instance()
            .nvmlDeviceGetPciInfo(this->device, &pciInfo);
        if (status != NVML_SUCCESS) {
            throw nvml_exception(status);
        }

        this->sensor_name = L"NVML/" + this->device_name + L"/"
            + power_overwhelming::convert_string<wchar_t>(pciInfo.busId);
    }
}


/*
 * visus::power_overwhelming::detail::nvml_sensor_impl::sample
 */
visus::power_overwhelming::measurement_data
visus::power_overwhelming::detail::nvml_sensor_impl::sample(
        const timestamp_resolution resolution) const {
    static constexpr auto thousand = static_cast<measurement_data::value_type>(1000);
    const auto timestamp = power_overwhelming::timestamp::now();

    // Get the power usage in milliwatts.
    unsigned int mw = 0;
    auto status = detail::nvidia_management_library::instance()
        .nvmlDeviceGetPowerUsage(this->device, &mw);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    return measurement_data(timestamp,
        static_cast<measurement_data::value_type>(mw) / thousand);
}
