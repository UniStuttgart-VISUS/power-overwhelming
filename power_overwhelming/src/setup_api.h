// <copyright file="setup_api.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 - 2025 Visualisierungsinstitut der Universit�t Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph M�ller</author>

#if !defined(_PWROWG_SETUP_API_H)
#define _PWROWG_SETUP_API_H
#pragma once

#include <string>

#if defined(_WIN32)
#include <Windows.h>
#include <emi.h>
#include <SetupAPI.h>

#pragma comment(lib, "Setupapi.lib")
#endif /* defined(_WIN32) */

#include <functional>

#include "visus/pwrowg/on_exit.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

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
template<class TCallback> std::size_t enumerate_device_interface(
    const GUID& interface_class, TCallback callback);

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

PWROWG_DETAIL_NAMESPACE_END

#include "setup_api.inl"

#endif /* !defined(_PWROWG_SETUP_API_H) */
