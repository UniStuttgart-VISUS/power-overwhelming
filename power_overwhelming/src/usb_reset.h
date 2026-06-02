// <copyright file="usb_reset.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#if defined(_WIN32)
#include <Windows.h>
#include <cfgmgr32.h>
#endif /* defined(_WIN32) */

#include "visus/pwrowg/visa_instrument.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

#if defined(_WIN32)
/// <summary>
/// Tries ejecting the device with the given instance handle.
/// </summary>
/// <param name="device"></param>
/// <exception cref="std::runtime_error">If the device or a driver vetoes the
/// eject request. The error message contains the reason for the veto.
/// </exception>
/// <exception cref="std::system_error">If the eject request fails for other
/// reasons. The error code contains the reason for the failure.</exception>
PWROWG_TEST_API void eject_device(_In_ const DEVINST device);
#endif /* defined(_WIN32) */


#if defined(_WIN32)
/// <summary>
/// Tries ejecting the device with the given instance ID.
/// </summary>
/// <param name="instance">The instance ID from the PNP manager. This ID has a
/// form like PCI\VEN_1000&DEV_0001&amp;SUBSYS_00000000&amp;REV_02\1&amp;08.
/// </param>
/// <return>The instance handle of the parent device of the ejected device,
/// which can be used to re-enumerate the device after it has been ejected.
/// </return>
/// <exception cref="std::runtime_error">If the device or a driver vetoes the
/// eject request. The error message contains the reason for the veto.
/// </exception>
/// <exception cref="std::system_error">If the device identified by
/// <see cref="instance" /> was not found or if the eject request fails for
/// other reasons. The error code contains the reason for the failure.
/// </exception>
PWROWG_TEST_API DEVINST eject_device(_In_z_ const char *instance);
#endif /* defined(_WIN32) */


#if defined(_WIN32)
/// <summary>
/// Derives the Windows device instance ID from the VISA path of the given
/// instrument.
/// <summary>
/// <param name="inst">The instrument to get the instance ID for.</param>
/// <return>The instance ID of the given instrument.</returns>
/// <exception cref="std::runtime_error">If the instance ID cannot be derived from
/// the VISA path of the given instrument, which could be because the instrument
/// is invalid or not connected via USB.</exception>
PWROWG_TEST_API std::string get_instance_id(_In_ const visa_instrument& inst);
#endif /* defined(_WIN32) */


/// <summary>
/// Programmatically ejects the USB device with the given instance ID and forces
/// its parent to re-enumerate instances.
/// </summary>
/// <param name="instance">The instance ID to eject and reconnect via its
/// parent.</param>
PWROWG_TEST_API void reset_usb_device(_In_z_ const char *instance);

PWROWG_DETAIL_NAMESPACE_END
