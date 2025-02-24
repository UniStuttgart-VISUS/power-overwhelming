// <copyright file="usbpd.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_USBPD_H)
#define _USBPD_H
#pragma once

#include <cstdlib>


#if defined(USBPD_EXPORTS)
#define USBPD_API __declspec(dllexport)
#else /* defined(USBPD_EXPORTS) */
#define USBPD_API __declspec(dllimport)
#endif /* defined(USBPD_EXPORTS) */


//extern "C" std::size_t USBPD_API


#endif /* !defined(_USBPD_H) */
