#include "device_sampler_source.h"
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
        auto retval = new device_sampler_source();
        _sources[sensor->device] = retal;
        return retval;

    } else {
        // We know the device already, so we need to make sure that the sampling
        // intervals match and the same sensor is not yet sampled.

        if (!it->_sensors.empty()) {
            auto duplicate = std::find(it->_sensors.begin(), it->_sensors.end(),
                sensor);
            if (duplicate != it->_sensors.end()) {
                throw std::invalid_argument("Asynchronous sampling cannot be "
                    "started on a sensor that is already being sampled.");
            }

            const auto& actual = it->_sensors.front().async_sampling;
            const auto& requested = sensor->async_sampling;

            if (actual.interval() != requested.interval()) {
                throw std::invalid_argument("Sensors from the same device can "
                    "only be asynchronosly sampled at the same rate.");
            }
        }

        it->_sensors.push_back(sensor);
    }

    return *it;
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
            auto it = std::find(s.second.begin(), s.second.end(), sensor);
            retval = (it != s.second.end());

            if (retval) {
                // Erase the sensor from the per-device list of sensors being
                // sampled. This has the effect that the source will
                // self-destruct once it is sampled the next time. This in turn
                // will cause the sampler thread to remove the source from the
                // list of sources it samples.
                s.second.erase(it);
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
        for (auto& s : this->_sensors) {
            // TODO: We could think about a way to optimise this using the devices ...
            return s->async_sampling.deliver(s->sensor_name.c_str(),
                s->sample(s->async_sampling.resolution()));
        }
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
        ? 0
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
    : _sensor({ sensor }) { }
