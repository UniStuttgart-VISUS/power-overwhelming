// <copyright file="usb_pd_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::from_descriptions
 */
template<class TInput>
TInput PWROWG_DETAIL_NAMESPACE::usb_pd_sensor::from_descriptions(
        _In_ list_type& dst,
        _In_ std::size_t index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const configuration_type& config) {
    auto retval = move_front_if(begin, end, is_usb_pd_sensor);

    auto d = std::distance(begin, retval);

    // Group the sensors by their device ID.
    std::sort(begin, retval,
        [](const sensor_description& lhs, const sensor_description& rhs) {
            return (compare(lhs.id(), rhs.id()) < 0);
        });

    for (auto it = begin; it != retval; /* [sic] */) {
        // At this point, there are one or two sensors from the same device.
        std::vector<sensor_type> types;
        auto sensor_index = [&types, index](const sensor_type type) {
            for (std::size_t i = 0; i < types.size(); ++i) {
                if (types[i] == type) {
                    return index + i;
                }
            }
            return invalid_index;
        };
        auto port = it->path();

        // Determine the types of all sensors on the same device.
        types.reserve(2);
        while ((it != retval) && equals(it->path(), port)) {
            types.push_back(pwr_volt_cur_mask(*it++));
        }

        // Generate sensor IDs for the active sources.
        const auto voltage = sensor_index(sensor_type::voltage);
        const auto current = sensor_index(sensor_type::current);

        dst.emplace_back(port, voltage, current);
    }

    return retval;
}
