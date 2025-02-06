// <copyright file="tinkerforge_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::descriptions
 */
template<class TOutput>
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::descriptions(
        _In_ TOutput oit, _In_ const configuration_type& config) {
    typedef tinkerforge_bricklet bricklet_type;

    std::vector<bricklet_type> bricklets;
    auto builder = sensor_description_builder::create()
        .with_vendor(L"Tinkerforge")
        .with_editable_type(sensor_type::cpu
            | sensor_type::external
            | sensor_type::gpu
            | sensor_type::system)
        .produces(reading_type::floating_point);

    for (std::size_t i = 0; i < config.count_end_points(); ++i) {
        auto& end_point = config.end_points()[i];

        try {
            tinkerforge_scope scope(end_point.name(), end_point.port());

            bricklets.clear();
            scope.copy_bricklets(
                std::back_inserter(bricklets),
                [](const bricklet_type& b) { return (b.device_type()
                    == VOLTAGE_CURRENT_V2_DEVICE_IDENTIFIER); },
                std::chrono::milliseconds(config.timeout()));

            for (auto& b : bricklets) {
                *oit++ = specialise(builder,
                    scope,
                    end_point,
                    b,
                    sensor_type::current,
                    reading_unit::ampere).build();
                *oit++ = specialise(builder,
                    scope,
                    end_point,
                    b,
                    sensor_type::voltage,
                    reading_unit::volt).build();
                *oit++ = specialise(builder,
                    scope,
                    end_point,
                    b,
                    sensor_type::power,
                    reading_unit::watt).build();
            }
        } catch (tinkerforge_exception) {
            // If the connection failed in the scope, we do not have any
            // bricklets from the specific host. This is typically caused
            // by brickd not running on 'end_point'. At this point, the
            // resolution is to just ignore the end point.
        }
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::from_descriptions
 */
template<class TOutput, class TInput>
TInput PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::from_descriptions(
        _In_ TOutput oit,
        _In_ std::size_t index,
        _In_ const TInput begin,
        _In_ const TInput end) {
    typedef sensor_description_builder builder_type;

    // Find out which are the TF sensors.
    auto retval = move_front_if(begin, end, [](const sensor_description& d) {
        return starts_with(d.name(), L"Tinkerforge/");
    });

    // Group the sensors by their brick daemon and bricklet. Sensors on the same
    // bricklet are sorted to match the order in the constructor.
    std::sort(begin, retval,
            [](const sensor_description& lhs, const sensor_description& rhs) {
        auto pdl = builder_type::private_data<tinkerforge_scope>(lhs);
        auto pdr = builder_type::private_data<tinkerforge_scope>(rhs);

        // First of all, group by the brick daemon.
        auto retval = static_cast<const IPConnection *>(*pdl)
            - static_cast<const IPConnection *>(*pdr);

        // If on the same daemon, group by bricklet.
        if (retval == 0) {
            retval = compare(lhs.id(), rhs.id());
        }

        return (retval < 0);
    });

    for (auto it = begin; it != retval; ++it) {
        // At this point, there are always up to three sensors that come from the
        // same bricklet. We group these into a single sensor instance.
        auto scope = *builder_type::private_data<tinkerforge_scope>(*it);
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

        auto sensor = std::make_shared<tinkerforge_sensor>(scope, uid,
            power, voltage, current);
        // TODO: sensor->configure!
        *oit++ = sensor;
    }

    return retval;
}
