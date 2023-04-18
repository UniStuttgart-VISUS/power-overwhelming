// <copyright file="rapl_close.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include <ntddk.h>


/// <summary>
/// Entry point for a close request.
/// </summary>
/// <param name="device"></param>
/// <param name="irp"></param>
/// <returns><c>STATUS_SUCCESS</c> if the operation succeeded, an error code
/// otherwise.</returns>
_Function_class_(IRP_MJ_CLOSE)
_Function_class_(DRIVER_DISPATCH)
NTSTATUS __cdecl rapl_close(_In_ PDEVICE_OBJECT device, _Inout_ PIRP irp) {
    ASSERT(irp != nullptr);
    NTSTATUS status = STATUS_SUCCESS;

    if (NT_SUCCESS(status)) {
        irp->IoStatus.Status = STATUS_SUCCESS;
        irp->IoStatus.Information = STATUS_SUCCESS;
        ::IofCompleteRequest(irp, IO_NO_INCREMENT);
    }

    return status;
}
