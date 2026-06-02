// <copyright file="usb_reset.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "usb_reset.h"

#include <array>
#include <regex>
#include <stdexcept>
#include <system_error>
#include <vector>

#include "visus/pwrowg/string_functions.h"


#if defined(_WIN32)
/*
 * PWROWG_DETAIL_NAMESPACE::eject_device
 */
void PWROWG_DETAIL_NAMESPACE::eject_device(_In_ const DEVINST device) {
    std::array<char, _MAX_PATH> msg;
    PNP_VETO_TYPE veto;

    const auto cr = ::CM_Request_Device_EjectA(device, &veto, msg.data(),
        static_cast<ULONG>(msg.size()), 0);
    switch (cr) {
        case CR_SUCCESS:
            break;

        case CR_REMOVE_VETOED:
            switch (veto) {
                case PNP_VetoLegacyDevice:
                    throw std::runtime_error("The device does not support the "
                        "specified PnP operation.");
                case PNP_VetoPendingClose:
                    throw std::runtime_error("The specified operation cannot "
                        "be completed because of a pending close operation.");
                case PNP_VetoWindowsApp:
                    throw std::runtime_error("A Microsoft Win32 application "
                        "vetoed the specified operation.");
                case PNP_VetoWindowsService:
                    throw std::runtime_error("A Win32 service vetoed the "
                        "specified operation.");
                case PNP_VetoOutstandingOpen:
                    throw std::runtime_error("The requested operation was "
                        "rejected because of outstanding open handles.");
                case PNP_VetoDevice:
                    throw std::runtime_error("The device supports the "
                        "specified operation, but the device rejected the "
                        "operation.");
                case PNP_VetoDriver:
                    throw std::runtime_error("The driver supports the specified "
                        "operation, but the driver rejected the operation.");
                case PNP_VetoIllegalDeviceRequest:
                    throw std::runtime_error("The device does not support the "
                        "specified operation.");
                case PNP_VetoInsufficientPower:
                    throw std::runtime_error("There is insufficient power to "
                        "perform the requested operation.");
                case PNP_VetoNonDisableable:
                    throw std::runtime_error("The device cannot be disabled.");
                case PNP_VetoLegacyDriver:
                    throw std::runtime_error("The driver does not support the "
                        "specified PnP operation.");
                case PNP_VetoInsufficientRights:
                    throw std::runtime_error("The caller has insufficient "
                        "privileges to complete the operation.");
                case PNP_VetoTypeUnknown:
                default:
                    throw std::runtime_error("The specified operation was "
                        "rejected for an unknown reason.");
            }

        default:
            throw std::system_error(::CM_MapCrToWin32Err(cr, ERROR_GEN_FAILURE),
                std::system_category());
    }
}
#endif /* defined(_WIN32) */


#if defined(_WIN32)
/*
 * PWROWG_DETAIL_NAMESPACE::eject_device
 */
DEVINST PWROWG_DETAIL_NAMESPACE::eject_device(_In_z_ const char *instance) {
    DEVINST retval;
    DEVINST device;
    auto i = const_cast<char *>(instance);

    {
        const auto cr = ::CM_Locate_DevNodeA(&device, i, 0);
        if (cr != CR_SUCCESS) {
            throw std::system_error(::CM_MapCrToWin32Err(cr, ERROR_GEN_FAILURE),
                std::system_category());
        }
    }

    {
        const auto cr = ::CM_Get_Parent(&retval, device, 0);
        if (cr != CR_SUCCESS) {
            throw std::system_error(::CM_MapCrToWin32Err(cr, ERROR_GEN_FAILURE),
                std::system_category());
        }
    }

    eject_device(device);

    return retval;
}
#endif /* defined(_WIN32) */


#if defined(_WIN32)
/*
 * PWROWG_DETAIL_NAMESPACE::reset_usb_device
 */
std::string PWROWG_DETAIL_NAMESPACE::get_instance_id(
        _In_ const visa_instrument& inst) {
    static const std::regex rx_ids("USB.+::0x([0-9a-f]+)::"
        "0x([0-9a-f]+)::(?:0x)?([0-9a-f]+)::.+", std::regex::icase);

    auto p = inst.path();
    std::cmatch m;
    if ((p == nullptr) || !std::regex_match(p, m, rx_ids)) {
        throw std::invalid_argument("The instrument is not connected via USB "
            "or has an unexpected VISA path.");
    }

    return detail::format_string("USB\\VID_%s&PID_%s\\%s", m[1].str().c_str(),
        m[2].str().c_str(), m[3].str().c_str());
}
#endif /* defined(_WIN32) */


/*
 * PWROWG_DETAIL_NAMESPACE::reset_usb_device
 */
PWROWG_TEST_API void PWROWG_DETAIL_NAMESPACE::reset_usb_device(
        _In_z_ const char *instance) {
#if defined(_WIN32)
    auto bus = eject_device(instance);

    const auto cr = ::CM_Reenumerate_DevNode(bus, CM_REENUMERATE_SYNCHRONOUS);
    if (cr != CR_SUCCESS) {
        throw std::system_error(::CM_MapCrToWin32Err(cr, ERROR_GEN_FAILURE),
            std::system_category());
    }
#endif /* defined(_WIN32) */
}
