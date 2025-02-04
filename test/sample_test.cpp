// <copyright file="sample_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN


TEST_CLASS(sample_test) {

public:

    TEST_METHOD(test_ctor) {
        auto ts = timestamp::now();

        {
            sample s;
            Assert::IsTrue(ts.value() <= s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(0.0, s.reading.floating_point, L"value", LINE_INFO());
        }

        {
            sample s(42.0);
            Assert::IsTrue(ts.value() <= s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(42.0, s.reading.floating_point, L"value", LINE_INFO());
        }

        {
            sample s(42.0f);
            Assert::IsTrue(ts.value() <= s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(42.0, s.reading.floating_point, L"value", LINE_INFO());
        }

        {
            sample s(std::int64_t(-42));
            Assert::IsTrue(ts.value() <= s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(std::int64_t(-42), s.reading.signed_integer, L"value", LINE_INFO());
        }

        {
            sample s(std::int32_t(-42));
            Assert::IsTrue(ts.value() <= s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(std::int64_t(-42), s.reading.signed_integer, L"value", LINE_INFO());
        }

        {
            sample s(std::uint64_t(42));
            Assert::IsTrue(ts.value() <= s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(std::uint64_t(42), s.reading.unsigned_integer, L"value", LINE_INFO());
        }

        {
            sample s(std::uint32_t(42));
            Assert::IsTrue(ts.value() <= s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(std::uint64_t(42), s.reading.unsigned_integer, L"value", LINE_INFO());
        }

        {
            sample s(ts);
            Assert::AreEqual(ts.value(), s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(0.0, s.reading.floating_point, L"value", LINE_INFO());
        }

        {
            sample s(ts, 42.0);
            Assert::AreEqual(ts.value(), s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(42.0, s.reading.floating_point, L"value", LINE_INFO());
        }

        {
            sample s(ts, 42.0f);
            Assert::AreEqual(ts.value(), s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(42.0, s.reading.floating_point, L"value", LINE_INFO());
        }

        {
            sample s(ts, std::int64_t(-42));
            Assert::AreEqual(ts.value(), s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(std::int64_t(-42), s.reading.signed_integer, L"value", LINE_INFO());
        }

        {
            sample s(ts, std::int32_t(-42));
            Assert::AreEqual(ts.value(), s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(std::int64_t(-42), s.reading.signed_integer, L"value", LINE_INFO());
        }

        {
            sample s(ts, std::uint64_t(42));
            Assert::AreEqual(ts.value(), s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(std::uint64_t(42), s.reading.unsigned_integer, L"value", LINE_INFO());
        }

        {
            sample s(ts, std::uint32_t(42));
            Assert::AreEqual(ts.value(), s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(std::uint64_t(42), s.reading.unsigned_integer, L"value", LINE_INFO());
        }

    }

};

PWROWG_TEST_NAMESPACE_END
