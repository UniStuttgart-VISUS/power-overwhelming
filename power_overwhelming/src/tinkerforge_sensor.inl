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
                    end_point,
                    b,
                    tinkerforge_sensor_source::current,
                    sensor_type::current,
                    reading_unit::ampere).build();
                *oit++ = specialise(builder,
                    end_point,
                    b,
                    tinkerforge_sensor_source::voltage,
                    sensor_type::voltage,
                    reading_unit::volt).build();
                *oit++ = specialise(builder,
                    end_point,
                    b,
                    tinkerforge_sensor_source::power,
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
    auto retval = move_front_if(begin, end, [](const sensor_description& d) {
        return starts_with(d.name(), L"Tinkerforge/");
    });

    // TODO

    return retval;
}
