// <copyright file="emi_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <xutility>

#include "sampler.h"
#include "setup_api.h"
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
        /// Gets the EMI metadata for the given device.
        /// </summary>
        /// <param name="device"></param>
        /// <returns></returns>
        static std::pair<EMI_VERSION, std::vector<std::uint8_t>> get_metadata(
            HANDLE device);

        /// <summary>
        /// A sampler for EMI sensors.
        /// </summary>
        static sampler<default_sampler_context<emi_sensor_impl>> sampler;

        /// <summary>
        /// The file handle for the sensor source, which is queried by the
        /// EMI IOCTLs.
        /// </summary>
        HANDLE handle;

        /// <summary>
        /// A buffer holding the EMI metadata.
        /// </summary>
        /// <remarks>
        /// The content of the buffer is dependent on the
        /// <see cref="emi_sensor_impl::version" />. See
        /// https://learn.microsoft.com/en-us/windows/win32/api/emi/ni-emi-ioctl_emi_get_metadata
        /// for details.
        /// </remarks>
        std::vector<std::uint8_t> metadata;

        /// <summary>
        /// The sensor name.
        /// </summary>
        std::wstring sensor_name;

        /// <summary>
        /// The EMI version of the sensor.
        /// </summary>
        EMI_VERSION version;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline emi_sensor_impl(void) : handle(INVALID_HANDLE_VALUE),
            version({ 0 }) { }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~emi_sensor_impl(void);

        void open(HDEVINFO dev_info, SP_DEVICE_INTERFACE_DATA& interface_data,
            const ULONG channel);

        std::size_t sample(void *dst, const ULONG cnt);
#endif /* defined(_WIN32) */
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
