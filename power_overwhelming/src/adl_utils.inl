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
    int isActive = 0;
    std::vector<AdapterInfo> retval;

    {
        int cnt;
        auto status = detail::amd_display_library::instance()
            .ADL2_Adapter_NumberOfAdapters_Get(scope, &cnt);
        if (status != ADL_OK) {
            throw adl_exception(status);
        }

        retval.resize(cnt);
    }

    {
        const auto size = static_cast<int>(retval.size() * sizeof(AdapterInfo));
        ::ZeroMemory(retval.data(), size);

        auto status = detail::amd_display_library::instance()
            .ADL2_Adapter_AdapterInfo_Get(scope, retval.data(), size);
        if (status != ADL_OK) {
            throw adl_exception(status);
        }
    }

    for (auto it = retval.begin(); it != retval.end(); ++it) {
        if (!predicate(scope, *it)) {
            it = retval.erase(it);
            continue;
        }
    }

    return retval;
}
