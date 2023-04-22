// <copyright file="RaplMsr.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

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
