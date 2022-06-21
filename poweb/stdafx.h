// <copyright file="stdafx.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "targetver.h"

#include <cassert>
#include <cstdlib>
#include <memory>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <tchar.h>
#include <wrl.h>

#include <wil/com.h>

// Must be after all of Windows, WRL and WIL.
#include <WebView2.h>


#include "power_overwhelming/collector.h"
