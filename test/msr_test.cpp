// <copyright file="msr_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(msr_test) {

    public:

        TEST_METHOD(test_rapl_domain_to_string) {
            Assert::AreEqual(L"amd_package_energy_status", to_string(rapl_domain::amd_package_energy_status), L"amd_package_energy_status", LINE_INFO());
            Assert::AreEqual(L"amd_pp0_energy_status", to_string(rapl_domain::amd_pp0_energy_status), L"amd_pp0_energy_status", LINE_INFO());
            Assert::AreEqual(L"dram_energy_status", to_string(rapl_domain::dram_energy_status), L"dram_energy_status", LINE_INFO());
            Assert::AreEqual(L"dram_performance_status", to_string(rapl_domain::dram_performance_status), L"dram_performance_status", LINE_INFO());
            Assert::AreEqual(L"dram_power_info", to_string(rapl_domain::dram_power_info), L"dram_power_info", LINE_INFO());
            Assert::AreEqual(L"dram_power_limit", to_string(rapl_domain::dram_power_limit), L"dram_power_limit", LINE_INFO());
            Assert::AreEqual(L"intel_package_energy_status", to_string(rapl_domain::intel_package_energy_status), L"intel_package_energy_status", LINE_INFO());
            Assert::AreEqual(L"intel_pp0_energy_status", to_string(rapl_domain::intel_pp0_energy_status), L"intel_pp0_energy_status", LINE_INFO());
            Assert::AreEqual(L"package_performance_status", to_string(rapl_domain::package_performance_status), L"package_performance_status", LINE_INFO());
            Assert::AreEqual(L"package_power_info", to_string(rapl_domain::package_power_info), L"package_power_info", LINE_INFO());
            Assert::AreEqual(L"package_power_limit", to_string(rapl_domain::package_power_limit), L"package_power_limit", LINE_INFO());
            Assert::AreEqual(L"platform_energy_status", to_string(rapl_domain::platform_energy_status), L"platform_energy_status", LINE_INFO());
            Assert::AreEqual(L"pp0_performance_status", to_string(rapl_domain::pp0_performance_status), L"pp0_performance_status", LINE_INFO());
            Assert::AreEqual(L"pp0_policy", to_string(rapl_domain::pp0_policy), L"pp0_policy", LINE_INFO());
            Assert::AreEqual(L"pp0_power_limit", to_string(rapl_domain::pp0_power_limit), L"pp0_power_limit", LINE_INFO());
            Assert::AreEqual(L"pp1_energy_status", to_string(rapl_domain::pp1_energy_status), L"pp1_energy_status", LINE_INFO());
            Assert::AreEqual(L"pp1_policy", to_string(rapl_domain::pp1_policy), L"pp1_policy", LINE_INFO());
            Assert::AreEqual(L"pp1_power_limit", to_string(rapl_domain::pp1_power_limit), L"pp1_power_limit", LINE_INFO());
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
