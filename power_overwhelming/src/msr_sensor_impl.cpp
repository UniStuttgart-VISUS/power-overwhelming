// <copyright file="msr_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "msr_sensor_impl.h"

#include <algorithm>
#include <map>
#include <stdexcept>

#include "msr_offsets.h"
#include "msr_units.h"
#include "timestamp.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// The configuration data we need to know for a RAPL domain.
    /// </summary>
    struct rapl_domain_config {
        /// <summary>
        /// The offset of the specific domain in the MSR device file.
        /// </summary>
        std::streamoff offset;

        inline rapl_domain_config(_In_ const std::streamoff offset)
            : offset(offset) { }
    };

    /// <summary>
    /// The type of a lookup table mapping RAPL domains to their location in
    /// the MSR device file, which can also be used to find out whether a
    /// RAPL domain is supported for a CPU vendor.
    /// </summary>
    typedef std::map<cpu_vendor, std::map<rapl_domain, rapl_domain_config>>
        rapl_domain_configs_type;

    /// <summary>
    /// Build a lookup table for the locations of the energy samples for the given
    /// combination of CPU vendor and RAPL domain.
    /// </summary>
    static const rapl_domain_configs_type domain_configs = {
        {
            cpu_vendor::amd,
            {
                {
                    visus::power_overwhelming::rapl_domain::dram,
                    rapl_domain_config(msr_offsets::dram_energy_status)
                },
                {
                    visus::power_overwhelming::rapl_domain::package,
                    rapl_domain_config(msr_offsets::amd_package_energy_status)
                },
                {
                    visus::power_overwhelming::rapl_domain::pp0,
                    rapl_domain_config(msr_offsets::amd_pp0_energy_status)
                },
                {
                    // TODO: is that the same on AMD and Intel or just not supported on AMD?
                    visus::power_overwhelming::rapl_domain::pp1,
                    rapl_domain_config(msr_offsets::pp1_energy_status)
                },
            }
        },

        {
            cpu_vendor::intel,
            {
                {
                    visus::power_overwhelming::rapl_domain::dram,
                    rapl_domain_config(msr_offsets::dram_energy_status)
                },
                {
                    visus::power_overwhelming::rapl_domain::package,
                    rapl_domain_config(msr_offsets::intel_package_energy_status)
                },
                {
                    visus::power_overwhelming::rapl_domain::pp0,
                    rapl_domain_config(msr_offsets::intel_pp0_energy_status)
                },
                {
                    visus::power_overwhelming::rapl_domain::pp1,
                    rapl_domain_config(msr_offsets::pp1_energy_status)
                },
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
    typedef std::pair<rapl_domain, rapl_domain_config> offset_pair;
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
 * visus::power_overwhelming::detail::msr_sensor_impl::sample
 */
void visus::power_overwhelming::detail::msr_sensor_impl::sample(void) {
    assert(this->device != nullptr);
    this->last_sample = this->device->read(this->offset);
    this->last_time = std::chrono::system_clock::now();
}


/*
 * visus::power_overwhelming::detail::msr_sensor_impl::sample
 */
visus::power_overwhelming::measurement
visus::power_overwhelming::detail::msr_sensor_impl::sample(
        _In_ const timestamp_resolution resolution) const {
    assert(this->device != nullptr);
    typedef std::chrono::duration<measurement::value_type> seconds_type;

    // Obtain new readings.
    const auto value = this->device->read(this->offset);
    const auto now = std::chrono::system_clock::now();

    // Compute the difference and convert it to Joules by applying the
    // divisor obtained during initialisation.
    auto sample_value = static_cast<measurement::value_type>(this->last_sample
        - value) / this->unit_divisor;

    // Compute the time elapsed since the last call to the method. We use that
    // to compute the point in time for the sample in between the two calls.
    const auto dt = now - this->last_time;
    const auto sample_time = this->last_time + dt / 2;
    const auto timestamp = convert(sample_time, resolution);

    sample_value /= std::chrono::duration_cast<seconds_type>(dt).count();

    // Preserve the current values for the next call.
    this->last_sample = value;
    this->last_time = now;

    return measurement(this->sensor_name.c_str(), timestamp, sample_value);
}


/*
 * visus::power_overwhelming::detail::msr_sensor_impl::set
 */
void visus::power_overwhelming::detail::msr_sensor_impl::set(
        _In_ const msr_device::core_type core,
        _In_ const rapl_domain domain,
        _In_ const std::streamoff offset) {
    if (offset >= 0) {
        // We have an override by the user, so just use it.
        this->offset = offset;

    } else {
        // Before doing anything else, we need to find out the CPU vendor for
        // being able to decide what the offsetf of the RAPL domain are. In
        // order to make sure that we read the CPUID of the correct socket, we
        // set the thread affinity to the core requested by the user. If this
        // fails, the core does not exist, so we do not need to continue anyway.
        thread_affinity_restore_point restore_point;
        set_thread_affinity(core);

        const auto vendor = get_cpu_vendor();
        if (vendor == cpu_vendor::unknown) {
            throw std::runtime_error("The vendor of the CPU could not be "
                "determined, which is vital for initialising the RAPL domain "
                "information correctly.");
        }

        // Next, find out whether the sensor is supported on the CPU.
        {
            auto vit = domain_configs.find(vendor);
            if (vit == domain_configs.end()) {
                throw std::runtime_error("The MSR sensor is not supported for "
                    "the CPU of this machine.");
            }

            auto dit = vit->second.find(domain);
            if (dit == vit->second.end()) {
                throw std::invalid_argument("The specified RAPL domain is not "
                    "supported for the CPU of this machine.");
            }

            // As we already have the entry from the map, preserve it for later.
            this->offset = dit->second.offset;
        }
    }

    // Open the MSR device file or get access to an already open instance for
    // the same CPU core.
    this->device = msr_device_factory::create(core);

    // If we could open the file, it is safe to assume that we can use the
    // sensor, so it makes sense now to compile its name.
    this->sensor_name = L"msr/" + std::to_wstring(core) + L"/"
        + to_string(domain);

    // Next, retrieve the unit conversion constants for the values as in
    // https://lkml.org/lkml/2011/5/26/93.
    {
        auto sample = this->device->read(msr_offsets::unit_divisors);
        sample = (sample & msr_units::energy_mask) >> msr_units::energy_offset;
        this->unit_divisor = static_cast<measurement::value_type>(1 << sample);
    }

    // Finally, retrieve a first sample, because we need a reference whenever
    // the user samples the sensor as the RAPL registers record incremental
    // measurements.
    this->sample();
}
