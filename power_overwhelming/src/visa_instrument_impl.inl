// <copyright file="visa_instrument_impl.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::format
 */
template<class ...TArgs>
void PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::format(
        _In_z_ const char *format, TArgs&&... args) const {
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viPrintf(this->session, format, std::forward<TArgs>(args)...));
    this->check_system_error();
}
