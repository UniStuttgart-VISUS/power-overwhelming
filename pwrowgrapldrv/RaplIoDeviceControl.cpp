// <copyright file="RaplIoDeviceControl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <ntddk.h>
#include <wdf.h>

#include "RaplDriver.h"


// Retrieves all RAPL registers that are valid for the CPU core that has been
// opened via the file object.
#define IOCTL_RAPL_REGISTERS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_READ_DATA)


/// <summary>
/// Fulfils <c>IOCTL_RAPL_REGISTERS</c>.
/// </summary>
static void IoctlRaplRegisters(
        _In_ WDFQUEUE queue,
        _In_ WDFREQUEST request,
        _In_ const SIZE_T cntOut,
        _In_ const SIZE_T cntIn,
        _In_ const RAPL_FILE_CONTEXT *context) {
    UNREFERENCED_PARAMETER(queue);
    UNREFERENCED_PARAMETER(cntOut);
    UNREFERENCED_PARAMETER(cntIn);
    ASSERT(context != nullptr);

    constexpr auto MSR_SIZE = sizeof(RAPL_FILE_CONTEXT::Msrs[0]);
    SIZE_T bytesReturned = 0;
    SIZE_T cntOutput = 0;
    void *output = nullptr;
    NTSTATUS status = (context != nullptr)
        ? STATUS_SUCCESS
        : STATUS_INVALID_PARAMETER_6;

    if (NT_SUCCESS(status)) {
        status = ::WdfRequestRetrieveOutputBuffer(request, MSR_SIZE,
            &output, &cntOutput);
        KdPrint(("[PWROWG] IOCTL_RAPL_REGISTERS retrieve output buffer result: "
            "0x%x\r\n", status));
    }

    if (NT_SUCCESS(status)) {
        if ((context->Msrs == nullptr) || (context->CountMsrs < 1)) {
            KdPrint(("[PWROWG] IOCTL_RAPL_REGISTERS found no MSRs in the file "
                "context. This is the case if all MSRs are allowed.\r\n"));
            status = STATUS_INVALID_DEVICE_STATE;
        }
    }

    if (NT_SUCCESS(status) && (cntOutput < MSR_SIZE)) {
        KdPrint(("[PWROWG] IOCTL_RAPL_REGISTERS must be able to return at "
            "least one register, but output buffer is %Iu Bytes, which is less "
            "than %Iu\r\n", cntOutput, MSR_SIZE));
        status = STATUS_BUFFER_TOO_SMALL;
    }

    if (NT_SUCCESS(status)) {
        // Compute required buffer size.
        bytesReturned = context->CountMsrs * MSR_SIZE;

        if (bytesReturned > cntOutput) {
            KdPrint(("[PWROWG] IOCTL_RAPL_REGISTERS requires an output buffer "
                "of %Iu Bytes for %Iu registers, but got %Iu Bytes.\r\n",
                bytesReturned, context->CountMsrs, cntOutput));
            bytesReturned = cntOutput / MSR_SIZE;
            ASSERT(bytesReturned > 0);
            bytesReturned *= MSR_SIZE;
            status = STATUS_BUFFER_TOO_SMALL;
        }
        ASSERT(bytesReturned % MSR_SIZE == 0);
        ASSERT(bytesReturned <= cntOutput);

        ::RtlZeroMemory(output, cntOutput);
        ::RtlCopyBytes(output, context->Msrs, bytesReturned);
    }

    // We are done. Make sure to return how much information we returned.
    KdPrint(("[PWROWG] Complete IOCTL_RAPL_REGISTERS with 0x%x.\r\n", status));
    if (NT_SUCCESS(status)) {
        ASSERT(bytesReturned > 0);
        ::WdfRequestCompleteWithInformation(request, status, bytesReturned);
    } else {
        ::WdfRequestComplete(request, status);
    }
}


/// <summary>
/// Fulfil an I/O control request.
/// </summary>
/// <param name="queue"></param>
/// <param name="request"></param>
/// <param name="cntOut"></param>
/// <param name="cntIn"></param>
/// <param name="ioctlCode"></param>
extern "C" void RaplIoDeviceControl(
        _In_ WDFQUEUE queue,
        _In_ WDFREQUEST request,
        _In_ SIZE_T cntOut,
        _In_ SIZE_T cntIn,
        _In_ ULONG code) {
    // Retrieve our context to get the core and the information about which
    // RAPL registers are available on the hardware.
    const auto file = ::WdfRequestGetFileObject(request);
    ASSERT(file != nullptr);
    const auto context = ::GetRaplFileContext(file);
    ASSERT(context != nullptr);

    // Process the I/O control code, which will handle request completion using
    // WDF on its own. Only unsupported code must be handled here.
    switch (code) {
        case IOCTL_RAPL_REGISTERS:
            KdPrint(("[PWROWG] Process IOCTL_RAPL_REGISTERS.\r\n"));
            ::IoctlRaplRegisters(queue, request, cntOut, cntIn, context);
            break;

        default:
            KdPrint(("[PWROWG] Unknown IOCTL code 0x%x.\r\n", code));
            ::WdfRequestComplete(request, STATUS_INVALID_DEVICE_REQUEST);
            break;
    }
}
