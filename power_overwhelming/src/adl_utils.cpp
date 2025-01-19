// <copyright file="adl_utils.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#include "adl_utils.h"

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
        if (status != ADL_OK) {
            throw adl_exception(status);
        }

        retval.resize(cnt);
    }

    {
        const auto size = static_cast<int>(retval.size() * sizeof(AdapterInfo));
        ::ZeroMemory(retval.data(), size);

        auto status = PWROWG_DETAIL_NAMESPACE::amd_display_library::instance()
            .ADL2_Adapter_AdapterInfo_Get(scope, retval.data(), size);
        if (status != ADL_OK) {
            throw adl_exception(status);
        }
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
    if (status != ADL_OK) {
        throw adl_exception(status);
    }
    return (retval == 0);
}


/*
 * PWROWG_DETAIL_NAMESPACE::supports_sensor
 */
bool PWROWG_DETAIL_NAMESPACE::supports_sensor(
        _In_ adl_scope& scope,
        _In_ const AdapterInfo& adapter,
        _In_ const int id) {
    ADLPMLogSupportInfo info;

    {
        auto status = PWROWG_DETAIL_NAMESPACE::amd_display_library::instance()
            .ADL2_Adapter_PMLog_Support_Get(scope, adapter.iAdapterIndex,
                &info);
        if (status != ADL_OK) {
            throw adl_exception(status);
        }
    }

    return supports_sensor(info, id);
}
