// <copyright file="emi_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "emi_sensor_impl.h"

#include <cassert>


#if defined(_WIN32)
/*
 * visus::power_overwhelming::detail::emi_sensor_impl::get_metadata
 */
std::pair<EMI_VERSION, std::vector<std::uint8_t>>
visus::power_overwhelming::detail::emi_sensor_impl::get_metadata(
        HANDLE device) {
    EMI_METADATA_SIZE size;
    EMI_VERSION version;

    // Determine the EMI version, which we need to know to interpret
    // the metadata that we retrieve next.
    {
        DWORD cnt_returned = 0;
        if (!::DeviceIoControl(device, IOCTL_EMI_GET_VERSION, nullptr, 0,
                &version, sizeof(version), &cnt_returned, 0)) {
            throw std::system_error(::GetLastError(), std::system_category());
        }
        assert(cnt_returned == sizeof(version));
    }

    // Find out how big the metadata are.
    {
        DWORD cnt_returned = 0;
        if (!::DeviceIoControl(device, IOCTL_EMI_GET_METADATA_SIZE, nullptr, 0,
                &size, sizeof(size), &cnt_returned, 0)) {
            throw std::system_error(::GetLastError(), std::system_category());
        }
        assert(cnt_returned == sizeof(size));
    }

    // Retrieve the metadata.
    std::vector<std::uint8_t> metadata(size.MetadataSize);
    {
        DWORD cnt_returned = 0;
        if (!::DeviceIoControl(device, IOCTL_EMI_GET_METADATA, nullptr, 0,
                metadata.data(), size.MetadataSize, &cnt_returned, 0)) {
            throw std::system_error(::GetLastError(), std::system_category());
        }
        assert(cnt_returned == size.MetadataSize);
    }

    return std::make_pair(version, metadata);
}


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
    if (this->handle != INVALID_HANDLE_VALUE) {
        ::CloseHandle(this->handle);
    }
}


/*
 * visus::power_overwhelming::detail::emi_sensor_impl::open
 */
void visus::power_overwhelming::detail::emi_sensor_impl::open(
        HDEVINFO dev_info, SP_DEVICE_INTERFACE_DATA& interface_data,
        const ULONG channel) {
    if (this->handle != INVALID_HANDLE_VALUE) {
        throw std::logic_error("The sensor is already open.");
    }

    auto path = detail::get_device_path(dev_info, interface_data);

    this->handle = ::CreateFile(path.data(), GENERIC_READ, FILE_SHARE_READ,
        nullptr, OPEN_EXISTING, 0, NULL);
    if (this->handle != INVALID_HANDLE_VALUE) {
        this->sensor_name = L"EMI/" + path;
    }

    auto metadata = get_metadata(this->handle);
    this->metadata = std::move(metadata.second);
    this->version = metadata.first;
    
    auto mdv2 = reinterpret_cast<EMI_METADATA_V2 *>(this->metadata.data());

    /*
typedef struct
{
    EMI_MEASUREMENT_UNIT MeasurementUnit;
    WCHAR HardwareOEM[EMI_NAME_MAX];
    WCHAR HardwareModel[EMI_NAME_MAX];
    USHORT HardwareRevision;
    USHORT MeteredHardwareNameSize;
    WCHAR MeteredHardwareName[ANYSIZE_ARRAY];
} EMI_METADATA_V1;
    */

    /*
    typedef struct
{
    ULONGLONG AbsoluteEnergy;
    ULONGLONG AbsoluteTime;
} EMI_CHANNEL_MEASUREMENT_DATA;
*/

/*
typedef struct
{
    WCHAR HardwareOEM[EMI_NAME_MAX];
    WCHAR HardwareModel[EMI_NAME_MAX];
    USHORT HardwareRevision;
    USHORT ChannelCount;
    EMI_CHANNEL_V2 Channels[ANYSIZE_ARRAY];
} EMI_METADATA_V2;
*/

    int x = 5;
}


/*
 * visus::power_overwhelming::detail::emi_sensor_impl::sample
 */
std::size_t visus::power_overwhelming::detail::emi_sensor_impl::sample(
        void *dst, const ULONG cnt) {
    assert(dst != nullptr);

    DWORD retval = 0;
    if (!::DeviceIoControl(this->handle, IOCTL_EMI_GET_MEASUREMENT, nullptr, 0,
            dst, cnt, &retval, 0)) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    return retval;
}
#endif /* defined(_WIN32) */
