// <copyright file="computer_name_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
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
            typedef char char_type;

            auto size = computer_name(static_cast<char_type *>(nullptr), 0);
            Assert::IsTrue(size > 0, L"Computer name is not empty", LINE_INFO());

            std::vector<char_type> buffer(size);
            computer_name(buffer.data(), buffer.size());
            Assert::AreEqual(buffer.back(), char_type(0), L"Name is null-terminated", LINE_INFO());

            auto name = computer_name<char_type>();
            Assert::AreEqual(size - 1, name.size(), L"String has length of raw API size", LINE_INFO());
            Assert::AreEqual(::strlen(buffer.data()), name.size(), L"String has length of raw string", LINE_INFO());
        }

        TEST_METHOD(test_utf16) {
            typedef wchar_t char_type;

            auto size = computer_name(static_cast<char_type *>(nullptr), 0);
            Assert::IsTrue(size > 0, L"Computer name is not empty", LINE_INFO());

            std::vector<char_type> buffer(size);
            computer_name(buffer.data(), buffer.size());
            Assert::AreEqual(buffer.back(), char_type(0), L"Name is null-terminated", LINE_INFO());

            auto name = computer_name<char_type>();
            Assert::AreEqual(size - 1, name.size(), L"String has length of raw API size", LINE_INFO());
            Assert::AreEqual(::wcslen(buffer.data()), name.size(), L"String has length of raw string", LINE_INFO());
        }
    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
