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
