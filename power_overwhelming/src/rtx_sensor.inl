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

    // Sort the RTA/RTB sensors such that sensors on the same instrument
    // are grouped. The paths of the sensors are the VISA paths to the
    // instruments.
    std::sort(begin, retval, [](const desc_type& lhs, const desc_type& rhs) {
        assert(lhs.path() != nullptr);
        assert(rhs.path() != nullptr);

        const auto d = ::wcscmp(lhs.path(), rhs.path());
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
        : _index(index), _owner(owner) {
    typedef sensor_description_builder builder_type;
    typedef sensor_description desc_type;

#if defined(POWER_OVERWHELMING_WITH_VISA)
    assert(this->_owner != nullptr);

    this->_trigger = config.trigger();
    assert(this->_trigger);
    assert(this->_trigger._impl != nullptr);
    auto& instruments = this->_trigger._impl->instruments;

    rtx_instrument::channel_type next_math = 0;
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

        PWROWG_TRACE(L"Connecting to instrument \"%s\".", b->path());
        instruments.emplace_back(b->path(), icfg.timeout());
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
            icfg.channel(c.second);
        }

        icfg.acquisition(rtx_acquisition()
            .enable_automatic_points()
            .count(1)
            .segmented(true));

        icfg.reference_position(rtx_reference_point::left);

        // TODO: Trigger

        PWROWG_TRACE("Reset \"%s\" before creating sensors.", i.path());
        i.reset(rtx_instrument_reset::reset | rtx_instrument_reset::status);

        PWROWG_TRACE("Applying configuration to instrument \"%s\".", i.path());
        icfg.apply(i);

        PWROWG_TRACE("Synchronising the clock of \"%s\" with the current UTC.",
            i.path());
        i.synchronise_clock(true);

        PWROWG_TRACE("Configuring events for instrument \"%s\".", i.path());
        i.event_status(visa_event_status::operation_complete);
        i.service_request_status(visa_status_byte::master_status
            | visa_status_byte::message_available);
        i.enable_event(VI_EVENT_SERVICE_REQ, VI_QUEUE);

        PWROWG_TRACE("Making sure that \"%s\" is not in an error state "
            "after applying all configuration changes.", i.path());
        i.operation_complete_async();
        i.wait_status(visa_event_status::operation_complete);
        i.throw_on_system_error();

            //if (this->_trigger._impl->daisy_chain > 0.0f) {
            //    PWROWG_TRACE(_T("Setting up daisy chain for trigger."));
            //    i.trigger_output(rtx_trigger_output::pulse);

            //    if (equals(this->_trigger._impl->path, i.path(), true)) {
            //        assert(!instruments.empty());
            //        const auto idx_trig = instruments.size() - 1;
            //        this->_trigger._impl->trigger_instrument = idx_trig;
            //        PWROWG_TRACE("\"%s\" at position %zu is the triggering "
            //            "instrument.", i.path(), idx_trig);

            //    } else {
            //        const auto level = this->_trigger._impl->daisy_chain;
            //        PWROWG_TRACE("Configuring \"%s\" to use the external "
            //            "trigger at %f V.", i.path(), level);
            //        i.trigger(rtx_trigger::external_edge(level)
            //            .mode(rtx_trigger_mode::normal));
            //    }
            //}

            //if (this->_trigger._impl->trigger != nullptr) {
            //    const auto& path = this->_trigger._impl->path;
            //    PWROWG_TRACE("Path to triggering instrument is \"%s.\".",
            //        path.c_str());

            //    if (path.empty() || equals(path, i.path(), true)) {
            //        PWROWG_TRACE("Configuring \"%s\" to use the trigger "
            //            "provided by the user.", i.path());
            //        i.trigger(*this->_trigger._impl->trigger);
            //    }
            //}
        //}
        //assert(!instruments.empty());
        //auto& instrument = instruments.back();

        //auto sd = builder_type::private_data<rtx_sensor_definition>(*it);
        //assert(sd != nullptr);
        //auto& cur = sd->current_channel();
        //auto& vol = sd->voltage_channel();

        //if (it->is_sensor_type(sensor_type::current)) {
        //    instrument.channel(cur);

        //    std::string name("CH");
        //    name += std::to_string(cur.channel());
        //    this->_channels.push_back(std::move(name));

        //} else if (it->is_sensor_type(sensor_type::power)) {
        //    std::string expr("CH");
        //    expr += std::to_string(cur.channel());
        //    expr += "*CH";
        //    expr += std::to_string(vol.channel());
        //    instrument.expression(++next_math, expr.c_str(), "VA");

        //    std::string name("MATH");
        //    name += std::to_string(next_math);
        //    this->_channels.push_back(std::move(name));

        //} else {
        //    assert(it->is_sensor_type(sensor_type::voltage));
        //    instrument.channel(vol);

        //    std::string name("CH");
        //    name += std::to_string(vol.channel());
        //    this->_channels.push_back(std::move(name));
        //}
    }
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
}
