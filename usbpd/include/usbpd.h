// <copyright file="usbpd.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_USBPD_H)
#define _USBPD_H
#pragma once

#include <cinttypes>
#include <cstdlib>


#if defined(_WIN32)
#if defined(USBPD_EXPORTS)
#define USBPD_API __declspec(dllexport)
#else /* defined(USBPD_EXPORTS) */
#define USBPD_API __declspec(dllimport)
#endif /* defined(USBPD_EXPORTS) */

#else /* defined(_WIN32) */
#define USBPD_API
#endif /* defined(_WIN32) */


/// <summary>
/// An opaque handle for a Passmark USB-PD tester device.
/// </summary>
typedef class PDTester *usb_pd_tester;


/// <summary>
/// Closes a connection toa USB-PD tester.
/// </summary>
/// <param name="tester">A handle for the tester to be closed. It is safe to
/// pass <c>nullptr</c>, in which case nothing will happen.</param>
extern "C" USBPD_API void usb_pd_tester_close(usb_pd_tester tester);

/// <summary>
/// Enumerates all Passmark USB-PD testers connected to the system and answer
/// their paths in the multi-sz format used by the Windows registry.
/// </summary>
/// <remarks>
/// <para>Rationale: The API allocates the required memory by itself and
/// requires the user to free it rather than requesting a caller-allocated
/// buffer, because the enumeration of devices is slow and to some extent not
/// very reliable. Therefore, we want to prevent double enumerations by this API
/// design.</para>
/// </remarks>
/// <param name="timeout">A timeout for the enumeration of the devices, in
/// milliseconds.</param>
/// <param name="wait">A waiting time, in milliseconds, that the API should stop
/// enumerating the devices if it failed to retrieve anything before trying
/// again. The sample by Passmark uses 100 ms for that.</param>
/// <returns>A buffer holding the paths of the devices. The caller must free
/// the memory using <see cref="usb_pd_tester_free" />. If no device was found,
/// the return value is <c>nullptr</c>.</returns>
extern "C" USBPD_API char *usb_pd_tester_enumerate(const std::int64_t timeout,
    const std::int64_t wait);

/// <summary>
/// Frees a buffer that has been allocated by the API.
/// </summary>
/// <param name="dst"></param>
/// <returns></returns>
extern "C" USBPD_API void usb_pd_tester_free(char *dst);

/// <summary>
/// Opens the given Passmark USB-PD tester.
/// </summary>
/// <param name="path">The path to the device to be opened. This path can be
/// obtained from <see cref="usb_pd_testers_enumerate" />.</param>
/// <returns>A handle for the device or <c>nullptr</c> if the
/// <paramref name="path" /> does not designate a valid device. The caller must
/// close this handle using <see cref="usb_pd_tester_close" />.</returns>
extern "C" USBPD_API usb_pd_tester usb_pd_tester_open(const char *path);

/// <summary>
/// Queries the current statistics from the given <paramref name="tester" />.
/// </summary>
/// <param name="tester">The handle for the device to query.</param>
/// <param name="temperature">Receives the current internal temperature in
/// degrees Celsius.</param>
/// <param name="voltage">Receives the current voltage in millivolts.</param>
/// <param name="set_current">Receives the current in milliamperes that has been
/// set as load for the device under test.</param>
/// <param name="current">Receives the current in milliamperes.</param>
/// <param name="loopback_current">Receives the loopback current in
/// milliamperes.</param>
/// <returns><c>true</c> in case the returned values are valid, <c>false</c>
/// otherwise.</returns>
extern "C" USBPD_API bool usb_pd_tester_query(usb_pd_tester tester,
    std::uint8_t *temperature,
    std::uint16_t *voltage,
    std::uint16_t *set_current,
    std::uint16_t *current,
    std::uint16_t *loopback_current);

#endif /* !defined(_USBPD_H) */
