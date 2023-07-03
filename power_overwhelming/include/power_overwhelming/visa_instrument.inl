// <copyright file="visa_instrument_impl.inl" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2021 - 2023 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>


/*
 * visus::power_overwhelming::visa_instrument::write
 */
template<class TChar>
const visus::power_overwhelming::visa_instrument&
visus::power_overwhelming::visa_instrument::write(
        _In_ const std::basic_string<TChar>& str) const {
    return this->write(str.c_str());
}
