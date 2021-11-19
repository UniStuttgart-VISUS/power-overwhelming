// <copyright file="nvml_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

#if defined(POWER_OVERWHELMING_WITH_NVML)
    TEST_CLASS(nvml_test) {

    public:

        TEST_METHOD(test_scope) {
            nvml_scope scope;
        }

        TEST_METHOD(test_sensor) {
            {
                auto sensors = nvml_sensor<measurement<>>::for_all();
            }

            Assert::ExpectException<nvml_exception>([](void) {
                auto sensor = nvml_sensor<measurement<>>::from_bus_id(nullptr);
            });

            Assert::ExpectException<nvml_exception>([](void) {
                auto sensor = nvml_sensor<measurement<>>::from_guid(nullptr);
            });

            Assert::ExpectException<nvml_exception>([](void) {
                auto sensor = nvml_sensor<measurement<>>::from_index(UINT_MAX);
            });

            Assert::ExpectException<nvml_exception>([](void) {
                auto sensor = nvml_sensor<measurement<>>::from_serial(nullptr);
            });

            {
                auto sensor = nvml_sensor<measurement<>>::from_index(0);
                auto measurement = sensor.sample();
            }
        }
    };
#endif /* defined(POWER_OVERWHELMING_WITH_NVML) */

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
