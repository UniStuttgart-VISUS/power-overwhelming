// <copyright file="driver_entry.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include <ntddk.h>
#include <sal.h>


/* The name of our device. */
#define RaplDeviceName L""
#define RaplVisibleDeviceName L""


/* Forward declarations. */
extern "C" NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT driver_object,
    _In_ PUNICODE_STRING registry_path);

_Function_class_(DRIVER_UNLOAD)
void rapl_unload(_In_ PDRIVER_OBJECT driver_object);

_Function_class_(IRP_MJ_CLEANUP)
_Function_class_(DRIVER_DISPATCH)
extern NTSTATUS __cdecl rapl_cleanup(_In_ PDEVICE_OBJECT device,
    _Inout_ PIRP irp);

_Function_class_(IRP_MJ_CLOSE)
_Function_class_(DRIVER_DISPATCH)
extern NTSTATUS rapl_close(_In_ PDEVICE_OBJECT device, _Inout_ PIRP irp);

_IRQL_requires_min_(PASSIVE_LEVEL)
_IRQL_requires_max_(APC_LEVEL)
_Function_class_(IRP_MJ_CREATE)
_Function_class_(DRIVER_DISPATCH)
extern NTSTATUS rapl_create(_In_ PDEVICE_OBJECT device, _Inout_ PIRP irp);

_Function_class_(IRP_MJ_READ)
_Function_class_(DRIVER_DISPATCH)
_IRQL_requires_max_(APC_LEVEL)
extern NTSTATUS rapl_read(_In_ PDEVICE_OBJECT device, _Inout_ PIRP irp);


#if defined(ALLOC_PRAGMA)
#pragma alloc_text(INIT, DriverEntry)
#endif  defined(ALLOC_PRAGMA)


/// <summary>
/// Entry point of the driver.
/// </summary>
/// <param name="driver_object"></param>
/// <param name="registry_path"></param>
/// <returns><c>STATUS_SUCCESS</c> if the operation succeeded, an error code
/// otherwise.</returns>
extern "C" NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT driver_object,
        _In_ PUNICODE_STRING registry_path) {
    ASSERT(driver_object != nullptr);
    UNREFERENCED_PARAMETER(registry_path);

    UNICODE_STRING device_name;
    PDEVICE_OBJECT device_object;
    NTSTATUS status = STATUS_SUCCESS;
    UNICODE_STRING user_visible_device_name;

    driver_object->DriverUnload = ::rapl_unload;
    driver_object->MajorFunction[IRP_MJ_CREATE] = ::rapl_create;
    driver_object->MajorFunction[IRP_MJ_READ] = ::rapl_read;
    driver_object->MajorFunction[IRP_MJ_CLOSE] = ::rapl_close;
    driver_object->MajorFunction[IRP_MJ_CLEANUP] = ::rapl_cleanup;

    ::RtlInitUnicodeString(&device_name, RaplDeviceName);
    ::RtlInitUnicodeString(&user_visible_device_name, RaplVisibleDeviceName);

    if (NT_SUCCESS(status)) {
        status = ::IoCreateDevice(driver_object, 0, &device_name,
            FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE,
            &device_object);
    }

    if (NT_SUCCESS(status)) {
         ::IoCreateSymbolicLink(&user_visible_device_name, &device_name);
    }

    return status;
}


/// <summary>
/// Unloads the driver
/// </summary>
/// <param name="driver_object"></param>
_Function_class_(DRIVER_UNLOAD)
void rapl_unload(_In_ PDRIVER_OBJECT driver_object) {
    ASSERT(driver_object != nullptr);

    UNICODE_STRING user_visible_device_name;
    ::RtlInitUnicodeString(&user_visible_device_name, RaplVisibleDeviceName);
    ::IoDeleteSymbolicLink(&user_visible_device_name);

    ::IoDeleteDevice(driver_object->DeviceObject);
}
