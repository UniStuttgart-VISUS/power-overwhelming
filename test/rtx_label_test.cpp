// <copyright file="rtx_label_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(rtx_label_test) {

public:

    TEST_METHOD(test_default_ctor) {
        rtx_label label;
        Assert::AreEqual("", label.text(), L"Empty label", LINE_INFO());
        Assert::IsFalse(label.visible(), L"Initially invisible", LINE_INFO());
    }
};

PWROWG_TEST_NAMESPACE_END
