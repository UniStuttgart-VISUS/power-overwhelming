// <copyright file="io_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace PWROWG_NAMESPACE;


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

            std::ofstream test_stream("io_test", std::ios::binary | std::ios::trunc);
            test_stream.write(expected.data(), expected.size());
            test_stream.close();

            {
                auto fd = detail::open("io_test", O_WRONLY);
                Assert::IsFalse(fd < 0, L"Posix file descriptor valid", LINE_INFO());
                Assert::ExpectException<std::system_error>([fd](void) {
                    auto actual = detail::read_all_bytes(fd);
                }, L"Reading from write-only file handle causes exception", LINE_INFO());
                ::close(fd);
            }

            {
                auto fd = ::open("io_test", O_RDONLY);
                auto actual = detail::read_all_bytes(fd);
                Assert::AreEqual(expected.size(), actual.size(), L"Expected number of bytes read", LINE_INFO());
                Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin(), actual.end()), L"Content matches", LINE_INFO());
                ::close(fd);
            }

            {
                auto handle = detail::open(L"io_test", GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING);
                auto actual = detail::read_all_bytes(handle);
                Assert::AreEqual(expected.size(), actual.size(), L"Expected number of bytes read", LINE_INFO());
                Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin(), actual.end()), L"Content matches", LINE_INFO());
                ::CloseHandle(handle);
            }
        }

        TEST_METHOD(test_read_bytes) {
            std::array<char, 16> expected;
            std::generate(expected.begin(), expected.end(), [](void) {
                static char i = 0;
                return i++;
            });

            std::ofstream test_stream("io_test", std::ios::binary | std::ios::trunc);
            test_stream.write(expected.data(), expected.size());
            test_stream.close();

            {
                auto fd = detail::open("io_test", O_RDONLY);
                char actual = 0xCD;
                detail::read_bytes(fd, &actual, sizeof(actual));
                Assert::AreEqual(char(0), actual, L"First byte read", LINE_INFO());
                ::close(fd);
            }

            {
                auto fd = detail::open("io_test", O_RDONLY);
                detail::seek(fd, 0, detail::posix_seek_origin::end);
                Assert::ExpectException<std::system_error>([fd](void) {
                    char actual = 0xCD;
                    detail::read_bytes(fd, &actual, sizeof(actual));
                }, L"Read more than what is available", LINE_INFO());
                ::close(fd);
            }

            {
                auto handle = detail::open(L"io_test", GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING);
                char actual = 0xCD;
                detail::read_bytes(handle, &actual, sizeof(actual));
                Assert::AreEqual(char(0), actual, L"First byte read", LINE_INFO());
                ::CloseHandle(handle);
            }

            {
                auto handle = detail::open(L"io_test", GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING);
                detail::seek(handle, 0, detail::win32_seek_origin::end);
                Assert::ExpectException<std::system_error>([handle](void) {
                    char actual = 0xCD;
                    detail::read_bytes(handle, &actual, sizeof(actual));
                }, L"Read more than what is available", LINE_INFO());
                ::CloseHandle(handle);
            }
        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
