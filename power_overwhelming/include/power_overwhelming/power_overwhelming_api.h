// <copyright file="power_overwhelming_api.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#if defined(_WIN32)

#if defined(POWER_OVERWHELMING_EXPORTS)
#define POWER_OVERWHELMING_API __declspec(dllexport)
#else /* defined(POWER_OVERWHELMING_EXPORTS) */
#define POWER_OVERWHELMING_API __declspec(dllimport)
#endif /* defined(POWER_OVERWHELMING_EXPORTS) */

#else /* defined(WIN32) */
#define POWER_OVERWHELMING_API

#endif /* defined(WIN32) */


#if defined(_WIN32)
#include <sal.h>

#else /* defined(_WIN32) */
// Empty SAL annotations for rancid platforms.
#include "salieri.h"

// These are missing in the salieri header.
#define _Analysis_assume_(expr)
#endif /* defined(_WIN32) */
