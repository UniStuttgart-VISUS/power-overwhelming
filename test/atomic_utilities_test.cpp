// <copyright file="atomic_utilities_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include <visus/pwrowg/atomic_utilities.h>

#include <sensor_trigger_state.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(atomic_utilities_test) {

    TEST_METHOD(single_threaded_set_unset) {
        std::atomic<detail::sensor_trigger_state> state = detail::sensor_trigger_state::none;
        Assert::IsFalse(detail::check_all(state, detail::sensor_trigger_state::running), L"Nothing set", LINE_INFO());
        Assert::AreEqual(int(detail::atomic_set(state, detail::sensor_trigger_state::running)), int(detail::sensor_trigger_state::none), L"Got previous", LINE_INFO());
        Assert::IsTrue(detail::check_all(state, detail::sensor_trigger_state::running), L"Running set", LINE_INFO());
        Assert::AreEqual(int(detail::atomic_unset(state, detail::sensor_trigger_state::running)), int(detail::sensor_trigger_state::running), L"Got previous", LINE_INFO());
        Assert::IsFalse(detail::check_all(state, detail::sensor_trigger_state::running), L"Running unset", LINE_INFO());
    }

};

PWROWG_TEST_NAMESPACE_END
