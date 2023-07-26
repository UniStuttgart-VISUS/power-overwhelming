// <copyright file="sampler_context.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * ...::basic_sampler_context<TSource, TContext>::basic_sampler_context
 */
template<class TSource, class TContext>
visus::power_overwhelming::detail::basic_sampler_context<TSource, TContext>
::basic_sampler_context(
        _In_ source_type *source,
        _Inout_ async_sampling&& configuration)
        : source(nullptr) {
    if (source == nullptr) {
        throw std::invalid_argument("A valid source must be provided to "
            "initialise a sampler source.");
    }
    if (!configuration) {
        throw std::invalid_argument("A valid callback must be provided to "
            "initialise a sampler source.");
    }

    this->configuration = std::move(configuration);
    this->source = this->source;
}
