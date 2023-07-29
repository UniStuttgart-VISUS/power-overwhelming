// <copyright file="rtx_instrument_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/rtx_instrument_configuration.h"

#include <cstring>
#include <stdexcept>
#include <vector>

#include "power_overwhelming/convert_string.h"


/*
 * visus::power_overwhelming::rtx_instrument_configuration::apply
 */
void visus::power_overwhelming::rtx_instrument_configuration::apply(
        _In_reads_(cnt) rtx_instrument *instruments,
        _In_ const std::size_t cnt,
        _In_ const rtx_instrument_configuration& configuration,
        _In_ const bool master_slave,
        _In_ const oscilloscope_quantity& level,
        _In_ const oscilloscope_trigger_slope slope) {
    if ((instruments == nullptr) || (cnt < 1)) {
        // Bail out if there is nothing to configure.
        return;
    }

    // If the first instrument was requested to beep, remember this as we want
    // to beep all subsequent instruments once more.
    const auto beep = (configuration.beep_on_apply() > 0);

    if (master_slave || beep) {
        // If we have a master-slave configurations or the instruments should
        // beep, each configuration is individual, so we need to adjust them in
        // the loop.
        auto config = configuration;

        for (std::size_t i = 0; i < cnt; ++i) {
            if (master_slave && (i == 1)) {
                config = config.as_slave(0, level, slope);
            }
            if (beep) {
                config.beep_on_apply(configuration.beep_on_apply() + i);
            }

            configuration.apply(instruments[i]);
        }

    } else {
        // In the trivial case, just apply the same stuff to all instruments.
        for (std::size_t i = 0; i < cnt; ++i) {
            configuration.apply(instruments[i]);
        }
    }
}


/*
 * visus::power_overwhelming::rtx_instrument_configuration::apply
 */
std::size_t visus::power_overwhelming::rtx_instrument_configuration::apply(
        _In_reads_(cnt) rtx_instrument *instruments,
        _In_ const std::size_t cnt,
        _In_ const rtx_instrument_configuration& configuration,
        _In_z_ const wchar_t *master,
        _In_ const oscilloscope_quantity& level,
        _In_ const oscilloscope_trigger_slope slope) {
    if (master == nullptr) {
        throw std::invalid_argument("A valid name for the master instrument "
            "must be supplied.");
    }

    auto m = convert_string<char>(master);
    return apply(instruments, cnt, configuration, m.c_str(), level, slope);
}


/*
 * visus::power_overwhelming::rtx_instrument_configuration::apply
 */
std::size_t visus::power_overwhelming::rtx_instrument_configuration::apply(
        _In_reads_(cnt) rtx_instrument *instruments,
        _In_ const std::size_t cnt,
        _In_ const rtx_instrument_configuration& configuration,
        _In_z_ const char *master,
        _In_ const oscilloscope_quantity& level,
        _In_ const oscilloscope_trigger_slope slope) {
    auto retval = cnt;

    if (master == nullptr) {
        throw std::invalid_argument("A valid name for the master instrument "
            "must be supplied.");
    }

    if ((instruments == nullptr) || (cnt < 1)) {
        // Bail out if there is nothing to configure.
        return retval;
    }

    auto beeps = configuration.beep_on_apply();
    auto slave_configuration = configuration.as_slave(beeps, level, slope);

    for (std::size_t i = 0; i < cnt; ++i) {
        std::vector<char> name(instruments[i].name(nullptr, 0));
        instruments[i].name(name.data(), name.size());

        if (::strcmp(name.data(), master) == 0) {
            configuration.apply(instruments[i]);
            retval = i;
        } else {
            if (beeps > 0) {
                slave_configuration.beep_on_apply(++beeps);
            }

            slave_configuration.apply(instruments[i]);
        }
    }

    return retval;
}


/*
 * ...::rtx_instrument_configuration::rtx_instrument_configuration
 */
visus::power_overwhelming::rtx_instrument_configuration::rtx_instrument_configuration(
        _In_ const oscilloscope_quantity time_range,
        _In_ const unsigned int samples,
        _In_ visa_instrument::timeout_type timeout)
    : _beep_on_apply(0),
        _beep_on_error(false),
        _beep_on_trigger(false),
        _slave(false),
        _timeout(0),
        _time_range(time_range),
        _trigger("EXT") {
    this->_acquisition.points(samples).segmented(true);
    this->_trigger.external().mode(oscilloscope_trigger_mode::automatic);
}


/*
 * ...::rtx_instrument_configuration::rtx_instrument_configuration
 */
visus::power_overwhelming::rtx_instrument_configuration::rtx_instrument_configuration(
        _In_ const oscilloscope_quantity time_range,
        _In_ const oscilloscope_single_acquisition& acquisition,
        _In_ const oscilloscope_edge_trigger& trigger,
        _In_ visa_instrument::timeout_type timeout) 
    : _acquisition(acquisition),
        _beep_on_apply(0),
        _beep_on_error(false),
        _beep_on_trigger(false),
        _slave(false),
        _timeout(timeout),
        _time_range(time_range),
        _trigger(trigger) { }


/*
 * visus::power_overwhelming::rtx_instrument_configuration::as_slave
 */
visus::power_overwhelming::rtx_instrument_configuration
visus::power_overwhelming::rtx_instrument_configuration::as_slave(
        _In_ const std::size_t beep,
        _In_ const oscilloscope_quantity& level,
        _In_ const oscilloscope_trigger_slope slope) const {
    rtx_instrument_configuration retval(*this);
    retval._slave = true;
    retval._trigger.external(level, slope);
    retval._beep_on_apply = beep;
    return retval;
}


/*
 * visus::power_overwhelming::rtx_instrument_configuration::apply
 */
void visus::power_overwhelming::rtx_instrument_configuration::apply(
        _Inout_ rtx_instrument& instrument) const {
    // Change the timeout before perfoming any operations that might time out.
    if (this->_timeout > 0) {
        instrument.timeout(this->_timeout);
    }

    instrument.time_range(this->_time_range)
        .trigger_output(oscilloscope_trigger_output::pulse)
        .trigger(this->_trigger)
        .acquisition(this->_acquisition, false, false)
        .operation_complete();

    // Note: Beep will do nothing if the count is zero.
    instrument.beep(this->_beep_on_apply);
}


/*
 * visus::power_overwhelming::rtx_instrument_configuration::beep_on_apply
 */
visus::power_overwhelming::rtx_instrument_configuration&
visus::power_overwhelming::rtx_instrument_configuration::beep_on_apply(
        _In_ const std::size_t count) noexcept {
    this->_beep_on_apply = count;
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument_configuration::beep_on_error
 */
visus::power_overwhelming::rtx_instrument_configuration&
visus::power_overwhelming::rtx_instrument_configuration::beep_on_error(
        _In_ const bool enable) noexcept {
    this->_beep_on_error = enable;
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument_configuration::beep_on_trigger
 */
visus::power_overwhelming::rtx_instrument_configuration&
visus::power_overwhelming::rtx_instrument_configuration::beep_on_trigger(
        _In_ const bool enable) noexcept {
    this->_beep_on_trigger = enable;
    return *this;
}
