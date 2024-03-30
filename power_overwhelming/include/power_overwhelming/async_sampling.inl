// <copyright file="async_sampling.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
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
    // TODO: We could further optimise this and store the context in
    // the pointer if we discover that it is at most sizeof(intptr)
    return this->stores_and_passes_context(new TContext(context),
        [](void *c) { delete static_cast<TContext *>(c); });
    return *this;
}


/*
 * visus::power_overwhelming::async_sampling::stores_and_passes_context
 */
template<class TContext>
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::stores_and_passes_context(
        _In_ TContext&& context) {
    typedef typename std::decay<TContext>::type context_type;
    // TODO: We could further optimise this and store the context in
    // the pointer if we discover that it is at most sizeof(intptr)
    return this->stores_and_passes_context(new context_type(std::move(context)),
        [](void *c) { delete static_cast<context_type *>(c); });
    return *this;
}
