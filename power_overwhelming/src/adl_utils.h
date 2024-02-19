// <copyright file="adl_utils.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#pragma once

#include <algorithm>
#include <cstdlib>
#include <iterator>

#include "adl_exception.h"
#include "adl_scope.h"
#include "adl_sensor_impl.h"
#include "zero_memory.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Answer all ADL adapters.
    /// </summary>
    /// <param name="scope">The scope holding the ADL function pointers.</param>
    /// <returns>The adapters found on the system.</returns>
    extern std::vector<AdapterInfo> get_adapters(_In_ adl_scope& scope);

    /// <summary>
    /// Gets all ADL adapters matching the given <paramref name="predicate" />
    /// using the specified output iterator.
    /// </summary>
    /// <typeparam name="TPredicate"></typeparam>
    /// <typeparam name="TIterator"></typeparam>
    /// <param name="oit"></param>
    /// <param name="scope"></param>
    /// <param name="predicate"></param>
    template<class TIterator, class TPredicate>
    inline void get_adapters_if(_In_ TIterator oit,
            _In_ adl_scope& scope,
            _In_ const TPredicate& predicate) {
        const auto adapters = get_adapters(scope);
        std::copy_if(adapters.begin(), adapters.end(), oit,
                [&scope, &predicate](const AdapterInfo& a) {
            return predicate(scope, a);
        });
        // Counting the elements copied would require C++ 20.
    }

    /// <summary>
    /// Gets all ADL adapters matching the given <paramref name="predicate" />.
    /// </summary>
    /// <typeparam name="TPredicate"></typeparam>
    /// <param name="scope"></param>
    /// <param name="predicate"></param>
    /// <returns></returns>
    template<class TPredicate>
    std::vector<AdapterInfo> get_adapters_if(_In_ adl_scope& scope,
        _In_ const TPredicate& predicate);

    /// <summary>
    /// Answer whether the given <paramref name="adapter" /> is active according
    /// to <see cref="ADL2_Adapter_Active_Get" />.
    /// </summary>
    /// <param name="scope"></param>
    /// <param name="adapter"></param>
    /// <returns></returns>
    extern bool is_active(_In_ adl_scope& scope,
        _In_ const AdapterInfo& adapter);

    /// <summary>
    /// Answer whether the given sensor <paramref name="id" /> is enabled in the
    /// given support <paramref name="info" />.
    /// </summary>
    /// <param name="info"></param>
    /// <param name="id"></param>
    /// <returns></returns>
    inline bool supports_sensor(_In_ const ADLPMLogSupportInfo& info,
            _In_ const int id) {
        const auto end = info.usSensors + ADL_PMLOG_MAX_SENSORS;
        const auto it = std::find(info.usSensors, end, id);
        return (it < end);
    }

    /// <summary>
    /// Answer whether the given sensor <paramref name="id" /> is supported by
    /// the given <paramref name="adapter" />.
    /// </summary>
    /// <param name="scope"></param>
    /// <param name="adapter"></param>
    /// <param name="id"></param>
    /// <returns></returns>
    extern bool supports_sensor(_In_ adl_scope& scope,
        _In_ const AdapterInfo& adapter,
        _In_ const int id);

    /// <summary>
    /// Answer wheher any of the sensor IDs within <paramref name="begin" /> and
    /// <paramref name="end" /> are supported by the given
    /// <paramref name="adapter" />.
    /// </summary>
    /// <typeparam name="TIterator"></typeparam>
    /// <param name="scope"></param>
    /// <param name="adapter"></param>
    /// <param name="begin"></param>
    /// <param name="end"></param>
    /// <returns></returns>
    template<class TIterator>
    bool supports_any_sensor(_In_ adl_scope& scope,
            _In_ const AdapterInfo& adapter,
            _In_ TIterator&& begin,
            _In_ TIterator&& end) {
        ADLPMLogSupportInfo info;

        {
            auto status = detail::amd_display_library::instance()
                .ADL2_Adapter_PMLog_Support_Get(scope, adapter.iAdapterIndex,
                    &info);
            if (status != ADL_OK) {
                throw adl_exception(status);
            }
        }

        return std::any_of(begin, end, [&info](const int id) {
            return supports_sensor(info, id);
        });
    }

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "adl_utils.inl"
