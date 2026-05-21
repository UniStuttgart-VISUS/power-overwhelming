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
#include "fnv1a.h"


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
        // Get handles for all devices.
        igcl_scope scope;
        auto devices = igcl_sensor::devices(scope);

        // Create descriptors for each device.
        for (std::size_t i = 0; i < devices.size(); ++i) {
            ctl_device_adapter_properties_t dev_props { };
            dev_props.Size = sizeof(dev_props);
            dev_props.Version = 2;
            //ctl_pci_properties_t pci_props { };
            //pci_props.Size = sizeof(pci_props);
            ctl_power_telemetry_t telemetry { };
            telemetry.Size = sizeof(telemetry);
            telemetry.Version = 1;

            throw_if_igcl_failed(igcl_library::instance()
                .ctlGetDeviceProperties(devices[i], &dev_props));
            //throw_if_igcl_failed(igcl_library::instance()
            //    .ctlPciGetProperties(devices[i], &pci_props));

            throw_if_igcl_failed(igcl_library::instance()
                .ctlPowerTelemetryGet(devices[i], &telemetry));

            builder.with_name("%s (IGCL)", dev_props.name);
            builder.with_private_data(hash(dev_props));

            const auto path = igcl_sensor::path(dev_props);
            builder.with_path(path);
            builder.with_id(L"IGCL/%s", path.c_str());

            if ((dst != nullptr) && (i < cnt)) {
                dst[i] = builder.build();
            }
        }

        return devices.size();
    } catch (...) {
        // Probably no Intel GPU, ignore it.
        return 0;
    }
    return 0;
}


/*
 * PWROWG_DETAIL_NAMESPACE::igcl_sensor::igcl_sensor
 */
PWROWG_DETAIL_NAMESPACE::igcl_sensor::igcl_sensor(
        _In_ const std::wstring& path,
        _In_ const std::size_t index)
        : _device(nullptr), _index(index), _offset(0) {
    // Search for the adapter that produces the specified hash for its
    // properties. The reason for this implementation is that the device handle
    // is tied to the igcl_scope taht was used to enumerate it. As each sensor
    // has its own scope, we need to re-open the devices here.
    const auto devices = igcl_sensor::devices(this->_scope);
    for (auto& d : devices) {
        ctl_device_adapter_properties_t dev_props { };
        dev_props.Size = sizeof(dev_props);
        dev_props.Version = 2;
        throw_if_igcl_failed(igcl_library::instance()
            .ctlGetDeviceProperties(d, &dev_props));
        const auto p = igcl_sensor::path(dev_props);
        if (path == p) {
            this->_device = d;
            break;
        }
    }

    // Create a dispatcher for delivering a sample from telemetry data.
    this->_deliver_sample = make_igcl_telemetry_disps<timestamp, std::size_t,
            const sensor_array_callback, const sensor_description *, void *>(
        [](auto value, const ctl_units_t, timestamp timestamp,
                const std::size_t index, const sensor_array_callback callback,
                const sensor_description *sensors, void *context) {
            PWROWG_NAMESPACE::sample s(index, timestamp);
            callback(&s, 1, sensors, context);
        });

    // Create a dispatcher for generating a timestamp from a sample.
    this->_make_timestamp = make_igcl_telemetry_disps<timestamp&>(
        [this](auto value, const ctl_units_t, timestamp& retval) {
            assert(std::is_floating_point_v<std::decay_t<decltype(value)>>);
            retval = this->make_timestamp(value);
        });
}



/*
 * PWROWG_DETAIL_NAMESPACE::igcl_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::igcl_sensor::sample(
        _In_ const sensor_array_callback callback,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context) {
    // Get the telemetry data from the device.
    ctl_power_telemetry_t telemetry { };
    telemetry.Size = sizeof(telemetry);
    telemetry.Version = 1;

    {
        auto status = igcl_library::instance()
            .ctlPowerTelemetryGet(this->_device, &telemetry);
        throw_if_igcl_failed(status);
    }

    // Convert the timestamp of the sample.
    timestamp timestamp;
    find_igcl_telemetry_disp(this->_make_timestamp, telemetry.timeStamp)(
        telemetry.timeStamp, timestamp);

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


/*
 * PWROWG_DETAIL_NAMESPACE::igcl_sensor::devices
 */
std::vector<ctl_device_adapter_handle_t>
PWROWG_DETAIL_NAMESPACE::igcl_sensor::devices(_In_ igcl_scope& scope) {
    std::uint32_t cnt = 0;
    throw_if_igcl_failed(igcl_library::instance()
        .ctlEnumerateDevices(scope, &cnt, nullptr));

    std::vector<ctl_device_adapter_handle_t> retval(cnt);
    throw_if_igcl_failed(igcl_library::instance()
        .ctlEnumerateDevices(scope, &cnt, retval.data()));

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::igcl_sensor::hash
 */
std::uint64_t PWROWG_DETAIL_NAMESPACE::igcl_sensor::hash(
        _In_ const ctl_device_adapter_properties_t& p) {
    fnv1a<std::uint64_t> retval;
    retval(reinterpret_cast<const std::uint8_t *>(&p),
        reinterpret_cast<const std::uint8_t*>(&p.reserved));
    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::igcl_sensor::path
 */
std::wstring PWROWG_DETAIL_NAMESPACE::igcl_sensor::path(
        _In_ const ctl_device_adapter_properties_t& p) {
    if ((p.adapter_bdf.bus == 0)
            && (p.adapter_bdf.device == 0)
            && (p.adapter_bdf.function == 0)) {
        // IGCL is too old, we cannot use the PCI location. We generate a hash
        // which hopefully uniquely identifies the GPU.
        return std::to_wstring(hash(p));

    } else {
        return std::to_wstring(p.adapter_bdf.bus) + L":"
            + std::to_wstring(p.adapter_bdf.device) + L"."
            + std::to_wstring(p.adapter_bdf.function);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::igcl_sensor::time_sync
 */
void PWROWG_DETAIL_NAMESPACE::igcl_sensor::time_sync(
        _In_ std::size_t samples) {
    using namespace std::chrono;

    const auto sample = [](void) {
        const auto s = timestamp::now();
#if (_WIN32_WINNT >= 0x0600)
        const auto t = std::chrono::milliseconds(::GetTickCount64());
#else /* (_WIN32_WINNT >= 0x0600) */
        const auto t = std::chrono::milliseconds(::GetTickCount());
#endif /* (_WIN32_WINNT >= 0x0600) */
        return std::make_pair(s, t);
    };

    if (samples < 1) {
        samples = 1;
    }

    this->_offset = std::chrono::duration<double>(0);
    for (std::size_t i = 0; i < samples; ++i) {
        const auto s = sample();
        const auto d = (s.first - timestamp::from_duration(s.second));
        this->_offset += (d - this->_offset) / (i + 1.0);
    }
}

#endif /* defined(POWER_OVERWHELMING_WITH_IGCL) */
