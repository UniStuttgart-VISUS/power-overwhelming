// <copyright file="transient_driver.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "transient_driver.h"

#if defined(_WIN32)
#include <cassert>
#include <stdexcept>
#include <system_error>

#include "visus/pwrowg/on_exit.h"


/*
 * PWROWG_DETAIL_NAMESPACE::transient_driver::transient_driver
 */
PWROWG_DETAIL_NAMESPACE::transient_driver::transient_driver(
        _In_z_ const wchar_t *path, _In_z_ const wchar_t *name) {
    // Install the driver service.
    auto hScm = ::OpenSCManagerW(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
    if (hScm == NULL) {
        throw std::system_error(::GetLastError(), std::system_category());
    }
    pwrowg_on_exit([hScm](void) { ::CloseServiceHandle(hScm); });

    std::wstring desc(name);
    desc += L" (transient)";

    this->_guard = std::make_shared<guard>(::CreateServiceW(hScm,
        name,                   // Name of service
        desc.c_str(),           // Display name
        SERVICE_ALL_ACCESS,     // Desired access
        SERVICE_KERNEL_DRIVER,  // Service type
        SERVICE_SYSTEM_START,   // Start type
        SERVICE_ERROR_NORMAL,   // Error control type
        path,                   // Path to service binary
        nullptr,                // No load ordering group
        nullptr,                // No tag identifier
        nullptr,                // No dependencies
        nullptr,                // LocalSystem
        nullptr));              // No password
    if (this->_guard->handle == NULL) {
        auto error = ::GetLastError();

        if (error == ERROR_SERVICE_EXISTS) {
            // If the service already exists, we just open it.
            this->_guard = std::make_shared<guard>(::OpenServiceW(hScm,
                name, SERVICE_ALL_ACCESS));
            if (this->_guard->handle == NULL) {
                error = ::GetLastError();
                throw std::system_error(error, std::system_category());
            }

            this->_guard->uninstall = false;
        } else {
            // Any other error is fatal.
            throw std::system_error(error, std::system_category());
        }
    }

    // Start the driver service.
    if (!::StartServiceW(this->_guard->handle, 0, nullptr)) {
        auto error = ::GetLastError();
        throw std::system_error(error, std::system_category());
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::transient_driver::guard::~guard
 */
PWROWG_DETAIL_NAMESPACE::transient_driver::guard::~guard(void) noexcept {
    if (this->handle != NULL) {
        SERVICE_STATUS status;
        ::ControlService(this->handle, SERVICE_CONTROL_STOP, &status);

        if (this->uninstall) {
            ::DeleteService(this->handle);
        }

        ::CloseServiceHandle(this->handle);
    }
}
#endif /* !defined(_WIN32) */
