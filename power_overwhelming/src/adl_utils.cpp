// <copyright file="adl_utils.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#include "adl_utils.h"


/*
 * visus::power_overwhelming::detail::all_adapters
 */
std::vector<AdapterInfo> visus::power_overwhelming::detail::all_adapters(
        _In_ adl_scope& scope, _In_ const bool active_only) {
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

    if (active_only) {
        auto end = std::remove_if(retval.begin(), retval.end(),
                [&scope](const AdapterInfo& a) {
            int isActive = 0;
            auto status = detail::amd_display_library::instance()
                .ADL2_Adapter_Active_Get(scope, a.iAdapterIndex, &isActive);
            if (status != ADL_OK) {
                throw adl_exception(status);
            }
            return (isActive == 0);
        });
        retval.erase(end, retval.end());
    }

    return retval;
}


/*
 * visus::power_overwhelming::detail::supports_sensor
 */
bool visus::power_overwhelming::detail::supports_sensor(_In_ adl_scope& scope,
        _In_ const AdapterInfo& adapter, _In_ const int id) {
    ADLPMLogSupportInfo info;

    {
        auto status = detail::amd_display_library::instance()
            .ADL2_Adapter_PMLog_Support_Get(scope, adapter.iAdapterIndex,
                &info);
        if (status != ADL_OK) {
            throw adl_exception(status);
        }
    }

    return supports_sensor(info, id);
}
