// <copyright file="emi_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cassert>
#include <map>
#include <memory>
#include <mutex>

#include "visus/pwrowg/emi_sensor.h"
#include "visus/pwrowg/measurement.h"
#include "visus/pwrowg/timestamp.h"

#include "device_sampler_source.h"
#include "emi_device_factory.h"
#include "sampler.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Private data container for the <see cref="emi_sensor" />.
    /// </summary>
    struct emi_sensor_impl final {

#if defined(_WIN32)
        /// <summary>
        /// The type used to identify a channel in EMIv2.
        /// </summary>
        typedef emi_sensor::channel_type channel_type;

        /// <summary>
        /// The type that EMI uses to store absolute energy.
        /// </summary>
        typedef decltype(EMI_CHANNEL_MEASUREMENT_DATA::AbsoluteEnergy)
            energy_type;

        /// <summary>
        /// The type of the asynchronous sampler source.
        /// </summary>
        typedef device_sampler_source<emi_sensor_impl,
            emi_device_factory::device_type> sampler_source_type;

        /// <summary>
        /// The type of string we use for Win32 API calls.
        /// </summary>
        typedef std::basic_string<emi_sensor::char_type> string_type;

        /// <summary>
        /// The type that EMI uses to store timestamps.
        /// </summary>
        /// <remarks>
        /// According to the documentation, absolute timestamps are in 100 ns
        /// units from an arbitrary starting point (probably the start of the
        /// system).
        /// </remarks>
        typedef decltype(EMI_CHANNEL_MEASUREMENT_DATA::AbsoluteTime)
            time_type;

        /// <summary>
        /// Creates sensors for all devices matching
        /// <paramref name="predicate" />.
        /// </summary>
        template<class TPredicate>
        static std::size_t create(emi_sensor *out_sensors,
            std::size_t cnt_sensors, TPredicate predicate);

        /// <summary>
        /// Obtains a sample from the given device by issuing the
        /// <c>IOCTL_EMI_GET_MEASUREMENT</c> I/O control request.
        /// </summary>
        /// <param name="device">The device to be sampled.</param>
        /// <param name="dst">Receives the sample.</param>
        /// <param name="cnt">The size of the buffer designated by
        /// <paramref name="dst" /> in bytes.</param>
        /// <returns>The actual size of the sample in bytes.</returns>
        static std::size_t sample(_In_ emi_device_factory::device_type& device,
            _Out_writes_(cnt) void *dst, _In_ const ULONG cnt);

        /// <summary>
        /// Obtains a sample from the given device by issuing the
        /// <c>IOCTL_EMI_GET_MEASUREMENT</c> I/O control request.
        /// </summary>
        /// <param name="device">The device to be sampled.</param>
        /// <returns>The sample obtained from the device. The caller must
        /// interpret the data according to the version reported by the
        /// underlying device.</returns>
        static std::vector<std::uint8_t> sample(
            _In_ emi_device_factory::device_type& device);

        /// <summary>
        /// Caches all devices and makes them accessible via their path.
        /// </summary>
        /// <remarks>
        /// For EMIv2 devices potenially having multiple channels, we do not
        /// want to open the same device for each channel, but reuse it in
        /// multiple sensors, if possible. This map enables us to find devices
        /// that have already been opened and reuse them for new sensors.
        /// </remarks>
        static std::map<string_type, std::shared_ptr<emi_device>> devices;

        /// <summary>
        /// A lock for protecting <see cref="emi_sensor_impl::devices" />
        /// against concurrent access.
        /// </summary>
        static std::mutex lock;

        /// <summary>
        /// The asynchronous sampling configuration.
        /// </summary>
        async_sampling async_sampling;

        /// <summary>
        /// The channel that is sampled by this sensor.
        /// </summary>
        channel_type channel;

        /// <summary>
        /// The RAII wrapper for the EMI device handle.
        /// </summary>
        emi_device_factory::device_type device;

        /// <summary>
        /// Remembers the absolute energy from when the sensor was last sampled.
        /// </summary>
        energy_type last_energy;

        /// <summary>
        /// Remembers the absolute time when the sensor was last sampled.
        /// </summary>
        time_type last_time;

        /// <summary>
        /// The path of the <see cref="device" />.
        /// </summary>
        string_type path;

        /// <summary>
        /// The sensor name.
        /// </summary>
        std::wstring sensor_name;

        /// <summary>
        /// The offset of the world clock time from the timestamps of the EMI
        /// sensor as computed for the first sample in
        /// <see cref="emi_sensor_impl::set" />.
        /// </summary>
        decltype(LARGE_INTEGER::QuadPart) time_offset;

        /// <summary>
        /// The unit of <see cref="last_energy" />.
        /// </summary>
        EMI_MEASUREMENT_UNIT unit;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline emi_sensor_impl(void) : channel(0), last_energy(0), last_time(0),
            time_offset(0), unit(EmiMeasurementUnitPicowattHours) { }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~emi_sensor_impl(void);

        /// <summary>
        /// Evaluate the given channel data and save them as the previous
        /// measurement in <see cref="emi_sensor_impl::last_energy" /> and
        /// <see cref="emi_sensor_impl::last_time" />.
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        measurement_data evaluate(const EMI_CHANNEL_MEASUREMENT_DATA& data);

        /// <summary>
        /// Evaluate the channel represented by this sensor with data from the
        /// given measurement and and same them as the previous measurement in
        /// <see cref="emi_sensor_impl::last_energy" /> and
        /// <see cref="emi_sensor_impl::last_time" />.
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        inline measurement_data evaluate(const EMI_MEASUREMENT_DATA_V2& data) {
            assert(this->channel < this->device->channels());
            return this->evaluate(data.ChannelData[this->channel]);
        }

        /// <summary>
        /// Evaluate the given channel data as the specified version of EMI data
        /// and  save them as the previous measurement in
        /// <see cref="emi_sensor_impl::last_energy" /> and
        /// <see cref="emi_sensor_impl::last_time" />.
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        measurement_data evaluate(const std::vector<std::uint8_t>& data);

        /// <summary>
        /// Evaluate the given channel data and deliver them to the registered
        /// asynchronous sampling callback.
        /// </summary>
        /// <param name="data"></param>
        bool evaluate_async(const std::vector<std::uint8_t>& data);

        /// <summary>
        /// Initialise the sensor.
        /// </summary>
        /// <remarks>
        /// <para>This method remembers all properties required for sampling the
        /// specified channel of the specified device; computes the
        /// human-readable name of the sensor; obtains an inital sample from the
        /// sensor, which allows us to have a unified measurement implementation
        /// that does not have to handle the special case of the first sample
        /// having no predecessor.</para>
        /// </remarks>
        /// <param name="device"></param>
        /// <param name="path"></param>
        /// <param name="channel"></param>
        void set(const std::shared_ptr<emi_device>& device,
            const string_type& path,
            const channel_type channel);
#endif /* defined(_WIN32) */
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "emi_sensor_impl.inl"
