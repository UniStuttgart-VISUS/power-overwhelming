// <copyright file="type_list_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(type_list_test) {

public:

    TEST_METHOD(test_at) {
        {
            typedef detail::type_list<int> list;
            Assert::IsTrue(std::is_same_v<int, detail::type_list_at<0, list>::type>, L"List of one", LINE_INFO());
        }

        {
            typedef detail::type_list<int, float> list;
            Assert::IsTrue(std::is_same_v<int, detail::type_list_at<0, list>::type>, L"List of two @0", LINE_INFO());
            Assert::IsTrue(std::is_same_v<float, detail::type_list_at<1, list>::type>, L"List of two @1", LINE_INFO());
        }
    }

    TEST_METHOD(test_cat) {
        typedef detail::type_list<> list0;
        typedef typename detail::type_list_cat<list0, int>::type list1;
        typedef typename detail::type_list_cat<list1, float>::type list2;
        Assert::IsTrue(std::is_same_v<int, detail::type_list_at<0, list2>::type>, L"cat @0", LINE_INFO());
        Assert::IsTrue(std::is_same_v<float, detail::type_list_at<1, list2>::type>, L"cat @1", LINE_INFO());

        typedef detail::type_list_cat_t<list1, detail::type_list<float, double>> list3;
        Assert::IsTrue(std::is_same_v<int, detail::type_list_at<0, list3>::type>, L"cat @0", LINE_INFO());
        Assert::IsTrue(std::is_same_v<float, detail::type_list_at<1, list3>::type>, L"cat @1", LINE_INFO());
    }

    TEST_METHOD(test_filter) {
        typedef detail::type_list<std::int32_t, float, std::uint32_t, double> list;

        {
            typedef detail::type_list_filter_t<std::is_integral, list> filtered;
            Assert::IsTrue(std::is_same_v<std::int32_t, detail::type_list_at<0, filtered>::type>, L"integral @0", LINE_INFO());
            Assert::IsTrue(std::is_same_v<std::uint32_t, detail::type_list_at<1, filtered>::type>, L"integral @1", LINE_INFO());
        }

        {
            typedef detail::type_list_filter_t<std::is_floating_point, list> filtered;
            Assert::IsTrue(std::is_same_v<float, detail::type_list_at<0, filtered>::type>, L"float @0", LINE_INFO());
            Assert::IsTrue(std::is_same_v<double, detail::type_list_at<1, filtered>::type>, L"float @1", LINE_INFO());
        }
    }

    TEST_METHOD(test_sensor_filter) {
        typedef detail::type_list<detail::nvml_sensor, detail::tinkerforge_sensor> list;
        typedef detail::type_list_filter_t<detail::has_sync_sample, list> filtered;
        Assert::IsTrue(std::is_same_v<detail::nvml_sensor, detail::type_list_at<0, filtered>::type>, L"NVML selected", LINE_INFO());
    }

    TEST_METHOD(test_index_of) {
        typedef detail::type_list<std::int32_t, float, std::uint32_t, double> list;
        Assert::AreEqual(std::size_t(0), detail::type_list_index_of_v<std::int32_t, list>, L"int32", LINE_INFO());
        Assert::AreEqual(std::size_t(2), detail::type_list_index_of_v<std::uint32_t, list>, L"uint32_t", LINE_INFO());
    }

    TEST_METHOD(test_tuple_types) {
        typedef std::tuple<std::int32_t, float, std::uint32_t, double> tuple;
        typedef detail::type_list<std::int32_t, float, std::uint32_t, double> list;
        Assert::IsTrue(std::is_same_v<detail::tuple_types_t<tuple>, list>, L"correct list", LINE_INFO());
    }
};

PWROWG_TEST_NAMESPACE_END
