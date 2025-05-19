// <copyright file="hmc8015_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(hmc8015_test) {

public:

    TEST_METHOD(test_hmcfunction_to_string) {
        Assert::AreEqual(L"EMPT", to_string(hmc8015_function::empty), L"empty", LINE_INFO());
        Assert::AreEqual(L"P", to_string(hmc8015_function::active_power), L"active_power", LINE_INFO());
        Assert::AreEqual(L"S", to_string(hmc8015_function::apparent_power), L"apparent_power", LINE_INFO());
        Assert::AreEqual(L"Q", to_string(hmc8015_function::reactive_power), L"reactive_power", LINE_INFO());
        Assert::AreEqual(L"LAMB", to_string(hmc8015_function::power_factor), L"power_factor", LINE_INFO());
        Assert::AreEqual(L"PHI", to_string(hmc8015_function::phase_difference), L"phase_difference", LINE_INFO());
        Assert::AreEqual(L"FU", to_string(hmc8015_function::voltage_frequency), L"voltage_frequency", LINE_INFO());
        Assert::AreEqual(L"FI", to_string(hmc8015_function::current_frequency), L"current_frequency", LINE_INFO());
        Assert::AreEqual(L"URMS", to_string(hmc8015_function::rms_voltage), L"rms_voltage", LINE_INFO());
        Assert::AreEqual(L"UAVG", to_string(hmc8015_function::average_voltage), L"average_voltage", LINE_INFO());
        Assert::AreEqual(L"IRMS", to_string(hmc8015_function::rms_current), L"rms_current", LINE_INFO());
        Assert::AreEqual(L"IAVG", to_string(hmc8015_function::current_average), L"current_average", LINE_INFO());
        Assert::AreEqual(L"UTHD", to_string(hmc8015_function::voltage_distortion), L"voltage_distortion", LINE_INFO());
        Assert::AreEqual(L"ITHD", to_string(hmc8015_function::current_distortion), L"current_distortion", LINE_INFO());
        Assert::AreEqual(L"FPLL", to_string(hmc8015_function::phase_locked_loop_frequency), L"phase_locked_loop_frequency", LINE_INFO());
        Assert::AreEqual(L"TIME", to_string(hmc8015_function::integration_time), L"integration_time", LINE_INFO());
        Assert::AreEqual(L"WH", to_string(hmc8015_function::watt_hour), L"watt_hour", LINE_INFO());
        Assert::AreEqual(L"WHP", to_string(hmc8015_function::positive_watt_hour), L"positive_watt_hour", LINE_INFO());
        Assert::AreEqual(L"WHM", to_string(hmc8015_function::negative_watt_hour), L"negative_watt_hour", LINE_INFO());
        Assert::AreEqual(L"AH", to_string(hmc8015_function::ampere_hour), L"ampere_hour", LINE_INFO());
        Assert::AreEqual(L"AHP", to_string(hmc8015_function::positive_ampere_hour), L"positive_ampere_hour", LINE_INFO());
        Assert::AreEqual(L"AHM", to_string(hmc8015_function::negative_ampere_hour), L"negative_ampere_hour", LINE_INFO());
        Assert::AreEqual(L"URAN", to_string(hmc8015_function::voltage_range), L"voltage_range", LINE_INFO());
        Assert::AreEqual(L"IRAN", to_string(hmc8015_function::current_range), L"current_range", LINE_INFO());
        Assert::ExpectException<std::invalid_argument>([]() {
            to_string((hmc8015_function)UINT_MAX);
        }, L"Illegal function", LINE_INFO());
    }

        TEST_METHOD(test_parse_hmcfunction) {
        Assert::AreEqual(int(hmc8015_function::empty), int(parse_hmc8015_function(L"EMPT")), L"empty", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::active_power), int(parse_hmc8015_function(L"P")), L"active_power", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::apparent_power), int(parse_hmc8015_function(L"S")), L"apparent_power", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::reactive_power), int(parse_hmc8015_function(L"Q")), L"reactive_power", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::power_factor), int(parse_hmc8015_function(L"LAMB")), L"power_factor", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::phase_difference), int(parse_hmc8015_function(L"PHI")), L"phase_difference", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::voltage_frequency), int(parse_hmc8015_function(L"FU")), L"voltage_frequency", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::current_frequency), int(parse_hmc8015_function(L"FI")), L"current_frequency", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::rms_voltage), int(parse_hmc8015_function(L"URMS")), L"rms_voltage", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::average_voltage), int(parse_hmc8015_function(L"UAVG")), L"average_voltage", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::rms_current), int(parse_hmc8015_function(L"IRMS")), L"rms_current", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::current_average), int(parse_hmc8015_function(L"IAVG")), L"current_average", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::voltage_distortion), int(parse_hmc8015_function(L"UTHD")), L"voltage_distortion", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::current_distortion), int(parse_hmc8015_function(L"ITHD")), L"current_distortion", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::phase_locked_loop_frequency), int(parse_hmc8015_function(L"FPLL")), L"phase_locked_loop_frequency", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::integration_time), int(parse_hmc8015_function(L"TIME")), L"integration_time", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::watt_hour), int(parse_hmc8015_function(L"WH")), L"watt_hour", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::positive_watt_hour), int(parse_hmc8015_function(L"WHP")), L"positive_watt_hour", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::negative_watt_hour), int(parse_hmc8015_function(L"WHM")), L"negative_watt_hour", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::ampere_hour),int(parse_hmc8015_function(L"AH")), L"ampere_hour",  LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::positive_ampere_hour), int(parse_hmc8015_function(L"AHP")), L"positive_ampere_hour", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::negative_ampere_hour), int(parse_hmc8015_function(L"AHM")), L"negative_ampere_hour", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::voltage_range), int(parse_hmc8015_function(L"URAN")), L"voltage_range", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::current_range), int(parse_hmc8015_function(L"IRAN")), L"current_range", LINE_INFO());
        Assert::ExpectException<std::invalid_argument>([]() {
            parse_hmc8015_function(L"horst");
        }, L"Illegal function", LINE_INFO());
    }

    TEST_METHOD(test_config) {
        hmc8015_configuration config;
        Assert::IsNull(config.functions(), L"No functions", LINE_INFO());
        Assert::AreEqual(std::size_t(0), config.count_functions(), L"No functions", LINE_INFO());

        config.functions(hmc8015_function::active_power);
        Assert::IsNotNull(config.functions(), L"Have functions", LINE_INFO());
        Assert::AreEqual(std::size_t(1), config.count_functions(), L"Function added", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::active_power), int(*config.functions()), L"Correct function", LINE_INFO());

        config.functions(hmc8015_function::apparent_power);
        Assert::AreEqual(std::size_t(2), config.count_functions(), L"Function added", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::active_power), int(*config.functions()), L"Correct function copied", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::apparent_power), int(*(config.functions() + 1)), L"Correct function added", LINE_INFO());

        std::array<hmc8015_function, 3> functions{
            hmc8015_function::average_voltage,
            hmc8015_function::current_average,
            hmc8015_function::integration_time
        };
        config.functions(functions.data(), functions.size());
        Assert::AreEqual(std::size_t(3), config.count_functions(), L"Functions replaced", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::average_voltage), int(*config.functions()), L"Correct function copied", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::current_average), int(*(config.functions() + 1)), L"Correct function added", LINE_INFO());
        Assert::AreEqual(int(hmc8015_function::integration_time), int(*(config.functions() + 2)), L"Correct function added", LINE_INFO());
    }
};

PWROWG_TEST_NAMESPACE_END
