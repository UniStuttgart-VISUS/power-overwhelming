// <copyright file="pwog_meta_data.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::pwog_meta_data<TChar>::pwog_meta_data
 */
template<class TChar>
PWROWG_NAMESPACE::pwog_meta_data<TChar>::pwog_meta_data(
        _In_z_ const char_type *key,
        _In_z_ const char_type *value)
        : _key(key), _value(value) {
    if (detail::empty(this->_key)) {
        throw std::invalid_argument("A non-empty key must be specified.");
    }

}
