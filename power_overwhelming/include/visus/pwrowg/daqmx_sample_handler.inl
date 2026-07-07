// <copyright file="daqmx_sample_handler.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sample_handler::install
 */
template<class TCallback>
_Ret_valid_ PWROWG_DETAIL_NAMESPACE::daqmx_sample_handler *
PWROWG_DETAIL_NAMESPACE::daqmx_sample_handler::install(
        _In_ daqmx_task& task,
        _In_ const daqmx_sample_event_type type,
        _In_ const uInt32 samples,
        _In_ TCallback&& callback) {
    typedef std::decay_t<TCallback> callback_type;
    typedef daqmx_sample_handler handler_type;
    std::unique_ptr<handler_type> retval(
        new (std::forward<TCallback>(callback)) handler_type(
        task, type, dtor<callback_type>));
    retval->install(samples, invoke<callback_type>);
    return retval.release();
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sample_handler::invoke
 */
template<class TCallback>
int32 CVICALLBACK PWROWG_DETAIL_NAMESPACE::daqmx_sample_handler::invoke(
        _In_ const TaskHandle task,
        _In_ const int32 type,
        _In_ const uInt32 cnt,
        _In_ void *context) {
    const auto t = static_cast<daqmx_sample_event_type>(type);
    assert(context != nullptr);
    auto that = static_cast<daqmx_sample_handler *>(context);
    assert(that != nullptr);
    auto cb = reinterpret_cast<TCallback *>(that + 1);
    return (*cb)(that->_task, t, cnt);
}
