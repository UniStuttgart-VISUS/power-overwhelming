// <copyright file="cpu_vendor_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(cpu_vendor_test) {

    public:

        TEST_METHOD(test_cpu_affinity) {
            thread_affinity_restore_point restore;
            set_thread_affinity(0);
        }

        TEST_METHOD(test_get_cpu_vendor) {
            const auto actual = get_cpu_vendor();
            Assert::AreNotEqual(int(cpu_vendor::unknown), int(actual), L"CPU vendor identified", LINE_INFO());
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
