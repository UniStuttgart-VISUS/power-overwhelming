// <copyright file="stable_power_state_scope.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/stable_power_state_scope.h"

#include <cassert>
#include <stdexcept>
#include <system_error>
#include <vector>

#include "com_error_category.h"
#include "safe_com.h"


/*
 * visus::power_overwhelming::stable_power_state_scope::stable_power_state_scope
 */
visus::power_overwhelming::stable_power_state_scope::stable_power_state_scope(
        void) : _cnt_devices(0), _devices(nullptr) {
    std::vector<graphics_device> devices;
    devices.resize(graphics_device::all(nullptr, 0, true));
    graphics_device::all(devices.data(), devices.size(), true);

    for (auto it = devices.begin(); it != devices.end(); ) {
        auto d = static_cast<graphics_device::device_type *>(*it);
        if (d != nullptr) {
            this->enable(d);
            ++it;
        } else {
            it = devices.erase(it);
        }
    }

    this->_devices = new graphics_device[devices.size()];
    this->_cnt_devices = devices.size();
    std::copy(devices.begin(), devices.end(), this->_devices);
}


/*
 * visus::power_overwhelming::stable_power_state_scope::stable_power_state_scope
 */
visus::power_overwhelming::stable_power_state_scope::stable_power_state_scope(
        _In_ graphics_device& device) : _cnt_devices(0), _devices(nullptr) {
    if (device != nullptr) {
        this->enable(device);

        this->_devices = new graphics_device[1];
        this->_cnt_devices = 1;
        this->_devices[0] = device;
    }
}


/*
 * visus::power_overwhelming::stable_power_state_scope::~stable_power_state_scope
 */
visus::power_overwhelming::stable_power_state_scope::~stable_power_state_scope(
        void) {
    delete[] this->_devices;
}


/*
 * visus::power_overwhelming::stable_power_state_scope::enable
 */
void visus::power_overwhelming::stable_power_state_scope::enable(
        _In_ graphics_device::device_type *device) {
#if (POWER_OVERWHELMING_GPU_ABSTRACTION == 12)
    if (device == nullptr) {
        throw std::invalid_argument("A valid Direct3D 12 device must be "
            "provided to enable the stable power state.");
    }

    {
        auto hr = device->SetStablePowerState(TRUE);
        if (FAILED(hr)) {
            throw std::system_error(hr, detail::com_category(), "Failed to set "
                "a stable power state on a Direct3D 12 adapter. Please make "
                "sure that you have installed the Windows 10 SDK and that your "
                "machine is in developer mode. The developer mode can be "
                "enabled in the Update section of the Windows 10 settings app "
                "or in the Privacy section of the Windows 11 settings app.");
        }
    }

#else /* (POWER_OVERWHELMING_GPU_ABSTRACTION == 12) */
    throw std::logic_error("Direct3D 12 is required to put GPUs in a stable "
        "power state. Make sure to build on a supported platform without "
        "disabling support for Direct3D 12 explicitly.");
#endif /* (POWER_OVERWHELMING_GPU_ABSTRACTION == 12) */
}
