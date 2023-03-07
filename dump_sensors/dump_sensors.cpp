// <copyright file="dump_sensors.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/dump_sensors.h"

#if defined(_WIN32)
#include <Windows.h>
#include <tchar.h>
#endif /* defined(_WIN32) */

#if !defined(_tmain)
#define _tmain main
#define TCHAR char
#endif /* !defined(_tmain) */


/// <summary>
/// Entry point of the dump_sensors application, which dumps the definitions of
/// all sensors into the user-provided file.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(const int argc, const TCHAR **argv) {
    return 0;
}
