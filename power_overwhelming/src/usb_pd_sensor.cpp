// <copyright file="usb_pd_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(_WIN32)
#include "usb_pd_sensor.h"

#include <algorithm>
#include <array>
#include <memory>
#include <thread>

#include "visus/pwrowg/convert_string.h"

#include "visus/pwrowg/on_exit.h"


/*
 * PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    static const auto base_type = sensor_type::hardware | sensor_type::external;
    std::size_t retval = 0;
    PDTester tester;
    // The sample says that 16 characters for the name is OK ...
    char hacknomatik[MAX_NUM_TESTERS * 16];
    char *testers[MAX_NUM_TESTERS];

    // Handle potential misuse of API.
    if (dst == nullptr) {
        cnt = 0;
    }

    // Build the output array expected by the enumerator.
    for (std::size_t i = 0; i < MAX_NUM_TESTERS; ++i) {
        testers[i] = hacknomatik + i * sizeof(hacknomatik) / MAX_NUM_TESTERS;
    }

    // Compute the point in time where we give up finding devices.
    const auto deadline = std::chrono::steady_clock::now()
        + std::chrono::milliseconds(config.timeout());

    // Find the PD testers attached to the system. Note: If this does not find
    // anything although a device has been attached, the software probably
    // crashed before and did not disconnect properly. The PD tester needs to be
    // power cycled in this case.
    do {
        retval = tester.GetConnectedDevices(testers);
        // Another magic number from the sample for the sleep here ...
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } while ((retval < 1) && (deadline < std::chrono::steady_clock::now()));

    auto builder = sensor_description_builder::create()
        .with_vendor(L"PassMark")
        .produces(reading_type::floating_point);

    for (std::size_t i = 0, d = 0; i < retval; ++i) {
        if (!tester.Connect(testers[i], event_callback)) {
            --retval;
            continue;
        }

        // It is really important to disconnect whatever happens below!
        tester.Disconnect();

        if (d < cnt) {
            dst[d++] = builder.with_id(L"%hs/voltage", testers[i])
                .with_path(testers[i])
                .with_name(L"USB PD/%hs/voltage", testers[i])
                .with_type(base_type | sensor_type::voltage)
                .measured_in(reading_unit::volt)
                .build();
        }

        if (d < cnt) {
            dst[d++] = builder.with_id(L"%hs/current", testers[i])
                .with_path(testers[i])
                .with_name(L"USB PD/%hs/current", testers[i])
                .with_type(base_type | sensor_type::current)
                .measured_in(reading_unit::ampere)
                .build();
        }
    }

    // We have voltage and current from each device.
    return (2 * retval);
}


/*
 * PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::usb_pd_sensor
 */
PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::usb_pd_sensor(
        _In_z_ const wchar_t *port,
        _In_ const std::size_t index_voltage,
        _In_ const std::size_t index_current)
        : _index_current(index_current), _index_voltage(index_voltage) {
    if (port == nullptr) {
        throw std::invalid_argument("A valid port must be provided.");
    }

    auto p = PWROWG_NAMESPACE::convert_string<char>(port);
    if (!this->_tester.Connect(const_cast<char *>(p.c_str()), event_callback)) {
        throw std::runtime_error("Failed to connect to USB PD tester.");
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::~usb_pd_sensor
 */
PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::~usb_pd_sensor(void) {
    this->_tester.Disconnect();
}


/*
 * PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::sample(
        _In_ const sensor_array_callback callback,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context) {
    unsigned char temperature;
    std::uint16_t voltage;
    std::uint16_t set_current;
    std::uint16_t current;
    std::uint16_t loopback_current;

    if (this->_tester.GetStatistics(&temperature,
            &voltage,
            &set_current,
            &current,
            &loopback_current)) {
        PWROWG_NAMESPACE::sample s;

        if (this->_index_voltage != invalid_index) {
            s.reading.floating_point = voltage / 1000.0;
            s.source = this->_index_voltage;
            callback(&s, 1, sensors, context);
        }

        if (this->_index_voltage != invalid_index) {
            s.reading.floating_point = loopback_current / 1000.0;
            s.source = this->_index_current;
            callback(&s, 1, sensors, context);
        }
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::event_callback
 */
void PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::event_callback(
    _In_ const int event_code) { }

#endif /* defined(_WIN32) */
