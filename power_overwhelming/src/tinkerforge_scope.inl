// <copyright file="tinkerforge_scope.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::copy_bricklets
 */
template<class TIterator, class TPredicate>
std::size_t PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::copy_bricklets(
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


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::copy_bricklets
 */
template<class TIterator, class TPredicate>
std::size_t PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::copy_bricklets(
            TIterator oit, const TPredicate& predicate,
            const std::chrono::milliseconds timeout,
            const std::size_t expected) const {
    const auto deadline = std::chrono::system_clock::now() + timeout;
    std::size_t retval = 0;

    while (std::chrono::system_clock::now() < deadline) {
        retval = this->copy_bricklets(oit, predicate);

        // Determine whether the bricklets are already known. If not, we
        // repeat this step every 100 ms until the bricklets have been
        // discovered or the timeout was reached. See also
        // https://www.tinkerunity.org/topic/5661-tipps-f%C3%BCr-l%C3%B6sung-eines-kniffligen-problems/#comment-30618
        if ((retval == 0) || ((expected > 0) && (retval < expected))) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } else {
            break;
        }
    }

    return retval;
}
