// <copyright file="rtx_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor::from_descriptions
 */
template<class TInput>
TInput PWROWG_DETAIL_NAMESPACE::rtx_sensor::from_descriptions(
        _In_ list_type& dst,
        _In_ sample::source_type index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config) {
    typedef sensor_description_builder builder_type;
    typedef sensor_description desc_type;
    assert(owner != nullptr);

    // Move the RTA/RTB sensor to the front of the list.
    auto retval = move_front_if(begin, end, is_rtx_sensor);

    // If there is no RTA/RTB-based sensor, bail out directly.
    if (begin == retval) {
        return retval;
    }

    // Sort the RTA/RTB sensors such that sensors on the same instrument
    // are grouped. The paths of the sensors are the VISA paths to the
    // instruments.
    std::sort(begin, retval, [](const desc_type& lhs, const desc_type& rhs) {
        const auto l = lhs.path();
        const auto r = rhs.path();
        assert(l != nullptr);
        assert(r != nullptr);

        const auto d = ::wcscmp(l, r);
        if (d == 0) {
            // If we are on the same device, order the sensors voltage, current
            // and power last.
            auto map = [](const desc_type& d) {
                if (d.is_sensor_type(sensor_type::voltage)) return 0;
                if (d.is_sensor_type(sensor_type::current)) return 1;
                assert(d.is_sensor_type(sensor_type::power));
                return 2;
            };
            return (map(lhs) < map(rhs));

        } else {
            // Otherwise, the VISA path determines the order.
            return (d < 0);
        }
    });

    // Create the sensor, which is always one managing every sensor within
    // [begin, retval[.
    dst.emplace_back(begin, retval, index, owner, config);

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor::rtx_sensor
 */
template<class TIterator>
PWROWG_DETAIL_NAMESPACE::rtx_sensor::rtx_sensor(
        _In_ const TIterator begin,
        _In_ const TIterator end,
        _In_ std::size_t index,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config)
    : _download_retries(config.download_retries()),
        _download_timeout(config.download_timeout()),
        _index(index),
        _owner(owner) {
    typedef sensor_description_builder builder_type;
    typedef sensor_description desc_type;

#if defined(POWER_OVERWHELMING_WITH_VISA)
    assert(this->_owner != nullptr);

    this->_trigger = config.trigger();
    assert(this->_trigger);
    assert(this->_trigger._impl != nullptr);
    auto& instruments = this->_trigger._impl->instruments;

    // Checks whether 'd' is using a different instrument than the last in
    // 'instruments'.
    const auto next_instrument = [&instruments](const sensor_description& d) {
        if (instruments.empty()) {
            return true;
        }

        auto p = PWROWG_NAMESPACE::convert_string<char>(d.path());
        return !equals(p, instruments.back().path(), true);
    };

    for (auto it = begin; it != end; /* [sic] */) {
        // Scan through all sensors on the same instrument. These must be
        // contiguous because we sort it this way.
        auto b = it;
        assert(b != end);

        // Prepare the instrument configuration. This is the base configuration
        // plus everything we need for the sensor to work.
        auto icfg = config.base_configuration();

        const auto timeout = icfg.timeout_or_default();
        PWROWG_TRACE(L"Connecting to instrument \"%s\" with a timeout of "
            "%u ms.", b->path(), timeout);
        instruments.emplace_back(b->path(), timeout);
        assert(!instruments.empty());
        auto& i = instruments.back();

        // Proceed to the next instrument. After the end of the loop, [b, it[
        // is the range of sensors on instrument 'i'. At the same time, we
        // collect the channel configurations and make sure that they are
        // consistently defined for all sensors on the same instrument.
        std::map<rtx_channel::channel_type, rtx_channel> channels;
        const auto collect_channel = [&channels](const rtx_channel& c) {
            auto e = channels.find(c.channel());
            if (e == channels.end()) {
                channels[c.channel()] = c;
            } else if (c != e->second) {
                throw std::invalid_argument("A channel must be identically "
                    "configured when used for multiple sensors.");
            }
        };

        for (; (it != end) && !next_instrument(*it); ++it) {
            if (it->is_sensor_type(sensor_type::voltage)) {
                auto d = builder_type::private_data<rtx_sensor_definition>(*it);
                assert(d != nullptr);
                collect_channel(d->voltage_channel());

            } else if (it->is_sensor_type(sensor_type::current)) {
                auto d = builder_type::private_data<rtx_sensor_definition>(*it);
                assert(d != nullptr);
                collect_channel(d->current_channel());

            } else if (it->is_sensor_type(sensor_type::power)) {
                auto d = builder_type::private_data<rtx_sensor_definition>(*it);
                assert(d != nullptr);
                collect_channel(d->voltage_channel());
                collect_channel(d->current_channel());
            }
        }
        assert(b != it);
        PWROWG_TRACE("Instrument \"%s\" has %zu sensor(s) configured on it.",
            i.path(), std::distance(b, it));
        PWROWG_TRACE("%zu channel(s) are used on instrument \"%s\".",
            channels.size(), i.path());

        // Modify the instrument configuration to match the needs of the sensor.
        for (auto& c : channels) {
            icfg.channel(c.second.state(true));
        }

        {
            // Force to only one segment, regardless of what the user said.
            auto a = icfg.acquisition();
            icfg.acquisition(a.count(1));
        }

        icfg.reference_position(rtx_reference_point::left);

        if (this->_trigger._impl->daisy_chain > 0.0f) {
            PWROWG_TRACE(_T("Setting up daisy chain for trigger."));
            i.trigger_output(rtx_trigger_output::pulse);
        }

        const auto& trig_instr = this->_trigger._impl->path;
        if (trig_instr.empty() || equals(trig_instr, i.path(), true)) {
            assert(!instruments.empty());
            const auto idx_trig = instruments.size() - 1;
            this->_trigger._impl->trigger_instrument = idx_trig;
            PWROWG_TRACE("\"%s\" at position %zu is the triggering instrument.",
                i.path(), idx_trig);

            if (this->_trigger._impl->trigger != nullptr) {
                auto& trigger = *this->_trigger._impl->trigger;
                PWROWG_TRACE("Configuring \"%s\" to use the %u trigger "
                    "provided by the user. The user-defined trigger will be"
                    "forced to normal mode.", i.path(), trigger.type());
                icfg.trigger(trigger.mode(rtx_trigger_mode::normal));

            } else {
                const auto level = (this->_trigger._impl->daisy_chain > 0.0f)
                    ? this->_trigger._impl->daisy_chain
                    : 0.0f;
                PWROWG_TRACE("Setting up an invalid dummy trigger on \"%s\" "
                    "at %fV.", i.path(), level);
                icfg.trigger(rtx_trigger(
                        static_cast<rtx_trigger::input_type>(0),
                        rtx_trigger_type::edge)
                    .mode(rtx_trigger_mode::normal));
            }

        } else {
            const auto level = this->_trigger._impl->daisy_chain;
            PWROWG_TRACE("Configuring \"%s\" to use the external trigger at "
                "%f V.", i.path(), level);
            icfg.trigger(rtx_trigger(5, rtx_trigger_type::edge)
                .external(level)
                .mode(rtx_trigger_mode::normal));
        } /* if (trig_instr.empty() || equals(trig_instr, i.path(), true)) */

        PWROWG_TRACE("Reset \"%s\" with flags 0x%x before creating sensors.",
            i.path(), config.reset_flags());
        i.reset(config.reset_flags());
        i.timeout(timeout);
        i.operation_complete();

        PWROWG_TRACE("Applying configuration to instrument \"%s\".", i.path());
        icfg.apply(i);

        PWROWG_TRACE("Configuring events for instrument \"%s\".", i.path());
        i.event_status(visa_event_status::operation_complete);
        i.service_request_status(visa_status_byte::master_status
            /*| visa_status_byte::message_available*/);
        i.enable_event(VI_EVENT_SERVICE_REQ, VI_QUEUE);

        PWROWG_TRACE("Synchronising the clock of \"%s\" with the current UTC.",
            i.path());
        i.synchronise_clock(true);

        PWROWG_TRACE("Waiting for all changes being applied to \"%s\".",
            i.path());
        i.operation_complete();
        // Note: In contrast to *OPC?, *OPC + *ESR? frequently runs into
        // timeouts when checking the status byte below ...
        //i.operation_complete_async();
        //i.wait_status(visa_event_status::operation_complete);

        PWROWG_TRACE("Making sure that \"%s\" is not in an error state "
            "after applying all configuration changes.", i.path());
        i.throw_on_system_error();

        if (this->_trigger._impl->trigger == nullptr) {
            PWROWG_TRACE("Allocating space for recording manual trigger "
                "timestamp for \"%s\".", i.path());
            this->_trigger._impl->trigger_timestamps.emplace_back(0);

        } else if (this->_trigger._impl->external_trigger) {
            PWROWG_TRACE(_T("Allocating space for recording timestamp of ")
                _T("external trigger."));
            this->_trigger._impl->trigger_timestamps.resize(1);
        }

        PWROWG_TRACE("Creating channel map for instrument \"%s\".", i.path());
        this->_channels.emplace_back();
        auto& ichannels = this->_channels.back();
        for (auto jt = b; jt != it; ++jt) {
            if (jt->is_sensor_type(sensor_type::voltage)) {
                auto d = builder_type::private_data<rtx_sensor_definition>(*jt);
                assert(d != nullptr);
                assert(d->voltage_channel().channel() != 0);
                ichannels.emplace_back(d->voltage_channel().channel());
                PWROWG_TRACE("Channel %u on \"%s\" is a voltage sensor.",
                    ichannels.back().channel, i.path());

            } else if (jt->is_sensor_type(sensor_type::current)) {
                auto d = builder_type::private_data<rtx_sensor_definition>(*jt);
                assert(d != nullptr);
                assert(d->current_channel().channel() != 0);
                ichannels.emplace_back(d->current_channel().channel());
                PWROWG_TRACE("Channel %u on \"%s\" is a current sensor.",
                    ichannels.back().channel, i.path());

            } else if (jt->is_sensor_type(sensor_type::power)) {
                auto d = builder_type::private_data<rtx_sensor_definition>(*jt);
                assert(d != nullptr);
                assert(d->voltage_channel().channel() != 0);
                assert(d->current_channel().channel() != 0);
                ichannels.emplace_back(
                    d->voltage_channel().channel(),
                    d->current_channel().channel());
                PWROWG_TRACE("Channel %u and %u on \"%s\" form a power sensor.",
                    ichannels.back().channel, ichannels.back().current,
                    i.path());
            }
        } /* for (auto jt = b; jt != it; ++jt) */
    }
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
}
