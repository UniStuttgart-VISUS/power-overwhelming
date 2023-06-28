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

        TEST_METHOD(test_safe_duplicate_wchar_t) {
            typedef wchar_t char_type;

            {
                const char_type *expected = L"input";
                auto actual = detail::safe_duplicate(expected);
                Assert::AreEqual(expected, actual, L"Duplicate matches", LINE_INFO());
                Assert::AreNotEqual((void *) expected, (void *) actual, L"Duplicate is different pointer", LINE_INFO());
                ::free(actual);
            }

            {
                const char_type *expected = nullptr;
                auto actual = detail::safe_duplicate(expected);
                Assert::IsNull(actual, L"Copy is nullptr", LINE_INFO());
                Assert::AreEqual(expected, actual, L"Duplicate matches", LINE_INFO());
            }
        }

        TEST_METHOD(test_safe_duplicate_char) {
            typedef char char_type;

            {
                const char_type *expected = "input";
                auto actual = detail::safe_duplicate(expected);
                Assert::AreEqual(expected, actual, L"Duplicate matches", LINE_INFO());
                Assert::AreNotEqual((void *) expected, (void *) actual, L"Duplicate is different pointer", LINE_INFO());
                ::free(actual);
            }

            {
                const char_type *expected = nullptr;
                auto actual = detail::safe_duplicate(expected);
                Assert::IsNull(actual, L"Copy is nullptr", LINE_INFO());
                Assert::AreEqual(expected, actual, L"Duplicate matches", LINE_INFO());
            }
        }

        TEST_METHOD(test_safe_assign) {
            {
                const auto expected = L"input";
                wchar_t *actual = nullptr;
                detail::safe_assign(actual, expected);
                Assert::AreEqual(expected, actual, L"Duplicate matches", LINE_INFO());
                Assert::AreNotEqual((void *) expected, (void *) actual, L"Duplicate is different pointer", LINE_INFO());
                ::free(actual);
            }

            {
                const wchar_t *expected = ::wcsdup(L"input");
                wchar_t *actual = nullptr;
                detail::safe_assign(actual, expected);
                Assert::AreEqual(expected, actual, L"Duplicate matches", LINE_INFO());
                Assert::AreNotEqual((void *)expected, (void *)actual, L"Duplicate is different pointer", LINE_INFO());
                ::free(actual);
                ::free((void *) expected);
            }

            {
                const wchar_t *expected = ::wcsdup(L"input");
                wchar_t *actual = ::wcsdup(L"actual");
                detail::safe_assign(actual, expected);
                Assert::AreEqual(expected, actual, L"Duplicate matches", LINE_INFO());
                Assert::AreNotEqual((void *)expected, (void *)actual, L"Duplicate is different pointer", LINE_INFO());
                ::free(actual);
                ::free((void *) expected);
            }

            {
                const wchar_t *expected = L"input";
                wchar_t *input = ::wcsdup(expected);
                wchar_t *actual = ::wcsdup(L"actual");
                detail::safe_assign(actual, std::move(input));
                Assert::AreEqual(expected, actual, L"Duplicate matches", LINE_INFO());
                Assert::AreNotEqual((void *) expected, (void *) actual, L"Duplicate is different pointer", LINE_INFO());
                Assert::IsNull(input, L"Input has been moved", LINE_INFO());
                ::free(actual);
                ::free(input);
            }

        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
