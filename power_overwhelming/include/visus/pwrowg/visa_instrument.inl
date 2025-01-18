// <copyright file="visa_instrument.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::visa_instrument::on_operation_complete
 */
template<class TContext>
visus::power_overwhelming::visa_instrument&
visus::power_overwhelming::visa_instrument::on_operation_complete_ex(
        _In_opt_ void (*callback)(visa_instrument&, void *),
        _Inout_ TContext&& context) {
    // Allocate memory for the new context and move it in.
    auto ctx = operator new(sizeof(TContext));
    new (ctx) TContext(std::move(context));

    // Install the callback and context with a custom deleter.
    this->on_operation_complete(callback, ctx, [](void *c) {
        assert(c != nullptr);
        static_cast<TContext *>(c)->~TContext();
        operator delete(c);
    });

    return *this;
}


/*
 * visus::power_overwhelming::visa_instrument::on_operation_complete_ex
 */
template<class TFunctor>
visus::power_overwhelming::visa_instrument&
visus::power_overwhelming::visa_instrument::on_operation_complete_ex(
        _In_ TFunctor&& callback) {
    typedef std::function<void(visa_instrument&)> callback_type;
    callback_type cb(std::forward<TFunctor>(callback));
    return this->on_operation_complete_ex([](visa_instrument& i, void *c) {
        (*static_cast<callback_type *>(c))(i);
    }, std::move(cb));
}


/*
 * visus::power_overwhelming::visa_instrument::write
 */
template<class TChar>
const visus::power_overwhelming::visa_instrument&
visus::power_overwhelming::visa_instrument::write(
        _In_ const std::basic_string<TChar>& str) const {
    return this->write(str.c_str());
}
