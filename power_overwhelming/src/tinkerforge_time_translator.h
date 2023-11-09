﻿// <copyright file="tinkerforge_time_translator.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <array>
#include <cassert>
#include <chrono>
#include <cinttypes>
#include <utility>

#include <bricklet_voltage_current_v2.h>

#include "power_overwhelming/power_overwhelming_api.h"
#include "power_overwhelming/timestamp_resolution.h"

#include "timestamp.h"
#include "tinkerforge_exception.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// A utility class for transforming timestamps from Tinkerforge bricklets
    /// into wall-clock timestamps.
    /// </summary>
    /// <remarks>
    /// This feature requires a special firmware on the Tinkerforge side.
    /// </remarks>
    class tinkerforge_time_translator final {

    public:

        /// <summary>
        /// The type of the timestamps from the bricklet.
        /// </summary>
        typedef std::uint32_t bricklet_time_type;

        /// <summary>
        /// The type of the bricklet that is supported by this class.
        /// </summary>
        typedef VoltageCurrentV2 bricklet_type;

        /// <summary>
        /// The type of a coordinated time comprising the current timestamp on
        /// the host and the time retrieved from the bricklet.
        /// </summary>
        typedef std::pair<timestamp_type, bricklet_time_type> times_type;

        /// <summary>
        /// Checks whether timestamps from the bricklet are supported, which
        /// requires two conditions to be met: first, the library must have been
        /// compiled with support for that (by setting the major firmware
        /// version we expect to support the feature) and the given bricklet
        /// must have the required firmware version.
        /// </summary>
        /// <param name="bricklet"></param>
        /// <returns></returns>
        static bool check_support(_In_ bricklet_type& bricklet) noexcept;

        /// <summary>
        /// Gets the coordinated times on the host and the bricklet.
        /// </summary>
        /// <param name="bricklet"></param>
        /// <returns></returns>
        /// <exception cref="tinkerforge_exception"></exception>
        static times_type get_coord_times(_In_ bricklet_type& bricklet);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        tinkerforge_time_translator(void) noexcept;

        /// <summary>
        /// Resets the calibration for the given bricklet by estimating the
        /// clock drift over the specified timespan.
        /// </summary>
        /// <remarks>
        /// <para>This method has no effect unless <see cref="check_support" />
        /// returns <c>true</c> for <paramref name="bricklet" />.</para>
        /// <para>Longer <paramref name="time_span" />s typically yield more
        /// reliable translations, but obviously take longer.</para>
        /// </remarks>
        /// <typeparam name="TRep></typeparam>
        /// <param name="bricklet"></param>
        /// <param name="time_span"></param>
        /// <returns></returns>
        template<class TRep> void reset(_In_ bricklet_type& bricklet,
            _In_ const std::chrono::duration<timestamp_type, TRep> time_span);

        /// <summary>
        /// Translates the given time from the bricklet into a timestamp of
        /// the specified resolution.
        /// </summary>
        /// <param name="time"></param>
        /// <returns></returns>
        timestamp_type translate(_In_ const bricklet_time_type time,
            _In_ const timestamp_resolution resolution);

        /// <summary>
        /// Updates the estimate of the offset and the scaling based on the
        /// time elapsed since the last <see cref="reset" />.
        /// </summary>
        /// <remarks>
        /// <para>This method must only be called if the times have been reset
        /// before.</para>
        /// <para>This method is relatively slow. Querying the time from the
        /// bricklet takes around 2 ms.</para>
        /// <para>This method does nothing if the bricklet does not support
        /// our modified firmware.</para>
        /// </remarks>
        /// <param name="bricklet"></param>
        /// <returns></returns>
        bool update(_In_ bricklet_type& bricklet) noexcept;

    private:

        /// <summary>
        /// The timestamp on the bricklet when the first calibration was
        /// performed in <see cref="reset " />.
        /// </summary>
        double _begin_bricklet;

        /// <summary>
        /// The timestamp on the host when the first calibration was performed
        /// in <see cref="reset " />.
        /// </summary>
        timestamp_type _begin_host;

        /// <summary>
        /// The wall-clock timestamp (in milliseconds) from the zero-point
        /// of the time reported by the bricklet with Moritz' custom firmware.
        /// </summary>
        timestamp_type _time_offset;

        /// <summary>
        /// Allows for adapting the slope of the bricklets clock to the system
        /// clock (the dübel constant).
        /// </summary>
        double _time_scale;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "tinkerforge_time_translator.inl"