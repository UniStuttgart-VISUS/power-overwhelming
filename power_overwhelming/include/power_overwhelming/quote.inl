// <copyright file="quote.inl" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2022 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>


/*
 * visus::power_overwhelming::quote
 */
template<class TChar>
std::basic_string<TChar> visus::power_overwhelming::quote(const TChar *str,
        const TChar quote) {
    std::basic_string<TChar> retval;

    if (str != nullptr) {
        retval.reserve(2 + decltype(retval)::traits_type::length(str));
        retval += quote;
        retval += str;
        retval += quote;

    } else {
        retval.reserve(2);
        retval += quote;
        retval += quote;
    }

    return retval;
}
