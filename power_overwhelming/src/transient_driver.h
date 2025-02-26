// <copyright file="transient_driver.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TRANSIENT_DRIVER_H)
#define _PWROWG_TRANSIENT_DRIVER_H
#pragma once

#include <memory>

#if defined(_WIN32)
#include <Windows.h>
#endif /* defined(_WIN32) */

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A RAII scope that temporarily starts a device driver service on Windows.
/// </summary>
class PWROWG_TEST_API transient_driver final {
#if defined(_WIN32)

public:

    transient_driver(_In_z_ const wchar_t *path, _In_z_ const wchar_t *name);

private:

    struct guard final {
        SC_HANDLE handle;
        bool uninstall;

        inline guard(_In_opt_ const SC_HANDLE handle = NULL) noexcept
            : handle(handle), uninstall(true) { }

        ~guard(void) noexcept;
    };

    std::shared_ptr<guard> _guard;

#endif /* !defined(_WIN32) */
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_TRANSIENT_DRIVER_H) */
