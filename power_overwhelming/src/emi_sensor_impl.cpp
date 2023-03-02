// <copyright file="emi_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "emi_sensor_impl.h"

#include "power_overwhelming/convert_string.h"

#include "filetime_period.h"
#include "timestamp.h"


#if defined(_WIN32)
/*
 * visus::power_overwhelming::detail::emi_sensor_impl::sampler
 */
visus::power_overwhelming::detail::sampler<
    visus::power_overwhelming::detail::default_sampler_context<
    visus::power_overwhelming::detail::emi_sensor_impl>>
visus::power_overwhelming::detail::emi_sensor_impl::sampler;


/*
 * visus::power_overwhelming::detail::emi_sensor_impl::~emi_sensor_impl
 */
visus::power_overwhelming::detail::emi_sensor_impl::~emi_sensor_impl(void) {
}


/*
 * visus::power_overwhelming::detail::emi_sensor_impl::evaluate
 */
visus::power_overwhelming::measurement
visus::power_overwhelming::detail::emi_sensor_impl::evaluate(
        const EMI_CHANNEL_MEASUREMENT_DATA& data,
        const timestamp_resolution resolution) {
    const auto de = data.AbsoluteEnergy - this->last_energy;
    const auto dt = data.AbsoluteTime - this->last_time;

    this->last_energy = data.AbsoluteEnergy;
    this->last_time = data.AbsoluteTime;

    switch (this->unit) {
        case EmiMeasurementUnitPicowattHours: {
            // de / dt [pWh / 100ns]
            // 1 [pW] = 10^-12 [W]
            // 100 [ns] = 10^-7 [s]
            auto value = static_cast<float>(de) * 0.036f;
            value /= static_cast<float>(dt);

            auto time = data.AbsoluteTime - dt / 2 + this->time_offset;
            time = convert(time, resolution);

            return measurement(this->sensor_name.c_str(), time, value);
            }

        default:
            throw std::logic_error("The sensor uses an unsupported unit that "
                "cannot be converted to Watts.");
    }
}


/*
 * visus::power_overwhelming::detail::emi_sensor_impl::sample
 */
std::size_t visus::power_overwhelming::detail::emi_sensor_impl::sample(
        void *dst, const ULONG cnt) {
    assert(this->device != nullptr);
    assert(dst != nullptr);

    DWORD retval = 0;
    if (!::DeviceIoControl(*this->device, IOCTL_EMI_GET_MEASUREMENT, nullptr, 0,
            dst, cnt, &retval, 0)) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    return retval;
}


/*
 * visus::power_overwhelming::detail::emi_sensor_impl::sample
 */
std::vector<std::uint8_t>
visus::power_overwhelming::detail::emi_sensor_impl::sample(void) {
    std::vector<std::uint8_t> retval(this->sample_size);
    this->sample(retval.data(), retval.size());
    return retval;
}


/*
 * visus::power_overwhelming::detail::emi_sensor_impl::set
 */
void visus::power_overwhelming::detail::emi_sensor_impl::set(
        const std::shared_ptr<emi_device>& device,
        const string_type& path,
        const channel_type channel) {
    assert(device != nullptr);
    this->device = device;
    this->sensor_name = L"EMI/"
        + power_overwhelming::convert_string<wchar_t>(path);

    switch (this->device->version().EmiVersion) {
        case EMI_VERSION_V1: {
            // The channel is irrelevant for v1 sensors.
            this->channel = 0;
            this->sample_size = sizeof(EMI_MEASUREMENT_DATA_V1);

            auto md = this->device->metadata_as<EMI_METADATA_V1>();
            this->unit = md->MeasurementUnit;

            // We need to sample the sensor once in order to obtain a starting
            // point that allows us to compute the difference between any two
            // samples requested by the user.
            EMI_MEASUREMENT_DATA_V1 m;
            this->sample(&m, sizeof(m));
            FILETIME t;
            ::GetSystemTimePreciseAsFileTime(&t);

            this->last_energy = m.AbsoluteEnergy;
            this->last_time = m.AbsoluteTime;
            this->time_offset = convert(t) - this->last_time;
            } break;

        case EMI_VERSION_V2: {
            this->channel = channel;

            auto md = this->device->metadata_as<EMI_METADATA_V2>();
            if (this->channel >= md->ChannelCount) {
                throw std::invalid_argument("The specified channel is "
                    "invalid.");
            }

            // Compute the size of a sample.
            assert(md->ChannelCount > 0);
            {
                auto extra = (md->ChannelCount - 1);
                this->sample_size = sizeof(EMI_MEASUREMENT_DATA_V2)
                    + extra * sizeof(EMI_CHANNEL_MEASUREMENT_DATA);
            }

            // As for v1, obtain the initial sample now.
            std::vector<std::uint8_t> m(this->sample_size);
            this->sample(m.data(), m.size());
            FILETIME t;
            ::GetSystemTimePreciseAsFileTime(&t);

            auto mm = reinterpret_cast<EMI_MEASUREMENT_DATA_V2 *>(m.data());
            this->last_energy = mm->ChannelData[this->channel].AbsoluteEnergy;
            this->last_time = mm->ChannelData[this->channel].AbsoluteTime;
            this->time_offset = convert(t) - this->last_time;

            // Determine the name of the channel and add it to the name of the
            // sensor.
            auto c = md->Channels;
            for (auto i = 0; i < this->channel; ++i) {
                c = EMI_CHANNEL_V2_NEXT_CHANNEL(c);
            }

            this->sensor_name += L"/";
            this->sensor_name += c->ChannelName;

            this->unit = c->MeasurementUnit;
            } break;

        default:
            throw std::logic_error("The specified version of the Energy "
                "Meter Interface is not supported by the implementation.");
    }
}
#endif /* defined(_WIN32) */
