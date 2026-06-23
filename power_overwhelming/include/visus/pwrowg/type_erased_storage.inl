// <copyright file="type_erased_storage.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::type_erased_storage::emplace
 */
template<class TType, class... TArgs>
TType& PWROWG_NAMESPACE::type_erased_storage::emplace(TArgs&&... args) {
    // We do not know what is already stored, so we must destruct it.
    this->reset();
    assert(this->_state == state::empty);

    if (sizeof(TType) <= sizeof(this->_data)) {
        // In-place construct the new object.
        new (this->_data.small_value) TType(std::forward<TArgs>(args)...);
        auto& retval = *reinterpret_cast<TType *>(this->_data.small_value);

        // Register the operations for the new type.
        this->_cp = make_copy<TType>();
        this->_dtor = make_dtor<TType>();

        // Remember what's in the storage.
        this->_state = state::small_value;
        return retval;

    } else {
        // Construct the new object on the heap.
        auto retval = new TType(std::forward<TArgs>(args)...);
        this->_data.value = retval;

        // Register the operations for the new type.
        this->_cp = make_copy<TType>();
        this->_dtor = make_dtor<TType>();

        // Remember what's in the storage.
        this->_state = state::large_value;
        return *retval;
    }
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::make_copy
 */
template<class TType>
static std::enable_if_t<!std::is_copy_constructible_v<TType>,
    PWROWG_NAMESPACE::type_erased_storage::copy_type>
PWROWG_NAMESPACE::type_erased_storage::make_copy(void) noexcept {
    return [](data& dst, const data& src) {
        throw std::logic_error("The object contained in a type-erased storage "
            "block is not copyable.");
    };
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::make_copy
 */
template<class TType>
static std::enable_if_t<std::is_copy_constructible_v<TType>
    && PWROWG_NAMESPACE::type_erased_storage::is_small_v<TType>,
    PWROWG_NAMESPACE::type_erased_storage::copy_type>
PWROWG_NAMESPACE::type_erased_storage::make_copy(void) noexcept {
    return [](_Out_ data& dst, _In_ const data& src) {
        auto d = reinterpret_cast<void *>(dst.small_value);
        auto s = reinterpret_cast<const void *>(src.small_value);
        new (d) TType(*static_cast<const TType *>(s));
    };
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::make_copy
 */
template<class TType>
static std::enable_if_t<std::is_copy_constructible_v<TType>
    && !PWROWG_NAMESPACE::type_erased_storage::is_small_v<TType>,
    PWROWG_NAMESPACE::type_erased_storage::copy_type>
PWROWG_NAMESPACE::type_erased_storage::make_copy(void) noexcept {
    return [](_Out_ data& dst, _In_ const data& src) {
        dst.value = new TType(*static_cast<const TType *>(src.value));
    };
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::make_dtor
 */
template<class TType>
std::enable_if_t<
    PWROWG_NAMESPACE::type_erased_storage::is_small_v<TType>,
    PWROWG_NAMESPACE::type_erased_storage::destruct_type>
PWROWG_NAMESPACE::type_erased_storage::make_dtor(void) noexcept {
    return [](_Inout_ data& obj) {
        reinterpret_cast<TType *>(obj.small_value)->~TType();
#if (defined(_DEBUG) || defined(_DEBUG))
        ::memset(&obj, 0x5D, sizeof(obj));
#endif /* (defined(_DEBUG) || defined(_DEBUG)) */
    };
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::make_dtor
 */
template<class TType>
std::enable_if_t<
    !PWROWG_NAMESPACE::type_erased_storage::is_small_v<TType>,
    PWROWG_NAMESPACE::type_erased_storage::destruct_type>
PWROWG_NAMESPACE::type_erased_storage::make_dtor(void) noexcept {
    return [](_Inout_ data& obj) {
        delete static_cast<TType *>(obj.value);
#if (defined(_DEBUG) || defined(_DEBUG))
        ::memset(&obj, 0, sizeof(obj));
#endif /* (defined(_DEBUG) || defined(_DEBUG)) */
    };
}
