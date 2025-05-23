// <copyright file="sensor_utilities_test.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2025 Visualisierungsinstitut der Universit�t Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph M�ller</author>

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

    TEST_METHOD(test_sensor_filters) {
        {
            auto desc = detail::sensor_description_builder::create().with_type(sensor_type::current).build();
            Assert::IsTrue(is_current_sensor(desc), L"is_current_sensor", LINE_INFO());
        }

        {
            auto desc = detail::sensor_description_builder::create().build();
            Assert::IsFalse(is_current_sensor(desc), L"!is_current_sensor", LINE_INFO());
        }

        {
            auto desc = detail::sensor_description_builder::create().with_type(sensor_type::energy).build();
            Assert::IsTrue(is_energy_sensor(desc), L"is_energy_sensor", LINE_INFO());
        }

        {
            auto desc = detail::sensor_description_builder::create().build();
            Assert::IsFalse(is_energy_sensor(desc), L"!is_energy_sensor", LINE_INFO());
        }

        {
            auto desc = detail::sensor_description_builder::create().with_type(sensor_type::power).build();
            Assert::IsTrue(is_power_sensor(desc), L"is_power_sensor", LINE_INFO());
        }

        {
            auto desc = detail::sensor_description_builder::create().build();
            Assert::IsFalse(is_power_sensor(desc), L"!is_power_sensor", LINE_INFO());
        }

        {
            auto desc = detail::sensor_description_builder::create().with_type(sensor_type::voltage).build();
            Assert::IsTrue(is_voltage_sensor(desc), L"is_power_sensor", LINE_INFO());
        }

        {
            auto desc = detail::sensor_description_builder::create().build();
            Assert::IsFalse(is_voltage_sensor(desc), L"!is_power_sensor", LINE_INFO());
        }
    }

    TEST_METHOD(test_all_of_filter) {
        auto desc = detail::sensor_description_builder::create().with_type(sensor_type::current | sensor_type::gpu).build();
        Assert::IsTrue(is_all_of<is_current_sensor>(desc), L"is_current_sensor", LINE_INFO());
        Assert::IsTrue(is_all_of<is_current_sensor, is_gpu_sensor>(desc), L"is_current_sensor && is_gpu_sensor", LINE_INFO());
        Assert::IsFalse(is_all_of<is_current_sensor, is_cpu_sensor>(desc), L"is_current_sensor && !is_cpu_sensor", LINE_INFO());
        Assert::IsFalse(is_all_of< is_power_sensor, is_cpu_sensor>(desc), L"!is_current_sensor && !is_cpu_sensor", LINE_INFO());
    }

    TEST_METHOD(test_any_of_filter) {
        auto desc = detail::sensor_description_builder::create().with_type(sensor_type::current | sensor_type::gpu).build();
        Assert::IsTrue(is_any_of<is_current_sensor>(desc), L"is_current_sensor", LINE_INFO());
        Assert::IsTrue(is_any_of<is_current_sensor, is_gpu_sensor>(desc), L"is_current_sensor && is_gpu_sensor", LINE_INFO());
        Assert::IsTrue(is_any_of<is_current_sensor, is_cpu_sensor>(desc), L"is_current_sensor && !is_cpu_sensor", LINE_INFO());
        Assert::IsFalse(is_any_of<is_power_sensor, is_cpu_sensor>(desc), L"!is_power_sensor && !is_cpu_sensor", LINE_INFO());
    }

    TEST_METHOD(test_none_of_filter) {
        auto desc = detail::sensor_description_builder::create().with_type(sensor_type::current | sensor_type::gpu).build();
        Assert::IsFalse(is_none_of<is_current_sensor>(desc), L"is_current_sensor", LINE_INFO());
        Assert::IsFalse(is_none_of<is_current_sensor, is_gpu_sensor>(desc), L"is_current_sensor && is_gpu_sensor", LINE_INFO());
        Assert::IsFalse(is_none_of<is_current_sensor, is_cpu_sensor>(desc), L"is_current_sensor && !is_cpu_sensor", LINE_INFO());
        Assert::IsTrue(is_none_of<is_power_sensor, is_cpu_sensor>(desc), L"!is_power_sensor && !is_cpu_sensor", LINE_INFO());
    }

    TEST_METHOD(test_sensor_type_filters) {
        auto desc = detail::sensor_description_builder::create().with_type(sensor_type::current | sensor_type::gpu).build();

        Assert::IsTrue(is_any_sensor_type_of<sensor_type::current, sensor_type::gpu, sensor_type::cpu>(desc), L"sensor_type::current, sensor_type::gpu, sensor_type::cpu", LINE_INFO());
        Assert::IsTrue(is_any_sensor_type_of<sensor_type::current, sensor_type::gpu>(desc), L"sensor_type::current, sensor_type::gpu", LINE_INFO());
        Assert::IsTrue(is_any_sensor_type_of<sensor_type::current>(desc), L"sensor_type::current", LINE_INFO());
        Assert::IsTrue(is_any_sensor_type_of<sensor_type::gpu>(desc), L"sensor_type::gpu", LINE_INFO());
        Assert::IsFalse(is_any_sensor_type_of<sensor_type::cpu>(desc), L"sensor_type::cpu", LINE_INFO());

        Assert::IsFalse(is_all_sensor_types_of<sensor_type::current, sensor_type::gpu, sensor_type::cpu>(desc), L"sensor_type::current, sensor_type::gpu , sensor_type::cpu", LINE_INFO());
        Assert::IsTrue(is_all_sensor_types_of<sensor_type::current, sensor_type::gpu>(desc), L"sensor_type::current, sensor_type::gpu", LINE_INFO());
        Assert::IsTrue(is_all_sensor_types_of<sensor_type::current>(desc), L"sensor_type::current", LINE_INFO());
        Assert::IsTrue(is_all_sensor_types_of<sensor_type::gpu>(desc), L"sensor_type::gpu", LINE_INFO());
        Assert::IsFalse(is_all_sensor_types_of<sensor_type::cpu>(desc), L"sensor_type::cpu", LINE_INFO());
    }
};

PWROWG_TEST_NAMESPACE_END
