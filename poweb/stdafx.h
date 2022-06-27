// <copyright file="stdafx.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "targetver.h"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <system_error>
#include <thread>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <tchar.h>
#include <wrl.h>

#include <nlohmann/json.hpp>

#include <wil/com.h>

// Must be after all of Windows, WRL and WIL.
#include <WebView2.h>

#include "power_overwhelming/collector.h"
#include "power_overwhelming/convert_string.h"
