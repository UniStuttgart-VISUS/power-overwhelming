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
#include "sensor_description_builder.h"
#include "string_functions.h"


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


#if false
/*
 * visus::power_overwhelming::nvml_sensor::for_all
 */
std::size_t visus::power_overwhelming::nvml_sensor::for_all(
        _Out_writes_opt_(cntSensors) nvml_sensor *outSensors,
        _In_ const std::size_t cntSensors) {
    try {
        unsigned int retval = 0;
        detail::nvml_scope scope;

        {
            auto status = detail::nvidia_management_library::instance()
                .nvmlDeviceGetCount(&retval);
            if (status != NVML_SUCCESS) {
                throw nvml_exception(status);
            }
        }

        for (unsigned int i = 0; (outSensors != nullptr) && (i < retval)
                && (i < cntSensors); ++i) {
            auto& sensor = outSensors[i]._impl;

            auto status = detail::nvidia_management_library::instance()
                .nvmlDeviceGetHandleByIndex(i, &sensor->device);
            if (status != NVML_SUCCESS) {
                throw nvml_exception(status);
            }

            sensor->load_device_name();
        }

        return retval;
    } catch (...) {
        return 0;
    }
}


/*
 * visus::power_overwhelming::nvml_sensor::from_bus_id
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_bus_id(
        _In_z_ const char *pciBusId) {
    nvml_sensor retval;

    auto status = detail::nvidia_management_library::instance()
        .nvmlDeviceGetHandleByPciBusId(pciBusId, &retval._impl->device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    retval._impl->load_device_name();

    return retval;
}


/*
 * visus::power_overwhelming::nvml_sensor::from_bus_id
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_bus_id(
        _In_z_ const wchar_t *pciBusId) {
    auto b = convert_string<char>(pciBusId);
    return from_bus_id(b.c_str());
}


/*
 * visus::power_overwhelming::nvml_sensor::from_guid
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_guid(_In_z_ const char *guid) {
    nvml_sensor retval;

    auto status = detail::nvidia_management_library::instance()
        .nvmlDeviceGetHandleByUUID(guid, &retval._impl->device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    retval._impl->load_device_name();

    return retval;
}


/*
 * visus::power_overwhelming::nvml_sensor::from_guid
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_guid(_In_z_ const wchar_t *guid) {
    auto g = convert_string<char>(guid);
    return from_guid(g.c_str());
}


/*
 * visus::power_overwhelming::nvml_sensor::from_index
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_index(
        _In_ const unsigned int index) {
    nvml_sensor retval;

    auto status = detail::nvidia_management_library::instance()
        .nvmlDeviceGetHandleByIndex(index, &retval._impl->device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    retval._impl->load_device_name();

    return retval;
}


/*
 * visus::power_overwhelming::nvml_sensor::from_serial
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_serial(
        _In_z_ const char *serial) {
    nvml_sensor retval;

    auto status = detail::nvidia_management_library::instance()
        .nvmlDeviceGetHandleBySerial(serial, &retval._impl->device);
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }

    retval._impl->load_device_name();

    return retval;
}


/*
 * visus::power_overwhelming::nvml_sensor::from_serial
 */
visus::power_overwhelming::nvml_sensor
visus::power_overwhelming::nvml_sensor::from_serial(
        const _In_z_ wchar_t *serial) {
    auto s = convert_string<char>(serial);
    return from_serial(s.c_str());
}



/*
 * visus::power_overwhelming::nvml_sensor::nvml_sensor
 */
visus::power_overwhelming::nvml_sensor::nvml_sensor(void)
    : _impl(new detail::nvml_sensor_impl()) { }


/*
 * visus::power_overwhelming::nvml_sensor::~nvml_sensor
 */
visus::power_overwhelming::nvml_sensor::~nvml_sensor(void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::nvml_sensor::device_guid
 */
_Ret_maybenull_z_ const char *
visus::power_overwhelming::nvml_sensor::device_guid(void) const noexcept {
    if (this->_impl == nullptr) {
        return nullptr;
    } else {
        return this->_impl->device_guid.c_str();
    }
}


/*
 * visus::power_overwhelming::nvml_sensor::name
 */
_Ret_maybenull_z_ const wchar_t *visus::power_overwhelming::nvml_sensor::name(
        void) const noexcept {
    if (this->_impl == nullptr) {
        return nullptr;
    } else {
        return this->_impl->sensor_name.c_str();
    }
}


/*
 * visus::power_overwhelming::nvml_sensor::sample
 */
void visus::power_overwhelming::nvml_sensor::sample(
        _In_opt_ const measurement_callback on_measurement,
        _In_ const microseconds_type period,
        _In_opt_ void *context) {
#if defined(_WIN32)
    ::OutputDebugStringW(L"PWROWG DEPRECATION WARNING: This method is only "
        L"provided for backwards compatibility and might be removed in "
        L"future versions of the library. Use async_sampling to configure "
        L"asynchronous sampling.\r\n");
#endif /* defined(_WIN32) */
    this->check_not_disposed();
    this->sample_async(std::move(async_sampling()
        .samples_every(period)
        .delivers_measurements_to(on_measurement)
        .passes_context(context)));
}


/*
 * visus::power_overwhelming::nvml_sensor::operator =
 */
visus::power_overwhelming::nvml_sensor&
visus::power_overwhelming::nvml_sensor::operator =(
        _In_ nvml_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        delete this->_impl;
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::nvml_sensor::operator bool
 */
visus::power_overwhelming::nvml_sensor::operator bool(void) const noexcept {
    return (this->_impl != nullptr);
}


/*
 * visus::power_overwhelming::nvml_sensor::sample_async
 */
void visus::power_overwhelming::nvml_sensor::sample_async(
        _Inout_ async_sampling&& sampling) {
    assert(this->_impl != nullptr);
    this->_impl->async_sampling = std::move(sampling);

    if (this->_impl->async_sampling) {
        detail::sampler::default_sampler += this->_impl;
    } else {
        detail::sampler::default_sampler -= this->_impl;
    }
}



/*
 * visus::power_overwhelming::nvml_sensor::sample_sync
 */
visus::power_overwhelming::measurement_data
visus::power_overwhelming::nvml_sensor::sample_sync(void) const {
    assert(this->_impl != nullptr);
    return this->_impl->sample();
}
#endif
