// <copyright file="main.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <Windows.h>


/// <summary>
/// Entry point of the DLL.
/// </summary>
/// <param name="handle"></param>
/// <param name="reason"></param>
/// <param name="reserved"></param>
/// <returns><c>TRUE</c>, unconditionally.</returns>
BOOL WINAPI DllMain(HINSTANCE handle, DWORD reason, LPVOID reserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            ::DisableThreadLibraryCalls(handle);
            break;

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}
