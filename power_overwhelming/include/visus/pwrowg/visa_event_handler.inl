// <copyright file="visa_event_handler.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::visa_event_handler::create
 */
template<class TCallback>
_Ret_valid_ PWROWG_DETAIL_NAMESPACE::visa_event_handler *
PWROWG_DETAIL_NAMESPACE::visa_event_handler::create(
        _In_ visa_instrument& instrument,
        _In_ const ViEventType event_type,
        _In_ TCallback&& callback) {
    typedef std::decay_t<TCallback> callback_type;
    return new (std::forward<TCallback>(callback)) visa_event_handler(
        instrument, event_type, invoke<callback_type>, dtor<callback_type>);
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_event_handler::operator new
 */
template<class TContext>
void *PWROWG_DETAIL_NAMESPACE::visa_event_handler::operator new(
        _In_ const std::size_t size,
        _In_ TContext&& context) {
    typedef std::decay_t<TContext> context_type;
    auto retval = ::operator new(size + sizeof(context_type));
    assert(retval != nullptr);

    try {
        auto ctx = reinterpret_cast<std::uint8_t *>(retval) + size;
        new (ctx) context_type(std::forward<TContext>(context));
    } catch (...) {
        ::operator delete(retval);
        throw;
    }

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_event_handler::dtor
 */
template<class TContext>
void PWROWG_DETAIL_NAMESPACE::visa_event_handler::dtor(
        _In_ _In_ visa_event_handler *ptr) noexcept {
    assert(ptr != nullptr);
    auto ctx = reinterpret_cast<TContext *>(ptr + 1);
    ctx->~TContext();
}


/*
 * PWROWG_DETAIL_NAMESPACE::visa_event_handler::invoke
 */
template<class TCallback>
ViStatus _VI_FUNCH PWROWG_DETAIL_NAMESPACE::visa_event_handler::invoke(
        _In_ const ViSession session,
        _In_ const ViEventType event_type,
        _In_ ViEvent event,
        _In_ ViAddr context) {
    assert(context != nullptr);
    auto that = static_cast<visa_event_handler *>(context);
    assert(that != nullptr);
    auto cb = reinterpret_cast<TCallback *>(that + 1);
    visa_object evt(std::move(event));
    assert(evt);
    assert(event == VI_NULL);
    return (*cb)(that->_instrument, event_type, evt);
}
