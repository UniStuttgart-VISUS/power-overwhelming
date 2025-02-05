// <copyright file="sensor_utilities_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(sensor_utilities_test) {

public:

    TEST_METHOD(test_move_front_if) {
        {
            std::array<int, 1> numbers { 1 };
            auto it = detail::move_front_if(numbers.begin(), numbers.end(), [](int x) { return (x % 2 == 0); });
            Assert::IsTrue(it == numbers.begin(), L"Have odd numbers", LINE_INFO());
            Assert::AreEqual(1, numbers[0], L"@0", LINE_INFO());
        }

        {
            std::array<int, 1> numbers { 2 };
            auto it = detail::move_front_if(numbers.begin(), numbers.end(), [](int x) { return (x % 2 == 0); });
            Assert::IsTrue(it == numbers.end(), L"Have no odd numbers", LINE_INFO());
            Assert::AreEqual(2, numbers[0], L"@0", LINE_INFO());
        }

        {
            std::array<int, 2> numbers { 1, 3 };
            auto it = detail::move_front_if(numbers.begin(), numbers.end(), [](int x) { return (x % 2 == 0); });
            Assert::IsTrue(it == numbers.begin(), L"Have odd numbers", LINE_INFO());
            Assert::AreEqual(1, numbers[0], L"@0", LINE_INFO());
            Assert::AreEqual(3, numbers[1], L"@1", LINE_INFO());
        }

        {
            std::array<int, 2> numbers { 1, 2 };
            auto it = detail::move_front_if(numbers.begin(), numbers.end(), [](int x) { return (x % 2 == 0); });
            Assert::IsFalse(it == numbers.begin(), L"Have odd numbers", LINE_INFO());
            Assert::AreEqual(2, numbers[0], L"@0", LINE_INFO());
            Assert::AreEqual(1, numbers[1], L"@1", LINE_INFO());
        }

        {
            std::array<int, 2> numbers { 2, 1 };
            auto it = detail::move_front_if(numbers.begin(), numbers.end(), [](int x) { return (x % 2 == 0); });
            Assert::IsFalse(it == numbers.begin(), L"Have odd numbers", LINE_INFO());
            Assert::AreEqual(2, numbers[0], L"@0", LINE_INFO());
            Assert::AreEqual(1, numbers[1], L"@1", LINE_INFO());
        }

        {
            std::array<int, 5> numbers { 1, 2, 3, 4, 5 };
            auto it = detail::move_front_if(numbers.begin(), numbers.end(), [](int x) { return (x % 2 == 0); });
            Assert::IsFalse(it == numbers.end(), L"Have odd numbers", LINE_INFO());
            Assert::AreEqual(2, numbers[0], L"@0", LINE_INFO());
            Assert::AreEqual(4, numbers[1], L"@1", LINE_INFO());
            Assert::AreNotEqual(0, numbers[2] % 2, L"@2 odd", LINE_INFO());
            Assert::AreNotEqual(0, numbers[3] % 2, L"@3 odd", LINE_INFO());
            Assert::AreNotEqual(0, numbers[4] % 2, L"@4 odd", LINE_INFO());
        }

        {
            std::array<int, 5> numbers { 2, 2, 8, 4, 5 };
            auto it = detail::move_front_if(numbers.begin(), numbers.end(), [](int x) { return (x % 2 == 0); });
            Assert::IsFalse(it == numbers.end(), L"Have odd numbers", LINE_INFO());
            Assert::AreEqual(2, numbers[0], L"@0", LINE_INFO());
            Assert::AreEqual(2, numbers[1], L"@1", LINE_INFO());
            Assert::AreEqual(8, numbers[2], L"@2", LINE_INFO());
            Assert::AreEqual(4, numbers[3], L"@3", LINE_INFO());
            Assert::AreNotEqual(0, numbers[4] % 2, L"@4 odd", LINE_INFO());
        }

        {
            std::array<int, 5> numbers { 2, 4, 6, 8, 10 };
            auto it = detail::move_front_if(numbers.begin(), numbers.end(), [](int x) { return (x % 2 == 0); });
            Assert::IsTrue(it == numbers.end(), L"Have only even numbers", LINE_INFO());
            Assert::AreEqual(2, numbers[0], L"@0", LINE_INFO());
            Assert::AreEqual(4, numbers[1], L"@1", LINE_INFO());
            Assert::AreEqual(6, numbers[2], L"@2", LINE_INFO());
            Assert::AreEqual(8, numbers[3], L"@3", LINE_INFO());
            Assert::AreEqual(10, numbers[4], L"@4", LINE_INFO());
        }

        {
            std::array<int, 5> numbers { 1, 3, 5, 7, 2 };
            auto it = detail::move_front_if(numbers.begin(), numbers.end(), [](int x) { return (x % 2 == 0); });
            Assert::IsFalse(it == numbers.end(), L"Have odd numbers", LINE_INFO());
            Assert::AreEqual(2, numbers[0], L"@0", LINE_INFO());
            Assert::AreNotEqual(0, numbers[1] % 2, L"@1 odd", LINE_INFO());
            Assert::AreNotEqual(0, numbers[2] % 2, L"@2 odd", LINE_INFO());
            Assert::AreNotEqual(0, numbers[3] % 2, L"@3 odd", LINE_INFO());
            Assert::AreNotEqual(0, numbers[4] % 2, L"@4 odd", LINE_INFO());
        }

        {
            std::array<int, 5> numbers{ 1, 3, 2, 7, 2 };
            auto it = detail::move_front_if(numbers.begin(), numbers.end(), [](int x) { return (x % 2 == 0); });
            Assert::IsFalse(it == numbers.end(), L"Have odd numbers", LINE_INFO());
            Assert::AreEqual(2, numbers[0], L"@0", LINE_INFO());
            Assert::AreEqual(2, numbers[1], L"@1", LINE_INFO());
            Assert::AreNotEqual(0, numbers[2] % 2, L"@2 odd", LINE_INFO());
            Assert::AreNotEqual(0, numbers[3] % 2, L"@3 odd", LINE_INFO());
            Assert::AreNotEqual(0, numbers[4] % 2, L"@4 odd", LINE_INFO());
        }

        {
            std::array<int, 5> numbers{ 1, 3, 7, 4, 2 };
            auto it = detail::move_front_if(numbers.begin(), numbers.end(), [](int x) { return (x % 2 == 0); });
            Assert::IsFalse(it == numbers.end(), L"Have odd numbers", LINE_INFO());
            Assert::AreEqual(4, numbers[0], L"@0", LINE_INFO());
            Assert::AreEqual(2, numbers[1], L"@1", LINE_INFO());
            Assert::AreNotEqual(0, numbers[2] % 2, L"@2 odd", LINE_INFO());
            Assert::AreNotEqual(0, numbers[3] % 2, L"@3 odd", LINE_INFO());
            Assert::AreNotEqual(0, numbers[4] % 2, L"@4 odd", LINE_INFO());
        }
    }
};

PWROWG_TEST_NAMESPACE_END
