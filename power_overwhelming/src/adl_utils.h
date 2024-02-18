// <copyright file="adl_utils.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#pragma once

#include <algorithm>
#include <cstdlib>

#include "adl_exception.h"
#include "adl_scope.h"
#include "adl_sensor_impl.h"
#include "zero_memory.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Answer all (active) ADL adapters.
    /// </summary>
    /// <param name="scope">The scope holding the ADL function pointers.</param>
    /// <param name="active_only">If <c>true</c>, inactive adapters are filtered
    /// from the result.</param>
    /// <returns>The adapters found on the system.</returns>
    extern std::vector<AdapterInfo> all_adapters(_In_ adl_scope& scope,
        _In_ const bool active_only);

    /// <summary>
    /// Answer all ADL adapter infos that match <paramref name="predicate" />.
    /// </summary>
    /// <typeparam name="TPredicate">A functor for checking a
    /// <see cref="AdapterInfo" />.</typeparam>
    /// <param name="predicate">The predicate the adapter must match in
    /// order to be returned.</param>
    /// <param name="active_only">If <c>true</c>, inactive adapters are filtered
    /// from the result.</param>
    /// <returns>The adapters matching the predicate.</returns>
    template<class TPredicate>
    std::vector<AdapterInfo> matching_adapters(_In_ adl_scope& scope,
            _In_ const TPredicate& predicate, _In_ const bool active_only) {
        auto retval = all_adapters(scope, active_only);
        auto end = std::remove_if(retval.begin(), retval.end(),
            [&predicate](AdapterInfo &a) { return !predicate(a); });
        retval.erase(end, retval.end());
        return retval;
    }

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

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
