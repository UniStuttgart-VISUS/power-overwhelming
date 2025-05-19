// <copyright file="adl_utils.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#if defined(POWER_OVERWHELMING_WITH_ADL)
#include "adl_utils.h"

#include "adl_error_category.h"
#include "amd_display_library.h"


/*
 * PWROWG_DETAIL_NAMESPACE::get_adapters
 */
std::vector<AdapterInfo> PWROWG_DETAIL_NAMESPACE::get_adapters(
        _In_ adl_scope& scope) {
    std::vector<AdapterInfo> retval;

    {
        int cnt;
        auto status = PWROWG_DETAIL_NAMESPACE::amd_display_library::instance()
            .ADL2_Adapter_NumberOfAdapters_Get(scope, &cnt);
        throw_if_adl_failed(status);
        retval.resize(cnt);
    }

    {
        const auto size = static_cast<int>(retval.size() * sizeof(AdapterInfo));
        ::ZeroMemory(retval.data(), size);

        auto status = PWROWG_DETAIL_NAMESPACE::amd_display_library::instance()
            .ADL2_Adapter_AdapterInfo_Get(scope, retval.data(), size);
        throw_if_adl_failed(status);
    }

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::is_active
 */
bool PWROWG_DETAIL_NAMESPACE::is_active(_In_ adl_scope& scope,
        _In_ const AdapterInfo& adapter) {
    int retval = 0;
    auto status = PWROWG_DETAIL_NAMESPACE::amd_display_library::instance()
        .ADL2_Adapter_Active_Get(scope, adapter.iAdapterIndex, &retval);
    throw_if_adl_failed(status);
    return (retval == 0);
}

#endif /* defined(POWER_OVERWHELMING_WITH_ADL) */
