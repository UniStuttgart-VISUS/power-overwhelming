// <copyright file="setup_api.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#if defined(_WIN32)
#include <initguid.h> // [sic]
#endif /* defined(_WIN32) */
#include "setup_api.h"

#include <system_error>
#include <vector>


#if defined(_WIN32)
/*
 * visus::power_overwhelming::detail::get_class_description
 */
std::basic_string<TCHAR>
visus::power_overwhelming::detail::get_class_description(const GUID& guid) {
    DWORD size = 0;

    ::SetupDiGetClassDescription(&guid, nullptr, 0, &size);
    {
        auto e = ::GetLastError();
        switch (e) {
            case ERROR_SUCCESS:
            case ERROR_INSUFFICIENT_BUFFER:
                break;

            default:
                throw std::system_error(e, std::system_category());
        }
    }

    std::basic_string<TCHAR> retval(size, static_cast<TCHAR>(0));
    if (!::SetupDiGetClassDescription(&guid, &retval[0], size, &size)) {
        auto e = ::GetLastError();
        throw std::system_error(e, std::system_category());
    }

    return retval;
}


/*
 * visus::power_overwhelming::detail::get_device_path
 */
std::basic_string<TCHAR>
visus::power_overwhelming::detail::get_device_path(HDEVINFO dev_info,
        SP_DEVICE_INTERFACE_DATA& interface_data,
        PSP_DEVINFO_DATA device_info_data) {
    DWORD size = 0;

    // Determine the required size of the buffer.
    ::SetupDiGetDeviceInterfaceDetail(dev_info, &interface_data, nullptr, 0,
        &size, nullptr);
    {
        auto e = ::GetLastError();
        switch (e) {
            case ERROR_SUCCESS:
            case ERROR_INSUFFICIENT_BUFFER:
                break;

            default:
                throw std::system_error(e, std::system_category());
        }
    }

    std::vector<std::uint8_t> buffer(size);

    auto d = reinterpret_cast<PSP_DEVICE_INTERFACE_DETAIL_DATA>(buffer.data());
    d->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
    if (!::SetupDiGetDeviceInterfaceDetail(dev_info, &interface_data, d,
            size, nullptr, device_info_data)) {
        auto e = ::GetLastError();
        throw std::system_error(e, std::system_category());
    }

    return d->DevicePath;
}
#endif /* defined(_WIN32) */
