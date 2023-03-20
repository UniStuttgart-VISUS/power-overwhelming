// <copyright file="string_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    /// <summary>
    /// Tests for string-related functions.
    /// </summary>
    TEST_CLASS(string_test) {

    public:

        TEST_METHOD(test_convert_char_char) {
            typedef char src_type;
            typedef char dst_type;

            {
                const std::basic_string<dst_type> expected = "input";
                const src_type *input = "input";
                Assert::AreEqual(expected, convert_string<dst_type>(input), L"standard input", LINE_INFO());
            }

            {
                const std::basic_string<dst_type> expected = "";
                const src_type *input = "";
                Assert::AreEqual(expected, convert_string<dst_type>(input), L"empty conversion", LINE_INFO());
            }

            {
                const std::basic_string<dst_type> expected = "";
                const src_type *input = nullptr;
                Assert::AreEqual(expected, convert_string<dst_type>(input), L"nullptr conversion", LINE_INFO());
            }
        }

        TEST_METHOD(test_convert_char_wchar_t) {
            typedef char src_type;
            typedef wchar_t dst_type;

            {
                const std::basic_string<dst_type> expected = L"input";
                const src_type *input = "input";
                Assert::AreEqual(expected, convert_string<dst_type>(input), L"standard input", LINE_INFO());
            }

            {
                const std::basic_string<dst_type> expected = L"";
                const src_type *input = "";
                Assert::AreEqual(expected, convert_string<dst_type>(input), L"empty conversion", LINE_INFO());
            }

            {
                const std::basic_string<dst_type> expected = L"";
                const src_type *input = nullptr;
                Assert::AreEqual(expected, convert_string<dst_type>(input), L"nullptr conversion", LINE_INFO());
            }
        }

        TEST_METHOD(test_convert_wchar_t_char) {
            typedef wchar_t src_type;
            typedef char dst_type;

            {
                const std::basic_string<dst_type> expected = "input";
                const src_type *input = L"input";
                Assert::AreEqual(expected, convert_string<dst_type>(input), L"standard input", LINE_INFO());
            }

            {
                const std::basic_string<dst_type> expected = "";
                const src_type *input = L"";
                Assert::AreEqual(expected, convert_string<dst_type>(input), L"empty conversion", LINE_INFO());
            }

            {
                const std::basic_string<dst_type> expected = "";
                const src_type *input = nullptr;
                Assert::AreEqual(expected, convert_string<dst_type>(input), L"nullptr conversion", LINE_INFO());
            }
        }

        TEST_METHOD(test_convert_wchar_t_wchar_t) {
            typedef wchar_t src_type;
            typedef wchar_t dst_type;

            {
                const std::basic_string<dst_type> expected = L"input";
                const src_type *input = L"input";
                Assert::AreEqual(expected, convert_string<dst_type>(input), L"standard input", LINE_INFO());
            }

            {
                const std::basic_string<dst_type> expected = L"";
                const src_type *input = L"";
                Assert::AreEqual(expected, convert_string<dst_type>(input), L"empty conversion", LINE_INFO());
            }

            {
                const std::basic_string<dst_type> expected = L"";
                const src_type *input = nullptr;
                Assert::AreEqual(expected, convert_string<dst_type>(input), L"nullptr conversion", LINE_INFO());
            }
        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
