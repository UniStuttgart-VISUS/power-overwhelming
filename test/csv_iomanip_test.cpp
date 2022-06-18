// <copyright file="csv_iomanip_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(csv_iomanip_test) {

    public:

        TEST_METHOD(test_char_delimiter) {
            Assert::AreEqual(long(0), std::cout.iword(detail::io_index_delimiter()), L"No delimiter set", LINE_INFO());
            Assert::AreEqual('\t', getcsvdelimiter(std::cout), L"Fallback retrieved.", LINE_INFO());
            std::cout << setcsvdelimiter(';');
            Assert::AreEqual(long(';'), std::cout.iword(detail::io_index_delimiter()), L"Delimiter set", LINE_INFO());
            Assert::AreEqual(';', getcsvdelimiter(std::cout), L"Delimiter retrieved.", LINE_INFO());
        }

        TEST_METHOD(test_char_quote) {
            Assert::AreEqual(long(0), std::cout.iword(detail::io_index_quote_char()), L"No quote set", LINE_INFO());
            Assert::AreEqual('"', getcsvquote(std::cout), L"Fallback retrieved.", LINE_INFO());
            std::cout << setcsvquote('\'');
            Assert::AreEqual(long('\''), std::cout.iword(detail::io_index_quote_char()), L"Quote set", LINE_INFO());
            Assert::AreEqual('\'', getcsvquote(std::cout), L"Quote retrieved.", LINE_INFO());
        }

        TEST_METHOD(test_header) {
            Assert::AreEqual(long(0), std::cout.iword(detail::io_index_header()), L"Print data", LINE_INFO());
            std::cout << csvheader;
            Assert::AreEqual(long(1), std::cout.iword(detail::io_index_header()), L"Print header", LINE_INFO());
            std::cout << csvdata;
            Assert::AreEqual(long(0), std::cout.iword(detail::io_index_header()), L"Print data", LINE_INFO());
        }

        TEST_METHOD(test_print_stringstream) {
            const measurement dummy(L"dummy", 9999, 1, 2, 3);

            {
                std::stringstream stream;
                stream << csvheader << dummy;
                auto actual = stream.str();
                auto expected = std::string("\"sensor\"\t\"timestamp\"\t\"valid\"\t\"voltage\"\t\"current\"\t\"power\"");
                Assert::AreEqual(expected, actual, L"Default CSV header.", LINE_INFO());
            }

            {
                std::stringstream stream;
                stream << csvheader << setcsvdelimiter(';') << setcsvquote('\'') << dummy;
                auto actual = stream.str();
                auto expected = std::string("'sensor';'timestamp';'valid';'voltage';'current';'power'");
                Assert::AreEqual(expected, actual, L"CSV header with ; delimiter.", LINE_INFO());
            }

            {
                std::stringstream stream;
                stream << dummy;
                auto actual = stream.str();
                auto expected = std::string("\"dummy\"\t9999\t1\t1\t2\t3");
                Assert::AreEqual(expected, actual, L"Default CSV line.", LINE_INFO());
            }

            {
                std::stringstream stream;
                stream << setcsvdelimiter(';') << setcsvquote('\'') << dummy;
                auto actual = stream.str();
                auto expected = std::string("'dummy';9999;1;1;2;3");
                Assert::AreEqual(expected, actual, L"Default CSV line.", LINE_INFO());
            }
        }

        TEST_METHOD(test_print_wstringstream) {
            const measurement dummy(L"dummy", 9999, 1, 2, 3);

            {
                std::wstringstream stream;
                stream << csvheader << dummy;
                auto actual = stream.str();
                auto expected = std::wstring(L"\"sensor\"\t\"timestamp\"\t\"valid\"\t\"voltage\"\t\"current\"\t\"power\"");
                Assert::AreEqual(expected, actual, L"Default CSV header.", LINE_INFO());
            }

            {
                std::wstringstream stream;
                stream << csvheader << setcsvdelimiter(L';') << setcsvquote(L'\'') << dummy;
                auto actual = stream.str();
                auto expected = std::wstring(L"'sensor';'timestamp';'valid';'voltage';'current';'power'");
                Assert::AreEqual(expected, actual, L"CSV header with ; delimiter.", LINE_INFO());
            }

            {
                std::wstringstream stream;
                stream << dummy;
                auto actual = stream.str();
                auto expected = std::wstring(L"\"dummy\"\t9999\t1\t1\t2\t3");
                Assert::AreEqual(expected, actual, L"Default CSV line.", LINE_INFO());
            }

            {
                std::wstringstream stream;
                stream << setcsvdelimiter(L';') << setcsvquote(L'\'') << dummy;
                auto actual = stream.str();
                auto expected = std::wstring(L"'dummy';9999;1;1;2;3");
                Assert::AreEqual(expected, actual, L"Default CSV line.", LINE_INFO());
            }
        }

        TEST_METHOD(test_quote) {
            Assert::AreEqual(long(0), std::cout.iword(detail::io_index_quote()), L"Quote set", LINE_INFO());
            std::cout << csvnoquote;
            Assert::AreEqual(long(1), std::cout.iword(detail::io_index_quote()), L"No-quote set", LINE_INFO());
            std::cout << csvquote;
            Assert::AreEqual(long(0), std::cout.iword(detail::io_index_quote()), L"Quote set", LINE_INFO());
        }

        TEST_METHOD(test_wchar_delimiter) {
            Assert::AreEqual(long(0), std::wcout.iword(detail::io_index_delimiter()), L"No delimiter set", LINE_INFO());
            Assert::AreEqual(L'\t', getcsvdelimiter(std::wcout), L"Fallback retrieved.", LINE_INFO());
            std::wcout << setcsvdelimiter(L';');
            Assert::AreEqual(long(';'), std::wcout.iword(detail::io_index_delimiter()), L"Delimiter set", LINE_INFO());
            Assert::AreEqual(L';', getcsvdelimiter(std::wcout), L"Delimiter retrieved.", LINE_INFO());
        }

        TEST_METHOD(test_wchar_quote) {
            Assert::AreEqual(long(0), std::wcout.iword(detail::io_index_quote_char()), L"No quote set", LINE_INFO());
            Assert::AreEqual(L'"', getcsvquote(std::wcout), L"Fallback retrieved.", LINE_INFO());
            std::wcout << setcsvquote(L'\'');
            Assert::AreEqual(long('\''), std::wcout.iword(detail::io_index_quote_char()), L"Quote set", LINE_INFO());
            Assert::AreEqual(L'\'', getcsvquote(std::wcout), L"Quote retrieved.", LINE_INFO());
        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
