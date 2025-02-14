// <copyright file="usb_pd_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/usb_pd_configuration.h"


/*
 * PWROWG_NAMESPACE::usb_pd_configuration::id
 */
const PWROWG_NAMESPACE::guid PWROWG_NAMESPACE::usb_pd_configuration::id(
    0x8A41886F, 0x0082, 0x4714, 0x9923, 0xBB, 0x16, 0x1E, 0x84, 0xFD, 0xC4);


/*
 * PWROWG_NAMESPACE::usb_pd_configuration::usb_pd_configuration
 */
PWROWG_NAMESPACE::usb_pd_configuration::usb_pd_configuration(void) noexcept 
    : _timeout(5000) { }
