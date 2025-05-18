// <copyright file="unique_container_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN


TEST_CLASS(unique_container_test) {

public:

    TEST_METHOD(test_ctor) {
        detail::unique_container<int> c;
        Assert::IsTrue(c.empty(), L"Initially empty", LINE_INFO());
        Assert::AreEqual(std::size_t(0), c.size(), L"Size", LINE_INFO());
        Assert::IsTrue(c.begin() == c.end(), L"Range empty", LINE_INFO());
    }

    TEST_METHOD(test_emplace) {
        detail::unique_container<int> c;
        c.emplace(42);
        Assert::IsFalse(c.empty(), L"Not empty", LINE_INFO());
        Assert::AreEqual(std::size_t(1), c.size(), L"Size", LINE_INFO());
        Assert::IsTrue(c.begin() != c.end(), L"Range empty", LINE_INFO());
        Assert::AreEqual(42, *c.begin(), L"Value", LINE_INFO());
    }

};

PWROWG_TEST_NAMESPACE_END
