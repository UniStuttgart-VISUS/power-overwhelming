// <copyright file="adl_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#include "adl_sensor_impl.h"

#include <algorithm>
#include <cassert>
#include <limits>

#include "power_overwhelming/convert_string.h"

#include "adl_exception.h"
#include "adl_utils.h"
#include "zero_memory.h"


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
 * visus::power_overwhelming::detail::adl_sensor_impl::filter_sensor_readings
 */
std::size_t
visus::power_overwhelming::detail::adl_sensor_impl::filter_sensor_readings(
        unsigned int& voltage, unsigned int& current, unsigned int& power,
        const ADLPMLogData& data) {
    auto have_current = false;
    auto have_power = false;
    auto have_voltage = false;
    std::size_t retval = 0;

    for (auto i = 0; (i < ADL_PMLOG_MAX_SENSORS)
            && (data.ulValues[i][0] != ADL_SENSOR_MAXTYPES); ++i) {
        auto s = static_cast<ADL_PMLOG_SENSORS>(data.ulValues[i][0]);

        if (is_power(s)) {
            power = data.ulValues[i][1];
            have_power = true;
            ++retval;

        } else if (is_current(s)) {
            current = data.ulValues[i][1];
            have_current = true;
            ++retval;

        } else if (is_voltage(s)) {
            voltage = data.ulValues[i][1];
            have_voltage = true;
            ++retval;
        }
    }

    if ((retval >= 3) && !(have_current && have_power && have_voltage)) {
        throw std::logic_error("An ADL sensor providing three values must "
            "provide voltage, current and power. The current sensor "
            "provides one of these multiple times and is lacking another, "
            "which is unexpected.");

    } else if ((retval == 2) && !(have_current && have_voltage)) {
        throw std::logic_error("An ADL sensor providing two values must "
            "provide voltage and current. The current sensor provides "
            "different values, most likely power, which is unexpcted.");

    } else if ((retval == 1) && !have_power) {
        throw std::logic_error("An ADL sensor providing one value must "
            "provide power. The current sensor provides a different value, "
            "which is not useful.");

    } else if (retval == 0) {
        throw std::logic_error("The current ADL sensor is not reading any "
            "of the quantities we are interested in.");
    }

    return (std::min)(static_cast<std::size_t>(3), retval);
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::filter_sensor_readings
 */
bool visus::power_overwhelming::detail::adl_sensor_impl::filter_sensor_readings(
        _Out_opt_ unsigned int& value,
        _In_ const ADLPMLogData& data,
        _In_ const ADL_PMLOG_SENSORS id) {
    for (auto i = 0; (i < ADL_PMLOG_MAX_SENSORS)
            && (data.ulValues[i][0] != ADL_SENSOR_MAXTYPES); ++i) {
        auto s = static_cast<ADL_PMLOG_SENSORS>(data.ulValues[i][0]);
        if (s == id) {
            value = data.ulValues[i][1];
            return true;
        }
    }
    // 'id' not found at this point.

    return false;
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::get_sensor_ids
 */
std::vector<ADL_PMLOG_SENSORS>
visus::power_overwhelming::detail::adl_sensor_impl::get_sensor_ids(
        const adl_sensor_source source) {
    switch (source) {
        case adl_sensor_source::asic:
            // TODO: Due to the logic combining voltage, current and power,
            // we currently cannot support SSPAIRED_ASICPOWER atm. Rework
            // this in the future.
            return std::vector<ADL_PMLOG_SENSORS> { ADL_PMLOG_ASIC_POWER /*,
                ADL_PMLOG_SSPAIRED_ASICPOWER */ };

        case adl_sensor_source::cpu:
            return std::vector<ADL_PMLOG_SENSORS> { ADL_PMLOG_CPU_POWER };

        case adl_sensor_source::board:
            return std::vector<ADL_PMLOG_SENSORS> { ADL_PMLOG_BOARD_POWER };

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

    // Erase all sensor IDs not supported according to 'supportInfo'.
    {
        auto end = std::remove_if(retval.begin(), retval.end(),
            [&supportInfo](const int id) {
                return !supports_sensor(supportInfo, id);
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
        case ADL_PMLOG_BOARD_POWER:
        case ADL_PMLOG_CPU_POWER:
        case ADL_PMLOG_GFX_POWER:
        case ADL_PMLOG_SOC_POWER:
        case ADL_PMLOG_SSPAIRED_ASICPOWER:
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
 * visus::power_overwhelming::detail::adl_sensor_impl::to_string
 */
std::wstring visus::power_overwhelming::detail::adl_sensor_impl::to_string(
        const ADL_PMLOG_SENSORS id) {
#define _TO_STRING_CASE(i) case i: return L#i

    switch (id) {
        _TO_STRING_CASE(ADL_PMLOG_CLK_GFXCLK);
        _TO_STRING_CASE(ADL_PMLOG_CLK_MEMCLK);
        _TO_STRING_CASE(ADL_PMLOG_CLK_SOCCLK);
        _TO_STRING_CASE(ADL_PMLOG_CLK_UVDCLK1);
        _TO_STRING_CASE(ADL_PMLOG_CLK_UVDCLK2);
        _TO_STRING_CASE(ADL_PMLOG_CLK_VCECLK);
        _TO_STRING_CASE(ADL_PMLOG_CLK_VCNCLK);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_EDGE);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_MEM);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_VRVDDC);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_VRMVDD);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_LIQUID);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_PLX);
        _TO_STRING_CASE(ADL_PMLOG_FAN_RPM);
        _TO_STRING_CASE(ADL_PMLOG_FAN_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_SOC_VOLTAGE);
        _TO_STRING_CASE(ADL_PMLOG_SOC_POWER);
        _TO_STRING_CASE(ADL_PMLOG_SOC_CURRENT);
        _TO_STRING_CASE(ADL_PMLOG_INFO_ACTIVITY_GFX);
        _TO_STRING_CASE(ADL_PMLOG_INFO_ACTIVITY_MEM);
        _TO_STRING_CASE(ADL_PMLOG_GFX_VOLTAGE);
        _TO_STRING_CASE(ADL_PMLOG_MEM_VOLTAGE);
        _TO_STRING_CASE(ADL_PMLOG_ASIC_POWER);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_VRSOC);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_VRMVDD0);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_VRMVDD1);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_HOTSPOT);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_GFX);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_SOC);
        _TO_STRING_CASE(ADL_PMLOG_GFX_POWER);
        _TO_STRING_CASE(ADL_PMLOG_GFX_CURRENT);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_CPU);
        _TO_STRING_CASE(ADL_PMLOG_CPU_POWER);
        _TO_STRING_CASE(ADL_PMLOG_CLK_CPUCLK);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_STATUS);
        _TO_STRING_CASE(ADL_PMLOG_CLK_VCN1CLK1);
        _TO_STRING_CASE(ADL_PMLOG_CLK_VCN1CLK2);
        _TO_STRING_CASE(ADL_PMLOG_SMART_POWERSHIFT_CPU);
        _TO_STRING_CASE(ADL_PMLOG_SMART_POWERSHIFT_DGPU);
        _TO_STRING_CASE(ADL_PMLOG_BUS_SPEED);
        _TO_STRING_CASE(ADL_PMLOG_BUS_LANES);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_LIQUID0);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_LIQUID1);
        _TO_STRING_CASE(ADL_PMLOG_CLK_FCLK);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_STATUS_CPU);
        _TO_STRING_CASE(ADL_PMLOG_SSPAIRED_ASICPOWER);
        _TO_STRING_CASE(ADL_PMLOG_SSTOTAL_POWERLIMIT);
        _TO_STRING_CASE(ADL_PMLOG_SSAPU_POWERLIMIT);
        _TO_STRING_CASE(ADL_PMLOG_SSDGPU_POWERLIMIT);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_HOTSPOT_GCD);
        _TO_STRING_CASE(ADL_PMLOG_TEMPERATURE_HOTSPOT_MCD);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_TEMP_EDGE_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_TEMP_HOTSPOT_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_TEMP_HOTSPOT_GCD_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_TEMP_HOTSPOT_MCD_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_TEMP_MEM_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_TEMP_VR_GFX_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_TEMP_VR_MEM0_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_TEMP_VR_MEM1_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_TEMP_VR_SOC_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_TEMP_LIQUID0_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_TEMP_LIQUID1_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_TEMP_PLX_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_TDC_GFX_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_TDC_SOC_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_TDC_USR_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_PPT0_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_PPT1_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_PPT2_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_PPT3_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_FIT_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_THROTTLER_GFX_APCC_PLUS_PERCENTAGE);
        _TO_STRING_CASE(ADL_PMLOG_BOARD_POWER);
        // Insert new sensors from adl_defines.h here.
        default: return L"";
    }

#undef _TO_STRING_CASE
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::sampler
 */
visus::power_overwhelming::detail::sampler
visus::power_overwhelming::detail::adl_sensor_impl::sampler;


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::adl_sensor_impl
 */
visus::power_overwhelming::detail::adl_sensor_impl::adl_sensor_impl(void)
    : adapter_index(0), device(0), source(adl_sensor_source::all),
        start_input({ 0 }), start_output({ 0 }), state(0),
        utc_offset(detail::get_timezone_bias()) { }


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::adl_sensor_impl
 */
visus::power_overwhelming::detail::adl_sensor_impl::adl_sensor_impl(
        const AdapterInfo& adapterInfo)
    : adapter_index(adapterInfo.iAdapterIndex), device(0),
        source(adl_sensor_source::all), start_input({ 0 }),
        start_output({ 0 }), state(0), udid(adapterInfo.strUDID),
        utc_offset(detail::get_timezone_bias()) {
    auto status = detail::amd_display_library::instance()
        .ADL2_Device_PMLog_Device_Create(this->scope, this->adapter_index,
        &this->device);
    if (status != ADL_OK) {
        throw adl_exception(status);
    }

    this->device_name = power_overwhelming::convert_string<wchar_t>(
        adapterInfo.strAdapterName);
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::~adl_sensor_impl
 */
visus::power_overwhelming::detail::adl_sensor_impl::~adl_sensor_impl(void) {
    // Unregister from any sampler the sensor might be referenced in.
    adl_sensor_impl::sampler -= this;

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
    this->source = source;

    // Determine which sensors are supported if not provided by the caller.
    if (sensorIDs.empty()) {
        ADLPMLogSupportInfo supportInfo;
        auto status = amd_display_library::instance()
            .ADL2_Adapter_PMLog_Support_Get(this->scope, this->adapter_index,
            &supportInfo);
        if (status != ADL_OK) {
            throw adl_exception(status);
        }

        sensorIDs = get_sensor_ids(this->source, supportInfo);
    }

    // Set the sensor name.
    switch (this->source) {
        case adl_sensor_source::asic:
            this->sensor_name = L"ADL/ASIC/" + this->device_name
                + L"/" + std::to_wstring(this->adapter_index);
            break;

        case adl_sensor_source::board:
            this->sensor_name = L"ADL/BOARD/" + this->device_name
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
 * visus::power_overwhelming::detail::adl_sensor_impl::deliver
 */
bool visus::power_overwhelming::detail::adl_sensor_impl::deliver(void) const {
    const auto name = this->sensor_name.c_str();
    const auto resolution = this->async_sampling.resolution();

    switch (this->async_sampling.delivery_method()) {
        case async_delivery_method::on_throttling_sample:
            return this->async_sampling.deliver(name,
                this->sample_throttling(resolution));

        default:
            return this->async_sampling.deliver(name, this->sample(resolution));
    }
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::interval
 */
visus::power_overwhelming::detail::adl_sensor_impl::interval_type
visus::power_overwhelming::detail::adl_sensor_impl::interval(
        void) const noexcept {
    return interval_type(this->async_sampling.interval());
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::sample
 */
visus::power_overwhelming::measurement_data
visus::power_overwhelming::detail::adl_sensor_impl::sample(
        const timestamp_resolution resolution) const {
    assert(this->state.load() == 1);
    const auto data = static_cast<ADLPMLogData *>(
        this->start_output.pLoggingAddress);
    static constexpr auto thousand = static_cast<measurement::value_type>(1000);
    const auto timestamp = this->timestamp(*data, resolution);

    // MAJOR HAZARD HERE!!! WE HAVE NO IDEA WHAT UNIT IS USED FOR VOLTAGE AND
    // CURRENT. The documentation says nothing about this, but some overclocking
    // tools (specifically "MorePowerTool") suggest that voltage is in mV,
    // current in A and power in W.

    unsigned int current, power, voltage;
    switch (filter_sensor_readings(voltage, current, power, *data)) {
        case 1:
            // If we have one reading, it must be a power reading due to the way
            // we enumerate the sensors in get_sensor_ids.
            return measurement_data(timestamp,
                static_cast<measurement::value_type>(power));

        case 2:
            // If we have two readings, it must be voltage and current.
            return measurement_data(timestamp,
                static_cast<measurement::value_type>(voltage) / thousand,
                static_cast<measurement::value_type>(current));

        case 3:
            // This must be voltage, current and power.
            return measurement_data(timestamp,
                static_cast<measurement::value_type>(voltage) / thousand,
                static_cast<measurement::value_type>(current),
                static_cast<measurement::value_type>(power));

        default:
            throw std::logic_error("The provided sensor data are not "
                "compatible with the expected measurements. Valid "
                "combinations are: power; voltage and current; voltage, "
                "current and power.");
    }
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::sample_throttling
 */
visus::power_overwhelming::throttling_sample
visus::power_overwhelming::detail::adl_sensor_impl::sample_throttling(
        _In_ const timestamp_resolution resolution) const {
    assert(this->state.load() == 1);
    const auto data = static_cast<ADLPMLogData *>(
        this->start_output.pLoggingAddress);
    const auto timestamp = this->timestamp(*data, resolution);
    auto state = throttling_state::none;
    unsigned int value = 0;

    if (detail::adl_sensor_impl::filter_sensor_readings(value, *data,
            ADL_PMLOG_THROTTLER_STATUS)) {
        const auto notification = static_cast<ADL_THROTTLE_NOTIFICATION>(value);

        if ((notification & ADL_PMLOG_THROTTLE_CURRENT) != 0) {
            state = state | throttling_state::current;
        }

        if ((notification & ADL_PMLOG_THROTTLE_POWER) != 0) {
            state = state | throttling_state::power;
        }

        if ((notification & ADL_PMLOG_THROTTLE_THERMAL) != 0) {
            state = state | throttling_state::thermal;
        }
    }

    return throttling_sample(timestamp, throttling_state::none);
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::start
 */
void visus::power_overwhelming::detail::adl_sensor_impl::start(
        const unsigned long samplingRate) {
    auto expected = 0;
    if (!this->state.compare_exchange_strong(expected, 2)) {
        throw std::runtime_error("The ADL sensor cannot be started while it is "
            "already running.");
    }

    this->start_input.ulSampleRate = samplingRate;

    auto status = detail::amd_display_library::instance()
        .ADL2_Adapter_PMLog_Start(this->scope, this->adapter_index,
            &this->start_input, &this->start_output, this->device);
    if (status == ADL_OK) {
        this->state.store(1, std::memory_order::memory_order_release);
    } else {
        this->state.store(0, std::memory_order::memory_order_release);
        throw new adl_exception(status);
    }
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::stop
 */
void visus::power_overwhelming::detail::adl_sensor_impl::stop(void) {
    auto expected = 1;
    if (this->state.compare_exchange_strong(expected, 2)) {
        // Note: Transitioning to two will ensure that the sensor cannot be
        // started or stopped by another thread while we are tearing it down.

        auto status = detail::amd_display_library::instance()
            .ADL2_Adapter_PMLog_Stop(this->scope, this->adapter_index,
                this->device);

        // Note: The sensor is broken if we marked it running and cannot stop
        // it, so we still mark it as not running in order to allow the user
        // to restart it (this might be an unreasonable approach so).
        this->state.store(0, std::memory_order::memory_order_release);

        if (status != ADL_OK) {
            throw new adl_exception(status);
        }
    }
}
