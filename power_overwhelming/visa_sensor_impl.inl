// <copyright file="visa_sensor_impl.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::printf
 */
template<class ...TArgs>
void visus::power_overwhelming::detail::visa_sensor_impl::printf(
        ViConstString format, TArgs&&... args) {
    visa_exception::throw_on_error(detail::visa_library::instance()
        .viPrintf(this->scope, format, std::forward<TArgs>(args)...));
}
