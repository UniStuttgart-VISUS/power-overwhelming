// <copyright file="tinkerforge_scope.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::detail::tinkerforge_scope::copy_bricklets
 */
template<class TIterator, class TPredicate>
std::size_t visus::power_overwhelming::detail::tinkerforge_scope::copy_bricklets(
        TIterator oit, const TPredicate& predicate) const {
    std::size_t retval = 0;

    std::lock_guard<decltype(this->_scope->lock_bricklets)> l(
        this->_scope->lock_bricklets);
    for (auto& b : this->_scope->bricklets) {
        if (predicate(b.second)) {
            *oit++ = b.second;
            ++retval;
        }
    }

    return retval;
}
