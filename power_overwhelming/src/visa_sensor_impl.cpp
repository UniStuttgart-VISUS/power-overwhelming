// <copyright file="visa_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "visa_sensor_impl.h"

#include <algorithm>


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::visa_sensor_impl
 */
visus::power_overwhelming::detail::visa_sensor_impl::visa_sensor_impl(
        _In_z_ const char *path, _In_ const std::int32_t timeout)
        : instrument(path, timeout) {
    this->instrument.clear();
}


/*
 * visus::power_overwhelming::detail::visa_sensor_impl::visa_sensor_impl
 */
visus::power_overwhelming::detail::visa_sensor_impl::visa_sensor_impl(
        _In_z_ const wchar_t *path, _In_ const std::int32_t timeout)
        : instrument(path, timeout) {
    this->instrument.clear();
}
