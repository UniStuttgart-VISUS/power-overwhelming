// <copyright file="nvapi_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_NVAPI)
#include "nvapi_sensor.h"

#include <array>
#include <stdexcept>

#include "nvapi_error_category.h"


/*
 * PWROWG_DETAIL_NAMESPACE_BEGIN::nvapi_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::nvapi_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    auto builder = sensor_description_builder::create()
        .with_vendor(L"NVIDIA")
        .with_type(sensor_type::gpu | sensor_type::power | sensor_type::software)
        .produces(reading_type::floating_point)
        .measured_in(reading_unit::watt);

    try {
        NvU32 cnt_gpus = 0;
        NvPhysicalGpuHandle gpu_handles[NVAPI_MAX_PHYSICAL_GPUS];
        nvapi_scope nvapi;
        unsigned int retval = 0;

        // Find out the number of NVIDIA devices on the machine.
        {
            auto status = nvapi_library::instance()
                .NvAPI_EnumPhysicalGPUs(gpu_handles, &cnt_gpus);
            throw_if_nvapi_failed(status);
        }

        // Create descriptors for each device.
        for (retval = 0; (retval < cnt_gpus); ++retval) {
            NvU32 gpu_id;
            NvAPI_ShortString name;

            // Pass on the handle to the sensor.
            builder.with_private_data(gpu_handles[retval]);

            // Get some info about the GPU to create a unique ID.
            {
                auto status = nvapi_library::instance()
                    .NvAPI_GetGPUIDfromPhysicalGPU(
                        gpu_handles[retval],
                        &gpu_id);
                throw_if_nvapi_failed(status);

                builder.with_path(L"0x%u", gpu_id);
                builder.with_id(L"NVAPI/0x%u", gpu_id);
            }

            {
                auto status = nvapi_library::instance()
                    .NvAPI_GPU_GetFullName(gpu_handles[retval], name);
                throw_if_nvapi_failed(status);

                builder.with_name("%s (NVAPI)", name);
            }

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
 * PWROWG_DETAIL_NAMESPACE::nvapi_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::nvapi_sensor::sample(_In_ const bool enable) {

}
#endif /* defined(POWER_OVERWHELMING_WITH_NVAPI) */
