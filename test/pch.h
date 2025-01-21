// <copyright file="pch.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <chrono>
#include <regex>
#include <sstream>
#include <thread>

#include <visus/pwrowg/blob.h>
#include <visus/pwrowg/collector.h>
#include <visus/pwrowg/convert_string.h>
#include <visus/pwrowg/computer_name.h>
#include <visus/pwrowg/cpu_affinity.h>
#include <visus/pwrowg/cpu_info.h>
#include <visus/pwrowg/csv_iomanip.h>
#include <visus/pwrowg/event.h>
#include <visus/pwrowg/for_each_rapl_domain.h>
#include <visus/pwrowg/hmc8015_function.h>
#include <visus/pwrowg/measurement.h>
#include <visus/pwrowg/measurement_data.h>
#include <visus/pwrowg/measurement_data_series.h>
#include <visus/pwrowg/rtx_sample.h>
#include <visus/pwrowg/parallel_port_trigger.h>
#include <visus/pwrowg/rtx_instrument_configuration.h>
#include <visus/pwrowg/rtx_sensor.h>
#include <visus/pwrowg/rtx_sensor_definition.h>
#include <visus/pwrowg/rapl_domain.h>
#include <visus/pwrowg/timestamp.h>
#include <visus/pwrowg/tinkerforge_sensor_definition.h>

#include <adl_exception.h>
#include <emi_device.h>
#include <io_util.h>
#include <on_exit.h>
#include <msr_magic.h>
#include <nvml_exception.h>
#include <nvml_scope.h>
#include <rtx_serialisation.h>
#include <sensor_desc.h>
#include <setup_api.h>
#include <string_functions.h>

#include <CppUnitTest.h>
