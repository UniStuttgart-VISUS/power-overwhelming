// <copyright file="RaplIoDeviceControl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <ntddk.h>
#include <wdf.h>


/// <summary>
/// Fulfil an I/O control request.
/// </summary>
/// <param name="queue"></param>
/// <param name="request"></param>
/// <param name="cntOut"></param>
/// <param name="cntIn"></param>
/// <param name="ioctlCode"></param>
_IRQL_requires_same_
_IRQL_requires_max_(DISPATCH_LEVEL)
extern "C" void RaplIoDeviceControl(_In_ WDFQUEUE queue,
        _In_ WDFREQUEST request,
        _In_ SIZE_T cntOut,
        _In_ SIZE_T cntIn,
        _In_ ULONG code) {
    UNREFERENCED_PARAMETER(queue);

    // TODO: remove this.
    ::WdfRequestComplete(request, STATUS_NOT_IMPLEMENTED);
    return;

    void *input = nullptr;
    void *output = nullptr;
    NTSTATUS status = STATUS_SUCCESS;
    size_t bufSize = 0;

    if (NT_SUCCESS(status)) {
        status = ::WdfRequestRetrieveInputBuffer(request, sizeof(ULONG),
            &input, &cntIn);
        KdPrint(("[PWROWG] IOCTL retrieve input buffer result: 0x%x\r\n",
            status));
    }

    if (NT_SUCCESS(status)) {
        status = ::WdfRequestRetrieveOutputBuffer(request, sizeof(ULONG),
            &output, &cntOut);
        KdPrint(("[PWROWG] IOCTL retrieve output buffer result: 0x%x\r\n",
            status));
    }

    if (NT_SUCCESS(status)) {
        switch (code) {}
        // TODO: think about the data structure for this.
    }

    // We are done. Make sure to return how much information we returned.
    KdPrint(("[PWROWG] Complete open with 0x%x\r\n", status));
    if (NT_SUCCESS(status)) {
        ::WdfRequestCompleteWithInformation(request, status, 0);// TODO
    } else {
        ::WdfRequestComplete(request, status);
    }
}
