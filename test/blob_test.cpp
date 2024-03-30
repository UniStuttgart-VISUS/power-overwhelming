// <copyright file="blob_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(blob_test) {

    public:

      TEST_METHOD(default_ctor) {
            blob b;

            Assert::IsNull(b.data(), L"Data of default-initialised blob is nullptr", LINE_INFO());
            Assert::AreEqual(std::size_t(0), b.size(), L"Size of default-initialised blob is zero", LINE_INFO());
        }

        TEST_METHOD(size_ctor) {
            const std::size_t expected = 42;
            blob b(expected);

            Assert::IsNotNull(b.data(), L"Data of has been allocated", LINE_INFO());
            Assert::AreEqual(expected, b.size(), L"Requested size has been allocated at construction", LINE_INFO());
        }

        TEST_METHOD(init_ctor) {
            {
                blob b { std::uint8_t(1), std::uint8_t(2), std::uint8_t(3) };

                Assert::IsNotNull(b.data(), L"Data of has been allocated", LINE_INFO());
                Assert::AreEqual(std::size_t(3), b.size(), L"Requested size has been allocated at construction", LINE_INFO());
                Assert::AreEqual(std::uint8_t(1), *b.as<std::uint8_t>(0), L"Initialiser at 0", LINE_INFO());
                Assert::AreEqual(std::uint8_t(2), *b.as<std::uint8_t>(1), L"Initialiser at 1", LINE_INFO());
                Assert::AreEqual(std::uint8_t(3), *b.as<std::uint8_t>(2), L"Initialiser at 2", LINE_INFO());
            }

            {
                blob b { std::int32_t(1), std::int32_t(2), std::int32_t(3) };
                Assert::IsNotNull(b.data(), L"Data of has been allocated", LINE_INFO());
                Assert::AreEqual(std::size_t(3 * sizeof(std::int32_t)), b.size(), L"Requested size has been allocated at construction", LINE_INFO());
                Assert::AreEqual(std::int32_t(1), *b.as<std::int32_t>(0 * sizeof(std::int32_t)), L"Initialiser at 0", LINE_INFO());
                Assert::AreEqual(std::int32_t(2), *b.as<std::int32_t>(1 * sizeof(std::int32_t)), L"Initialiser at 1", LINE_INFO());
                Assert::AreEqual(std::int32_t(3), *b.as<std::int32_t>(2 * sizeof(std::int32_t)), L"Initialiser at 2", LINE_INFO());
            }
        }

        TEST_METHOD(copy_ctor) {
            blob b1 { std::uint8_t(3), std::uint8_t(4), std::uint8_t(5) };
            blob b2(b1);

            Assert::IsNotNull(b2.data(), L"Data of has been allocated", LINE_INFO());
            Assert::AreEqual(b1.size(), b2.size(), L"Size has been copied", LINE_INFO());
            Assert::AreEqual(*b1.as<std::uint8_t>(0), *b2.as<std::uint8_t>(0), L"Copy at 0", LINE_INFO());
            Assert::AreEqual(*b1.as<std::uint8_t>(1), *b2.as<std::uint8_t>(1), L"Copy at 1'", LINE_INFO());
            Assert::AreEqual(*b1.as<std::uint8_t>(2), *b2.as<std::uint8_t>(2), L"Copy at 2", LINE_INFO());
        }

        TEST_METHOD(move_ctor) {
            blob b1 { std::uint8_t(6), std::uint8_t(7), std::uint8_t(8) };
            const auto expected_ptr = b1.data();
            const auto expected_size = b1.size();
            blob b2(std::move(b1));

            Assert::IsNotNull(b2.data(), L"Data of has been moved", LINE_INFO());
            Assert::AreEqual(expected_ptr, b2.data(), L"Pointer has been moved", LINE_INFO());
            Assert::AreEqual(expected_size, b2.size(), L"Size has been copied", LINE_INFO());
            Assert::IsNull(b1.data(), L"Source of move has been erased", LINE_INFO());
            Assert::AreEqual(std::size_t(0), b1.size(), L"Source of move has size zero", LINE_INFO());
        }

        TEST_METHOD(accessors) {
            blob b(1);
            const auto& r = b;

            Assert::IsTrue(b.data() == r.data(), L"Const vs non-const data", LINE_INFO());
            Assert::IsTrue(static_cast<void *>(b) == static_cast<const void *>(r), L"Const vs non-const cast", LINE_INFO());
            Assert::AreEqual(b.data(), static_cast<void *>(b), L"Cast vs data", LINE_INFO());
        }

        TEST_METHOD(reserve) {
            blob b;

            Assert::IsTrue(b.reserve(8), L"reserve 8 from 0", LINE_INFO());
            Assert::AreEqual(std::size_t(8), b.size(), L"Size after reserve", LINE_INFO());
            Assert::IsFalse(b.reserve(4), L"reserve 4 from 8", LINE_INFO());
            Assert::AreEqual(std::size_t(8), b.size(), L"Size unchanged after reserve", LINE_INFO());
        }

        TEST_METHOD(grow) {
            blob b { std::uint8_t(1), std::uint8_t(2) };

            Assert::IsTrue(b.grow(8), L"grow 8 from 2", LINE_INFO());
            Assert::AreEqual(std::size_t(8), b.size(), L"Size after grow", LINE_INFO());
            Assert::AreEqual(std::uint8_t(1), *b.as<std::uint8_t>(0), L"Data copied at 0", LINE_INFO());
            Assert::AreEqual(std::uint8_t(2), *b.as<std::uint8_t>(1), L"Data copied at 1", LINE_INFO());
            Assert::IsFalse(b.grow(4), L"grow 4 from 8", LINE_INFO());
            Assert::AreEqual(std::size_t(8), b.size(), L"Size unchanged after grow", LINE_INFO());
            Assert::AreEqual(std::uint8_t(1), *b.as<std::uint8_t>(0), L"Data unchanged at 0", LINE_INFO());
            Assert::AreEqual(std::uint8_t(2), *b.as<std::uint8_t>(1), L"Data unchanged at 1", LINE_INFO());
        }

        TEST_METHOD(resize) {
            blob b;

            b.resize(8);
            Assert::AreEqual(std::size_t(8), b.size(), L"Size after resize", LINE_INFO());
            b.resize(4);
            Assert::AreEqual(std::size_t(4), b.size(), L"Size unchanged after resize", LINE_INFO());
        }

        TEST_METHOD(truncate) {
            blob b { std::uint8_t(1), std::uint8_t(2) };

            b.truncate(8);
            Assert::AreEqual(std::size_t(8), b.size(), L"Size after truncate", LINE_INFO());
            Assert::AreEqual(std::uint8_t(1), *b.as<std::uint8_t>(0), L"Data copied at 0", LINE_INFO());
            Assert::AreEqual(std::uint8_t(2), *b.as<std::uint8_t>(1), L"Data copied at 1", LINE_INFO());
            b.truncate(4);
            Assert::AreEqual(std::size_t(4), b.size(), L"Size after truncate", LINE_INFO());
            Assert::AreEqual(std::uint8_t(1), *b.as<std::uint8_t>(0), L"Data unchanged at 0", LINE_INFO());
            Assert::AreEqual(std::uint8_t(2), *b.as<std::uint8_t>(1), L"Data unchanged at 1", LINE_INFO());
            b.truncate(1);
            Assert::AreEqual(std::size_t(1), b.size(), L"Size after truncate", LINE_INFO());
            Assert::AreEqual(std::uint8_t(1), *b.as<std::uint8_t>(0), L"Data unchanged at 0", LINE_INFO());
        }

        TEST_METHOD(as) {
            blob b { std::int16_t(1), std::int16_t(2) };

            Assert::AreEqual(std::size_t(4), b.size(), L"Size after ctor", LINE_INFO());
            Assert::AreEqual(std::int16_t(1), *b.as<std::int16_t>(), L"Data at 0", LINE_INFO());
            Assert::AreEqual(std::int16_t(2), *b.as<std::int16_t>(2), L"Data at 2", LINE_INFO());
        }

        TEST_METHOD(at) {
            blob b { std::int16_t(1), std::int16_t(2) };

            Assert::AreEqual(std::size_t(4), b.size(), L"Size after ctor", LINE_INFO());
            Assert::AreEqual(std::int16_t(1), *static_cast<std::int16_t *>(b.at(0)), L"Data at 0", LINE_INFO());
            Assert::AreEqual(std::int16_t(2), *static_cast<std::int16_t *>(b.at(2)), L"Data at 2", LINE_INFO());
        }

        TEST_METHOD(clear) {
            blob b(5);

            Assert::AreEqual(std::size_t(5), b.size(), L"Size after ctor", LINE_INFO());
            b.clear();
            Assert::AreEqual(std::size_t(0), b.size(), L"Size after clear", LINE_INFO());
            Assert::IsFalse(bool(b), L"Status after clear", LINE_INFO());
            Assert::IsNull(b.data(), L"Pointer after clear", LINE_INFO());
        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
