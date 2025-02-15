// <copyright file="type_erased_storage_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(type_erased_storage_test) {

public:

    class op_counter final {

    public:

        inline op_counter(int payload,
                std::size_t& cp_ctor,
                std::size_t& mv_ctor,
                std::size_t& dtor,
                std::size_t& cp,
                std::size_t& mv) noexcept
            : _cp(cp),
                _cp_ctor(cp_ctor),
                _dtor(dtor),
                _mv(mv),
                _mv_ctor(mv_ctor),
                _payload(payload) { }

        inline op_counter(const op_counter& rhs) noexcept
            : _cp(rhs._cp),
                _cp_ctor(rhs._cp_ctor),
                _dtor(rhs._dtor),
                _mv(rhs._mv),
                _mv_ctor(rhs._mv_ctor),
                _payload(rhs._payload) {
            ++this->_cp_ctor;
        }

        inline op_counter(op_counter&& rhs) noexcept
            : _cp(rhs._cp),
                _cp_ctor(rhs._cp_ctor),
                _dtor(rhs._dtor),
                _mv(rhs._mv),
                _mv_ctor(rhs._mv_ctor),
                _payload(rhs._payload) {
            ++this->_mv_ctor;
            rhs._payload = 0;
        }

        inline ~op_counter(void) noexcept {
            ++this->_dtor;
        }

        inline op_counter& operator =(const op_counter& rhs) noexcept {
            if (this != std::addressof(rhs)) {
                this->_payload = rhs._payload;
            }

            ++this->_cp;
            return *this;
        }

        inline op_counter& operator =(op_counter&& rhs) noexcept {
            if (this != std::addressof(rhs)) {
                this->_payload = rhs._payload;
                rhs._payload = 0;
            }

            ++this->_mv;
            return *this;
        }

        inline int payload(void) const noexcept {
            return this->_payload;
        }

    private:

        std::size_t& _cp;
        std::size_t& _cp_ctor;
        std::size_t& _dtor;
        std::size_t& _mv;
        std::size_t& _mv_ctor;
        int _payload;
    };

    TEST_METHOD(test_ctor) {
        type_erased_storage tes;
        Assert::IsFalse(tes, L"Initialised empty", LINE_INFO());
    }

    TEST_METHOD(test_cp_ctor) {
        std::size_t cp = 0;
        std::size_t cp_ctor = 0;
        std::size_t dtor = 0;
        std::size_t mv = 0;
        std::size_t mv_ctor = 0;

        type_erased_storage tes1;
        tes1.emplace<op_counter>(1, cp_ctor, mv_ctor, dtor, cp, mv);
        type_erased_storage tes2(tes1);
        Assert::AreEqual(1, tes2.get<op_counter>()->payload(), L"Payload copied", LINE_INFO());
        Assert::AreEqual(1, tes1.get<op_counter>()->payload(), L"Source unchanged", LINE_INFO());

        Assert::AreEqual(std::size_t(0), cp, L"No copy", LINE_INFO());
        Assert::AreEqual(std::size_t(1), cp_ctor, L"Copy construction", LINE_INFO());
        Assert::AreEqual(std::size_t(0), dtor, L"No destruction", LINE_INFO());
        Assert::AreEqual(std::size_t(0), mv, L"No move", LINE_INFO());
        Assert::AreEqual(std::size_t(0), mv_ctor, L"No move construct", LINE_INFO());
    }

    TEST_METHOD(test_cp) {
        std::size_t cp = 0;
        std::size_t cp_ctor = 0;
        std::size_t dtor = 0;
        std::size_t mv = 0;
        std::size_t mv_ctor = 0;

        type_erased_storage tes1;
        tes1.emplace<op_counter>(1, cp_ctor, mv_ctor, dtor, cp, mv);

        type_erased_storage tes2;
        tes2.emplace<op_counter>(2, cp_ctor, mv_ctor, dtor, cp, mv);
        Assert::AreEqual(1, tes1.get<op_counter>()->payload(), L"Source payload", LINE_INFO());
        Assert::AreEqual(2, tes2.get<op_counter>()->payload(), L"Destination payload", LINE_INFO());

        tes2 = tes1;
        Assert::AreEqual(1, tes1.get<op_counter>()->payload(), L"Source payload unchanged", LINE_INFO());
        Assert::AreEqual(1, tes2.get<op_counter>()->payload(), L"Destination payload updated", LINE_INFO());

        Assert::AreEqual(std::size_t(0), cp, L"No copy", LINE_INFO());
        Assert::AreEqual(std::size_t(1), cp_ctor, L"Copy construction", LINE_INFO());
        Assert::AreEqual(std::size_t(1), dtor, L"Destruction", LINE_INFO());
        Assert::AreEqual(std::size_t(0), mv, L"No move", LINE_INFO());
        Assert::AreEqual(std::size_t(0), mv_ctor, L"No move construct", LINE_INFO());
    }

    TEST_METHOD(test_cp_to_empty) {
        std::size_t cp = 0;
        std::size_t cp_ctor = 0;
        std::size_t dtor = 0;
        std::size_t mv = 0;
        std::size_t mv_ctor = 0;

        type_erased_storage tes1;
        tes1.emplace<op_counter>(1, cp_ctor, mv_ctor, dtor, cp, mv);

        type_erased_storage tes2;
        Assert::AreEqual(1, tes1.get<op_counter>()->payload(), L"Source payload", LINE_INFO());

        tes2 = tes1;
        Assert::AreEqual(1, tes1.get<op_counter>()->payload(), L"Source payload unchanged", LINE_INFO());
        Assert::AreEqual(1, tes2.get<op_counter>()->payload(), L"Destination payload updated", LINE_INFO());

        Assert::AreEqual(std::size_t(0), cp, L"No copy", LINE_INFO());
        Assert::AreEqual(std::size_t(1), cp_ctor, L"Copy construction", LINE_INFO());
        Assert::AreEqual(std::size_t(0), dtor, L"No destruction", LINE_INFO());
        Assert::AreEqual(std::size_t(0), mv, L"No move", LINE_INFO());
        Assert::AreEqual(std::size_t(0), mv_ctor, L"No move construct", LINE_INFO());
    }

    TEST_METHOD(test_dtor) {
        std::size_t cp = 0;
        std::size_t cp_ctor = 0;
        std::size_t dtor = 0;
        std::size_t mv = 0;
        std::size_t mv_ctor = 0;

        {
            type_erased_storage tes1;
            tes1.emplace<op_counter>(1, cp_ctor, mv_ctor, dtor, cp, mv);
        }

        Assert::AreEqual(std::size_t(0), cp, L"No copy", LINE_INFO());
        Assert::AreEqual(std::size_t(0), cp_ctor, L"No copy construction", LINE_INFO());
        Assert::AreEqual(std::size_t(1), dtor, L"Destruction", LINE_INFO());
        Assert::AreEqual(std::size_t(0), mv, L"No move", LINE_INFO());
        Assert::AreEqual(std::size_t(0), mv_ctor, L"No move construct", LINE_INFO());
    }
};

PWROWG_TEST_NAMESPACE_END
