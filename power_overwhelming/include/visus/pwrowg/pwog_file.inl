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
