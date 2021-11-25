// <copyright file="adl_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "adl_sensor_impl.h"

#include "adl_exception.h"
#include "convert_string.h"


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::get_sensor_ids
 */
std::vector<int>
visus::power_overwhelming::detail::adl_sensor_impl::get_sensor_ids(
        const adl_sensor_source source) {
    switch (source) {
        case adl_sensor_source::asic:
            return std::vector<int> { ADL_PMLOG_ASIC_POWER };

        case adl_sensor_source::cpu:
            return std::vector<int> { ADL_PMLOG_CPU_POWER };

        case adl_sensor_source::graphics:
            return std::vector<int> { ADL_PMLOG_GFX_VOLTAGE,
                ADL_PMLOG_GFX_CURRENT, ADL_PMLOG_GFX_POWER };

        case adl_sensor_source::soc:
            return std::vector<int> { ADL_PMLOG_SOC_VOLTAGE, 
                ADL_PMLOG_SOC_CURRENT, ADL_PMLOG_SOC_POWER };

        default:
            return std::vector<int>();
    };
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::get_sensor_ids
 */
std::vector<int>
visus::power_overwhelming::detail::adl_sensor_impl::get_sensor_ids(
        const adl_sensor_source source,
        const ADLPMLogSupportInfo& supportInfo) {
    auto required = get_sensor_ids(source);

    if (required.empty()) {
        // Sensor is not known, so it is not supported.
        return required;
    }

    std::vector<int> retval;
    retval.reserve(required.size());

    for (int i = 0; supportInfo.usSensors[i] != ADL_SENSOR_MAXTYPES; ++i) {
        auto it = std::find(required.begin(), required.end(),
            supportInfo.usSensors[i]);
        if (it != required.end()) {
            retval.push_back(*it);
            required.erase(it);
        }
    }

    return retval;
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::adl_sensor_impl
 */
visus::power_overwhelming::detail::adl_sensor_impl::adl_sensor_impl(void)
    : adapter_index(0), device(0), start_input({ 0 }),
    start_output({ 0 }) { }


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::adl_sensor_impl
 */
visus::power_overwhelming::detail::adl_sensor_impl::adl_sensor_impl(
        const AdapterInfo& adapterInfo)
    : adapter_index(adapterInfo.iAdapterIndex), device(0), start_input({ 0 }),
        start_output({ 0 }) {
    auto status = detail::amd_display_library::instance()
        .ADL2_Device_PMLog_Device_Create(this->scope, this->adapter_index,
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
            this->scope, this->device);
    }
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::configure_source
 */
void visus::power_overwhelming::detail::adl_sensor_impl::configure_source(
        const adl_sensor_source source, std::vector<int>&& sensorIDs) {

    // Determine which sensors are supported if not provided by the caller.
    if (sensorIDs.empty()) {
        ADLPMLogSupportInfo supportInfo;
        auto status = amd_display_library::instance()
            .ADL2_Adapter_PMLog_Support_Get(this->scope, this->adapter_index,
            &supportInfo);
        if (status != ADL_OK) {
            throw adl_exception(status);
        }

        sensorIDs = get_sensor_ids(source, supportInfo);
    }

    // Set the sensor name.
    switch (source) {
        case adl_sensor_source::asic:
            this->sensor_name = L"ADL/ASIC/" + this->device_name
                + L"/" + std::to_wstring(this->adapter_index);
            break;

        case adl_sensor_source::cpu:
            this->sensor_name = L"ADL/CPU/" + this->device_name
                + L"/" + std::to_wstring(this->adapter_index);
            break;

        case adl_sensor_source::graphics:
            this->sensor_name = L"ADL/GFX/" + this->device_name
                + L"/" + std::to_wstring(this->adapter_index);
            break;

        case adl_sensor_source::soc:
            this->sensor_name = L"ADL/SOC/" + this->device_name
                + L"/" + std::to_wstring(this->adapter_index);
            break;

        default:
            throw std::invalid_argument("The specified sensor source is "
                "unsupported.");
    }

    // ADL_SENSOR_MAXTYPES, which is the guard for invalid sensors, is zero.
    ::ZeroMemory(this->start_input.usSensors,
        sizeof(this->start_input.usSensors));

    for (std::size_t i = 0; i < sensorIDs.size(); ++i) {
        this->start_input.usSensors[i] = sensorIDs[i];
    }
}
