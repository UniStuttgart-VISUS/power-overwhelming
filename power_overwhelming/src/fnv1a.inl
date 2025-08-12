// <copyright file="fnv1a.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::fnv1a::operator ()
 */
template<class TIterator>
void PWROWG_DETAIL_NAMESPACE::fnv1a<std::uint32_t>::operator ()(
        _In_ const TIterator begin,
        _In_ const TIterator end) noexcept {
    typedef typename std::iterator_traits<TIterator>::value_type byte_type;
    static_assert(sizeof(byte_type) == 1, "The input iterator must iterate "
        "over single bytes.");
    // Cf. https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
    constexpr result_type magic_prime = 0x01000193;

    for (auto it = begin; it < end; ++it) {
        this->_value = (this->_value ^ *it) * magic_prime;
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::fnv1a::operator ()
 */
template<class TIterator>
void PWROWG_DETAIL_NAMESPACE::fnv1a<std::uint64_t>::operator ()(
        _In_ const TIterator begin,
        _In_ const TIterator end) noexcept {
    typedef typename std::iterator_traits<TIterator>::value_type byte_type;
    static_assert(sizeof(byte_type) == 1, "The input iterator must iterate "
        "over single bytes.");
https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
    constexpr result_type magic_prime = 0x00000100000001b3;

    for (auto it = begin; it < end; ++it) {
        this->_value = (this->_value ^ *it) * magic_prime;
    }
}
