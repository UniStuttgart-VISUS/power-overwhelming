// <copyright file="type_erased_storage.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::type_erased_storage::emplace
 */
template<class TType, class... TArgs>
std::enable_if_t<std::is_copy_constructible_v<TType>, TType&>
PWROWG_NAMESPACE::type_erased_storage::emplace(TArgs&&... args) {
    // We do not know what is already stored, so we must destruct it.
    this->reset();
    assert(this->_state == state::empty);

    if (sizeof(TType) <= sizeof(this->_data)) {
        // In-place construct the new object.
        new (this->_data.small_value) TType(std::forward<TArgs>(args)...);
        auto& retval = *reinterpret_cast<TType *>(this->_data.small_value);

        // Register the operations for the new type.
        this->_cp = [](_Out_ data& dst, _In_ const data& src) {
            auto d = reinterpret_cast<void *>(dst.small_value);
            auto s = reinterpret_cast<const void *>(src.small_value);
            new (d) TType(*static_cast<const TType *>(s));
        };

        this->_dtor = [](data& obj) {
            reinterpret_cast<TType *>(obj.small_value)->~TType();
#if (defined(_DEBUG) || defined(_DEBUG))
            ::memset(&obj, 0x5D, sizeof(obj));
#endif /* (defined(_DEBUG) || defined(_DEBUG)) */
        };

        this->_state = state::small_value;
        return retval;

    } else {
        // Construct the new object on the heap.
        auto retval = new TType(std::forward<TArgs>(args)...);
        this->_data.value = retval;

        // Register the operations for the new type.
        this->_cp = [](_Out_ data& dst, _In_ const data& src) {
            dst.value = new TType(*static_cast<const TType *>(src.value));
        };

        this->_dtor = [](data& obj) {
            delete static_cast<TType *>(obj.value);
#if (defined(_DEBUG) || defined(_DEBUG))
            ::memset(&obj, 0, sizeof(obj));
#endif /* (defined(_DEBUG) || defined(_DEBUG)) */
        };

        this->_state = state::large_value;
        return *retval;
    }
}


#if false
/*
 * PWROWG_NAMESPACE::type_erased_storage::emplace_non_copyable
 */
template<class TType, class... TArgs>
TType& PWROWG_NAMESPACE::type_erased_storage::emplace_non_copyable(
        TArgs&&... args) {
    // We do not know what is already stored, so we must destruct it.
    this->reset();
    assert(!*this);
    assert(this->_cp == nullptr);

    // Construct the new object in place.
    auto retval = new TType(std::forward<TArgs>(args)...);
    this->_data = retval;

    this->_dtor = [](void *obj) {
        delete static_cast<TType *>(obj);
    };

    return *retval;
}
#endif
