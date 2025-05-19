// <copyright file="multi_sz_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(multi_sz_test) {

    TEST_METHOD(char_ctor) {
        multi_sz<char> msz;
        Assert::IsTrue(msz.empty(), L"multi-sz is intially empty.", LINE_INFO());
        Assert::AreEqual(std::size_t(0), msz.count(), L"Empty multi-sz has zero entries.", LINE_INFO());
        Assert::AreEqual(size_t(0), msz.length(), L"Empty multi-sz has length zero.", LINE_INFO());
    }

    TEST_METHOD(wchar_t_ctor) {
        multi_sz<wchar_t> msz;
        Assert::IsTrue(msz.empty(), L"multi-sz is intially empty.", LINE_INFO());
        Assert::AreEqual(std::size_t(0), msz.count(), L"Empty multi-sz has zero entries.", LINE_INFO());
        Assert::AreEqual(size_t(0), msz.length(), L"Empty multi-sz has length zero.", LINE_INFO());
    }

    TEST_METHOD(char_array_ctor) {
        const char *strings[] = { "Horst", "Hugo", "Heinz", "Hans" };
        multi_sz<char> msz(strings, 4);
        Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());
        Assert::AreEqual(std::size_t(4), msz.count(), L"multi-sz has 4 entries.", LINE_INFO());
        Assert::AreEqual(size_t(23), msz.length(), L"multi-sz has length 23.", LINE_INFO());
        Assert::AreEqual("Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual("Hugo", msz.at(1), L"at(1) is \"Hugo\".", LINE_INFO());
        Assert::AreEqual("Heinz", msz.at(2), L"at(2) is \"Heinz\".", LINE_INFO());
        Assert::AreEqual("Hans", msz.at(3), L"at(3) is \"Hans\".", LINE_INFO());
        Assert::IsNull(msz.at(4), L"at(3) is nullptr.",  LINE_INFO());
        Assert::AreEqual(msz[0], "Horst", L"[0] is \"Horst\".", LINE_INFO());
        Assert::AreEqual(msz[1], "Hugo", L"[1] is \"Hugo\".", LINE_INFO());
        Assert::AreEqual(msz[2], "Heinz", L"[2] is \"Heinz\".", LINE_INFO());
        Assert::AreEqual(msz[3], "Hans", L"[3] is \"Hans\".", LINE_INFO());
        Assert::IsNull(msz[4], L"[3] is nullptr.", LINE_INFO());
    }

    TEST_METHOD(wchar_t_array_ctor) {
        const wchar_t *strings[] = { L"Horst", L"Hugo", L"Heinz", L"Hans" };
        multi_sz<wchar_t> msz(strings, 4);
        Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());
        Assert::AreEqual(std::size_t(4), msz.count(), L"multi-sz has 4 entries.", LINE_INFO());
        Assert::AreEqual(size_t(23), msz.length(), L"multi-sz has length 23.", LINE_INFO());
        Assert::AreEqual(L"Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual(L"Hugo", msz.at(1), L"at(1) is \"Hugo\".", LINE_INFO());
        Assert::AreEqual(L"Heinz", msz.at(2), L"at(2) is \"Heinz\".", LINE_INFO());
        Assert::AreEqual(L"Hans", msz.at(3), L"at(3) is \"Hans\".", LINE_INFO());
        Assert::IsNull(msz.at(4), L"at(3) is nullptr.", LINE_INFO());
        Assert::AreEqual(msz[0], L"Horst", L"[0] is \"Horst\".", LINE_INFO());
        Assert::AreEqual(msz[1], L"Hugo", L"[1] is \"Hugo\".", LINE_INFO());
        Assert::AreEqual(msz[2], L"Heinz", L"[2] is \"Heinz\".", LINE_INFO());
        Assert::AreEqual(msz[3], L"Hans", L"[3] is \"Hans\".", LINE_INFO());
        Assert::IsNull(msz[4], L"[3] is nullptr.", LINE_INFO());
    }

    TEST_METHOD(char_blob_ctor) {
        typedef char char_type;
        const char_type data[] = "Horst\0Hugo\0Heinz\0Hans\0";
        blob blob(sizeof(data));
        ::memcpy(blob, data, sizeof(data));
        multi_sz<char_type> msz(blob);
        Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());
        Assert::AreEqual(std::size_t(4), msz.count(), L"multi-sz has 4 entries.", LINE_INFO());
        Assert::AreEqual(size_t(23), msz.length(), L"multi-sz has length 23.", LINE_INFO());
        Assert::AreEqual("Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual("Hugo", msz.at(1), L"at(1) is \"Hugo\".", LINE_INFO());
        Assert::AreEqual("Heinz", msz.at(2), L"at(2) is \"Heinz\".", LINE_INFO());
        Assert::AreEqual("Hans", msz.at(3), L"at(3) is \"Hans\".", LINE_INFO());
        Assert::IsNull(msz.at(4), L"at(3) is nullptr.", LINE_INFO());
    }

    TEST_METHOD(wchar_t_blob_ctor) {
        typedef wchar_t char_type;
        const char_type data[] = L"Horst\0Hugo\0Heinz\0Hans\0";
        blob blob(sizeof(data));
        ::memcpy(blob, data, sizeof(data));
        multi_sz<char_type> msz(blob);
        Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());
        Assert::AreEqual(std::size_t(4), msz.count(), L"multi-sz has 4 entries.", LINE_INFO());
        Assert::AreEqual(size_t(23), msz.length(), L"multi-sz has length 23.", LINE_INFO());
        Assert::AreEqual(L"Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual(L"Hugo", msz.at(1), L"at(1) is \"Hugo\".", LINE_INFO());
        Assert::AreEqual(L"Heinz", msz.at(2), L"at(2) is \"Heinz\".", LINE_INFO());
        Assert::AreEqual(L"Hans", msz.at(3), L"at(3) is \"Hans\".", LINE_INFO());
        Assert::IsNull(msz.at(4), L"at(3) is nullptr.", LINE_INFO());
    }

    TEST_METHOD(char_clone) {
        const char *strings[] = { "Horst", "Hugo" };
        multi_sz<char> msz(strings, 2);
        Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());
        Assert::AreEqual(std::size_t(2), msz.count(), L"multi-sz has 2 entries.", LINE_INFO());

        multi_sz<char> clone(msz);
        Assert::AreEqual(msz.count(), clone.count(), L"Clone has 2 entries.", LINE_INFO());

        Assert::AreEqual(msz.length(), clone.length(), L"Same length.", LINE_INFO());
        Assert::AreEqual(msz.at(0), clone.at(0), L"Same @0.", LINE_INFO());
        Assert::AreEqual(msz.at(1), clone.at(1), L"Same @1.", LINE_INFO());

        Assert::IsTrue(msz == clone, L"Equality", LINE_INFO());
        Assert::IsFalse(msz != clone, L"Inequality", LINE_INFO());
    }

    TEST_METHOD(wchar_t_clone) {
        const wchar_t *strings[] = { L"Horst", L"Hugo" };
        multi_sz<wchar_t> msz(strings, 2);
        Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());
        Assert::AreEqual(std::size_t(2), msz.count(), L"multi-sz has 2 entries.", LINE_INFO());

        multi_sz<wchar_t> clone(msz);
        Assert::AreEqual(msz.count(), clone.count(), L"Clone has 2 entries.", LINE_INFO());

        Assert::AreEqual(msz.length(), clone.length(), L"Same length.", LINE_INFO());
        Assert::AreEqual(msz.at(0), clone.at(0), L"Same @0.", LINE_INFO());
        Assert::AreEqual(msz.at(1), clone.at(1), L"Same @1.", LINE_INFO());

        Assert::IsTrue(msz == clone, L"Equality", LINE_INFO());
        Assert::IsFalse(msz != clone, L"Inequality", LINE_INFO());
    }

    TEST_METHOD(char_move) {
        const char *strings[] = { "Horst", "Hugo" };
        multi_sz<char> msz(strings, 2);
        Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());
        Assert::AreEqual(std::size_t(2), msz.count(), L"multi-sz has 2 entries.", LINE_INFO());

        multi_sz<char> clone(std::move(msz));
        Assert::AreEqual(std::size_t(2), clone.count(), L"Clone has 2 entries.", LINE_INFO());
        Assert::IsTrue(msz.empty(), L"multi-sz is now empty.", LINE_INFO());

        Assert::AreEqual(clone.at(0), "Horst", L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual(clone.at(1), "Hugo", L"at(1) is \"Hugo\".", LINE_INFO());

        Assert::IsFalse(msz == clone, L"Equality", LINE_INFO());
        Assert::IsTrue(msz != clone, L"Inequality", LINE_INFO());

        msz = std::move(clone);
        Assert::AreEqual(std::size_t(2), msz.count(), L"multi-sz has 2 entries.", LINE_INFO());
        Assert::IsTrue(clone.empty(), L"clone is now empty.", LINE_INFO());

        Assert::AreEqual("Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual("Hugo", msz.at(1), L"at(1) is \"Hugo\".", LINE_INFO());

        Assert::IsFalse(msz == clone, L"Equality", LINE_INFO());
        Assert::IsTrue(msz != clone, L"Inequality", LINE_INFO());
    }

    TEST_METHOD(wchar_t_move) {
        const wchar_t *strings[] = { L"Horst", L"Hugo" };
        multi_sz<wchar_t> msz(strings, 2);
        Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());
        Assert::AreEqual(std::size_t(2), msz.count(), L"multi-sz has 2 entries.", LINE_INFO());

        multi_sz<wchar_t> clone(std::move(msz));
        Assert::AreEqual(std::size_t(2), clone.count(), L"Clone has 2 entries.", LINE_INFO());
        Assert::IsTrue(msz.empty(), L"multi-sz is now empty.", LINE_INFO());

        Assert::AreEqual(clone.at(0), L"Horst", L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual(clone.at(1), L"Hugo", L"at(1) is \"Hugo\".", LINE_INFO());

        Assert::IsFalse(msz == clone, L"Equality", LINE_INFO());
        Assert::IsTrue(msz != clone, L"Inequality", LINE_INFO());

        msz = std::move(clone);
        Assert::AreEqual(std::size_t(2), msz.count(), L"multi-sz has 2 entries.", LINE_INFO());
        Assert::IsTrue(clone.empty(), L"clone is now empty.", LINE_INFO());

        Assert::AreEqual(L"Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual(L"Hugo", msz.at(1), L"at(1) is \"Hugo\".", LINE_INFO());

        Assert::IsFalse(msz == clone, L"Equality", LINE_INFO());
        Assert::IsTrue(msz != clone, L"Inequality", LINE_INFO());
    }

    TEST_METHOD(char_clear) {
        const char *strings[] = { "Horst", "Hugo" };
        multi_sz<char> msz(strings, 2);
        Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());
        msz.clear();
        Assert::IsTrue(msz.empty(), L"multi-sz cleared.", LINE_INFO());
    }

    TEST_METHOD(wchar_t_clear) {
        const wchar_t *strings[] = { L"Horst", L"Hugo" };
        multi_sz<wchar_t> msz(strings, 2);
        Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());
        msz.clear();
        Assert::IsTrue(msz.empty(), L"multi-sz cleared.", LINE_INFO());
    }

    TEST_METHOD(char_add) {
        multi_sz<char> msz;
        Assert::IsTrue(msz.empty(), L"Intially not empty.", LINE_INFO());

        msz.add("Horst");
        Assert::IsFalse(msz.empty(), L"Not empty.", LINE_INFO());
        Assert::AreEqual(std::size_t(1), msz.count(), L"One added.", LINE_INFO());
        Assert::AreEqual("Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::IsNull( msz.at(1), L"at(1) is nullptr.",LINE_INFO());

        msz.add("Hugo");
        Assert::IsFalse(msz.empty(), L"Not empty.", LINE_INFO());
        Assert::AreEqual(std::size_t(2), msz.count(), L"One added.", LINE_INFO());
        Assert::AreEqual("Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual("Hugo", msz.at(1), L"at(1) is \"Hugo\".", LINE_INFO());
        Assert::IsNull(msz.at(2), L"at(2) is nullptr.", LINE_INFO());

        msz.add("Heinz");
        Assert::IsFalse(msz.empty(), L"Not empty.", LINE_INFO());
        Assert::AreEqual(std::size_t(3), msz.count(), L"One added.", LINE_INFO());
        Assert::AreEqual("Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual("Hugo", msz.at(1), L"at(2) is \"Hugo\".", LINE_INFO());
        Assert::AreEqual("Heinz", msz.at(2), L"at(3) is \"Heinz\".", LINE_INFO());
        Assert::IsNull(msz.at(3), L"at(3) is nullptr.", LINE_INFO());
    }

    TEST_METHOD(wchar_t_add) {
        multi_sz<wchar_t> msz;
        Assert::IsTrue(msz.empty(), L"Intially not empty.", LINE_INFO());

        msz.add(L"Horst");
        Assert::IsFalse(msz.empty(), L"Not empty.", LINE_INFO());
        Assert::AreEqual(std::size_t(1), msz.count(), L"One added.", LINE_INFO());
        Assert::AreEqual(L"Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::IsNull(msz.at(1), L"at(1) is nullptr.", LINE_INFO());

        msz.add(L"Hugo");
        Assert::IsFalse(msz.empty(), L"Not empty.", LINE_INFO());
        Assert::AreEqual(std::size_t(2), msz.count(), L"One added.", LINE_INFO());
        Assert::AreEqual(L"Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual(L"Hugo", msz.at(1), L"at(1) is \"Hugo\".", LINE_INFO());
        Assert::IsNull(msz.at(2), L"at(2) is nullptr.", LINE_INFO());

        msz.add(L"Heinz");
        Assert::IsFalse(msz.empty(), L"Not empty.", LINE_INFO());
        Assert::AreEqual(std::size_t(3), msz.count(), L"One added.", LINE_INFO());
        Assert::AreEqual(L"Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual(L"Hugo", msz.at(1), L"at(2) is \"Hugo\".", LINE_INFO());
        Assert::AreEqual(L"Heinz", msz.at(2), L"at(3) is \"Heinz\".", LINE_INFO());
        Assert::IsNull(msz.at(3), L"at(3) is nullptr.", LINE_INFO());
    }

    TEST_METHOD(char_remove_if) {
        {
            multi_sz<char> msz;
            Assert::IsTrue(msz.empty(), L"multi-sz is intially empty.", LINE_INFO());
            msz.remove_if([](const char *s) { return *s == 'H'; });
            Assert::IsTrue(msz.empty(), L"All cleared.", LINE_INFO());
        }

        {
            const char *strings[] = { "Horst", "Hugo", "Heinz", "Hans" };
            multi_sz<char> msz(strings, 4);
            Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());
            msz.remove_if([](const char *s) { return *s == 'H'; });
            Assert::IsTrue(msz.empty(), L"All cleared.", LINE_INFO());
        }

        {
            const char *strings[] = { "Horst", "Hugo", "Holger", "Hans" };
            multi_sz<char> msz(strings, 4);
            Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());
            msz.remove_if([](const char *s) { return s[0] == 'H' && s[1] == 'o'; });
            Assert::AreEqual(std::size_t(2), msz.count(), L"Two remaining.", LINE_INFO());
            Assert::AreEqual("Hugo", msz.at(0), L"at(0) is \"Hugo\".", LINE_INFO());
            Assert::AreEqual("Hans", msz.at(1), L"at(1) is \"Hans\".", LINE_INFO());
        }
    }

    TEST_METHOD(wchar_t_remove_if) {
        {
            multi_sz<wchar_t> msz;
            Assert::IsTrue(msz.empty(), L"multi-sz is intially empty.", LINE_INFO());
            msz.remove_if([](const wchar_t *s) { return *s == L'H'; });
            Assert::IsTrue(msz.empty(), L"All cleared.", LINE_INFO());
        }

        {
            const wchar_t *strings[] = { L"Horst", L"Hugo", L"Heinz", L"Hans" };
            multi_sz<wchar_t> msz(strings, 4);
            Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());
            msz.remove_if([](const wchar_t *s) { return *s == L'H'; });
            Assert::IsTrue(msz.empty(), L"All cleared.", LINE_INFO());
        }

        {
            const wchar_t *strings[] = { L"Horst", L"Hugo", L"Holger", L"Hans" };
            multi_sz<wchar_t> msz(strings, 4);
            Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());
            msz.remove_if([](const wchar_t *s) { return s[0] == L'H' && s[1] == L'o'; });
            Assert::AreEqual(std::size_t(2), msz.count(), L"Two remaining.", LINE_INFO());
            Assert::AreEqual(L"Hugo", msz.at(0), L"at(0) is \"Hugo\".", LINE_INFO());
            Assert::AreEqual(L"Hans", msz.at(1), L"at(1) is \"Hans\".", LINE_INFO());
        }
    }

    TEST_METHOD(char_remove) {
        typedef char char_type;

        const char_type *strings[] = { "Horst", "Hugo", "Heinz", "Hans" };
        multi_sz<char_type> msz(strings, 4);
        Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());

        msz.remove("Hugo");
        Assert::AreEqual(std::size_t(3), msz.count(), L"Three remaining.", LINE_INFO());
        Assert::AreEqual("Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual("Heinz", msz.at(1), L"at(1) is \"Heinz\".", LINE_INFO());
        Assert::AreEqual("Hans", msz.at(2), L"at(2) is \"Hans\".", LINE_INFO());

        msz.remove("Horst");
        Assert::AreEqual(std::size_t(2), msz.count(), L"Two remaining.", LINE_INFO());
        Assert::AreEqual("Heinz", msz.at(0), L"at(0) is \"Heinz\".", LINE_INFO());
        Assert::AreEqual("Hans", msz.at(1), L"at(1) is \"Hans\".", LINE_INFO());

        msz.remove("Hans");
        Assert::AreEqual(std::size_t(1), msz.count(), L"One remaining.", LINE_INFO());
        Assert::AreEqual("Heinz", msz.at(0), L"at(0) is \"Heinz\".", LINE_INFO());

        msz.remove("Hans"); // [sic]
        Assert::AreEqual(std::size_t(1), msz.count(), L"One remaining.", LINE_INFO());
        Assert::AreEqual("Heinz", msz.at(0), L"at(0) is \"Heinz\".", LINE_INFO());

        msz.remove("Heinz");
        Assert::AreEqual(std::size_t(0), msz.count(), L"None remaining.", LINE_INFO());
        Assert::IsNull(msz.at(0), L"at(0) is nullptr.", LINE_INFO());
    }

    TEST_METHOD(wchar_t_remove) {
        typedef wchar_t char_type;

        const char_type *strings[] = { L"Horst", L"Hugo", L"Heinz", L"Hans" };
        multi_sz<char_type> msz(strings, 4);
        Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());

        msz.remove(L"Hugo");
        Assert::AreEqual(std::size_t(3), msz.count(), L"Three remaining.", LINE_INFO());
        Assert::AreEqual(L"Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual(L"Heinz", msz.at(1), L"at(1) is \"Heinz\".", LINE_INFO());
        Assert::AreEqual(L"Hans", msz.at(2), L"at(2) is \"Hans\".", LINE_INFO());

        msz.remove(L"Horst");
        Assert::AreEqual(std::size_t(2), msz.count(), L"Two remaining.", LINE_INFO());
        Assert::AreEqual(L"Heinz", msz.at(0), L"at(0) is \"Heinz\".", LINE_INFO());
        Assert::AreEqual(L"Hans", msz.at(1), L"at(1) is \"Hans\".", LINE_INFO());

        msz.remove(L"Hans");
        Assert::AreEqual(std::size_t(1), msz.count(), L"One remaining.", LINE_INFO());
        Assert::AreEqual(L"Heinz", msz.at(0), L"at(0) is \"Heinz\".", LINE_INFO());

        msz.remove(L"Hans"); // [sic]
        Assert::AreEqual(std::size_t(1), msz.count(), L"One remaining.", LINE_INFO());
        Assert::AreEqual(L"Heinz", msz.at(0), L"at(0) is \"Heinz\".", LINE_INFO());

        msz.remove(L"Heinz");
        Assert::AreEqual(std::size_t(0), msz.count(), L"None remaining.", LINE_INFO());
        Assert::IsNull(msz.at(0), L"at(0) is nullptr.", LINE_INFO());
    }

    TEST_METHOD(char_insert) {
        typedef char char_type;

        multi_sz<char_type> msz;
        Assert::IsTrue(msz.empty(), L"multi-sz is intially empty.", LINE_INFO());

        msz.insert(0, "Hugo");
        Assert::AreEqual(std::size_t(1), msz.count(), L"Element added.", LINE_INFO());
        Assert::AreEqual("Hugo", msz.at(0), L"at(0) is \"Hugo\".", LINE_INFO());

        msz.insert(0, "Horst");
        Assert::AreEqual(std::size_t(2), msz.count(), L"Element added.", LINE_INFO());
        Assert::AreEqual("Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual("Hugo", msz.at(1), L"at(1) is \"Hugo\".", LINE_INFO());

        msz.insert(1, "Heinz");
        Assert::AreEqual(std::size_t(3), msz.count(), L"Element added.", LINE_INFO());
        Assert::AreEqual("Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual("Heinz", msz.at(1), L"at(1) is \"Heinz\".", LINE_INFO());
        Assert::AreEqual("Hugo", msz.at(2), L"at(2) is \"Hugo\".", LINE_INFO());

        msz.insert(3, "Egon");
        Assert::AreEqual(std::size_t(4), msz.count(), L"Element added.", LINE_INFO());
        Assert::AreEqual("Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual("Heinz", msz.at(1), L"at(1) is \"Heinz\".", LINE_INFO());
        Assert::AreEqual("Hugo", msz.at(2), L"at(2) is \"Hugo\".", LINE_INFO());
        Assert::AreEqual("Egon", msz.at(3), L"at(3) is \"Egon\".", LINE_INFO());

        msz.insert(100, "Walter");
        Assert::AreEqual(std::size_t(5), msz.count(), L"Element added.", LINE_INFO());
        Assert::AreEqual("Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual("Heinz", msz.at(1), L"at(1) is \"Heinz\".", LINE_INFO());
        Assert::AreEqual("Hugo", msz.at(2), L"at(2) is \"Hugo\".", LINE_INFO());
        Assert::AreEqual("Egon", msz.at(3), L"at(3) is \"Egon\".", LINE_INFO());
        Assert::AreEqual("Walter", msz.at(4), L"at(4) is \"Walter\".", LINE_INFO());
    }

    TEST_METHOD(wchar_t_insert) {
        typedef wchar_t char_type;

        multi_sz<char_type> msz;
        Assert::IsTrue(msz.empty(), L"multi-sz is intially empty.", LINE_INFO());

        msz.insert(0, L"Hugo");
        Assert::AreEqual(std::size_t(1), msz.count(), L"Element added.", LINE_INFO());
        Assert::AreEqual(L"Hugo", msz.at(0), L"at(0) is \"Hugo\".", LINE_INFO());

        msz.insert(0, L"Horst");
        Assert::AreEqual(std::size_t(2), msz.count(), L"Element added.", LINE_INFO());
        Assert::AreEqual(L"Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual(L"Hugo", msz.at(1), L"at(1) is \"Hugo\".", LINE_INFO());

        msz.insert(1, L"Heinz");
        Assert::AreEqual(std::size_t(3), msz.count(), L"Element added.", LINE_INFO());
        Assert::AreEqual(L"Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual(L"Heinz", msz.at(1), L"at(1) is \"Heinz\".", LINE_INFO());
        Assert::AreEqual(L"Hugo", msz.at(2), L"at(2) is \"Hugo\".", LINE_INFO());

        msz.insert(3, L"Egon");
        Assert::AreEqual(std::size_t(4), msz.count(), L"Element added.", LINE_INFO());
        Assert::AreEqual(L"Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual(L"Heinz", msz.at(1), L"at(1) is \"Heinz\".", LINE_INFO());
        Assert::AreEqual(L"Hugo", msz.at(2), L"at(2) is \"Hugo\".", LINE_INFO());
        Assert::AreEqual(L"Egon", msz.at(3), L"at(3) is \"Egon\".", LINE_INFO());

        msz.insert(100, L"Walter");
        Assert::AreEqual(std::size_t(5), msz.count(), L"Element added.", LINE_INFO());
        Assert::AreEqual(L"Horst", msz.at(0), L"at(0) is \"Horst\".", LINE_INFO());
        Assert::AreEqual(L"Heinz", msz.at(1), L"at(1) is \"Heinz\".", LINE_INFO());
        Assert::AreEqual(L"Hugo", msz.at(2), L"at(2) is \"Hugo\".", LINE_INFO());
        Assert::AreEqual(L"Egon", msz.at(3), L"at(3) is \"Egon\".", LINE_INFO());
        Assert::AreEqual(L"Walter", msz.at(4), L"at(4) is \"Walter\".", LINE_INFO());
    }

    TEST_METHOD(char_iterator) {
        typedef char char_type;

        {
            multi_sz<char_type> msz;
            Assert::IsTrue(msz.empty(), L"multi-sz is intially empty.", LINE_INFO());

            auto it = msz.begin();
            Assert::IsTrue(it == msz.end(), L"Immediately at end", LINE_INFO());
        }

        {
            const char_type *strings[] = { "Horst", "Hugo", "Heinz", "Hans" };
            multi_sz<char_type> msz(strings, 4);
            Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());

            auto it = msz.begin();
            Assert::IsFalse(it == msz.end(), L"Not at end", LINE_INFO());
            Assert::AreEqual("Horst", *it, "At \"Horst\".", LINE_INFO());

            ++it;
            Assert::IsFalse(it == msz.end(), L"Not at end", LINE_INFO());
            Assert::AreEqual("Hugo", *it, "At \"Hugo\".", LINE_INFO());

            ++it;
            Assert::IsFalse(it == msz.end(), L"Not at end", LINE_INFO());
            Assert::AreEqual("Heinz", *it, "At \"Heinz\".", LINE_INFO());

            ++it;
            Assert::IsFalse(it == msz.end(), L"Not at end", LINE_INFO());
            Assert::AreEqual("Hans", *it, "At \"Hans\".", LINE_INFO());

            ++it;
            Assert::IsTrue(it == msz.end(), L"At end", LINE_INFO());
        }
    }

    TEST_METHOD(wchar_t_iterator) {
        typedef wchar_t char_type;

        {
            multi_sz<char_type> msz;
            Assert::IsTrue(msz.empty(), L"multi-sz is intially empty.", LINE_INFO());

            auto it = msz.begin();
            Assert::IsTrue(it == msz.end(), L"Immediately at end", LINE_INFO());
        }

        {
            const char_type *strings[] = { L"Horst", L"Hugo", L"Heinz", L"Hans" };
            multi_sz<char_type> msz(strings, 4);
            Assert::IsFalse(msz.empty(), L"multi-sz is intially not empty.", LINE_INFO());

            auto it = msz.begin();
            Assert::IsFalse(it == msz.end(), L"Not at end", LINE_INFO());
            Assert::AreEqual(L"Horst", *it, "At \"Horst\".", LINE_INFO());

            ++it;
            Assert::IsFalse(it == msz.end(), L"Not at end", LINE_INFO());
            Assert::AreEqual(L"Hugo", *it, "At \"Hugo\".", LINE_INFO());

            ++it;
            Assert::IsFalse(it == msz.end(), L"Not at end", LINE_INFO());
            Assert::AreEqual(L"Heinz", *it, "At \"Heinz\".", LINE_INFO());

            ++it;
            Assert::IsFalse(it == msz.end(), L"Not at end", LINE_INFO());
            Assert::AreEqual(L"Hans", *it, "At \"Hans\".", LINE_INFO());

            ++it;
            Assert::IsTrue(it == msz.end(), L"At end", LINE_INFO());
        }
    }


    TEST_METHOD(char_copy) {
        typedef char char_type;

        {
            std::vector<std::basic_string<char_type>> strings;
            multi_sz<char_type>::copy(nullptr, std::back_inserter(strings));
            Assert::IsTrue(strings.empty(), L"Nothing copied", LINE_INFO());
        }

        {
            multi_sz<char_type> msz;
            std::vector<std::basic_string<char_type>> strings;
            multi_sz<char_type>::copy(msz.data(), std::back_inserter(strings));
            Assert::IsTrue(strings.empty(), L"Nothing copied", LINE_INFO());
        }

        {
            multi_sz<char_type> msz;
            msz.add(PWROWG_TPL_LITERAL(char_type, "Horst"));
            std::vector<std::basic_string<char_type>> strings;
            multi_sz<char_type>::copy(msz.data(), std::back_inserter(strings));
            Assert::AreEqual(std::size_t(1), strings.size(), L"One copied", LINE_INFO());
            Assert::AreEqual(PWROWG_TPL_LITERAL(char_type, "Horst"), strings.front().data(), L"Copy OK", LINE_INFO());
        }

        {
            multi_sz<char_type> msz;
            msz.add(PWROWG_TPL_LITERAL(char_type, "Horst"));
            msz.add(PWROWG_TPL_LITERAL(char_type, "Egon"));
            std::vector<std::basic_string<char_type>> strings;
            multi_sz<char_type>::copy(msz.data(), std::back_inserter(strings));
            Assert::AreEqual(std::size_t(2), strings.size(), L"Two copied", LINE_INFO());
            Assert::AreEqual(PWROWG_TPL_LITERAL(char_type, "Horst"), strings.front().data(), L"Front OK", LINE_INFO());
            Assert::AreEqual(PWROWG_TPL_LITERAL(char_type, "Egon"), strings.back().data(), L"Back OK", LINE_INFO());
        }
    }

    TEST_METHOD(wchar_t_copy) {
        typedef wchar_t char_type;

        {
            std::vector<std::basic_string<char_type>> strings;
            multi_sz<char_type>::copy(nullptr, std::back_inserter(strings));
            Assert::IsTrue(strings.empty(), L"Nothing copied", LINE_INFO());
        }

        {
            multi_sz<char_type> msz;
            std::vector<std::basic_string<char_type>> strings;
            multi_sz<char_type>::copy(msz.data(), std::back_inserter(strings));
            Assert::IsTrue(strings.empty(), L"Nothing copied", LINE_INFO());
        }

        {
            multi_sz<char_type> msz;
            msz.add(PWROWG_TPL_LITERAL(char_type, "Horst"));
            std::vector<std::basic_string<char_type>> strings;
            multi_sz<char_type>::copy(msz.data(), std::back_inserter(strings));
            Assert::AreEqual(std::size_t(1), strings.size(), L"One copied", LINE_INFO());
            Assert::AreEqual(PWROWG_TPL_LITERAL(char_type, "Horst"), strings.front().data(), L"Copy OK", LINE_INFO());
        }

        {
            multi_sz<char_type> msz;
            msz.add(PWROWG_TPL_LITERAL(char_type, "Horst"));
            msz.add(PWROWG_TPL_LITERAL(char_type, "Egon"));
            std::vector<std::basic_string<char_type>> strings;
            multi_sz<char_type>::copy(msz.data(), std::back_inserter(strings));
            Assert::AreEqual(std::size_t(2), strings.size(), L"Two copied", LINE_INFO());
            Assert::AreEqual(PWROWG_TPL_LITERAL(char_type, "Horst"), strings.front().data(), L"Front OK", LINE_INFO());
            Assert::AreEqual(PWROWG_TPL_LITERAL(char_type, "Egon"), strings.back().data(), L"Back OK", LINE_INFO());
        }
    }
};

PWROWG_TEST_NAMESPACE_END
