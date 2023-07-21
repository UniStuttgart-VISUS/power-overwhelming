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

        TEST_METHOD(test_convert_reference) {
            auto a = detail::convert(std::chrono::system_clock::from_time_t(0), timestamp_resolution::hundred_nanoseconds);
            Assert::AreEqual(this->_filetime_zero, a, L"Unix epoch as FILETIME", LINE_INFO());
        }

        TEST_METHOD(test_convert_duration) {
            {
                const std::chrono::seconds duration(1);
                Assert::AreEqual(std::int64_t(1), detail::convert(duration, timestamp_resolution::seconds), L"s to s", LINE_INFO());
                Assert::AreEqual(std::int64_t(1000), detail::convert(duration, timestamp_resolution::milliseconds), L"s to ms", LINE_INFO());
                Assert::AreEqual(std::int64_t(1000000), detail::convert(duration, timestamp_resolution::microseconds), L"s to us", LINE_INFO());
                Assert::AreEqual(std::int64_t(10000000), detail::convert(duration, timestamp_resolution::hundred_nanoseconds), L"s to 100 ns", LINE_INFO());
                Assert::AreEqual(std::int64_t(1000000000), detail::convert(duration, timestamp_resolution::nanoseconds), L"s to ns", LINE_INFO());
            }

            {
                const std::chrono::microseconds duration(1);
                Assert::AreEqual(std::int64_t(1), detail::convert(duration, timestamp_resolution::microseconds), L"us to us", LINE_INFO());
                Assert::AreEqual(std::int64_t(1000), detail::convert(duration, timestamp_resolution::nanoseconds), L"us to ns", LINE_INFO());
            }
        }

        TEST_METHOD(test_microseconds) {
            typedef std::chrono::microseconds unit;
            static const auto resolution = timestamp_resolution::microseconds;
            const auto max_dt = std::chrono::duration_cast<unit>(std::chrono::milliseconds(100)).count();

            auto n = std::chrono::system_clock::now();
            auto t = detail::create_timestamp(resolution);
            auto s = std::chrono::duration_cast<unit>(n - this->_system_zero).count();
            auto z = detail::convert(this->_filetime_zero, resolution);
            Assert::IsTrue(s - z - t <= max_dt, L"timestamp microsecond", LINE_INFO());

            auto c = detail::convert(n, resolution);
            Assert::IsTrue(t - c <= max_dt, L"Convert microsecond", LINE_INFO());
        }

        TEST_METHOD(test_milliseconds) {
            typedef std::chrono::milliseconds unit;
            static const auto resolution = timestamp_resolution::milliseconds;
            const auto max_dt = std::chrono::duration_cast<unit>(std::chrono::milliseconds(100)).count();

            auto n = std::chrono::system_clock::now();
            auto t = detail::create_timestamp(timestamp_resolution::milliseconds);
            auto s = std::chrono::duration_cast<std::chrono::milliseconds>(n - this->_system_zero).count();
            auto z = detail::convert(this->_filetime_zero, timestamp_resolution::milliseconds);
            Assert::IsTrue(t - z - s <= max_dt, L"timestamp millisecond", LINE_INFO());

            auto c = detail::convert(n, resolution);
            Assert::IsTrue(t - c <= max_dt, L"Convert millisecond", LINE_INFO());
        }

        TEST_METHOD(test_hundred_nanoseconds) {
            typedef std::chrono::duration<std::chrono::system_clock::duration::rep, detail::filetime_period> unit;
            static const auto resolution = timestamp_resolution::hundred_nanoseconds;
            const auto max_dt = std::chrono::duration_cast<unit>(std::chrono::milliseconds(100)).count();

            auto n = std::chrono::system_clock::now();
            auto t = detail::create_timestamp(resolution);
            auto s = std::chrono::duration_cast<unit>(n - this->_system_zero).count();
            auto z = detail::convert(this->_filetime_zero, resolution);
            Assert::IsTrue(t - z - s <= max_dt, L"timestamp 100 nanoseconds", LINE_INFO());

            auto c = detail::convert(n, resolution);
            Assert::IsTrue(t - c <= max_dt, L"Convert 100 nanoseconds", LINE_INFO());
        }

        TEST_METHOD(test_nanoseconds) {
            typedef std::chrono::nanoseconds unit;
            static const auto resolution = timestamp_resolution::milliseconds;
            const auto max_dt = std::chrono::duration_cast<unit>(std::chrono::milliseconds(100)).count();

            auto n = std::chrono::system_clock::now();
            auto t = detail::create_timestamp(resolution);
            auto s = std::chrono::duration_cast<unit>(n - this->_system_zero).count();
            auto z = detail::convert(this->_filetime_zero, resolution);
            Assert::IsTrue(t - z - s <= max_dt, L"timestamp nanosecond", LINE_INFO());

            auto c = detail::convert(n, resolution);
            Assert::IsTrue(t - c <= max_dt, L"Convert nanosecond", LINE_INFO());
        }

        TEST_METHOD(test_seconds) {
            typedef std::chrono::seconds unit;
            static const auto resolution = timestamp_resolution::seconds;
            const auto max_dt = std::chrono::duration_cast<unit>(std::chrono::milliseconds(100)).count();

            auto n = std::chrono::system_clock::now();
            auto t = detail::create_timestamp(resolution);
            auto s = std::chrono::duration_cast<unit>(n - this->_system_zero).count();
            auto z = detail::convert(this->_filetime_zero, resolution);
            Assert::IsTrue(s - z - t <= max_dt, L"timestamp second", LINE_INFO());

            auto c = detail::convert(n, resolution);
            Assert::IsTrue(t - c <= max_dt, L"Convert nanosecond", LINE_INFO());
        }

    private:

        std::int64_t _filetime_zero;
        std::chrono::system_clock::time_point _system_zero;
    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
