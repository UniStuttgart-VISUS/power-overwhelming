// <copyright file="hash_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(hash_test) {

public:

    TEST_METHOD(fnv1a32) {
        // Reference values from https://github.com/lcn2/fnv?/test_fnv.c
        typedef std::uint32_t value_type;
        typedef visus::pwrowg::detail::fnv1a<value_type> hash_type;

        {
            const char *input = "";
            hash_type hash;
            hash(input, input + ::strlen(input));
            Assert::AreEqual(value_type(0x811c9dc5UL), static_cast<value_type>(hash), L"empty string", LINE_INFO());
        }

        {
            const char *input = "a";
            hash_type hash;
            hash(input, input + ::strlen(input));
            Assert::AreEqual(value_type(0xe40c292cUL), static_cast<value_type>(hash), L"a", LINE_INFO());
        }

        {
            const char *input = "b";
            hash_type hash;
            hash(input, input + ::strlen(input));
            Assert::AreEqual(value_type(0xe70c2de5UL), static_cast<value_type>(hash), L"b", LINE_INFO());
        }

        {
            const char *input = "foobar";
            hash_type hash;
            hash(input, input + ::strlen(input));
            Assert::AreEqual(value_type(0xbf9cf968UL), static_cast<value_type>(hash), L"foobar", LINE_INFO());
        }
    }

    TEST_METHOD(fnv1a64) {
        // Reference values from https://github.com/lcn2/fnv?/test_fnv.c
        typedef std::uint64_t value_type;
        typedef visus::pwrowg::detail::fnv1a<value_type> hash_type;

        {
            const char *input = "";
            hash_type hash;
            hash(input, input + ::strlen(input));
            Assert::AreEqual(value_type(0xcbf29ce484222325ULL), static_cast<value_type>(hash), L"empty string", LINE_INFO());
        }

        {
            const char *input = "a";
            hash_type hash;
            hash(input, input + ::strlen(input));
            Assert::AreEqual(value_type(0xaf63dc4c8601ec8cULL), static_cast<value_type>(hash), L"a", LINE_INFO());
        }

        {
            const char *input = "b";
            hash_type hash;
            hash(input, input + ::strlen(input));
            Assert::AreEqual(value_type(0xaf63df4c8601f1a5ULL), static_cast<value_type>(hash), L"b", LINE_INFO());
        }

        {
            const char *input = "foobar";
            hash_type hash;
            hash(input, input + ::strlen(input));
            Assert::AreEqual(value_type(0x85944171f73967e8ULL), static_cast<value_type>(hash), L"foobar", LINE_INFO());
        }
    }

};

PWROWG_TEST_NAMESPACE_END
