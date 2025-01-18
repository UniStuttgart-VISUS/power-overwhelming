// <copyright file="pch.h" company="Visualisierungsinstitut der Universität Stuttgart">
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

#include "visus/pwrowg/adl_sensor.h"
#include "visus/pwrowg/adl_thermal_sensor.h"
#include "visus/pwrowg/adl_throttling_sensor.h"
#include "visus/pwrowg/emi_sensor.h"
#include "visus/pwrowg/collector.h"
#include "visus/pwrowg/graphics_device.h"
#include "visus/pwrowg/hmc8015_sensor.h"
#include "visus/pwrowg/measurement.h"
#include "visus/pwrowg/msr_sensor.h"
#include "visus/pwrowg/nvml_sensor.h"
#include "visus/pwrowg/rtx_sensor.h"
#include "visus/pwrowg/stable_power_state_scope.h"
#include "visus/pwrowg/tinkerforge_display.h"
#include "visus/pwrowg/tinkerforge_sensor.h"


#if !defined(_WIN32)
#define TCHAR char
#define _tmain main
#endif /* !defined(_WIN32) */
