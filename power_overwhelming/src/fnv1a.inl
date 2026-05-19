// <copyright file="fnv1a.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::fnv1a::operator ()
 */
template<class TResult>
template<class TIterator>
void PWROWG_DETAIL_NAMESPACE::fnv1a<TResult>::operator ()(
        _In_ const TIterator begin,
        _In_ const TIterator end) noexcept {
    typedef typename std::iterator_traits<TIterator>::value_type byte_type;
    static_assert(sizeof(byte_type) == 1, "The input iterator must iterate "
        "over single bytes.");
    // Cf. https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
    for (auto it = begin; it < end; ++it) {
        this->_value = (this->_value ^ *it) * _traits::magic_prime;
    }
}
