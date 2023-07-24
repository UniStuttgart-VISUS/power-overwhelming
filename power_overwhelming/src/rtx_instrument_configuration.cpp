// <copyright file="rtx_instrument_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/rtx_instrument_configuration.h"


/*
 * ...::rtx_instrument_configuration::rtx_instrument_configuration
 */
visus::power_overwhelming::rtx_instrument_configuration::rtx_instrument_configuration(
        _In_ const oscilloscope_quantity time_range,
        _In_ const unsigned int samples,
        _In_ visa_instrument::timeout_type timeout)
    : _slave(false), _timeout(0), _time_range(time_range),
        _trigger(external_trigger()) {
    this->_acquisition.points(samples).segmented(true);
    this->_trigger.mode(oscilloscope_trigger_mode::automatic);
}


/*
 * ...::rtx_instrument_configuration::rtx_instrument_configuration
 */
visus::power_overwhelming::rtx_instrument_configuration::rtx_instrument_configuration(
        _In_ const oscilloscope_quantity time_range,
        _In_ const oscilloscope_acquisition& acquisition,
        _In_ const oscilloscope_edge_trigger& trigger,
        _In_ visa_instrument::timeout_type timeout) 
    : _acquisition(acquisition),
        _slave(false),
        _timeout(timeout),
        _time_range(time_range),
        _trigger(trigger) {
    this->_acquisition.state(oscilloscope_acquisition_state::unknown);
}


/*
 * visus::power_overwhelming::rtx_instrument_configuration::acquisition
 */
const visus::power_overwhelming::oscilloscope_acquisition&
visus::power_overwhelming::rtx_instrument_configuration::acquisition(
        void) const noexcept {
    return this->_acquisition;
}


/*
 * visus::power_overwhelming::rtx_instrument_configuration::as_slave
 */
visus::power_overwhelming::rtx_instrument_configuration
visus::power_overwhelming::rtx_instrument_configuration::as_slave(void) const {
    rtx_instrument_configuration retval(*this);
    retval._slave = true;
    retval._trigger = external_trigger();
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

    // Create a preliminary trigger configuration that triggers automatically
    // and thus makes sure that switching to single mode acquisition will
    // complete even if there is no valid trigger signal available.
    auto preliminary_trigger = this->_trigger;
    preliminary_trigger.mode(oscilloscope_trigger_mode::automatic);

    // Apply the configuration changes. Note that the order of changes is
    // deliberate for automatic changes the instrument may make to be most
    // predictable.
    instrument.time_range(this->_time_range)
        .trigger_output(oscilloscope_trigger_output::pulse)
        .trigger(preliminary_trigger)
        .acquisition(this->_acquisition, true)
        .operation_complete();

    // Apply the actual trigger, which might make time out the acquisition if
    // it is using normal mode and there is no actual trigger present.
    instrument.trigger(this->_trigger)
        .operation_complete();
}


/*
 * visus::power_overwhelming::rtx_instrument_configuration::external_trigger
 */
visus::power_overwhelming::oscilloscope_edge_trigger
visus::power_overwhelming::rtx_instrument_configuration::external_trigger(
        void) {
    // The external trigger usually uses 5V if passed on via the AUX output, so
    // 2.5 V is a safe bet.
    return oscilloscope_edge_trigger("EXT")
        .level(5, oscilloscope_quantity(2.5, "V"))
        .slope(oscilloscope_trigger_slope::rising);
}
