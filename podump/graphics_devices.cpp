// <copyright file="graphics_devices.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "graphics_devices.h"


/*
 * ::enumerate_graphics_devices
 */
void enumerate_graphics_devices(void) {
    using namespace visus::power_overwhelming;

    try {
        std::vector<graphics_device> devices;
        devices.resize(graphics_device::all(nullptr, 0));
        graphics_device::all(devices.data(), devices.size());

        for (auto& d : devices) {
            std::wcout << d.name() << L": " << d.id() << std::endl;
        }
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}
