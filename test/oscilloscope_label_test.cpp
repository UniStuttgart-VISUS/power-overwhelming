// <copyright file="rtx_label_test.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph M�ller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(rtx_label_test) {

    public:

        TEST_METHOD(test_default_ctor) {
            rtx_label label;
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
