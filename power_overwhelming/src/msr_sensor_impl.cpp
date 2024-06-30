// <copyright file="msr_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "msr_sensor_impl.h"

#include <algorithm>
#include <map>
#include <stdexcept>

#include "device_sampler_source.h"
#include "msr_magic.h"
#include "sampler.h"


#define ERROR_MSG_UNSUPPORTED_CPU "The MSR sensor is not supported for the "\
    "CPU of this machine."
#define ERROR_MSG_UNSUPPORTED_CORE "The specified RAPL domain is not "\
    "supported for the specified CPU core."


namespace visus {
namespace power_overwhelming {
namespace detail {

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

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */


/*
 * visus::power_overwhelming::detail::msr_sensor_impl::supported_domains
 */
std::vector<visus::power_overwhelming::rapl_domain>
visus::power_overwhelming::detail::msr_sensor_impl::supported_domains(
        _In_ const cpu_vendor vendor) {
    typedef detail::msr_magic_config_entry offset_pair;
    std::vector<rapl_domain> retval;

    auto it = domain_configs.find(vendor);
    if (it != domain_configs.end()) {
        retval.reserve(it->second.size());

        std::transform(it->second.begin(), it->second.end(),
                std::back_inserter(retval), [](const offset_pair& p) {
            return p.first;
        });
    }

    return retval;
}


/*
 * visus::power_overwhelming::detail::msr_sensor_impl::~msr_sensor_impl
 */
visus::power_overwhelming::detail::msr_sensor_impl::~msr_sensor_impl(
        void) noexcept {
    // Make sure that the sensor is unregistered from asynchronous sampling.
    sampler::default_sampler -= this;
}


/*
 * visus::power_overwhelming::detail::msr_sensor_impl::read
 */
visus::power_overwhelming::detail::msr_device::sample_type
visus::power_overwhelming::detail::msr_sensor_impl::read(
        _In_ const bool convert) const {
    auto retval = this->device->read(this->offset);

    if (convert) {
        retval /= static_cast<decltype(retval)>(this->unit_divisor);
    }

    return retval;
}


/*
 * visus::power_overwhelming::detail::msr_sensor_impl::sample
 */
visus::power_overwhelming::measurement_data
visus::power_overwhelming::detail::msr_sensor_impl::sample(void) const {
    assert(this->device != nullptr);
    typedef std::chrono::duration<measurement_data::value_type> seconds_type;

    // Obtain new readings.
    const auto value = this->device->read(this->offset);
    const auto now = std::chrono::system_clock::now();

    // Compute the difference and convert it to Joules by applying the
    // divisor obtained during initialisation.
    const auto dv = value - this->last_sample;
    auto sample_value = static_cast<measurement_data::value_type>(dv)
        / this->unit_divisor;

    // Compute the time elapsed since the last call to the method. We use that
    // to compute the point in time for the sample in between the two calls.
    const auto dt = now - this->last_time;
    const auto sample_time = this->last_time + dt / 2;
    const auto timestamp = power_overwhelming::timestamp(sample_time);

    sample_value /= std::chrono::duration_cast<seconds_type>(dt).count();

    // Preserve the current values for the next call.
    this->last_sample = value;
    this->last_time = now;

    return measurement_data(timestamp, sample_value);
}


/*
 * visus::power_overwhelming::detail::msr_sensor_impl::set
 */
void visus::power_overwhelming::detail::msr_sensor_impl::set(
        _In_ const msr_device::core_type core,
        _In_ const rapl_domain domain,
        _In_opt_ const msr_magic_config *config_override) {
    // Before doing anything else, we need to find out the CPU vendor for being
    // able to decide what the offset of the RAPL domain is (and where the
    // divisor for the energy unit is located). In order to make sure that we
    // read the CPUID of the correct socket, we set the thread affinity to the
    // core requested by the user. If this fails, the core does not exist, so we
    // do not need to continue anyway.
    thread_affinity_scope affinity_scope(core);

    const auto vendor = get_cpu_vendor();
    if (vendor == cpu_vendor::unknown) {
        throw std::runtime_error("The vendor of the CPU could not be "
            "determined, which is vital for initialising the RAPL domain "
            "information correctly.");
    }

    // This is the configuration we will use to determine the offsets. Assign it
    // either from user input or from our hardcoded magic tables.
    msr_magic_config config;

    if (config_override != nullptr) {
        config = *config_override;

    } else {
        auto vit = domain_configs.find(vendor);
        if (vit == domain_configs.end()) {
            throw std::runtime_error(ERROR_MSG_UNSUPPORTED_CPU);
        }

        auto dit = vit->second.find(domain);
        if (dit == vit->second.end()) {
            throw std::invalid_argument(ERROR_MSG_UNSUPPORTED_CORE);
        }

        if (dit->second.is_supported && !dit->second.is_supported(core)) {
            throw std::invalid_argument(ERROR_MSG_UNSUPPORTED_CORE);
        }

        config = dit->second;
    }

    // Open the MSR device file or get access to an already open instance for
    // the same CPU core.
    this->device = msr_device_factory::create(core);

    // If we could open the file, it is safe to assume that we can use the
    // sensor, so it makes sense now to compile its name.
    this->core = core;
    this->domain = domain;
    this->offset = config.data_location;
    this->sensor_name = L"msr/" + std::to_wstring(this->core) + L"/"
        + to_string(this->domain);

    // Next, retrieve the unit conversion constants for the values.
    {
        auto divisor = this->device->read(config.unit_location);
        divisor = (divisor & config.unit_mask) >> config.unit_offset;
        this->unit_divisor = static_cast<measurement::value_type>(1 << divisor);
    }

    // Finally, retrieve a first sample, because we need a reference whenever
    // the user samples the sensor as the RAPL registers record incremental
    // measurements.
    this->sample();
}
