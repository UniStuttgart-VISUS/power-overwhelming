// <copyright file="tokenise.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licenced under the MIT License. See LICENCE.txt for further details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::tokenise_range_if
 */
template<class TChar, class TPredicate>
std::vector<std::basic_string<TChar>>
PWROWG_DETAIL_NAMESPACE::tokenise_range_if(
        _In_opt_ const TChar *begin,
        _In_opt_ const TChar *end,
        _In_ const TPredicate predicate,
        _In_ const bool omit_empty) {
    auto is_end = [end](const TChar *c) {
        return (((end != nullptr) && (c >= end)) || (*c == 0));
    };

    std::vector<std::basic_string<TChar>> retval;

    if (begin != nullptr) {
        auto cur = begin;

        while (!is_end(cur)) {
            auto b = cur;

            while (!is_end(cur) && !predicate(*cur)) {
                ++cur;
            }

            if (!omit_empty || ((cur - b) > 0)) {
                retval.emplace_back(b, cur);
            }

            ++cur;
        }
    }

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
