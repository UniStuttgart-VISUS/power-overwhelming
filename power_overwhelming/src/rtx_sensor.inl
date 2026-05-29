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
    // are grouped. The path of the sensors are the VISA paths to the
    // instruments.
    std::sort(begin, retval, [](const desc_type& lhs, const desc_type& rhs) {
        return (lhs.path() < rhs.path());
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
    : _index(index),
        _owner(owner),
        _trigger_index((std::numeric_limits<std::size_t>::max)()) {
    typedef sensor_description_builder builder_type;

#if defined(POWER_OVERWHELMING_WITH_VISA)
    assert(this->_owner != nullptr);

    this->_trigger = config.trigger();
    assert(this->_trigger);
    assert(this->_trigger._impl != nullptr);

    rtx_instrument::channel_type next_math = 0;
    const auto next_instrument = [this](const sensor_description& d) {
        if (this->_instruments.empty()) {
            return true;
        }

        auto p = PWROWG_NAMESPACE::convert_string<char>(d.path());
        return !equals(p, this->_instruments.back().path(), true);
    };

    for (auto it = begin; it != end; ++it) {
        if (next_instrument(*it)) {
            // We found an instrument we do not yet know, so we connect to it
            // and configure it for use with the sensor.
            PWROWG_TRACE(L"Connecting to instrument \"%s\".", it->path());
            this->_instruments.emplace_back(it->path(), config.timeout());
            auto& i = this->_instruments.back();

            PWROWG_TRACE("Reset instrument \"%s\" before creating sensors.",
                i.path());
            i.reset(rtx_instrument_reset::reset | rtx_instrument_reset::status);

            if (config.configure_instruments()) {
                PWROWG_TRACE("Applying the user-provided global instrument "
                    "configuration to \"%s\".", i.path());
                config.instrument_configuration().apply(i);
            }

            PWROWG_TRACE("Setting the timeout of \"%s\" to %u ms.", i.path(),
                config.timeout());
            i.timeout(config.timeout());

            PWROWG_TRACE("Synchronising the clock of \"%s\" with the current "
                "UTC.", i.path());
            i.synchronise_clock(true);

            PWROWG_TRACE("Applying ESE filter for OPC to instrument \"%s\".",
                i.path());
            i.event_status(visa_event_status::operation_complete);

            //PWROWG_TRACE("Configurating \"%s\" to deliver trigger events to "
            //    "the queue.", i.path());
            //i.enable_event(VI_EVENT_TRIG);

            PWROWG_TRACE("Moving reference point of \"%s\" to the left.",
                i.path());
            i.reference_position(rtx_reference_point::left);

            if (this->_trigger._impl->daisy_chain > 0.0f) {
                PWROWG_TRACE(_T("Setting up daisy chain for trigger."));
                i.trigger_output(rtx_trigger_output::pulse);

                if (equals(this->_trigger._impl->path, i.path(), true)) {
                    this->_trigger_index = this->_instruments.size() - 1;
                    PWROWG_TRACE("\"%s\" at position %zu is the triggering "
                        "instrument.", i.path(), this->_trigger_index);
                } else {
                    PWROWG_TRACE("Configuring \"%s\" to use the external "
                        "trigger.", i.path());
                    i.trigger(rtx_trigger::external_edge(
                        this->_trigger._impl->daisy_chain));
                }
            }

            PWROWG_TRACE("Configuring acquisition for instrument \"%s\" to "
                "match the single acquisition mode expected by the rtx_sensor.",
                i.path());
            i.acquisition(rtx_acquisition()
                .enable_automatic_points()
                .count(1)
                .segmented(true));

            PWROWG_TRACE("Making sure that \"%s\" is not in an error state "
                "after applying all configuration changes.", i.path());
            i.throw_on_system_error();
        }
        assert(!this->_instruments.empty());
        auto& instrument = this->_instruments.back();

        auto sd = builder_type::private_data<rtx_sensor_definition>(*it);
        assert(sd != nullptr);
        auto& cur = sd->current_channel();
        auto& vol = sd->voltage_channel();

        if (it->is_sensor_type(sensor_type::current)) {
            instrument.channel(cur);

            std::string name("CH");
            name += std::to_string(cur.channel());
            this->_channels.push_back(std::move(name));

        } else if (it->is_sensor_type(sensor_type::power)) {
            std::string expr("CH");
            expr += std::to_string(cur.channel());
            expr += "*CH";
            expr += std::to_string(vol.channel());
            instrument.expression(++next_math, expr.c_str(), "VA");

            std::string name("MATH");
            name += std::to_string(next_math);
            this->_channels.push_back(std::move(name));

        } else {
            assert(it->is_sensor_type(sensor_type::voltage));
            instrument.channel(vol);

            std::string name("CH");
            name += std::to_string(vol.channel());
            this->_channels.push_back(std::move(name));
        }
    }
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
}
