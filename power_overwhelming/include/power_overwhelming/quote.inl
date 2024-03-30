// <copyright file="quote.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart.
// Licenced under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::quote
 */
template<class TChar>
std::basic_string<TChar> visus::power_overwhelming::quote(
        _In_opt_z_ const TChar *str, _In_ const TChar quote) {
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
