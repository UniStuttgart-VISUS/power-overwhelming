// <copyright file="msr_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "msr_sensor_impl.h"


/*
 * visus::power_overwhelming::detail::msr_sensor_impl::~msr_sensor_impl
 */
visus::power_overwhelming::detail::msr_sensor_impl::~msr_sensor_impl(void) {
    this->close();
}


/*
 * visus::power_overwhelming::detail::msr_sensor_impl::close
 */
void visus::power_overwhelming::detail::msr_sensor_impl::close(void) noexcept {
    if (this->handle != -1) {
        ::close(this->handle);
    }
}


/*
 * visus::power_overwhelming::detail::msr_sensor_impl::open
 */
void visus::power_overwhelming::detail::msr_sensor_impl::open(
        _In_ const std::uint32_t core) {
    this->close();
    auto path = std::string("/dev/cpu/") + std::to_string(core) + "/ msr";
    this->handle = detail::open(path.c_str(), O_RDONLY);
}


/*
 * visus::power_overwhelming::detail::msr_sensor_impl::read
 */
visus::power_overwhelming::detail::msr_sensor_impl::sample_type
visus::power_overwhelming::detail::msr_sensor_impl::read(
        _In_ const rapl_domain which) {
    sample_type retval;

    detail::seek(this->handle, static_cast<std::streamoff>(which),
        posix_seek_origin::begin);
    read_bytes(this->handle, &retval, sizeof(retval));

    return retval;
}
