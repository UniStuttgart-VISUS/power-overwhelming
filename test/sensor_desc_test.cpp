// <copyright file="sensor_desc_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(sensor_desc_test) {

    public:

        TEST_METHOD(test_adl_sensor) {
            typedef detail::sensor_desc<adl_sensor> desc_type;
            Assert::AreEqual("adl_sensor", desc_type::type_name, L"adl_sensor type name", LINE_INFO());
            Assert::IsFalse(desc_type::intrinsic_async, L"adl_sensor not intrinsically asynchronous", LINE_INFO());
        }

        TEST_METHOD(test_emi_sensor) {
            typedef detail::sensor_desc<emi_sensor> desc_type;
            Assert::AreEqual("emi_sensor", desc_type::type_name, L"emi_sensor type name", LINE_INFO());
            Assert::IsFalse(desc_type::intrinsic_async, L"emi_sensor not intrinsically asynchronous", LINE_INFO());
        }


        TEST_METHOD(test_hmc8015_sensor) {
            typedef detail::sensor_desc<hmc8015_sensor> desc_type;
            Assert::AreEqual("hmc8015_sensor", desc_type::type_name, L"hmc8015_sensor type name", LINE_INFO());
            Assert::IsFalse(desc_type::intrinsic_async, L"hmc8015_sensor not intrinsically asynchronous", LINE_INFO());
        }

        TEST_METHOD(test_nvml_sensor) {
            typedef detail::sensor_desc<nvml_sensor> desc_type;
            Assert::AreEqual("nvml_sensor", desc_type::type_name, L"nvml_sensor type name", LINE_INFO());
            Assert::IsFalse(desc_type::intrinsic_async, L"nvml_sensor not intrinsically asynchronous", LINE_INFO());
        }

        TEST_METHOD(test_rtb_sensor) {
            typedef detail::sensor_desc<rtb_sensor> desc_type;
            Assert::AreEqual("rtb_sensor", desc_type::type_name, L"rtb_sensor type name", LINE_INFO());
            Assert::IsFalse(desc_type::intrinsic_async, L"rtb_sensor not intrinsically asynchronous", LINE_INFO());
        }

        TEST_METHOD(test_tinkerforge_sensor) {
            typedef detail::sensor_desc<tinkerforge_sensor> desc_type;
            Assert::AreEqual("tinkerforge_sensor", desc_type::type_name, L"tinkerforge_sensor type name", LINE_INFO());
            Assert::IsTrue(desc_type::intrinsic_async, L"tinkerforge_sensor intrinsically asynchronous", LINE_INFO());
        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
