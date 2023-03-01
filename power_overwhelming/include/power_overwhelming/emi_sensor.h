// <copyright file="emi_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#if defined(_WIN32)
#include <Windows.h>
#include <emi.h>
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
        static std::size_t for_all(emi_sensor *out_sensors,
            const std::size_t cnt_sensors);

#if 0

        /// <summary>
        /// Create a new instance for the device with the specified PCI bus ID.
        /// </summary>
        /// <param name="pciBusId"></param>
        /// <returns></returns>
        /// <exception cref="nvml_exception">If the specified device was not
        /// found, is not unique or another error occurred in NVML.</exception>
        static nvml_sensor from_bus_id(const char *pciBusId);

        /// <summary>
        /// Create a new instance for the device with the specified unique ID.
        /// </summary>
        /// <param name="guid"></param>
        /// <returns></returns>
        /// <exception cref="nvml_exception">If the specified device was not
        /// found, is not unique or another error occurred in NVML.</exception>
        static nvml_sensor from_guid(const char *guid);

        /// <summary>
        /// Create a new instance from a device index.
        /// </summary>
        /// <remarks>
        /// <para>Device indices start at zero and go up to the number of
        /// supported NVIDIA cards minus one.</para>
        /// <para>Please note that the indices may not match the indices of
        /// CUDA devices and/or DXGI adapters.</para>
        /// </remarks>
        /// <param name="index"></param>
        /// <returns></returns>
        /// <exception cref="nvml_exception">If the specified device was not
        /// found, is not unique or another error occurred in NVML.</exception>
        static nvml_sensor from_index(const unsigned int index);

        /// <summary>
        /// Create a new instance for a specific device serial number printed on
        /// the board.
        /// </summary>
        /// <param name="serial"></param>
        /// <returns></returns>
        /// <exception cref="nvml_exception">If the specified device was not
        /// found, is not unique or another error occurred in NVML.</exception>
        static nvml_sensor from_serial(const char *serial);
#endif

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

        /// <inheritdoc />
        virtual const wchar_t *name(void) const noexcept override;

        /// <inheritdoc />
        virtual measurement sample(
            const timestamp_resolution resolution) const override;

        /// <summary>
        /// Obtains a new sample from EMI using an IOCTL on the underlying
        /// device handle.
        /// </summary>
        /// <param name="measurement">Receives the measurement results.</param>
        /// <returns>A pointer to <paramref name="measurement" />.</returns>
        /// <exception cref="std::runtime_error">If the method is called on a
        /// sensor that has been disposed.</exception>
        /// <exception cref="std::invalid_argument">If the method is called on a
        /// sensor that uses a different version than EMIv1.</exception>
        /// <exception cref="std::system_error">If the IOCTL failed.</exception>
        EMI_MEASUREMENT_DATA_V1 *sample(
            EMI_MEASUREMENT_DATA_V1& measurement) const;

        /// <summary>
        /// Obtains a new sample from EMI using an IOCTL on the underlying
        /// device handle.
        /// </summary>
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
        EMI_MEASUREMENT_DATA_V2 *sample(void *measurement,
            const std::size_t size) const;

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
        decltype(EMI_VERSION::EmiVersion) version(void) const noexcept;

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

    };

} /* namespace power_overwhelming */
} /* namespace visus */
