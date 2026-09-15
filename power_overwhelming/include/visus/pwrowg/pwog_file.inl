// <copyright file="pwog_file.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::pwog_file::write
 */
template<class TChar>
PWROWG_NAMESPACE::pwog_file& PWROWG_NAMESPACE::pwog_file::write(
        _In_ const pwog_meta_data<TChar>& meta_data) {
    if (this->_state != state::meta_data) {
        throw std::logic_error("The file is not in the state to receive meta "
            "data.");
    }

    this->write(meta_data.key());
    this->write(meta_data.value());

    return *this;
}


/*
 * PWROWG_NAMESPACE::pwog_file::swap
 */
template<class TType>
void PWROWG_NAMESPACE::pwog_file::swap(_Inout_ TType& value) const noexcept {
    if (this->_swap) {
        auto bytes = reinterpret_cast<std::uint8_t *>(std::addressof(value));
        std::reverse(bytes, bytes + sizeof(value));
    }
}


/*
 * PWROWG_NAMESPACE::pwog_file::swap
 */
template<std::size_t N> void PWROWG_NAMESPACE::pwog_file::swap(
        _Inout_ std::uint8_t(&value)[N]) const noexcept {
    if (this->_swap) {
        std::reverse(std::begin(value), std::end(value));
    }
}
