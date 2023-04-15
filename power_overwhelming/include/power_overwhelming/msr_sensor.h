// <copyright file="msr_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/msr_offsets.h"
#include "power_overwhelming/rapl_domain.h"
#include "power_overwhelming/sensor.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations */
    namespace detail { struct msr_sensor_impl; }

    /// <summary>
    /// Implementation of a power sensor using the MSR files for reading RAPL
    /// registers.
    /// </summary>
    class POWER_OVERWHELMING_API msr_sensor final : public sensor {

    public:

        /// <summary>
        /// Create sensors for all MSR files.
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
        static std::size_t for_all(
            _Out_writes_opt_(cnt_sensors) msr_sensor *out_sensors,
            _In_ const std::size_t cnt_sensors);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        msr_sensor(void);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline msr_sensor(_In_ msr_sensor&& rhs) noexcept : _impl(rhs._impl) {
            rhs._impl = nullptr;
        }

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        virtual ~msr_sensor(void);

        /// <inheritdoc />
        virtual _Ret_maybenull_z_ const wchar_t *name(
            void) const noexcept override;

        /// <inheritdoc />
        virtual measurement sample(
            _In_ const timestamp_resolution resolution) const override;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        msr_sensor& operator =(_In_ msr_sensor&& rhs) noexcept;

        /// <inheritdoc />
        virtual operator bool(void) const noexcept override;

    private:

        detail::msr_sensor_impl *_impl;

        friend struct detail::msr_sensor_impl;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
