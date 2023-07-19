// <copyright file="podump.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include "adl_sensor.h"
#include "collector.h"
#include "emi_sensor.h"
#include "graphics_devices.h"
#include "msr_sensor.h"
#include "nvml_sensor.h"
#include "rohde_und_schwarz.h"
#include "tinkerforge.h"


/// <summary>
/// Entry point of the podump application, which dumps all available sensor data
/// once to the console.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(const int argc, const TCHAR **argv) {
#if (defined(DEBUG) || defined(_DEBUG))
    ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //::_CrtSetBreakAlloc(420);
#endif /* (defined(DEBUG) || defined(_DEBUG)) */

#if false
    visus::power_overwhelming::stable_power_state_scope spss;
#endif

    // AMD sensors
#if false
#if true
    ::sample_adl_sensor();
#endif

#if true
    ::sample_adl_sensor_data();
#endif

#if true
    ::sample_adl_sensor_async(5);
#endif

#if true
    // Vega FE
    ::sample_adl_from_udid("PCI_VEN_1002&DEV_6863&SUBSYS_6B761002&REV_00_6&377B8C4D&0&00000019A");
#endif
#endif

    // EMI sensors
#if false
#if true
    ::sample_emi_sensor();
#endif

#if true
    ::sample_emi_sensor_data();
#endif

#if true
    ::sample_emi_sensor_async(5);
#endif
#endif

    // MSR sensors
#if false
#if true
    ::sample_msr_sensor();
#endif

#if true
    ::sample_msr_sensor_async(5);
#endif
#endif

    // NVML sensors
#if false
#if true
    ::sample_nvml_sensor();
#endif

#if true
    ::sample_nvml_sensor_data();
#endif

#if true
    ::sample_nvml_sensor_async(5);
#endif
#endif

    // Tinkerforge sensors
#if false
#if true
    ::sample_tinkerforge_sensor();
#endif

#if true
    ::sample_tinkerforge_sensor_data();
#endif

#if true
    ::sample_tinkerforge_sensor_async(5);
#endif

#if true
    ::print_tinkerforge_display();
#endif
#endif

    // Rohde & Schwarz sensors
#if true
#if false
    ::query_hmc8015();
#endif

#if true
    ::query_rtx_instrument();
#endif

#if false
    ::query_rtx();
#endif
#endif

    // Collector abstraction
#if false
#if false
    ::collect_all(L"idle.csv", 20);
#endif

#if true
    ::collect_template(L"tpl.json",  20);
#endif
#endif

    // Utility APIs
#if false
    ::enumerate_graphics_devices();
#endif

    return 0;
}
