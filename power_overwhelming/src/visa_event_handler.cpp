// <copyright file="visa_event_handler.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_VISA)
#include "visus/pwrowg/visa_event_handler.h"

#include "visus/pwrowg/visa_instrument.h"

#include "visa_error_category.h"
#include "visa_instrument_impl.h"


/*
 * PWROWG_DETAIL_NAMESPACE::visa_event_handler::visa_event_handler
 */
PWROWG_DETAIL_NAMESPACE::visa_event_handler::visa_event_handler(
        _In_ visa_instrument& instrument,
        _In_ const ViEventType type,
        _In_ const ViHndlr handler,
        _In_ const destructor_type dtor) noexcept
    : _dtor(dtor),
        _handler(handler),
        _instrument(instrument),
        _type(type) {
    assert(this->_dtor != nullptr);
    assert(this->_handler != nullptr);
    assert(this->_instrument);
}

#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
