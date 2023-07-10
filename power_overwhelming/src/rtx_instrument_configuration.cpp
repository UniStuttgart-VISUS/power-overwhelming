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
        : _slave(false), _timeout(0), _time_range(time_range) {
    this->_acquisition.enable_automatic_points().segmented(true);
}


/*
 * ...::rtx_instrument_configuration::rtx_instrument_configuration
 */
visus::power_overwhelming::rtx_instrument_configuration::rtx_instrument_configuration(
        _In_ const oscilloscope_quantity time_range,
        _In_ const oscilloscope_single_acquisition& acquisition,
        _In_ visa_instrument::timeout_type timeout) 
    : _acquisition(acquisition),
        _slave(false),
        _timeout(timeout),
        _time_range(time_range) { }


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
        .operation_complete();

    //instrument.trigger(oscilloscope_edge_trigger())
}
