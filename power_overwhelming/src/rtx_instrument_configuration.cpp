// <copyright file="rtx_instrument_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/rtx_instrument_configuration.h"


/*
 * visus::power_overwhelming::rtx_instrument_configuration::apply
 */
void visus::power_overwhelming::rtx_instrument_configuration::apply(
        _Inout_ rtx_instrument& instrument) const {
    // Change the timeout before perfoming any operations that might time out.
    instrument.timeout(this->_timeout);

    // Apply the configuration changes. Note that the order of changes is
    // deliberate for automatic changes the instrument may make to be most
    // predictable.
    instrument.time_range(this->_time_range)
        .acquisition(this->_acquisition)
        .operation_complete();
}
