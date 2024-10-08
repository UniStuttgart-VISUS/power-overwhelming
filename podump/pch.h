﻿// <copyright file="pch.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

#if defined(_WIN32)
#include <tchar.h>
#include <Windows.h>
#endif /* defined (_WIN32) */

#include "power_overwhelming/adl_sensor.h"
#include "power_overwhelming/adl_thermal_sensor.h"
#include "power_overwhelming/adl_throttling_sensor.h"
#include "power_overwhelming/emi_sensor.h"
#include "power_overwhelming/collector.h"
#include "power_overwhelming/graphics_device.h"
#include "power_overwhelming/hmc8015_sensor.h"
#include "power_overwhelming/measurement.h"
#include "power_overwhelming/msr_sensor.h"
#include "power_overwhelming/nvml_sensor.h"
#include "power_overwhelming/rtx_sensor.h"
#include "power_overwhelming/stable_power_state_scope.h"
#include "power_overwhelming/tinkerforge_display.h"
#include "power_overwhelming/tinkerforge_sensor.h"


#if !defined(_WIN32)
#define TCHAR char
#define _tmain main
#endif /* !defined(_WIN32) */
