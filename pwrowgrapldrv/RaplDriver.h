// <copyright file="RaplDriver.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <ntddk.h>
#include <wdf.h>

#define NTSTRSAFE_LIB
#include <ntstrsafe.h>


/// <summary>
/// This block of custom data is attached to the root driver object.
/// </summary>
typedef struct _RAPL_DRIVER_CONTEXT {
    /// <summary>
    /// Indicates that MSR addresses should not be filtered by the driver, but
    /// just passed through as is.
    /// </summary>
    bool AllowAllMsrs;
} RAPL_DRIVER_CONTEXT, *PRAPL_DRIVER_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(RAPL_DRIVER_CONTEXT, GetRaplDriverContext)


/// <summary>
/// This is the block of custom data we attach to the device itself.
/// </summary>
typedef struct _RAPL_DEVICE_CONTEXT {
    /// <summary>
    /// Points to the custom data of the driver, which allows us to access
    /// driver-global information when working with a device.
    /// </summary>
    PRAPL_DRIVER_CONTEXT DriverContext;
} RAPL_DEVICE_CONTEXT, *PRAPL_DEVICE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(RAPL_DEVICE_CONTEXT, GetRaplDeviceContext)


/// <summary>
/// A context we attach to the file object we get from the KMDF, which allows us
/// restoring the thread affinity of the core which was requested in the call to
/// <see cref="RaplCreate" />.
/// </summary>
typedef struct _RAPL_FILE_CONTEXT {
    /// <summary>
    /// The core for which the MSR reads have been requested.
    /// </summary>
    __int32 Core;

    /// <summary>
    /// The number of MSRs we found valid for the specified core.
    /// </summary>
    /// <remarks>
    /// If this is zero and the context still exists, the read operation should
    /// not check the register, but assume the caller knows what he is doing.
    /// </remarks>
    SIZE_T CountMsrs;

    /// <summary>
    /// The register indices of the MSRs we found valid for the specified core.
    /// </summary>
    _Field_size_(CountMsrs) unsigned __int32 *Msrs;
} RAPL_FILE_CONTEXT, *PRAPL_FILE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(RAPL_FILE_CONTEXT, GetRaplFileContext)


/// <summary>
/// The memory pool tag we use for our own allocations.
/// </summary>
#define RAPL_POOL_TAG ('lpaR')


extern "C" DRIVER_INITIALIZE DriverEntry;
extern "C" EVT_WDF_DEVICE_CONTEXT_CLEANUP RaplCleanup;
extern "C" EVT_WDF_FILE_CLOSE RaplClose;
extern "C" EVT_WDF_DEVICE_FILE_CREATE RaplCreate;
// We should not declare this as EVT_WDF_DRIVER_DEVICE_ADD according to
// https://github.com/microsoft/Windows-driver-samples/blob/main/general/ioctl/kmdf/sys/nonpnp.h
extern "C" NTSTATUS RaplDeviceAdd(_In_ WDFDRIVER driver,
    _In_ PWDFDEVICE_INIT deviceInit);
extern "C" EVT_WDF_DRIVER_UNLOAD RaplDriverUnload;
extern "C" EVT_WDF_IO_QUEUE_IO_READ RaplRead;
extern "C" EVT_WDF_DEVICE_SHUTDOWN_NOTIFICATION RaplShutdown;
