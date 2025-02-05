// <copyright file="sensor_utilities.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::move_front_if
 */
template<class TIterator, class TPredicate>
TIterator PWROWG_DETAIL_NAMESPACE::move_front_if(const _In_ TIterator begin,
        const _In_ TIterator end, const _In_ TPredicate predicate) {
    auto retval = begin;

    for (auto it = begin; it != end; ++it) {
        if (predicate(*it)) {
            while ((retval != it) && predicate(*retval)) {
                ++retval;
            }

            if (retval != it) {
                std::swap(*it, *retval);
            }

            ++retval;
        }
    }

    return retval;
}
