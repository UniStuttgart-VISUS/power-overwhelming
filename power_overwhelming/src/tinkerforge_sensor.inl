// <copyright file="tinkerforge_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::from_descriptions
 */
template<class TInput>
TInput PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::from_descriptions(
        _In_ list_type& dst,
        _In_ sample::source_type index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config) {
    typedef sensor_description_builder builder_type;
    assert(owner != nullptr);

    // Find out which are the TF sensors.
    auto retval = move_front_if(begin, end, is_tinkerforge_sensor);
#if (defined(DEBUG) || defined(_DEBUG))
    auto _rem = std::distance(begin, retval);
#endif /* (defined(DEBUG) || defined(_DEBUG)) */

    // Group the sensors by their brick daemon and bricklet. Sensors on the same
    // bricklet are sorted to match the order in the constructor.
    std::sort(begin, retval,
            [](const sensor_description& lhs, const sensor_description& rhs) {
        auto pdl = *builder_type::private_data<tinkerforge_scope>(lhs);
        auto pdr = *builder_type::private_data<tinkerforge_scope>(rhs);

        // First of all, group by the brick daemon.
        auto retval = static_cast<const IPConnection *>(pdl)
            - static_cast<const IPConnection *>(pdr);

        // If on the same daemon, group by bricklet.
        if (retval == 0) {
            retval = compare(lhs.id(), rhs.id());
        }

        return (retval < 0);
    });

    for (auto it = begin; it != retval; /* [sic] */) {
        // At this point, there are always up to three sensors that come from the
        // same bricklet. We group these into a single sensor instance.
        auto scope = builder_type::private_data<tinkerforge_scope>(*it);
        std::vector<sensor_type> types;
        auto sensor_index = [&types, index](const sensor_type type) {
            for (std::size_t i = 0; i < types.size(); ++i) {
                if (types[i] == type) {
                    return index + i;
                }
            }
            return invalid_index;
        };
        auto uid = it->path();

        // Determine the types of all sensors on the same bricklet.
        types.reserve(3);
        for (auto jt = it; it != retval && same_bricklet(*it, *jt);) {
            types.push_back(pwr_volt_cur_mask(*it++));
#if (defined(DEBUG) || defined(_DEBUG))
            --_rem;
#endif /* (defined(DEBUG) || defined(_DEBUG)) */
        }

        // Generate sensor IDs for the active sources.
        const auto power = sensor_index(sensor_type::power);
        const auto voltage = sensor_index(sensor_type::voltage);
        const auto current = sensor_index(sensor_type::current);

        index += types.size();
        dst.emplace_back(*scope, uid, owner, power, voltage, current);
        dst.back().configuration(config.averaging(),
            config.voltage_conversion_time(),
            config.current_conversion_time());
    }

#if (defined(DEBUG) || defined(_DEBUG))
    assert(_rem == 0);
#endif /* (defined(DEBUG) || defined(_DEBUG)) */
    return retval;
}
