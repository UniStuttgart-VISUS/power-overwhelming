// <copyright file="hmc8015_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

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
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
