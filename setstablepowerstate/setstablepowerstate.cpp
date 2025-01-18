// <copyright file="setstablepowerstate.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <iostream>

#include <conio.h>

#include "visus/pwrowg/stable_power_state_scope.h"


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
        std::cout << "Copyright © 2021 - 2023 Visualisierungsinstitut "
            "der Universität Stuttgart."
            << std::endl << "All rights reserved."
            << std::endl << std::endl;

        visus::power_overwhelming::stable_power_state_scope spss;

        std::cout << spss.size() << ((spss.size() == 1)
            ? " graphics device has " : " graphics devices have ")
            << "been put into stable power state. Press any key to revert."
            << std::endl;

        ::_getch();
        return 0;

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return -1;
    }
}
