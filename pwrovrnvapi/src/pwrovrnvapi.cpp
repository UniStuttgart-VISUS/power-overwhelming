// <copyright file="nvapi.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pwrovrnvapi.h"

#include <nvapi.h>


/*
 * ::nvapi_enumerate_physical_gpus
 */
NvAPI_Status nvapi_enumerate_physical_gpus(
        _Out_writes_(NVAPI_MAX_PHYSICAL_GPUS) NvPhysicalGpuHandle *dst,
        _Out_ NvU32 *cnt) {
    return ::NvAPI_EnumPhysicalGPUs(dst, cnt);
}


/*
 * ::nvapi_finalise
 */
NvAPI_Status nvapi_finalise(void) {
    return ::NvAPI_Unload();
}


/*
 * nvapi_get_error_message
 */
NvAPI_Status nvapi_get_error_message(
        _Out_ NvAPI_ShortString dst,
        _In_ NvAPI_Status status) {
    return ::NvAPI_GetErrorMessage(status, dst);
}


/*
 * ::nvapi_get_gpu_bus_id
 */
NvAPI_Status nvapi_get_gpu_bus_id(
        _Out_ NvU32 *dst,
        _In_ NvPhysicalGpuHandle handle) {
    return ::NvAPI_GPU_GetBusId(handle, dst);
}


/*
 * ::nvapi_get_gpu_name
 */
NvAPI_Status nvapi_get_gpu_name(
        _Out_writes_(NVAPI_SHORT_STRING_MAX) NvAPI_ShortString dst,
        _In_ NvPhysicalGpuHandle handle) {
    return ::NvAPI_GPU_GetFullName(handle, dst);
}


/*
 * ::nvapi_get_gpu_pci_identifiers
 */
NvAPI_Status nvapi_get_gpu_pci_identifiers(_Out_ NvU32 *device_id,
        _Out_ NvU32 *sub_system_id,
        _Out_ NvU32 *revision_id,
        _Out_ NvU32 *ext_device_id,
        _In_ NvPhysicalGpuHandle handle) {
    return ::NvAPI_GPU_GetPCIIdentifiers(handle, device_id,
        sub_system_id, revision_id, ext_device_id);
}


/*
 * nvapi_get_gpu_slot_id
 */
NvAPI_Status nvapi_get_gpu_slot_id(
        _Out_ NvU32 *dst,
        _In_ NvPhysicalGpuHandle handle) {
    return ::NvAPI_GPU_GetBusSlotId(handle, dst);
}


/*
 * ::nvapi_initialise
 */
NvAPI_Status nvapi_initialise(void) {
    return ::NvAPI_Initialize();
}


/*
 * ::nvapi_register_power_callback
 */
NvAPI_Status nvapi_register_power_callback(
        _In_ NvPhysicalGpuHandle handle,
        _In_ NV_GPU_CLIENT_POWER_PERIODIC_CALLBACK_SETTINGS *settings) {
    return ::NvAPI_GPU_ClientRegisterForPowerSampleUpdates(handle, settings);
}
