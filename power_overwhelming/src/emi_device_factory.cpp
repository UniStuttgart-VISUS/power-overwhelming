// <copyright file="emi_device_factory.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "emi_device_factory.h"


/*
 * visus::power_overwhelming::detail::emi_device_factory::create
 */
visus::power_overwhelming::detail::emi_device_factory::device_type
visus::power_overwhelming::detail::emi_device_factory::create(
        const string_type& path) {
    std::lock_guard<decltype(_lock)> _l(_lock);
    auto it = _instances.find(path);

    if (it == _instances.end()) {
#if defined(_WIN32)
        auto retval = std::make_shared<emi_device>(path);
#else /* defined(_WIN32) */
        auto retval = std::make_shared<emi_device>();
#endif /* defined(_WIN32) */
        _instances[path] = retval;
        return retval;

    } else {
        return it->second;
    }
}


/*
 * visus::power_overwhelming::detail::emi_device_factory::clear
 */
void visus::power_overwhelming::detail::emi_device_factory::clear(void) {
    std::lock_guard<decltype(_lock)> _l(_lock);
    _instances.clear();
}


/*
 * visus::power_overwhelming::detail::emi_device_factory::_instances
 */
std::unordered_map<
    visus::power_overwhelming::detail::emi_device_factory::string_type,
    visus::power_overwhelming::detail::emi_device_factory::device_type>
visus::power_overwhelming::detail::emi_device_factory::_instances;


/*
 * visus::power_overwhelming::detail::emi_device_factory::_lock
 */
std::mutex visus::power_overwhelming::detail::emi_device_factory::_lock;
