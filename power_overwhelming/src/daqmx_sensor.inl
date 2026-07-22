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
    // individually and as a computed power channel. The lambda returns
    // the index of the channel in 'channels' and whether it was newly added
    // to the list and should therefore be added to the DAQmx task.
    std::vector<std::string> channels;
    auto it = begin;
    const auto channel_index = [&channels, &it](const auto *channel) {
        constexpr auto invalid = (std::numeric_limits<std::size_t>::max)();
        if (channel == nullptr) {
            PWROWG_TRACE(_T("Ignoring invalid channel."));
            return std::make_pair(invalid, false);
        }

        auto c = PWROWG_NAMESPACE::convert_string<wchar_t>(channel->channel());
        if (!contains(it->path(), c.c_str(), true)) {
            PWROWG_TRACE("Channel \"%s\" is not part of the sensor.",
                channel->channel());
            return std::make_pair(invalid, false);
        }

        for (std::size_t i = 0; i < channels.size(); ++i) {
            if (equals(channels[i], channel->channel(), true)) {
                PWROWG_TRACE("Channel \"%s\" is already known.",
                    channel->channel());
                return std::make_pair(i, false);
            }
        }

        PWROWG_TRACE("Channel \"%s\" is not yet known.", channel->channel());
        const auto index = channels.size();
        channels.emplace_back(channel->channel());
        return std::make_pair(index, true);
    };

    // Answer whether the given channel index is valid.
    const auto valid_channel = [](const std::pair<std::size_t, bool> idx) {
        return (idx.first != (std::numeric_limits<std::size_t>::max)());
    };

    PWROWG_TRACE(_T("Adding channel(s) for %zu sensor(s) to DAQmx task."),
        this->_sensors.size());
    for (std::size_t i = 0; i < this->_sensors.size(); ++i, ++it) {
        assert(it != end);
        const auto& s = this->_sensors[i];  // Shortcut to current sensor.
        const auto id = this->_index + i;   // ID of current sensor.

        // Check whether a channel is available.
        const auto idx_cur = channel_index(s.current_channel());
        const auto idx_pow = channel_index(s.power_channel());
        const auto idx_vol = channel_index(s.voltage_channel());
        const auto idx_vfc = channel_index(s.voltage_for_current_channel());

        // Check what the sensor is measuring.
        const auto is_cur = it->is_sensor_type(sensor_type::current);
        const auto is_pow = it->is_sensor_type(sensor_type::power);
        const auto is_vol = it->is_sensor_type(sensor_type::voltage);

        // Add all active channels to the task.
        if (idx_cur.second && (is_cur || is_pow)) {
            assert(valid_channel(idx_cur));
            assert(s.current_channel() != nullptr);
            trigger->task += *s.current_channel();
        }

        if (idx_pow.second && is_pow) {
            assert(valid_channel(idx_pow));
            assert(s.power_channel() != nullptr);
            trigger->task += *s.power_channel();
        }

        if (idx_vol.second && (is_vol || is_pow)) {
            assert(valid_channel(idx_vol));
            assert(s.voltage_channel() != nullptr);
            trigger->task += *s.voltage_channel();
        }

        if (idx_vfc.second && (is_cur || is_pow)) {
            assert(valid_channel(idx_vfc));
            assert(s.voltage_for_current_channel() != nullptr);
            trigger->task += *s.voltage_for_current_channel();
        }

        // Install sample emitters for all sensors.
        if (is_pow && valid_channel(idx_cur) && (valid_channel(idx_vol))) {
            assert(it->is_sensor_type(sensor_type::power));
            assert(s.voltage_channel() != nullptr);
            assert(s.current_channel() != nullptr);
            PWROWG_TRACE("Configuring sample emitter for DAQ channels \"%s\" "
                "(voltage) and \"%s\" (current).",
                s.voltage_channel()->channel(), s.current_channel()->channel());
            this->_make_sample.push_back([id, idx_cur, idx_vol](
                    _In_ const timestamp timestamp,
                    _In_ const double *values,
                    _In_ const std::size_t stride) {
                assert(values != nullptr);
                const auto voltage = values[idx_vol.first * stride];
                const auto current = values[idx_cur.first * stride];
                const auto value = static_cast<float>(voltage * current);
                return PWROWG_NAMESPACE::sample(id, timestamp, value);
            });

        } else if (is_pow && valid_channel(idx_vfc) && (valid_channel(idx_vol))) {
            assert(it->is_sensor_type(sensor_type::power));
            assert(s.voltage_channel() != nullptr);
            assert(s.voltage_for_current_channel() != nullptr);
            const auto xf = s.volt_per_ampere();
            PWROWG_TRACE("Configuring sample emitter for DAQ channels \"%s\" "
                "(voltage) and \"%s\" (%g A per V).",
                s.voltage_channel()->channel(),
                s.voltage_for_current_channel()->channel(),
                xf);
            this->_make_sample.push_back([id, idx_vfc, idx_vol, xf](
                    _In_ const timestamp timestamp,
                    _In_ const double *values,
                    _In_ const std::size_t stride) {
                assert(values != nullptr);
                const auto voltage = values[idx_vol.first * stride];
                const auto current = values[idx_vfc.first * stride] * xf;
                const auto value = static_cast<float>(voltage * current);
                return PWROWG_NAMESPACE::sample(id, timestamp, value);
            });

        } else if (is_cur && valid_channel(idx_cur)) {
            assert(it->is_sensor_type(sensor_type::current));
            assert(s.current_channel() != nullptr);
            PWROWG_TRACE("Configuring sample emitter for DAQ current channel "
                "\"%s\".", s.current_channel()->channel());
            this->_make_sample.push_back([id, idx_cur](
                    _In_ const timestamp timestamp,
                    _In_ const double *values,
                    _In_ const std::size_t stride) {
                assert(values != nullptr);
                const auto value = static_cast<float>(
                    values[idx_cur.first * stride]);
                return PWROWG_NAMESPACE::sample(id, timestamp, value);
            });

        } else if (is_pow && valid_channel(idx_pow)) {
            assert(it->is_sensor_type(sensor_type::power));
            assert(s.power_channel() != nullptr);
            PWROWG_TRACE("Configuring sample emitter for DAQ power channel "
                "\"%s\".", s.power_channel()->channel());
            this->_make_sample.push_back([id, idx_pow](
                    _In_ const timestamp timestamp,
                    _In_ const double *values,
                    _In_ const std::size_t stride) {
                assert(values != nullptr);
                const auto value = static_cast<float>(
                    values[idx_pow.first * stride]);
                return PWROWG_NAMESPACE::sample(id, timestamp, value);
            });

        } else if (is_vol && valid_channel(idx_vol)) {
            assert(it->is_sensor_type(sensor_type::voltage));
            assert(s.voltage_channel() != nullptr);
            PWROWG_TRACE("Configuring sample emitter for DAQ voltage channel "
                "\"%s\".", s.voltage_channel()->channel());
            this->_make_sample.push_back([id, idx_vol](
                    _In_ const timestamp timestamp,
                    _In_ const double *values,
                    _In_ const std::size_t stride) {
                assert(values != nullptr);
                const auto value = static_cast<float>(
                    values[idx_vol.first * stride]);
                return PWROWG_NAMESPACE::sample(id, timestamp, value);
            });

        } else if (is_cur && valid_channel(idx_vfc)) {
            assert(it->is_sensor_type(sensor_type::current));
            assert(s.voltage_for_current_channel() != nullptr);
            const auto xf = s.volt_per_ampere();
            PWROWG_TRACE("Configuring sample emitter for DAQ voltage channel "
                "\"%s\" (%g A per V).",
                s.voltage_for_current_channel()->channel(), xf);
            this->_make_sample.push_back([id, idx_vfc, xf](
                    _In_ const timestamp timestamp,
                    _In_ const double *values,
                    _In_ const std::size_t stride) {
                assert(values != nullptr);
                const auto value = static_cast<float>(
                    values[idx_vfc.first * stride] * xf);
                return PWROWG_NAMESPACE::sample(id, timestamp, value);
            });
        }
    } /* for (std::size_t i = 0; i < this->_sensors.size(); ++i, ++it) */

    PWROWG_TRACE(_T("Configuring DAQmx task timing."));
    trigger->task.timing(config.timing());

    // Configure the trigger that starts the data acquisition from the sensor.
    // If no user-defined trigger is given, tell the task to start immediately.
    if (trigger->trigger != nullptr) {
        PWROWG_TRACE(_T("Configuring DAQmx trigger."));
        trigger->task.trigger(*trigger->trigger);

    } else {
        PWROWG_TRACE(_T("Configuring DAQmx to start acquisition immediately."));
        throw_if_daqmx_failed(detail::daqmx_library::instance()
            ._DAQmxDisableStartTrig(trigger->task));
    }

    // Install a callback receiving the data.
    const auto chunk = (std::max)(config.samples() / config.reads(),
        static_cast<std::size_t>(1));
    this->_buffer.resize(chunk * channels.size());
    trigger->task.on_sample(chunk, [this](_In_ daqmx_task& task,
            const daqmx_sample_event_type, _In_ const uInt32 cnt) {
        const auto read = task.read(this->_buffer.data(), this->_buffer.size(),
            cnt, false);
        auto& timestamp = this->_trigger._impl->trigger_timestamp;

        this->_samples.clear();
        this->_samples.reserve(read * this->_make_sample.size());

        for (std::size_t i = 0; i < read; ++i) {
            for (auto& m : this->_make_sample) {
                this->_samples.push_back(m(
                    timestamp,
                    this->_buffer.data() + i,
                    this->_make_sample.size()));
            }

            timestamp += cnt * this->_trigger._impl->period;
        }

        sensor_array_impl::callback(this->_owner, this->_samples.data(),
            this->_samples.size());

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
