// <copyright file="convert_string.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::convert_string
 */
template<class TOutput, class TInput>
typename std::enable_if<std::is_same<TOutput, TInput>::value,
    std::basic_string<TOutput>>::type
visus::power_overwhelming::convert_string(_In_opt_z_ const TInput *str) {
    return (str != nullptr) ? str : std::basic_string<TOutput>();
}


/*
 * visus::power_overwhelming::convert_string
 */
template<class TOutput, class TInput>
typename std::enable_if<!std::is_same<TOutput, TInput>::value,
    std::basic_string<TOutput>>::type
visus::power_overwhelming::convert_string(_In_opt_z_ const TInput *str) {
    std::vector<TOutput> retval;

    if (str != nullptr) {
        auto len = std::char_traits<TInput>::length(str);
        const std::size_t zero = 0;

        retval.resize(detail::convert_string(nullptr, zero, str, len));
        detail::convert_string(retval.data(), retval.size(), str, len);
    }

    retval.emplace_back(0); // Make sure that result is always terminated.
    return retval.data();
}
