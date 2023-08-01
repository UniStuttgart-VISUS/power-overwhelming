// <copyright file="sampler_collection.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * ...::power_overwhelming::detail::basic_sampler_collection<TSampler>::default
 */
template<class TSampler>
visus::power_overwhelming::detail::basic_sampler_collection<TSampler>
visus::power_overwhelming::detail::basic_sampler_collection<TSampler>::default;


/*
 * visus::power_overwhelming::detail::basic_sampler_collection<TSampler>::add
 */
template<class TSampler>
bool visus::power_overwhelming::detail::basic_sampler_collection<TSampler>::add(
        _In_ source_type source, _Inout_ async_sampling&& sampling) {
    auto retval = false;

    if ((source != nullptr) && sampling) {
        std::lock_guard<decltype(that->lock)> l(that->lock);

        // Find out whether we are already sampling the given source and if not
        // whether we have a sampler at the requested interval.
        auto sampler = this->_samplers.end();
        for (auto it = this->_samplers.begin(), end = this->_samplers.end();
                it != end; ++it) {
            if (**it.samples(source)) {
                // A sensor can only be sampled once.
                return false;
            }

            if (**it.interval() == sampling.interval()) {
                // This is the sampler with the same interval. We cannot leave
                // the loop here as we need to check whether the source is
                // registered in *any* sampler.
                sampler = it;
            }
        }

        if (sampler != this->_samplers.end()) {
            // Add the source to the existing sampler for the interval.
            source.update_async(std::move(sampling));
            **sampler += source;

        } else {
            // We need a new sampler for the given interval.
            this->_samplers.emplace_back(sampling.interval());
            source.update_async(std::move(sampling));
            this->_samplers.back() += source;
        }

        retval = true;
    }

    return retval;
}


/*
 * visus::power_overwhelming::detail::basic_sampler_collection<TSampler>::remove
 */
template<class TSampler>
bool visus::power_overwhelming::detail::basic_sampler_collection<TSampler>::remove(
        _In_ const source_type source) {
    if (source == nullptr) {
        // Trivial reject as this could have been never added.
        return false;
    }


    throw "TODO";
    return false;
}


/*
 * ...::detail::basic_sampler_collection<TSampler>::operator bool
 */
template<class TSampler>
visus::power_overwhelming::detail::basic_sampler_collection<TSampler>::operator bool(
        void) const {
    std::lock_guard<decltype(that->lock)> l(that->lock);
    return !this->_samplers.empty();
}
