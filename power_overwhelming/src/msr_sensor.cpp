﻿// <copyright file="msr_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/msr_sensor.h"

#include <cassert>

#include "power_overwhelming/for_each_rapl_domain.h"

#include "msr_magic.h"
#include "msr_sensor_impl.h"
#include "sampler.h"


/*
 * visus::power_overwhelming::msr_sensor::force_create
 */
visus::power_overwhelming::msr_sensor
visus::power_overwhelming::msr_sensor::force_create(
        _In_ const core_type core,
        _In_ const rapl_domain domain,
        _In_ const std::streamoff data_location,
        _In_ const std::streamoff unit_location,
        _In_ const std::uint64_t unit_mask,
        _In_ const std::uint32_t unit_offset) {
    static const std::function<bool(const core_type)> because_i_know
        = [](const core_type) { return true; };
    detail::msr_magic_config config;
    msr_sensor retval;

    config.data_location = data_location;
    config.is_supported = because_i_know;
    config.unit_location = unit_location;
    config.unit_mask = unit_mask;
    config.unit_offset = unit_offset;

    assert(retval._impl != nullptr);
    retval._impl->set(core, domain, &config);
    return retval;
}


/*
 * visus::power_overwhelming::msr_sensor::for_all
 */
std::size_t visus::power_overwhelming::msr_sensor::for_all(
        _Out_writes_opt_(cnt_sensors) msr_sensor *out_sensors,
        _In_ const std::size_t cnt_sensors,
        _In_ const bool consider_topology) {
    std::size_t retval = 0;
    bool succeeded = true;

    for (core_type c = 0; succeeded; ++c) {
        try {
            // Test-create the device file to find out whether the core exists.
            auto dev = detail::msr_device_factory::create(c);
            if (dev == nullptr) {
                throw std::logic_error("An invalid MSR device was created by "
                    "the msr_device_factory, which should never happen.");
            }

            // Now that we know that the core exists, try creating sensors for
            // all RAPL domains.
            for_each_rapl_domain([&](const rapl_domain domain) {
                try {
                    msr_sensor sensor;
                    assert(sensor._impl != nullptr);
                    sensor._impl->set(c, domain, nullptr);

                    if (retval < cnt_sensors) {
                        out_sensors[retval] = std::move(sensor);
                    }

                    ++retval;
                } catch (...) {
                    // Not being able to create a sensor for a specific RAPL
                    // domain does not constitute a fatall error. The RAPL
                    // domain just might not be supported for the CPU, so we
                    // continue enumerating in this case.
                }

                return true;
            });

        } catch (std::system_error) {
            // If creating a device for core 'c' causes an std::system_error, we
            // have reached the last core and leave the loop. Papa Schlumpf
            // would not approve this use of exceptions for control flow, but it
            // is the simplest way to implement this without duplicating code.
            succeeded = false;
        }
    }

    return retval;
}


/*
 * visus::power_overwhelming::msr_sensor::for_core
 */
visus::power_overwhelming::msr_sensor
visus::power_overwhelming::msr_sensor::for_core(_In_ const core_type core,
        _In_ const rapl_domain domain) {
    msr_sensor retval;
    assert(retval._impl != nullptr);
    retval._impl->set(core, domain, nullptr);
    return retval;
}


/*
 * visus::power_overwhelming::msr_sensor::msr_sensor
 */
visus::power_overwhelming::msr_sensor::msr_sensor(void)
    : _impl(new detail::msr_sensor_impl()) { }


/*
 * visus::power_overwhelming::msr_sensor::~msr_sensor
 */
visus::power_overwhelming::msr_sensor::~msr_sensor(void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::msr_sensor::core
 */
visus::power_overwhelming::msr_sensor::core_type
visus::power_overwhelming::msr_sensor::core(void) const {
    this->check_not_disposed();
    return this->_impl->core;
}


/*
 * visus::power_overwhelming::msr_sensor::domain
 */
visus::power_overwhelming::rapl_domain
visus::power_overwhelming::msr_sensor::domain(void) const {
    this->check_not_disposed();
    return this->_impl->domain;
}


/*
 * visus::power_overwhelming::msr_sensor::read
 */
visus::power_overwhelming::msr_sensor::raw_sample_type
visus::power_overwhelming::msr_sensor::read(void) const {
    this->check_not_disposed();
    return this->_impl->read(true);
}


/*
 * visus::power_overwhelming::msr_sensor::name
 */
_Ret_maybenull_z_
const wchar_t *visus::power_overwhelming::msr_sensor::name(
        void) const noexcept {
    return (this->_impl != nullptr)
        ? this->_impl->sensor_name.c_str()
        : nullptr;
}


/*
 * visus::power_overwhelming::msr_sensor::sample
 */
void visus::power_overwhelming::msr_sensor::sample(
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
 * visus::power_overwhelming::msr_sensor::operator =
 */
visus::power_overwhelming::msr_sensor&
visus::power_overwhelming::msr_sensor::operator =(
        _In_ msr_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        delete this->_impl;
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::msr_sensor::operator bool
 */
visus::power_overwhelming::msr_sensor::operator bool(void) const noexcept {
    return ((this->_impl != nullptr) && (this->_impl->device != nullptr)
        && *this->_impl->device);
}


/*
 * visus::power_overwhelming::msr_sensor::sample_async
 */
void visus::power_overwhelming::msr_sensor::sample_async(
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
 * visus::power_overwhelming::msr_sensor::sample_sync
 */
visus::power_overwhelming::measurement_data
visus::power_overwhelming::msr_sensor::sample_sync(void) const {
    assert(this->_impl);
    return this->_impl->sample();
}
