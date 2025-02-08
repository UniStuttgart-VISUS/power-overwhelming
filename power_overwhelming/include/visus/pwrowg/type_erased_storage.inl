// <copyright file="type_erased_storage.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
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

    // Construct the new object in place.
    this->_data.resize(sizeof(TType));
    new (this->_data.as<TType>()) TType(std::forward<TArgs>(args)...);

    // Register the operations for the new type.
    this->reg_cp<TType>();
    this->reg_cp_ctor<TType>();
    this->reg_dtor<TType>();

    return *(this->_data.as<TType>());
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::reg_cp
 */
template<class TType>
void PWROWG_NAMESPACE::type_erased_storage::reg_cp(void) noexcept {
    if (std::is_trivially_copyable_v<TType>) {
        // If the type is trivally copyable, we trivally copy the blob.
        this->_cp = [](blob& dst, const blob& src) {
            dst = src;
        };

    } else if (std::is_copy_constructible_v<TType>) {
        // Note: we always must copy *construct*, because we cannot know whether
        // 'dst' was the same type as 'src' before the operation.
        this->_cp = [](blob& dst, const blob& src) {
            dst.resize(src.size());
            new (dst.as<TType>()) TType(*src.as<TType>());
        };

    } else {
        this->_cp = nullptr;
    }
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::reg_cp_ctor
 */
template<class TType>
void PWROWG_NAMESPACE::type_erased_storage::reg_cp_ctor(void) noexcept {
    if (std::is_copy_constructible_v<TType>) {
        this->_cp_ctor = [](blob& dst, const blob& src) {
            assert(dst.empty());
            dst.resize(src.size());
            new (dst.as<TType>()) TType(*src.as<TType>());
        };

    } else {
        this->_cp_ctor = nullptr;
    }
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::reg_dtor
 */
template<class TType>
void PWROWG_NAMESPACE::type_erased_storage::reg_dtor(void) noexcept {
    this->_dtor = [](blob& obj) {
        obj.as<TType>()->~TType();
    };
}
