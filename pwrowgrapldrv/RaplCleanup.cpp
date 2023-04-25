// <copyright file="RaplCleanup.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "RaplDriver.h"


/// <summary>
/// Called when the driver object is deleted during driver unload.
/// </summary>
extern "C" void RaplCleanup(_In_ WDFOBJECT driver) noexcept {
    ASSERT(driver != nullptr);
    PAGED_CODE();
    // TODO: cleanup tracing
    //WPP_CLEANUP(::WdfDriverWdmGetDriverObject(driver));
}
