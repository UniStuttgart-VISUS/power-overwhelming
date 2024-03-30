// <copyright file="oscilloscope_quantity_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
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

    TEST_CLASS(oscilloscope_quantity_test) {

    public:

        TEST_METHOD(test_default_ctor) {
            oscilloscope_quantity q;
            Assert::AreEqual(0.0f, q.value(), L"Default value", LINE_INFO());
            Assert::AreEqual("", q.unit(), L"Default unit", LINE_INFO());
        }

        TEST_METHOD(test_default_unit_ctor) {
            oscilloscope_quantity q(42.0f);
            Assert::AreEqual(42.0f, q.value(), L"Set value", LINE_INFO());
            Assert::AreEqual("", q.unit(), L"Default unit", LINE_INFO());
        }

        TEST_METHOD(test_set_all_ctor) {
            {
                oscilloscope_quantity q(42.0f, "GF");
                Assert::AreEqual(42.0f, q.value(), L"Set value", LINE_INFO());
                Assert::AreEqual("GF", q.unit(), L"Set unit", LINE_INFO());
            }

            {
                oscilloscope_quantity q(42.0f, L"MT");
                Assert::AreEqual(42.0f, q.value(), L"Set value", LINE_INFO());
                Assert::AreEqual("MT", q.unit(), L"Set unit", LINE_INFO());
            }
        }

        TEST_METHOD(test_copy_ctor) {
            const oscilloscope_quantity q1(42.0f, "PB");
            oscilloscope_quantity q2(q1);

            Assert::AreEqual(42.0f, q1.value(), L"Set value", LINE_INFO());
            Assert::AreEqual("PB", q1.unit(), L"Set unit", LINE_INFO());

            Assert::AreEqual(q1.value(), q2.value(), L"Assigned value", LINE_INFO());
            Assert::AreEqual(q1.unit(), q2.unit(), L"Assigned unit", LINE_INFO());
        }

        TEST_METHOD(test_move_ctor) {
            oscilloscope_quantity q1(42.0f, "km");
            oscilloscope_quantity q2(std::move(q1));

            Assert::AreEqual(42.0f, q2.value(), L"Moved value", LINE_INFO());
            Assert::AreEqual("km", q2.unit(), L"Moved unit", LINE_INFO());

            Assert::AreEqual(0.0f, q1.value(), L"Moved out value", LINE_INFO());
            Assert::AreEqual("", q1.unit(), L"Moved out unit", LINE_INFO());
        }

        TEST_METHOD(test_assign) {
            const oscilloscope_quantity q1(42.0f, "kV");
            oscilloscope_quantity q2(7.0f, "GA");

            Assert::AreEqual(42.0f, q1.value(), L"Set value", LINE_INFO());
            Assert::AreEqual("kV", q1.unit(), L"Set unit", LINE_INFO());

            Assert::AreEqual(7.0f, q2.value(), L"Set value", LINE_INFO());
            Assert::AreEqual("GA", q2.unit(), L"Set unit", LINE_INFO());

            q2 = q1;

            Assert::AreEqual(q1.value(), q2.value(), L"Copied value", LINE_INFO());
            Assert::AreEqual(q2.unit(), q2.unit(), L"Copied unit", LINE_INFO());
        }

        TEST_METHOD(test_move_assign) {
            oscilloscope_quantity q1(42.0f, "kV");
            oscilloscope_quantity q2(7.0f, "GA");

            Assert::AreEqual(42.0f, q1.value(), L"Set value", LINE_INFO());
            Assert::AreEqual("kV", q1.unit(), L"Set unit", LINE_INFO());

            Assert::AreEqual(7.0f, q2.value(), L"Set value", LINE_INFO());
            Assert::AreEqual("GA", q2.unit(), L"Set unit", LINE_INFO());

            q2 = std::move(q1);

            Assert::AreEqual(42.0f, q2.value(), L"Moved value", LINE_INFO());
            Assert::AreEqual("kV", q2.unit(), L"Moved unit", LINE_INFO());

            Assert::AreEqual(0.0f, q1.value(), L"Moved out value", LINE_INFO());
            Assert::AreEqual("", q1.unit(), L"Moved out unit", LINE_INFO());
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
