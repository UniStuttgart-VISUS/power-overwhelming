﻿// <copyright file="blob.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::blob::blob
 */
template<class TElement>
PWROWG_NAMESPACE::blob::blob(_In_ const std::initializer_list<TElement>& data)
        : _data(nullptr), _size(data.size() * sizeof(TElement)) {
    if (this->_size > 0) {
        this->_data = new byte_type[this->_size];
        auto d = reinterpret_cast<TElement *>(this->_data);
        std::copy(data.begin(), data.end(), d);
    }
}
