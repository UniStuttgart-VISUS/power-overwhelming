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
static float msr_unit_divisor(_In_ const msr_device& device,
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
    const auto base_type = sensor_type::software | sensor_type::power;
    sensor_description_builder builder;
    std::size_t retval = 0;
    bool succeeded = true;

    if (dst == nullptr) {
        cnt = 0;
    }

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

            const auto vendor = get_cpu_vendor();
            builder.with_vendor(to_string(vendor));

            auto vit = domain_configs.find(vendor);
            if (vit == domain_configs.end()) {
                // We do not have MSR addresses for the CPU vendor.
                continue;
            }

            // Test-create the device file to find out whether it is supported.
            const auto path = msr_device::path(c);
            auto dev = msr_device(path);

            // Emit descriptions for all RAPL supported RAPL domains.
            for (auto& d : vit->second) {
                if (d.second.is_supported && !d.second.is_supported(c)) {
                    // The specified RAPL domain has specifically been marked as
                    // unsupported for the given core.
                    continue;
                }

                switch (d.first) {
                    case rapl_domain::package:
                    case rapl_domain::pp0:
                    case rapl_domain::pp1:
                        builder.with_type(base_type | sensor_type::cpu);
                        break;

                    case rapl_domain::dram:
                        builder.with_type(base_type | sensor_type::memory);
                        break;
                }

                builder.with_id(L"MSR/%d/%s", c, to_string(d.first))
                    .with_name(L"%s Core %d %s (MSR)", to_string(vendor), c,
                        to_string(d.first))
                    .with_path(path)
                    .produces(reading_type::floating_point)
                    .measured_in(reading_unit::watt)
                    .with_new_private_data<register_identifier>(
                        d.second.data_location,
                        msr_unit_divisor(dev, d.second));

                if (retval < cnt) {
                    dst[retval] = builder.build();
                }

                ++retval;
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
#endif


/*
 * PWROWG_DETAIL_NAMESPACE::msr_sensor::msr_sensor
 */
PWROWG_DETAIL_NAMESPACE::msr_sensor::msr_sensor(_In_z_ const wchar_t *path,
        _Inout_ std::vector<register_identifier>&& registers,
        _In_ const PWROWG_NAMESPACE::sample::source_type index)
    : _device(PWROWG_NAMESPACE::convert_string<path_char_type>(path)),
        _index(index),
        _registers(std::move(registers)) {
    this->_last_timestamp.reserve(this->_registers.size());
    this->_last_value.reserve(this->_registers.size());

    // Obtain the first reading, which (i) ensures the sensor is working and
    // (ii) provides the reference value to convert energy into power estimates.
    for (auto& r : this->_registers) {
        this->_last_value.emplace_back(this->_device.read(r.offset)
            / r.divisor);
        this->_last_timestamp.push_back(timestamp::now());
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::msr_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::msr_sensor::sample(
        _In_ const sensor_array_callback callback,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context) {
    typedef std::chrono::duration<float> seconds_type;
    assert(callback != nullptr);

    std::vector<PWROWG_NAMESPACE::sample> samples;
    samples.reserve(this->_registers.size());

    for (decltype(this->_index) i = 0; i < this->_registers.size(); ++i) {
        const auto& r = this->_registers[i];

        // Obtain new readings.
        const auto value = this->_device.read(r.offset) / r.divisor;
        const auto now = timestamp::now();

        // Compute the time elapsed since the last call to the method. We use
        // that to compute the point in time for the sample in between the two
        // calls as the timestamp of the sample we deliver.
        const auto dt = now - this->_last_timestamp[i];
        const auto timestamp = this->_last_timestamp[i] + dt / 2;

        auto dv = value - this->_last_value[i];
        dv /= std::chrono::duration_cast<seconds_type>(dt).count();

        samples.emplace_back(this->_index + i, timestamp, dv);

        // Preserve the current values for the next call.
        this->_last_timestamp[i] = now;
        this->_last_value[i] = value;
    }

    callback(samples.data(), samples.size(), sensors, context);
}
