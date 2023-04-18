// <copyright file="rapl_create.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include <intrin.h>
#include <ntddk.h>

#include "thread_affinity.h"


/// <summary>
/// Possible CPU vendors.
/// </summary>
/// <remarks>
/// At this point, we are only interested whether the CPU is AMD, Intel or any
/// other, because others do not support RAPL MSRs.
/// </remarks>
enum class rapl_cpu_vendor {
    amd,
    intel,
    other
};


/// <summary>
/// A structure holding all necessary information about the CPU we are running
/// on.
/// </summary>
struct rapl_cpu_info {
    __int8 base_family;
    __int8 extended_family;
    __int8 base_model;
    __int8 extended_model;
    __int8 stepping;
    rapl_cpu_vendor vendor;
};


/// <summary>
/// Retrieve all members of <see cref="rapl_cpu_info" /> for the CPU the calling
/// thread is running on.
/// </summary>
/// <param name="dst">A pointer to a <see cref="rapl_cpu_info" /> to retrieve
/// the CPU vendor and model information.</param>
/// <returns><c>STATUS_SUCCESS</c> in case of success,
/// <c>STATUS_INVALID_PARAMETER</c> if <paramref name="dst" /> is
/// <c>nullptr</c>,
/// <c>STATUS_UNSUCCESSFUL</c> if the CPU does not allow for retrieving the
/// family and model.</returns>
NTSTATUS rapl_identify_cpu(_In_ rapl_cpu_info *dst) {
    __int32 info[4];

    NTSTATUS status = (dst != nullptr)
        ? STATUS_SUCCESS
        : STATUS_INVALID_PARAMETER;

    if (NT_SUCCESS(status)) {
        ::__cpuid(info, 0);
        if (info[0] < 2) {
            // We need to be able to retrieve the family and model, which is at
            // index 1.
            status = STATUS_UNSUCCESSFUL;
        }
    }

    if (NT_SUCCESS(status)) {
        char vendor[0x20];
        ::RtlZeroMemory(vendor, sizeof(vendor));

        // Kansas city shuffle.
        *reinterpret_cast<int *>(vendor + 0) = info[1];
        *reinterpret_cast<int *>(vendor + 4) = info[3];
        *reinterpret_cast<int *>(vendor + 8) = info[2];

#define _IS_VENDOR(v) (::strncmp(vendor, (v), sizeof(vendor)) == 0)
        if (_IS_VENDOR("AuthenticAMD") || _IS_VENDOR("AMDisbetter!")) {
            dst->vendor = rapl_cpu_vendor::amd;
        } else if (_IS_VENDOR("GenuineIntel")) {
            dst->vendor = rapl_cpu_vendor::intel;
        } else {
            dst->vendor = rapl_cpu_vendor::other;
        }
#undef _IS_VENDOR
    }

    if (NT_SUCCESS(status)) {
        ::__cpuid(info, 1);
        dst->stepping = (info[0] & 0x0000000F) >> 0;
        dst->base_model = (info[0] & 0x000000F0) >> 4;
        dst->base_family = (info[0] & 0x00000F00) >> 8;
        dst->extended_model = (info[0] & 0x0000F0000) >> 16;
        dst->extended_family = (info[0] & 0x00FF00000) >> 20;
    }

    return status;
}


/// <summary>
/// Entry point for a request to open a file handle.
/// </summary>
/// <param name="device"></param>
/// <param name="irp"></param>
/// <returns><c>STATUS_SUCCESS</c> if the operation succeeded, an error code
/// otherwise.</returns>
_IRQL_requires_min_(PASSIVE_LEVEL)
_IRQL_requires_max_(APC_LEVEL)
_Function_class_(IRP_MJ_CREATE)
_Function_class_(DRIVER_DISPATCH)
NTSTATUS rapl_create(_In_ PDEVICE_OBJECT device, _Inout_ PIRP irp) {
    ASSERT(device != nullptr);
    ASSERT(irp != nullptr);
    __int32 core = 0;
    rapl_cpu_info cpu_info { 0 };
    GROUP_AFFINITY original_affinity { 0 };
    NTSTATUS status = STATUS_SUCCESS;

    // TODO: Parse the core from the path.
    // TODO: How do we attach our own information to the file handle?

    // Bind the calling thread to the CPU which of the RAPL registers have been
    // requested. This way, we make sure that the CPUID instructions return data
    // on the CPU we are interested in.
    if (NT_SUCCESS(status)) {
        status = ::rapl_set_thread_affinity(core, &original_affinity);
    }
    const auto restore_affinity = NT_SUCCESS(status);

    // Obtain the CPU vendor and model, which allows us to find out whether the
    // requested core supports RAPL MSRs. Afterwards, we restore the thread
    // affinity to its original state.
    if (NT_SUCCESS(status)) {
        status = ::rapl_identify_cpu(&cpu_info);
    }

    if (restore_affinity) {
        ::KeSetSystemGroupAffinityThread(&original_affinity, nullptr);
    }

    // Next, make sure that the CPU is by AMD or Intel.
    if (NT_SUCCESS(status)) {
        switch (cpu_info.vendor) {
            case rapl_cpu_vendor::amd:
                // TODO: retrieve the valid offsets for AMD
                break;

            case rapl_cpu_vendor::intel:
                // TODO: retrieve the vaid fofsets for Intel.
                break;

            default:
                // Other vendors do not have the RAPL MSRs, so we tell the
                // caller that we could not find it.
                status = STATUS_NOT_FOUND;
                break;
        }
    }

    irp->IoStatus.Status = status;
    irp->IoStatus.Information = NT_SUCCESS(status)
        ? FILE_OPENED
        : FILE_DOES_NOT_EXIST;
    ::IofCompleteRequest(irp, IO_NO_INCREMENT);

    return STATUS_SUCCESS;
}
