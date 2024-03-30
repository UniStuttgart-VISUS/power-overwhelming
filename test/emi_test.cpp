// <copyright file="emi_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
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

    TEST_CLASS(emi_test) {

    public:

        TEST_METHOD(test_for_all) {
            std::vector<emi_sensor> sensors(emi_sensor::for_all(nullptr, 0));
            emi_sensor::for_all(sensors.data(), sensors.size());

            for (auto& s : sensors) {
                Assert::IsNotNull(s.name(), L"Enumerated sensor has a name", LINE_INFO());
            }
        }

        TEST_METHOD(test_for_channel) {
            const auto filter = _T("PKG$");
            const std::basic_regex<TCHAR> rx(filter);

            std::vector<emi_sensor> sensors(emi_sensor::for_channel(nullptr, 0, filter));
            emi_sensor::for_channel(sensors.data(), sensors.size(), filter);


            for (auto &s : sensors) {
                Assert::IsNotNull(s.name(), L"Enumerated sensor has a name", LINE_INFO());
                Assert::IsTrue(std::regex_match(s.name(), rx), L"Name matches filter (must end with channel name)", LINE_INFO());
            }
        }

        TEST_METHOD(test_for_device) {
            const auto filter = _T(".*");
            const std::basic_regex<TCHAR> rx(filter);

            std::vector<emi_sensor> sensors(emi_sensor::for_device(nullptr, 0, filter));
            emi_sensor::for_device(sensors.data(), sensors.size(), filter);


            for (auto &s : sensors) {
                Assert::IsNotNull(s.name(), L"Enumerated sensor has a name", LINE_INFO());
                Assert::IsTrue(std::regex_match(s.name(), rx), L"Name matches filter", LINE_INFO());
            }
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
