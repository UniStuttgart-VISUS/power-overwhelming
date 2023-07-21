// <copyright file="oscilloscope_label_test.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(oscilloscope_label_test) {

    public:

        TEST_METHOD(test_default_ctor) {
            oscilloscope_label label;
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
