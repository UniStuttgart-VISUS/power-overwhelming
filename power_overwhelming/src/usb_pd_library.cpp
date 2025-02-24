// <copyright file="usb_pd_library.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "usb_pd_library.h"


#define __PWROWG_GET_USB_PD_FUNC(n) \
    this->n = this->get_function<decltype(this->n)>(#n)


/*
 * PWROWG_DETAIL_NAMESPACE::usb_pd_library::instance
 */
const PWROWG_DETAIL_NAMESPACE::usb_pd_library&
PWROWG_DETAIL_NAMESPACE::usb_pd_library::instance(void) {
    static const usb_pd_library instance;
    return instance;
}


/*
 * PWROWG_DETAIL_NAMESPACE::usb_pd_library::usb_pd_library
 */
PWROWG_DETAIL_NAMESPACE::usb_pd_library::usb_pd_library(void)
#if defined(_WIN32)
        : library_base(TEXT("usbpd.dll")) {
#else /* defined(_WIN32) */
        : library_base("usbpd.so") {
#endif /* defined(_WIN32) */
    __PWROWG_GET_USB_PD_FUNC(usb_pd_tester_close);
    __PWROWG_GET_USB_PD_FUNC(usb_pd_tester_enumerate);
    __PWROWG_GET_USB_PD_FUNC(usb_pd_tester_free);
    __PWROWG_GET_USB_PD_FUNC(usb_pd_tester_open);
    __PWROWG_GET_USB_PD_FUNC(usb_pd_tester_query);
}
