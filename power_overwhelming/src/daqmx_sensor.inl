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
    : _owner(owner),
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        _task(guid::create().to_string<char>()),
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
        _trigger(config.trigger()) {
    typedef sensor_description_builder builder_type;
    typedef daqmx_sensor_definition private_type;
    assert(this->_trigger._impl != nullptr);
    auto trigger = this->_trigger._impl;

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    assert(this->_task);

    // Note: we need to keep track of the channels that have already been
    // activated, because voltage and current channels might be used
    // individually and as a computed power channel. The lambda returns
    // the index of the channel in 'channels' and whether it was newly added
    // to the list and should therefore be added to the DAQmx task.
    std::vector<std::string> channels;
    const auto channel_index = [&channels](const auto *channel, auto& sit) {
        constexpr auto invalid = (std::numeric_limits<std::size_t>::max)();
        if (channel == nullptr) {
            PWROWG_TRACE(_T("Ignoring invalid channel."));
            return std::make_pair(invalid, false);
        }

        auto c = PWROWG_NAMESPACE::convert_string<wchar_t>(channel->channel());
        if (!contains(sit->path(), c.c_str(), true)) {
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

    for (auto it = begin; it != end; ++it, ++index) {
        assert(it != end);
        const auto& s = *builder_type::private_data<private_type>(*it);

        // Check whether a channel is available.
        const auto idx_cur = channel_index(s.current_channel(), it);
        const auto idx_pow = channel_index(s.power_channel(), it);
        const auto idx_vol = channel_index(s.voltage_channel(), it);
        const auto idx_vfc = channel_index(s.voltage_for_current_channel(), it);

        // Check what the sensor is measuring.
        const auto is_cur = it->is_sensor_type(sensor_type::current);
        const auto is_pow = it->is_sensor_type(sensor_type::power);
        const auto is_vol = it->is_sensor_type(sensor_type::voltage);

        // Add all active channels to the task.
        if (idx_cur.second && (is_cur || is_pow)) {
            assert(valid_channel(idx_cur));
            assert(s.current_channel() != nullptr);
            this->_task += *s.current_channel();
        }

        if (idx_pow.second && is_pow) {
            assert(valid_channel(idx_pow));
            assert(s.power_channel() != nullptr);
            this->_task += *s.power_channel();
        }

        if (idx_vol.second && (is_vol || is_pow)) {
            assert(valid_channel(idx_vol));
            assert(s.voltage_channel() != nullptr);
            this->_task += *s.voltage_channel();
        }

        if (idx_vfc.second && (is_cur || is_pow)) {
            assert(valid_channel(idx_vfc));
            assert(s.voltage_for_current_channel() != nullptr);
            this->_task += *s.voltage_for_current_channel();
        }

        // Install sample generators for all sensors. The sampling callback will
        // use these to interpret the numbers in the DAQmx buffer.
        if (is_pow && valid_channel(idx_cur) && (valid_channel(idx_vol))) {
            assert(it->is_sensor_type(sensor_type::power));
            assert(s.voltage_channel() != nullptr);
            assert(s.current_channel() != nullptr);
            PWROWG_TRACE("Configuring sample generator for DAQ channels \"%s\" "
                "(voltage) and \"%s\" (current) used by sensor %zu.",
                s.voltage_channel()->channel(), s.current_channel()->channel(),
                index);
            this->_make_sample.push_back([index, idx_cur, idx_vol](
                    _In_ const timestamp timestamp,
                    _In_ const double *values,
                    _In_ const std::size_t stride) {
                assert(values != nullptr);
                const auto voltage = values[idx_vol.first * stride];
                const auto current = values[idx_cur.first * stride];
                const auto value = static_cast<float>(voltage * current);
                return PWROWG_NAMESPACE::sample(index, timestamp, value);
            });

        } else if (is_pow && valid_channel(idx_vfc) && (valid_channel(idx_vol))) {
            assert(it->is_sensor_type(sensor_type::power));
            assert(s.voltage_channel() != nullptr);
            assert(s.voltage_for_current_channel() != nullptr);
            const auto xf = s.volt_per_ampere();
            PWROWG_TRACE("Configuring sample generator for DAQ channels \"%s\" "
                "(voltage) and \"%s\" (%g A per V) used by sensor %zu.",
                s.voltage_channel()->channel(),
                s.voltage_for_current_channel()->channel(),
                xf, index);
            this->_make_sample.push_back([index, idx_vfc, idx_vol, xf](
                    _In_ const timestamp timestamp,
                    _In_ const double *values,
                    _In_ const std::size_t stride) {
                assert(values != nullptr);
                const auto voltage = values[idx_vol.first * stride];
                const auto current = values[idx_vfc.first * stride] * xf;
                const auto value = static_cast<float>(voltage * current);
                return PWROWG_NAMESPACE::sample(index, timestamp, value);
            });

        } else if (is_cur && valid_channel(idx_cur)) {
            assert(it->is_sensor_type(sensor_type::current));
            assert(s.current_channel() != nullptr);
            PWROWG_TRACE("Configuring sample generator for DAQ current channel "
                "\"%s\" used by sensor %zu.", s.current_channel()->channel(),
                index);
            this->_make_sample.push_back([index, idx_cur](
                    _In_ const timestamp timestamp,
                    _In_ const double *values,
                    _In_ const std::size_t stride) {
                assert(values != nullptr);
                const auto value = static_cast<float>(
                    values[idx_cur.first * stride]);
                return PWROWG_NAMESPACE::sample(index, timestamp, value);
            });

        } else if (is_pow && valid_channel(idx_pow)) {
            assert(it->is_sensor_type(sensor_type::power));
            assert(s.power_channel() != nullptr);
            PWROWG_TRACE("Configuring sample generator for DAQ power channel "
                "\"%s\" used by sensor %zu.", s.power_channel()->channel(),
                index);
            this->_make_sample.push_back([index, idx_pow](
                    _In_ const timestamp timestamp,
                    _In_ const double *values,
                    _In_ const std::size_t stride) {
                assert(values != nullptr);
                const auto value = static_cast<float>(
                    values[idx_pow.first * stride]);
                return PWROWG_NAMESPACE::sample(index, timestamp, value);
            });

        } else if (is_vol && valid_channel(idx_vol)) {
            assert(it->is_sensor_type(sensor_type::voltage));
            assert(s.voltage_channel() != nullptr);
            PWROWG_TRACE("Configuring sample generator for DAQ voltage channel "
                "\"%s\" used by sensor %zu.", s.voltage_channel()->channel(),
                index);
            this->_make_sample.push_back([index, idx_vol](
                    _In_ const timestamp timestamp,
                    _In_ const double *values,
                    _In_ const std::size_t stride) {
                assert(values != nullptr);
                const auto value = static_cast<float>(
                    values[idx_vol.first * stride]);
                return PWROWG_NAMESPACE::sample(index, timestamp, value);
            });

        } else if (is_cur && valid_channel(idx_vfc)) {
            assert(it->is_sensor_type(sensor_type::current));
            assert(s.voltage_for_current_channel() != nullptr);
            const auto xf = s.volt_per_ampere();
            PWROWG_TRACE("Configuring sample generator for DAQ voltage channel "
                "\"%s\" (%g A per V) used by sensor %zu.",
                s.voltage_for_current_channel()->channel(), xf, index);
            this->_make_sample.push_back([index, idx_vfc, xf](
                    _In_ const timestamp timestamp,
                    _In_ const double *values,
                    _In_ const std::size_t stride) {
                assert(values != nullptr);
                const auto value = static_cast<float>(
                    values[idx_vfc.first * stride] * xf);
                return PWROWG_NAMESPACE::sample(index, timestamp, value);
            });
        }
    } /* for (std::size_t i = 0; i < this->_sensors.size(); ++i, ++it) */

    PWROWG_TRACE(_T("Configuring DAQmx task timing."));
    this->_task.timing(config.timing());

    {
        // Note: the following cast should never fail because implicit timing
        // are not allowed for DAQmx-based sensors. If the cast fails, it is
        // a fatal error.
        auto& timing = dynamic_cast<const daqmx_sample_clock_timing&>(
            config.timing());
        this->_period = decltype(this->_period)(1.0 / timing.rate());
    }

    // Configure the trigger that starts the data acquisition from the sensor.
    // If no user-defined trigger is given, tell the task to start immediately
    // by disabling th start trigger.
    if (trigger->trigger != nullptr) {
        PWROWG_TRACE(_T("Configuring DAQmx trigger."));
        this->_task += daqmx_voltage_channel(trigger->trigger->source())
            .min_value(trigger->external_range.first)
            .max_value(trigger->external_range.second);
        this->_task.trigger(*trigger->trigger);

    } else {
        PWROWG_TRACE(_T("Configuring DAQmx to start acquisition immediately."));
        throw_if_daqmx_failed(detail::daqmx_library::instance()
            ._DAQmxDisableStartTrig(this->_task));
    }

    // Install a callback receiving the data. This callback will read as many
    // values as available from the DAQ and use the generator functions
    // installed above to generate the per-sensor samples.
    const auto chunk = (std::max)(config.samples() / config.reads(),
        static_cast<std::size_t>(1));
    this->_buffer.resize(chunk * channels.size());
    this->_task.on_sample(chunk, [this](_In_ daqmx_task& task,
            const daqmx_sample_event_type, _In_ const uInt32 cnt) {
        assert(this->_trigger._impl != nullptr);
        auto& trigger = *this->_trigger._impl;

        // Tell everyone we are busy working on the 'trigger' and register a
        // cleanup handler to be invoked when the scope is left.
        atomic_set(trigger.state, sensor_trigger_state::busy);
        pwrowg_on_exit([&trigger](void) {
            atomic_unset(trigger.state, sensor_trigger_state::busy);
        });

        // Read the sample data. This must always happen, even if the sensor is
        // not running, in order to ensure a consistent increment of the
        // timestamp. While the sensor is running, samples are generated from
        // the raw readings and delivered to the sensor callback.
        try {
            const auto read = task.read(
                this->_buffer.data(),
                this->_buffer.size(),
                cnt,
                false);

            if ((trigger.state & sensor_trigger_state::running)
                    == sensor_trigger_state::running) {
                auto timestamp = trigger.trigger_timestamp;
                this->_samples.clear();
                this->_samples.reserve(read * this->_make_sample.size());

                for (std::size_t i = 0; i < read; ++i) {
                    for (auto& m : this->_make_sample) {
                        this->_samples.push_back(m(
                            timestamp,
                            this->_buffer.data() + i,
                            this->_make_sample.size()));
                    }

                    // TODO: Could _period be that small that the timestamp never advances?
                    timestamp += this->_period;
                }

                sensor_array_impl::callback(
                    this->_owner,
                    this->_samples.data(),
                    this->_samples.size());
                PWROWG_TRACE(_T("The samples from the DAQ have been ")
                    _T("delivered."));
            }

            // Always update the timestamp, even if we have not delivered
            // anything to the sensor callback.
            trigger.trigger_timestamp += read * this->_period;
        } catch (...) {
            // Note: The callback can effectively only fail if the read on the
            // task fails. In this case, the sequence of consecutive samples is
            // broken, which means that we cannot compute the next timestamp.
            // Therefore, all errors in the daqmx_sensor are fatal.
            if (check_all(trigger.state, sensor_trigger_state::armed)) {
                assert(trigger.when_failed != nullptr);
                trigger.when_failed(std::current_exception(),
                    trigger.when_failed_context);
            }

            // We do not want to rethrow here if the task is invalid, etc.
            this->_task.try_stop();
        }

        return 0;
    });

    // Register a handler that handles the completion of the task.
    this->_task.on_done([trigger](const daqmx_task&, const int32) {
        assert(trigger != nullptr);

        // Clear the armed flag to mark the acquisition as finished.
        if (atomic_try_unset(trigger->state, sensor_trigger_state::armed)) {
            // If the trigger was armed, the sensor was manually triggered via
            // a daqmx_sensor_trigger. In this case, there must be a completion
            // callback that needs to be invoked now.
            assert(trigger->when_done != nullptr);
            trigger->when_done(trigger->when_done_context);

            // If the sensor is still running, re-arm the trigger.
            if (check_all(trigger->state, sensor_trigger_state::running)) {
                atomic_set(trigger->state, sensor_trigger_state::armed);
            }
        }

        return 0;
    });
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
}
