// <copyright file="adl_throttling_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/throttling_sensor.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations */
    namespace detail { struct adl_sensor_impl; }

    /// <summary>
    /// Defines a sensor for obtaining the throttling state of an AMD GPU.
    /// </summary>
    class POWER_OVERWHELMING_API adl_throttling_sensor final
            : public throttling_sensor {

    public:

        /// <summary>
        /// Initialises a new, but invalid, instance.
        /// </summary>
        adl_throttling_sensor(void) noexcept;

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs"></param>
        /// <returns></returns>
        inline adl_throttling_sensor(
                _Inout_ adl_throttling_sensor&& rhs) noexcept
                : _impl(rhs._impl) {
            rhs._impl = nullptr;
        }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        virtual ~adl_throttling_sensor(void);

        /// <inheritdoc />
        _Ret_maybenull_z_ const wchar_t *name(void) const noexcept override;

        /// <inheritdoc />
        throttling_sample sample(_In_ const timestamp_resolution resolution
            = timestamp_resolution::milliseconds) const;

        /// <inheritdoc />
        void sample(_Inout_ async_sampling&& async_sampling) override;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        adl_throttling_sensor& operator =(
            _Inout_ adl_throttling_sensor&& rhs) noexcept;

        /// <inheritdoc />
        operator bool(void) const noexcept override;

    private:

        detail::adl_sensor_impl *_impl;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
