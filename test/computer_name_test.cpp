// <copyright file="computer_name_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(computer_name_test) {

    public:

        TEST_METHOD(test_mbcs) {
            auto size = computer_name(static_cast<char *>(nullptr), 0);
            Assert::IsTrue(size > 0, L"Computer name is not empty", LINE_INFO());

            std::vector<char> buffer(size);
            computer_name(buffer.data(), buffer.size());
            Assert::AreEqual(buffer.back(), char(0), L"Name is null-terminated", LINE_INFO());
        }

        TEST_METHOD(test_utf16) {
            auto size = computer_name(static_cast<wchar_t *>(nullptr), 0);
            Assert::IsTrue(size > 0, L"Computer name is not empty", LINE_INFO());

            std::vector<wchar_t> buffer(size);
            computer_name(buffer.data(), buffer.size());
            Assert::AreEqual(buffer.back(), wchar_t(0), L"Name is null-terminated", LINE_INFO());
        }
    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
