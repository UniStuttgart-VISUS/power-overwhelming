// <copyright file="async_sampling.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * ...::power_overwhelming::async_sampling::delivers_measurement_data_to_functor
 */
template<class TFunctor>
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::delivers_measurement_data_to_functor(
        _In_ TFunctor&& callback) {
    typedef std::function<void(const wchar_t *, const measurement_data *,
        const std::size_t)> function_type;
    this->stores_and_passes_context(function_type(
        std::forward<TFunctor>(callback)));
    this->delivers_measurement_data_to([](const wchar_t *n,
            const measurement_data *m, const size_t s, void *c) {
        (*static_cast<function_type *>(c))(n, m, s);
    });
    return *this;
}


/*
 * visus::power_overwhelming::async_sampling::stores_and_passes_context
 */
template<class TContext>
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::stores_and_passes_context(
        _In_ const TContext& context) {
    // Free previous object-owned context, if any.
    this->passes_context(nullptr);

    // Allocate memory for the copy of the context.
    this->_context = operator new(sizeof(TContext));

    // Install the deleter. This must be done before assigning the context as
    // the assignment operator might throw.
    this->_context_deleter = [](void *c) { operator delete(c); };

    // Copy the context.
    new (this->_context) TContext(context);

    // Update the deleter to include the destructor if the copy was a success.
    this->_context_deleter = [](void *c) {
        static_cast<TContext *>(c)->~TContext();
        operator delete(c);
    };

    return *this;
}


/*
 * visus::power_overwhelming::async_sampling::stores_and_passes_context
 */
template<class TContext>
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::stores_and_passes_context(
        _In_ TContext&& context) {
    // Free previous object-owned context, if any.
    this->passes_context(nullptr);

    // Allocate memory for the new context and move it in.
    this->_context = operator new(sizeof(TContext));
    new (this->_context) TContext(std::move(context));

    // Install the deleter at the end. Note that move must not throw.
    this->_context_deleter = [](void *c) {
        static_cast<TContext *>(c)->~TContext();
        operator delete(c);
    };

    return *this;
}
