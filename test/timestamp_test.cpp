// <copyright file="timestamp_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
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
            const auto a = timestamp(std::chrono::system_clock::from_time_t(0));
            Assert::AreEqual(this->_filetime_zero, a.value(), L"Unix epoch as FILETIME", LINE_INFO());
        }

        TEST_METHOD(test_from_system_clock) {
            typedef std::chrono::duration<timestamp::value_type, std::ratio<1, 10000000>> dur;
            const auto max_dt = std::chrono::duration_cast<dur>(std::chrono::milliseconds(100)).count();

            const auto f = timestamp::now();
            const auto s = timestamp::from_system_clock();
            Assert::IsTrue(s.value() - f.value() < max_dt, L"FILETIME from STL", LINE_INFO());
        }

        TEST_METHOD(test_now) {
            typedef std::chrono::duration<timestamp::value_type, std::ratio<1, 10000000>> dur;
            const auto max_dt = std::chrono::duration_cast<dur>(std::chrono::milliseconds(100)).count();

            const auto n = std::chrono::system_clock::now();
            const auto t = timestamp::now();
            const auto s = std::chrono::duration_cast<dur>(n - this->_system_zero).count();
            Assert::IsTrue(s - this->_filetime_zero - t <= max_dt, L"timestamp near system clock", LINE_INFO());
        }

        TEST_METHOD(test_from_time_t) {
            const auto n = ::time(nullptr);
            const auto t = timestamp::from_time_t(n);

            const auto r = time_t_to_filetime(n);
            LARGE_INTEGER rr;
            rr.HighPart = r.dwHighDateTime;
            rr.LowPart = r.dwLowDateTime;
            Assert::AreEqual(rr.QuadPart, t.value(), L"timestamp from time_t", LINE_INFO());
        }

        TEST_METHOD(file_time_roundtrip) {
            FILETIME e;
            e.dwLowDateTime = 42;
            e.dwHighDateTime = 17;

            const auto t = timestamp::from_file_time(e);
            const auto a = static_cast<FILETIME>(t);

            Assert::AreEqual(e.dwLowDateTime, a.dwLowDateTime, L"dwLowDateTime", LINE_INFO());
            Assert::AreEqual(e.dwHighDateTime, a.dwHighDateTime, L"dwHighDateTime", LINE_INFO());
        }

        TEST_METHOD(system_clock_roundtrip) {
            const auto e = std::chrono::system_clock::now();
            const auto t = timestamp(e);
            const auto a = static_cast<std::chrono::system_clock::time_point>(t);
            Assert::AreEqual(e.time_since_epoch().count(), a.time_since_epoch().count(), L"system clock round trip", LINE_INFO());
        }

        TEST_METHOD(time_point_roundtrip) {
            const auto e = std::chrono::system_clock::now();
            const auto t = timestamp::from_time_point(e);
            const auto a = static_cast<std::chrono::system_clock::time_point>(t);
            Assert::AreEqual(e.time_since_epoch().count(), a.time_since_epoch().count(), L"from_time_point round trip", LINE_INFO());
        }

        TEST_METHOD(test_create) {
            {
                const auto timestamp = power_overwhelming::timestamp::create(2000, 1, 2, 3, 4, 5, 6);
                const auto expected = make_filetime(2000, 1, 2, 3, 4, 5, 6);
                Assert::AreEqual(expected, timestamp.value(), L"Create 100ns", LINE_INFO());
            }

            {
                const auto timestamp = power_overwhelming::timestamp::create(2000, 1, 2, 3, 4, 5, 6, 7, 800);
                const auto filetime = make_filetime(2000, 1, 2, 3, 4, 5, 6);
                const auto expected = filetime + 70 + 8;
                Assert::AreEqual(expected, timestamp.value(), L"Create 100ns", LINE_INFO());
            }

            {
                const auto timestamp = power_overwhelming::timestamp::create(2000, 1, 2, 3, 4, 5, 6, 7);
                const auto filetime = make_filetime(2000, 1, 2, 3, 4, 5, 6);
                const auto expected = filetime + 70;
                Assert::AreEqual(expected, timestamp.value(), L"Create µs", LINE_INFO());
            }
        }

        TEST_METHOD(test_arithmetics) {
            {
                const timestamp::value_type expected = 1;
                auto actual = timestamp();
                actual += std::chrono::nanoseconds(100);
                Assert::AreEqual(expected, actual.value(), L"+=", LINE_INFO());
            }

            {
                const timestamp::value_type expected = 1;
                const auto t = timestamp();
                const auto actual = t + std::chrono::nanoseconds(100);
                Assert::AreEqual(timestamp::value_type(0), t.value(), L"lhs unchanged", LINE_INFO());
                Assert::AreEqual(expected, actual.value(), L"+", LINE_INFO());
            }

            {
                const timestamp::value_type expected = 0;
                auto actual = timestamp(1);
                actual -= std::chrono::nanoseconds(100);
                Assert::AreEqual(expected, actual.value(), L"-=", LINE_INFO());
            }

            {
                const timestamp::value_type expected = 0;
                const auto t = timestamp(1);
                const auto actual = t - std::chrono::nanoseconds(100);
                Assert::AreEqual(timestamp::value_type(1), t.value(), L"lhs unchanged", LINE_INFO());
                Assert::AreEqual(expected, actual.value(), L"-", LINE_INFO());
            }
        }

    private:

        static inline timestamp::value_type make_filetime(const std::uint16_t year,
                const std::uint16_t month, const std::uint16_t day,
                const std::uint16_t hours, const std::uint16_t minutes,
                const std::uint16_t seconds, const std::uint16_t millis) {
            SYSTEMTIME utctime;
            ::ZeroMemory(&utctime, sizeof(utctime));
            utctime.wYear = year;
            utctime.wMonth = month;
            utctime.wDay = day;
            utctime.wHour = hours;
            utctime.wMinute = minutes;
            utctime.wSecond = seconds;
            utctime.wMilliseconds = millis;

            FILETIME filetime;
            Assert::IsTrue(::SystemTimeToFileTime(&utctime, &filetime));

            LARGE_INTEGER retval;
            retval.HighPart = filetime.dwHighDateTime;
            retval.LowPart = filetime.dwLowDateTime;

            return retval.QuadPart;
        }

        static inline FILETIME time_t_to_filetime(const std::time_t t) {
            // From https://github.com/MicrosoftDocs/win32/blob/docs/desktop-src/SysInfo/converting-a-time-t-value-to-a-file-time.md
            ULARGE_INTEGER time_value;
            time_value.QuadPart = (t * 10000000LL) + 116444736000000000LL;
            FILETIME retval;
            retval.dwLowDateTime = time_value.LowPart;
            retval.dwHighDateTime = time_value.HighPart;
            return retval;
        }

        std::int64_t _filetime_zero;
        std::chrono::system_clock::time_point _system_zero;
    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
