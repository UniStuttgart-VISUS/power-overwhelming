// <copyright file="on_exit_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace PWROWG_NAMESPACE;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(on_exit_test) {

    public:

        TEST_METHOD(test_normal_exit) {
            {
                auto i = 0;
                Assert::AreEqual(0, i, L"Initialisation", LINE_INFO());

                {
                    auto g = on_exit([&i](void) { i = 10; });
                    Assert::AreEqual(0, i, L"Unchanged", LINE_INFO());
                }

                Assert::AreEqual(10, i, L"Exit handler called", LINE_INFO());
            }
        }

        TEST_METHOD(test_cancellation) {
            {
                auto i = 0;
                Assert::AreEqual(0, i, L"Initialisation", LINE_INFO());

                {
                    auto g = on_exit([&i](void) { i = 10; });
                    Assert::AreEqual(0, i, L"Unchanged", LINE_INFO());
                    g.cancel();
                }

                Assert::AreEqual(0, i, L"Exit handler not called", LINE_INFO());
            }
        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
