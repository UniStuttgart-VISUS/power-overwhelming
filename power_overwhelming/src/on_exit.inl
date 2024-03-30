// <copyright file="on_exit.inl" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2021 Visualisierungsinstitut der Universit�t Stuttgart.
// Licenced under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph M�ller</author>


/*
 * visus::power_overwhelming::detail::OnExitGuard<TExitHandler>::Invoke
 */
template<class TExitHandler>
void visus::power_overwhelming::detail::on_exit_guard<TExitHandler>::invoke(
        void) noexcept {
    if (*this) {
        this->_exitHandler();
        this->_isInvoked = true;
    }
}


/*
 * visus::power_overwhelming::detail::OnExitGuard<T>::operator =
 */
template<class TExitHandler>
visus::power_overwhelming::detail::on_exit_guard<TExitHandler>&
visus::power_overwhelming::detail::on_exit_guard<TExitHandler>::operator =(
        on_exit_guard&& rhs) {
    if (this != std::addressof(rhs)) {
        this->_exitHandler = std::move(rhs._exitHandler);
        this->_isInvoke = rhs._isInvoke;
        rhs._isInvoked = true;
    }

    return *this;
}
