// <copyright file="collector_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(collector_test) {

    public:

        TEST_METHOD(test_for_all) {
            auto collector = collector::for_all(L"test.csv");
            Assert::IsTrue(bool(collector), L"New collector is valid.", LINE_INFO());
        }

        TEST_METHOD(test_from_defaults) {
            auto collector = collector::from_defaults();
            Assert::IsTrue(bool(collector), L"New collector is valid.", LINE_INFO());
        }

        TEST_METHOD(test_from_sensor_lists) {
            std::vector<adl_sensor> adl_sensors(adl_sensor::for_all(nullptr, 0));
            adl_sensor::for_all(adl_sensors.data(), adl_sensors.size());
            std::vector<emi_sensor> emi_sensors(emi_sensor::for_all(nullptr, 0));
            emi_sensor::for_all(emi_sensors.data(), emi_sensors.size());
            std::vector<nvml_sensor> nvml_sensors(nvml_sensor::for_all(nullptr, 0));
            nvml_sensor::for_all(nvml_sensors.data(), nvml_sensors.size());

            auto collector = collector::from_sensor_lists(collector_settings(), adl_sensors, emi_sensors, nvml_sensors);
            Assert::IsTrue(bool(collector), L"New collector is valid.", LINE_INFO());
            Assert::IsTrue(std::none_of(adl_sensors.begin(), adl_sensors.end(),
                [](const adl_sensor& s) {return bool(s); }), L"ADL sensors have been moved.", LINE_INFO());
            Assert::IsTrue(std::none_of(emi_sensors.begin(), emi_sensors.end(),
                [](const emi_sensor& s) {return bool(s); }), L"EMI sensors have been moved.", LINE_INFO());
            Assert::IsTrue(std::none_of(nvml_sensors.begin(), nvml_sensors.end(),
                [](const nvml_sensor& s) {return bool(s); }), L"NVML sensors have been moved.", LINE_INFO());
        }

        TEST_METHOD(test_from_sensors) {
            {
                std::vector<adl_sensor> sensors(adl_sensor::for_all(nullptr, 0));
                adl_sensor::for_all(sensors.data(), sensors.size());

                if (!sensors.empty()) {
                    auto collector = collector::from_sensors(collector_settings(), sensors[0]);
                    Assert::IsTrue(bool(collector), L"New collector is valid.", LINE_INFO());
                    Assert::IsFalse(bool(sensors[0]), L"Sensor has been moved.", LINE_INFO());
                }
            }

            {
                std::vector<emi_sensor> sensors(emi_sensor::for_all(nullptr, 0));
                emi_sensor::for_all(sensors.data(), sensors.size());

                if (!sensors.empty()) {
                    auto collector = collector::from_sensors(collector_settings(), sensors[0]);
                    Assert::IsTrue(bool(collector), L"New collector is valid.", LINE_INFO());
                    Assert::IsFalse(bool(sensors[0]), L"Sensor has been moved.", LINE_INFO());
                }
            }

            {
                std::vector<nvml_sensor> sensors(nvml_sensor::for_all(nullptr, 0));
                nvml_sensor::for_all(sensors.data(), sensors.size());

                if (!sensors.empty()) {
                    auto collector = collector::from_sensors(collector_settings(), sensors[0]);
                    Assert::IsTrue(bool(collector), L"New collector is valid.", LINE_INFO());
                    Assert::IsFalse(bool(sensors[0]), L"Sensor has been moved.", LINE_INFO());
                }
            }
        }
    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
