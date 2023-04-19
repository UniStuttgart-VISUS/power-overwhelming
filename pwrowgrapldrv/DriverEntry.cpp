// <copyright file="driver_entry.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include <ntddk.h>
#include <wdmsec.h>

#include "RaplDriver.h"


#if defined(ALLOC_PRAGMA)
#pragma alloc_text( INIT, DriverEntry)
#pragma alloc_text( PAGE, RaplCleanup)
#pragma alloc_text( PAGE, RaplClose)
#pragma alloc_text( PAGE, RaplCreate)
#pragma alloc_text( PAGE, RaplDeviceAdd)
#pragma alloc_text( PAGE, RaplDriverUnload)
#pragma alloc_text( PAGE, RaplRead)
#pragma alloc_text( PAGE, RaplShutdown)
#endif /* defined(ALLOC_PRAGMA) */


/// <summary>
/// Initialises the driver on request by the operating system.
/// </summary>
/// <param name="driverObject"></param>
/// <param name="registryPath"></param>
/// <returns><c>STATUS_SUCCESS</c> if the operation succeeded, an error code
/// otherwise.</returns>
extern "C" NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT driverObject,
        _In_ PUNICODE_STRING registryPath) noexcept {
    WDF_OBJECT_ATTRIBUTES attributes { 0 };
    WDF_DRIVER_CONFIG config { 0 };
    PWDFDEVICE_INIT deviceInit = nullptr;
    WDFDRIVER hDriver = NULL;
    NTSTATUS status = STATUS_SUCCESS;

    KdPrint(("[PWROWG] DriverEntry enter\r\n"));

    // Prepare the configuration. Most importanly, tell the framework that this
    // is a non-pop driver, which effectively disables RaplDeviceAdd.
    WDF_DRIVER_CONFIG_INIT(&config, WDF_NO_EVENT_CALLBACK);
    config.DriverInitFlags |= WdfDriverInitNonPnpDriver;
    config.EvtDriverUnload = ::RaplDriverUnload;

    // Register a callback that notifies us about the driver object being
    // cleaned up.
    WDF_OBJECT_ATTRIBUTES_INIT(&attributes);
    attributes.EvtCleanupCallback = ::RaplCleanup;


    if (NT_SUCCESS(status)) {
        status = ::WdfDriverCreate(driverObject, registryPath, &attributes,
            &config, &hDriver);
    }
    KdPrint(("[PWROWG] WdfDriverCreate result: 0x%x\r\n", status));

    // TODO: configure tracing
    //if (NT_SUCCESS(status)) {
    //    WPP_INIT_TRACING(driverObject, registryPath);
    //}

    //TraceEvents(TRACE_LEVEL_VERBOSE, DBG_INIT,
    //    "Driver Frameworks NONPNP Legacy Driver Example");

    if (NT_SUCCESS(status)) {
        if ((deviceInit = ::WdfControlDeviceInitAllocate(hDriver,
                &SDDL_DEVOBJ_SYS_ALL_ADM_RWX_WORLD_RW_RES_R))
                == nullptr) {
            status = STATUS_INSUFFICIENT_RESOURCES;
        }
    }
    KdPrint(("[PWROWG] WdfControlDeviceInitAllocate result: 0x%x\r\n", status));

    if (NT_SUCCESS(status)) {
        // Manually add our device, because the framework will not call us as
        // we have disabled PNP.
        status = ::RaplDeviceAdd(hDriver, deviceInit);
    }

    KdPrint(("[PWROWG] DriverEntry exit with 0x%x\r\n", status));
    return status;
}
