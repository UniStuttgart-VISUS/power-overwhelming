// <copyright file="nvapi_synchronous_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_NVAPI)
#include "nvapi_synchronous_sensor.h"

#include <array>
#include <stdexcept>

#include "nvapi_error_category.h"
#include "nvapi_util.h"
#include "sensor_array_impl.h"
#include "sensor_utilities.h"


/*
 * PWROWG_DETAIL_NAMESPACE_BEGIN::nvapi_synchronous_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::nvapi_synchronous_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    auto builder = sensor_description_builder::create()
        .with_vendor(L"NVIDIA")
        .with_type(sensor_type::gpu | sensor_type::software | sensor_type::throttling)
        .with_class(configuration_type::id)
        .produces(reading_type::unsigned_integer);

    try {
        NvU32 cnt_gpus = 0;
        NvPhysicalGpuHandle gpu_handles[NVAPI_MAX_PHYSICAL_GPUS];
        nvapi_scope nvapi;
        std::size_t retval = 0;

        // Find out the number of NVIDIA devices on the machine.
        throw_if_nvapi_failed(nvapi_library::instance()
            ._nvapi_enumerate_physical_gpus(gpu_handles, &cnt_gpus));

        // Create descriptors for each device.
        for (retval = 0; (retval < cnt_gpus); ++retval) {
            NvAPI_ShortString name;

            // Set the unique hardware identity of the sensor.
            set_nvapi_identity(builder, gpu_handles[retval],
                L"NVAPI/Throttling");

            // Add a friendly name to the sensor.
            throw_if_nvapi_failed(nvapi_library::instance()
                ._nvapi_get_gpu_name(name, gpu_handles[retval]));
            builder.with_name("%s Throttling State (NVAPI)", name);

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
 * PWROWG_DETAIL_NAMESPACE::nvapi_synchronous_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::nvapi_synchronous_sensor::sample(
        _In_ const sensor_array_callback callback,
        _In_reads_(cnt) const sensor_description *sensors,
        _In_ const std::size_t cnt,
        _In_opt_ void *context) {
    NV_GPU_PERF_POLICIES_STATUS_PARAMS params { };
    params.version = NV_GPU_PERF_POLICIES_STATUS_PARAMS_VER;
    throw_if_nvapi_failed(nvapi_library::instance()
        ._nvapi_get_perf_policies_status(this->_handle, &params));

    PWROWG_NAMESPACE::sample samples(this->_index,
        static_cast<std::uint32_t>(params.limitingPoliciesMask));
    callback(&samples, 1, sensors, cnt, context);
}

#endif /* defined(POWER_OVERWHELMING_WITH_NVAPI) */
