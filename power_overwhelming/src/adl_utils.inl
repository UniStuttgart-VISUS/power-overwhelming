// <copyright file="adl_utils.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>


/*
 * visus::power_overwhelming::detail::get_adapters_if
 */
template<class TPredicate>
std::vector<AdapterInfo>
visus::power_overwhelming::detail::get_adapters_if(_In_ adl_scope& scope,
        _In_ const TPredicate& predicate) {
    auto retval = get_adapters(scope);

    // In-place filter out the adapters the caller does not want.
    auto end = std::remove_if(retval.begin(), retval.end(),
            [&scope, &predicate](const AdapterInfo& a) {
        return !predicate(scope, a);
    });
    retval.erase(end, retval.end());

    return retval;
}
