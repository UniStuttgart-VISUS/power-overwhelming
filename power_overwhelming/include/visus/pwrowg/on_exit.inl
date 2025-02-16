// <copyright file="on_exit.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::OnExitGuard<TExitHandler>::Invoke
 */
template<class TExitHandler>
void PWROWG_DETAIL_NAMESPACE::on_exit_guard<TExitHandler>::invoke(
        void) noexcept {
    if (*this) {
        this->_exitHandler();
        this->_isInvoked = true;
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::OnExitGuard<T>::operator =
 */
template<class TExitHandler>
PWROWG_DETAIL_NAMESPACE::on_exit_guard<TExitHandler>&
PWROWG_DETAIL_NAMESPACE::on_exit_guard<TExitHandler>::operator =(
        on_exit_guard&& rhs) {
    if (this != std::addressof(rhs)) {
        this->_exitHandler = std::move(rhs._exitHandler);
        this->_isInvoke = rhs._isInvoke;
        rhs._isInvoked = true;
    }

    return *this;
}
