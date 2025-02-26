// <copyright file="msr_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "msr_sensor.h"

#include <cassert>
#include <stdexcept>

#include "visus/pwrowg/cpu_affinity.h"
#include "visus/pwrowg/cpu_info.h"
#include "visus/pwrowg/for_each_rapl_domain.h"

#include "msr_magic.h"
#include "msr_sensor_impl.h"
#include "sensor_description_builder.h"
#include "sensor_utilities.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// The type of a lookup table mapping RAPL domains to their location in
/// the MSR device file, which can also be used to find out whether a
/// RAPL domain is supported for a CPU vendor.
/// </summary>
typedef std::map<cpu_vendor, std::map<rapl_domain, msr_magic_config>>
rapl_domain_configs_type;

/// <summary>
/// Build a lookup table for the locations of the energy samples for the given
/// combination of CPU vendor and RAPL domain.
/// </summary>
static const rapl_domain_configs_type domain_configs = {
    {
        cpu_vendor::amd,
        {
            make_energy_magic_config(cpu_vendor::amd,
                rapl_domain::package,
                msr_offsets::amd::package_energy_status),
            make_energy_magic_config(cpu_vendor::amd,
                rapl_domain::pp0,
                msr_offsets::amd::pp0_energy_status)
        }
    },

    {
        cpu_vendor::intel,
        {
            make_energy_magic_config(cpu_vendor::intel,
                rapl_domain::dram,
                msr_offsets::intel::dram_energy_status),
            make_energy_magic_config(cpu_vendor::intel,
                rapl_domain::package,
                msr_offsets::intel::package_energy_status),
            make_energy_magic_config(cpu_vendor::intel,
                rapl_domain::pp0,
                msr_offsets::intel::pp0_energy_status),
            make_energy_magic_config(cpu_vendor::intel,
                rapl_domain::pp1,
                msr_offsets::intel::pp1_energy_status),
        }
    },
};


/// <summary>
/// Determine the unit divisor for the given configuration.
/// </summary>
static float divisor(_In_ const msr_device& device,
        _In_ const msr_magic_config& config) {
    auto divisor = device.read(config.unit_location);
    divisor = (divisor & config.unit_mask) >> config.unit_offset;
    return static_cast<float>(1 << divisor);
}

PWROWG_DETAIL_NAMESPACE_END


/*
 * PWROWG_DETAIL_NAMESPACE::msr_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::msr_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    sensor_description_builder builder;
    std::size_t retval = 0;
    bool succeeded = true;

    for (core_type c = 0; succeeded; ++c) {
        try {
            // Before doing anything else, we need to find out the CPU vendor
            // for being able to decide what the offset of the RAPL domain is
            // (and where the divisor for the energy unit is located). In order
            // to make sure that we read the CPUID of the correct socket, we set
            // the thread affinity to the core requested by the user. If this
            // fails, the core does not exist, so we do not need to continue
            // anyway.
            thread_affinity_scope affinity_scope(c);

            const auto v = get_cpu_vendor();
            builder.with_vendor(to_string(v))
                .with_name(L"%s (MSR)", to_string(v));

            auto vit = domain_configs.find(v);
            if (vit == domain_configs.end()) {
                // We do not have MSR addresses for the CPU vendor.
                continue;
            }

            // Test-create the device file to find out whether it is supported.
            auto dev = msr_device(msr_device::path(c));

            // Emit descriptions for all RAPL supported RAPL domains.
            for (auto& d : vit->second) {
                if (d.second.is_supported && !d.second.is_supported(c)) {
                    // The specified RAPL domain has specifically been marked as
                    // unsupported for the given core.
                    continue;
                }

                //d.second.
            }

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

//
///*
// * PWROWG_DETAIL_NAMESPACE::msr_sensor::offset
// */
//std::pair<std::streamoff, float> PWROWG_DETAIL_NAMESPACE::msr_sensor::offset(
//        _In_ const msr_device::core_type core,
//        _In_ const rapl_domain domain,
//        _In_opt_ const msr_magic_config *config_override) {
//    // Before doing anything else, we need to find out the CPU vendor for being
//    // able to decide what the offset of the RAPL domain is (and where the
//    // divisor for the energy unit is located). In order to make sure that we
//    // read the CPUID of the correct socket, we set the thread affinity to the
//    // core requested by the user. If this fails, the core does not exist, so we
//    // do not need to continue anyway.
//    thread_affinity_scope affinity_scope(core);
//
//    const auto vendor = get_cpu_vendor();
//    if (vendor == cpu_vendor::unknown) {
//        throw std::runtime_error("The vendor of the CPU could not be "
//            "determined, which is vital for initialising the RAPL domain "
//            "information correctly.");
//    }
//
//    // This is the configuration we will use to determine the offsets. Assign it
//    // either from user input or from our hardcoded magic tables.
//    msr_magic_config config;
//
//    if (config_override != nullptr) {
//        config = *config_override;
//
//    } else {
//        auto vit = domain_configs.find(vendor);
//        if (vit == domain_configs.end()) {
//            throw std::runtime_error("The MSR sensor is not supported for the "
//                "CPU of this machine.");
//        }
//
//        auto dit = vit->second.find(domain);
//        if (dit == vit->second.end()) {
//            throw std::invalid_argument("The specified RAPL domain is not "
//                "supported for the specified CPU core.");
//        }
//
//        if (dit->second.is_supported && !dit->second.is_supported(core)) {
//            throw std::invalid_argument("The specified RAPL domain is not "
//                "supported for the specified CPU core.");
//        }
//
//        config = dit->second;
//    }
//
//    // Open the MSR device file or get access to an already open instance for
//    // the same CPU core. We need this to read the divisor.
//    auto device = msr_device_factory::create(core);
//    auto divisor = device->read(config.unit_location);
//    divisor = (divisor & config.unit_mask) >> config.unit_offset;
//    divisor = 1 << divisor;
//
//    return std::make_pair(config.data_location, static_cast<float>(divisor));
//}


#if false
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
#endif
