// <copyright file="instrument_range.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines how the range setters of the <see cref="hmc8015_sensor" />
    /// behave.
    /// </summary>
    enum class instrument_range {

        /// <summary>
        /// Determine the measurement range automatically.
        /// </summary>
        /// <remarks>
        /// The instrument will adjust the measurement range by itself as
        /// necessary. However, if that happens, any integration of values will
        /// fail, wherefore it is reasonable to set an explicit or the maximum
        /// possible range if integration is desired.
        /// </remarks>
        automatically,

        /// <summary>
        /// Use the explicitly set range.
        /// </summary>
        /// <remarks>
        /// A valid value for the range must be provided in this case. Consult
        /// the documentation of the instrument to find out what valid values
        /// for the quantity in question are.
        /// </remarks>
        explicitly,

        /// <summary>
        /// Use the minimum possible range.
        /// </summary>
        minimum,

        /// <summary>
        /// Use the maximum possible range.
        /// </summary>
        maximum
    };

} /* namespace power_overwhelming */
} /* namespace visus */
