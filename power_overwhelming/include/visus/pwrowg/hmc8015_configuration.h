// <copyright file="hmc8015_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_HMC8015_CONFIGURATION_H)
#define _PWROWG_HMC8015_CONFIGURATION_H
#pragma once

#include <array>
#include <chrono>

#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/hmc8015_function.h"
#include "visus/pwrowg/hmc8015_instrument_range.h"
#include "visus/pwrowg/sensor_configuration.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Provides additional configuration options for R &amp; S HMC 8015 sensors
/// when creating a <see cref="sensor_array" />.
/// </summary>
class POWER_OVERWHELMING_API hmc8015_configuration final
        : public sensor_configuration {

public:

    /// <summary>
    /// A unique identifer for the <see cref="hmc8015_configuration" /> type.
    /// </summary>
    static const guid id;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    hmc8015_configuration(void) noexcept;

    /// <summary>
    /// Clone <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The object to be cloned.</param>
    hmc8015_configuration(_In_ const hmc8015_configuration& rhs) noexcept;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    /// <param name=""></param>
    ~hmc8015_configuration(void) noexcept;

    /// <summary>
    /// Answer whether the sensor should clean the internal memory of the
    /// HMC 8015 on initialisation.
    /// </summary>
    /// <returns><c>true</c> if the memory should be cleaned, <c>false</c>
    /// otherwise.</returns>
    inline bool clear_internal_memory(void) const noexcept {
        return this->_clear_internal_memory;
    }

    /// <summary>
    /// Instructs the sensor to (not) clear the internal device memory of the
    /// HMC 8015 on initialisation.
    /// </summary>
    /// <param name="value"><c>true</c> for clearing the memory, <c>false</c>
    /// for leaving existing data untouched..</param>
    /// <returns><c>*this</c>.</returns>
    hmc8015_configuration& clear_internal_memory(
            _In_ const bool value) noexcept {
        this->_clear_internal_memory = value;
        return *this;
    }

    /// <summary>
    /// Answer the number of functions to be displayed.
    /// </summary>
    /// <returns>The number of elements in <see cref="functions" />.</returns>
    inline std::size_t count_functions(void) const noexcept {
        return this->_cnt_functions;
    }

    /// <summary>
    /// Answer how the <see cref="current_range_value" /> is interpreted.
    /// </summary>
    /// <returns>The interpretation of the current range.</returns>
    inline hmc8015_instrument_range current_range(void) const noexcept {
        return this->_current_range;
    }

    /// <summary>
    /// Answer the current range if it is explicitly set.
    /// </summary>
    /// <returns>The current range.</returns>
    inline float current_range_value(void) const noexcept {
        return this->_current_range_value;
    }

    /// <summary>
    /// Sets the measured range for current.
    /// </summary>
    /// <param name="range">Defines how <paramref name="value" /> is
    /// interpreted.</param>
    /// <param name="value">The current range in Amperes. This parameter
    /// is only used if <paramref name="range" /> is set to
    /// <see cref="instrument_range::explicitly" />. Valid values are
    /// 0.005, 0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1, 2, 5, 10 an 20.</param>
    /// <returns><c>*this</c>.</returns>
    inline hmc8015_configuration& current_range(
            _In_ const hmc8015_instrument_range range,
            _In_ const float value = 0.0f) noexcept {
        this->_current_range = range;
        this->_current_range_value = value;
        return *this;
    }

    /// <summary>
    /// Answer the functions that are configured to be displayed and logged.
    /// </summary>
    /// <returns>An array of <see cref="count_functions" /> functions to be
    /// enabled. The return value may be <c>nullptr</c> if the number of
    /// functions is zero.</returns>
    inline _Ret_maybenull_ const hmc8015_function *functions(
                void) const noexcept {
        return this->_functions;
    }

    /// <summary>
    /// Sets the functions to be displayed and measured.
    /// </summary>
    /// <param name="functions">An array of <paramref name="cnt" /> functions
    /// to be enabled.</param>
    /// <param name="cnt">The number of functions to be enabled.</param>
    /// <returns><c>*this</c>.</returns>
    hmc8015_configuration& functions(
        _In_reads_opt_(cnt) const hmc8015_function *functions,
        _In_ const std::size_t cnt);

    /// <summary>
    /// Appends a function to be displayed and measured.
    /// </summary>
    /// <param name="function">The function to be appended.</param>
    /// <returns><c>*this</c>.</returns>
    hmc8015_configuration& functions(_In_ const hmc8015_function function);

    /// <summary>
    /// Sets the functions to be displayed and measured.
    /// </summary>
    /// <param name="functions">A list of functions to be enabled.</param>
    /// <returns><c>*this</c>.</returns>
    template<class... TArgs>
    inline hmc8015_configuration& function_list(_In_ const TArgs&&... args) {
        std::array<hmc8015_function, sizeof...(TArgs)> funcs { args... };
        return this->functions(funcs.data(), funcs.size());
    }

    /// <summary>
    /// Answer the name of the log file or <c>nullptr</c> if the sensor should
    /// generate a file name based on the timestamp.
    /// </summary>
    /// <returns>The name of the log file.</returns>
    inline _Ret_maybenull_z_ const char *log_file(void) const noexcept {
        return this->_log_file.as<char>();
    }

    /// <summary>
    /// Sets the path to the log file generated by the sensor.
    /// </summary>
    /// <remarks>
    /// <para>If you provide a file name, the method may transform it to conform
    /// with the requirements of the instrument.</para>
    /// </remarks>
    /// <param name="path">The path to the log file or <c>nullptr</c> to have
    /// the sensor create a file name based on the timestamp.</param>
    /// <returns><c>*this</c>.</returns>
    hmc8015_configuration& log_file(_In_opt_z_ const char *path);

    /// <summary>
    /// Sets the path to the log file generated by the sensor.
    /// </summary>
    /// <remarks>
    /// <para>If you provide a file name, the method may transform it to conform
    /// with the requirements of the instrument.</para>
    /// </remarks>
    /// <param name="path">The path to the log file or <c>nullptr</c> to have the
    /// sensor create a file name based on the timestamp.</param>
    /// <param name="usb"><c>true</c> for logging to USB, <c>false</c> for
    /// logging to internal memory.</param>
    /// <returns><c>*this</c>.</returns>
    hmc8015_configuration& log_file(_In_opt_z_ const char *path,
            _In_ const bool usb) {
        return this->log_file(path).log_to_usb(usb);
    }

    /// <summary>
    /// Sets the path to the log file generated by the sensor.
    /// </summary>
    /// <param name="path">The path to the log file or <c>nullptr</c> to have the
    /// sensor create a file name based on the timestamp.</param>
    /// <returns><c>*this</c>.</returns>
    hmc8015_configuration& log_file(_In_opt_z_ const wchar_t *path);

    /// <summary>
    /// Sets the path to the log file generated by the sensor.
    /// </summary>
    /// <param name="path">The path to the log file or <c>nullptr</c> to have the
    /// sensor create a file name based on the timestamp.</param>
    /// <param name="usb"><c>true</c> for logging to USB, <c>false</c> for
    /// logging to internal memory.</param>
    /// <returns><c>*this</c>.</returns>
    hmc8015_configuration& log_file(_In_opt_z_ const wchar_t *path,
            _In_ const bool usb) {
        return this->log_file(path).log_to_usb(usb);
    }

    /// <summary>
    /// Answer whether the log file should be created on a USB thumb drive
    /// plugged into the instrument rather than in internal memory.
    /// </summary>
    /// <returns><c>true</c> if the USB drive should be used, <c>false</c>
    /// otherwise.</returns>
    inline bool log_to_usb(void) const noexcept {
        return this->_log_to_usb;
    }

    /// <summary>
    /// Configures whether the log file should be created on a USB thumb drive
    /// plugged into the instrument rather than in internal memory.
    /// </summary>
    /// <param name="value"><c>true</c> for logging to USB, <c>false</c> for
    /// logging to internal memory.</param>
    /// <returns><c>*this</c>.</returns>
    inline hmc8015_configuration& log_to_usb(_In_ const bool value) noexcept {
        this->_log_to_usb = value;
        return *this;
    }

    /// <summary>
    /// Answer the timeout for searching devices, in milliseconds.
    /// </summary>
    /// <returns>The timeout in milliseconds.</returns>
    inline std::int32_t timeout(void) const noexcept {
        return this->_timeout;
    }

    /// <summary>
    /// Sets the timeout for the VISA connection.
    /// </summary>
    /// <typeparam name="TType"></typeparam>
    /// <typeparam name="TPeriod"></typeparam>
    /// <param name="timeout"></param>
    /// <returns><c>*this</c>.</returns>
    template<class TType, class TPeriod>
    inline hmc8015_configuration& timeout(
            _In_ const std::chrono::duration<TType, TPeriod> timeout) {
        auto m = std::chrono::duration_cast<std::chrono::milliseconds>(timeout);
        this->_timeout = static_cast<std::int32_t>(std::abs(m.count()));
        return *this;
    }

    /// <summary>
    /// Gets the timeout for the VISA connection.
    /// </summary>
    /// <typeparam name="TDuration"></typeparam>
    /// <param name=""></param>
    /// <returns></returns>
    template<class TDuration> inline TDuration timeout_as(void) const {
        std::chrono::milliseconds retval(this->_timeout);
        return std::chrono::duration_cast<TDuration>(retval);
    }

    /// <summary>
    /// Answer the name of the column holding the timestamp in the CSV file
    /// produced by the HMC 8015.
    /// </summary>
    /// <returns>The name of the timestamp column.</returns>
    inline _Ret_z_ const char *timestamp_column(void) const noexcept {
        auto retval = this->_timestamp_column.as<char>();
        _Analysis_assume_(retval != nullptr);
        return retval;
    }

    /// <summary>
    /// Sets the name of the column holding the timestamp in the CSV file
    /// produced by the HMC 8015.
    /// </summary>
    /// <param name="name">The name of the colum. If this parameter is
    /// <c>nullptr</c>, the default value will be used.</param>
    /// <returns><c>*this</c>.</returns>
    hmc8015_configuration& timestamp_column(_In_opt_z_ const char *name);

    /// <summary>
    /// Sets the name of the column holding the timestamp in the CSV file
    /// produced by the HMC 8015.
    /// </summary>
    /// <param name="name">The name of the colum. If this parameter is
    /// <c>nullptr</c>, the default value will be used.</param>
    /// <returns><c>*this</c>.</returns>
    hmc8015_configuration& timestamp_column(_In_z_ const wchar_t *name);

    /// <summary>
    /// Sets the default name for the column holding the timestamp in the
    /// CSV file produced by the HMC 8015.
    /// </summary>
    /// <param name="name"><c>nullptr</c></param>
    /// <returns><c>*this</c>.</returns>
    hmc8015_configuration& timestamp_column(
        _In_opt_z_ const std::nullptr_t name);

    /// <summary>
    /// Answer how the <see cref="voltage_range_value" /> is interpreted.
    /// </summary>
    /// <returns>The interpretation of the current range.</returns>
    inline hmc8015_instrument_range voltage_range(void) const noexcept {
        return this->_voltage_range;
    }

    /// <summary>
    /// Answer the voltage range if it is explicitly set.
    /// </summary>
    /// <returns>The voltage range.</returns>
    inline float voltage_range_value(void) const noexcept {
        return this->_voltage_range_value;
    }

    /// <summary>
    /// Sets the measured range for voltage.
    /// </summary>
    /// <param name="range">Defines how <paramref name="value" /> is
    /// interpreted.</param>
    /// <param name="value">The current range in Volts. This parameter
    /// is only used if <paramref name="range" /> is set to
    /// <see cref="instrument_range::explicitly" />. Valid values are
    /// 5, 15, 30, 60, 150, 300 and 600.</param>
    /// <returns><c>*this</c>.</returns>
    inline hmc8015_configuration& voltage_range(
            _In_ const hmc8015_instrument_range range,
            _In_ const float value = 0.0f) noexcept {
        this->_voltage_range = range;
        this->_voltage_range_value = value;
        return *this;
    }

    /// <summary>
    /// Assignment.
    /// </summary>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>*this</c>.</returns>
    hmc8015_configuration& operator =(
        _In_ const hmc8015_configuration& rhs) noexcept;

private:

    bool _clear_internal_memory;
    std::size_t _cnt_functions;
    hmc8015_instrument_range _current_range;
    float _current_range_value;
    hmc8015_function *_functions;
    blob _log_file;
    bool _log_to_usb;
    std::int32_t _timeout;
    blob _timestamp_column;
    hmc8015_instrument_range _voltage_range;
    float _voltage_range_value;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_HMC8015_CONFIGURATION_H) */
