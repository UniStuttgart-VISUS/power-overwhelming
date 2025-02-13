// <copyright file="sensor_list.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_list<TSensor>::sample
 */
template<class TSensor>
void PWROWG_DETAIL_NAMESPACE::sensor_list<TSensor>::sample(
        _In_ const std::size_t begin,
        _In_ const std::size_t cnt,
        _In_ const sensor_array_callback callback,
        _In_opt_ void *context) {
    assert(begin + cnt < this->sensors.size());
    assert(callback != nullptr);
    assert(this->sampler != nullptr);

    auto it = this->sensors.begin();
    std::advance(it, begin);

    for (std::size_t i = 0; i < cnt; ++i, ++it) {
        (it.*this->sampler)(callback, context);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_list<TSensor>::sample
 */
template<class TSensor>
bool PWROWG_DETAIL_NAMESPACE::sensor_list<TSensor>::sample(
        _In_ const sensor_array_callback callback,
        _In_ const std::chrono::milliseconds interval,
        _In_opt_ void *context) {
    constexpr auto retval = detail::has_async_sample<T>::type::value;

    if (retval) {
        for (auto& it : this->sensors) {
            it.sample(callback, interval, context);
        }
    }

    return retval;
}
