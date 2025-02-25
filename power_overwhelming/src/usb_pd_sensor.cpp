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
        DWORD devices;
        char path[64];

        {
            auto status = usb_pd_library::instance().FT_ListDevices(&devices,
                nullptr,
                FT_LIST_NUMBER_ONLY);
            if (!FT_SUCCESS(status)) {
                return 0;
            }
        }

        auto builder = sensor_description_builder::create()
            .with_vendor(L"PassMark")
            .produces(reading_type::floating_point);

        for (std::uintptr_t i = 0; i < devices; ++i) {
            auto status = usb_pd_library::instance().FT_ListDevices(
                reinterpret_cast<void *>(i),
                path,
                FT_LIST_BY_INDEX | FT_OPEN_BY_SERIAL_NUMBER);
            if (!FT_SUCCESS(status)) {
                // That did not work.
                continue;
            }

            if (::strncmp(path, "PMPD", 4) != 0) {
                // This is some other device.
                continue;
            }

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

            if (retval < cnt) {
                dst[retval] = builder.with_id(L"%hs/power", path)
                    .with_path(path)
                    .with_name(L"USB PD %hs (apparent power)", path)
                    .with_type(base_type | sensor_type::power)
                    .measured_in(reading_unit::watt)
                    .build();
            }
            ++retval;
        }

    } catch (...) {
        // This typically indicates that the usbpd library could not be loaded,
        // most likely due to a missing driver on the sytem which would have been
        // installed if a device had been connected.
        retval = 0;
    }

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::usb_pd_sensor
 */
PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::usb_pd_sensor(
        _In_z_ const wchar_t *serial,
        _In_ const configuration_type& config,
        _In_ const std::size_t index_voltage,
        _In_ const std::size_t index_current,
        _In_ const std::size_t index_power)
    : _index_current(index_current),
        _index_power(index_power),
        _index_voltage(index_voltage),
        _tester(nullptr) {
    if (serial == nullptr) {
        throw std::invalid_argument("A valid device serial must be provided.");
    }

    {
        auto s = PWROWG_NAMESPACE::convert_string<char>(serial);
        auto status = usb_pd_library::instance().FT_OpenEx(
            const_cast<char *>(s.c_str()),
            FT_OPEN_BY_SERIAL_NUMBER,
            &this->_tester);
        if (!FT_SUCCESS(status)) {
            // TODO: create a system_error specialisation.
            throw std::runtime_error("Failed to connect to USB PD tester.");
        }
    }

    {
        auto status = usb_pd_library::instance().FT_SetBaudRate(
            this->_tester,
            115200);
        if (!FT_SUCCESS(status)) {
            // TODO: create a system_error specialisation.
            throw std::runtime_error("FT_SetBaudRate failed.");
        }
    }

    {
        auto status = usb_pd_library::instance().FT_SetDataCharacteristics(
            this->_tester,
            FT_BITS_8,
            FT_STOP_BITS_1,
            FT_PARITY_NONE);
        if (!FT_SUCCESS(status)) {
            // TODO: create a system_error specialisation.
            throw std::runtime_error("FT_SetDataCharacteristics failed.");
        }
    }

    {
        auto status = usb_pd_library::instance().FT_SetTimeouts(
            this->_tester,
            config.read_timeout(),
            config.write_timeout());
        if (!FT_SUCCESS(status)) {
            // TODO: create a system_error specialisation.
            throw std::runtime_error("FT_SetTimeouts failed.");
        }
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::~usb_pd_sensor
 */
PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::~usb_pd_sensor(void) {
    usb_pd_library::instance().FT_Close(this->_tester);
}


/*
 * PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::sample(
        _In_ const sensor_array_callback callback,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context) {
    static const std::uint8_t request[] = { 0x02, 0x01, 0x0C, 0x0C, 0x03 };

    this->write(request, std::size(request));
    auto response = this->read();

    PWROWG_NAMESPACE::sample s;

    auto voltage = *reinterpret_cast<std::uint16_t*>(response.data() + 5);
    auto current = *reinterpret_cast<std::uint16_t*>(response.data() + 11);

    if (this->_index_voltage != invalid_index) {
        s.reading.floating_point = voltage / 1000.0f;
        s.source = this->_index_voltage;
        callback(&s, 1, sensors, context);
    }

    if (this->_index_current != invalid_index) {
        s.reading.floating_point = current / 1000.0f;
        s.source = this->_index_current;
        callback(&s, 1, sensors, context);
    }

    if (this->_index_power != invalid_index) {
        s.reading.floating_point = (voltage / 1000.0f) * (current / 1000.0f);
        s.source = this->_index_power;
        callback(&s, 1, sensors, context);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::read
 */
void PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::read(
        _Out_writes_bytes_(cnt) void *data,
        _In_ const std::uint32_t cnt) {
    assert(data != nullptr);
    auto rem = cnt;
    auto dst = static_cast<std::uint8_t *>(data);

    while (rem > 0) {
        DWORD read;
        auto status = usb_pd_library::instance().FT_Read(this->_tester,
            dst,
            rem,
            &read);
        if (!FT_SUCCESS(status)) {
            // TODO: create a system_error specialisation.
            throw std::runtime_error("FT_Read failed.");
        }

        assert(read <= rem);
        rem -= read;
        dst += read;
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::read
 */
std::vector<std::uint8_t> PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::read(void) {
    std::vector<std::uint8_t> retval(2);
    this->read(retval.data(), static_cast<std::uint32_t>(retval.size()));

    const auto off = retval.size();
    const auto cnt = static_cast<uint32_t>(retval[1] + 1 + 1);
    retval.resize(retval.size() + cnt);
    this->read(retval.data() + off, cnt);

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::write
 */
void PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::write(
        _In_reads_bytes_(cnt) const void *data,
        _In_ const std::uint32_t cnt) {
    assert(data != nullptr);
    auto rem = cnt;
    auto src = static_cast<std::uint8_t *>(const_cast<void *>(data));

    while (rem > 0) {
        DWORD written;
        auto status = usb_pd_library::instance().FT_Write(this->_tester,
            src,
            rem,
            &written);
        if (!FT_SUCCESS(status)) {
            // TODO: create a system_error specialisation.
            throw std::runtime_error("FT_Write failed.");
        }

        assert(written <= rem);
        rem -= written;
        src += written;
    }
}
#endif /* defined(_WIN32) */
