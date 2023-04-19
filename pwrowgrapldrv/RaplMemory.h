// <copyright file="RaplMemory.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include <wdm.h>


/// <summary>
/// Allocates <paramref name="cnt" /> bytes in the specified pool.
/// </summary>
/// <param name="cnt"></param>
/// <param name="pool"></param>
/// <returns></returns>
void *operator new(const SIZE_T cnt, const POOL_TYPE pool) {
    return ::ExAllocatePoolWithTag(pool, cnt, 'lpaR');
}
