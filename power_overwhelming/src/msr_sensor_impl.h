// <copyright file="msr_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/msr_sensor.h"
#include "power_overwhelming/measurement.h"

#include "io_util.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Private data container for the <see cref="msr_sensor" />.
    /// </summary>
    struct msr_sensor_impl final {

        /// <summary>
        /// The type of data read from the MSR file.
        /// </summary>
        typedef std::uint64_t sample_type;

        /// <summary>
        /// The handle to the MSR file.
        /// </summary>
        int handle;

        /// <summary>
        /// A sampler for MSR sensors.
        /// </summary>
        //static detail::sampler<emi_sampler_context> sampler;

        /// <summary>
        /// The sensor name.
        /// </summary>
        std::wstring sensor_name;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline msr_sensor_impl(void) : handle(-1) { }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~msr_sensor_impl(void);

        /// <summary>
        /// Closes <see cref="handle" /> if it is open.
        /// </summary>
        void close(void) noexcept;

        /// <summary>
        /// Open the MSR file for the given core.
        /// </summary>
        /// <remarks>
        /// It is safe to call the method if <see cref="handle" /> is already
        /// open, in which case the existing handle will be closed.
        /// </remarks>
        /// <param name="core">The core to open the MSR file for.</param>
        /// <exception cref="std::system_error">If the MSR file for the given
        /// core could not be opened.</exception>
        void open(_In_ const std::uint32_t core);

        /// <summary>
        /// Reads a sample from <see cref="handle" />.
        /// </summary>
        /// <param name="which">The RAPL domain to read, which is equivalent
        /// to the offset into the file.</param>
        /// <returns>The content of the MSR file.</returns>
        /// <exception cref="std::system_error">If reading the MSR file failed.
        /// </exception>
        sample_type read(_In_ const rapl_domain which);

    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
