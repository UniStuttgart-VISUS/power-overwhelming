// <copyright file="device_sampler_source.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>



/*
 * ...::detail::device_sampler_source<TSensor, TDevice>::create
 */
template<class TSensor, class TDevice>
_Ret_valid_ typename visus::power_overwhelming::detail::device_sampler_source<
    TSensor, TDevice>::source_type
visus::power_overwhelming::detail::device_sampler_source<TSensor,
        TDevice>::create(_In_ sensor_type sensor) {
    if (sensor == nullptr) {
        throw std::invalid_argument("A device_sampler_source can only be "
            "created for a valid sensor.");
    }
    if (!sensor->device) {
        throw std::invalid_argument("A device_sampler_source can only be "
            "created if the sensor has a valid source device.");
    }

    std::lock_guard<decltype(_lock)> l(_lock);
    auto it = _sources.find(sensor->device);
    if (it == _sources.end()) {

    }

    throw "TODO";
    return nullptr;
}


/*
 * ...::detail::device_sampler_source<TSensor, TDevice>::deliver
 */
template<class TSensor, class TDevice>
bool visus::power_overwhelming::detail::device_sampler_source<TSensor,
        TDevice>::deliver(void) const {
    auto retval = (this->_sensor != nullptr);
    return retval;
}


/*
 * ...::detail::device_sampler_source<TSensor, TDevice>::interval
 */
template<class TSensor, class TDevice>
typename visus::power_overwhelming::detail::device_sampler_source<TSensor,
    TDevice>::interval_type
visus::power_overwhelming::detail::device_sampler_source<TSensor,
        TDevice>::interval(void) const noexcept {
    return (this->_sensor != nullptr)
        ? interval_type(this->_sensor->async_sampling.interval)
        : 0;
}


/*
 * ...::detail::device_sampler_source<TSensor, TDevice>::_lock
 */
template<class TSensor, class TDevice>
std::mutex visus::power_overwhelming::detail::device_sampler_source<TSensor,
    TDevice>::_lock;


/*
 * ...::detail::device_sampler_source<TSensor, TDevice>::_sources
 */
template<class TSensor, class TDevice>
std::map<
    typename visus::power_overwhelming::detail::device_sampler_source<TSensor,
        TDevice>::device_type,
    typename visus::power_overwhelming::detail::device_sampler_source<TSensor,
        TDevice>::source_type>
visus::power_overwhelming::detail::device_sampler_source<TSensor,
    TDevice>::_sources;


/*
 * ::detail::device_sampler_source<TSensor, TDevice>::device_sampler_source
 */
template<class TSensor, class TDevice>
visus::power_overwhelming::detail::device_sampler_source<TSensor,
    TDevice>::device_sampler_source(void) : _sensor(nullptr) { }
