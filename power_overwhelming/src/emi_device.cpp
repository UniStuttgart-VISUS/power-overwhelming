// <copyright file="emi_device.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "emi_device.h"

#include <cassert>
#include <memory>
#include <system_error>


#if defined(_WIN32)
/*
 * visus::power_overwhelming::detail::emi_device::emi_device
 */
visus::power_overwhelming::detail::emi_device::emi_device(
        const string_type& path)
        : _handle(INVALID_HANDLE_VALUE), _version({ 0 }) {
    this->_handle = ::CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ,
        nullptr, OPEN_EXISTING, 0, NULL);
    if (this->_handle == INVALID_HANDLE_VALUE) {
        // Nothing has been allocated in the object here, so it is OK to fail.
        throw std::system_error(::GetLastError(), std::system_category());
    }
}


/*
 * visus::power_overwhelming::detail::emi_device::emi_device
 */

visus::power_overwhelming::detail::emi_device::emi_device(
        emi_device&& rhs) noexcept {
    *this = std::move(rhs);
}


/*
 * visus::power_overwhelming::detail::emi_device::~emi_device
 */
visus::power_overwhelming::detail::emi_device::~emi_device(void) noexcept {
    if (this->_handle != INVALID_HANDLE_VALUE) {
        ::CloseHandle(this->_handle);
    }
}


/*
 * visus::power_overwhelming::detail::emi_device::channels
 */
decltype(EMI_METADATA_V2::ChannelCount)
visus::power_overwhelming::detail::emi_device::channels(void) const {
    switch (this->version().EmiVersion) {
        case EMI_VERSION_V1:
            return 1;

        case EMI_VERSION_V2:
            return this->metadata_as<EMI_METADATA_V2>()->ChannelCount;

        default:
            return 0;
    }
}


/*
 * visus::power_overwhelming::detail::emi_device::metadata
 */
const visus::power_overwhelming::detail::emi_device::metadata_type&
visus::power_overwhelming::detail::emi_device::metadata(void) const {
    if (this->_metadata.empty()) {
        // Find out how big the metadata are.
        {
            DWORD returned = 0;
            EMI_METADATA_SIZE size;
            if (!::DeviceIoControl(this->_handle, IOCTL_EMI_GET_METADATA_SIZE,
                    nullptr, 0,
                    &size, sizeof(size),
                    &returned, 0)) {
                const auto e = ::GetLastError();
                throw std::system_error(e, std::system_category());
            }
            assert(returned == sizeof(size));

            this->_metadata.resize(size.MetadataSize);
        }

        // Retrieve the metadata.
        {
            DWORD returned = 0;
            const auto size = static_cast<DWORD>(this->_metadata.size());
            if (!::DeviceIoControl(this->_handle, IOCTL_EMI_GET_METADATA,
                    nullptr, 0,
                    this->_metadata.data(), size,
                    &returned, 0)) {
                this->_metadata.clear();
                const auto e = ::GetLastError();
                throw std::system_error(e, std::system_category());
            }
            assert(returned == size);
        }
    }

    return this->_metadata;
}


/*
 * visus::power_overwhelming::detail::emi_device::version
 */
EMI_VERSION visus::power_overwhelming::detail::emi_device::version(void) const {
    if (this->_version.EmiVersion < 1) {
        DWORD returned = 0;
        if (!::DeviceIoControl(this->_handle, IOCTL_EMI_GET_VERSION,
                nullptr, 0,
                &_version, sizeof(_version),
                &returned, 0)) {
            const auto e = ::GetLastError();
            throw std::system_error(e, std::system_category());
        }
        assert(returned == sizeof(this->_version));
    }

    return this->_version;
}


/*
 * visus::power_overwhelming::detail::emi_device::operator =
 */
visus::power_overwhelming::detail::emi_device&
visus::power_overwhelming::detail::emi_device::operator =(
        emi_device &&rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_handle = rhs._handle;
        rhs._handle = INVALID_HANDLE_VALUE;
        this->_metadata = std::move(rhs._metadata);
        this->_version = rhs._version;
        rhs._version.EmiVersion = 0;
    }

    return *this;
}
#endif /* defined(_WIN32) */
