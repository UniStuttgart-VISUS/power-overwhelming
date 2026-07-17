// <copyright file="daqmx_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sensor::from_descriptions
 */
template<class TInput>
TInput PWROWG_DETAIL_NAMESPACE::daqmx_sensor::from_descriptions(
        _In_ list_type& dst,
        _In_ sample::source_type index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config) {
    typedef sensor_description_builder builder_type;
    typedef sensor_description desc_type;
    assert(owner != nullptr);

    // Move the NI-DAQmx sensor to the front of the list.
    auto retval = move_front_if(begin, end, is_daqmx_sensor);

    // If there is no NI-DAQmx-based sensor, bail out directly.
    if (begin == retval) {
        return retval;
    }

    // Create the sensor, which is always one managing every sensor within
    // [begin, retval[.
    dst.emplace_back(begin, retval, index, owner, config);

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sensor::daqmx_sensor
 */
template<class TIterator> PWROWG_DETAIL_NAMESPACE::daqmx_sensor::daqmx_sensor(
        _In_ const TIterator begin,
        _In_ const TIterator end,
        _In_ std::size_t index,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config)
    : _index(index),
        _owner(owner),
        _trigger(config.trigger()) {
    typedef sensor_description_builder builder_type;
    typedef daqmx_sensor_definition private_type;
    assert(this->_trigger._impl != nullptr);
    auto trigger = this->_trigger._impl;

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    std::transform(begin, end,
        std::back_inserter(this->_sensors),
        [](const auto& d) {
            return *builder_type::private_data<private_type>(d);
        });

    // Note: we need to keep track of the channels that have already been
    // activated, because voltage and current channels might be used
    // individually and as a computed power channel.
    std::set<std::string> known;
    const auto is_unknown = [&known](const auto *channel) {
        if (channel == nullptr) {
            PWROWG_TRACE(_T("Ignoring invalid channel."));
            return false;
        }

        const auto retval = (known.find(channel->channel()) == known.end());

        if (retval) {
            PWROWG_TRACE("Channel \"%s\" is not yet known.",
                channel->channel());
            known.insert(channel->channel());
        }

        return retval;
    };

    PWROWG_TRACE(_T("Adding %zu channel(s) to DAQmx task."),
        this->_sensors.size());
    for (auto& s : this->_sensors) {
        if (is_unknown(s.current_channel())) {
            trigger->task += *s.current_channel();
        }
        if (is_unknown(s.power_channel())) {
            trigger->task += *s.power_channel();
        }
        if (is_unknown(s.voltage_channel())) {
            trigger->task += *s.voltage_channel();
        }
        if (is_unknown(s.voltage_for_current_channel())) {
            trigger->task += *s.voltage_for_current_channel();
        }
    }

    PWROWG_TRACE(_T("Configuring DAQmx task timing."));
    trigger->task.timing(config.timing());

    if (trigger->trigger != nullptr) {
        PWROWG_TRACE(_T("Configuring DAQmx trigger."));
        //trigger->task.trigger(*trigger->trigger);
    }

    trigger->task.on_sample(10, [this](_In_ daqmx_task& task,
            const daqmx_sample_event_type, _In_ const uInt32 cnt) {
        return 0;
    });

    // Register a handler that clears the running flag from the task when it is
    // done. This cannot be done until there is at least one channel in the
    // task.
    trigger->task.on_done([trigger](const daqmx_task&, const int32) {
        PWROWG_TRACE(_T("Mark sensor as done on DAQmx task finishing."));
        constexpr auto mask = sensor_trigger_state::running;
        atomic_unset(trigger->state, mask);
        return 0;
    });
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
}
