// <copyright file="RaplRegistry.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <ntddk.h>
#include <wdf.h>


/// <summary>
/// Opens the driver parameter location in the registry using
/// <see cref="WdfDriverOpenParametersRegistryKey" /> and queries the value
/// named <pararmref name="name" /> from there.
/// </summary>
/// <param name="dst">The variable that receives the value from the registry in
/// case the read succeeded.</param>
/// <param name="driver">The driver to open the parameter key for.</param>
/// <param name="name">The name of the value to be read.</param>
/// <returns><c>STATUS_SUCCESS</c> in case of success, an error code otherwise.
/// </returns>
NTSTATUS RaplQueryRegistryParameterUlong(_Out_ ULONG& dst, _In_ WDFDRIVER driver,
    _In_ const UNICODE_STRING& name);
