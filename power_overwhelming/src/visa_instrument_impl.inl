// <copyright file="visa_instrument_impl.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::detail::visa_instrument_impl::write
 */
template<class ...TArgs>
void visus::power_overwhelming::detail::visa_instrument_impl::write(
        _In_z_ const char *format, TArgs&&... args) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viPrintf(this->session, format, std::forward<TArgs>(args)...));
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}
