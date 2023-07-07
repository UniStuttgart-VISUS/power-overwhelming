// <copyright file="rtx_instrumen.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/oscilloscope_acquisition_state.h"
#include "power_overwhelming/oscilloscope_channel.h"
#include "power_overwhelming/oscilloscope_edge_trigger.h"
#include "power_overwhelming/oscilloscope_quantity.h"
#include "power_overwhelming/oscilloscope_reference_point.h"
#include "power_overwhelming/oscilloscope_single_acquisition.h"
#include "power_overwhelming/oscilloscope_trigger.h"
#include "power_overwhelming/oscilloscope_waveform.h"
#include "power_overwhelming/oscilloscope_waveform_points.h"
#include "power_overwhelming/visa_instrument.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Specialisation for a Rohde &amp; Schwarz RTA/RTB oscilloscope.
    /// </summary>
    /// <remarks>
    /// <para>This specialisation only provides additional APIs for commonly
    /// used commands on the oscilloscopes. The rationale for exposing this
    /// in a separate public class rather than putting it in the sensor is
    /// twofold: First, there might be cases for controlling the oscilloscopes
    /// that are not related to Power Overwhelming sensors. By using this class,
    /// you can do that without reimplementing the logic for all of the methods
    /// in this class. Second, there are things that need to be configured
    /// only once, even if there are two sensors configured on a four-port
    /// oscilloscope. By iterating over all <see cref="rtx_instruments" />,
    /// these settings can be made easily without tracking the topology of
    /// the oscilloscope sensors manually.</para>
    /// </remarks>
    class POWER_OVERWHELMING_API rtx_instrument final
            : public visa_instrument {

    public:

        /// <summary>
        /// The product ID of the RTA and RTB series oscilloscopes.
        /// </summary>
        /// <remarks>
        /// This is the ID reported by the RTB2004 and RTA4004 devices we use at
        /// VISUS. If this does not work, use the RsVisaTester tool and discover
        /// the device via the &quot;Find Resource&quot; functionality. Do not
        /// forget to put the device in USB mode if discovering via USB.
        /// </remarks>
        static constexpr const char *product_id = "0x01D6";

        /// <summary>
        /// Initialises a new, but invalid instance.
        /// </summary>
        rtx_instrument(void);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <remarks>
        /// This constructor will set the name of the sensor to the identity
        /// string of the instrument, reset the instrument and clear any error
        /// state in the instrument.
        /// </remarks>
        /// <param name="path">The VISA resource path of the instrument.</param>
        /// <param name="timeout">The timeout for the connection attempt in
        /// milliseconds. This parameter defaults to
        /// <see cref="default_timeout" />.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="path" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="std::bad_alloc">If the memory for the sensor state
        /// could not be allocated.</exception>
        /// <exception cref="std::system_error">If the VISA library could not be
        /// loaded.</exception>
        /// <exception cref="visa_exception">If the sensor could not be
        /// initialised.</exception>
        rtx_instrument(_In_z_ const wchar_t *path,
            _In_ const timeout_type timeout = default_timeout);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <remarks>
        /// This constructor will set the name of the sensor to the identity
        /// string of the instrument, reset the instrument and clear any error
        /// state in the instrument.
        /// </remarks>
        /// <param name="path">The VISA resource path of the instrument.</param>
        /// <param name="timeout">The timeout for the connection attempt in
        /// milliseconds. This parameter defaults to
        /// <see cref="default_timeout" />.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="path" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="std::bad_alloc">If the memory for the sensor state
        /// could not be allocated.</exception>
        /// <exception cref="std::system_error">If the VISA library could not be
        /// loaded.</exception>
        /// <exception cref="visa_exception">If the sensor could not be
        /// initialised.</exception>
        rtx_instrument(_In_z_ const char *path,
            _In_ const timeout_type timeout = default_timeout);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="is_new_connection">Indicates whether a new connection
        /// to an instrument was established or an existing one was reused. If
        /// this parameter returns <c>false</c>, callers should be aware that
        /// multiple code paths might manipulate the instrument independently.
        /// </param>
        /// <param name="path">The VISA resource path of the instrument.</param>
        /// <param name="timeout">The timeout for the connection attempt in
        /// milliseconds. This parameter defaults to
        /// <see cref="default_timeout" />.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="path" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="std::bad_alloc">If the memory for the sensor state
        /// could not be allocated.</exception>
        /// <exception cref="std::system_error">If the VISA library could not be
        /// loaded.</exception>
        /// <exception cref="visa_exception">If the sensor could not be
        /// initialised.</exception>
        rtx_instrument(_Out_ bool& is_new_connection,
            _In_z_ const wchar_t *path,
            _In_ const timeout_type timeout = default_timeout);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="is_new_connection">Indicates whether a new connection
        /// to an instrument was established or an existing one was reused. If
        /// this parameter returns <c>false</c>, callers should be aware that
        /// multiple code paths might manipulate the instrument independently.
        /// </param>
        /// <param name="path">The VISA resource path of the instrument.</param>
        /// <param name="timeout">The timeout for the connection attempt in
        /// milliseconds. This parameter defaults to
        /// <see cref="default_timeout" />.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="path" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="std::bad_alloc">If the memory for the sensor state
        /// could not be allocated.</exception>
        /// <exception cref="std::system_error">If the VISA library could not be
        /// loaded.</exception>
        /// <exception cref="visa_exception">If the sensor could not be
        /// initialised.</exception>
        rtx_instrument(_Out_ bool& is_new_connection,
            _In_z_ const char *path,
            _In_ const timeout_type timeout = default_timeout);

        /// <summary>
        /// Configures signle acquisition mode on the device.
        /// </summary>
        /// <param name="acquisition">The configuration of single acquisition
        /// mode.</param>
        /// <param name="run">If <c>true</c>, start the acquisiton. This
        /// parameter defaults to <c>false</c>.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the instument has been
        /// disposed by a move.</exception>
        /// <exception cref="visa_exception">If a VISA call failed.</exception>
        rtx_instrument& acquisition(
            _In_ const oscilloscope_single_acquisition& acquisition,
            _In_ const bool run = false);

        /// <summary>
        /// Changes the acquisition state of the instrument.
        /// </summary>
        /// <param name="state">The new state of the instrument.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the instument has been
        /// disposed by a move.</exception>
        /// <exception cref="visa_exception">If a VISA call failed.</exception>
        rtx_instrument& acquisition(
            _In_ const oscilloscope_acquisition_state state);

#if false
        /// <summary>
        /// 
        /// </summary>
        /// <param name="channel"></param>
        /// <returns></returns>
        blob ascii_data(_In_ const std::uint32_t channel);
#endif

        /// <summary>
        /// 
        /// </summary>
        /// <param name="channel"></param>
        /// <returns></returns>
        blob binary_data(_In_ const std::uint32_t channel);

        /// <summary>
        /// Apply the specified channel configuration.
        /// </summary>
        /// <remarks>
        /// <para>This method does nothing if the library has been compiled
        /// without VISA support.</para>
        /// </remarks>
        /// <param name="channel">The channel configuration to apply.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::system_error">If the VISA library could not be
        /// loaded.</exception>
        /// <exception cref="visa_exception">If the sensor could not be
        /// initialised.</exception>
        rtx_instrument& channel(_In_ const oscilloscope_channel& channel);

        /// <summary>
        /// Retrieves the waveform data for the specified channel.
        /// </summary>
        /// <param name="channel">The one-based index of the channel to retrieve
        /// the waveform for.</param>
        /// <param name="points">Specifies which sample points should be
        /// transferred.</param>
        /// <returns>The waveform for the specified channel.</returns>
        oscilloscope_waveform data(_In_ const std::uint32_t channel,
            _In_ const oscilloscope_waveform_points points);

        /// <summary>
        /// Enable and configure one of the mathematical expressions.
        /// </summary>
        /// <param name="channel">The maths channel to be configured. For an
        /// RTB2004, this must be within [1, 4].</param>
        /// <param name="expression">The arithmetic expression to be computed,
        /// ie &quot;CH1*CH2&quot;.</param>
        /// <param name="unit">The unit of the resulting values. If
        /// <c>nullptr</c>, the currently set unit will be unchanged. This
        /// parameter defaults to <c>nullptr</c>.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& expression(_In_ const std::uint32_t channel,
            _In_opt_z_ const wchar_t *expression,
            _In_opt_z_ const wchar_t *unit = nullptr);

        /// <summary>
        /// Enable and configure one of the mathematical expressions.
        /// </summary>
        /// <param name="channel">The maths channel to be configured. For an
        /// RTB2004, this must be within [1, 4].</param>
        /// <param name="expression">The arithmetic expression to be computed,
        /// ie &quot;CH1*CH2&quot;.</param>
        /// <param name="unit">The unit of the resulting values. If
        /// <c>nullptr</c>, the currently set unit will be unchanged. This
        /// parameter defaults to <c>nullptr</c>.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& expression(_In_ const std::uint32_t channel,
            _In_opt_z_ const char *expression,
            _In_opt_z_ const char *unit = nullptr);

        /// <summary>
        /// Queries the currently displayed history segment index.
        /// </summary>
        /// <returns>The history segment index currently displayed.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the library was compiled without support for VISA.</exception>
        int history_segment(void) const;

        /// <summary>
        /// Accesses a specific history segment in the memory.
        /// </summary>
        /// <param name="channel">The one-based channel index.</param>
        /// <param name="segment">The segment index, which can either be a
        /// negative index count where the latest segment is 0 and the older
        /// segments have a negative index, or positive index cound where the
        /// oldest segment has index 1 and the newest has index <c>n</c> where
        /// is the number of segments returned by
        /// <see cref="history_segments" />.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& history_segment(_In_ const int segment);

        /// <summary>
        /// Gets the number of history segments currently available in memory.
        /// </summary>
        /// <returns>The number of history segments in memory.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the library was compiled without support for VISA.</exception>
        std::size_t history_segments(void) const;

        /// <summary>
        /// Sets the reference point in the diagram.
        /// </summary>
        /// <param name="position">The location of the reference point on the
        /// horizontal axis, which can be the left side, the middle or the
        /// right side.</param>
        /// <returns><c>*this</c>.</returns>
        rtx_instrument& reference_position(
            _In_ const oscilloscope_reference_point position);

        /// <summary>
        /// Sets the time range of a single acquisition covering all grid
        ///  divisions.
        /// </summary>
        /// <param name="scale">Time scale within [250e-12, 500].</param>
        /// <returns><c>*this</c>.</returns>
        rtx_instrument& time_range(_In_ const oscilloscope_quantity& scale);

        /// <summary>
        /// Sets the horizontal scale for all channels in time units per grid
        /// division.
        /// </summary>
        /// <param name="scale">Time scale within [1e-9, 50].</param>
        /// <returns><c>*this</c>.</returns>
        rtx_instrument& time_scale(_In_ const oscilloscope_quantity& scale);

        /// <summary>
        /// Configures the trigger.
        /// </summary>
        /// <param name="trigger">The trigger configuration.</param>
        /// <returns><c>*this</c>.</returns>
        rtx_instrument& trigger(_In_ const oscilloscope_trigger& trigger);

        /// <summary>
        /// Forces a manual trigger.
        /// </summary>
        /// <returns><c>*this</c>.</returns>
        rtx_instrument& trigger(void);

        /// <summary>
        /// Sets the trigger position, which is the time distance from the
        /// trigger point to the reference point.
        /// </summary>
        /// <remarks>
        /// <para>The trigger point is the horizontal origin of the diagram.
        /// Changing the horizontal position you can move the trigger, even
        /// outside the screen.</para>
        /// </remarks>
        /// <param name="offset">The offset of the trigger point.</param>
        /// <returns><c>*this</c>.</returns>
        rtx_instrument& trigger_position(
            _In_ const oscilloscope_quantity& offset);

        /// <summary>
        /// Sets the unit of the specified channel.
        /// </summary>
        /// <param name="channel">The number (starting at 1) of the channel to
        /// be configured.</param>
        /// <param name="unit">The unit being measured (either &quot;A&quot;
        /// or &quot;V&quot;).</param>
        /// <exception cref="std::invalid_argument">If <paramref name="unit" />
        /// is <c>nullptr</c>.</exception>
        /// <returns><c>*this</c>.</returns>
        rtx_instrument& unit(_In_ const std::uint32_t channel,
            _In_z_ const wchar_t *unit);

        /// <summary>
        /// Sets the unit of the specified channel.
        /// </summary>
        /// <param name="channel">The number (starting at 1) of the channel to
        /// be configured.</param>
        /// <param name="unit">The unit being measured (either &quot;A&quot;
        /// or &quot;V&quot;).</param>
        /// <exception cref="std::invalid_argument">If <paramref name="unit" />
        /// is <c>nullptr</c>.</exception>
        /// <returns><c>*this</c>.</returns>
        rtx_instrument& unit(_In_ const std::uint32_t channel,
            _In_z_ const char *unit);
    };

} /* namespace power_overwhelming */
} /* namespace visus */
