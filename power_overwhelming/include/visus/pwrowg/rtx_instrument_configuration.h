// <copyright file="rtx_instrument_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_INSTRUMENT_CONFIGURATION_H)
#define _PWROWG_RTX_INSTRUMENT_CONFIGURATION_H
#pragma once

#include "visus/pwrowg/rtx_acquisition.h"
#include "visus/pwrowg/rtx_channel.h"
#include "visus/pwrowg/rtx_quantity.h"
#include "visus/pwrowg/rtx_reference_point.h"
#include "visus/pwrowg/rtx_trigger.h"
#include "visus/pwrowg/rtx_instrument.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// This class stores the shared part of the configuration of an
/// <see cref="rtx_sensor" />, which cannot be configured individually if
/// multiple sensors are created on the same <see cref="rtx_instrument" />.
/// </summary>
/// <remarks>
/// <para>When using an oscilloscope with four channels or more, it is
/// possible to create an <see cref="rtx_sensor" /> for each pair of
/// channels (one for voltage and one for current), thus having more than
/// one sensor operating on the same <see cref="rtx_instrument" />. In this
/// situation, not all of the parameters of the instrument can be configured
/// individually. For instance, the length of the waveform being recorded
/// on a trigger signal is the same for all channels. This configuration
/// object groups all of these settings that will be shared between sensors
/// on the same instrument.</para>
/// <para>Settings grouped in this class need to be set only once for the
/// set of sensors created from the same instruments. Likewise, it is
/// strongly recommended to apply the same settings to all instruments when
/// working with multiple oscilloscopes in order to produce consistent
/// results.</para>
/// <para>This class does not at all interact with the actual instrument
/// until the configuration is applied. Therefore, it is possible to create
/// configurations that are invalid without noticing it until the
/// configuration is realised.</para>
/// <para>Although it is possible to configure settings that are only
/// relevant on a per-sensor basis, most notably the channels, using this
/// class, you should never do this when using it in conjunction with
/// <see cref="rtx_sensor" /> as this might apply an invalid configuration
/// for this use case. Make sure to call <see cref="ignore_all_channels" />
/// when working with a configuration object that you have not built
/// yourself.</para>
/// <para>This class effectively implements the builder pattern for
/// RTA/RTB oscilloscope instances.</para>
/// </remarks>
class POWER_OVERWHELMING_API rtx_instrument_configuration final {

public:

    /// <summary>
    /// The type used to express device timeouts in milliseconds.
    /// </summary>
    typedef std::uint32_t timeout_type;

#if defined(POWER_OVERWHELMING_WITH_VISA)
    /// <summary>
    /// Applies the given <paramref name="configuration" /> to all
    /// given <paramref name="instruments" />.
    /// </summary>
    /// <param name="instruments">The array of instruments to apply the
    /// configuration to. It is safe to pass <c>nullptr</c>, in which case
    /// nothing will happen.</param>
    /// <param name="cnt">The number of elements in
    /// <paramref name="instruments" />.</param>
    /// <param name="configuration">The configuration to apply to. If
    /// <paramref name="master_slave" /> is set <c>true</c>, the first
    /// instrument will be considered the master device and all subsequent
    /// ones will get a slave configuration derived from
    /// <paramref name="configuration "/>. If the configuration is set to
    /// make the instrument beep once it was applied, every instrument past
    /// the first one will beep once more to indicate how many instruments
    /// have been configured at the end</param>
    /// <param name="master_slave">If <c>true</c>, apply the given
    /// configuration only to the first instrument and a slave configuration
    /// derived from it to all subsequent ones. If <c>false</c>, which is
    /// the default, apply the given configuration to all instruments.
    /// </param>
    /// <param name="level">The trigger level of the external trigger of the
    /// slave instruments. The external trigger usually uses 5V if passed on
    /// via the AUX output, so the default of 2.5 V is a safe bet.</param>
    /// <param name="slope">The slope on which to trigger, which is the
    /// rising one by default.</param>
    /// <exception cref="std::runtime_error">If the any of the given
    /// <paramref name="instruments" /> has been disposed by a move
    /// operation.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    static void apply(_In_reads_(cnt) rtx_instrument *instruments,
        _In_ const std::size_t cnt,
        _In_ const rtx_instrument_configuration& configuration,
        _In_ const bool master_slave = false,
        _In_ const rtx_quantity& level
        = rtx_quantity(2.5f, "V"),
        _In_ const rtx_trigger_slope slope
        = rtx_trigger_slope::rising);
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

#if defined(POWER_OVERWHELMING_WITH_VISA)
    /// <summary>
    /// Applies a master/slave configuration to the given insturments where
    /// the instrument with the specified device name receives the master
    /// configuration while all other instruments receive a slave
    /// configuration derived from that.
    /// </summary>
    /// <param name="instruments">The array of instruments to apply the
    /// configuration to. It is safe to pass <c>nullptr</c>, in which case
    /// nothing will happen.</param>
    /// <param name="cnt">The number of elements in
    /// <paramref name="instruments" />.</param>
    /// <param name="configuration">The configuration to apply to the master
    /// instrument. All other instruments will receive a slave configuration
    /// derived from this object.</param>
    /// <param name="master">The instrument name of the master instrument.
    /// </param>
    /// <param name="level">The trigger level of the external trigger of the
    /// slave instruments. The external trigger usually uses 5V if passed on
    /// via the AUX output, so the default of 2.5 V is a safe bet.</param>
    /// <param name="slope">The slope on which to trigger, which is the
    /// rising one by default.</param>
    /// <returns>The index of the master instrument in
    /// <paramref name="instruments" />. If this value is equal to or larger
    /// than <paramref name="cnt" />, the specified name of the master
    /// instrument was not found among the instruments provided. The
    /// configuration is most likely not working in this case, because all
    /// instruments have been configured as slave instruments.</returns>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="master" /> is <c>nullptr</c>.</exception>
    /// <exception cref="std::runtime_error">If the any of the given
    /// <paramref name="instruments" /> has been disposed by a move
    /// operation.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    static std::size_t apply(_In_reads_(cnt) rtx_instrument *instruments,
        _In_ const std::size_t cnt,
        _In_ const rtx_instrument_configuration& configuration,
        _In_z_ const wchar_t *master,
        _In_ const rtx_quantity& level
        = rtx_quantity(2.5f, "V"),
        _In_ const rtx_trigger_slope slope
        = rtx_trigger_slope::rising);
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

#if defined(POWER_OVERWHELMING_WITH_VISA)
    /// <summary>
    /// Applies a master/slave configuration to the given insturments where
    /// the instrument with the specified device name receives the master
    /// configuration while all other instruments receive a slave
    /// configuration derived from that.
    /// </summary>
    /// <param name="instruments">The array of instruments to apply the
    /// configuration to. It is safe to pass <c>nullptr</c>, in which case
    /// nothing will happen.</param>
    /// <param name="cnt">The number of elements in
    /// <paramref name="instruments" />.</param>
    /// <param name="configuration">The configuration to apply to the master
    /// instrument. All other instruments will receive a slave configuration
    /// derived from this object.</param>
    /// <param name="master">The instrument name of the master instrument.
    /// </param>
    /// <param name="level">The trigger level of the external trigger of the
    /// slave instruments. The external trigger usually uses 5V if passed on
    /// via the AUX output, so the default of 2.5 V is a safe bet.</param>
    /// <param name="slope">The slope on which to trigger, which is the
    /// rising one by default.</param>
    /// <returns>The index of the master instrument in
    /// <paramref name="instruments" />. If this value is equal to or larger
    /// than <paramref name="cnt" />, the specified name of the master
    /// instrument was not found among the instruments provided. The
    /// configuration is most likely not working in this case, because all
    /// instruments have been configured as slave instruments.</returns>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="master" /> is <c>nullptr</c>.</exception>
    /// <exception cref="std::runtime_error">If the any of the given
    /// <paramref name="instruments" /> has been disposed by a move
    /// operation.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    static std::size_t apply(_In_reads_(cnt) rtx_instrument *instruments,
        _In_ const std::size_t cnt,
        _In_ const rtx_instrument_configuration& configuration,
        _In_z_ const char *master,
        _In_ const rtx_quantity& level
        = rtx_quantity(2.5f, "V"),
        _In_ const rtx_trigger_slope slope
        = rtx_trigger_slope::rising);
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

#if defined(POWER_OVERWHELMING_WITH_VISA)
    /// <summary>
    /// Loads the instruments configurations from the given file and applies
    /// them based on the device path to the given instruments.
    /// </summary>
    /// <remarks>
    /// <para>If no matching configuration could be found for any of the
    /// given instruments, the first one from the file will be used.</para>
    /// </remarks>
    /// <param name="instruments">The instruments to be configured.</param>
    /// <param name="cnt">The number of instruments in
    /// <paramref name="instruments" />.</param>
    /// <param name="path">The path to the configuration file.</param>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="path" /> is <c>nullptr</c>.</exception>
    /// <exception cref="std::ifstream::failure">If the I/O operation
    /// failed.</exception>
    /// <exception cref="visa_exception">If the configuration could not be
    /// applied to one or more of the instruments.</exception>
    static void apply(_In_reads_(cnt) rtx_instrument *instruments,
        _In_ const std::size_t cnt, _In_z_ const wchar_t *path);
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

#if defined(POWER_OVERWHELMING_WITH_VISA)
    /// <summary>
    /// Deserialises the JSON-encoded instrument configuration from the
    /// given string and applies them based on the device path to the given
    /// instruments.
    /// </summary>
    /// <remarks>
    /// <para>If no matching configuration could be found for any of the
    /// given instruments, the first one from the file will be used.</para>
    /// <para>The string provided <i>must</i> be encoded in UTF-8. Any other
    /// narrow character string is illegal. Specifically, Latin-1 or
    /// ISO 8859-1 literal strings are illegal.</para>
    /// </remarks>
    /// <param name="instruments">The instruments to be configured.</param>
    /// <param name="cnt">The number of instruments in
    /// <paramref name="instruments" />.</param>
    /// <param name="str">The JSON configuration string.  This string
    /// must be UTF-8.</param>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="str" /> is <c>nullptr</c>.</exception>
    /// <exception cref="nlohmann::json::exception">If the input could not
    /// be parsed, eg because it is ISO 8859-1 and not UTF-8.</exception>
    /// <exception cref="visa_exception">If the configuration could not be
    /// applied to one or more of the instruments.</exception>
    static void apply_from_json(_In_reads_(cnt) rtx_instrument *instruments,
        _In_ const std::size_t cnt, _In_z_ const char *str);
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

    /// <summary>
    /// Loads a single configuration from the given JSON string.
    /// </summary>
    /// <remarks>
    /// The string provided <i>must</i> be encoded in UTF-8. Any other
    /// narrow character string is illegal. Specifically, Latin-1 or
    /// ISO 8859-1 literal strings are illegal.
    /// </remarks>
    /// <param name="str">The JSON string to be deserialised. This string
    /// must be UTF-8.</param>
    /// <returns>The configuration represented by the string.</returns>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="path" /> is <c>nullptr</c>.</exception>
    /// <exception cref="nlohmann::json::exception">If the input could not
    /// be parsed, eg because it is ISO 8859-1 and not UTF-8.</exception>
    static rtx_instrument_configuration deserialise(_In_z_ const char *str);

    /// <summary>
    /// Loads one or more configuration from the given JSON string.
    /// </summary>
    /// <remarks>
    /// The string provided <i>must</i> be encoded in UTF-8. Any other
    /// narrow character string is illegal. Specifically, Latin-1 or
    /// ISO 8859-1 literal strings are illegal.
    /// </remarks>
    /// <param name="dst">Receives at most <paramref name="cnt" />
    /// configurations from the JSON array provided.</param>
    /// <param name="cnt">The number of elments that can be stored to
    /// <paramref name="dst" />.</param>
    /// <param name="str">The JSON string to be deserialised. This string
    /// must be UTF-8 and can contain either an array or a single object.
    /// </param>
    /// <returns>The number of configurations found in
    /// <paramref name="str" />.</returns>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="path" /> is <c>nullptr</c>.</exception>
    /// <exception cref="nlohmann::json::exception">If the input could not
    /// be parsed, eg because it is ISO 8859-1 and not UTF-8.</exception>
    static std::size_t deserialise(_When_(dst != nullptr,
        _Out_writes_opt_(cnt)) rtx_instrument_configuration *dst,
        _In_ std::size_t cnt, _In_z_ const char *str);

    /// <summary>
    /// Loads the instrument configurations from the given file.
    /// </summary>
    /// <param name="dst">The array to receive the configuration object. If
    /// not <c>nullptr</c>, this array must be able to receive at least
    /// <paramref name="cnt" /> elements.</param>
    /// <param name="cnt">The number of elements in <paramref name="dst" />.
    /// </param>
    /// <param name="path">The path to read the configuration from.</param>
    /// <returns>The number of configurations in the file, regardless of
    /// whether these have been written to <paramref name="dst" />.
    /// </returns>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="path" /> is <c>nullptr</c>.</exception>
    /// <exception cref="std::ifstream::failure">If the I/O operation
    /// failed.</exception>
    static std::size_t load(_When_(dst != nullptr, _Out_writes_opt_(cnt))
        rtx_instrument_configuration *dst,
        _In_ std::size_t cnt, _In_z_ const wchar_t *path);

    /// <summary>
    /// Loads a single configuration from the given JSON file.
    /// </summary>
    /// <remarks>
    /// If the JSON file contains an array, only the first configuration is
    /// read and returned.
    /// </remarks>
    /// <param name="path">The path to read the configuration from.</param>
    /// <returns>The first or only configuration in the file.</returns>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="path" /> is <c>nullptr</c>.</exception>
    /// <exception cref="std::ifstream::failure">If the I/O operation
    /// failed.</exception>
    static rtx_instrument_configuration load(_In_z_ const wchar_t *path);

    /// <summary>
    /// Saves the given instrument configurations in a JSON file.
    /// </summary>
    /// <param name="configs">The configurations to be saved.</param>
    /// <param name="cnt">The number of <paramref name="instruments" /> in
    /// the input array.</param>
    /// <param name="path">The path to the output file.</param>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="instruments" /> is <c>nullptr</c>.</exception>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="path" /> is <c>nullptr</c>.</exception>
    /// <exception cref="std::ofstream::failure">If the I/O operation
    /// failed.</exception>
    static void save(
        _In_reads_(cnt) const rtx_instrument_configuration *configs,
        _In_ const std::size_t cnt, _In_z_ const wchar_t *path);

#if defined(POWER_OVERWHELMING_WITH_VISA)
    /// <summary>
    /// Saves the given instrument configurations in a JSON file.
    /// </summary>
    /// <remarks>
    /// <para>In contrast to the method overload accepting
    /// <see cref="rtx_instrument_configuration" />, this method will
    /// preserve the identity of the instrument along the configuration.
    /// Files from this method can therefore be used to restore the state
    /// of multiple known instruments at once. It is the preferred way of
    /// storing setups for future use with the <see cref="apply" /> method.
    /// </para>
    /// </remarks>
    /// <param name="instruments">The instruments to be saved.</param>
    /// <param name="cnt">The number of <paramref name="instruments" /> in
    /// the input array.</param>
    /// <param name="path">The path to the output file.</param>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="instruments" /> is <c>nullptr</c>.</exception>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="path" /> is <c>nullptr</c>.</exception>
    /// <exception cref="std::ofstream::failure">If the I/O operation
    /// failed.</exception>
    static void save(_In_reads_(cnt) const rtx_instrument *instruments,
        _In_ const std::size_t cnt, _In_z_ const wchar_t *path);
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

    /// <summary>
    /// Saves the given configuration as a JSON file.
    /// </summary>
    /// <param name="configuration">The configuration to save.</param>
    /// <param name="path">The path to the output file.</param>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="path" /> is <c>nullptr</c>.</exception>
    /// <exception cref="std::ofstream::failure">If the I/O operation
    /// failed.</exception>
    static void save(_In_ const rtx_instrument_configuration& configuration,
        _In_z_ const wchar_t *path);

    /// <summary>
    /// Serialises the given configuration as a JSON string.
    /// </summary>
    /// <param name="dst">A buffer of at least <paramref name="cnt" />
    /// code units to receive the output. This parameter can only be
    /// <c>nullptr</c> if <paramref name="cnt" /> is zero.</param>
    /// <param name="cnt">The size of <paramref name="dst" /> in number
    /// of UTF-8 code units.</param>
    /// <param name="configuration">The configuration to be serialised.</param>
    /// <returns>The number of UTF-8 code units (including the terminating
    /// zero) required to store the JSON representation of the
    /// configuration. Nothing will have been written if the return value is
    /// larger than <paramref name="cnt" />.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="cnt" />
    /// is larger than zero, but <paramref name="dst" /> is <c>nullptr</c>.
    /// </exception>
    static std::size_t serialise(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) char *dst,
        _In_ const std::size_t cnt,
        _In_ const rtx_instrument_configuration& configuration);

    /// <summary>
    /// Serialises the given configurations as a JSON string.
    /// </summary>
    /// <param name="dst">A buffer of at least <paramref name="cnt_dst" />
    /// code units to receive the output. This parameter can only be
    /// <c>nullptr</c> if <paramref name="cnt_dst" /> is zero.</param>
    /// <param name="cnt_dst">The size of <paramref name="dst" /> in number
    /// of UTF-8 code units.</param>
    /// <param name="configs">The configurations to serialise.</param>
    /// <param name="cnt_configs">The number of configurations to serialise.
    /// </param>
    /// <returns>The number of UTF-8 code units (including the terminating
    /// zero) required to store the JSON representation of the
    /// configurations. Nothing will have been written if the return value is
    /// larger than <paramref name="cnt" />.</returns>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="cnt_dst" /> is larger than zero, but
    /// <paramref name="dst" /> is <c>nullptr</c>.</exception>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="configs" /> is <c>nullptr</c>.</exception>
    static std::size_t serialise(
        _When_(dst != nullptr, _Out_writes_opt_(cnt_dst)) char *dst,
        _In_ const std::size_t cnt_dst,
        _In_reads_(cnt_configs) const rtx_instrument_configuration *configs,
        _In_ const std::size_t cnt_configs);

#if defined(POWER_OVERWHELMING_WITH_VISA)
    /// <summary>
    /// Serialises the configurations of the given instruments as a JSON
    /// string.
    /// </summary>
    /// <param name="dst">A buffer of at least <paramref name="cnt_dst" />
    /// code units to receive the output. This parameter can only be
    /// <c>nullptr</c> if <paramref name="cnt_dst" /> is zero.</param>
    /// <param name="cnt_dst">The size of <paramref name="dst" /> in number
    /// of UTF-8 code units.</param>
    /// <param name="instruments">The instruments to serialise the
    /// configurations of.</param>
    /// <param name="cnt_instruments">The number of instruments in
    /// <paramref name="instruments" />.
    /// <returns>The number of UTF-8 code units (including the terminating
    /// zero) required to store the JSON representation of the
    /// configurations. Nothing will have been written if the return value is
    /// larger than <paramref name="cnt_dst" />.</returns>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="cnt_dst" /> is larger than zero, but
    /// <paramref name="dst" /> is <c>nullptr</c>.</exception>
    /// <exception cref="std::invalid_argument">If
    /// <paramref name="instruments" /> is <c>nullptr</c>.</exception>
    static std::size_t serialise(
        _When_(dst != nullptr, _Out_writes_opt_(cnt_dst)) char *dst,
        _In_ const std::size_t cnt_dst,
        _In_reads_(cnt_instruments) const rtx_instrument *instruments,
        _In_ const std::size_t cnt_instruments);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <remarks>
    /// The instance created by the default constructor is not really
    /// usable. This constructor only exists such that it is possible to
    /// create temporary variables and arrays of the type. Actual instances
    /// should always be created using one of the other constructors.
    /// </remarks>
    rtx_instrument_configuration(void);

    /// <summary>
    /// Clone <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The object to be cloned.</param>
    rtx_instrument_configuration(
        _In_ const rtx_instrument_configuration& rhs);

    /// <summary>
    /// Move <paramref name="rhs" /> to a new instance.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    rtx_instrument_configuration(
        _Inout_ rtx_instrument_configuration&& rhs) noexcept;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <remarks>
    /// <para>The default configuration uses the defaults of the
    /// <see cref="rtx_acquisition" /> and
    /// <see cref="rtx_tigger" /> with the following changes:
    /// On the acquisition, fast-segmentation is enabled and the number of
    /// points is computed automatically. The rationally for that is that we
    /// want the instrument to be as fast as possible in production mode.
    /// Furthermore, computing the number of samples automatically is most
    /// suitable for this construction, which is designed to require the
    /// least user input possible. The edge trigger is configured in
    /// <see cref="rtx_trigger_mode::automatic" /> automatic, which
    /// ensures that the instrument forces a trigger if none occurs on the
    /// device. This might not be desirable if working with external
    /// triggers on the instrument, but it is the least error-prone way to
    /// configure the instrument. Therefore, it is again the most reasonable
    /// thing for this simplified constructor. If you have additional
    /// requirements, you must configure new instances using fully
    /// customised configuration objects.</para>
    /// </remarks>
    /// <param name="time_range">The time range the oscilloscope should
    /// acquire after it has been triggers.</param>
    /// <param name="samples">The number of samples to be acquired during
    /// <paramref name="time_range" />. If this is zero, which is the
    /// default, the instrument will be configured to determine the best
    /// number of samples on its own.</param>
    /// <param name="timeout">The timeout of the instrument (for connections
    /// and for I/O operations including <c>*OPC?</c> queries. If this value
    /// is zero, which is the default, the timeout will not be modified. Be
    /// aware that you must be able to wait for acqusitions to complete, so
    /// the timeout should be larger than the time range you intend to
    /// acquire.</param>
    explicit rtx_instrument_configuration(
        _In_ const rtx_quantity time_range,
        _In_ const unsigned int samples = 0,
        _In_ timeout_type timeout = 0);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="time_range">The time range the oscilloscope should
    /// acquire after it has been triggers.</param>
    /// <param name="acquisition">The acquisition configuration to be
    /// applied to the instrument.</param>
    /// <param name="trigger">Configures how the instrument will be
    /// triggered.</param>
    /// <param name="timeout">The timeout of the instrument (for connections
    /// and for I/O operations including <c>*OPC?</c> queries. If this value
    /// is zero, which is the default, the timeout will not be modified. Be
    /// aware that you must be able to wait for acqusitions to complete, so
    /// the timeout should be larger than the time range you intend to
    /// acquire.</param>
    rtx_instrument_configuration(
        _In_ const rtx_quantity time_range,
        _In_ const rtx_acquisition& acquisition,
        _In_ const rtx_trigger& trigger,
        _In_ timeout_type timeout = 0);

#if defined(POWER_OVERWHELMING_WITH_VISA)
    /// <summary>
    /// Extracts the configuration from the given instrument.
    /// </summary>
    /// <remarks>
    /// This constructor tries enumerating the channels of the device until
    /// it fails. It may therefore take significant time to complete as the
    /// instrument must hit a timeout to detect that the final channel was
    /// opened.
    /// </remarks>
    /// <param name="instrument">The instrument to retrieve the
    /// configuration from.</param>
    /// <param name="ignore_channels">If this parameter is set <c>true</c>,
    /// the constructor will not try enumerating the channel configurations
    /// of the instrument.</param>
    explicit rtx_instrument_configuration(
        _In_ const rtx_instrument& instrument,
        _In_ const bool ignore_channels = false);
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~rtx_instrument_configuration(void);

    /// <summary>
    /// Answers the way the instrument will acquire one or more samples.
    /// </summary>
    /// <returns>The acquisition configuration of the instrument.</returns>
    const rtx_acquisition& acquisition(void) const noexcept;

    /// <summary>
    /// Creates a copy of the configuration, but configured such that the
    /// instrument is triggered by the external trigger.
    /// </summary>
    /// <param name="beep">Instructs the slave configuration to make the
    /// instrument beep <paramref name="beep" /> times once it was applied.
    /// </param>
    /// <param name="level">The trigger level of the external trigger of the
    /// slave instruments. The external trigger usually uses 5V if passed on
    /// via the AUX output, so the default of 2.5 V is a safe bet.</param>
    /// <param name="slope">The slope on which to trigger, which is the
    /// rising one by default.</param>
    /// <returns>A new configuration for instruments that are chained after
    /// the first one that is triggered as configured by the user.</returns>
    rtx_instrument_configuration as_slave(
        _In_ const std::size_t beep = 0,
        _In_ const rtx_quantity& level
        = rtx_quantity(2.5f, "V"),
        _In_ const rtx_trigger_slope slope
        = rtx_trigger_slope::rising) const;

#if defined(POWER_OVERWHELMING_WITH_VISA)
    /// <summary>
    /// Applies the configuration on the given instrument.
    /// </summary>
    /// <remarks>
    /// <para>This method will block the calling thread until the instrument
    /// has applied all changes.</para>
    /// </remarks>
    /// <param name="instrument">The instrument to apply the configuration
    /// to.</param>
    /// <exception cref="std::runtime_error">If the given
    /// <paramref name="instrument" /> has been disposed by a move
    /// operation.</exception>
    /// <exception cref="visa_exception">If any of the API calls to the
    /// instrument failed.</exception>
    void apply(_Inout_ rtx_instrument& instrument) const;
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

    /// <summary>
    /// Answer how often the instrument should beep once
    /// <see cref="apply" /> completed.
    /// </summary>
    /// <returns>The number of beeps on apply.</returns>
    inline std::size_t beep_on_apply(void) const noexcept {
        return this->_beep_on_apply;
    }

    /// <summary>
    /// Configures object to make the instrument beep
    /// <paramref name="count" /> times once the <see cref="apply" /> method
    /// finishes.
    /// </summary>
    /// <param name="count">The number of beeps to emit. If zero, the
    /// instrument will not beep.</param>
    /// <returns><c>*this</c>.</returns>
    rtx_instrument_configuration& beep_on_apply(
        _In_ const std::size_t count) noexcept;

    /// <summary>
    /// Answer whether the instrument should be configured to beep if it
    /// encounters an error.
    /// </summary>
    /// <returns><c>true</c> if the beep should be enabled, <c>false</c>
    /// otherwise.</returns>
    inline bool beep_on_error(void) const noexcept {
        return this->_beep_on_error;
    }

    /// <summary>
    /// Configures the instrument to beep if it encounters an error.
    /// </summary>
    /// <param name="enable"><c>true</c> to enable the beep, <c>false</c>
    /// otherwise.</param>
    /// <returns><c>*this</c>.</returns>
    rtx_instrument_configuration& beep_on_error(
        _In_ const bool enable) noexcept;

    /// <summary>
    /// Answer whether the instrument should be configured to beep if a
    /// trigger occurs.
    /// </summary>
    /// <returns><c>true</c> if the beep should be enabled, <c>false</c>
    /// otherwise.</returns>
    inline bool beep_on_trigger(void) const noexcept {
        return this->_beep_on_trigger;
    }

    /// <summary>
    /// Configures the instrument to beep if a trigger occurs.
    /// </summary>
    /// <param name="enable"><c>true</c> to enable the beep, <c>false</c>
    /// otherwise.</param>
    /// <returns><c>*this</c>.</returns>
    rtx_instrument_configuration& beep_on_trigger(
        _In_ const bool enable) noexcept;

    /// <summary>
    /// Configures the given channel.
    /// </summary>
    /// <param name="channel">The channel configuration to apply. Please
    /// note that each channel can only be configured once. Subsequent
    /// calls with the name channel number will overwrite any existing
    /// configuration.</param>
    /// <returns><c>*this</c>.</returns>
    rtx_instrument_configuration& channel(
        _In_ const rtx_channel& channel);

    /// <summary>
    /// Counts or returns the channels configured.
    /// </summary>
    /// <remarks>
    /// The value reported by this object does not necessarily reflect the
    /// number of channels on the instrument. It only reflects the channels
    /// that should be configured by it.
    /// </remarks>
    /// <param name="dst">Receives at most <paramref name="cnt" /> channels
    /// if not <c>nullptr</c>.</param>
    /// <param name="cnt">The number of elements that can be written to
    /// <paramref name="dst" />.</param>
    /// <returns>The number of channels configured.</returns>
    std::size_t channels(_When_(dst != nullptr, _Out_writes_opt_(cnt))
        rtx_channel *dst = nullptr,
        _In_ const std::size_t cnt = 0) const;

    /// <summary>
    /// Disables automatic roll mode without changing <c>TIM:ROLL:MTIM</c>.
    /// </summary>
    /// <returns><c>*this</c>.</returns>
    rtx_instrument_configuration& disable_automatic_roll(void) noexcept;

    /// <summary>
    /// Sets automatic roll mode to be on.
    /// </summary>
    /// <remarks>
    /// If automatic roll mode was configured to be prevented (which is the
    /// default), the default minimum time base for RTA/RTB instruments will
    /// be applied.
    /// </remarks>
    /// <returns><c>*this</c>.</returns>
    rtx_instrument_configuration& enable_automatic_roll(void) noexcept;

    /// <summary>
    /// Removes the channel with the given number from the configuration.
    /// </summary>
    /// <param name="channel">The channel to be removed. It is safe to pass
    /// a channel that is not configured, in which case nothing will happen.
    /// </param>
    /// <returns><c>*this</c>.</returns>
    rtx_instrument_configuration& ignore_channel(
        _In_ const std::uint32_t channel);

    /// <summary>
    /// Removes all per-channel configurations from the object such that the
    /// channels of the instrument remain unchanged when applying the
    /// configuration.
    /// </summary>
    /// <returns><c>*this</c>.</returns>
    rtx_instrument_configuration& ignore_all_channels(void) noexcept;

    /// <summary>
    /// Gets the minimum time base for which roll mode is enabled
    /// automatically if the length of a division is undercut.
    /// </summary>
    /// <returns>The minimum time base in seconds.</returns>
    inline float min_time_base(void) const noexcept {
        return this->_min_time_base;
    }

    /// <summary>
    /// Sets the minimum time base for which roll mode is enabled
    /// automatically if the length of a division is undercut.
    /// </summary>
    /// <remarks>
    /// <para>The instrument will enable roll mode automatically (which is
    /// typically not desirable for automated measurement application cases)
    /// if the length of a division undercuts the value configured here. The
    /// default value for RTA/RTB instruments is half a second for this
    /// value.</para>
    /// <para>There are a few special cases in this implementation: If you
    /// set a value of zero or a negative one, the method will disable
    /// <c>TIM:ROLL:AUT</c>. If you set exactly zero, the maximum possible
    /// value for <c>TIM:ROLL:MTIM</c> will be set, effectively preventing
    /// for automatic roll to ever happen. If the value is negative, its
    /// absolute will be set as the effective value.</para>
    /// </remarks>
    /// <param name="min_time_base">The minimum time base in seconds.
    /// </param>
    /// <returns><c>*this</c>.</returns>
    inline rtx_instrument_configuration& min_time_base(
            _In_ const float min_time_base) noexcept {
        this->_min_time_base = min_time_base;
        return *this;
    }

    /// <summary>
    /// Configures the instrument such that automatic roll should never
    /// occur.
    /// </summary>
    /// <returns><c>*this</c>.</returns>
    rtx_instrument_configuration& prevent_automatic_roll(void) noexcept {
        this->_min_time_base = 0.0f;
        return *this;
    }

    /// <summary>
    /// Gets the horizontal reference point to be configured on the
    /// instrument.
    /// </summary>
    /// <returns>The horizontal reference point.</returns>
    inline rtx_reference_point reference_position(
            void) const noexcept {
        return this->_reference_position;
    }

    /// <summary>
    /// Sets the horizontal reference point to be configured on the
    /// instrument.
    /// </summary>
    /// <param name="position">The new reference position.</param>
    /// <returns><c>*this</c>.</returns>
    inline rtx_instrument_configuration& reference_position(
            const rtx_reference_point position) noexcept {
        this->_reference_position = position;
        return *this;
    }

    /// <summary>
    /// Indicates whether this configuration is for a slave instrument that
    /// is being triggered by another instrument via the external trigger
    /// input.
    /// </summary>
    /// <returns><c>true</c> if the instrument is running as slave,
    /// <c>false</c> if it needs to be triggered by the user.</returns>
    inline bool slave(void) const noexcept {
        return this->_slave;
    }

    /// <summary>
    /// Answers the timeout of the instrument in milliseconds.
    /// </summary>
    /// <returns>The timeout of the instrument, or zero if the timeout
    /// should not be modified.</returns>
    inline timeout_type timeout(void) const noexcept {
        return this->_timeout;
    }

    /// <summary>
    /// Answers the time range the instrument will cover when a new sample
    /// is being requested.
    /// </summary>
    /// <returns>The time range the instrument will acquire.</returns>
    inline const rtx_quantity& time_range(void) const noexcept {
        return this->_time_range;
    }

    /// <summary>
    /// Answer the trigger configured on the instrument.
    /// </summary>
    /// <returns>The trigger to be configured on the instrument.</returns>
    inline const rtx_trigger& trigger(void) const noexcept {
        return this->_trigger;
    }

    /// <summary>
    /// Answer the horizontal trigger position to be configured on the
    /// instrument.
    /// </summary>
    /// <returns>The trigger position to be configured.</returns>
    inline const rtx_quantity& trigger_position(
            void) const noexcept {
        return this->_trigger_position;
    }

    /// <summary>
    /// Set the the horizontal trigger position to configured on the
    /// instrument.
    /// </summary>
    /// <param name="pos">The new trigger position.</param>
    /// <returns><c>*this</c>.</returns>
    inline rtx_instrument_configuration& trigger_position(
            const rtx_quantity& pos) {
        this->_trigger_position = pos;
        return *this;
    }

    /// <summary>
    /// Assignment.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    rtx_instrument_configuration& operator =(
        _In_ const rtx_instrument_configuration& rhs);

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    rtx_instrument_configuration& operator =(
        _Inout_ rtx_instrument_configuration&& rhs) noexcept;

private:

    rtx_acquisition _acquisition;
    std::size_t _beep_on_apply;
    bool _beep_on_error;
    bool _beep_on_trigger;
    rtx_channel *_channels;
    std::size_t _cnt_channels;
    float _min_time_base;
    rtx_reference_point _reference_position;
    bool _slave;
    timeout_type _timeout;
    rtx_quantity _time_range;
    rtx_trigger _trigger;
    rtx_quantity _trigger_position;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_INSTRUMENT_CONFIGURATION_H) */
