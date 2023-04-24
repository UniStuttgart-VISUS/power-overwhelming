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
#if defined(_WIN32)
    return string_type(L"\\\\?\\PowerOverwhelmingRaplMsrs\\")
        + std::to_wstring(core);
#else /* defined(_WIN32) */
    return string_type("/dev/cpu/") + std::to_string(core) + "/msr";
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::detail::msr_device::invalid_handle_value
 */
constexpr const visus::power_overwhelming::detail::msr_device::handle_type
visus::power_overwhelming::detail::msr_device::invalid_handle_value;


/*
 * visus::power_overwhelming::detail::msr_device::msr_device
 */
visus::power_overwhelming::detail::msr_device::msr_device(
        _In_ const string_type& path)
#if defined(_WIN32)
    : _handle(detail::open(path.c_str(), GENERIC_READ, FILE_SHARE_READ,
        OPEN_EXISTING, 0)) { }
#else /* defined(_WIN32) */
    : _handle(detail::open(path.c_str(), O_RDONLY)) { }
#endif /* defined(_WIN32) */


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
    if (this->_handle != invalid_handle_value) {
#if defined(_WIN32)
        ::CloseHandle(this->_handle);
#else /* defined(_WIN32) */
        ::close(this->_handle);
#endif /* defined(_WIN32) */
    }
}


/*
 * visus::power_overwhelming::detail::msr_device::read
 */
visus::power_overwhelming::detail::msr_device::sample_type
visus::power_overwhelming::detail::msr_device::read(
        _In_ const std::streamoff where) const {
#if defined(_WIN32)
    constexpr auto seek_origin = win32_seek_origin::begin;
#else /* defined(_WIN32) */
    constexpr auto seek_origin = posix_seek_origin::begin;
#endif /* defined(_WIN32) */
    sample_type retval;
    detail::seek(this->_handle, where, seek_origin);
    detail::read_bytes(this->_handle, &retval, sizeof(retval));
    return retval;
}


/*
 * visus::power_overwhelming::detail::msr_device::read
 */
std::vector<std::uint8_t> visus::power_overwhelming::detail::msr_device::read(
        void) const {
    return detail::read_all_bytes(this->_handle);
}


/*
 * visus::power_overwhelming::detail::msr_device::operator =
 */
visus::power_overwhelming::detail::msr_device&
visus::power_overwhelming::detail::msr_device::operator =(
        _In_ msr_device&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_handle = rhs._handle;
        rhs._handle = invalid_handle_value;
    }

    return *this;
}
