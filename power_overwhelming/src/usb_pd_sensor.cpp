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

    // Handle potential misuse of API.
    if (dst == nullptr) {
        cnt = 0;
    }

    try {
        auto testers = usb_pd_library::instance().usb_pd_tester_enumerate(
            config.timeout(), 100);
        if (testers == nullptr) {
            return 0;
        }

        pwrowg_on_exit([testers](void) {
            usb_pd_library::instance().usb_pd_tester_free(testers);
        });

        auto builder = sensor_description_builder::create()
            .with_vendor(L"PassMark")
            .produces(reading_type::floating_point);

        assert(testers != nullptr);
        for (auto path = testers; *path != 0; path += ::strlen(path) + 1) {
            auto tester = usb_pd_library::instance().usb_pd_tester_open(path);
            if (tester == nullptr) {
                continue;
            }

            // It is really important to disconnect whatever happens below!
            usb_pd_library::instance().usb_pd_tester_close(tester);

            if (retval < cnt) {
                dst[retval] = builder.with_id(L"%hs/voltage", path)
                    .with_path(path)
                    .with_name(L"USB PD %hs (voltage)", path)
                    .with_type(base_type | sensor_type::voltage)
                    .measured_in(reading_unit::volt)
                    .build();
            }
            ++retval;

            if (retval < cnt) {
                dst[retval] = builder.with_id(L"%hs/current", path)
                    .with_path(path)
                    .with_name(L"USB PD %hs (current)", path)
                    .with_type(base_type | sensor_type::current)
                    .measured_in(reading_unit::ampere)
                    .build();
            }
            ++retval;
        }

        return retval;
    } catch (...) {
        // This typically indicates that the usbpd library could not be loaded,
        // most likely due to a missing driver on the sytem which would have been
        // installed if a device had been connected.
        return 0;
    }
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
    this->_tester = usb_pd_library::instance().usb_pd_tester_open(p.c_str());
    if (this->_tester == nullptr) {
        throw std::runtime_error("Failed to connect to USB PD tester.");
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::~usb_pd_sensor
 */
PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::~usb_pd_sensor(void) {
    usb_pd_library::instance().usb_pd_tester_close(this->_tester);
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

    

    if (usb_pd_library::instance().usb_pd_tester_query(this->_tester,
            &temperature,
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

#endif /* defined(_WIN32) */
