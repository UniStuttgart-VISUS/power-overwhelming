// <copyright file="pch.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <chrono>
#include <fstream>
#include <iterator>
#include <mutex>
#include <regex>
#include <sstream>
#include <thread>

#include <visus/pwrowg/convert_string.h>
#include <visus/pwrowg/computer_name.h>
#include <visus/pwrowg/cpu_affinity.h>
#include <visus/pwrowg/cpu_info.h>
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
#include <visus/pwrowg/sample.h>
#include <visus/pwrowg/sensor_array.h>
#include <visus/pwrowg/sensor_description.h>

#include <CppUnitTest.h>


#define PWROWG_TEST_NAMESPACE_BEGIN \
PWROWG_NAMESPACE_BEGIN _PWROWG_NAMESPACE_BEGIN(test)

#define PWROWG_TEST_NAMESPACE_END } PWROWG_NAMESPACE_END

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
