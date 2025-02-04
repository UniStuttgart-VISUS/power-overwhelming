//// <copyright file="emi_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
//// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
//// Licensed under the MIT licence. See LICENCE file for details.
//// </copyright>
//// <author>Christoph Müller</author>
//
//#include "emi_sensor_impl.h"
//
//#include "visus/pwrowg/convert_string.h"
//#include "visus/pwrowg/timestamp.h"
//
//
//#if defined(_WIN32)
///*
// * visus::power_overwhelming::detail::emi_sensor_impl::sample
// */
//std::size_t visus::power_overwhelming::detail::emi_sensor_impl::sample(
//        _In_ emi_device_factory::device_type& device,
//        _Out_writes_(cnt) void *dst,
//        _In_ const ULONG cnt) {
//    assert(device != nullptr);
//    assert(dst != nullptr);
//
//    DWORD retval = 0;
//    if (!::DeviceIoControl(*device, IOCTL_EMI_GET_MEASUREMENT, nullptr, 0,
//            dst, cnt, &retval, 0)) {
//        throw std::system_error(::GetLastError(), std::system_category());
//    }
//
//    return retval;
//}
//
//
///*
// * visus::power_overwhelming::detail::emi_sensor_impl::sample
// */
//std::vector<std::uint8_t> visus::power_overwhelming::detail::emi_sensor_impl::sample(
//        _In_ emi_device_factory::device_type& device) {
//    std::vector<std::uint8_t> retval(0);
//
//    switch (device->version().EmiVersion) {
//        case EMI_VERSION_V1:
//            retval.resize(sizeof(EMI_MEASUREMENT_DATA_V1));
//            break;
//
//        case EMI_VERSION_V2: {
//            retval.resize(sizeof(EMI_MEASUREMENT_DATA_V2)
//                + device->metadata_as<EMI_METADATA_V2>()->ChannelCount
//                * sizeof(EMI_CHANNEL_MEASUREMENT_DATA));
//            break;
//        }
//    }
//
//    sample(device, retval.data(), retval.size());
//
//    return retval;
//}
//
//
///*
// * visus::power_overwhelming::detail::emi_sensor_impl::~emi_sensor_impl
// */
//visus::power_overwhelming::detail::emi_sensor_impl::~emi_sensor_impl(void) {
//    // Make sure that a sensor that is being destroyed is removed from all
//    // asynchronous sampling threads.
//    sampler_source_type::release(this);
//}
//
//
///*
// * visus::power_overwhelming::detail::emi_sensor_impl::evaluate
// */
//visus::power_overwhelming::measurement_data
//visus::power_overwhelming::detail::emi_sensor_impl::evaluate(
//        const EMI_CHANNEL_MEASUREMENT_DATA& data) {
//    const auto de = data.AbsoluteEnergy - this->last_energy;
//    const auto dt = data.AbsoluteTime - this->last_time;
//
//    this->last_energy = data.AbsoluteEnergy;
//    this->last_time = data.AbsoluteTime;
//
//    switch (this->unit) {
//        case EmiMeasurementUnitPicowattHours: {
//            // de / dt [pWh / 100ns]
//            // 1 [pW] = 10^-12 [W]
//            // 100 [ns] = 10^-7 [s]
//            auto value = static_cast<float>(de) * 0.036f;
//            value /= static_cast<float>(dt);
//
//            auto time = data.AbsoluteTime - dt / 2 + this->time_offset;
//
//            return measurement_data(timestamp(time), value);
//            }
//
//        default:
//            throw std::logic_error("The sensor uses an unsupported unit that "
//                "cannot be converted to Watts.");
//    }
//}
//
//
///*
// * visus::power_overwhelming::detail::emi_sensor_impl::evaluate
// */
//visus::power_overwhelming::measurement_data
//visus::power_overwhelming::detail::emi_sensor_impl::evaluate(
//        const std::vector<std::uint8_t>& data) {
//    switch (this->device->version().EmiVersion) {
//        case EMI_VERSION_V1:
//            assert(data.size() >= sizeof(EMI_MEASUREMENT_DATA_V1));
//            return this->evaluate(
//                *reinterpret_cast<const EMI_MEASUREMENT_DATA_V1 *>(data.data()));
//
//        case EMI_VERSION_V2:
//            assert(data.size() >= sizeof(EMI_MEASUREMENT_DATA_V2));
//            return this->evaluate(
//                *reinterpret_cast<const EMI_MEASUREMENT_DATA_V2 *>(data.data()));
//
//        default:
//            throw std::logic_error("The specified version of the Energy "
//                "Meter Interface is not supported by the implementation.");
//    }
//}
//
//
///*
// * visus::power_overwhelming::detail::emi_sensor_impl::evaluate_async
// */
//bool visus::power_overwhelming::detail::emi_sensor_impl::evaluate_async(
//        const std::vector<std::uint8_t>& data) {
//    if (this->async_sampling) {
//        return this->async_sampling.deliver(this->sensor_name.c_str(),
//            this->evaluate(data));
//    } else {
//        return false;
//    }
//}
//
//
///*
// * visus::power_overwhelming::detail::emi_sensor_impl::set
// */
//void visus::power_overwhelming::detail::emi_sensor_impl::set(
//        const std::shared_ptr<emi_device>& device,
//        const string_type& path,
//        const channel_type channel) {
//    assert(device != nullptr);
//    this->device = device;
//    this->path = path;
//    this->sensor_name = L"EMI/"
//        + power_overwhelming::convert_string<wchar_t>(this->path);
//
//    switch (this->device->version().EmiVersion) {
//        case EMI_VERSION_V1: {
//            // The channel is irrelevant for v1 sensors.
//            this->channel = 0;
//
//            auto md = this->device->metadata_as<EMI_METADATA_V1>();
//            this->unit = md->MeasurementUnit;
//
//            // We need to sample the sensor once in order to obtain a starting
//            // point that allows us to compute the difference between any two
//            // samples requested by the user.
//            EMI_MEASUREMENT_DATA_V1 m;
//            sample(this->device, &m, sizeof(m));
//            FILETIME t;
//            ::GetSystemTimePreciseAsFileTime(&t);
//
//            this->last_energy = m.AbsoluteEnergy;
//            this->last_time = m.AbsoluteTime;
//            this->time_offset = timestamp::from_file_time(t) - this->last_time;
//            } break;
//
//        case EMI_VERSION_V2: {
//            this->channel = channel;
//
//            auto md = this->device->metadata_as<EMI_METADATA_V2>();
//            if (this->channel >= md->ChannelCount) {
//                throw std::invalid_argument("The specified channel is "
//                    "invalid.");
//            }
//
//            // As for v1, obtain the initial sample now.
//            auto m = sample(this->device);
//            FILETIME t;
//            ::GetSystemTimePreciseAsFileTime(&t);
//
//            auto mm = reinterpret_cast<EMI_MEASUREMENT_DATA_V2 *>(m.data());
//            this->last_energy = mm->ChannelData[this->channel].AbsoluteEnergy;
//            this->last_time = mm->ChannelData[this->channel].AbsoluteTime;
//            this->time_offset = timestamp::from_file_time(t) - this->last_time;
//
//            // Determine the name of the channel and add it to the name of the
//            // sensor.
//            auto c = md->Channels;
//            for (auto i = 0; i < this->channel; ++i) {
//                c = EMI_CHANNEL_V2_NEXT_CHANNEL(c);
//            }
//
//            this->sensor_name += L"/";
//            this->sensor_name += c->ChannelName;
//
//            this->unit = c->MeasurementUnit;
//            } break;
//
//        default:
//            throw std::logic_error("The specified version of the Energy "
//                "Meter Interface is not supported by the implementation.");
//    }
//}
//#endif /* defined(_WIN32) */
