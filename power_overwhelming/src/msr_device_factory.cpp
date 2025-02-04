// <copyright file="msr_device_factory.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "msr_device_factory.h"


/*
 * PWROWG_DETAIL_NAMESPACE::msr_device_factory::create
 */
PWROWG_DETAIL_NAMESPACE::msr_device_factory::device_type
PWROWG_DETAIL_NAMESPACE::msr_device_factory::create(
        _In_ const string_type& path) {
    std::lock_guard<decltype(_lock)> _l(_lock);
    auto it = _instances.find(path);

    if (it == _instances.end()) {
        auto retval = std::make_shared<msr_device>(path);
        _instances[path] = retval;
        return retval;

    } else {
        return it->second;
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::msr_device_factory::create
 */
PWROWG_DETAIL_NAMESPACE::msr_device_factory::device_type
PWROWG_DETAIL_NAMESPACE::msr_device_factory::create(
        _In_ const core_type core) {
    return create(msr_device::path(core));
}


/*
 * PWROWG_DETAIL_NAMESPACE::msr_device_factory::clear
 */
void PWROWG_DETAIL_NAMESPACE::msr_device_factory::clear(void) {
    std::lock_guard<decltype(_lock)> _l(_lock);
    _instances.clear();
}


/*
 * PWROWG_DETAIL_NAMESPACE::msr_device_factory::_instances
 */
std::unordered_map<
    PWROWG_DETAIL_NAMESPACE::msr_device_factory::string_type,
    PWROWG_DETAIL_NAMESPACE::msr_device_factory::device_type>
PWROWG_DETAIL_NAMESPACE::msr_device_factory::_instances;


/*
 * PWROWG_DETAIL_NAMESPACE::msr_device_factory::_lock
 */
std::mutex PWROWG_DETAIL_NAMESPACE::msr_device_factory::_lock;
