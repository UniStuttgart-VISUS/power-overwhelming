// <copyright file="event_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(event_test) {

    public:

        TEST_METHOD(test_auto_reset) {
            auto event = create_event(false, false);
            auto reference = 0;

            Assert::IsNotNull(event, L"New event is valid", LINE_INFO());
            Assert::IsFalse(wait_event(event, 1), L"Event is not signalled", LINE_INFO());

            std::thread t([&event, &reference] {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                reference = 42;
                set_event(event);
            });
            t.detach();

            wait_event(event);
            Assert::AreEqual(42, reference, L"Thread signalled after variable change", LINE_INFO());
            Assert::IsFalse(wait_event(event, 1), L"Second wait times out", LINE_INFO());

        }

        TEST_METHOD(test_manual_reset) {
            auto event = create_event(true, false);
            auto reference = 0;

            Assert::IsNotNull(event, L"New event is valid", LINE_INFO());
            Assert::IsFalse(wait_event(event, 1), L"Event is not signalled", LINE_INFO());

            std::thread t([&event, &reference] {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                reference = 42;
                set_event(event);
            });
            t.detach();

            wait_event(event);
            Assert::AreEqual(42, reference, L"Thread signalled after variable change", LINE_INFO());
            Assert::IsTrue(wait_event(event, 1), L"Event stays signalled", LINE_INFO());

            reset_event(event);
            Assert::IsFalse(wait_event(event, 1), L"Event was reset", LINE_INFO());

        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
