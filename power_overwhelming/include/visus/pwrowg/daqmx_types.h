// <copyright file="daqmx_types.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_TYPES_H)
#define _PWROWG_DAQMX_TYPES_H
#pragma once

#include <cinttypes>

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include <NIDAQmx.h>
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

#include "visus/pwrowg/api.h"


#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#define __PWOWG_DAQMX_TYPE(d, f) d
#else  /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
#define __PWOWG_DAQMX_TYPE(d, f) f
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */


#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#define __PWOWG_DAQMX_VALUE(d, f) (d)
#else  /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
#define __PWOWG_DAQMX_VALUE(d, f) (f)
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */


#if !defined(CVICALLBACK)
#if defined(_WIN32)
#define CVICALLBACK __cdecl
#else /* defined(_WIN32) */
#define CVICALLBACK 
#endif /* defined(_WIN32) */
#endif /* !defined(CVICALLBACK) */


PWROWG_NAMESPACE_BEGIN

// This namespace holds types using in the DAQmx API and that must be visible
// to users to the library even if the library is used without support for DAQmx.
namespace daqmx {

    typedef __PWOWG_DAQMX_TYPE(::int32, std::int32_t) int32;
    typedef __PWOWG_DAQMX_TYPE(::uInt32, std::uint32_t) uint32;

} /* namespace daqmx */

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_TYPES_H) */
