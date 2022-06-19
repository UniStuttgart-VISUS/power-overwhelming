// <copyright file="convert_string.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::convert_string
 */
template<class TOutput, class TInput>
typename std::enable_if<std::is_same<TOutput, TInput>::value,
    std::basic_string<TOutput>>::type
visus::power_overwhelming::convert_string(const TInput *str) {
    return (str != nullptr) ? str : std::basic_string<TOutput>();
}


/*
 * visus::power_overwhelming::convert_string
 */
template<class TOutput, class TInput>
typename std::enable_if<!std::is_same<TOutput, TInput>::value,
    std::basic_string<TOutput>>::type
visus::power_overwhelming::convert_string(const TInput *str) {
    std::vector<TOutput> retval;

    if (str != nullptr) {
        auto len = std::char_traits<TInput>::length(str);
        const std::size_t zero = 0;

        retval.resize(detail::convert_string(nullptr, zero, str, len));
        detail::convert_string(retval.data(), retval.size(), str, len);
    }

    return retval.data();
}
