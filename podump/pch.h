// <copyright file="pch.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
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

#include "visus/pwrowg/atomic_sink.h"
#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/csv_sink.h"
#include "visus/pwrowg/graphics_device.h"
#include "visus/pwrowg/hmc8015_configuration.h"
#include "visus/pwrowg/hmc8015_instrument.h"
#include "visus/pwrowg/rtx_instrument.h"
#include "visus/pwrowg/rtx_instrument_configuration.h"
#include "visus/pwrowg/sensor_array.h"
#include "visus/pwrowg/sensor_filters.h"
#include "visus/pwrowg/stable_power_state_scope.h"
#include "visus/pwrowg/tinkerforge_display.h"
#include "visus/pwrowg/usb_pd_configuration.h"


#if !defined(_WIN32)
#define TCHAR char
#define _tmain main
#endif /* !defined(_WIN32) */
