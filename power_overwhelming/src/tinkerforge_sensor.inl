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
        _In_ std::size_t index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const configuration_type& config) {
    typedef sensor_description_builder builder_type;

    // Find out which are the TF sensors.
    auto retval = move_front_if(begin, end, is_tinkerforge_sensor);

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

    // Generate a shared configuration object to prevent a copy for each sensor.
    auto shared_config = std::make_shared<configuration_type>(config);

    for (auto it = begin; it != retval; ++it) {
        // At this point, there are always up to three sensors that come from the
        // same bricklet. We group these into a single sensor instance.
        auto scope = builder_type::private_data<tinkerforge_scope>(*it);
        std::array<sensor_type, 3> types {
            sensor_mask(*it),
            sensor_type::unknown,
            sensor_type::unknown
        };
        auto active = [&types](const sensor_type type) {
            return (std::find(types.begin(), types.end(), type) != types.end());
        };
        auto uid = it->id();

        auto jt = it;
        if ((++jt != retval) && same_bricklet(*it, *jt)) {
            ++it;
            types[1] = sensor_mask(*jt);

            if ((++jt != retval) && same_bricklet(*it, *jt)) {
                ++it;
                types[2] = sensor_mask(*jt);
            }
        }

        // Generate sensor IDs for the active sources.
        auto power = active(sensor_type::power) ? index++ : invalid_index;
        auto voltage = active(sensor_type::voltage) ? index++ : invalid_index;
        auto current = active(sensor_type::current) ? index++ : invalid_index;

        dst.emplace_back(*scope, uid, shared_config, power, voltage, current);
        dst.back().configuration(config.averaging(),
            config.voltage_conversion_time(),
            config.current_conversion_time());
    }

    return retval;
}
