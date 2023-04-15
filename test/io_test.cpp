// <copyright file="io_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(io_test) {

    public:

        TEST_METHOD(test_read_all_bytes) {
            std::array<char, 16> expected;
            std::generate(expected.begin(), expected.end(), [](void) {
                static char i = 0;
                return i++;
            });

            std::ofstream test_stream("io_test", std::ios::trunc);
            test_stream.write(expected.data(), expected.size());
            test_stream.close();

            {
                auto fd = ::open("io_test", O_WRONLY);
                Assert::IsFalse(fd < 0, L"File descriptor valid", LINE_INFO());
                Assert::ExpectException<std::system_error>([fd](void) {
                    auto actual = detail::read_all_bytes(fd);
                }, L"Reading from write-only file handle causes exception", LINE_INFO());
            }

            {
                auto fd = ::open("io_test", O_RDONLY);
                auto actual = detail::read_all_bytes(fd);
                Assert::AreEqual(expected.size(), actual.size(), L"Expected number of bytes read", LINE_INFO());
                Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin(), actual.end()), L"Content matches", LINE_INFO());
            }
        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
