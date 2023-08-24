// <copyright file="rtx_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "rtx_sensor_impl.h"

#include "rtx_sampler.h"


/*
 * visus::power_overwhelming::detail::rtx_sensor_impl::~rtx_sensor_impl
 */
visus::power_overwhelming::detail::rtx_sensor_impl::~rtx_sensor_impl(void) {
    rtx_sampler::default.remove(this);
}
