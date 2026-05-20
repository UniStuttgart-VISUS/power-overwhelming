// <copyright file="igcl_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_IGCL)
#include "igcl_sensor.h"

#include <array>
#include <stdexcept>

#include "igcl_error_category.h"
#include "igcl_telemetry.h"


/*
 * PWROWG_DETAIL_NAMESPACE_BEGIN::igcl_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::igcl_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    auto builder = sensor_description_builder::create()
        .with_vendor(L"Intel")
        .with_type(sensor_type::gpu | sensor_type::power | sensor_type::software)
        .produces(reading_type::floating_point)
        .measured_in(reading_unit::watt);

    try {
        std::uint32_t cnt_devices = 0;
        igcl_scope scope;

        // Find out the number of Intel devices on the machine.
        {
            auto status = igcl_library::instance()
                .ctlEnumerateDevices(scope, &cnt_devices, nullptr);
            throw_if_igcl_failed(status);
        }

        // Get handles for all devices.
        std::vector<ctl_device_adapter_handle_t> devices(cnt_devices);
        {
            auto status = igcl_library::instance()
                .ctlEnumerateDevices(scope, &cnt_devices, devices.data());
            throw_if_igcl_failed(status);
        }

        // Create descriptors for each device.
        for (std::size_t i = 0; i < cnt_devices; ++i) {
            ctl_device_adapter_properties_t properties { };
            properties.Size = sizeof(properties);

            {
                auto status = igcl_library::instance()
                    .ctlGetDeviceProperties(devices[i], &properties);
                throw_if_igcl_failed(status);
            }

            builder.with_name("%s (IGCL)", properties.name);
            builder.with_private_data(devices[i]);

            //    builder.with_path(pci_info.busId);
            //    builder.with_id("IGCL/%s", pci_info.busId);

            throw "TODO";

            if ((dst != nullptr) && (i < cnt)) {
                dst[i] = builder.build();
            }
        }

        return cnt_devices;
    } catch (...) {
        // Probably no Intel GPU, ignore it.
        return 0;
    }
    return 0;
}



/*
 * PWROWG_DETAIL_NAMESPACE::igcl_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::igcl_sensor::sample(
        _In_ const sensor_array_callback callback,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context) {
    typedef PWROWG_NAMESPACE::sample sample_type;
    static constexpr auto lut = make_igcl_data_type_list();
    const auto make_sample = make_igcl_telemetry_disps<sample_type&>(
        [](auto value, ctl_units_t units, sample_type& sample) {
            sample = sample_type(0, timestamp::from_time_t(value));
        });
    assert(callback != nullptr);



    // Get the telemetry data from the device.
    ctl_power_telemetry_t telemetry { };
    telemetry.Size = sizeof(telemetry);

    auto status = igcl_library::instance()
        .ctlPowerTelemetryGet(this->_device, &telemetry);
    throw_if_igcl_failed(status);

    sample_type sample;
    auto i = find_igcl_telemetry_disp(lut, telemetry.gpuEnergyCounter);
    make_sample[i](telemetry.timeStamp, sample);

    //PWROWG_NAMESPACE::sample s(this->_index, timestamp::from_time_t(
    //    telemetry.timeStamp.value));
    //visit(telemetry.gpuEnergyCounter,
    //        [&callback, &sensors, &context](auto value, auto units) {
    //    //PWROWG_NAMESPACE::sample s(this->_index, timestamp::from_time_t(
    //    //    telemetry.timeStamp.value), value / thousand);
    //    //callback(&s, 1, sensors, context);
    //});

    throw "TODO";
    //callback(&s, 1, sensors, context);
}

#endif /* defined(POWER_OVERWHELMING_WITH_IGCL) */
