// <copyright file="adl_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "adl_sensor_impl.h"

#include "adl_exception.h"
#include "convert_string.h"


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::adl_sensor_impl
 */
visus::power_overwhelming::detail::adl_sensor_impl::adl_sensor_impl(void)
        : adapter_index(0), context(nullptr), device(0), start_input({ 0 }),
        start_output({ 0 }) { }


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::adl_sensor_impl
 */
visus::power_overwhelming::detail::adl_sensor_impl::adl_sensor_impl(
        const AdapterInfo& adapterInfo) : adapter_index(0), context(nullptr),
        device(0), start_input({ 0 }), start_output({ 0 }) {
    auto status = detail::amd_display_library::instance()
        .ADL2_Device_PMLog_Device_Create(nullptr, adapterInfo.iAdapterIndex,
        &this->device);
    if (status != ADL_OK) {
        throw adl_exception(status);
    }

    this->device_name = convert_string(adapterInfo.strAdapterName);
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::~adl_sensor_impl
 */
visus::power_overwhelming::detail::adl_sensor_impl::~adl_sensor_impl(void) {
    if (this->device != 0) {
        // Note: AMD's sample uses zero as guard as well, so we assume this is
        // safe to do.
        amd_display_library::instance().ADL2_Device_PMLog_Device_Destroy(
            this->context, this->device);
    }
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::configure_source
 */
void visus::power_overwhelming::detail::adl_sensor_impl::configure_source(
        const adl_sensor_source source, const unsigned long sampleRate) {
    ADLPMLogSupportInfo support;

    // Determine which sensors are supported.
    {
        auto status = amd_display_library::instance()
            .ADL2_Adapter_PMLog_Support_Get(this->context, this->adapter_index,
            &support);
        if (status != ADL_OK) {
            throw adl_exception(status);
        }
    }

    // ADL_SENSOR_MAXTYPES, which is the guard for invalid sensors, is zero.
    ::ZeroMemory(this->start_input.usSensors,
        sizeof(this->start_input.usSensors));

    switch (source) {
        case adl_sensor_source::asic:
            this->sensor_name = L"ADL/ASIC/" + this->device_name;
            break;

        case adl_sensor_source::cpu:
            this->sensor_name = L"ADL/CPU/" + this->device_name;
            break;

        case adl_sensor_source::graphics:
            this->sensor_name = L"ADL/GFX/" + this->device_name;
            break;

        case adl_sensor_source::soc:
            this->sensor_name = L"ADL/SOC/" + this->device_name;
            break;

        default:
            throw std::invalid_argument("The specified sensor source is "
                "unsupported.");
    }

    //this->sensor_name = L"ADL/" + this->device_name + L"/"
    //    + convert_string(adapterInfo.strDisplayName);

    //ADL_PMLOG_SOC_VOLTAGE = 16,
    //    ADL_PMLOG_SOC_POWER = 17,
    //    ADL_PMLOG_SOC_CURRENT
    // ADL_PMLOG_GFX_VOLTAGE
    // ADL_PMLOG_GFX_POWER
    // ADL_PMLOG_GFX_CURRENT
    // ADL_PMLOG_ASIC_POWER
    // ADL_PMLOG_CPU_POWER

    ADL_SENSOR_MAXTYPES
    //while (this->supported_sensors.usSensors[i] != ADL_SENSOR_MAXTYPES)
    //{
    //    adlPMLogStartInput.usSensors[i] = adlPMLogSupportInfo.usSensors[i];
    //    i++;
    //}
}
