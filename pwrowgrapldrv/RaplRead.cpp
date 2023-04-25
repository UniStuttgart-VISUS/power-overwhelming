// <copyright file="RaplRead.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include <intrin.h>
#include <ntddk.h>
#include <wdf.h>

#include "RaplDriver.h"
#include "RaplThreadAffinity.h"



/// <summary>
/// This event is called when the framework receives <c>IRP_MJ_READ</c>
/// requests. It uses the offset into the file object provided as the index
/// of the MSR to read and calls the <see cref="__readmsr" /> intrinsic for
/// it. The 64 bits read from it are the result of the read request.
/// </summary>
/// <param name="queue"></param>
/// <param name="request"></param>
/// <param name="length"></param>
/// <returns></returns>
extern "C" void RaplRead(_In_ WDFQUEUE queue, _In_ WDFREQUEST request,
        _In_ SIZE_T length) noexcept {
    ASSERT(request != nullptr);
    PAGED_CODE();

    SIZE_T bytesAvailable = 0;
    SIZE_T bytesRead = sizeof(unsigned __int64);
    PVOID output = nullptr;
    WDF_REQUEST_PARAMETERS parameters { 0 };
    GROUP_AFFINITY originalAffinity { 0 };
    NTSTATUS status = STATUS_SUCCESS;

    KdPrint(("[PWROWG] RaplRead enter\r\n"));

    // Retrieve our context to get the core and the information about which
    // RAPL registers are available on the hardware.
    const auto file = ::WdfRequestGetFileObject(request);
    ASSERT(file != nullptr);
    const auto context = ::GetRaplFileContext(file);
    ASSERT(context != nullptr);

    // Get the current file pointer from the file object.
    auto file_object = ::WdfFileObjectWdmGetFileObject(file);
    auto offset = file_object->CurrentByteOffset;
    //// Get the request parameters which hold the offset into the file, which we
    //// interpret as the register number,
    //::WdfRequestGetParameters(request, &parameters);
    //const auto offset = parameters.Parameters.Read.DeviceOffset;
    KdPrint(("[PWROWG] RAPL request offset 0x%I64x\r\n", offset.QuadPart));

    if (NT_SUCCESS(status) && (offset.HighPart != 0)) {
        // The offset is larger thatn 32-bit, so it cannot be a valid register.
        // We indicate invalid register addresses as end of file.
        KdPrint(("[PWROWG] Register 0x%I64x does not fit into 32 bits\r\n",
            offset.QuadPart));
        status = STATUS_END_OF_FILE;
    }

    // TODO: Check validity of register.
    const auto msrRegister = static_cast<unsigned long>(offset.QuadPart);

    // Retrieve the output buffer where we should put the data.
    if (NT_SUCCESS(status)) {
        status = ::WdfRequestRetrieveOutputBuffer(request, bytesRead, &output,
            &bytesAvailable);
    }

    // Set the thread affinity to the core that is represented by the file, thus
    // making sure that we read the MSR of the correct CPU. Furthermore,
    // remember the original thread affinity to restore it once we are done.
    if (NT_SUCCESS(status)) {
        status = ::RaplSetThreadAffinity(context->Core, &originalAffinity);
    }
    const auto restoreAffinity = NT_SUCCESS(status);

    // Read the register which is given by the offset in the file. This one line
    // is the only reason for this whole driver existing ...
    auto data = __readmsr(msrRegister);

    // Restore previous thread affinity.
    if (restoreAffinity) {
        ::KeSetSystemGroupAffinityThread(&originalAffinity, nullptr);
    }

    // Make sure that we do not write too much if the caller requested a partial
    // register (although this does not make sense) and return the data to the
    // output buffer.
    if (bytesRead > bytesAvailable) {
        KdPrint(("[PWROWG] Read too small for MSR register\r\n"));
        bytesRead = bytesAvailable;
    }

    ::RtlCopyBytes(output, &data, bytesRead);

    // We are done. Make sure to return how much we read if the operation did
    // succeed.
    KdPrint(("[PWROWG] Complete open with 0x%x\r\n", status));
    if (NT_SUCCESS(status)) {
        ::WdfRequestCompleteWithInformation(request, status, bytesRead);
    } else {
        ::WdfRequestComplete(request, status);
    }
}
