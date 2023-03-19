// <copyright file="collector_settings.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>

#include "power_overwhelming/sensor.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Enapsulates the settings of a
    /// <see cref="visus::power_overwhelming::collector" />.
    /// </summary>
    class POWER_OVERWHELMING_API collector_settings final {

    public:

        /// <summary>
        /// The type used to specify sampling intervals in (microseconds).
        /// </summary>
        typedef sensor::microseconds_type sampling_interval_type;

        /// <summary>
        /// The default output path.
        /// </summary>
        static constexpr const wchar_t *default_output_path = L"output.csv";

        /// <summary>
        /// The default sampling interval of 5 milliseconds (or 5000
        /// microseconds).
        /// </summary>
        static constexpr sampling_interval_type default_sampling_interval
            = 5000;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name=""></param>
        collector_settings(void);

        /// <summary>
        /// Clone <paramref name="rhs" />.
        /// </summary>
        /// <param name="rhs">The object to be cloned.</param>
        collector_settings(_In_ const collector_settings& rhs);

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~collector_settings(void);

        /// <summary>
        /// Gets the path to the file where the collector should write its
        /// output to.
        /// </summary>
        /// <returns>The path to the output file.</returns>
        inline _Ret_z_ const wchar_t *output_path(void) const noexcept {
            return this->_output_path;
        }

        /// <summary>
        /// Sets the path to the file where the collector should write its
        /// output to.
        /// </summary>
        /// <param name="path">The path to the output file.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="output_path" /> is <c>nullptr</c>.</exception>
        collector_settings& output_path(_In_z_ const wchar_t *path);

        /// <summary>
        /// Gets the time interval in which the collector should sample the
        /// sensors.
        /// </summary>
        /// <returns>The sampling interval.</returns>
        inline sampling_interval_type sampling_interval(void) const noexcept {
            return this->_sampling_interval;
        }

        /// <summary>
        /// Sets the interval in which the collector should sample the sensors.
        /// </summary>
        /// <param name="interval">The sampling interval.</param>
        /// <returns><c>*this</c>.</returns>
        collector_settings& sampling_interval(
            _In_ const sampling_interval_type interval);

        /// <summary>
        /// Assignment.
        /// </summary>
        /// <param name="rhs">The right hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        collector_settings& operator =(_In_ const collector_settings& rhs);

    private:

        wchar_t *_output_path;
        sampling_interval_type _sampling_interval;

    };

} /* namespace power_overwhelming */
} /* namespace visus */
