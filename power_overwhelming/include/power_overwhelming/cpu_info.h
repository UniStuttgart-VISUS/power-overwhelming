// <copyright file="cpu_info.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Represents the data that are received from the x86 CPUID instruction.
    /// </summary>
    /// <remarks>
    /// <para>The values retrieved from the registers depend on the index
    /// queried from the CPU. Out implementation retrieves these in order, i.e.
    /// the first element is at index 0 and holds the vendor string, the one at
    /// index 1 holds the model information and so on.</para>
    /// </remarks>
    union cpu_info {
        struct {
            /// <summary>
            /// The value of the EAX register.
            /// </summary>
            std::uint32_t eax;

            /// <summary>
            /// The value of the EBX register.
            /// </summary>
            std::uint32_t ebx;

            /// <summary>
            /// The value of the ECX register.
            /// </summary>
            std::uint32_t ecx;

            /// <summary>
            /// The value of the EDX register.
            /// </summary>
            std::uint32_t edx;
        } registers;

        /// <summary>
        /// A contiguous view on the registers.
        /// </summary>
        std::int32_t values[4];
    };

    static_assert(sizeof(cpu_info) == sizeof(cpu_info::values), "The cpu_info "
        "structure must not be padded. If this is the case on your machine, "
        "you need to add some kind of alignment annotation.s");

    /// <summary>
    /// Represents the CPU model extracted from <see cref="cpu_info" />.
    /// </summary>
    struct cpu_model {
        std::uint8_t base_family;
        std::uint8_t extended_family;
        std::uint8_t base_model;
        std::uint8_t extended_model;
        std::uint8_t stepping;
    };

    /// <summary>
    /// Specifies different vendors of CPUs.
    /// </summary>
    /// <remarks>
    /// <para>Some sensors, most notably the <see cref="msr_sensor" /> are
    /// dependent on vendor-specific implementations. This enumeration
    /// identifies the supported CPU vendors.</para>
    /// <para>Callers should not make any assumption about the numeric values
    /// of the enumeration except for <see cref="cpu_vendor::unknown" /> being
    /// zero.</para>
    /// </remarks>
    enum class cpu_vendor {

        /// <summary>
        /// The CPU vendor is not known.
        /// </summary>
        unknown = 0,

        /// <summary>
        /// Identifies an AMD CPU.
        /// </summary>
        amd,

        /// <summary>
        /// Identifies an ao486 soft CPU core.
        /// </summary>
        /// <remarks>
        /// Cf. https://github.com/MiSTer-devel/ao486_MiSTer
        /// </remarsk>
        ao486,

        /// <summary>
        /// Identifies the bhyve hypervisor.
        /// </summary>
        bhyve,

        /// <summary>
        /// Identifies a Centaur CPU.
        /// </summary>
        centaur,

        /// <summary>
        /// Identifies a Cyrix CPU.
        /// </summary>
        cyrix,

        /// <summary>
        /// Identifies a DM&P Vortex86 CPU.
        /// </summary>
        dmp,

        /// <summary>
        /// Identifies an MCST Elbrus CPU.
        /// </summary>
        elbrus,

        /// <summary>
        /// Identifies a Hygon CPU.
        /// </summary>
        hygon,

        /// <summary>
        /// Identifies the HyperV hypervisor.
        /// </summary>
        hyperv,

        /// <summary>
        /// Identifies an Intel CPU.
        /// </summary>
        intel,

        /// <summary>
        /// Identifies the KVM hypervisor.
        /// </summary>
        kvm,

        /// <summary>
        /// Identifies the CPU emulated by the Microsoft ARM emulation
        /// layer.
        /// </summary>
        microsoft_xta,

        /// <summary>
        /// Identifies a National Semiconductor CPU.
        /// </summary>
        national_semiconductor,

        /// <summary>
        /// Identifies a NexGen CPU.
        /// </summary>
        nexgen,

        /// <summary>
        /// Identifies an emulated CPU by Parallels.
        /// </summary>
        parallels,

        /// <summary>
        /// Identifies the Project ACRN hypervisor.
        /// </summary>
        /// <remarks>
        /// Cf. https://projectacrn.org/
        /// </remarks>
        project_acrn,

        /// <summary>
        /// Identifies the QEMU hypervisor.
        /// </summary>
        qemu,

        /// <summary>
        /// Identifies the QNX hypervisor.
        /// </summary>
        qnx,

        /// <summary>
        /// Identifies a CPU by RDC Semiconductor Co. Ltd.
        /// </summary>
        rdc,

        /// <summary>
        /// Identifies a Rise Technology CPU.
        /// </summary>
        rise,

        /// <summary>
        /// Identifies the emulation layer by the rotten fruit company.
        /// </summary>
        rosetta2,

        /// <summary>
        /// Identifies an SiS CPU.
        /// </summary>
        sis,

        /// <summary>
        /// Identifies a Transmeta CPU.
        /// </summary>
        transmeta,

        /// <summary>
        /// Identifies a UMC CPU.
        /// </summary>
        umc,

        /// <summary>
        /// Identifies a VIA CPU.
        /// </summary>
        via,

        /// <summary>
        /// Identifies the VMware hypervisor.
        /// </summary>
        vmware,

        /// <summary>
        /// Identifies the Xen hypervisor.
        /// </summary>
        xen,

        /// <summary>
        /// Identifies a Zhaoxin CPU:
        /// </summary>
        zhaoxin
    };

    /// <summary>
    /// Extracts the CPU family and model from the second CPUID result.
    /// </summary>
    /// <param name="info">The first two <see cref="cpu_info" />s retrieved from
    /// <see cref="get_cpu_info" />.</param>
    /// <returns>A description of the CPU model.</returns>
    extern POWER_OVERWHELMING_API cpu_model extract_cpu_model(
        _In_reads_(2) const cpu_info info[2]) noexcept;

    /// <summary>
    /// Extracts the vendor from the first CPUID result.
    /// </summary>
    /// <param name="info">The first <see cref="cpu_info" /> retrieved from
    /// <see cref="get_cpu_info" />.</param>
    /// <returns>An enumeration value identifying the CPU vendor or
    /// <see cref="cpu_vendor::unknown" /> if the CPU vendor could not be
    /// determined.</returns>
    extern POWER_OVERWHELMING_API cpu_vendor extract_cpu_vendor(
        _In_ const cpu_info& info) noexcept;

    /// <summary>
    /// Retrieves up to <paramref name="max_id" /> values from the CPUID
    /// instruction.
    /// </summary>
    /// <param name="infos">An array to receive at most
    /// <paramref name="max_id" /> CPUID results. It is safe to pass
    /// <c>nullptr</c>, in which case nothing will be written.</param>
    /// <param name="cnt">The limit for the CPUIDs to retrieve.</param>
    /// <returns>The maxmimum CPUID available on the system. This may be smaller
    /// or larger than <paramref name="cnt" />. Only the minimum of
    /// <paramref name="cnt" /> and the return value have been written to
    /// <paramref name="infos" />.</returns>
    extern POWER_OVERWHELMING_API std::uint32_t get_cpu_info(
        _Out_writes_opt_(cnt) cpu_info *infos,
        _In_ std::uint32_t cnt);

    /// <summary>
    /// Determines the vendor of the CPUs on the system.
    /// </summary>
    /// <remarks>
    /// This function works using the CPUID intrinsics. For the unlikely case
    /// that the code is running on a machine with different kinds of CPUs, the
    /// caller should set the thread affinity to the desired CPU in order to
    /// make sure that the CPUID registers of the expected processors are read.
    /// The <see cref="set_thread_affinity" /> function can be used for this
    /// purpose.
    /// </remarks>
    /// <returns>An enumeration value identifying the CPU vendor or
    /// <see cref="cpu_vendor::unknown" /> if the CPU vendor could not be
    /// determined.</returns>
    extern POWER_OVERWHELMING_API cpu_vendor get_cpu_vendor(void) noexcept;

} /* namespace power_overwhelming */
} /* namespace visus */
