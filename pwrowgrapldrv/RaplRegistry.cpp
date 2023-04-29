// <copyright file="RaplRegistry.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "RaplRegistry.h"

#include <wdfregistry.h>


/*
 * ::RaplQueryRegistryParameterUlong
 */
NTSTATUS RaplQueryRegistryParameterUlong(_Out_ ULONG& dst,
        _In_ WDFDRIVER driver,
        _In_ const UNICODE_STRING& name) {
    WDFKEY key = nullptr;
    auto status = (driver != nullptr)
        ? STATUS_SUCCESS
        : STATUS_INVALID_PARAMETER_2;

    if (NT_SUCCESS(status)) {
        status = ::WdfDriverOpenParametersRegistryKey(driver, KEY_READ,
            nullptr, &key);
        KdPrint(("[PWROWG] Opening driver parameter registry resulted "
            "in 0x%x\r\n", status));
    }
    const bool closeKey = NT_SUCCESS(status);

    if (NT_SUCCESS(status)) {
        status = ::WdfRegistryQueryULong(key, &name, &dst);
        KdPrint(("[PWROWG] Querying ULONG from registry resulted in 0x%x\r\n",
            status));
    }

    if (closeKey) {
        ::WdfRegistryClose(key);
    }

    return status;
}
