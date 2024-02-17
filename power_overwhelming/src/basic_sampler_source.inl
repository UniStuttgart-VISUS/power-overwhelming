// <copyright file="basic_sampler_source.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * ...::detail::basic_sampler_source<TDerived>::deliver
 */
template<class TDerived>
bool visus::power_overwhelming::detail::basic_sampler_source<TDerived>::deliver(
        void) const {
    auto that = static_cast<const TDerived *>(this);
    return that->async_sampling.deliver(that->sensor_name.c_str(),
        that->sample(that->async_sampling.resolution()));
}


/*
 * visus::power_overwhelming::detail::basic_sampler_source<TDerived>::interval
 */
template<class TDerived>
typename visus::power_overwhelming::detail::basic_sampler_source<TDerived>::interval_type
visus::power_overwhelming::detail::basic_sampler_source<TDerived>::interval(
        void) const noexcept {
    return interval_type(this->async_sampling.interval());
}
