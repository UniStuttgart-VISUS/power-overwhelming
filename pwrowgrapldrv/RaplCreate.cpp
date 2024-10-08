﻿// <copyright file="RaplCreate.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <intrin.h>

#include "RaplCpuInfo.h"
#include "RaplDriver.h"
#include "RaplMsr.h"
#include "RaplString.h"
#include "RaplThreadAffinity.h"


/// <summary>
/// Retrieve all members of <see cref="RaplCpuInfo" /> for the CPU the calling
/// thread is running on.
/// </summary>
/// <param name="dst">A pointer to a <see cref="RaplCpuInfo" /> to retrieve
/// the CPU vendor and model information.</param>
/// <returns><c>STATUS_SUCCESS</c> in case of success,
/// <c>STATUS_INVALID_PARAMETER</c> if <paramref name="dst" /> is
/// <c>nullptr</c>,
/// <c>STATUS_UNSUCCESSFUL</c> if the CPU does not allow for retrieving the
/// family and model.</returns>
NTSTATUS RaplIdentifyCpu(_In_ RaplCpuInfo& dst) {
    __int32 info[4];
    NTSTATUS status = STATUS_SUCCESS;

    if (NT_SUCCESS(status)) {
        ::__cpuid(info, 0);
        if (info[0] < 2) {
            // We need to be able to retrieve the family and model, which is at
            // index 1.
            status = STATUS_UNSUCCESSFUL;
        }
    }

    if (NT_SUCCESS(status)) {
        char vendor[3 * sizeof(__int32) + 1];
        ::RtlZeroMemory(vendor, sizeof(vendor));

        // Kansas city shuffle.
        *reinterpret_cast<__int32 *>(vendor + 0) = info[1];
        *reinterpret_cast<__int32 *>(vendor + 4) = info[3];
        *reinterpret_cast<__int32 *>(vendor + 8) = info[2];
        KdPrint(("[PWROWG] CPU vendor string is \"%hs\".\r\n", vendor));

#define _IS_VENDOR(v) (::strncmp(vendor, (v), sizeof(vendor)) == 0)
        if (_IS_VENDOR("AuthenticAMD") || _IS_VENDOR("AMDisbetter!")) {
            dst.Vendor = RaplCpuVendor::Amd;
        } else if (_IS_VENDOR("GenuineIntel")) {
            dst.Vendor = RaplCpuVendor::Intel;
        } else {
            dst.Vendor = RaplCpuVendor::Other;
        }
#undef _IS_VENDOR
        KdPrint(("[PWROWG] CPU vendor %d.\r\n", dst.Vendor));
    }

    if (NT_SUCCESS(status)) {
        ::__cpuid(info, 1);
        dst.Stepping = (info[0] & 0x0000000F) >> 0;
        dst.BaseModel = (info[0] & 0x000000F0) >> 4;
        dst.BaseFamily = (info[0] & 0x00000F00) >> 8;
        dst.ExtendedModel = (info[0] & 0x0000F0000) >> 16;
        dst.ExtendedFamily = (info[0] & 0x00FF00000) >> 20;
        KdPrint(("[PWROWG] CPU family is 0x%hhx, 0x%hhx.\r\n", dst.BaseFamily,
            dst.ExtendedFamily));
        KdPrint(("[PWROWG] CPU model is 0x%hhx, 0x%hhx.\r\n", dst.BaseModel,
            dst.ExtendedModel));
        KdPrint(("[PWROWG] CPU stepping is 0x%hhx.\r\n", dst.Stepping));
    }

    return status;
}


/// <summary>
/// The framework calls the driver's <c>EvtDeviceFileCreate</c> callback when
/// it receives an <c>IRP_MJ_CREATE</c> request.
/// </summary>
/// <remarks>
/// <para>Cf. https://github.com/microsoft/Windows-driver-samples/blob/f28183b782d1f113492f6eea424172f2addaf565/general/ioctl/kmdf/sys/nonpnp.c#L400
/// </para>
/// <para>The system sends this request when a user application opens the device
/// to perform an I/O operation, such as reading or writing a file. This
/// callback is called synchronously, in the fileContext of the thread that created
/// the <c>IRP_MJ_CREATE</c> request.</para>
/// <param name="device"></param>
/// <param name="request"></param>
/// <param name="fileObject"></param>
extern "C" void RaplCreate(_In_ WDFDEVICE device, _In_ WDFREQUEST request,
        _In_ WDFFILEOBJECT fileObject) noexcept {
    ASSERT(fileObject != nullptr);
    PAGED_CODE();

    RaplCpuInfo cpuInfo { 0 };
    GROUP_AFFINITY originalAffinity { 0 };
    WDF_REQUEST_PARAMETERS parameters { 0 };
    NTSTATUS status = STATUS_SUCCESS;

    // Retrieve the parameters and make sure that we accept nothing but opening
    // existing files for reading them.
    ::WdfRequestGetParameters(request, &parameters);
    //parameters.Parameters.Create.

    // Get the device context, which we need for global settings.
    const auto deviceContext = ::GetRaplDeviceContext(device);
    ASSERT(deviceContext != nullptr);

    // Retrieve our custom fileContext structure. As we have registered it in the
    // file object config of RaplDeviceAdd, the framework should have already
    // allocated this for us.
    const auto fileContext = ::GetRaplFileContext(fileObject);
    ASSERT(fileContext != nullptr);

    // Parsed filename has "\" in the begining. The object manager strips all
    // "\" except one, after the device name.
    const auto fileName = ::WdfFileObjectGetFileName(fileObject);
    KdPrint(("[PWROWG] Open \"%wZ\"\r\n", fileName));

    // The file name must be the number of the core, i.e. an integral number in
    // the decimal system. If the path is empty or if it contains anything but a
    // number, this is illegal and we reject this as "file not found".
    if (NT_SUCCESS(status)) {
        if (fileName->Length < 2) {
            KdPrint(("[PWROWG] Cannot open a volume.\r\n"));
            status = STATUS_NOT_FOUND;
        }
    }

    if (NT_SUCCESS(status)) {
        ASSERT(fileName->Length >= 2);
        if (!NT_SUCCESS(::RaplParseInt32(fileContext->Core, *fileName, 1))) {
            KdPrint(("[PWROWG] Parsing the logical core number failed.\r\n"));
            status = STATUS_NOT_FOUND;
        }
    }

    // Bind the calling thread to the CPU which of the RAPL registers have been
    // requested. This way, we make sure that the CPUID instructions return data
    // on the CPU we are interested in.
    if (NT_SUCCESS(status)) {
        status = ::RaplSetThreadAffinity(fileContext->Core, &originalAffinity);
    }
    const auto restoreAffinity = NT_SUCCESS(status);

    // Obtain the CPU vendor and model, which allows us to find out whether the
    // requested core supports RAPL MSRs. Afterwards, we restore the thread
    // affinity to its original state.
    if (NT_SUCCESS(status)) {
        status = ::RaplIdentifyCpu(cpuInfo);
    }

    if (restoreAffinity) {
        ::KeSetSystemGroupAffinityThread(&originalAffinity, nullptr);
    }

    // Next, make sure that the CPU is by AMD or Intel and determine which
    // MSRs can be accessed on the model.
    if (NT_SUCCESS(status)) {
        if (deviceContext->DriverContext->AllowAllMsrs) {
            // User override to allow all MSRs. Setting 'Msrs' to nullptr will
            // skip the test in RaplIsRegisterSupported.
            KdPrint(("[PWROWG] Check of MSR addresses is disabled.\r\n"));
            fileContext->CountMsrs = 0;
            fileContext->Msrs = nullptr;

        } else {
            fileContext->CountMsrs = ::RaplGetSupportedRegisters(cpuInfo,
                nullptr, 0);
            // Note: We allocate at least one byte, because 'Msrs' being
            // nullptr indicates that the test should be skipped and if we
            // have zero registers in this code path, we want to signal that
            // none us supported.
            fileContext->Msrs = reinterpret_cast<unsigned __int32 *>(
                ::ExAllocatePoolWithTag(PagedPool,
                max(1, fileContext->CountMsrs * sizeof(unsigned __int32)),
                RAPL_POOL_TAG));

            if (fileContext->Msrs != nullptr) {
                fileContext->CountMsrs = ::RaplGetSupportedRegisters(cpuInfo,
                    fileContext->Msrs, fileContext->CountMsrs);
                KdPrint(("[PWROWG] MSR list 0x%p has %I64u element(s).\r\n",
                    fileContext->Msrs, fileContext->CountMsrs));

            } else {
                KdPrint(("[PWROWG] Insufficient memory for MSR list.\r\n"));
                status = STATUS_NO_MEMORY;
            }
        }
    }

    KdPrint(("[PWROWG] Complete open with 0x%x\r\n", status));
    ::WdfRequestComplete(request, status);
}
