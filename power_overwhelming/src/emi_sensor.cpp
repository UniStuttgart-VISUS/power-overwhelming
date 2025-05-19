// <copyright file="emi_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "emi_sensor.h"

#include <algorithm>
#include <stdexcept>
#include <system_error>

#include "sensor_description_builder.h"
#include "setup_api.h"


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::emi_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    std::size_t retval = 0;

#if defined(_WIN32)
    if (dst == nullptr) {
        cnt = 0;
    }

    detail::enumerate_device_interface(::GUID_DEVICE_ENERGY_METER,
            [dst, cnt, &retval](HDEVINFO h, SP_DEVICE_INTERFACE_DATA& d) {
        const auto base_type = sensor_type::software | sensor_type::power;
        const auto editable_type = sensor_type::system | sensor_type::cpu
            | sensor_type::gpu;
        auto path = detail::get_device_path(h, d);
        auto dev = emi_device_factory::create(path);

        auto builder = sensor_description_builder::create()
            .with_path(path);

        switch (dev->version().EmiVersion) {
            case EMI_VERSION_V1:
                if (retval < cnt) {
                    const auto md = dev->metadata_as<EMI_METADATA_V1>();
                    builder.with_vendor(md->HardwareOEM)
                        .with_name(L"%s %hu", md->HardwareModel,
                            md->HardwareRevision)
                        .with_id(L"EMI/%s", path.c_str())
                        .with_type(base_type)
                        .with_editable_type(editable_type)
                        .produces(reading_type::floating_point)
                        .measured_in(reading_unit::watt);
                    dst[retval] = builder.build();
                }
                ++retval;
                break;

            case EMI_VERSION_V2: {
                const auto md = dev->metadata_as<EMI_METADATA_V2>();
                auto c = md->Channels;

                for (USHORT i = 0; i < md->ChannelCount; ++i) {
                    if (retval < cnt) {
                        std::wstring n(c->ChannelName, c->ChannelNameSize);
                        builder.with_vendor(md->HardwareOEM)
                            .with_name(L"%s %hu/%s", md->HardwareModel,
                                md->HardwareRevision, n.c_str())
                            .with_id(L"EMI/%s/%hu", path.c_str(), i)
                            .with_type(base_type)
                            .with_editable_type(editable_type)
                            .produces(reading_type::floating_point)
                            .measured_in(reading_unit::watt)
                            .with_private_data(i);
                        dst[retval] = builder.build();
                    }
                    ++retval;
                    c = EMI_CHANNEL_V2_NEXT_CHANNEL(c);
                }
            } break;
        }

        return true;
    });
#endif /* defined(_WIN32) */

    return retval;
}


#if defined(_WIN32)
/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::emi_sensor
 */
PWROWG_DETAIL_NAMESPACE::emi_sensor::emi_sensor(
        _In_z_ const wchar_t *path,
        _In_ std::vector<channel_type>&& channels,
        _In_ const PWROWG_NAMESPACE::sample::source_type index)
    : _channels(std::move(channels)),
        _device(emi_device_factory::create(path)),
        _index(index) {
    if (this->_device == nullptr) {
        throw std::invalid_argument("A valid EMI device must be provided to a "
            "new EMI sensor.");
    }

    switch (this->version()) {
        case EMI_VERSION_V1: {
            // Channels are irrelevant for v1, allocate just one slot
            assert(this->_channels.empty());
            this->_last_energy.resize(1);
            this->_last_time.resize(1);
            this->_time_offset.resize(1);

            //auto md = this->_device->metadata_as<EMI_METADATA_V1>();
            //this->_unit = md->MeasurementUnit;

            // We need to sample the sensor once in order to obtain a starting
            // point that allows us to compute the difference between any two
            // samples requested by the user.
            EMI_MEASUREMENT_DATA_V1 m;
            this->sample(&m, sizeof(m));
            FILETIME t;
            ::GetSystemTimePreciseAsFileTime(&t);

            this->_last_energy.back() = m.AbsoluteEnergy;
            this->_last_time.back() = m.AbsoluteTime;
            this->_time_offset.back() = timestamp::from_file_time(t)
                - this->_last_time.back();
        } break;

        case EMI_VERSION_V2: {
            auto md = this->_device->metadata_as<EMI_METADATA_V2>();

            // As for v1, obtain the initial sample now.
            std::vector<std::uint8_t> m(this->buffer_size());
            this->sample(m.data(), m.size());
            FILETIME t;
            ::GetSystemTimePreciseAsFileTime(&t);

            this->_last_energy.reserve(this->_channels.size());
            this->_last_time.reserve(this->_channels.size());
            this->_time_offset.reserve(this->_channels.size());

            auto mm = reinterpret_cast<EMI_MEASUREMENT_DATA_V2 *>(m.data());
            for (auto c : this->_channels) {
                if (c > md->ChannelCount) {
                    throw std::invalid_argument("An invalid EMI channel was "
                        "specified.");
                }

                this->_last_energy.push_back(mm->ChannelData[c].AbsoluteEnergy);
                this->_last_time.push_back(mm->ChannelData[c].AbsoluteTime);
                this->_time_offset.push_back(timestamp::from_file_time(t)
                    - this->_last_time.back());
            }
        } break;

        default:
            throw std::logic_error("The specified version of the Energy "
                "Meter Interface is not supported by the implementation.");
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::emi_sensor::sample(
        _In_ const sensor_array_callback callback,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context) {
    assert(callback != nullptr);
    std::vector<std::uint8_t> data(0);

    switch (this->version()) {
        case EMI_VERSION_V1:
            data.resize(sizeof(EMI_MEASUREMENT_DATA_V1));
            this->sample(data.data(), data.size());
            this->evaluate(
                *reinterpret_cast<EMI_MEASUREMENT_DATA_V1 *>(data.data()),
                callback,
                sensors,
                context);
            break;

        case EMI_VERSION_V2:
            data.resize(sizeof(EMI_MEASUREMENT_DATA_V2)
                + this->_device->metadata_as<EMI_METADATA_V2>()->ChannelCount
                * sizeof(EMI_CHANNEL_MEASUREMENT_DATA));
            this->sample(data.data(), data.size());
            this->evaluate(
                *reinterpret_cast<EMI_MEASUREMENT_DATA_V2 *>(data.data()),
                callback,
                sensors,
                context);
            break;
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::buffer_size
 */
std::size_t PWROWG_DETAIL_NAMESPACE::emi_sensor::buffer_size(void) const {
    switch (this->version()) {
        case EMI_VERSION_V1:
            return sizeof(EMI_MEASUREMENT_DATA_V1);

        case EMI_VERSION_V2:
            return sizeof(EMI_MEASUREMENT_DATA_V2)
                + this->_device->metadata_as<EMI_METADATA_V2>()->ChannelCount
                * sizeof(EMI_CHANNEL_MEASUREMENT_DATA);

        default:
            return 0;
    }
}

/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::evaluate
 */
void PWROWG_DETAIL_NAMESPACE::emi_sensor::evaluate(
        _In_ const EMI_CHANNEL_MEASUREMENT_DATA& data,
        _In_ const sensor_array_callback callback,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context) {
    assert(callback != nullptr);
    assert(this->_last_energy.size() == 1);
    assert(this->_last_time.size() == 1);
    assert(this->_time_offset.size() == 1);

    auto de = data.AbsoluteEnergy - this->_last_energy.back();
    auto dt = data.AbsoluteTime - this->_last_time.back();
    this->_last_energy.back() = data.AbsoluteEnergy;
    this->_last_time.back() = data.AbsoluteEnergy;

    // The unit currently is always pWh.
    // de / dt [pWh / 100ns]
    // 1 [pW] = 10^-12 [W]
    // 100 [ns] = 10^-7 [s]
    auto value = static_cast<float>(de) * 0.036f;
    value /= static_cast<float>(dt);
    auto time = data.AbsoluteTime - dt / 2 + this->_time_offset.back();

    PWROWG_NAMESPACE::sample s(this->_index, timestamp(time), value);
    callback(&s, 1, sensors, context);
}


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::evaluate
 */
void PWROWG_DETAIL_NAMESPACE::emi_sensor::evaluate(
        _In_ const EMI_MEASUREMENT_DATA_V2& data,
        _In_ const sensor_array_callback callback,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context) {
    assert(callback != nullptr);
    const auto md = this->_device->metadata_as<EMI_METADATA_V2>();
    assert(this->_channels.size() == md->ChannelCount);

    PWROWG_NAMESPACE::sample::source_type i = 0;

    for (auto c : this->_channels) {
        assert(this->_last_energy.size() > c);
        assert(this->_last_time.size() > c);
        assert(this->_time_offset.size() > c);

        auto de = data.ChannelData[c].AbsoluteEnergy - this->_last_energy[c];
        auto dt = data.ChannelData[c].AbsoluteTime - this->_last_time[c];
        this->_last_energy[c] = data.ChannelData[c].AbsoluteEnergy;
        this->_last_time[c] = data.ChannelData[c].AbsoluteEnergy;

        // The unit currently is always pWh.
        // de / dt [pWh / 100ns]
        // 1 [pW] = 10^-12 [W]
        // 100 [ns] = 10^-7 [s]
        auto value = static_cast<float>(de) * 0.036f;
        value /= static_cast<float>(dt);
        auto time = data.ChannelData[c].AbsoluteTime - dt / 2
            + this->_time_offset.back();

        // TODO: filter out inactive channels.

        PWROWG_NAMESPACE::sample s(this->_index + i++, timestamp(time), value);
        callback(&s, 1, sensors, context);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::sample
 */
std::size_t PWROWG_DETAIL_NAMESPACE::emi_sensor::sample(
        _Out_writes_bytes_opt_(cnt) void *buffer,
        _In_ const std::size_t cnt) {
    DWORD retval = 0;

    if (!::DeviceIoControl(*this->_device,
            IOCTL_EMI_GET_MEASUREMENT,
            nullptr, 0,
            buffer, static_cast<ULONG>(cnt),
            &retval, 0)) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    return retval;
}
#endif /* defined(_WIN32) */

#if false

#include <cinttypes>
#include <memory>
#include <regex>
#include <system_error>
#include <stdexcept>
#include <vector>

#include "emi_sensor_impl.h"
#include "setup_api.h"


#define ERROR_MSG_NOT_SUPPORTED ("The EMI sensor is not supported on this " \
    "platform.")


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::for_channel
 */
std::size_t PWROWG_DETAIL_NAMESPACE::emi_sensor::for_channel(
        _Out_writes_opt_(cnt_sensors) emi_sensor *out_sensors,
        _In_ const std::size_t cnt_sensors,
        _In_z_ const wchar_t *channel) {
    if (channel == nullptr) {
        throw std::invalid_argument("The regular expression selecting the "
            "channel must not be null.");
    }

#if defined(_WIN32)
    typedef detail::emi_sensor_impl::string_type string_type;
    std::basic_regex<wchar_t> rx(channel);
    return detail::emi_sensor_impl::create(out_sensors, cnt_sensors,
            [&rx](const string_type&, const EMI_CHANNEL_V2 *c,
            const std::size_t) {
        return std::regex_match(c->ChannelName, rx);
    });
#else /* defined(_WIN32) */
    return 0;
#endif /* defined(_WIN32) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::for_device
 */
std::size_t PWROWG_DETAIL_NAMESPACE::emi_sensor::for_device(
        _Out_writes_opt_(cnt_sensors) emi_sensor *out_sensors,
        _In_ const std::size_t cnt_sensors,
        _In_z_ const char_type *device) {
    if (device == nullptr) {
        throw std::invalid_argument("The regular expression selecting the "
            "device must not be null.");
    }

#if defined(_WIN32)
    typedef detail::emi_sensor_impl::string_type string_type;
    std::basic_regex<char_type> rx(device);
    return detail::emi_sensor_impl::create(out_sensors, cnt_sensors,
            [&rx](const string_type& d, const EMI_CHANNEL_V2 *,
            const std::size_t) {
        return std::regex_match(d, rx);
    });
#else /* defined(_WIN32) */
    return 0;
#endif /* defined(_WIN32) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::for_device_and_channel
 */
std::size_t PWROWG_DETAIL_NAMESPACE::emi_sensor::for_device_and_channel(
        _Out_writes_opt_(cnt_sensors) emi_sensor *out_sensors,
        _In_ const std::size_t cnt_sensors,
        _In_z_ const char_type *device,
        _In_z_ const char_type *channel) {
    if (device == nullptr) {
        throw std::invalid_argument("The regular expression selecting the "
            "device must not be null.");
    }
    if (channel == nullptr) {
        throw std::invalid_argument("The regular expression selecting the "
            "channel must not be null.");
    }

#if defined(_WIN32)
    typedef detail::emi_sensor_impl::string_type string_type;
    std::basic_regex<char_type> rxc(channel);
    std::basic_regex<char_type> rxd(device);
    return detail::emi_sensor_impl::create(out_sensors, cnt_sensors,
            [&rxc, &rxd](const string_type& d, const EMI_CHANNEL_V2 *c,
            const std::size_t) {
        return (std::regex_match(d, rxd)
            && std::regex_match(c->ChannelName, rxc));
    });
#else /* defined(_WIN32) */
    return 0;
#endif /* defined(_WIN32) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::for_device_and_channel
 */
std::size_t PWROWG_DETAIL_NAMESPACE::emi_sensor::for_device_and_channel(
        _Out_writes_opt_(cnt_sensors) emi_sensor *out_sensors,
        _In_ const std::size_t cnt_sensors,
        _In_z_ const char_type *device,
        _In_ const channel_type channel) {
    if (device == nullptr) {
        throw std::invalid_argument("The regular expression selecting the "
            "device must not be null.");
    }

#if defined(_WIN32)
    typedef detail::emi_sensor_impl::string_type string_type;
    std::basic_regex<char_type> rx(device);
    return detail::emi_sensor_impl::create(out_sensors, cnt_sensors,
            [channel, &rx](const string_type &d, const EMI_CHANNEL_V2 *,
            const std::size_t c) {
        return ((channel == c) && std::regex_match(d, rx));
    });
#else /* defined(_WIN32) */
    return 0;
#endif /* defined(_WIN32) */
}



/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::~emi_sensor
 */
PWROWG_DETAIL_NAMESPACE::emi_sensor::~emi_sensor(void) {
    delete this->_impl;
}


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::channel
 */
PWROWG_DETAIL_NAMESPACE::emi_sensor::channel_type
PWROWG_DETAIL_NAMESPACE::emi_sensor::channel(void) const {
#if defined(_WIN32)
    return (*this)
        ? this->_impl->channel
        : static_cast<decltype(this->channel())>(0);
#else /* defined(_WIN32) */
    return 0;
#endif /* defined(_WIN3) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::channels
 */
PWROWG_DETAIL_NAMESPACE::emi_sensor::channel_type
PWROWG_DETAIL_NAMESPACE::emi_sensor::channels(void) const {
#if defined(_WIN32)
    return (*this)
        ? this->_impl->device->channels()
        : static_cast<decltype(this->channels())>(0);
#else /* defined(_WIN32) */
    return 0;
#endif /* defined(_WIN32) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::name
 */
_Ret_maybenull_z_ const wchar_t *PWROWG_DETAIL_NAMESPACE::emi_sensor::name(
        void) const noexcept {
#if defined(_WIN32)
    return (this->_impl != nullptr)
        ? this->_impl->sensor_name.c_str()
        : nullptr;
#else /* defined(_WIN32) */
    return nullptr;
#endif /* defined(_WIN32) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::path
 */
_Ret_maybenull_z_ const PWROWG_DETAIL_NAMESPACE::emi_sensor::char_type *
PWROWG_DETAIL_NAMESPACE::emi_sensor::path(void) const noexcept {
#if defined(_WIN32)
    return (this->_impl != nullptr)
        ? this->_impl->path.c_str()
        : nullptr;
#else /* defined(_WIN32) */
    return nullptr;
#endif /* defined(_WIN32) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::emi_sensor::sample(
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


#if defined(_WIN32)
/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::sample
 */
_Ret_ EMI_MEASUREMENT_DATA_V1 *PWROWG_DETAIL_NAMESPACE::emi_sensor::sample(
        _In_ EMI_MEASUREMENT_DATA_V1& measurement) const {
    this->check_not_disposed();

    if (this->version() != EMI_VERSION_V1) {
        throw std::invalid_argument("The given sensor does not use an EMIv1 "
            "device.");
    }

    detail::emi_sensor_impl::sample(this->_impl->device, &measurement,
        sizeof(measurement));
    return &measurement;
}
#endif /* defined(_WIN32) */


#if defined(_WIN32)
/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::sample
 */
_Ret_ EMI_MEASUREMENT_DATA_V2 *PWROWG_DETAIL_NAMESPACE::emi_sensor::sample(
        _Inout_updates_bytes_(size) EMI_MEASUREMENT_DATA_V2 *measurement,
        _In_ const std::size_t size) const {
    this->check_not_disposed();

    if (this->version() != EMI_VERSION_V2) {
        throw std::invalid_argument("The given sensor does not use an EMIv2 "
            "device.");
    }
    if (size < sizeof(EMI_MEASUREMENT_DATA_V2)) {
        throw std::invalid_argument("The output buffer must be able to hold at "
            "least the EMI_MEASUREMENT_DATA_V2 structure.");
    }

    detail::emi_sensor_impl::sample(this->_impl->device, measurement, size);
    return measurement;
}
#endif /* defined(_WIN32) */


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::version
 */
PWROWG_DETAIL_NAMESPACE::emi_sensor::version_type
PWROWG_DETAIL_NAMESPACE::emi_sensor::version(void) const noexcept {
#if defined(_WIN32)
    return (*this)
        ? this->_impl->device->version().EmiVersion
        : static_cast<decltype(EMI_VERSION::EmiVersion)>(0);
#else /* defined(_WIN32) */
    return 0;
#endif /* defined(_WIN32) */
}

/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::operator =
 */
PWROWG_DETAIL_NAMESPACE::emi_sensor&
PWROWG_DETAIL_NAMESPACE::emi_sensor::operator =(
        _In_ emi_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        delete this->_impl;
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::operator bool
 */
PWROWG_DETAIL_NAMESPACE::emi_sensor::operator bool(void) const noexcept {
#if defined(_WIN32)
    return ((this->_impl != nullptr) && (this->_impl->device != nullptr));
#else /* defined(_WIN32) */
    return false;
#endif /* defined(_WIN32) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::sample_async
 */
void PWROWG_DETAIL_NAMESPACE::emi_sensor::sample_async(
        _Inout_ async_sampling&& sampling) {
#if defined(_WIN32)
    assert(this->_impl != nullptr);

    if ((this->_impl->async_sampling = std::move(sampling))) {
        auto source = detail::emi_sensor_impl::sampler_source_type::create(
            this->_impl);
        detail::sampler::default_sampler += source;

    } else {
        detail::emi_sensor_impl::sampler_source_type::release(this->_impl);
    }

#else /* defined(_WIN32) */
    throw std::logic_error(ERROR_MSG_NOT_SUPPORTED);
#endif /* defined(_WIN32) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::emi_sensor::sample_sync
 */
PWROWG_DETAIL_NAMESPACE::measurement_data
PWROWG_DETAIL_NAMESPACE::emi_sensor::sample_sync(void) const {
#if defined(_WIN32)
    this->check_not_disposed();

    switch (this->version()) {
        case EMI_VERSION_V1: {
            EMI_MEASUREMENT_DATA_V1 s;
            detail::emi_sensor_impl::sample(this->_impl->device, &s, sizeof(s));
            return this->_impl->evaluate(s);
            }

        case EMI_VERSION_V2: {
            auto m = detail::emi_sensor_impl::sample(this->_impl->device);
            auto s = reinterpret_cast<EMI_MEASUREMENT_DATA_V2 *>(m.data());
            return this->_impl->evaluate(*s);
            }

        default:
            throw std::logic_error("The specified version of the Energy "
                "Meter Interface is not supported by the implementation.");
    }
#else /* defined(_WIN32) */
    throw std::logic_error(ERROR_MSG_NOT_SUPPORTED);
#endif /* defined(_WIN32) */
}

#endif

