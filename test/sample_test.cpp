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
            Assert::AreEqual(0.0f, s.reading.floating_point, L"value", LINE_INFO());
            Assert::AreEqual(sample::source_type(0), s.source, L"source", LINE_INFO());
        }

        {
            sample s(1, 42.0f);
            Assert::IsTrue(ts.value() <= s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(42.0f, s.reading.floating_point, L"value", LINE_INFO());
            Assert::AreEqual(sample::source_type(1), s.source, L"source", LINE_INFO());
        }

        {
            sample s(1, std::int32_t(-42));
            Assert::IsTrue(ts.value() <= s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(std::int32_t(-42), s.reading.signed_integer, L"value", LINE_INFO());
            Assert::AreEqual(sample::source_type(1), s.source, L"source", LINE_INFO());
        }

        {
            sample s(1, std::uint32_t(42));
            Assert::IsTrue(ts.value() <= s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(std::uint32_t(42), s.reading.unsigned_integer, L"value", LINE_INFO());
            Assert::AreEqual(sample::source_type(1), s.source, L"source", LINE_INFO());
        }

        {
            sample s(1, ts);
            Assert::AreEqual(ts.value(), s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(0.0f, s.reading.floating_point, L"value", LINE_INFO());
            Assert::AreEqual(sample::source_type(1), s.source, L"source", LINE_INFO());
        }

        {
            sample s(1, ts, 42.0f);
            Assert::AreEqual(ts.value(), s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(sample::source_type(1), s.source, L"source", LINE_INFO());
            Assert::AreEqual(42.0f, s.reading.floating_point, L"value", LINE_INFO());
        }

        {
            sample s(1, ts, std::int32_t(-42));
            Assert::AreEqual(ts.value(), s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(std::int32_t(-42), s.reading.signed_integer, L"value", LINE_INFO());
            Assert::AreEqual(sample::source_type(1), s.source, L"source", LINE_INFO());
        }

        {
            sample s(1, ts, std::uint32_t(42));
            Assert::AreEqual(ts.value(), s.timestamp.value(), L"timestamp", LINE_INFO());
            Assert::AreEqual(std::uint32_t(42), s.reading.unsigned_integer, L"value", LINE_INFO());
            Assert::AreEqual(sample::source_type(1), s.source, L"source", LINE_INFO());
        }

    }

};

PWROWG_TEST_NAMESPACE_END
