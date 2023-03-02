// <copyright file="emi_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
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
            auto cnt = emi_sensor::for_all(nullptr, 0);
            std::vector<emi_sensor> sensors(cnt);
            emi_sensor::for_all(sensors.data(), cnt);

            for (auto& s : sensors) {
                auto n = s.name();
                std::vector<std::uint8_t> m(sizeof(EMI_MEASUREMENT_DATA_V2) + (s.channels() - 1) * sizeof(EMI_CHANNEL_MEASUREMENT_DATA));
                auto mm = s.sample(reinterpret_cast<EMI_MEASUREMENT_DATA_V2 *>(m.data()), m.size());
                auto mmm = s.sample(timestamp_resolution::seconds);
            }
        }

    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
