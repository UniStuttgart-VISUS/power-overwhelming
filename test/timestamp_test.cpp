// <copyright file="timestamp_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(timestamp_test) {

    public:

        TEST_METHOD_INITIALIZE(prepare) {
            FILETIME fileTime;
            LARGE_INTEGER largeInteger;
            SYSTEMTIME systemTime;

            ::ZeroMemory(&systemTime, sizeof(systemTime));
            systemTime.wYear = 1970;
            systemTime.wMonth = 1;
            systemTime.wDay = 1;

            if (!::SystemTimeToFileTime(&systemTime, &fileTime)) {
                throw std::system_error(::GetLastError(), std::system_category());
            }

            largeInteger.HighPart = fileTime.dwHighDateTime;
            largeInteger.LowPart = fileTime.dwLowDateTime;

            this->_filetime_zero = largeInteger.QuadPart;
            this->_system_zero = std::chrono::system_clock::from_time_t(0);
        }

        TEST_METHOD(test_microseconds) {
            auto n = std::chrono::system_clock::now();
            auto t = detail::timestamp<timestamp_resolution::microseconds>::create();
            auto s = std::chrono::duration_cast<std::chrono::microseconds>(n - this->_system_zero).count();
            auto z = detail::convert(this->_filetime_zero, timestamp_resolution::microseconds);
            Assert::IsTrue(s - z - t < 1000000, L"timestamp microsecond", LINE_INFO());
        }

        TEST_METHOD(test_milliseconds) {
            auto n = std::chrono::system_clock::now();
            auto t = detail::timestamp<timestamp_resolution::milliseconds>::create();
            auto s = std::chrono::duration_cast<std::chrono::milliseconds>(n - this->_system_zero).count();
            auto z = detail::convert(this->_filetime_zero, timestamp_resolution::milliseconds);
            Assert::IsTrue(t - z - s < 1000, L"timestamp millisecond", LINE_INFO());
        }

        TEST_METHOD(test_nanoseconds) {
            auto n = std::chrono::system_clock::now();
            auto t = detail::timestamp<timestamp_resolution::nanoseconds>::create();
            auto s = std::chrono::duration_cast<std::chrono::nanoseconds>(n - this->_system_zero).count();
            auto z = detail::convert(this->_filetime_zero, timestamp_resolution::nanoseconds);
            Assert::IsTrue(t - z - s < 1000000000, L"timestamp nanosecond", LINE_INFO());
        }

        TEST_METHOD(test_seconds) {
            auto n = std::chrono::system_clock::now();
            auto t = detail::timestamp<timestamp_resolution::seconds>::create();
            auto s = std::chrono::duration_cast<std::chrono::seconds>(n - this->_system_zero).count();
            auto z = detail::convert(this->_filetime_zero, timestamp_resolution::seconds);
            Assert::IsTrue(s - z - t < 1, L"timestamp second", LINE_INFO());
        }

    private:

        std::int64_t _filetime_zero;
        std::chrono::system_clock::time_point _system_zero;
    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
