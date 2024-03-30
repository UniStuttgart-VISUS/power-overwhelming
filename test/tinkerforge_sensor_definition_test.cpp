// <copyright file="tinkerforge_sensor_definition_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(tinkerforge_sensor_definition_test) {

    public:

        TEST_METHOD(test_ctor) {
            {
                tinkerforge_sensor_definition d;
                Assert::IsNull(d.description(), L"Description is nullptr", LINE_INFO());
                Assert::IsNull(d.uid(), L"UID is nullptr", LINE_INFO());
            }

            {
                tinkerforge_sensor_definition d("horst");
                Assert::IsNull(d.description(), L"Description is nullptr", LINE_INFO());
                Assert::AreEqual("horst", d.uid(), L"UID is \"horst\"", LINE_INFO());
            }

            {
                tinkerforge_sensor_definition d("horst");
                d.description(L"Hugo");
                Assert::AreEqual(L"Hugo", d.description(), L"Description is \"Hugo\"", LINE_INFO());
                Assert::AreEqual("horst", d.uid(), L"UID is \"horst\"", LINE_INFO());

                tinkerforge_sensor_definition dd(d);
                Assert::AreEqual(d.description(), dd.description(), L"Description copied", LINE_INFO());
                Assert::AreEqual(d.uid(), dd.uid(), L"UID copied", LINE_INFO());
            }

            {
                tinkerforge_sensor_definition d("horst");
                d.description(L"Hugo");
                Assert::AreEqual(L"Hugo", d.description(), L"Description is \"Hugo\"", LINE_INFO());
                Assert::AreEqual("horst", d.uid(), L"UID is \"horst\"", LINE_INFO());

                tinkerforge_sensor_definition dd(std::move(d));
                Assert::AreEqual(L"Hugo", dd.description(), L"Description is \"Hugo\"", LINE_INFO());
                Assert::AreEqual("horst", dd.uid(), L"UID is \"horst\"", LINE_INFO());
                Assert::IsNull(d.description(), L"Description source erased.", LINE_INFO());
                Assert::IsNull(d.uid(), L"UID source erased.", LINE_INFO());
            }
        }

        TEST_METHOD(test_assignment) {
            {
                tinkerforge_sensor_definition d("horst");
                d.description(L"Hugo");
                Assert::AreEqual(L"Hugo", d.description(), L"Description is \"Hugo\"", LINE_INFO());
                Assert::AreEqual("horst", d.uid(), L"UID is \"horst\"", LINE_INFO());

                tinkerforge_sensor_definition dd;
                Assert::IsNull(dd.description(), L"Description is nullptr", LINE_INFO());
                Assert::IsNull(dd.uid(), L"UID is nullptr", LINE_INFO());

                dd = d;
                Assert::AreEqual(d.description(), dd.description(), L"Description copied", LINE_INFO());
                Assert::AreEqual(d.uid(), dd.uid(), L"UID copied", LINE_INFO());
            }

            {
                tinkerforge_sensor_definition d("horst");
                d.description(L"Hugo");
                Assert::AreEqual(L"Hugo", d.description(), L"Description is \"Hugo\"", LINE_INFO());
                Assert::AreEqual("horst", d.uid(), L"UID is \"horst\"", LINE_INFO());

                tinkerforge_sensor_definition dd;
                Assert::IsNull(dd.description(), L"Description is nullptr", LINE_INFO());
                Assert::IsNull(dd.uid(), L"UID is nullptr", LINE_INFO());

                dd = std::move(d);
                Assert::AreEqual(L"Hugo", dd.description(), L"Description is \"Hugo\"", LINE_INFO());
                Assert::AreEqual("horst", dd.uid(), L"UID is \"horst\"", LINE_INFO());
                Assert::IsNull(d.description(), L"Description source erased.", LINE_INFO());
                Assert::IsNull(d.uid(), L"UID source erased.", LINE_INFO());
            }
        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
