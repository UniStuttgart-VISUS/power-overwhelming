// <copyright file="emi_test.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

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
        }

    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
