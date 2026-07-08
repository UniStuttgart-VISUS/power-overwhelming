// <copyright file="daqmx_timing_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include <visus/pwrowg/daqmx_implicit_timing.h>
#include <visus/pwrowg/daqmx_sample_clock_timing.h>

#include <daqmx_serialisation.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(daqmx_timing_test) {

public:

    TEST_METHOD(implicit) {
        {
            daqmx_implicit_timing timing;
            Assert::AreEqual(int(daqmx_sample_mode::finite), int(timing.mode()), L"mode", LINE_INFO());
            Assert::AreEqual(1024ull, timing.samples(), L"samples", LINE_INFO());
        }
        {
            daqmx_implicit_timing timing(daqmx_sample_mode::continuous, 42);
            Assert::AreEqual(int(daqmx_sample_mode::continuous), int(timing.mode()), L"mode", LINE_INFO());
            Assert::AreEqual(42ull, timing.samples(), L"samples", LINE_INFO());
        }
    }

    TEST_METHOD(implicit_serialisation) {
        const daqmx_implicit_timing t(daqmx_sample_mode::continuous, 42);
        const auto json = detail::json_serialise(t);
        const auto u = detail::json_deserialise<daqmx_implicit_timing>(json);
        Assert::AreEqual(int(t.mode()), int(u.mode()), L"mode", LINE_INFO());
        Assert::AreEqual(t.samples(), u.samples(), L"samples", LINE_INFO());
    }

    TEST_METHOD(sample_clock) {
        {
            daqmx_sample_clock_timing timing(42.0);
            Assert::AreEqual(int(daqmx_edge::rising), int(timing.edge()), L"edge", LINE_INFO());
            Assert::AreEqual(int(daqmx_sample_mode::finite), int(timing.mode()), L"mode", LINE_INFO());
            Assert::AreEqual(42.0, timing.rate(), L"rate", LINE_INFO());
            Assert::AreEqual(1024ull, timing.samples(), L"samples", LINE_INFO());
            Assert::IsNull(timing.source(), L"source", LINE_INFO());
        }
        {
            daqmx_sample_clock_timing timing("ai1", 42.0);
            Assert::AreEqual(int(daqmx_edge::rising), int(timing.edge()), L"edge", LINE_INFO());
            Assert::AreEqual(int(daqmx_sample_mode::finite), int(timing.mode()), L"mode", LINE_INFO());
            Assert::AreEqual(42.0, timing.rate(), L"rate", LINE_INFO());
            Assert::AreEqual(1024ull, timing.samples(), L"samples", LINE_INFO());
            Assert::AreEqual("ai1", timing.source(), L"source", LINE_INFO());
        }
        {
            daqmx_sample_clock_timing timing(L"ai1", 42.0);
            Assert::AreEqual(int(daqmx_edge::rising), int(timing.edge()), L"edge", LINE_INFO());
            Assert::AreEqual(int(daqmx_sample_mode::finite), int(timing.mode()), L"mode", LINE_INFO());
            Assert::AreEqual(42.0, timing.rate(), L"rate", LINE_INFO());
            Assert::AreEqual(1024ull, timing.samples(), L"samples", LINE_INFO());
            Assert::AreEqual("ai1", timing.source(), L"source", LINE_INFO());
        }
    }

    TEST_METHOD(sample_clock_serialisation) {
        {
            const daqmx_sample_clock_timing t("ai1", 7.0, daqmx_edge::rising, daqmx_sample_mode::continuous, 42);
            const auto json = detail::json_serialise(t);
            const auto u = detail::json_deserialise<daqmx_sample_clock_timing>(json);
            Assert::AreEqual(int(t.edge()), int(u.edge()), L"edge", LINE_INFO());
            Assert::AreEqual(int(t.mode()), int(u.mode()), L"mode", LINE_INFO());
            Assert::AreEqual(t.rate(), u.rate(), L"rate", LINE_INFO());
            Assert::AreEqual(t.samples(), u.samples(), L"samples", LINE_INFO());
            Assert::AreEqual(t.source(), u.source(), L"source", LINE_INFO());
        }
        {
            daqmx_sample_clock_timing t(42.0);
            const auto json = detail::json_serialise(t);
            const auto u = detail::json_deserialise<daqmx_sample_clock_timing>(json);
            Assert::AreEqual(int(t.edge()), int(u.edge()), L"edge", LINE_INFO());
            Assert::AreEqual(int(t.mode()), int(u.mode()), L"mode", LINE_INFO());
            Assert::AreEqual(t.rate(), u.rate(), L"rate", LINE_INFO());
            Assert::AreEqual(t.samples(), u.samples(), L"samples", LINE_INFO());
            Assert::AreEqual("", u.source(), L"source", LINE_INFO());
        }
    }

};

PWROWG_TEST_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
