// <copyright file="emi_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#if defined(_WIN32)
#include <Windows.h>
#include <emi.h>
#include <tchar.h>
#endif /* defined(_WIN32) */

#include "sensor.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations */
    namespace detail { struct emi_sensor_impl; }

    /// <summary>
    /// Implementation of a power sensor using the Energy Meter Interface
    /// available in Windows 10 and above.
    /// </summary>
    class POWER_OVERWHELMING_API emi_sensor final : public sensor {

    public:

        /// <summary>
        /// The type used to identify a channel in EMIv2.
        /// </summary>
#if defined(_WIN32)
        typedef decltype(EMI_METADATA_V2::ChannelCount) channel_type;
#else /* defined(_WIN32) */
        typedef int channel_type;
#endif /* defined(_WIN32) */

        /// <summary>
        /// The type used for strings that are passed to the OS API.
        /// </summary>
#if defined(_WIN32)
        typedef TCHAR char_type;
#else /* defined(_WIN32) */
        typedef char char_type;
#endif /* defined(_WIN32) */

        /// <summary>
        /// The type used to store the version of the EMI.
        /// </summary>
#if defined(_WIN32)
        typedef decltype(EMI_VERSION::EmiVersion) version_type;
#else /* defined(_WIN32) */
        typedef int version_type;
#endif /* defined(_WIN32) */

        /// <summary>
        /// Create sensors for all devices that support the Energy Meter
        /// Interface.
        /// </summary>
        /// <param name="out_sensors">Receives the sensors, if not
        /// <c>nullptr</c>.</param>
        /// <param name="cnt_sensors">The available space in
        /// <paramref name="out_sensors" />.</param>
        /// <returns>The number of sensors available on the system, regardless
        /// of the size of the output array. If this number is larger than
        /// <paramref name="cntSensors" />, not all sensors have been returned.
        /// </returns>
        /// <exception cref="std::system_error">If enumerating or opening the
        /// devices failed.</exception>
        static std::size_t for_all(emi_sensor *out_sensors,
            const std::size_t cnt_sensors);

        /// <summary>
        /// Create sensors for all channels of all devices whose name matches
        /// the given regular expression.
        /// </summary>
        /// <param name="out_sensors">Receives the sensors, if not
        /// <c>nullptr</c>.</param>
        /// <param name="cnt_sensors">The available space in
        /// <paramref name="out_sensors" />.</param>
        /// <param name="channel">A regular expression for matching the name
        /// of the channel.</param>
        /// <returns>The number of sensors available on the system, regardless
        /// of the size of the output array. If this number is larger than
        /// <paramref name="cntSensors" />, not all sensors have been returned.
        /// </returns>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="channel" /> is <c>nullptr</c>.</exception>
        /// <exception cref="std::system_error">If enumerating or opening the
        /// devices failed.</exception>
        static std::size_t for_channel(emi_sensor *out_sensors,
            const std::size_t cnt_sensors, const wchar_t *channel);

        /// <summary>
        /// Create sensors for all devices whose name matches the given regular
        /// expression.
        /// </summary>
        /// <param name="out_sensors">Receives the sensors, if not
        /// <c>nullptr</c>.</param>
        /// <param name="cnt_sensors">The available space in
        /// <paramref name="out_sensors" />.</param>
        /// <param name="device">A regular expression for matching the name
        /// of the device.</param>
        /// <returns>The number of sensors available on the system, regardless
        /// of the size of the output array. If this number is larger than
        /// <paramref name="cntSensors" />, not all sensors have been returned.
        /// </returns>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="device" /> is <c>nullptr</c>.</exception>
        /// <exception cref="std::system_error">If enumerating or opening the
        /// devices failed.</exception>
        static std::size_t for_device(emi_sensor *out_sensors,
            const std::size_t cnt_sensors, const char_type *device);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        emi_sensor(void);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline emi_sensor(emi_sensor&& rhs) noexcept : _impl(rhs._impl) {
            rhs._impl = nullptr;
        }

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        virtual ~emi_sensor(void);

        /// <summary>
        /// Answer the channel that is actually sampled by this sensor.
        /// </summary>
        /// <returns>The index of the channel sampled by this sensor.</returns>
        channel_type channel(void) const;

        /// <summary>
        /// Answer the number of channels the underlying Energy Meter Interface
        /// device reads at once.
        /// </summary>
        /// <remarks>
        /// <para>This information is only relevant when using the raw sampling
        /// method.</para>
        /// </para>When performing raw sampling of EMIv2 data, the caller
        /// needs to provide sufficient buffer to write all channels at once.
        /// As the <c>EMI_MEASUREMENT_DATA_V2</c> only provides memory for the
        /// first channel, the caller must allocate a buffer that is sufficient
        /// to receive the remaining channels as reported by this method.</para>
        /// </remarks>
        /// <returns>The number of channels read at once.</returns>
        channel_type channels(void) const;

        /// <inheritdoc />
        virtual const wchar_t *name(void) const noexcept override;

        /// <inheritdoc />
        virtual measurement sample(
            const timestamp_resolution resolution) const override;

#if defined(_WIN32)
        /// <summary>
        /// Obtains a new sample from EMI using an IOCTL on the underlying
        /// device handle.
        /// </summary>
        /// <remarks>
        /// <para>The interpretation of sample is documented at
        /// https://learn.microsoft.com/en-us/windows/win32/api/emi/ns-emi-emi_channel_measurement_data
        /// </para>
        /// </remarks>
        /// <param name="measurement">Receives the measurement results.</param>
        /// <returns>A pointer to <paramref name="measurement" />.</returns>
        /// <exception cref="std::runtime_error">If the method is called on a
        /// sensor that has been disposed.</exception>
        /// <exception cref="std::invalid_argument">If the method is called on a
        /// sensor that uses a different version than EMIv1.</exception>
        /// <exception cref="std::system_error">If the IOCTL failed.</exception>
        EMI_MEASUREMENT_DATA_V1 *sample(
            EMI_MEASUREMENT_DATA_V1& measurement) const;
#endif /* defined(_WIN32) */

#if defined(_WIN32)
        /// <summary>
        /// Obtains a new sample from EMI using an IOCTL on the underlying
        /// device handle.
        /// </summary>
        /// <remarks>
        /// <para>The interpretation of sample is documented at
        /// https://learn.microsoft.com/en-us/windows/win32/api/emi/ns-emi-emi_measurement_data_v2
        /// </para>
        /// </remarks>
        /// <param name="measurement">Receives the measurement results.</param>
        /// <param name="size">The overall size of the buffer designated by
        /// <paramref name="measurement" />, including the structure itself.
        /// </param>
        /// <returns>A pointer to <paramref name="measurement" />.</returns>
        /// <exception cref="std::runtime_error">If the method is called on a
        /// sensor that has been disposed.</exception>
        /// <exception cref="std::invalid_argument">If the method is called on a
        /// sensor that uses a different version than EMIv2.</exception>
        /// <exception cref="std::system_error">If the IOCTL failed.</exception>
        EMI_MEASUREMENT_DATA_V2 *sample(EMI_MEASUREMENT_DATA_V2 *measurement,
            const std::size_t size) const;
#endif /* defined(_WIN32) */

        using sensor::sample;

        /// <summary>
        /// Answer the version of the Energy Meter Interface used by the sensor.
        /// </summary>
        /// <remarks>
        /// <para>The sensor behaves differently depending on the EMI version
        /// provided by the operating system: first, when using the raw
        /// version of the sampling method, the caller needs to know which
        /// structure to pass as input parameter. Second, when using EMI version
        /// 2, the sensor reads multiple channels at once.</para>
        /// </remarks>
        /// <param name=""></param>
        /// <returns></returns>
        version_type version(void) const noexcept;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        emi_sensor& operator =(emi_sensor&& rhs) noexcept;

        /// <inheritdoc />
        virtual operator bool(void) const noexcept override;

    private:

        detail::emi_sensor_impl *_impl;

        friend struct detail::emi_sensor_impl;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
