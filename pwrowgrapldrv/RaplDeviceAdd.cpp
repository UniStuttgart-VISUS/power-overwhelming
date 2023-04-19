// <copyright file="RaplDeviceAdd.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "RaplDriver.h"


/// <summary>
/// This function is called by <see cref="DriverEntry" /> to create a control device.
/// </summary>
/// <param name="driver"></param>
/// <param name="deviceInit"></param>
/// <returns></returns>
extern "C" NTSTATUS RaplDeviceAdd(_In_ WDFDRIVER driver,
        _In_ PWDFDEVICE_INIT deviceInit) noexcept {
    UNREFERENCED_PARAMETER(driver);
    PAGED_CODE();

    WDF_OBJECT_ATTRIBUTES attributes { 0 };
    WDFDEVICE controlDevice = nullptr;
    WDFQUEUE queue = nullptr;
    NTSTATUS status = STATUS_SUCCESS;

    DECLARE_CONST_UNICODE_STRING(ntDeviceName, RaplDeviceName);
    DECLARE_CONST_UNICODE_STRING(symbolicLinkName, RaplVisibleDeviceName);

    //TraceEvents(TRACE_LEVEL_VERBOSE, DBG_INIT,
    //    "NonPnpDeviceAdd DeviceInit %p\n", DeviceInit);

    // Set exclusive to TRUE so that no more than one app can talk to the
    // control device at any time.
    // ::WdfDeviceInitSetExclusive(deviceInit, TRUE);

    if (NT_SUCCESS(status)) {
        ::WdfDeviceInitSetIoType(deviceInit, WdfDeviceIoDirect);
    }

    if (NT_SUCCESS(status)) {
        status = ::WdfDeviceInitAssignName(deviceInit, &ntDeviceName);
    }

    if (NT_SUCCESS(status)) {
        ::WdfControlDeviceInitSetShutdownNotification(deviceInit,
            ::RaplShutdown, WdfDeviceShutdown);
    }

    if (NT_SUCCESS(status)) {
        WDF_OBJECT_ATTRIBUTES fileAttributes { 0 };
        WDF_FILEOBJECT_CONFIG fileConfig { 0 };
        ::WDF_OBJECT_ATTRIBUTES_INIT(&fileAttributes);
        WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&fileAttributes,
            RAPL_FILE_CONTEXT);
        ::WDF_FILEOBJECT_CONFIG_INIT(&fileConfig, ::RaplCreate, ::RaplClose,
            WDF_NO_EVENT_CALLBACK);
        ::WdfDeviceInitSetFileObjectConfig(deviceInit, &fileConfig,
            &fileAttributes);
    }

    ////
    //// In order to support METHOD_NEITHER Device controls, or
    //// NEITHER device I/O type, we need to register for the
    //// EvtDeviceIoInProcessContext callback so that we can handle the request
    //// in the calling threads context.
    ////
    //WdfDeviceInitSetIoInCallerContextCallback(DeviceInit,
    //    NonPnpEvtDeviceIoInCallerContext);

    if (NT_SUCCESS(status)) {
        ::WDF_OBJECT_ATTRIBUTES_INIT(&attributes);
    }

    // We don't need a per-device context.
    //if (NT_SUCCESS(status)) {
    //    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&attributes,
    //        RAPL_CONTROL_DEVICE);
    //}

    if (NT_SUCCESS(status)) {
        status = ::WdfDeviceCreate(&deviceInit, &attributes, &controlDevice);
    }
    
    if (NT_SUCCESS(status)) {
        // Create a symbolic link for the control object so that usermode can
        // open the device.
        status =:: WdfDeviceCreateSymbolicLink(controlDevice,
            &symbolicLinkName);
    }

    if (NT_SUCCESS(status)) {
        WDF_IO_QUEUE_CONFIG ioQueueConfig{ 0 };
        WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&ioQueueConfig,
            WdfIoQueueDispatchSequential);
        ioQueueConfig.EvtIoRead = ::RaplRead;

        WDF_OBJECT_ATTRIBUTES_INIT(&attributes);
        // When reading the MSRs, we need to set the thread affinity to the
        // correct core to make sure that we read the right register. This
        // operation is only effective immediately at passive level, so we ask
        // the framework to call us only on passive level.
        attributes.ExecutionLevel = WdfExecutionLevelPassive;

        // By default, Static Driver Verifier (SDV) displays a warning if it
        // doesn nott find the EvtIoStop callback on a power-managed queue.
        // The 'assume' below causes SDV to suppress this warning. If the driver
        // has not explicitly set PowerManaged to WdfFalse, the framework
        // creates power-managed queues when the device is not a filter driver.
        // Normally the EvtIoStop is required for power-managed queues, but for
        // this driver it is not needed because the driver does not hold on to
        // the requests or forwards them to other drivers. This driver completes
        // all requests directly in the queue's handlers. If the EvtIoStop
        // callback is not implemented, the framework waits for all driver-owned
        // requests to be done before moving in the Dx/sleep states or before
        // removing the device, which is the correct behaviour for this type of
        // driver.
        __analysis_assume(ioQueueConfig.EvtIoStop != 0);
        status = ::WdfIoQueueCreate(controlDevice, &ioQueueConfig, &attributes,
            &queue);
        __analysis_assume(ioQueueConfig.EvtIoStop == 0);
    }

    if (NT_SUCCESS(status)) {
        // Notify the framework that we are done.
        ::WdfControlFinishInitializing(controlDevice);
    }

    if (deviceInit != nullptr) {
        // If the framework has not cleared the initialisation value, we must do
        // so.
        ::WdfDeviceInitFree(deviceInit);
    }

    return status;
}
