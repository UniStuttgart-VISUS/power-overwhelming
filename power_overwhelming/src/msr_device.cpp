// <copyright file="msr_device.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "msr_device.h"

#include "io_util.h"


/*
 * visus::power_overwhelming::detail::msr_device::path
 */
visus::power_overwhelming::detail::msr_device::string_type
visus::power_overwhelming::detail::msr_device::path(
        _In_ const core_type core) {
    return string_type("/dev/cpu/") + std::to_string(core) + "/ msr";
}


/*
 * visus::power_overwhelming::detail::msr_device::msr_device
 */
visus::power_overwhelming::detail::msr_device::msr_device(
        _In_ const string_type& path)
    : _handle(detail::open(path.c_str(), O_RDONLY)) { }


/*
 * visus::power_overwhelming::detail::msr_device::msr_device
 */

visus::power_overwhelming::detail::msr_device::msr_device(
        _In_ msr_device&& rhs) noexcept {
    *this = std::move(rhs);
}


/*
 * visus::power_overwhelming::detail::msr_device::~msr_device
 */
visus::power_overwhelming::detail::msr_device::~msr_device(void) noexcept {
    if (this->_handle != -1) {
        ::close(this->_handle);
    }
}


/*
 * visus::power_overwhelming::detail::msr_device::read
 */
visus::power_overwhelming::detail::msr_device::sample_type
visus::power_overwhelming::detail::msr_device::read(
        _In_ const std::streamoff where) const {
    sample_type retval;
    detail::seek(this->_handle, where, posix_seek_origin::begin);
    detail::read_bytes(this->_handle, &retval, sizeof(retval));
    return retval;
}


/*
 * visus::power_overwhelming::detail::msr_device::operator =
 */
visus::power_overwhelming::detail::msr_device&
visus::power_overwhelming::detail::msr_device::operator =(
        _In_ msr_device &&rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_handle = rhs._handle;
        rhs._handle = -1;
    }

    return *this;
}
