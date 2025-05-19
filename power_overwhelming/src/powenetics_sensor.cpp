// <copyright file="powenetics_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_POWENETICS)
#include "powenetics_sensor.h"

#include <array>
#include <stdexcept>
#include <system_error>

#include "com_error_category.h"
#include "sensor_array_impl.h"


/*
 * PWROWG_DETAIL_NAMESPACE_BEGIN::powenetics_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::powenetics_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    auto builder = sensor_description_builder::create()
        .with_vendor(L"Cybenetics")
        .produces(reading_type::floating_point);
    auto retval = static_cast<std::size_t>(0);

    if (dst == nullptr) {
        cnt = 0;
    }

    try {
        // Get all COM ports with a PMD attached.
        std::vector<powenetics_char> ports(64, static_cast<powenetics_char>(0));

        {
            auto len = ports.size();
            auto hr = ::powenetics_probe(ports.data(), &len);
            if (hr == HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER)) {
                // Increase the buffer size and try again.
                ports.resize(len);
                hr = ::powenetics_probe(ports.data(), &len);
            }

            if (FAILED(hr)) {
                throw std::system_error(hr, com_category());
            }
        }

        assert(!ports.empty());
        for (auto port = ports.data(); *port != 0;) {
            const auto p = PWROWG_NAMESPACE::convert_string<wchar_t>(port);
            builder.with_path(p);

            retval = specialise(dst, cnt, retval, builder,
                p, L"ATX 12V", sensor_type::system,
                [](const powenetics_sample& s) {
                    return s.atx_12v.voltage;
                },
                [](const powenetics_sample& s) {
                    return s.atx_12v.current;
                },
                [](const powenetics_sample& s) {
                    return s.atx_12v.voltage * s.atx_12v.current;
                });

            retval = specialise(dst, cnt, retval, builder,
                p, L"ATX 3.3V", sensor_type::system,
                [](const powenetics_sample& s) {
                    return s.atx_3_3v.voltage;
                },
                [](const powenetics_sample& s) {
                    return s.atx_3_3v.current;
                },
                [](const powenetics_sample& s) {
                    return s.atx_3_3v.voltage * s.atx_3_3v.current;
                });

            retval = specialise(dst, cnt, retval, builder,
                p, L"ATX 5V", sensor_type::system,
                [](const powenetics_sample& s) {
                    return s.atx_5v.voltage;
                },
                [](const powenetics_sample& s) {
                    return s.atx_5v.current;
                },
                [](const powenetics_sample& s) {
                    return s.atx_5v.voltage * s.atx_5v.current;
                });

            retval = specialise(dst, cnt, retval, builder,
                p, L"ATX Standby", sensor_type::system,
                [](const powenetics_sample& s) {
                    return s.atx_stb.voltage;
                },
                [](const powenetics_sample& s) {
                    return s.atx_stb.current;
                },
                [](const powenetics_sample& s) {
                    return s.atx_stb.voltage * s.atx_stb.current;
                });

            retval = specialise(dst, cnt, retval, builder,
                p, L"ATX EPS1", sensor_type::cpu,
                [](const powenetics_sample& s) {
                    return s.eps1.voltage;
                },
                [](const powenetics_sample& s) {
                    return s.eps1.current;
                },
                [](const powenetics_sample& s) {
                    return s.eps1.voltage * s.eps1.current;
                });

            retval = specialise(dst, cnt, retval, builder,
                p, L"ATX EPS2", sensor_type::cpu,
                [](const powenetics_sample& s) {
                    return s.eps2.voltage;
                },
                [](const powenetics_sample& s) {
                    return s.eps2.current;
                },
                [](const powenetics_sample& s) {
                    return s.eps2.voltage * s.eps2.current;
                });

            retval = specialise(dst, cnt, retval, builder,
                p, L"ATX EPS3", sensor_type::cpu,
                [](const powenetics_sample& s) {
                    return s.eps3.voltage;
                },
                [](const powenetics_sample& s) {
                    return s.eps3.current;
                },
                [](const powenetics_sample& s) {
                    return s.eps3.voltage * s.eps3.current;
                });

            retval = specialise(dst, cnt, retval, builder,
                p, L"ATX PCIe 1", sensor_type::gpu,
                [](const powenetics_sample& s) {
                    return s.pcie_12v1.voltage;
                },
                [](const powenetics_sample& s) {
                    return s.pcie_12v1.current;
                },
                [](const powenetics_sample& s) {
                    return s.pcie_12v1.voltage * s.pcie_12v1.current;
                });

            retval = specialise(dst, cnt, retval, builder,
                p, L"ATX PCIe 2", sensor_type::gpu,
                [](const powenetics_sample& s) {
                    return s.pcie_12v2.voltage;
                },
                [](const powenetics_sample& s) {
                    return s.pcie_12v2.current;
                },
                [](const powenetics_sample& s) {
                    return s.pcie_12v2.voltage * s.pcie_12v2.current;
                });

            retval = specialise(dst, cnt, retval, builder,
                p, L"ATX PCIe 3", sensor_type::gpu,
                [](const powenetics_sample& s) {
                    return s.pcie_12v3.voltage;
                },
                [](const powenetics_sample& s) {
                    return s.pcie_12v3.current;
                },
                [](const powenetics_sample& s) {
                    return s.pcie_12v3.voltage * s.pcie_12v3.current;
                });

            retval = specialise(dst, cnt, retval, builder,
                p, L"ATX PEG 12V", sensor_type::gpu,
                [](const powenetics_sample& s) {
                    return s.peg_12v.voltage;
                },
                [](const powenetics_sample& s) {
                    return s.peg_12v.current;
                },
                [](const powenetics_sample& s) {
                    return s.peg_12v.voltage * s.peg_12v.current;
                });

            retval = specialise(dst, cnt, retval, builder,
                p, L"ATX PEG 3.3V", sensor_type::gpu,
                [](const powenetics_sample& s) {
                    return s.peg_3_3v.voltage;
                },
                [](const powenetics_sample& s) {
                    return s.peg_3_3v.current;
                },
                [](const powenetics_sample& s) {
                    return s.peg_3_3v.voltage * s.peg_3_3v.current;
                });

            while (*port++ != 0);
        }

        return retval;
    } catch (...) {
        // Probably no PMD attached, ignore it.
        return 0;
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::powenetics_sensor::powenetics_sensor
 */
PWROWG_DETAIL_NAMESPACE::powenetics_sensor::powenetics_sensor(
        _In_z_ const wchar_t *path,
        _Inout_ std::map<index_type, selector_type>&& indices,
        _In_ const sensor_array_impl *owner)
    : _handle(nullptr),
        _indices(std::move(indices)),
        _owner(owner) {
    if (this->_owner == nullptr) {
        throw std::invalid_argument("The owning sensor array of a Powenetics "
            "sensor must not be null.");
    }

#if defined(_WIN32)
    auto hr = ::powenetics_open(&this->_handle, path, nullptr);
#else /* defined(_WIN32) */
    auto p = PWROWG_NAMESPACE::convert_string<powenetics_char>(path);
    auto hr = ::powenetics_open(&this->_handle, p.c_str(), nullptr);
#endif /* defined(_WIN32) */
    if (FAILED(hr)) {
        throw std::system_error(hr, com_category());
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::powenetics_sensor::~powenetics_sensor
 */
PWROWG_DETAIL_NAMESPACE::powenetics_sensor::~powenetics_sensor(void) noexcept {
    ::powenetics_close(this->_handle);
}


/*
 * PWROWG_DETAIL_NAMESPACE::powenetics_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::powenetics_sensor::sample(
        _In_ const bool enable) {
    if (enable) {
        this->_state.begin_start();

        auto hr = ::powenetics_start_streaming(this->_handle, on_sample, this);
        if (FAILED(hr)) {
            this->_state.stop();
            throw new std::system_error(hr, com_category());
        }

        this->_state.end_start();

    } else {
        this->_state.begin_stop();
        ::powenetics_stop_streaming(this->_handle);
        this->_state.end_stop();
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::powenetics_sensor::on_sample
 */
void PWROWG_DETAIL_NAMESPACE::powenetics_sensor::on_sample(
        _In_ powenetics_handle source,
        _In_ const struct powenetics_sample_t *sample,
        _In_opt_ void *context) {
    assert(sample != nullptr);
    assert(context != nullptr);

    auto that = static_cast<powenetics_sensor *>(context);
    std::vector<PWROWG_NAMESPACE::sample> samples;
    const timestamp ts(sample->timestamp);

    samples.reserve(that->_indices.size());

    for (auto& i : that->_indices) {
        samples.emplace_back(i.first, ts, i.second(*sample));
    }

    sensor_array_impl::callback(that->_owner, samples.data(), samples.size());
}


/*
 * PWROWG_DETAIL_NAMESPACE::powenetics_sensor::specialise
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::powenetics_sensor::specialise(
        _In_ sensor_description_builder& builder,
        _In_ const std::wstring& port,
        _In_z_ const wchar_t *rail,
        _In_ const sensor_type type,
        _In_z_ const wchar_t *quantity,
        _In_ const reading_unit unit,
        _In_ const selector_type& selector) {
    return builder.with_type(type)
        .with_id(L"Powenetics/%s/%s/%s", port.c_str(), rail, quantity)
        .with_name(L"Powenetics %s %s", rail, quantity)
        .measured_in(unit)
        .with_private_data(selector);
}


/*
 * PWROWG_DETAIL_NAMESPACE::powenetics_sensor::specialise
 */
std::size_t PWROWG_DETAIL_NAMESPACE::powenetics_sensor::specialise(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ const std::size_t cnt,
        _In_ std::size_t index,
        _In_ sensor_description_builder& builder,
        _In_ const std::wstring& port,
        _In_z_ const wchar_t *rail,
        _In_ const sensor_type type,
        _In_ const selector_type& voltage_selector,
        _In_ const selector_type& current_selector,
        _In_ const selector_type& power_selector) {
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
            L"apparent power",
            reading_unit::watt,
            power_selector).build();
    }
    ++index;

    return index;
}

#endif /* defined(POWER_OVERWHELMING_WITH_POWENETICS) */
