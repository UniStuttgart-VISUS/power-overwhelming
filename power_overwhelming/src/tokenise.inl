﻿// <copyright file="tokenise.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licenced under the MIT License. See LICENCE.txt for further details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::tokenise_if
 */
template<class C, class P>
std::vector<std::basic_string<C>> PWROWG_DETAIL_NAMESPACE::tokenise_if(
        const std::basic_string<C>& str, const P predicate,
        const bool omitEmpty) {
    typedef typename std::decay<decltype(str)>::type StringType;

    auto s = str.data();
    std::vector<StringType> retval;

    do {
        auto begin = s;

        while ((*s != 0) && !predicate(*s)) {
            ++s;
        }

        if (!omitEmpty || ((s - begin) > 0)) {
            retval.emplace_back(begin, s);
        }
    } while (*s++ != 0);

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::tokenise
 */
template<class C>
std::vector<std::basic_string<C>> PWROWG_DETAIL_NAMESPACE::tokenise(
        const std::basic_string<C>& str, const std::basic_string<C>& delim,
        const bool omitEmpty) {
    typedef typename std::decay<decltype(str)>::type StringType;

    std::vector<StringType> retval;

    auto cur = static_cast<typename StringType::size_type>(0);
    while (cur != StringType::npos) {
        auto next = str.find(delim, cur);
        if (!omitEmpty || (cur != next)) {
            retval.emplace_back(str.substr(cur, next - cur));
        }
        if (next != StringType::npos) {
            next += delim.size();
        }
        cur = next;
    }

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::tokenise
 */
template<class C>
std::vector<std::basic_string<C>> PWROWG_DETAIL_NAMESPACE::tokenise(
        const std::basic_string<C>& str, const C *delim, const bool omitEmpty) {
    if (delim != nullptr) {
        return tokenise(str, std::basic_string<C>(delim), omitEmpty);
    } else {
        return { str };
    }
}
