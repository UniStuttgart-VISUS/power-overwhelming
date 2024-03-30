// <copyright file="RaplDriverUnload.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "RaplDriver.h"


/// <summary>
/// Called by the I/O subsystem just before unloading the driver.
/// </summary>
/// <remarks>
/// <para>Cf. https://github.com/microsoft/Windows-driver-samples/blob/f28183b782d1f113492f6eea424172f2addaf565/general/ioctl/kmdf/sys/nonpnp.c#L1254
/// </para>
/// <para>You can free the resources created in the <see cref="DriverEntry" />
/// either here or in <see cref="RaplCleanup" />.</para>
/// <param name="driver"></param>
extern "C" void RaplDriverUnload(_In_ WDFDRIVER driver) noexcept {
    PAGED_CODE();
    UNREFERENCED_PARAMETER(driver);
    //TraceEvents(TRACE_LEVEL_VERBOSE, DBG_INIT, "Entered NonPnpDriverUnload\n");
}
