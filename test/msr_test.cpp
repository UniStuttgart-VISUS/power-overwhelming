// <copyright file="msr_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(msr_test) {

    public:

        TEST_METHOD(test_rapl_domain_to_string) {
            Assert::AreEqual(L"dram", to_string(rapl_domain::dram), L"dram", LINE_INFO());
            Assert::AreEqual(L"package", to_string(rapl_domain::package), L"package", LINE_INFO());
            Assert::AreEqual(L"pp0", to_string(rapl_domain::pp0), L"pp0", LINE_INFO());
            Assert::AreEqual(L"pp1", to_string(rapl_domain::pp1), L"pp1", LINE_INFO());
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
