// <copyright file="usb_pd_library.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_USB_PD_LIBRARY_H)
#define _PWROWG_USB_PD_LIBRARY_H
#pragma once

#include <usbpd.h>

#include "library_base.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

#define __PWROWG_USB_PD_FUNC(f) decltype(&::f) f

/// <summary>
/// Wrapper for lazily loading the wrapper around the Passmark USB-PD API.
/// </summary>
class PWROWG_TEST_API usb_pd_library final : library_base {

public:

    /// <summary>
    /// Gets the only instance of the class.
    /// </summary>
    /// <returns>The only instance of the class.</returns>
    /// <exception cref="std::system_error">If the library could not be loaded,
    /// eg because the driver for the power delivery tester was not installed
    /// ont eh machine we are running on.</exception>
    static const usb_pd_library& instance(void);

    __PWROWG_USB_PD_FUNC(usb_pd_tester_close);
    __PWROWG_USB_PD_FUNC(usb_pd_tester_enumerate);
    __PWROWG_USB_PD_FUNC(usb_pd_tester_free);
    __PWROWG_USB_PD_FUNC(usb_pd_tester_open);
    __PWROWG_USB_PD_FUNC(usb_pd_tester_query);

private:

    usb_pd_library(void);

};

#undef __PWROWG_USB_PD_FUNC

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_USB_PD_LIBRARY_H) */
