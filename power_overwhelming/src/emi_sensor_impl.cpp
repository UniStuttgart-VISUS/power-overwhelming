// <copyright file="emi_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "emi_sensor_impl.h"

#include <cassert>

#include "power_overwhelming/convert_string.h"


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

//
///*
// * visus::power_overwhelming::detail::emi_sensor_impl::open
// */
//void visus::power_overwhelming::detail::emi_sensor_impl::open(
//        HDEVINFO dev_info, SP_DEVICE_INTERFACE_DATA& interface_data,
//        const ULONG channel) {
//    if (this->handle != INVALID_HANDLE_VALUE) {
//        throw std::logic_error("The sensor is already open.");
//    }
//
//    auto path = detail::get_device_path(dev_info, interface_data);
//
//    this->handle = ::CreateFile(path.data(), GENERIC_READ, FILE_SHARE_READ,
//        nullptr, OPEN_EXISTING, 0, NULL);
//    if (this->handle != INVALID_HANDLE_VALUE) {
//        this->sensor_name = L"EMI/" + path;
//    }
//
//    auto metadata = get_metadata(this->handle);
//    this->metadata = std::move(metadata.second);
//    this->version = metadata.first;
//    
//    auto mdv2 = reinterpret_cast<EMI_METADATA_V2 *>(this->metadata.data());
//
//    /*
//typedef struct
//{
//    EMI_MEASUREMENT_UNIT MeasurementUnit;
//    WCHAR HardwareOEM[EMI_NAME_MAX];
//    WCHAR HardwareModel[EMI_NAME_MAX];
//    USHORT HardwareRevision;
//    USHORT MeteredHardwareNameSize;
//    WCHAR MeteredHardwareName[ANYSIZE_ARRAY];
//} EMI_METADATA_V1;
//    */
//
//    /*
//    typedef struct
//{
//    ULONGLONG AbsoluteEnergy;
//    ULONGLONG AbsoluteTime;
//} EMI_CHANNEL_MEASUREMENT_DATA;
//*/
//
///*
//typedef struct
//{
//    WCHAR HardwareOEM[EMI_NAME_MAX];
//    WCHAR HardwareModel[EMI_NAME_MAX];
//    USHORT HardwareRevision;
//    USHORT ChannelCount;
//    EMI_CHANNEL_V2 Channels[ANYSIZE_ARRAY];
//} EMI_METADATA_V2;
//*/
//
//    int x = 5;
//}


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
 * visus::power_overwhelming::detail::emi_sensor_impl::set
 */
void visus::power_overwhelming::detail::emi_sensor_impl::set(
        const std::shared_ptr<emi_device>& device,
        const std::basic_string<TCHAR>& path,
        const std::uint16_t channel) {
    assert(device != nullptr);
    this->device = device;
    this->sensor_name = L"EMI/"
        + power_overwhelming::convert_string<wchar_t>(path);

    switch (this->device->version().EmiVersion) {
        case EMI_VERSION_V1:
            // Nothing to do for EMIv1 as it has only one channel.
            break;

        case EMI_VERSION_V2: {
            auto md = this->device->metadata_as<EMI_METADATA_V2>();
            if (channel >= md->ChannelCount) {
                throw std::invalid_argument("The specified channel is "
                    "invalid.");
            }

            auto c = md->Channels;
            for (auto i = 0; i < channel; ++i) {
                // DAFUQ?! Who does that?! Cf.
                // https://learn.microsoft.com/en-us/windows/win32/api/emi/ns-emi-emi_channel_v2
                auto b = reinterpret_cast<const std::uint8_t *>(c->ChannelName);
                b += c->ChannelNameSize;
                c = reinterpret_cast<const EMI_CHANNEL_V2 *>(b);
            }

            this->sensor_name += L"/";
            this->sensor_name += c->ChannelName;
            } break;

        default:
            throw std::logic_error("The specified version of the Energy "
                "Metering Interface is not supported by the implementation.");
    }
}
#endif /* defined(_WIN32) */
