// <copyright file="nvml_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "nvml_sensor_impl.h"

#include <vector>

#include "convert_string.h"
#include "nvidia_management_library.h"
#include "nvml_exception.h"


/*
 * visus::power_overwhelming::detail::nvml_sensor_impl::load_device_name
 */
void visus::power_overwhelming::detail::nvml_sensor_impl::load_device_name(
        void) {
    std::array<char, NVML_DEVICE_NAME_BUFFER_SIZE> name;
    nvmlPciInfo_t pciInfo;

    {
        auto status = nvidia_management_library::instance().nvmlDeviceGetName(
            this->device, name.data(), static_cast<unsigned int>(name.size()));
        if (status != NVML_SUCCESS) {
            throw nvml_exception(status);
        }
    }

    this->device_name = convert_string(name.data());

    {
        auto status = nvidia_management_library::instance()
            .nvmlDeviceGetPciInfo(this->device, &pciInfo);
        if (status != NVML_SUCCESS) {
            throw nvml_exception(status);
        }
    }

    this->sensor_name = L"NVML/" + this->device_name + L"/"
        + convert_string(pciInfo.busId);
}
