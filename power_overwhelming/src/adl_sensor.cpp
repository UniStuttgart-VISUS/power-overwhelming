// <copyright file="adl_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#include "adl_sensor.h"

#include <algorithm>
#include <cassert>
#include <cstring>
#include <vector>

#include "visus/pwrowg/convert_string.h"

#include "adl_utils.h"
#include "amd_display_library.h"
#include "sensor_description_builder.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Answer whether the given sensor ID refers to a current sensor.
/// </summary>
static constexpr bool is_current(_In_ const ADL_PMLOG_SENSORS id) noexcept {
    switch (id) {
        case ADL_PMLOG_GFX_CURRENT:
        case ADL_PMLOG_SOC_CURRENT:
            return true;

        default:
            return false;
    }
}

/// <summary>
/// Answer whether the given sensor ID refers to a power sensor.
/// </summary>
static constexpr bool is_power(_In_ const ADL_PMLOG_SENSORS id) noexcept {
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

/// <summary>
/// Answer whether the given sensor ID refers to a thermal sensor.
/// </summary>
static constexpr bool is_thermal(_In_ const ADL_PMLOG_SENSORS id) noexcept {
    switch (id) {
        case ADL_PMLOG_TEMPERATURE_EDGE:
        case ADL_PMLOG_TEMPERATURE_MEM:
        case ADL_PMLOG_TEMPERATURE_VRVDDC:
        case ADL_PMLOG_TEMPERATURE_VRMVDD:
        case ADL_PMLOG_TEMPERATURE_LIQUID:
        case ADL_PMLOG_TEMPERATURE_PLX:
        case ADL_PMLOG_TEMPERATURE_VRSOC:
        case ADL_PMLOG_TEMPERATURE_VRMVDD0:
        case ADL_PMLOG_TEMPERATURE_VRMVDD1:
        case ADL_PMLOG_TEMPERATURE_HOTSPOT:
        case ADL_PMLOG_TEMPERATURE_GFX:
        case ADL_PMLOG_TEMPERATURE_SOC:
        case ADL_PMLOG_TEMPERATURE_CPU:
        case ADL_PMLOG_TEMPERATURE_LIQUID0:
        case ADL_PMLOG_TEMPERATURE_LIQUID1:
        case ADL_PMLOG_TEMPERATURE_HOTSPOT_GCD:
        case ADL_PMLOG_TEMPERATURE_HOTSPOT_MCD:
            return true;

        default:
            return false;
    }
}

/// <summary>
/// Answer whether the given sensor ID refers to a sensor reporting the
/// throttling status of the GPU.
/// </summary>
static constexpr bool is_throttling(_In_ const ADL_PMLOG_SENSORS id) noexcept {
    return (id == ADL_PMLOG_THROTTLER_STATUS);
}

/// <summary>
/// Answer whether the given sensor ID refers to a voltage sensor.
/// </summary>
static constexpr bool is_voltage(_In_ const ADL_PMLOG_SENSORS id) noexcept {
    switch (id) {
        case ADL_PMLOG_GFX_VOLTAGE:
        case ADL_PMLOG_SOC_VOLTAGE:
            return true;

        default:
            return false;
    }
}

/// <summary>
/// Answer the symbolic constant for the given sensor ID.
/// </summary>
static std::wstring to_string(_In_ const ADL_PMLOG_SENSORS id) {
#define _TO_STRING(i) L##i
#define _TO_STRING_CASE(i) case i: return _TO_STRING(#i)

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

#undef _TO_STRING
#undef _TO_STRING_CASE
}

PWROWG_DETAIL_NAMESPACE_END


/*
 * PWROWG_DETAIL_NAMESPACE::adl_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::adl_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    try {
        detail::adl_scope scope;

        // Get all active adapters.
        const auto adapters = get_adapters(scope);

        // For each adapter, get all supported sensors.
        auto builder = sensor_description_builder::create()
            .with_vendor(L"AMD");

        for (auto& a : adapters) {
            ADLPMLogSupportInfo support_info;

            // First, find out whether the adapter supports PMLog.
            {
                auto status = amd_display_library::instance()
                    .ADL2_Adapter_PMLog_Support_Get(scope,
                        a.iAdapterIndex,
                        &support_info);
                if (status != ADL_OK) {
                    throw adl_exception(status);
                }
            }

            // Now, process all of the supported sensor sources.
            for (auto s : support_info.usSensors) {
                auto sensor = static_cast<ADL_PMLOG_SENSORS>(s);

                if (is_current(sensor)) {
                } else if (is_power(sensor)) {
                } else if (is_thermal(sensor)) {
                } else if (is_throttling(sensor)) {
                } else if (is_voltage(sensor)) {
                }
            }
        /*case adl_sensor_source::asic:
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
                "unsupported.");*/


            //for_adapter(std::back_inserter(retval),
            //    scope,
            //    a,
            //    adl_sensor_source::all);
        }
        throw "TODO";
        return 0;

    } catch (...) {
        // AMD is not supported, we ignore that at this point.
        return 0;
    }
}



#if false
/// <summary>
/// Counts how many valid sensor readings are in <paramref name="data" />.
/// </summary>
/// <param name="data"></param>
/// <returns></returns>
static std::size_t count_sensor_readings(_In_ const ADLPMLogData& data) {
    std::size_t retval = 0;

    for (; (retval < ADL_PMLOG_MAX_SENSORS)
        && (data.ulValues[retval][0] != ADL_SENSOR_MAXTYPES);
        ++retval);

    return retval;
}


/// <summary>
/// Filter out the values we are interested in from the log data.
/// </summary>
/// <param name="voltage"></param>
/// <param name="current"></param>
/// <param name="power"></param>
/// <param name="data"></param>
/// <returns>The number of readings returned. If this is 1, only power
/// has been set. If it is 2, voltage and current have been set.
/// Otherwise, all values are set.</returns>
static std::size_t filter_sensor_readings(unsigned int& voltage,
        unsigned int& current,
        unsigned int& power,
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


/// <summary>
/// Retrieve the value of the requested sensor ID if in the sensor data.
/// </summary>
/// <param name="value"></param>
/// <param name="data"></param>
/// <param name="id"></param>
/// <returns></returns>
static bool filter_sensor_readings(_Out_opt_ unsigned int& value,
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


/// <summary>
/// Add all <see cref="sensor_description" />s for all supported sensors of
/// <paramref name="adapter" /> to the specified output iterator.
/// </summary>
/// <typeparam name="TIterator"></typeparam>
/// <param name="oit"></param>
/// <param name="scope"></param>
/// <param name="adapter"></param>
/// <param name="source"></param>
/// <returns></returns>
template<class TIterator>
std::size_t for_adapter(_In_ TIterator oit,
        _In_ PWROWG_DETAIL_NAMESPACE::adl_scope& scope,
        _In_ const AdapterInfo& adapter,
        _In_ const PWROWG_DETAIL_NAMESPACE::adl_sensor_source source) {
    using namespace PWROWG_DETAIL_NAMESPACE;
#define _PWROWG_ENABLED(haystack, needle) ((haystack & needle) == needle)

    std::size_t retval = 0;
    ADLPMLogSupportInfo supportInfo;

    // First, find out whether the adapter supports PMLlog.
    {
        auto status = detail::amd_display_library::instance()
            .ADL2_Adapter_PMLog_Support_Get(scope, adapter.iAdapterIndex,
            &supportInfo);
        if (status != ADL_OK) {
            throw adl_exception(status);
        }
    }

    // Now, check all of the supported sensor sources.
    if (_PWROWG_ENABLED(source, adl_sensor_source::asic)) {
        auto source = adl_sensor_source::asic;
        auto ids = detail::adl_sensor_impl::get_sensor_ids(source,
            supportInfo);

        if (!ids.empty()) {
            auto impl = new detail::adl_sensor_impl(adapter);
            impl->configure_source(source, std::move(ids));
            *oit++ = adl_sensor(std::move(impl));
            ++retval;
        }
    }

    if (_PWROWG_ENABLED(source, adl_sensor_source::cpu)) {
        auto source = adl_sensor_source::cpu;
        auto ids = detail::adl_sensor_impl::get_sensor_ids(source,
            supportInfo);

        if (!ids.empty()) {
            auto impl = new detail::adl_sensor_impl(adapter);
            impl->configure_source(source, std::move(ids));
            *oit++ = adl_sensor(std::move(impl));
            ++retval;
        }
    }

    if (_PWROWG_ENABLED(source, adl_sensor_source::graphics)) {
        auto source = adl_sensor_source::graphics;
        auto ids = detail::adl_sensor_impl::get_sensor_ids(source,
            supportInfo);

        if (!ids.empty()) {
            auto impl = new detail::adl_sensor_impl(adapter);
            impl->configure_source(source, std::move(ids));
            *oit++ = adl_sensor(std::move(impl));
            ++retval;
        }
    }

    if (_PWROWG_ENABLED(source, adl_sensor_source::soc)) {
        auto source = adl_sensor_source::soc;
        auto ids = detail::adl_sensor_impl::get_sensor_ids(source,
            supportInfo);

        if (!ids.empty()) {
            auto impl = new detail::adl_sensor_impl(adapter);
            impl->configure_source(source, std::move(ids));
            *oit++ = adl_sensor(std::move(impl));
            ++retval;
        }
    }

    if (_PWROWG_ENABLED(source, adl_sensor_source::board)) {
        auto source = adl_sensor_source::board;
        auto ids = detail::adl_sensor_impl::get_sensor_ids(source,
            supportInfo);

        if (!ids.empty()) {
            auto impl = new detail::adl_sensor_impl(adapter);
            impl->configure_source(source, std::move(ids));
            *oit++ = adl_sensor(std::move(impl));
            ++retval;
        }
    }

    return retval;
#undef _PWROWG_ENABLED
}


/// <summary>
/// Gets the IDs of the hardware sensors associated with the specified
/// source.
/// </summary>
/// <remarks>
/// The sensors are ordered (if supported): voltage, current, power.
/// </remarks>
/// <param name="source">The source to be measured.</param>
/// <returns>The IDs of the hardware sensors measuring the values at the
/// source.</returns>
static std::vector<ADL_PMLOG_SENSORS> get_sensor_ids(
        _In_ const PWROWG_DETAIL_NAMESPACE::adl_sensor_source source) {
    using PWROWG_DETAIL_NAMESPACE::adl_sensor_source;

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


/// <summary>
/// Determine which sensors of the specified source are supported in the
/// given <see cref="ADLPMLogSupportInfo" />.
/// </summary>
/// <param name="source"></param>
/// <param name="supportInfo"></param>
/// <returns>The intersection of the sensors supported according to
/// <paramref name="supportInfo" /> and the sensors required for
/// <paramref name="source" />.</returns>
static std::vector<ADL_PMLOG_SENSORS> get_sensor_ids(
        _In_ const PWROWG_DETAIL_NAMESPACE::adl_sensor_source source,
        _In_ const ADLPMLogSupportInfo& supportInfo) {
    using PWROWG_DETAIL_NAMESPACE::supports_sensor;
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
 * PWROWG_DETAIL_NAMESPACE::adl_sensor::descriptions
 */
std::vector<PWROWG_NAMESPACE::sensor_description>
PWROWG_DETAIL_NAMESPACE::adl_sensor::descriptions(void) {
    std::vector<sensor_description> retval;

    try {
        auto builder = sensor_description_builder::create().with_vendor(L"AMD");
        detail::adl_scope scope;

        // Get all active adapters.
        const auto adapters = detail::get_adapters(scope);

        // For each adapter, get all supported sensors.
        for (auto& a : adapters) {
            for_adapter(std::back_inserter(retval),
                scope,
                a,
                adl_sensor_source::all);
        }
    } catch (...) {
        /* AMD is not supported, we ignore that at this point.*/
    }

    return retval;
}


///*
// * visus::power_overwhelming::adl_sensor::from_index
// */
//visus::power_overwhelming::adl_sensor
//visus::power_overwhelming::adl_sensor::from_index(_In_ const int index,
//        _In_ const adl_sensor_source source) {
//    adl_sensor retval;
//
//    auto status = detail::amd_display_library::instance()
//        .ADL2_Device_PMLog_Device_Create(nullptr, index, &retval._impl->device);
//    if (status != ADL_OK) {
//        throw adl_exception(status);
//    }
//
//    throw "TODO: Implement retrieval from index.";
//
//    return retval;
//}


///*
// * visus::power_overwhelming::adl_sensor::from_udid
// */
//visus::power_overwhelming::adl_sensor
//visus::power_overwhelming::adl_sensor::from_udid(_In_z_ const char *udid,
//        _In_ const adl_sensor_source source) {
//    if (udid == nullptr) {
//        throw std::invalid_argument("The unique device identifier cannot be "
//            "null.");
//    }
//
//    detail::adl_scope scope;
//
//    auto adapters = detail::get_adapters_if(scope,
//        [udid](const detail::adl_scope&, const AdapterInfo& a) {
//            return (::strcmp(udid, a.strUDID) == 0);
//        });
//    if (adapters.size() != 1) {
//        throw std::invalid_argument("The unique device identifier did not "
//            "match a single device.");
//    }
//
//    std::vector<adl_sensor> retval;
//    auto sensors = detail::for_adapter(std::back_inserter(retval), scope,
//        adapters.front(), source);
//    if (sensors != 1) {
//        throw std::invalid_argument("A unique sensor source must be specified "
//            "when creating a single sensor.");
//    }
//
//    return std::move(retval.front());
//}
//
//
///*
// * visus::power_overwhelming::adl_sensor::from_udid
// */
//visus::power_overwhelming::adl_sensor
//visus::power_overwhelming::adl_sensor::from_udid(_In_z_ const wchar_t *udid,
//        _In_ const adl_sensor_source source) {
//    auto u = convert_string<char>(udid);
//    return from_udid(u.c_str(), source);
//}
//


/*
 * visus::power_overwhelming::adl_sensor::adl_sensor
 */
visus::power_overwhelming::adl_sensor::adl_sensor(void)
    : _impl(new detail::adl_sensor_impl()) { }


/*
 * visus::power_overwhelming::adl_sensor::~adl_sensor
 */
visus::power_overwhelming::adl_sensor::~adl_sensor(void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::adl_sensor::name
 */
_Ret_maybenull_z_ const wchar_t *visus::power_overwhelming::adl_sensor::name(
        void) const noexcept {
    if (this->_impl == nullptr) {
        return nullptr;
    } else {
        return this->_impl->sensor_name.c_str();
    }
}


/*
 * visus::power_overwhelming::adl_sensor::sample
 */
void visus::power_overwhelming::adl_sensor::sample(
        _In_opt_ const measurement_callback on_measurement,
        _In_ const microseconds_type period,
        _In_opt_ void *context) {
#if defined(_WIN32)
    ::OutputDebugStringW(L"PWROWG DEPRECATION WARNING: This method is only "
        L"provided for backwards compatibility and might be removed in "
        L"future versions of the library. Use async_sampling to configure "
        L"asynchronous sampling.\r\n");
#endif /* defined(_WIN32) */
    this->check_not_disposed();
    this->sample_async(std::move(async_sampling()
        .samples_every(period)
        .delivers_measurements_to(on_measurement)
        .passes_context(context)));
}


/*
 * visus::power_overwhelming::adl_sensor::start
 */
void visus::power_overwhelming::adl_sensor::start(
        _In_ const microseconds_type sampling_period) {
    using std::chrono::duration;
    using std::chrono::duration_cast;
    typedef duration<microseconds_type, std::micro> interval_type;

    this->check_not_disposed();

    auto sampler_rate = interval_type(sampling_period);
    auto adl_rate = duration_cast<std::chrono::milliseconds>(sampler_rate);
    this->_impl->start(static_cast<unsigned long>(adl_rate.count()));
}


/*
 * visus::power_overwhelming::adl_sensor::stop
 */
void visus::power_overwhelming::adl_sensor::stop(void) {
    if (this->_impl != nullptr) {
        this->_impl->stop();
    }
}


/*
 * visus::power_overwhelming::adl_sensor::source
 */
visus::power_overwhelming::adl_sensor_source
visus::power_overwhelming::adl_sensor::source(void) const {
    this->check_not_disposed();
    return this->_impl->source;
}


/*
 * visus::power_overwhelming::adl_sensor::udid
 */
_Ret_maybenull_z_ const char *visus::power_overwhelming::adl_sensor::udid(
        void) const noexcept {
    if (this->_impl == nullptr) {
        return nullptr;
    } else {
        return this->_impl->udid.c_str();
    }
}


/*
 * visus::power_overwhelming::adl_sensor::operator =
 */
visus::power_overwhelming::adl_sensor&
visus::power_overwhelming::adl_sensor::operator =(
        _Inout_ adl_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        delete this->_impl;
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::adl_sensor::operator bool
 */
visus::power_overwhelming::adl_sensor::operator bool(void) const noexcept {
    return (this->_impl != nullptr);
}


/*
 * visus::power_overwhelming::adl_sensor::sample_async
 */
void visus::power_overwhelming::adl_sensor::sample_async(
        _Inout_ async_sampling&& sampling) {
    using std::chrono::duration;
    using std::chrono::duration_cast;
    typedef duration<microseconds_type, std::micro> interval_type;

    if ((this->_impl->async_sampling = std::move(sampling))) {
        auto sampler_rate = interval_type(this->_impl->async_sampling.interval());
        auto adl_rate = duration_cast<std::chrono::milliseconds>(sampler_rate);

        // Make sure that the sensor is running before queuing to the thread.
        if (!this->_impl->running()) {
            this->_impl->start(static_cast<unsigned long>(adl_rate.count()));
        }

        // Register in the sampler collection dedicated to ADL. This is required
        // as we need to be able to find out when the last ADL sampler was
        // removed from the collection. We therefore cannot share the samplers
        // with other sensors.
        detail::adl_sensor_impl::sampler += this->_impl;

    } else {
        detail::adl_sensor_impl::sampler -= this->_impl;

        if (!detail::adl_sensor_impl::sampler) {
            // If there is no sensor left to sample, stop the sensor. This
            // condition is the reason for having a dedicated ADL sampler
            // collection.
            this->_impl->stop();
        }
    }
}


/*
 * visus::power_overwhelming::adl_sensor::sample_sync
 */
visus::power_overwhelming::measurement_data
visus::power_overwhelming::adl_sensor::sample_sync(void) const {
    this->check_not_disposed();
    const auto is_running = this->_impl->running();

    if (!is_running) {
        // If the sensor is not running asynchronously, start it for obtaining
        // a single sample.
        this->_impl->start(0);
    }

    auto retval = this->_impl->sample();

    if (!is_running) {
        // If we started the sensor here, stop it.
        this->_impl->stop();
    }

    return retval;
}

#endif


#if false
// <copyright file="adl_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#include "adl_sensor_impl.h"

#include <algorithm>
#include <cassert>
#include <limits>

#include "visus/pwrowg/convert_string.h"

#include "adl_exception.h"
#include "adl_utils.h"
#include "zero_memory.h"




/*
 * visus::power_overwhelming::detail::adl_sensor_impl::adl_sensor_impl
 */
visus::power_overwhelming::detail::adl_sensor_impl::adl_sensor_impl(void)
    : adapter_index(0), device(0), source(adl_sensor_source::all),
    start_input({ 0 }), start_output({ 0 }), state(0),
    utc_offset(detail::get_timezone_bias()) {}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::adl_sensor_impl
 */
visus::power_overwhelming::detail::adl_sensor_impl::adl_sensor_impl(
    const AdapterInfo &adapterInfo)
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
    std::vector<ADL_PMLOG_SENSORS> &&sensorIDs) {
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
 * visus::power_overwhelming::detail::adl_sensor_impl::configure_source
 */
void visus::power_overwhelming::detail::adl_sensor_impl::configure_source(
    _In_ const ADL_PMLOG_SENSORS sensor_id) {
    this->source = static_cast<adl_sensor_source>(0);

    // Set the sensor name.
    this->sensor_name = L"ADL/" + to_string(sensor_id)
        + L"/" + this->device_name
        + L"/" + std::to_wstring(this->adapter_index);

    // ADL_SENSOR_MAXTYPES, which is the guard for invalid sensors, is zero.
    ::ZeroMemory(this->start_input.usSensors,
        sizeof(this->start_input.usSensors));
    this->start_input.usSensors[0] = sensor_id;
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::deliver
 */
bool visus::power_overwhelming::detail::adl_sensor_impl::deliver(void) const {
    const auto name = this->sensor_name.c_str();

    if (this->async_sampling) {
        switch (this->async_sampling.delivery_method()) {
            case async_delivery_method::on_thermal_sample:
                return this->async_sampling.deliver(name,
                    this->sample_thermal());

            case async_delivery_method::on_throttling_sample:
                return this->async_sampling.deliver(name,
                    this->sample_throttling());

            default:
                return this->async_sampling.deliver(name,
                    this->sample());
        }

    } else {
        // If asynchronous sampling is disabled, the delivery method might be
        // bogus and this can cause an attempt to sample the wrong data.
        return false;
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
visus::power_overwhelming::detail::adl_sensor_impl::sample(void) const {
    assert(this->state.load() == 1);
    const auto data = static_cast<ADLPMLogData *>(
        this->start_output.pLoggingAddress);
    static constexpr auto thousand = static_cast<measurement::value_type>(1000);

    const auto timestamp = this->timestamp(*data);

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
 * visus::power_overwhelming::detail::adl_sensor_impl::sample_thermal
 */
visus::power_overwhelming::thermal_sample
visus::power_overwhelming::detail::adl_sensor_impl::sample_thermal(void) const {
    assert(this->state.load() == 1);
    const auto data = static_cast<ADLPMLogData *>(
        this->start_output.pLoggingAddress);
    const auto timestamp = this->timestamp(*data);
    auto state = throttling_state::none;
    auto temperature = std::numeric_limits<thermal_sample::value_type>::lowest();
    unsigned int value = 0;

    if (detail::adl_sensor_impl::filter_sensor_readings(value, *data,
        static_cast<ADL_PMLOG_SENSORS>(this->start_input.usSensors[0]))) {
        temperature = static_cast<decltype(temperature)>(value);
    }

    return thermal_sample(timestamp, value);
}


/*
 * visus::power_overwhelming::detail::adl_sensor_impl::sample_throttling
 */
visus::power_overwhelming::throttling_sample
visus::power_overwhelming::detail::adl_sensor_impl::sample_throttling(
    void) const {
    assert(this->state.load() == 1);
    const auto data = static_cast<ADLPMLogData *>(
        this->start_output.pLoggingAddress);
    const auto timestamp = this->timestamp(*data);
    auto state = throttling_state::none;
    unsigned int value = 0;

    if (detail::adl_sensor_impl::filter_sensor_readings(value, *data,
        static_cast<ADL_PMLOG_SENSORS>(this->start_input.usSensors[0]))) {
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

        if ((notification != 0) && (state == throttling_state::none)) {
            // Card reports throttling state we do not understand, so tell the
            // caller at least that we are throttled.
            state = throttling_state::other;
        }
    }

    return throttling_sample(timestamp, state);
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
#endif