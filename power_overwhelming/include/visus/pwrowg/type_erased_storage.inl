// <copyright file="type_erased_storage.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::type_erased_storage::emplace
 */
template<class TType, class... TArgs>
std::enable_if_t<std::is_copy_constructible_v<TType>, TType &>
PWROWG_NAMESPACE::type_erased_storage::emplace(TArgs&&... args) {
    // We do not know what is already stored, so we must destruct it.
    this->reset();
    assert(!*this);

    // Construct the new object in place.
    auto retval = new TType(std::forward<TArgs>(args)...);
    this->_data = retval;

    // Register the operations for the new type.
    this->_cp = [](_Out_ void *& dst, _In_ const void *src) {
        assert(dst == nullptr);
        dst = new TType(*static_cast<const TType *>(src));
    };

    this->_dtor = [](void *obj) {
        delete static_cast<TType *>(obj);
    };

    return *retval;
}
