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
        _owner(owner) {
    typedef sensor_description_builder builder_type;

#if defined(POWER_OVERWHELMING_WITH_VISA)
    assert(this->_owner != nullptr);
    rtx_instrument::channel_type next_math = 0;
    const auto next_instrument = [this](const sensor_description& d) {
        if (this->_instruments.empty()) {
            return true;
        }

        auto p = PWROWG_NAMESPACE::convert_string<char>(d.path());
        return (p != this->_instruments.back().path());
    };

    for (auto it = begin; it != end; ++it) {
        if (next_instrument(*it)) {
            PWROWG_TRACE(L"Connecting to instrument \"%s\".", it->path());
            this->_instruments.emplace_back(it->path(), config.timeout());

            PWROWG_TRACE("Reset instrument \"%s\" before creating sensors.",
                this->_instruments.back().path());
            this->_instruments.back().reset();

            PWROWG_TRACE("Setting the timeout of \"%s\" to %u ms.",
                this->_instruments.back().path(), config.timeout());
            this->_instruments.back().timeout(config.timeout());

            PWROWG_TRACE("Synchronising the clock of \"%s\" with the current "
                "UTC.", this->_instruments.back().path());
            this->_instruments.back().synchronise_clock(true);

            if (config.configure_instruments()) {
                PWROWG_TRACE("Applying the global instrument configuration to "
                    "\"%s\".", this->_instruments.back().path());
                config.instrument_configuration().apply(
                    this->_instruments.back());
            }
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
