// <copyright file="nvml_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE_BEGIN::nvml_sensor::descriptions
 */
template<class TOutput>
void PWROWG_DETAIL_NAMESPACE::nvml_sensor::descriptions(_In_ TOutput oit,
        _In_ const configuration_type& config) {
    auto builder = sensor_description_builder::create()
        .with_vendor(L"NVIDIA")
        .with_type(sensor_type::gpu | sensor_type::power | sensor_type::software)
        .produces(reading_type::floating_point)
        .measured_in(reading_unit::watt);

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

        *oit++ = builder.build();
    } catch (...) { /* Probably no NVIDIA GPU, ignore it.*/ }
}


/*
 * PWROWG_DETAIL_NAMESPACE::nvml_sensor::from_descriptions
 */
template<class TOutput, class TInput>
TInput PWROWG_DETAIL_NAMESPACE::nvml_sensor::from_descriptions(
        _In_ TOutput oit,
        _In_ std::size_t index,
        _In_ const TInput begin,
        _In_ const TInput end) {
    auto retval = move_front_if(begin, end, [](const sensor_description& d) {
        return starts_with(d.name(), L"NVML/");
    });

    for (auto it = begin; it != retval; ++it) {
        *oit++ = std::make_shared<nvml_sensor>(
            *sensor_description_builder::private_data<nvmlDevice_t>(*it),
            index++);
    }

    return retval;
}
