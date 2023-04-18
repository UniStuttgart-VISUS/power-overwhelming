// <copyright file="rapl_read.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include <ntddk.h>


/// <summary>
/// The driver entry for the common read function initiated by
/// <c>NtReadFile</c>.
/// </summary>
/// <param name="device"></param>
/// <param name="irp"></param>
/// <returns><c>STATUS_SUCCESS</c> if the operation succeeded, an error code
/// otherwise.</returns>
_Function_class_(IRP_MJ_READ)
_Function_class_(DRIVER_DISPATCH)
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS rapl_read(_In_ PDEVICE_OBJECT device, _Inout_ PIRP irp) {
    // https://learn.microsoft.com/en-us/windows-hardware/drivers/ifs/irp-mj-read
    ASSERT(irp != nullptr);
    NTSTATUS status = STATUS_SUCCESS;
    return status;

    //IrpSp->Parameters.Read.ByteOffset is a LARGE_INTEGER variable that specifies the starting byte offset within the file of the data to be read.
    //https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-kesetsystemgroupaffinitythread
}

#if 0
NTSTATUS DispatchDeviceControl(PDEVICE_OBJECT device, PIRP irp)
{
    NTSTATUS ntStatus;
    UINT32 msrRegister;
    ULONG inputBufferLength;
    ULONG outputBufferLength;
    ULONGLONG msrResult;
    PIO_STACK_LOCATION stackLocation;

    stackLocation = irp->Tail.Overlay.CurrentStackLocation;
    inputBufferLength = stackLocation->Parameters.DeviceIoControl.InputBufferLength;
    outputBufferLength = stackLocation->Parameters.DeviceIoControl.OutputBufferLength;

    DbgPrint("Received event for driver %s... \n", device->DriverObject->DriverName);

    /* METHOD_BUFFERED */
    if (inputBufferLength == sizeof(ULONGLONG))
    {
        /* MSR register codes provided by userland must not exceed 8 bytes */
        memcpy(&msrRegister, irp->AssociatedIrp.SystemBuffer, sizeof(ULONGLONG));
        if (validate_msr_lookup(msrRegister) != 0)
        {
            DbgPrint("Requested MSR register (%08x) access is not allowed!\n", msrRegister);
            ntStatus = STATUS_INVALID_DEVICE_REQUEST;
        }
        else
        {
            /* Call readmsr instruction */
            msrResult = __readmsr(msrRegister);
            memcpy(irp->AssociatedIrp.SystemBuffer, &msrResult, sizeof(ULONGLONG));
            ntStatus = STATUS_SUCCESS;
            irp->IoStatus.Information = sizeof(ULONGLONG);
        }
    }
    else
    {
        DbgPrint("Bad input length provided. Expected %u bytes, got %u.\n", sizeof(ULONGLONG), inputBufferLength);
        ntStatus = STATUS_INVALID_DEVICE_REQUEST;
    }

    irp->IoStatus.Status = ntStatus;
    IofCompleteRequest(irp, IO_NO_INCREMENT);

    return ntStatus;
}
#endif