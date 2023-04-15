// <copyright file="msr_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "msr_sensor_impl.h"

#include <stdexcept>

#include "power_overwhelming/cpu_vendor.h"


/*
 * visus::power_overwhelming::detail::msr_sensor_impl::~msr_sensor_impl
 */
visus::power_overwhelming::detail::msr_sensor_impl::~msr_sensor_impl(void) {
}


/*
 * visus::power_overwhelming::detail::msr_sensor_impl::set
 */
void visus::power_overwhelming::detail::msr_sensor_impl::set(
        _In_ const msr_device::core_type core,
        _In_ const rapl_domain domain) {
    // Before doing anything else, we need to find out the CPU vendor for being
    // able to decide what the offsetf of the RAPL domain are.
    const auto vendor = get_cpu_vendor();
    if (vendor == cpu_vendor::unknown) {
        throw std::runtime_error("The vendor of the CPU could not be "
            "determined, which is vital for initialising the RAPL domain "
            "information correctly.");
    }

    // Open the MSR device file or get access to an already open instance for
    // the same CPU core.
    this->device = msr_device_factory::create(core);

    // If we could open the file, it is safe to assume that we can use the
    // sensor, so it makes sense now to compile its name.
    this->sensor_name = L"msr/" + std::to_wstring(core) + L"/"
        + to_string(domain);

    // If we have the device file, retrieve the unit conversion constants as the
    // very first step.
    {
        const auto sample = this->device->read(unit_offset);
        std::uint32_t value = 0;

        value = (sample & energy_unit_mask) >> energy_unit_offset;
        this->energy_unit_divisor = 1 << value;

        value = (sample & power_unit_mask) >> power_unit_offset;
        this->energy_unit_divisor = 1 << value;

        value = (sample & time_unit_mask) >> time_unit_offset;
        this->energy_unit_divisor = 1 << value;
    }

    // TODO: compose the right offset.
}
