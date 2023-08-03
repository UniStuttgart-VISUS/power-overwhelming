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
        // The device it not being sampled, so we need a new source.
        auto retval = new device_sampler_source(sensor);
        _sources[sensor->device] = retval;
        return retval;

    } else {
        // We know the device already, so we need to make sure that the sampling
        // intervals match and the same sensor is not yet sampled.
        auto& sensors = it->second->_sensors;

        if (!sensors.empty()) {
            auto duplicate = std::find(sensors.begin(), sensors.end(), sensor);
            if (duplicate != sensors.end()) {
                throw std::invalid_argument("Asynchronous sampling cannot be "
                    "started on a sensor that is already being sampled.");
            }

            const auto& actual = sensors.front()->async_sampling;
            const auto& requested = sensor->async_sampling;

            if (actual.interval() != requested.interval()) {
                throw std::invalid_argument("Sensors from the same device can "
                    "only be asynchronosly sampled at the same rate.");
            }
        }

        sensors.push_back(sensor);
        return it->second;
    }
}


/*
 * ...::detail::device_sampler_source<TSensor, TDevice>::release
 */
template<class TSensor, class TDevice>
bool visus::power_overwhelming::detail::device_sampler_source<TSensor,
        TDevice>::release(_In_opt_ sensor_type sensor) {
    auto retval = false;

    if (sensor != nullptr) {
        std::lock_guard<decltype(_lock)> l(_lock);
        for (auto& s : _sources) {
            auto& sensors = s.second->_sensors;
            auto it = std::find(sensors.begin(), sensors.end(), sensor);
            retval = (it != sensors.end());

            if (retval) {
                // Erase the sensor from the per-device list of sensors being
                // sampled. This has the effect that the source will
                // self-destruct once it is sampled the next time. This in turn
                // will cause the sampler thread to remove the source from the
                // list of sources it samples.
                sensors.erase(it);
            }
        }
    }

    return retval;
}


/*
 * ...::detail::device_sampler_source<TSensor, TDevice>::deliver
 */
template<class TSensor, class TDevice>
bool visus::power_overwhelming::detail::device_sampler_source<TSensor,
        TDevice>::deliver(void) const {
    auto retval = !this->_sensors.empty();

    if (retval) {
        auto sample = TSensor::sample(this->_sensors.front()->device);
        for (auto& s : this->_sensors) {
            return s->evaluate_async(sample);
        }

    } else {
        // If we have nothin left to do, unregister the device from the master
        // sensor list of the sampler source.
        std::lock_guard<decltype(_lock)> l(_lock);
        auto it = std::find_if(_sources.begin(), _sources.end(),
                [this](const std::pair<device_type, source_type>& p) {
            return (p.second == this);
        });
        _sources.erase(it, _sources.end());

        // Self-destruct and rely on the sampler thread not calling again if we
        // return false from there.
        delete this;
    }

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
    return (this->_sensors.empty())
        ? interval_type(0)
        : interval_type(this->_sensors.front()->async_sampling.interval());
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
        TDevice>::device_sampler_source(_In_ sensor_type sensor)
    : _sensors({ sensor }) { }
