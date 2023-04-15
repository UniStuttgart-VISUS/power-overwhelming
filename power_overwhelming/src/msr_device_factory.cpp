// <copyright file="msr_device_factory.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "msr_device_factory.h"


/*
 * visus::power_overwhelming::detail::msr_device_factory::create
 */
visus::power_overwhelming::detail::msr_device_factory::device_type
visus::power_overwhelming::detail::msr_device_factory::create(
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
 * visus::power_overwhelming::detail::msr_device_factory::create
 */
visus::power_overwhelming::detail::msr_device_factory::device_type
visus::power_overwhelming::detail::msr_device_factory::create(
        _In_ const core_type core) {
    return create(msr_device::path(core));
}


/*
 * visus::power_overwhelming::detail::msr_device_factory::clear
 */
void visus::power_overwhelming::detail::msr_device_factory::clear(void) {
    std::lock_guard<decltype(_lock)> _l(_lock);
    _instances.clear();
}


/*
 * visus::power_overwhelming::detail::msr_device_factory::_instances
 */
std::unordered_map<
    visus::power_overwhelming::detail::msr_device_factory::string_type,
    visus::power_overwhelming::detail::msr_device_factory::device_type>
visus::power_overwhelming::detail::msr_device_factory::_instances;


/*
 * visus::power_overwhelming::detail::msr_device_factory::_lock
 */
std::mutex visus::power_overwhelming::detail::msr_device_factory::_lock;
