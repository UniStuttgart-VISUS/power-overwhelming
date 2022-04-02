// <copyright file="setstablepowerstate.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2022 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#include <iostream>

#include <conio.h>

#include "stable_power_state_scope.h"


/// <summary>
/// Entry point of the application.
/// </summary>
/// <remarks>
/// <para>This library creates a
/// <see cref="visus::power_overwhelming::stable_power_state_scope" /> for all
/// hardware GPUs in the system putting them into a stable power state. It then
/// waits until user input. This way, the devices are kept in stable power state
/// until the application exits.</para>
/// <para>This tool is intended to testing applications that do not want to
/// include the Power Overwhelming library in their own code, but need to enable
/// stable power state for benchmarks.</para>
/// </remarks>
/// <returns>Zero in case of success, -1 otherwise.</returns>
int main(void) {
    try {
        std::cout << "Power Overwhelming" << std::endl;
        std::cout << "Copyright (C) 2021 - 2022 Visualisierungsinstitut "
            "der Universit�t Stuttgart."
            << std::endl << "All rights reserved."
            << std::endl << std::endl;

        visus::power_overwhelming::stable_power_state_scope spss;

        std::cout << spss.size() << " graphics device(s) have been put into "
            "stable power state. Press any key to revert." << std::endl;

        ::_getch();

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return -1;
    }
}
