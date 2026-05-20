// <copyright file="nvapi.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROVRNVAPI_NVAPI_H)
#define _PWROVRNVAPI_NVAPI_H
#pragma once

#include <stdlib.h>

#include <nvapi.h>

#if (defined(PWROVRNVAPI_EXPORTS) || defined(pwrovrnvapi_EXPORTS))
#define PWROVRNVAPI_API __declspec(dllexport)
#else /* (defined(PWROVRNVAPI_EXPORTS) || defined(pwrovrnvapi_EXPORTS)) */
#define PWROVRNVAPI_API __declspec(dllimport)
#endif /* (defined(PWROVRNVAPI_EXPORTS) || defined(pwrovrnvapi_EXPORTS)) */


#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

/// <summary>
/// Calls <see cref="NvAPI_EnumPhysicalGPUs" />.
/// </summary>
/// <param name="dst">A buffer of at least <c>NVAPI_MAX_PHYSICAL_GPUS</c>
/// elements.</param>
/// <param name="cnt">A pointer to a variable that receives the number of handles
/// actually written to <paramref name="dst" />.</param>
/// <returns>A status code indicating whether the operation was successful.
/// </returns>
PWROVRNVAPI_API NvAPI_Status nvapi_enumerate_physical_gpus(
    _Out_writes_(NVAPI_MAX_PHYSICAL_GPUS) NvPhysicalGpuHandle *dst,
    _Out_ NvU32 *cnt);

/// <summary>
/// Calls <see cref="NvAPI_Unload" />.
/// </summary>
/// <returns>A status code indicating whether the operation was successful.
/// </returns>
PWROVRNVAPI_API NvAPI_Status nvapi_finalise(void);

/// <summary>
/// Gets, if possible, a human-readable error message for the given status code
/// by calling <see cref="NvAPI_GetErrorMessage" />.
/// </summary>
/// <param name="dst"></param>
/// <param name="status"></param>
/// <returns>A status code indicating whether the operation was successful.
/// </returns>
PWROVRNVAPI_API NvAPI_Status nvapi_get_error_message(
    _Out_ NvAPI_ShortString dst,
    _In_ NvAPI_Status status);

/// <summary>
/// Calls <see cref="NvAPI_GPU_GetBusId" /> to get the bus ID of the GPU
/// associated with the given handle.
/// </summary>
/// <param name="handle">A handle for a physical GPU.</param>
/// <returns>A status code indicating whether the operation was successful.
/// </returns>
PWROVRNVAPI_API NvAPI_Status nvapi_get_gpu_bus_id(
    _Out_ NvU32 *dst,
    _In_ NvPhysicalGpuHandle handle);

/// <summary>
/// Calls <see cref="NvAPI_GetPhysicalGPUFromGPUID" /> to get a handle for the
/// GPU with the given ID.
/// </summary>
/// <param name="id"></param>
/// <returns>A status code indicating whether the operation was successful.
/// </returns>
PWROVRNVAPI_API NvAPI_Status nvapi_get_gpu_from_id(
    _Out_ NvPhysicalGpuHandle *dst,
    _In_ NvU32 id);

/// <summary>
/// Calls <see cref="NvAPI_GetGPUIDfromPhysicalGPU" /> to get the GPU ID of the
/// GPU associated with the given handle.
/// </summary>
/// <param name="handle">A handle for a physical GPU.</param>
/// <returns>A status code indicating whether the operation was successful.
/// </returns>
PWROVRNVAPI_API NvAPI_Status nvapi_get_gpu_id(
    _Out_ NvU32 *dst,
    _In_ NvPhysicalGpuHandle handle);

/// <summary>
/// Calls <see cref="NvAPI_GPU_GetFullName" /> to get the name of the GPU
/// associated with the given handle.
/// </summary>
/// <param name="dst">A buffer to receive the name of the GPU.</param>
/// <param name="handle">A handle for a physical GPU.</param>
/// <returns>A status code indicating whether the operation was successful.
/// </returns>
PWROVRNVAPI_API NvAPI_Status nvapi_get_gpu_name(
    _Out_writes_(NVAPI_SHORT_STRING_MAX) NvAPI_ShortString dst,
    _In_ NvPhysicalGpuHandle handle);

/// <summary>
/// Calls <see cref="NvAPI_GPU_GetPCIIdentifiers" /> to get the PCI identifiers
/// of the GPU associated with the given handle.
/// </summary>
/// <param name="device_id">Receives the device ID.</param>
/// <param name="sub_system_id">Receives the sub-system ID.</param>
/// <param name="revision_id">Receives the revision ID.</param>
/// <param name="ext_device_id">Receives the extended device ID.</param>
/// <param name="handle">A handloe for a physical GPU.</param>
/// <returns>A status code indicating whether the operation was successful.
/// </returns>
PWROVRNVAPI_API NvAPI_Status nvapi_get_gpu_pci_identifiers(
    _Out_ NvU32 *device_id,
    _Out_ NvU32 *sub_system_id,
    _Out_ NvU32 *revision_id,
    _Out_ NvU32 *ext_device_id,
    _In_ NvPhysicalGpuHandle handle);

/// <summary>
/// Calls <see cref="NvAPI_Initialize" />.
/// </summary>
/// <returns>A status code indicating whether the operation was successful.
/// </returns>
PWROVRNVAPI_API NvAPI_Status nvapi_initialise(void);

/// <summary>
/// Registers a callback for periodic power updates by calling
/// <see cref="NvAPI_GPU_ClientRegisterForPowerSampleUpdates" />.
/// </summary>
/// <param name="handle"></param>
/// <param name="settings"></param>
/// <returns>A status code indicating whether the operation was successful.
/// </returns>
PWROVRNVAPI_API NvAPI_Status nvapi_register_power_callback(
    _In_ NvPhysicalGpuHandle handle, 
    _In_ NV_GPU_CLIENT_POWER_PERIODIC_CALLBACK_SETTINGS *settings);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_PWROVRNVAPI_NVAPI_H) */
