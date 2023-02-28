// <copyright file="emi_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include <initguid.h> // [sic]
#include "emi_sensor_impl.h"


#if 0
/*
 * visus::power_overwhelming::detail::emi_sensor_impl::sampler
 */
visus::power_overwhelming::detail::sampler<
    visus::power_overwhelming::detail::default_sampler_context<
    visus::power_overwhelming::detail::emi_sensor_impl>>
visus::power_overwhelming::detail::emi_sensor_impl::sampler;
#endif

/*
 * visus::power_overwhelming::detail::emi_sensor_impl::~emi_sensor_impl
 */
visus::power_overwhelming::detail::emi_sensor_impl::~emi_sensor_impl(void) {
}


/*c
 * visus::power_overwhelming::detail::emi_sensor_impl::sample
 */
visus::power_overwhelming::measurement
visus::power_overwhelming::detail::emi_sensor_impl::sample(
        const timestamp_resolution resolution) const {
    throw "TODO";
}
