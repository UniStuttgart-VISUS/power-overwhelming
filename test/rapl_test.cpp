// <copyright file="rapl_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(rapl_test) {

        TEST_METHOD(test_parse_rapl_domain) {
            Assert::AreEqual(int(rapl_domain::package), int(parse_rapl_domain(L"package")), L"Parse package", LINE_INFO());
            Assert::AreEqual(int(rapl_domain::pp0), int(parse_rapl_domain(L"pp0")), L"Parse pp0", LINE_INFO());
            Assert::AreEqual(int(rapl_domain::pp1), int(parse_rapl_domain(L"pp1")), L"Parse pp1", LINE_INFO());
            Assert::AreEqual(int(rapl_domain::dram), int(parse_rapl_domain(L"dram")), L"Parse dram", LINE_INFO());
            Assert::ExpectException<std::invalid_argument>([]() {
                parse_rapl_domain(nullptr);
            }, L"Parse nullptr", LINE_INFO());
            Assert::ExpectException<std::invalid_argument>([]() {
                parse_rapl_domain(L"Bla, bla, bla, Mr Freeman");
            }, L"Parse inexistent string", LINE_INFO());
        }

        TEST_METHOD(test_to_string) {
            Assert::AreEqual(L"package", to_string(rapl_domain::package), L"Stringise package", LINE_INFO());
            Assert::AreEqual(L"pp0", to_string(rapl_domain::pp0), L"Stringise pp0", LINE_INFO());
            Assert::AreEqual(L"pp1", to_string(rapl_domain::pp1), L"Stringise pp1", LINE_INFO());
            Assert::AreEqual(L"dram", to_string(rapl_domain::dram), L"Stringise dram", LINE_INFO());
        }

        TEST_METHOD(test_foreach_template) {
            {
                std::size_t expected = 0;
                const auto actual = for_each_rapl_domain([&expected](const rapl_domain) {
                    ++expected;
                    return true;
                });
                Assert::AreEqual(expected, actual, L"All callbacks invoked", LINE_INFO());
            }

            {
                std::size_t expected = 0;
                const auto actual = for_each_rapl_domain([&expected](const rapl_domain) {
                    ++expected;
                    return false;
                });
                Assert::AreEqual(std::size_t(1), actual, L"Enumeration aborded", LINE_INFO());
                Assert::AreEqual(expected, actual, L"Callback invoked once", LINE_INFO());
            }
        }

        TEST_METHOD(test_foreach_pointer) {
            std::size_t expected = 0;
            const auto actual = for_each_rapl_domain(rapl_domain_counter, &expected);
            Assert::AreEqual(expected, actual, L"All callbacks invoked", LINE_INFO());
        }

        static bool rapl_domain_counter(const rapl_domain, void *counter) {
            ++(*reinterpret_cast<std::size_t *>(counter));
            return true;
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
