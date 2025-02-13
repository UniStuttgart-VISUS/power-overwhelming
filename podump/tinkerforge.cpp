// <copyright file="tinkerforge.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "tinkerforge.h"


/*
 * ::print_tinkerforge_display
 */
void print_tinkerforge_display(const char *text) {
    using namespace visus::pwrowg;

    try {
        std::vector<tinkerforge_display> displays;
        displays.resize(tinkerforge_display::for_all(nullptr, 0));
        auto cnt = tinkerforge_display::for_all(displays.data(),
            displays.size());

        if (cnt < displays.size()) {
            displays.resize(cnt);
        }

        for (auto& d : displays) {
            d.clear();
            d.print(text);
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}
