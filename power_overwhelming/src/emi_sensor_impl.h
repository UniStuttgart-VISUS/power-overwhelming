// <copyright file="emi_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cassert>
#include <map>
#include <memory>
#include <mutex>

#include "power_overwhelming/emi_sensor.h"
#include "power_overwhelming/measurement.h"

#include "emi_device_factory.h"
#include "emi_sampler_context.h"
#include "sampler.h"
#include "timestamp.h"


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
        /// A sampler for EMI sensors.
        /// </summary>
        static detail::sampler<emi_sampler_context> sampler;

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
        /// The size of a raw sample obtained from the this sensor in bytes.
        /// </summary>
        std::size_t sample_size;

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
            sample_size(0), time_offset(0),
            unit(EmiMeasurementUnitPicowattHours) { }

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
        /// <param name="resolution"></param>
        /// <returns></returns>
        measurement_data evaluate(const EMI_CHANNEL_MEASUREMENT_DATA& data,
            const timestamp_resolution resolution);

        /// <summary>
        /// Evaluate the channel represented by this sensor with data from the
        /// given measurement and and same them as the previous measurement in
        /// <see cref="emi_sensor_impl::last_energy" /> and
        /// <see cref="emi_sensor_impl::last_time" />.
        /// </summary>
        /// <param name="data"></param>
        /// <param name="resolution"></param>
        /// <returns></returns>
        inline measurement_data evaluate(const EMI_MEASUREMENT_DATA_V2& data,
                const timestamp_resolution resolution) {
            assert(this->channel < this->device->channels());
            return this->evaluate(data.ChannelData[this->channel],
                resolution);
        }

        /// <summary>
        /// Evaluate the given channel data as the specified version of EMI data
        /// and  save them as the previous measurement in
        /// <see cref="emi_sensor_impl::last_energy" /> and
        /// <see cref="emi_sensor_impl::last_time" />.
        /// </summary>
        /// <param name="data"></param>
        /// <param name="version"></param>
        /// <param name="resolution"></param>
        /// <returns></returns>
        measurement_data evaluate(const std::vector<std::uint8_t>& data,
            const emi_sensor::version_type version,
            const timestamp_resolution resolution);

        /// <summary>
        /// Obtains a sample from the sensor by issuing the
        /// <c>IOCTL_EMI_GET_MEASUREMENT</c> I/O control request on the device.
        /// </summary>
        /// <param name="dst">Receives the sample.</param>
        /// <param name="cnt">The size of the buffer designated by
        /// <paramref name="dst" /> in bytes.</param>
        /// <returns>The actual size of the sample in bytes.</returns>
        std::size_t sample(void *dst, const ULONG cnt);

        /// <summary>
        /// Obtains a sample from the sensor by issuing the
        /// <c>IOCTL_EMI_GET_MEASUREMENT</c> I/O control request on the device.
        /// </summary>
        /// <returns>The sample obtained from the device. The caller must
        /// interpret the data according to the version reported by the
        /// underlying device.</returns>
        std::vector<std::uint8_t> sample(void);

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
