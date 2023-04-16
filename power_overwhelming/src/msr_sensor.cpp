// <copyright file="msr_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/msr_sensor.h"

#include <cassert>

#include "msr_sensor_impl.h"


/*
 * visus::power_overwhelming::msr_sensor::force_create
 */
visus::power_overwhelming::msr_sensor
visus::power_overwhelming::msr_sensor::force_create(
        _In_ const core_type core,
        _In_ const rapl_domain domain,
        _In_ const std::streamoff offset) {
    msr_sensor retval;
    retval._impl->set(core, domain, offset);
    return retval;
}


/*
 * visus::power_overwhelming::msr_sensor::for_all
 */
std::size_t visus::power_overwhelming::msr_sensor::for_all(
        _Out_writes_opt_(cnt_sensors) msr_sensor *out_sensors,
        _In_ const std::size_t cnt_sensors) {
#if defined(_WIN32)
    return 0;

#else /* defined(_WIN32) */
#endif /* defined(_WIN32) */
    std::size_t retval = 0;
    bool succeeded = true;

    for (core_type c = 0; succeeded; ++c) {
        try {
            // Test-create the device file to find out whether the core exists.
            auto dev = detail::msr_device_factory::create(c);
            if (dev == nullptr) {
                throw std::logic_error("An invalid MSR device was created by "
                    "the msr_device_factor, which should never happen.");
            }

            // Now that we know that the core exists, try creating sensors for
            // all RAPL domains.
            try {
                msr_sensor sensor;
                assert(sensor);
                sensor._impl->set(c, rapl_domain::package, -1);


                ++retval;
            } catch (...) {
                // Not being able to create a sensor for a specific RAPL domain
                // does not constitute a fatall error. The RAPL domain just
                // might not be supported for the CPU, so we continue
                // enumerating in this case.
            }
        } catch (std::system_error) {
            // If creating a device for core 'c' causes an std::system_error, we
            // have reached the last core and leave the loop.
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
    // Specifying a negative offset will trigger an automatic lookup.
    return force_create(core, domain, -1);
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
 * visus::power_overwhelming::msr_sensor::offset
 */
std::streamoff visus::power_overwhelming::msr_sensor::offset(void) const {
    this->check_not_disposed();
    return this->_impl->offset;
}


/*
 * visus::power_overwhelming::msr_sensor::sample
 */
visus::power_overwhelming::measurement
visus::power_overwhelming::msr_sensor::sample(
        _In_ const timestamp_resolution resolution) const {
    this->check_not_disposed();
    return this->_impl->sample(resolution);
}


/*
 * visus::power_overwhelming::msr_sensor::operator =
 */
visus::power_overwhelming::msr_sensor&
visus::power_overwhelming::msr_sensor::operator =(_In_ msr_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
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
