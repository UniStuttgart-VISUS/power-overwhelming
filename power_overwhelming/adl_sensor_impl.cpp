// <copyright file="adl_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "adl_sensor_impl.h"

#include "adl_exception.h"
#include "convert_string.h"


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::count_sensor_readings
 */
std::size_t
visus::power_overwhelming::detail::adl_sensor_impl::count_sensor_readings(
        const ADLPMLogData& data) {
    std::size_t retval = 0;

    for (; (retval < ADL_PMLOG_MAX_SENSORS)
        && (data.ulValues[retval][0] != ADL_SENSOR_MAXTYPES); ++retval);

    return retval;
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::get_sensor_ids
 */
std::vector<ADL_PMLOG_SENSORS>
visus::power_overwhelming::detail::adl_sensor_impl::get_sensor_ids(
        const adl_sensor_source source) {
    switch (source) {
        case adl_sensor_source::asic:
            return std::vector<ADL_PMLOG_SENSORS> { ADL_PMLOG_ASIC_POWER };

        case adl_sensor_source::cpu:
            return std::vector<ADL_PMLOG_SENSORS> { ADL_PMLOG_CPU_POWER };

        case adl_sensor_source::graphics:
            return std::vector<ADL_PMLOG_SENSORS> { ADL_PMLOG_GFX_VOLTAGE,
                ADL_PMLOG_GFX_CURRENT, ADL_PMLOG_GFX_POWER };

        case adl_sensor_source::soc:
            return std::vector<ADL_PMLOG_SENSORS> { ADL_PMLOG_SOC_VOLTAGE,
                ADL_PMLOG_SOC_CURRENT, ADL_PMLOG_SOC_POWER };

        default:
            return std::vector<ADL_PMLOG_SENSORS>();
    };
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::get_sensor_ids
 */
std::vector<ADL_PMLOG_SENSORS>
visus::power_overwhelming::detail::adl_sensor_impl::get_sensor_ids(
        const adl_sensor_source source,
        const ADLPMLogSupportInfo& supportInfo) {
    auto retval = get_sensor_ids(source);

    {
        auto end = std::remove_if(retval.begin(), retval.end(),
            [&supportInfo](const int id) {
                auto found = std::find(supportInfo.usSensors,
                    supportInfo.usSensors + ADL_PMLOG_MAX_SENSORS, id);
                return (found == supportInfo.usSensors + ADL_PMLOG_MAX_SENSORS);
            });
        retval.erase(end, retval.end());
    }

    if ((retval.size() == 1) && !is_power(retval.front())) {
        // If there is only one sensor, it must be a power sensor. Having either
        // voltage or current is useless, so we do not report this.
        retval.clear();

    } else if (retval.size() == 2) {
        // If we have two sensors, it must be voltage and current as we can
        // compute the power from both. Alternatively, if one of the sensors
        // is a power sensor, remove all except this one.
        auto haveCurrent = is_current(retval[0]) || is_current(retval[1]);
        auto haveVoltage = is_voltage(retval[0]) || is_voltage(retval[1]);

        if (!haveCurrent || !haveVoltage) {
            auto end = std::remove_if(retval.begin(), retval.end(),
                [](const ADL_PMLOG_SENSORS id) { return !is_power(id); });
            retval.erase(end, retval.end());
        }
    }

    return retval;
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::is_current
 */
bool visus::power_overwhelming::detail::adl_sensor_impl::is_current(
        const ADL_PMLOG_SENSORS id) {
    switch (id) {
        case ADL_PMLOG_GFX_CURRENT:
        case ADL_PMLOG_SOC_CURRENT:
            return true;

        default:
            return false;
    }
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::is_power
 */
bool visus::power_overwhelming::detail::adl_sensor_impl::is_power(
        const ADL_PMLOG_SENSORS id) {
    switch (id) {
        case ADL_PMLOG_ASIC_POWER:
        case ADL_PMLOG_CPU_POWER:
        case ADL_PMLOG_GFX_POWER:
        case ADL_PMLOG_SOC_POWER:
            return true;

        default:
            return false;
    }
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::is_voltage
 */
bool visus::power_overwhelming::detail::adl_sensor_impl::is_voltage(
        const ADL_PMLOG_SENSORS id) {
    switch (id) {
        case ADL_PMLOG_GFX_VOLTAGE:
        case ADL_PMLOG_SOC_VOLTAGE:
            return true;

        default:
            return false;
    }
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
        const adl_sensor_source source,
        std::vector<ADL_PMLOG_SENSORS>&& sensorIDs) {

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


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::to_measurement
 */
visus::power_overwhelming::measurement
visus::power_overwhelming::detail::adl_sensor_impl::to_measurement(
        const ADLPMLogData& data, const timestamp_resolution resolution) {
    // We found empirically that the timestamp from ADL is in 100 ns units (at
    // least on Windows). Based on this assumption, convert to the requested
    // unit.
    auto timestamp = convert(static_cast<measurement::timestamp_type>(
        data.ulLastUpdated), resolution);

    // TODO: MAJOR HAZARD HERE!!! WE HAVE NO IDEA WHAT UNIT IS USED FOR VOLTAGE AND CURRENT. CURRENT CODE ASSUMES VOLT/AMPERE, BUT IT MIGHT BE MILLIVOLTS ...
    // The documentation says nothing about this.

    switch (count_sensor_readings(data)) {
        case 1:
            // If we have one reading, it must be a power reading due to the way
            // we enumerate the sensors in get_sensor_ids.
            return measurement(this->sensor_name.c_str(), timestamp,
                static_cast<measurement::value_type>(data.ulValues[0][1]));

        case 2:
            // If we have two readings, it must be voltage and current.
            return measurement(this->sensor_name.c_str(), timestamp,
                static_cast<measurement::value_type>(
                    data.ulValues[find_if(data, is_voltage)][1]),
                static_cast<measurement::value_type>(
                    data.ulValues[find_if(data, is_current)][1]));

        case 3:
            // This must be voltage, current and power.
            return measurement(this->sensor_name.c_str(), timestamp,
                static_cast<measurement::value_type>(
                    data.ulValues[find_if(data, is_voltage)][1]),
                static_cast<measurement::value_type>(
                    data.ulValues[find_if(data, is_current)][1]),
                static_cast<measurement::value_type>(
                    data.ulValues[find_if(data, is_power)][1]));

        default:
            throw std::logic_error("The provided sensor data are not "
                "compatible with the expected measurements . Valid "
                "combinations are: power; voltage and current; voltage, "
                "current and power.");
    }
}
