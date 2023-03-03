// <copyright file="setup_api.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <string>

#if defined(_WIN32)
#include <Windows.h>
#include <emi.h>
#include <SetupAPI.h>

#pragma comment(lib, "Setupapi.lib")
#endif /* defined(_WIN32) */

#include <functional>

#include "on_exit.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

#if defined(_WIN32)
    /// <summary>
    /// Enumerate all known devices with the specified interface class.
    /// </summary>
    /// <typeparam name="TCallback">The callback that is invoked per device
    /// found. This callback must return a <c>bool</c> indicating whether the
    /// enumeration should continue and accept a <c>HDEVINFO</c> and a
    /// <c>SP_DEVICE_INTERFACE_DATA&</c> as parameters.</typeparam>
    /// <param name="interface_class"></param>
    /// <param name="callback"></param>
    /// <returns></returns>
    template<class TCallback>
    std::size_t enumerate_device_interface(const GUID& interface_class,
        TCallback callback);

    /// <summary>
    /// Gets the humand-readable description of the given class.
    /// </summary>
    /// <param name="guid"></param>
    /// <returns></returns>
    std::basic_string<TCHAR> get_class_description(const GUID& guid);

    /// <summary>
    /// Retrieves the path to the device specified by the given enumeration
    /// handle and device interface data.
    /// </summary>
    /// <param name="dev_info"></param>
    /// <param name="interface_data"></param>
    /// <param name="device_info_data"></param>
    /// <returns></returns>
    /// <exception cref=std::system_error">In case the path could not be
    /// retrieved from the provided input.</exception>
    std::basic_string<TCHAR> get_device_path(HDEVINFO dev_info,
        SP_DEVICE_INTERFACE_DATA& interface_data,
        PSP_DEVINFO_DATA device_info_data = nullptr);
#endif /* defined(_WIN32) */

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "setup_api.inl"
