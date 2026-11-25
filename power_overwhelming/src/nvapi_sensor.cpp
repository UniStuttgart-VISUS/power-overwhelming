// <copyright file="nvapi_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_NVAPI)
#include "nvapi_sensor.h"

#include <array>
#include <stdexcept>

#include "nvapi_error_category.h"
#include "nvapi_util.h"
#include "sensor_array_impl.h"
#include "sensor_utilities.h"


/*
 * PWROWG_DETAIL_NAMESPACE_BEGIN::nvapi_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::nvapi_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    auto builder = sensor_description_builder::create()
        .with_vendor(L"NVIDIA")
        .with_class(configuration_type::id)
        .with_type(sensor_type::gpu | sensor_type::power | sensor_type::software)
        .produces(reading_type::floating_point)
        .measured_in(reading_unit::watt);

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
            set_nvapi_identity(builder, gpu_handles[retval], L"NVAPI");

            // Add a friendly name to the sensor.
            throw_if_nvapi_failed(nvapi_library::instance()
                ._nvapi_get_gpu_name(name, gpu_handles[retval]));
            builder.with_name("%s (NVAPI)", name);

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
    NV_GPU_CLIENT_POWER_PERIODIC_CALLBACK_SETTINGS settings { };
    settings.version = NV_GPU_CLIENT_POWER_PERIODIC_CALLBACK_SETTINGS_VER;

    if (enable) {
        const auto interval = get_sampling_interval(*this->_owner);
        settings.callback = &nvapi_sensor::on_sample;
        settings.super.super.pCallbackParam = this;
        settings.super.callbackPeriodms = (std::max)(static_cast<NvU32>(1),
            static_cast<NvU32>(interval.count()));
    }

    throw_if_nvapi_failed(nvapi_library::instance()
        ._nvapi_register_power_callback(this->_handle, &settings));
}


/*
 * PWROWG_DETAIL_NAMESPACE::nvapi_sensor::on_sample
 */
void PWROWG_DETAIL_NAMESPACE::nvapi_sensor::on_sample(
        _In_ NvPhysicalGpuHandle handle,
        _In_ NV_GPU_CLIENT_CALLBACK_POWER_DATA_V1* data) {
    assert(data != nullptr);
    typedef decltype(reading::floating_point) value_type;
    constexpr auto one_watt = static_cast<value_type>(1000);
    auto that = reinterpret_cast<nvapi_sensor *>(data->super.pCallbackParam);

    const auto t = data->timestamp / static_cast<NvU64>(std::micro::den)
        * static_cast<NvU64>(std::micro::num);
    const auto r = data->timestamp % static_cast<NvU64>(std::micro::den)
        * static_cast<NvU64>(std::micro::num);
    const auto timestamp = PWROWG_NAMESPACE::timestamp::from_time_t(t, 0, r);
#if (defined(DEBUG) || defined(_DEBUG))
    PWROWG_TRACE(_T("NVAPI dt: %"PRId64" ms"),std::chrono::duration_cast<
        std::chrono::milliseconds>(timestamp::now() - timestamp).count());
//    const auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(
//        timestamp::now() - timestamp);
//    assert(dt < std::chrono::milliseconds(500));
#endif /* (defined(DEBUG) || defined(_DEBUG)) */

    PWROWG_NAMESPACE::sample sample(
        that->_index,
        timestamp,
        static_cast<value_type>(data->totalGpuPowermw) / one_watt);
    sensor_array_impl::callback(that->_owner)(&sample, 1,
        sensor_array_impl::raw_descriptions(that->_owner),
        sensor_array_impl::count_descriptions(that->_owner),
        sensor_array_impl::context(that->_owner));
}

#endif /* defined(POWER_OVERWHELMING_WITH_NVAPI) */
