// <copyright file="RaplMsr.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
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
/// <returns></returns>
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
