// <copyright file="pch.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <chrono>
#include <iterator>
#include <regex>
#include <sstream>
#include <thread>

#include <visus/pwrowg/atomic_collector.h>
#include <visus/pwrowg/blob.h>
#include <visus/pwrowg/convert_string.h>
#include <visus/pwrowg/computer_name.h>
#include <visus/pwrowg/cpu_affinity.h>
#include <visus/pwrowg/cpu_info.h>
#include <visus/pwrowg/csv_iomanip.h>
#include <visus/pwrowg/csv_sink.h>
#include <visus/pwrowg/event.h>
#include <visus/pwrowg/for_each_rapl_domain.h>
#include <visus/pwrowg/hmc8015_configuration.h>
#include <visus/pwrowg/hmc8015_function.h>
#include <visus/pwrowg/marker_configuration.h>
#include <visus/pwrowg/multi_sz.h>
#include <visus/pwrowg/on_exit.h>
#include <visus/pwrowg/rapl_domain.h>
#include <visus/pwrowg/rtx_sample.h>
#include <visus/pwrowg/parallel_port_trigger.h>
#include <visus/pwrowg/rtx_instrument.h>
#include <visus/pwrowg/rtx_instrument_configuration.h>
#include <visus/pwrowg/rtx_sensor_definition.h>
#include <visus/pwrowg/sample.h>
#include <visus/pwrowg/sensor_array.h>
#include <visus/pwrowg/sensor_description.h>
#include <visus/pwrowg/timestamp.h>

#include <adl_error_category.h>
#include <detect_sample.h>
#include <emi_device.h>
#include <io_util.h>
#include <marker_sensor.h>
#include <msr_magic.h>
#include <msr_sensor.h>
#include <nvml_error_category.h>
#include <nvml_scope.h>
#include <nvml_sensor.h>
#include <rtx_serialisation.h>
#include <sensor_array_impl.h>
#include <sensor_description_builder.h>
#include <sensor_registry.h>
#include <sensor_utilities.h>
#include <setup_api.h>
#include <string_functions.h>
#include <tokenise.h>
#include <transient_driver.h>

#include <CppUnitTest.h>


#define PWROWG_TEST_NAMESPACE_BEGIN \
PWROWG_NAMESPACE_BEGIN _PWROWG_NAMESPACE_BEGIN(test)

#define PWROWG_TEST_NAMESPACE_END } PWROWG_NAMESPACE_END
