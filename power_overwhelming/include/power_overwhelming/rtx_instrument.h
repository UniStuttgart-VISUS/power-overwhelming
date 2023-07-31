// <copyright file="rtx_instrument.h" company="Visualisierungsinstitut der Universität Stuttgart">
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
#include "power_overwhelming/oscilloscope_trigger_output.h"
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
        /// Retrieves all RTA and RTB instruments connected to the system.
        /// </summary>
        /// <param name="dst">Receives the instruments. It is safe to pass
        /// <c>nullptr</c>, in which case the number of instruments will be
        /// counted.</param>
        /// <param name="cnt">The number of elements in
        /// <paramref name="dst" />.</param>
        /// <param name="timeout">The timeout for establishing the connection,
        /// in milliseconds.</param>
        /// <returns>The number of instruments attached to the machine.
        /// </returns>
        /// <exception cref="visa_exception">If any of the API calls failed.
        /// </exception>
        static std::size_t all(
            _When_(dst != nullptr, _Out_writes_opt_(cnt)) rtx_instrument *dst,
            _In_ std::size_t cnt,
            _In_ const std::int32_t timeout = default_timeout);

        /// <summary>
        /// Creates a new istrument and invokes the given callback if the
        /// instrument was newly opened in contrast to be reused from other
        /// instances.
        /// </summary>
        /// <param name="path">The VISA resource path of the instrument.</param>
        /// <param name="on_new">The callback to be invoked if the instrument
        /// is new. If you only plan to reset the instrument, you can also
        /// use <see cref="create_and_reset_new" />.</param>
        /// <param name="context">A user-defined context pointer to be passed
        /// to the <see cref="on_new" /> callback.</param>
        /// <param name="timeout">The timeout for the connection attempt in
        /// milliseconds. This parameter defaults to
        /// <see cref="default_timeout" />.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="path" />
        /// is <c>nullptr</c> or if <paramref name="on_new" /> is
        /// <c>nullptr</c>.</exception>
        /// <exception cref="std::bad_alloc">If the memory for the sensor state
        /// could not be allocated.</exception>
        /// <exception cref="std::system_error">If the VISA library could not be
        /// loaded.</exception>
        /// <exception cref="visa_exception">If the instrument could not be
        /// initialised.</exception>
        static rtx_instrument create(_In_z_ const wchar_t *path,
            _In_ void (*on_new)(rtx_instrument&, void *),
            _In_opt_ void *context = nullptr,
            _In_ const timeout_type timeout = default_timeout);

        /// <summary>
        /// Creates a new istrument and invokes the given callback if the
        /// instrument was newly opened in contrast to be reused from other
        /// instances.
        /// </summary>
        /// <param name="path">The VISA resource path of the instrument.</param>
        /// <param name="on_new">The callback to be invoked if the instrument
        /// is new. If you only plan to reset the instrument, you can also
        /// use <see cref="create_and_reset_new" />.</param>
        /// <param name="context">A user-defined context pointer to be passed
        /// to the <see cref="on_new" /> callback.</param>
        /// <param name="timeout">The timeout for the connection attempt in
        /// milliseconds. This parameter defaults to
        /// <see cref="default_timeout" />.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="path" />
        /// is <c>nullptr</c> or if <paramref name="on_new" /> is
        /// <c>nullptr</c>.</exception>
        /// <exception cref="std::bad_alloc">If the memory for the sensor state
        /// could not be allocated.</exception>
        /// <exception cref="std::system_error">If the VISA library could not be
        /// loaded.</exception>
        /// <exception cref="visa_exception">If the sensor could not be
        /// initialised.</exception>
        static rtx_instrument create(_In_z_ const char *path,
            _In_ void (*on_new)(rtx_instrument&, void *),
            _In_opt_ void *context = nullptr,
            _In_ const timeout_type timeout = default_timeout);

        /// <summary>
        /// Creates a new istrument and perform a full reset of the device and
        /// the status and the error queue provided there is no other instrument
        /// instance running on the same hardware yet.
        /// </summary>
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
        static rtx_instrument create_and_reset_new(_In_z_ const wchar_t *path,
            _In_ const timeout_type timeout = default_timeout);

        /// <summary>
        /// Creates a new istrument and perform a full reset of the device and
        /// the status and the error queue provided there is no other instrument
        /// instance running on the same hardware yet.
        /// </summary>
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
        static rtx_instrument create_and_reset_new(_In_z_ const char *path,
            _In_ const timeout_type timeout = default_timeout);

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
        /// <para>This method will initialise a new instance of the instrument
        /// and reuse any shared connection that is already open for the
        /// given <paramref name="path" />. If you need to know whether the
        /// instrument is an alias, you can use the factory methods of the
        /// class, which allow you to know whether an existing connection was
        /// reused or this is the first connection to the instrument with the
        /// specified <paramref name="path" />. The factory methods allow you
        /// to perform one-time initialisation operations if the instrument
        /// is the first connection.</para>
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
        /// <para>This method will initialise a new instance of the instrument
        /// and reuse any shared connection that is already open for the
        /// given <paramref name="path" />. If you need to know whether the
        /// instrument is an alias, you can use the factory methods of the
        /// class, which allow you to know whether an existing connection was
        /// reused or this is the first connection to the instrument with the
        /// specified <paramref name="path" />. The factory methods allow you
        /// to perform one-time initialisation operations if the instrument
        /// is the first connection.</para>
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
        /// Configures single acquisition mode on the device.
        /// </summary>
        /// <remarks>
        /// The subset of the instrument's state configured by this method can
        /// be retrieved via the <see cref="single_acquisition" /> method. There
        /// is no way in C++ to safely return a polymorphic object without a
        /// heap allocation, so the caller needs to know which kind of
        /// acquisition information to retrieve. As it is strongly recommended
        /// to use only single acquisition mode for programmatically obtaining
        /// data from RTA/RTB instruments, it is safe to assume that the
        /// instrument is configured for single acquisition. However, the
        /// current design allows for future extensions of the API without
        /// breaking code if the need to configure additional types of
        /// acquisitions arises.
        /// </remarks>
        /// <param name="acquisition">The configuration of single acquisition
        /// mode.</param>
        /// <param name="run">If <c>true</c>, start the acquisiton. This
        /// parameter defaults to <c>false</c>.</param>
        /// <param name="wait">If <paramref name="run" /> is <c>true</c> and
        /// this parameter is set <c>true</c> as well, the method will add an
        /// <c>*OPC?</c> query and block the calling code until the acquisition
        /// has completed.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the instument has been
        /// disposed by a move.</exception>
        /// <exception cref="visa_exception">If a VISA call failed.</exception>
        rtx_instrument& acquisition(
            _In_ const oscilloscope_single_acquisition& acquisition,
            _In_ const bool run = false,
            _In_ const bool wait = false);

        /// <summary>
        /// Answer the current acquisition state of the instrument.
        /// </summary>
        /// <returns>The current acquisition state of the instrument.</returns>
        /// <exception cref="std::runtime_error">If the instance was disposed
        /// by moving it.</exception>
        /// <exception cref="visa_exception">If the sensor could not be
        /// initialised.</exception>
        /// <exception cref="std::logic_error">If the library was compiled
        /// without support for VISA.</exception>
        /// <exception cref="std::range_error">If the response of the instrument
        /// did not fall into the range of states that can be expressed by the
        /// <see cref="oscilloscope_acquisition_state" /> enumeration.
        /// </exception>
        oscilloscope_acquisition_state acquisition(void) const;

        /// <summary>
        /// Changes the acquisition state of the instrument.
        /// </summary>
        /// <param name="state">The new state of the instrument.</param>
        /// <param name="wait">If the <paramref name="state" /> parameter is
        /// <see cref="oscilloscope_acquisition_state::single" /> and this
        /// parameter is <c>true</c>, the method will issue an <c>*OPC?</c>
        /// query after the single acquisition causing the calling code to block
        /// until the acquisition completed. Likewise, if a continuous
        /// acquisition is stopped gracefully by
        /// <see cref="oscilloscope_acquisition_state::stop" />, an <c>*OPC?</c>
        /// query will be added causing the calling code to block until the
        /// acquisition actually ended.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the instument has been
        /// disposed by a move.</exception>
        /// <exception cref="visa_exception">If a VISA call failed.</exception>
        const rtx_instrument& acquisition(
            _In_ const oscilloscope_acquisition_state state,
            _In_ const bool wait = false) const;

#if false
        /// <summary>
        /// 
        /// </summary>
        /// <param name="channel"></param>
        /// <returns></returns>
        blob ascii_data(_In_ const std::uint32_t channel);
#endif

        /// <summary>
        /// Makes the instrument beep.
        /// </summary>
        /// <remarks>
        /// This method has no effect if the library was compiled without
        /// support for VISA.
        /// </remarks>
        /// <param name="cnt">The number of times the method should beep. This
        /// defaults to one.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& beep(_In_ const std::size_t cnt = 1);

        /// <summary>
        /// Answer whether the instrument beeps if it encounters an error.
        /// </summary>
        /// <remarks>
        /// The answer will always be <c>false</c> if the library was compiled
        /// without support for VISA.
        /// </remarks>
        /// <returns><c>true</c> if the beep is enabled, <c>false</c> otherwise.
        /// </returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        bool beep_on_error(void);

        /// <summary>
        /// Configures the instrument to beep or not to beep if it encounters
        /// an error.
        /// </summary>
        /// <remarks>
        /// This method has no effect if the library was compiled without
        /// support for VISA.
        /// </remarks>
        /// <param name="enable">Set <c>true</c> to enable beeps on errors,
        /// <c>false</c> to disable them.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& beep_on_error(_In_ const bool enable);

        /// <summary>
        /// Answer whether the instrument beeps if a trigger occurs.
        /// </summary>
        /// <remarks>
        /// The answer will always be <c>false</c> if the library was compiled
        /// without support for VISA.
        /// </remarks>
        /// <returns><c>true</c> if the beep is enabled, <c>false</c> otherwise.
        /// </returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        bool beep_on_trigger(void);

        /// <summary>
        /// Configures the instrument to beep or not to beep if a trigger
        /// occurs.
        /// </summary>
        /// <remarks>
        /// This method has no effect if the library was compiled without
        /// support for VISA.
        /// </remarks>
        /// <param name="enable">Set <c>true</c> to enable beeps on triggers,
        /// <c>false</c> to disable them.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& beep_on_trigger(_In_ const bool enable);

        /// <summary>
        /// Downloads the data of the specified channel as floating-point
        /// numbers.
        /// </summary>
        /// <param name="channel">The one-based index of the channel to
        /// retrieve.</param>
        /// <returns>The channel data as a series of <c>float</c> values.
        /// </returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the library was compiled without support for VISA.</exception>
        blob binary_data(_In_ const std::uint32_t channel) const;

        /// <summary>
        /// Retrieve the configuration for the specified channel.
        /// </summary>
        /// <param name="channel">The one-based index of the channel to
        /// retrieve the configuration for.</param>
        /// <returns>The configuration for the specified channel.</returns>
        /// <exception cref="std::runtime_error">If the instance was disposed
        /// by moving it.</exception>
        /// <exception cref="visa_exception">If the sensor could not be
        /// initialised.</exception>
        /// <exception cref="std::logic_error">If the library was compiled
        /// without support for VISA.</exception>
        oscilloscope_channel channel(_In_ const std::uint32_t channel) const;

        /// <summary>
        /// Apply the specified channel configuration.
        /// </summary>
        /// <remarks>
        /// <para>This method does nothing if the library has been compiled
        /// without VISA support.</para>
        /// </remarks>
        /// <param name="channel">The channel configuration to apply.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the instance was disposed
        /// by moving it.</exception>
        /// <exception cref="visa_exception">If the sensor could not be
        /// initialised.</exception>
        rtx_instrument& channel(_In_ const oscilloscope_channel& channel);

        /// <summary>
        /// Counts the number of channels the instrument has.
        /// </summary>
        /// <remarks>
        /// It is safe to call this method on an instrument that has been
        /// disposed. It is also safe to call the method if the library has
        /// been compiled without support for VISA. In both cases, the method
        /// will return zero.
        /// </remarks>
        /// <remarks>An override timeout that the implementation uses for
        /// probing the channels. The previous timeout will be restored before
        /// the method returns.</remarks>
        /// <returns>The number of channels the instrument has.</returns>
        std::size_t channels(_In_ const timeout_type timeout = 500) const;

        /// <summary>
        /// Reads a file from the device into memory.
        /// </summary>
        /// <param name="name">The name of the file to retrieve.</param>
        /// <param name="path">The directory where the file is located. This
        /// parameter defaults to <c>nullptr</c>, which means that the file
        /// must be located in the current directory.</param>
        /// <returns>The content of the file.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="std::invalid_argument">If <paramref name="name" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the library was compiled without support for VISA.</exception>
        blob copy_file_from_instrument(_In_z_ const wchar_t *name,
            _In_opt_z_ const wchar_t *path = nullptr) const;

        /// <summary>
        /// Reads a file from the device into memory.
        /// </summary>
        /// <param name="name">The name of the file to retrieve.</param>
        /// <param name="path">The directory where the file is located. This
        /// parameter defaults to <c>nullptr</c>, which means that the file
        /// must be located in the current directory.</param>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="std::invalid_argument">If <paramref name="name" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the library was compiled without support for VISA.</exception>
        blob copy_file_from_instrument(_In_z_ const char *name,
            _In_opt_z_ const char *path = nullptr) const;

        /// <summary>
        /// Copies the given content into a file on the instrument.
        /// </summary>
        /// <remarks>
        /// It is safe to call this method if the library was built without
        /// support for VISA. Nothing will be done in this case.
        /// </remarks>
        /// <param name="name">The name of the file to be created on the
        /// instrument. Please note that the instrument only supports 8.3 file
        /// names.</param>
        /// <param name="content">The content to be copied to the device.
        /// </param>
        /// <param name="path">The path where the file should be created, e.g.
        /// &quot;INT&quot; for the internal memory. This parameter can be
        /// <c>nullptr</c>, which is the default. In this case, the file will
        /// be copied to the current directory.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="std::invalid_argument">If any of the parameters
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& copy_file_to_instrument(_In_z_ const wchar_t *name,
            _In_ const blob& content, _In_opt_z_ const wchar_t *path = nullptr);

        /// <summary>
        /// Copies the given content into a file on the instrument.
        /// </summary>
        /// <remarks>
        /// It is safe to call this method if the library was built without
        /// support for VISA. Nothing will be done in this case.
        /// </remarks>
        /// <param name="name">The name of the file to be created on the
        /// instrument. Please note that the instrument only supports 8.3 file
        /// names.</param>
        /// <param name="content">The content to be copied to the device.
        /// </param>
        /// <param name="path">The path where the file should be created, e.g.
        /// &quot;INT&quot; for the internal memory. This parameter can be
        /// <c>nullptr</c>, which is the default. In this case, the file will
        /// be copied to the current directory.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="std::invalid_argument">If any of the parameters
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& copy_file_to_instrument(_In_z_ const char *name,
            _In_ const blob& content, _In_opt_z_ const char *path = nullptr);

#if false
        /// <summary>
        /// Persists the current state of the instrument and downloads it to
        /// the host computer.
        /// </summary>
        /// <returns>A <see cref="blob" /> holding the state of the instrument.
        /// You can persist this on the host computer, but you should make sure
        /// that the file is stored in binary mode.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="std::invalid_argument">If any of the parameters
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the library was compiled without support for VISA.</exception>
        blob copy_state_from_instrument(void) const;
#endif

        /// <summary>
        /// Retrieves the waveform data for the specified channel.
        /// </summary>
        /// <param name="channel">The one-based index of the channel to retrieve
        /// the waveform for.</param>
        /// <param name="points">Specifies which sample points should be
        /// transferred.</param>
        /// <returns>The waveform for the specified channel.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the library was compiled without support for VISA.</exception>
        oscilloscope_waveform data(_In_ const std::uint32_t channel,
            _In_ const oscilloscope_waveform_points points) const;

        /// <summary>
        /// Retrieves the trigger configuration provided the configured trigger
        /// is an edge trigger.
        /// </summary>
        /// <returns>The trigger configuration</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the library was compiled without support for VISA.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the configured trigger is not an edge trigger.</exception>
        oscilloscope_edge_trigger edge_trigger(void) const;

        /// <summary>
        /// Enable and configure one of the mathematical expressions.
        /// </summary>
        /// <param name="channel">The maths channel to be configured. For an
        /// RTA4004 or and RTB2004, this must be within [1, 4].</param>
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
        /// Gets the current position of the reference point in the diagram.
        /// </summary>
        /// <returns>The location of the reference point on the horizontal
        /// axis.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the library was compiled without support for VISA.</exception>
        oscilloscope_reference_point reference_position(void) const;

        /// <summary>
        /// Restores the state of the instrument from a file stored on the
        /// instrument itself or on a USB mass-storage device connected to the
        /// instrument.
        /// </summary>
        /// <param name="name">The name of the settings file.</param>
        /// <param name="path">The path where to load the settings file
        /// from. This parameter defaults to &quot;/INT/SETTINGS&quot;.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="std::invalid_argument">If any of the parameters
        /// is <c>nullptr</c> or empty.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& load_state_from_instrument(_In_z_ const wchar_t *name,
            _In_z_ const wchar_t *path = L"/INT/SETTINGS");

        /// <summary>
        /// Restores the state of the instrument from a file stored on the
        /// instrument itself or on a USB mass-storage device connected to the
        /// instrument.
        /// </summary>
        /// <param name="name">The name of the settings file.</param>
        /// <param name="path">The path where to load the settings file
        /// from. This parameter defaults to &quot;/INT/SETTINGS&quot;.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="std::invalid_argument">If any of the parameters
        /// is <c>nullptr</c> or empty.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& load_state_from_instrument(_In_z_ const char *name,
            _In_z_ const char *path = "/INT/SETTINGS");

        /// <summary>
        /// Gets the configured name of the instrument.
        /// </summary>
        /// <param name="dst">A buffer that is able to hold at least
        /// <paramref name="cnt" /> elements. It is safe to pass <c>nullptr</c>,
        /// in which case the method will only measure the required buffer size.
        /// </param>
        /// <param name="cnt">The size of <paramref name="dst" /> in number of
        /// characters. The name of an RTA/RTB instrument cannot exceed 20
        /// characters, so a buffer of 21 characters should always suffice.
        /// </param>
        /// <returns>The required buffer size for the name, including the
        /// terminating zero.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        std::size_t name(_Out_writes_(cnt) wchar_t *dst,
            _In_ const std::size_t cnt) const;

        /// <summary>
        /// Gets the configured name of the instrument.
        /// </summary>
        /// <param name="dst">A buffer that is able to hold at least
        /// <paramref name="cnt" /> elements. It is safe to pass <c>nullptr</c>,
        /// in which case the method will only measure the required buffer size.
        /// </param>
        /// <param name="cnt">The size of <paramref name="dst" /> in number of
        /// characters. The name of an RTA/RTB instrument cannot exceed 20
        /// characters, so a buffer of 21 characters should always suffice.
        /// </param>
        /// <returns>The required buffer size for the name, including the
        /// terminating zero.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        std::size_t name(_Out_writes_(cnt) char *dst,
            _In_ const std::size_t cnt) const;

        /// <summary>
        /// Measures the size of the buffer to hold the name of the instrument.
        /// </summary>
        /// <param name="dst"><c>nullptr</c>.</param>
        /// <param name="cnt">This parameter is ignored.</param>
        /// <returns>The required buffer size for the name, including the
        /// terminating zero.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        std::size_t name(_In_opt_ const std::nullptr_t dst,
            _In_ const std::size_t cnt) const;

        /// <summary>
        /// Sets the name of the instrument.
        /// </summary>
        /// <param name="name">The new name of the instrument.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::invalid_argument">If <paramref name="name" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& name(_In_z_ const wchar_t *name);

        /// <summary>
        /// Sets the name of the instrument.
        /// </summary>
        /// <param name="name">The new name of the instrument.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::invalid_argument">If <paramref name="name" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& name(_In_z_ const char *name);

        /// <summary>
        /// Sets the reference point in the diagram.
        /// </summary>
        /// <param name="position">The location of the reference point on the
        /// horizontal axis, which can be the left side, the middle or the
        /// right side.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& reference_position(
            _In_ const oscilloscope_reference_point position);

        /// <summary>
        /// Persists the current state of the instrument to internal memory (or
        /// to a USB mass storage device connected to the instrument).
        /// </summary>
        /// <remarks>
        /// It is safe to call the method if the library was built without
        /// support for VISA, in which case nothing will happen.
        /// </remarks>
        /// <param name="name">The name of the state file, which will be
        /// truncated to eight characters if longer. The file extension
        /// &quot;.SET&quot; will be added by the method. If the file name has
        /// any other extension, it will be truncated to at most three
        /// characters.</param>
        /// <param name="path">The directory where to store the settings. This
        /// defaults to &quot;/INT/SETTINGS&quot;</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="std::invalid_argument">If any of the parameters
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        const rtx_instrument& save_state_to_instrument(
            _In_z_ const wchar_t *name,
            _In_z_ const wchar_t *path = L"/INT/SETTINGS") const;

        /// <summary>
        /// Persists the current state of the instrument to internal memory (or
        /// to a USB mass storage device connected to the instrument).
        /// </summary>
        /// <remarks>
        /// It is safe to call the method if the library was built without
        /// support for VISA, in which case nothing will happen.
        /// </remarks>
        /// <param name="name">The name of the state file, which will be
        /// truncated to eight characters if longer. The file extension
        /// &quot;.SET&quot; will be added by the method. If the file name has
        /// any other extension, it will be truncated to at most three
        /// characters.</param>
        /// <param name="path">The directory where to store the settings. This
        /// defaults to &quot;/INT/SETTINGS&quot;</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="std::invalid_argument">If any of the parameters
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        const rtx_instrument& save_state_to_instrument(
            _In_z_ const char *name,
            _In_z_ const char *path = "/INT/SETTINGS") const;

        /// <summary>
        /// Answer the part of the configuration of the instrument that is
        /// relevant for single-mode acquisition.
        /// </summary>
        /// <returns>The single-mode acquisition configuration</returns>
        /// <exception cref="std::runtime_errpr">If the method was called on an
        /// instance that was disposed by moving it..</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the library was compiled without support for VISA.</exception>
        oscilloscope_single_acquisition single_acquisition(void) const;

        /// <summary>
        /// Gets the length of a single acquisition covering all horizontal grid
        /// divisions.
        /// </summary>
        /// <returns>The time range of the whole waveform displayed.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the library was compiled without support for VISA.</exception>
        oscilloscope_quantity time_range(void) const;

        /// <summary>
        /// Sets the time range of a single acquisition covering all grid
        /// divisions.
        /// </summary>
        /// <param name="scale">Time range within [250e-12, 500].</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& time_range(_In_ const oscilloscope_quantity& scale);

        /// <summary>
        /// Gets the length of a horizontal single grid division.
        /// </summary>
        /// <returns>The time scale of a single grid division.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the library was compiled without support for VISA.</exception>
        oscilloscope_quantity time_scale(void) const;

        /// <summary>
        /// Sets the horizontal scale for all channels in time units per grid
        /// division.
        /// </summary>
        /// <param name="scale">Time scale within [1e-9, 50].</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& time_scale(_In_ const oscilloscope_quantity& scale);

        /// <summary>
        /// Configures the trigger.
        /// </summary>
        /// <param name="trigger">The trigger configuration.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& trigger(_In_ const oscilloscope_trigger& trigger);

        /// <summary>
        /// Forces a manual trigger.
        /// </summary>
        /// <param name="wait">If <c>true</c>, the trigger is combined with an
        /// <c>*OPC?</c> query that blocks the calling code until the instrument
        /// has actually triggered. This parameter defaults to <c>false</c>.
        /// </param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& trigger(_In_ const bool wait = false);

        /// <summary>
        /// Gets what kind of trigger signal the instrument produces on the
        /// auxilliary trigger output.
        /// </summary>
        /// <returns>THe behaviour of the trigger output.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the library was compiled without support for VISA.</exception>
        /// <exception cref="std::range_error">If the response of the instrument
        /// did not fall into the range of states that can be expressed by the
        /// <see cref="oscilloscope_trigger_output" /> enumeration.
        /// </exception>
        oscilloscope_trigger_output trigger_output(void) const;

        /// <summary>
        /// Configures which signal is generated on the auxilliary trigger
        /// output.
        /// </summary>
        /// <param name="output">The behaviour of the trigger output.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& trigger_output(
            _In_ const oscilloscope_trigger_output output);

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
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& trigger_position(
            _In_ const oscilloscope_quantity& offset);

        /// <summary>
        /// Gets the unit of the specified channel.
        /// </summary>
        /// <param name="dst">A buffer of at least <paramref name="cnt" />
        /// characters to receive the unit. It is safe to pass <c>nullptr</c>,
        /// in which case the method will measure the required buffer size and
        /// write nothing.</param>
        /// <param name="cnt">The size of <paramref name="dst" /> in number
        /// of characters.</param>
        /// <param name="channel">The one-based index of the channel to retrieve
        /// the unit for.</param>
        /// <returns>The number of characters required to store the unit
        /// including the terminating zero.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the library was compiled without support for VISA.</exception>
        std::size_t unit(_Out_writes_(cnt) wchar_t *dst,
            _In_ const std::size_t cnt,
            _In_ const std::uint32_t channel) const;

        /// <summary>
        /// Sets the unit of the specified channel.
        /// </summary>
        /// <param name="channel">The number (starting at 1) of the channel to
        /// be configured.</param>
        /// <param name="unit">The unit being measured (either &quot;A&quot;
        /// or &quot;V&quot;).</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::invalid_argument">If <paramref name="unit" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& unit(_In_ const std::uint32_t channel,
            _In_z_ const wchar_t *unit);

        /// <summary>
        /// Gets the unit of the specified channel.
        /// </summary>
        /// <param name="dst">A buffer of at least <paramref name="cnt" />
        /// characters to receive the unit. It is safe to pass <c>nullptr</c>,
        /// in which case the method will measure the required buffer size and
        /// write nothing.</param>
        /// <param name="cnt">The size of <paramref name="dst" /> in number
        /// of characters.</param>
        /// <param name="channel">The one-based index of the channel to retrieve
        /// the unit for.</param>
        /// <returns>The number of characters required to store the unit
        /// including the terminating zero.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the library was compiled without support for VISA.</exception>
        std::size_t unit(_Out_writes_(cnt) char *dst,
            _In_ const std::size_t cnt,
            _In_ const std::uint32_t channel) const;

        /// <summary>
        /// Sets the unit of the specified channel.
        /// </summary>
        /// <param name="channel">The number (starting at 1) of the channel to
        /// be configured.</param>
        /// <param name="unit">The unit being measured (either &quot;A&quot;
        /// or &quot;V&quot;).</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::invalid_argument">If <paramref name="unit" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        rtx_instrument& unit(_In_ const std::uint32_t channel,
            _In_z_ const char *unit);

        /// <summary>
        /// Measures the number of characters in the unit of the given
        /// <paramref name="channel" />.
        /// </summary>
        /// <param name="dst">A <c>nullptr</c>.</param>
        /// <param name="cnt">Any number.</param>
        /// <param name="channel">The one-based index of the channel to retrieve
        /// the unit for.</param>
        /// <returns>The number of characters required to store the unit
        /// including the terminating zero.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        /// <exception cref="std::logic_error">If the method is called while
        /// the library was compiled without support for VISA.</exception>
        std::size_t unit(_In_opt_ std::nullptr_t dst,
            _In_ const std::size_t cnt,
            _In_ const std::uint32_t channel) const;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
