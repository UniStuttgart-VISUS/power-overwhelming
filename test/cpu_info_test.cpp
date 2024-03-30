// <copyright file="cpu_vendor_test.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph M�ller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(cpu_info_test) {

    public:

        TEST_METHOD(test_cpu_affinity) {
            thread_affinity_scope scope(0);
        }

        TEST_METHOD(test_cpu_model) {
            cpu_info vendor_and_model[2];
            Assert::IsTrue(get_cpu_info(vendor_and_model, 2) >= 2, L"Vendor and model available", LINE_INFO());
            auto vendor = extract_cpu_vendor(vendor_and_model[1]);
            auto model = extract_cpu_model(vendor_and_model);
        }

        TEST_METHOD(test_get_cpu_vendor) {
            const auto actual = get_cpu_vendor();
            Assert::AreNotEqual(int(cpu_vendor::unknown), int(actual), L"CPU vendor identified", LINE_INFO());
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
