// <copyright file="msr_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
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

        TEST_METHOD(test_for_all) {
            std::vector<msr_sensor> sensors(msr_sensor::for_all(nullptr, 0));
            msr_sensor::for_all(sensors.data(), sensors.size());
            Assert::AreEqual(std::size_t(0), sensors.size(), L"MSR is not supported on Windows", LINE_INFO());
        }

        TEST_METHOD(test_support) {
            // We test the default support check, which is the same for all vendors.
            auto actual = detail::is_rapl_energy_supported(0, rapl_domain::package);
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
