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

        TEST_METHOD(test_format_string) {
            typedef char char_type;

            {
                const char_type *expected = "input";
                auto actual = detail::format_string(expected);
                Assert::AreEqual(expected, actual.c_str(), L"Format string without parameters", LINE_INFO());
            }

            {
                const char_type *expected = "input";
                auto actual = detail::format_string("%s", expected);
                Assert::AreEqual(expected, actual.c_str(), L"Format whole string", LINE_INFO());
            }

            {
                const char_type *expected = "12";
                auto actual = detail::format_string("%d%d", 1, 2);
                Assert::AreEqual(expected, actual.c_str(), L"Format two ints", LINE_INFO());
            }
        }

        TEST_METHOD(test_format_wstring) {
            typedef wchar_t char_type;

            {
                const char_type *expected = L"input";
                auto actual = detail::format_string(expected);
                Assert::AreEqual(expected, actual.c_str(), L"Format string without parameters", LINE_INFO());
            }

            {
                const char_type *expected = L"input";
                auto actual = detail::format_string(L"%s", expected);
                Assert::AreEqual(expected, actual.c_str(), L"Format whole string", LINE_INFO());
            }

            {
                const char_type *expected = L"12";
                auto actual = detail::format_string(L"%d%d", 1, 2);
                Assert::AreEqual(expected, actual.c_str(), L"Format two ints", LINE_INFO());
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

        TEST_METHOD(test_parse_float) {
            {
                const auto actual = detail::parse_float(nullptr);
                Assert::AreEqual(0.0f, actual, L"nullptr", LINE_INFO());
            }

            {
                const auto actual = detail::parse_float("");
                Assert::AreEqual(0.0f, actual, L"empty", LINE_INFO());
            }

            {
                const auto actual = detail::parse_float("horst");
                Assert::AreEqual(0.0f, actual, L"horst", LINE_INFO());
            }

            {
                const auto actual = detail::parse_float("1.2");
                Assert::AreEqual(1.2f, actual, L"1.2", LINE_INFO());
            }

            {
                const auto actual = detail::parse_float("1e1");
                Assert::AreEqual(10.0f, actual, L"1e1", LINE_INFO());
            }
        }

        TEST_METHOD(test_parse_int) {
            {
                const auto actual = detail::parse_int(nullptr);
                Assert::AreEqual(0, actual, L"nullptr", LINE_INFO());
            }

            {
                const auto actual = detail::parse_int("");
                Assert::AreEqual(0, actual, L"empty", LINE_INFO());
            }

            {
                const auto actual = detail::parse_int("horst");
                Assert::AreEqual(0, actual, L"horst", LINE_INFO());
            }

            {
                const auto actual = detail::parse_int("1");
                Assert::AreEqual(1, actual, L"1.2", LINE_INFO());
            }

            {
                const auto actual = detail::parse_int("1bla");
                Assert::AreEqual(1, actual, L"1bla", LINE_INFO());
            }
        }

        TEST_METHOD(test_equals_string) {
            Assert::IsTrue(detail::equals((char *) nullptr, (char *) nullptr), L"nullptr", LINE_INFO());
            Assert::IsFalse(detail::equals((char *) nullptr, "bla"), L"nullptr vs. string", LINE_INFO());
            Assert::IsTrue(detail::equals("bla", "bla"), L"bla, bla", LINE_INFO());
            Assert::IsFalse(detail::equals("bla", "BLA"), L"bla, BLA", LINE_INFO());
            Assert::IsTrue(detail::equals("bla", "BLA", true), L"bla, BLA case-insensitive", LINE_INFO());
            Assert::IsTrue(detail::equals(std::string("bla"), "BLA", true), L"string left", LINE_INFO());
            Assert::IsTrue(detail::equals("bla", std::string("BLA"), true), L"string right", LINE_INFO());
            Assert::IsTrue(detail::equals(std::string("bla"), std::string("BLA"), true), L"string both", LINE_INFO());
        }

        TEST_METHOD(test_equals_wstring) {
            Assert::IsTrue(detail::equals((wchar_t *) nullptr, (wchar_t *) nullptr), L"nullptr", LINE_INFO());
            Assert::IsFalse(detail::equals((wchar_t *) nullptr, L"bla"), L"nullptr vs. string", LINE_INFO());
            Assert::IsTrue(detail::equals(L"bla", L"bla"), L"bla, bla", LINE_INFO());
            Assert::IsFalse(detail::equals(L"bla", L"BLA"), L"bla, BLA", LINE_INFO());
            Assert::IsTrue(detail::equals(L"bla", L"BLA", true), L"bla, BLA case-insensitive", LINE_INFO());
            Assert::IsTrue(detail::equals(std::wstring(L"bla"), L"BLA", true), L"string left", LINE_INFO());
            Assert::IsTrue(detail::equals(L"bla", std::wstring(L"BLA"), true), L"string right", LINE_INFO());
            Assert::IsTrue(detail::equals(std::wstring(L"bla"), std::wstring(L"BLA"), true), L"string both", LINE_INFO());
        }

        TEST_METHOD(test_starts_with_string) {
            Assert::IsTrue(detail::starts_with((char *) nullptr, (char *) nullptr), L"nullptr, nullptr", LINE_INFO());
            Assert::IsTrue(detail::starts_with("bla", (char *) nullptr), L"bla, nullptr", LINE_INFO());
            Assert::IsFalse(detail::starts_with((char *) nullptr, "bla"), L"nullptr, bla", LINE_INFO());
            Assert::IsFalse(detail::starts_with("", "bla"), L"\"\", bla", LINE_INFO());
            Assert::IsTrue(detail::starts_with("foo", "foo"), L"foo, foo", LINE_INFO());
            Assert::IsTrue(detail::starts_with("foobar", "foo"), L"foobar, foo", LINE_INFO());
            Assert::IsFalse(detail::starts_with("foo", "foobar"), L"foo, foobar", LINE_INFO());
        }

        TEST_METHOD(test_starts_with_wstring) {
            Assert::IsTrue(detail::starts_with((wchar_t *) nullptr, (wchar_t *) nullptr), L"nullptr, nullptr", LINE_INFO());
            Assert::IsTrue(detail::starts_with(L"bla", (wchar_t *) nullptr), L"bla, nullptr", LINE_INFO());
            Assert::IsFalse(detail::starts_with((wchar_t *) nullptr, L"bla"), L"nullptr, bla", LINE_INFO());
            Assert::IsFalse(detail::starts_with(L"", L"bla"), L"\"\", bla", LINE_INFO());
            Assert::IsTrue(detail::starts_with(L"foo", L"foo"), L"foo, foo", LINE_INFO());
            Assert::IsTrue(detail::starts_with(L"foobar", L"foo"), L"foobar, foo", LINE_INFO());
            Assert::IsFalse(detail::starts_with(L"foo", L"foobar"), L"foo, foobar", LINE_INFO());
        }

        TEST_METHOD(test_trim_end_if_string) {
            Assert::IsNull(detail::trim_end_if((char *) nullptr, [](const char c) { return true; }), L"nullptr", LINE_INFO());

            {
                auto str = "bla";
                Assert::IsTrue(detail::trim_end_if(str, [](const char c) { return true; }) == str, L"trim all", LINE_INFO());
            }

            {
                auto str = "blaaa";
                Assert::IsTrue(detail::trim_end_if(str, [](const char c) { return c == 'a'; }) == (str + 2), L"trim a", LINE_INFO());
            }

            {
                auto str = "bla\r\n\t ";
                Assert::IsTrue(detail::trim_end_if(str, [](const char c) { return std::isspace(c); }) == (str + 3), L"trim space", LINE_INFO());
            }
        }

        TEST_METHOD(test_trim_end_if_wstring) {
            typedef wchar_t char_type;
            Assert::IsNull(detail::trim_end_if((char_type *) nullptr, [](const char_type c) { return true; }), L"nullptr", LINE_INFO());

            {
                auto str = L"bla";
                Assert::IsTrue(detail::trim_end_if(str, [](const char_type c) { return true; }) == str, L"trim all", LINE_INFO());
            }

            {
                auto str = L"blaaa";
                Assert::IsTrue(detail::trim_end_if(str, [](const char_type c) { return c == L'a'; }) == (str + 2), L"trim a", LINE_INFO());
            }

            {
                auto str = L"bla\r\n\t ";
                Assert::IsTrue(detail::trim_end_if(str, [](const char_type c) { return std::isspace(c); }) == (str + 3), L"trim space", LINE_INFO());
            }
        }

        TEST_METHOD(test_trim_if_string) {
            typedef char char_type;
            Assert::IsNull(detail::trim_if((char_type *) nullptr, [](const char_type c) {return true; }), L"nullptr", LINE_INFO());

            {
                char_type str[] = "bla";
                Assert::AreEqual("", detail::trim_if(str, [](const char_type c) { return true; }), L"trim all", LINE_INFO());
            }

            {
                char_type str[] = "bla";
                Assert::AreEqual(str, detail::trim_if(str, [](const char_type c) { return false; }), L"trim nothing", LINE_INFO());
            }

            {
                char_type str[] = "ablahaa";
                auto actual = detail::trim_if(str, [](const char_type c) { return c == 'a'; });
                Assert::AreEqual("blah", actual, L"trim a", LINE_INFO());
            }

            {
                char_type str[] = "\r\t\nbla\r\n\t ";
                Assert::AreEqual("bla", detail::trim_if(str, [](const char_type c) { return std::isspace(c); }), L"trim space", LINE_INFO());
            }
        }

        TEST_METHOD(test_trim_if_wstring) {
            typedef wchar_t char_type;
            Assert::IsNull(detail::trim_if((char_type *) nullptr, [](const char_type c) {return true; }), L"nullptr", LINE_INFO());

            {
                char_type str[] = L"bla";
                Assert::AreEqual(L"", detail::trim_if(str, [](const char_type c) { return true; }), L"trim all", LINE_INFO());
            }

            {
                char_type str[] = L"bla";
                Assert::AreEqual(str, detail::trim_if(str, [](const char_type c) { return false; }), L"trim nothing", LINE_INFO());
            }

            {
                char_type str[] = L"ablahaa";
                auto actual = detail::trim_if(str, [](const char_type c) { return c == L'a'; });
                Assert::AreEqual(L"blah", actual, L"trim a", LINE_INFO());
            }

            {
                char_type str[] = L"\r\t\nbla\r\n\t ";
                Assert::AreEqual(L"bla", detail::trim_if(str, [](const char_type c) { return std::isspace(c); }), L"trim space", LINE_INFO());
            }
        }

        TEST_METHOD(test_trim_eol_string) {
            typedef char char_type;

            {
                char_type str[] = "bla";
                detail::trim_eol(str);
                Assert::AreEqual("bla", str, L"bla", LINE_INFO());
            }

            {
                char_type str[] = "bla\r";
                detail::trim_eol(str);
                Assert::AreEqual("bla", str, L"bla\\r", LINE_INFO());
            }

            {
                char_type str[] = "bla\r\n";
                detail::trim_eol(str);
                Assert::AreEqual("bla", str, L"bla\\r\\n", LINE_INFO());
            }

            {
                char_type str[] = "bla\n";
                detail::trim_eol(str);
                Assert::AreEqual("bla", str, L"bla\\n", LINE_INFO());
            }

            {
                char_type str[] = "bla\n\r";
                detail::trim_eol(str);
                Assert::AreEqual("bla", str, L"bla\\n\\r", LINE_INFO());
            }
        }

        TEST_METHOD(test_trim_eol_wstring) {
            typedef wchar_t char_type;

            {
                char_type str[] = L"bla";
                detail::trim_eol(str);
                Assert::AreEqual(L"bla", str, L"bla", LINE_INFO());
            }

            {
                char_type str[] = L"bla\r";
                detail::trim_eol(str);
                Assert::AreEqual(L"bla", str, L"bla\\r", LINE_INFO());
            }

            {
                char_type str[] = L"bla\r\n";
                detail::trim_eol(str);
                Assert::AreEqual(L"bla", str, L"bla\\r\\n", LINE_INFO());
            }

            {
                char_type str[] = L"bla\n";
                detail::trim_eol(str);
                Assert::AreEqual(L"bla", str, L"bla\\n", LINE_INFO());
            }

            {
                char_type str[] = L"bla\n\r";
                detail::trim_eol(str);
                Assert::AreEqual(L"bla", str, L"bla\\n\\r", LINE_INFO());
            }
        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
