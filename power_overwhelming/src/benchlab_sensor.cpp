// <copyright file="benchlab_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_BENCHLAB)
#include "benchlab_sensor.h"

#include <array>
#include <stdexcept>
#include <system_error>

#include "com_error_category.h"
#include "sensor_array_impl.h"


/*
 * PWROWG_DETAIL_NAMESPACE_BEGIN::benchlab_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::benchlab_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    auto builder = sensor_description_builder::create()
        .with_vendor(L"ElmorLabs")
        .with_class(configuration_type::id)
        .produces(reading_type::floating_point);
    auto retval = static_cast<std::size_t>(0);

    if (dst == nullptr) {
        cnt = 0;
    }

    try {
        // Get all COM ports with a PMD attached.
        std::vector<benchlab_char> ports(MAX_PATH + 1, 0);

        {
            auto len = ports.size();
            auto hr = ::benchlab_probe(ports.data(), &len);
            if (hr == HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER)) {
                // Increase the buffer size and try again.
                ports.resize(len);
                hr = ::benchlab_probe(ports.data(), &len);
            }

            if (FAILED(hr)) {
                throw std::system_error(hr, com_category());
            }
        }

        // Get the names of all power sensors available.
        auto power_sensors = visus::benchlab::get_power_sensors();

        assert(!ports.empty());
        for (auto port = ports.data(); *port != 0;) {
            const auto p = PWROWG_NAMESPACE::convert_string<wchar_t>(port);
            builder.with_path(p);

            for (std::size_t i = 0; i < power_sensors.size(); ++i) {
                const auto& s = power_sensors[i];
                const auto r = PWROWG_NAMESPACE::convert_string<wchar_t>(s);
                retval = specialise(dst, cnt, retval, builder, p, r.c_str(),
                    [i](const benchlab_sensor_readings& r) {
                        return r.power_readings[i].voltage / 1000.0f;
                    },
                    [i](const benchlab_sensor_readings& r) {
                        return r.power_readings[i].current / 1000.0f;
                    },
                    [i](const benchlab_sensor_readings& r) {
                        return r.power_readings[i].power / 1000.0f;
                    });
            }

            while (*port++ != 0);
        }

        return retval;
    } catch (...) {
        // Probably no PMD attached, ignore it.
        return 0;
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::benchlab_sensor::benchlab_sensor
 */
PWROWG_DETAIL_NAMESPACE::benchlab_sensor::benchlab_sensor(
        _In_z_ const wchar_t *path,
        _Inout_ std::map<index_type, selector_type>&& indices)
        : _handle(nullptr), _indices(std::move(indices)) {
    benchlab_handle h;

#if defined(_WIN32)
    auto hr = ::benchlab_open(&h, path, nullptr);
#else /* defined(_WIN32) */
    auto p = PWROWG_NAMESPACE::convert_string<benchlab_char>(path);
    auto hr = ::benchlab_open(&h, p.c_str(), nullptr);
#endif /* defined(_WIN32) */
    if (FAILED(hr)) {
        throw std::system_error(hr, com_category());
    }

    this->_handle.reset(h);
}


/*
 * PWROWG_DETAIL_NAMESPACE::benchlab_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::benchlab_sensor::sample(
        _In_ const sensor_array_callback callback,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context) {
    benchlab_sensor_readings readings;

    const auto t1 = timestamp::now();
    if (SUCCEEDED(::benchlab_read_sensors(&readings, this->_handle.get()))) {
        const auto t2 = timestamp::now();
        const auto t = timestamp::middle(t1, t2);

        this->_samples.resize(this->_indices.size());

        std::size_t i = 0;
        for (auto& idx : this->_indices) {
            this->_samples[i].source = static_cast<index_type>(idx.first);
            this->_samples[i].timestamp = t;
            this->_samples[i].reading.floating_point = idx.second(readings);
            ++i;
        }

        callback(this->_samples.data(), this->_samples.size(), sensors,
            context);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::benchlab_sensor::specialise
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::benchlab_sensor::specialise(
        _In_ sensor_description_builder& builder,
        _In_ const std::wstring& port,
        _In_z_ const wchar_t *rail,
        _In_ const sensor_type type,
        _In_z_ const wchar_t *quantity,
        _In_ const reading_unit unit,
        _In_ const selector_type& selector) {
    return builder.with_type(type)
        .with_id(L"BenchLab/%s/%s/%s", port.c_str(), rail, quantity)
        .with_name(L"BenchLab %s %s", rail, quantity)
        .measured_in(unit)
        .with_private_data(selector);
}


/*
 * PWROWG_DETAIL_NAMESPACE::benchlab_sensor::specialise
 */
std::size_t PWROWG_DETAIL_NAMESPACE::benchlab_sensor::specialise(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ const std::size_t cnt,
        _In_ std::size_t index,
        _In_ sensor_description_builder& builder,
        _In_ const std::wstring& port,
        _In_z_ const wchar_t *rail,
        _In_ const selector_type& voltage_selector,
        _In_ const selector_type& current_selector,
        _In_ const selector_type& power_selector) {
    sensor_type type = sensor_type::unknown;

    // We know that we can obtain the type of the sensor from the name of the
    // rail as follows because libbenchlab is our own product...
    if (detail::starts_with(rail, L"ATX", true)) {
        type = sensor_type::system;

    } else if (detail::starts_with(rail, L"EPS", true)) {
        type = sensor_type::cpu;

    } else if (detail::starts_with(rail, L"PCIE", true)) {
        type = sensor_type::gpu;

    } else if (detail::starts_with(rail, L"HPWR", true)) {
        type = sensor_type::gpu;
    }

    if (index < cnt) {
        dst[index] = specialise(builder,
            port,
            rail,
            type | sensor_type::voltage,
            L"voltage",
            reading_unit::volt,
            voltage_selector).build();
    }
    ++index;

    if (index < cnt) {
        dst[index] = specialise(builder,
            port,
            rail,
            type | sensor_type::current,
            L"current",
            reading_unit::ampere,
            current_selector).build();
    }
    ++index;

    if (index < cnt) {
        dst[index] = specialise(builder,
            port,
            rail,
            type | sensor_type::power,
            L"power",
            reading_unit::watt,
            power_selector).build();
    }
    ++index;

    return index;
}

#endif /* defined(POWER_OVERWHELMING_WITH_BENCHLAB) */
