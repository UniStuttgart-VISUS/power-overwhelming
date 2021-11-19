// <copyright file="adl_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(adl_test) {

    public:

        TEST_METHOD(test_exception) {
            {
                adl_exception ex(ADL_OK);
                Assert::AreEqual("The ADL function completed successfully.", ex.what(), L"ADL_OK message", LINE_INFO());
            }
        }

        TEST_METHOD(test_singleton) {
            auto& a = adl::instance();
        }
    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
