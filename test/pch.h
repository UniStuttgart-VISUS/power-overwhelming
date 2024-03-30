// <copyright file="pch.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2021 Visualisierungsinstitut der Universit�t Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph M�ller</author>

#pragma once

#include <chrono>
#include <regex>
#include <sstream>
#include <thread>

#include <power_overwhelming/adl_sensor.h>
#include <power_overwhelming/async_sampling.h>
#include <power_overwhelming/blob.h>
#include <power_overwhelming/collector.h>
#include <power_overwhelming/convert_string.h>
#include <power_overwhelming/computer_name.h>
#include <power_overwhelming/cpu_affinity.h>
#include <power_overwhelming/cpu_info.h>
#include <power_overwhelming/csv_iomanip.h>
#include <power_overwhelming/emi_sensor.h>
#include <power_overwhelming/event.h>
#include <power_overwhelming/for_each_rapl_domain.h>
#include <power_overwhelming/hmc8015_function.h>
#include <power_overwhelming/measurement.h>
#include <power_overwhelming/measurement_data.h>
#include <power_overwhelming/measurement_data_series.h>
#include <power_overwhelming/nvml_sensor.h>
#include <power_overwhelming/oscilloscope_sample.h>
#include <power_overwhelming/parallel_port_trigger.h>
#include <power_overwhelming/rtx_instrument_configuration.h>
#include <power_overwhelming/rtx_sensor.h>
#include <power_overwhelming/rtx_sensor_definition.h>
#include <power_overwhelming/rapl_domain.h>
#include <power_overwhelming/timestamp.h>
#include <power_overwhelming/tinkerforge_sensor_definition.h>

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
