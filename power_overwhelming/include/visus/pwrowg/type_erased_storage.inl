// <copyright file="type_erased_storage.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::type_erased_storage::type_erased_storage
 */
template<class TType>
PWROWG_NAMESPACE::type_erased_storage::type_erased_storage(
        _In_ const TType& data) : _data(sizeof(data)) {
    this->reg_cp<TType>();
    this->reg_cp_ctor<TType>();
    this->reg_dtor<TType>();
    this->reg_mv<TType>();
    this->reg_mv_ctor<TType>();
    this->_cp_ctor(this->_data, &data);
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::reg_cp
 */
template<class TType>
std::enable_if_t<std::is_copy_assignable_v<TType>>
PWROWG_NAMESPACE::type_erased_storage::reg_cp(void) noexcept {
    this->_copy = [](void *dst, const void *src) {
        auto d = static_cast<TType *>(dst);
        auto s = static_cast<const TType *>(src);
        *d = *s;
    };
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::reg_cp
 */
template<class TType>
std::enable_if_t<!std::is_copy_assignable_v<TType>>
PWROWG_NAMESPACE::type_erased_storage::reg_cp(void) noexcept {
    this->_copy = nullptr;
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::reg_cp_ctor
 */
template<class TType>
std::enable_if_t<std::is_copy_constructible_v<TType>>
PWROWG_NAMESPACE::type_erased_storage::reg_cp_ctor(void) noexcept {
    this->_copy_constructor = [](void *dst, const void *src) {
        auto d = static_cast<TType *>(dst);
        auto s = static_cast<const TType *>(src);
        new (d)(*s);
    };
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::reg_cp_ctor
 */
template<class TType>
std::enable_if_t<!std::is_copy_constructible_v<TType>>
PWROWG_NAMESPACE::type_erased_storage::reg_cp_ctor(void) noexcept {
    this->_copy_constructor = nullptr;
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::reg_dtor
 */
template<class TType>
void PWROWG_NAMESPACE::type_erased_storage::reg_dtor(void) noexcept {
    this->_destructor = [](void *obj) {
        auto o = static_cast<TType *>(obj);
        o->~TType();
    };
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::reg_mv
 */
template<class TType>
std::enable_if_t<std::is_move_assignable_v<TType>>
PWROWG_NAMESPACE::type_erased_storage::reg_mv(void) noexcept {
    this->_move = [](void *dst, const void *src) {
        auto d = static_cast<TType *>(dst);
        auto s = static_cast<const TType *>(src);
        *d = std::move(*s);
    };
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::reg_mv
 */
template<class TType>
std::enable_if_t<!std::is_move_assignable_v<TType>>
PWROWG_NAMESPACE::type_erased_storage::reg_mv(void) noexcept {
    this->_move = nullptr;
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::reg_mv_ctor
 */
template<class TType>
std::enable_if_t<std::is_move_constructible_v<TType>>
PWROWG_NAMESPACE::type_erased_storage::reg_mv_ctor(void) noexcept {
    this->_move_constructor = [](void *dst, const void *src) {
        auto d = static_cast<TType *>(dst);
        auto s = static_cast<const TType *>(src);
        new (d)(std::move(*s));
    };
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::reg_mv_ctor
 */
template<class TType>
std::enable_if_t<!std::is_move_constructible_v<TType>>
PWROWG_NAMESPACE::type_erased_storage::reg_mv_ctor(void) noexcept {
    this->_move_constructor = nullptr;
}
