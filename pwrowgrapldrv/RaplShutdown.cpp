// <copyright file="RaplShutdown.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "RaplDriver.h"


/// <summary>
///  Callback invoked when the machine is shutting down.
/// </summary>
/// <remarks>
/// <para>See https://github.com/microsoft/Windows-driver-samples/blob/f28183b782d1f113492f6eea424172f2addaf565/general/ioctl/kmdf/sys/nonpnp.c#L1221
/// </para>
/// <para>When registered for a last-chance shutdown notification, the function
/// must not (i) call any pageable routines, (ii) access pageable memory,
/// (iii) perform any file I/O.</para>
/// <para>When registered for a normal shutdown notification, all of the above.
/// This implementation does nothing, but any open handles would be closed here.
/// </para>
/// </remarks>
/// <param name="device"></param>
extern "C" void RaplShutdown(_In_ WDFDEVICE device) noexcept {
    UNREFERENCED_PARAMETER(device);
}
