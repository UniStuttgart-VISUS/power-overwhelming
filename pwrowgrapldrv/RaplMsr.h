// <copyright file="RaplMsr.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "RaplCpuInfo.h"


/// <summary>
/// Gets the indices that are supported for the given CPU.
/// </summary>
/// <param name="cpuInfo"></param>
/// <param name="dst"></param>
/// <param name="cnt"></param>
/// <returns>If <paramref name="dst" /> is <see langword="nullptr"/>, the
/// maximum number of registers supported, which can be used to allocate the
/// required memory for a second call. Otherwise, the number of registers
/// written to <paramref name="dst" />.</returns>
SIZE_T RaplGetSupportedRegisters(_In_ const RaplCpuInfo& cpuInfo,
    _Out_writes_opt_(cnt) unsigned __int32 *dst,
    _In_ const SIZE_T cnt);

/// <summary>
/// Answer whether <paramref name="reg" /> is in the given list of valid
/// registers <paramref name="regs" /> or if the filter list is disabled
/// (<c>nullptr</c>).
/// </summary>
/// <param name="reg"></param>
/// <param name="regs"></param>
/// <param name="cnt"></param>
/// <returns></returns>
bool RaplIsRegisterSupported(_In_ const unsigned __int32 reg,
    _In_reads_(cnt) const unsigned __int32 *regs,
    _In_ const SIZE_T cnt);
