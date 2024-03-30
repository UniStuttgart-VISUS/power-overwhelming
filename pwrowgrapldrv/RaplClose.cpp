// <copyright file="RaplClose.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "RaplDriver.h"


/// <summary>
/// This function is called when all the handles represented by the 
/// <paramref name="fileObject" /> are closed and all the references to
/// <paramref name="fileObject" /> are removed. 
/// </summary>
/// <remarks>
/// This callback may get called in an arbitrary thread context instead of the
/// thread that called <see cref="CloseHandle" />. If you want to delete any
/// per <see cref="fileObject" /> context that must be done in the context of
/// the user thread that made the <see cref="RaplCreate" /> call, you should do
/// that in the cleanup callback.
/// </remarks>
/// <param name="fileObject"></param>
extern "C" void RaplClose(IN WDFFILEOBJECT fileObject) noexcept {
    ASSERT(fileObject != nullptr);
    PAGED_CODE();

    const auto context = ::GetRaplFileContext(fileObject);
    if ((context != nullptr) && (context->Msrs != nullptr)) {
        KdPrint(("[PWROWG] Free MSR list 0x%p\r\n", context->Msrs));
        ::ExFreePoolWithTag(context->Msrs, RAPL_POOL_TAG);
        context->CountMsrs = 0;
        context->Msrs = nullptr;
    }
}
