// <copyright file="DriverEntry.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <ntddk.h>
#include <wdmsec.h>

#include "RaplDriver.h"
#include "RaplRegistry.h"


#if defined(ALLOC_PRAGMA)
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, RaplCleanup)
#pragma alloc_text(PAGE, RaplClose)
#pragma alloc_text(PAGE, RaplCreate)
#pragma alloc_text(PAGE, RaplDeviceAdd)
#pragma alloc_text(PAGE, RaplDriverUnload)
#pragma alloc_text(PAGE, RaplRead)
#pragma alloc_text(PAGE, RaplShutdown)
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
    WDFDRIVER driver = nullptr;
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

    // Furthermore, add a global state to the driver object that can hold
    // configuration data we obtained from the registry and need to pass on
    // to the devices.
    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&attributes, RAPL_DRIVER_CONTEXT);

    if (NT_SUCCESS(status)) {
        status = ::WdfDriverCreate(driverObject, registryPath, &attributes,
            &config, &driver);
    }
    KdPrint(("[PWROWG] WdfDriverCreate result: 0x%x\r\n", status));

    // Initialise the context.
    if (NT_SUCCESS(status)) {
        auto context = ::GetRaplDriverContext(driver);
        ASSERT(context != nullptr);

        // Note: reading the AllowAllMsrs flag from the registry is a non-fatal
        // error. If we cannot read it, we just disable it, because this is
        // the reasonable default.
        {
            DECLARE_CONST_UNICODE_STRING(n, L"AllowAllMsrs");
            ULONG v = 0;
            if (NT_SUCCESS(::RaplQueryRegistryParameterUlong(v, driver, n))) {
                KdPrint(("[PWROWG] AllowAllMsrs parameter is: %d\r\n", v));
                context->AllowAllMsrs = (v != 0);

            } else {
                KdPrint(("[PWROWG] Defaulting to AllowAllMsrs = false\r\n"));
                context->AllowAllMsrs = false;
            }
        }
    }

    // TODO: configure tracing
    //if (NT_SUCCESS(status)) {
    //    WPP_INIT_TRACING(driverObject, registryPath);
    //}

    //TraceEvents(TRACE_LEVEL_VERBOSE, DBG_INIT,
    //    "Driver Frameworks NONPNP Legacy Driver Example");

    if (NT_SUCCESS(status)) {
        if ((deviceInit = ::WdfControlDeviceInitAllocate(driver,
                &SDDL_DEVOBJ_SYS_ALL_ADM_RWX_WORLD_RW_RES_R))
                == nullptr) {
            status = STATUS_INSUFFICIENT_RESOURCES;
        }
    }
    KdPrint(("[PWROWG] WdfControlDeviceInitAllocate result: 0x%x\r\n", status));

    if (NT_SUCCESS(status)) {
        // Manually add our device, because the framework will not call us as
        // we have disabled PNP.
        status = ::RaplDeviceAdd(driver, deviceInit);
    }

    KdPrint(("[PWROWG] DriverEntry exit with 0x%x\r\n", status));
    return status;
}
