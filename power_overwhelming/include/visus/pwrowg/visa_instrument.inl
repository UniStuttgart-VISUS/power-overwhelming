// <copyright file="visa_instrument.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::visa_instrument::on_operation_complete
 */
template<class TCallback>
PWROWG_DETAIL_NAMESPACE::visa_event_handler *
PWROWG_NAMESPACE::visa_instrument::on_operation_complete(
        _In_ const TCallback& callback) {
    auto es = this->event_status();
    this->event_status(es | visa_event_status::operation_complete);
    auto ss = this->service_request_status();
    this->service_request_status(ss | visa_status_byte::master_status);

    auto retval = this->on_event(VI_EVENT_SERVICE_REQ, [callback](
            visa_instrument& i, ViEventType t, const visa_object&) {
        assert(t == VI_EVENT_SERVICE_REQ);
        // According to
        // https://www.ni.com/docs/de-DE/bundle/ni-visa/page/ni-visa/vi_event_service_req.html,
        // we must read the status byte here for the callback to work. We have
        // to do that anyway, because this seems to be the only way to
        // distinguish between OPC events and other status changes.
        // It is not necessary for us to delete the event object, because the
        // framework will wrap it into an RAII object for us that will
        // automatically release it once this callback returns.
        if (i.status() && visa_status_byte::operation_status) {
            auto events = i.event_status();
            if (events && visa_event_status::operation_complete) {
                callback(i);
            }
        }

        return VI_SUCCESS;
    });

    this->enable_event(VI_EVENT_SERVICE_REQ, VI_HNDLR);
    return retval;
}


/*
 * PWROWG_NAMESPACE::visa_instrument::write
 */
template<class TChar, class TTraits, class TAlloc>
const PWROWG_NAMESPACE::visa_instrument&
PWROWG_NAMESPACE::visa_instrument::write(
        _In_ const std::basic_string<TChar, TTraits, TAlloc>& str) const {
    return this->write(str.c_str());
}
