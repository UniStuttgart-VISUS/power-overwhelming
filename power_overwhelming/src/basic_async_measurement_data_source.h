// <copyright file="basic_async_measurement_data_source.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "async_measurement_data_source.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Basic implementation of <see cref="async_measurement_data_source" />
    /// using the CRTP to direct the synchronous sampling to
    /// <typeparamref name="TDerived" />.
    /// </summary>
    /// <remarks>
    /// <para>This adapter class can be used to easily convert inherently
    /// synchronous sensors, like the NVML one, to asynchronous ones without
    /// special implementation effort. Sensors that are inherently asynchronous
    /// or require special handling (e.g. oscilloscopes and EMI, which sample
    /// multiple sources at once) should be manually implemented and not rely
    /// on this class.</para>
    /// </remarks>
    /// <typeparam name="TDerived">The derived implementation class that needs
    /// to provide a <c>sample</c> method and have a <c>sensor_name</c> field.
    /// </typeparam>
    template<class TDerived>
    class basic_async_measurement_data_source
            : public async_measurement_data_source {

    public:

        /// <inheritdoc />
        void deliver_async(void) const override;

        /// <inheritdoc />
        void update_async(_Inout_ async_sampling&& sampling) override;

    private:

        async_sampling _async_sampling;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "basic_async_measurement_data_source.h"
