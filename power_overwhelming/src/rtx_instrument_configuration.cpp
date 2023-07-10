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
        _In_ visa_instrument::timeout_type timeout)
    : _slave(false), _timeout(0), _time_range(time_range),
        _trigger(external_trigger()) {
    this->_acquisition.enable_automatic_points().segmented(true);
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
        _slave(false),
        _timeout(timeout),
        _time_range(time_range),
        _trigger(trigger) { }


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

    // Apply the configuration changes. Note that the order of changes is
    // deliberate for automatic changes the instrument may make to be most
    // predictable.
    instrument.time_range(this->_time_range)
        .acquisition(this->_acquisition)
        .trigger_output(oscilloscope_trigger_output::pulse)
        .trigger(this->_trigger)
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
        .level(5, oscilloscope_quantity(2.5, "V"));
}
