// <copyright file="tinkerforge_scope.inl" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2021 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>


/*
 * visus::power_overwhelming::detail::tinkerforge_scope::copy_bricklets
 */
template<class TIterator>
std::size_t visus::power_overwhelming::detail::tinkerforge_scope::copy_bricklets(
        TIterator oit) const {
    std::size_t retval = 0;

    std::lock_guard<decltype(this->_scope->lock_bricklets)> l(
        this->_scope->lock_bricklets);
    for (auto& b : this->_scope->bricklets) {
        *oit++ = b.second;
        ++retval;
    }

    return retval;
}
