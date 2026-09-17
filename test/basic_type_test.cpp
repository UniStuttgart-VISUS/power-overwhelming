// <copyright file="basic_type_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include <visus/pwrowg/reading.h>
#include <visus/pwrowg/reading_type.h>
#include <visus/pwrowg/reading_unit.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(basic_type_test) {

public:

    TEST_METHOD(reading_type_to_string) {
        Assert::AreEqual(L"float32", to_string<wchar_t>(reading_type::floating_point).c_str(), L"floating_point wchar_t", LINE_INFO());
        Assert::AreEqual(L"int32", to_string<wchar_t>(reading_type::signed_integer).c_str(), L"signed_integer wchar_t", LINE_INFO());
        Assert::AreEqual(L"uint32", to_string<wchar_t>(reading_type::unsigned_integer).c_str(), L"unsigned_integer wchar_t", LINE_INFO());
        Assert::AreEqual(L"void", to_string<wchar_t>(reading_type(UINT32_MAX)).c_str(), L"UINT32_MAX wchar_t", LINE_INFO());

        Assert::AreEqual("float32", to_string<char>(reading_type::floating_point).c_str(), L"floating_point char", LINE_INFO());
        Assert::AreEqual("int32", to_string<char>(reading_type::signed_integer).c_str(), L"signed_integer char", LINE_INFO());
        Assert::AreEqual("uint32", to_string<char>(reading_type::unsigned_integer).c_str(), L"unsigned_integer char", LINE_INFO());
        Assert::AreEqual("void", to_string<char>(reading_type(UINT32_MAX)).c_str(), L"UINT32_MAX char", LINE_INFO());
    }

    TEST_METHOD(reading_unit_to_string) {
        Assert::AreEqual(L"unknown", to_string<wchar_t>(reading_unit::unknown).c_str(), L"unknown wchar_t", LINE_INFO());
        Assert::AreEqual(L"A", to_string<wchar_t>(reading_unit::ampere).c_str(), L"ampere wchar_t", LINE_INFO());
        Assert::AreEqual(L"V", to_string<wchar_t>(reading_unit::volt).c_str(), L"volt wchar_t", LINE_INFO());
        Assert::AreEqual(L"W", to_string<wchar_t>(reading_unit::watt).c_str(), L"watt wchar_t", LINE_INFO());
        Assert::AreEqual(L"J", to_string<wchar_t>(reading_unit::joule).c_str(), L"joule wchar_t", LINE_INFO());
        Assert::AreEqual(L"Wh", to_string<wchar_t>(reading_unit::watt_hour).c_str(), L"watt_hour wchar_t", LINE_INFO());
        Assert::AreEqual(L"C", to_string<wchar_t>(reading_unit::coulomb).c_str(), L"coulomb wchar_t", LINE_INFO());
        Assert::AreEqual(L"Ah", to_string<wchar_t>(reading_unit::ampere_hour).c_str(), L"ampere_hour wchar_t", LINE_INFO());
        Assert::AreEqual(L"°C", to_string<wchar_t>(reading_unit::celsius).c_str(), L"celsius wchar_t", LINE_INFO());
        Assert::AreEqual(L"K", to_string<wchar_t>(reading_unit::kelvin).c_str(), L"kelvin wchar_t", LINE_INFO());

        Assert::AreEqual("unknown", to_string<char>(reading_unit::unknown).c_str(), L"unknown char", LINE_INFO());
        Assert::AreEqual("A", to_string<char>(reading_unit::ampere).c_str(), L"ampere char", LINE_INFO());
        Assert::AreEqual("V", to_string<char>(reading_unit::volt).c_str(), L"volt char", LINE_INFO());
        Assert::AreEqual("W", to_string<char>(reading_unit::watt).c_str(), L"watt char", LINE_INFO());
        Assert::AreEqual("J", to_string<char>(reading_unit::joule).c_str(), L"joule char", LINE_INFO());
        Assert::AreEqual("Wh", to_string<char>(reading_unit::watt_hour).c_str(), L"watt_hour char", LINE_INFO());
        Assert::AreEqual("C", to_string<char>(reading_unit::coulomb).c_str(), L"coulomb char", LINE_INFO());
        Assert::AreEqual("Ah", to_string<char>(reading_unit::ampere_hour).c_str(), L"ampere_hour char", LINE_INFO());
        Assert::AreEqual("°C", to_string<char>(reading_unit::celsius).c_str(), L"celsius char", LINE_INFO());
        Assert::AreEqual("K", to_string<char>(reading_unit::kelvin).c_str(), L"kelvin char", LINE_INFO());
    }

    TEST_METHOD(reading_to_float) {
        {
            reading r;
            r.floating_point = 42.0f;
            Assert::AreEqual(42.0f, to_float(r, reading_type::floating_point), L"floating_point", LINE_INFO());
        }
        {
            reading r;
            r.signed_integer = -42;
            Assert::AreEqual(-42.0f, to_float(r, reading_type::signed_integer), L"signed_integer", LINE_INFO());
        }
        {
            reading r;
            r.unsigned_integer = 42;
            Assert::AreEqual(42.0f, to_float(r, reading_type::unsigned_integer), L"unsigned_integer", LINE_INFO());
        }
    }

};

PWROWG_TEST_NAMESPACE_END
