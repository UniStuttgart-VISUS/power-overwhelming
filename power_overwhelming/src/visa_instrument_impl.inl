// <copyright file="visa_instrument_impl.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::foreach
 */
template<class TCallback>
std::size_t PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::foreach(
        _In_ const TCallback& callback) {
    std::size_t retval = 0;

    std::lock_guard<decltype(_lock_instruments)> l(_lock_instruments);
    for (auto& i : _instruments) {
        ++retval;
        if (!callback(i.second)) {
            break;
        }
    }

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::format
 */
template<class ...TArgs>
void PWROWG_DETAIL_NAMESPACE::visa_instrument_impl::format(
        _In_z_ const char *format, TArgs&&... args) const {
    throw_if_visa_failed(detail::visa_library::instance()
        ._viPrintf(this->session, const_cast<char *>(format),
            std::forward<TArgs>(args)...));
    this->check_system_error();
}
