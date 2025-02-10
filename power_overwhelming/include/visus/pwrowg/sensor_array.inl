// <copyright file="sensor_array.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_NAMESPACE::sensor_array::for_matches
 */
template<class TPredicate>
PWROWG_NAMESPACE::sensor_array
PWROWG_NAMESPACE::sensor_array::for_matches(
        _In_ const sensor_array_configuration& config,
        _In_ const TPredicate predicate) {
    std::vector<sensor_description> descs;
    descs.resize(all_descriptions(nullptr, 0, config));

    // Count sensors, but account for dynamic sensors being detached
    // betweeen the calls.
    auto cnt = all_descriptions(descs.data(), descs.size(), config);
    auto end = (cnt < descs.size()) ? descs.begin() + cnt : descs.end();

    // Select the sensors matching the predicate and create the array.
    end = std::partition(descs.begin(), end, predicate);
    cnt = std::distance(descs.begin(), end);

    return sensor_array(descs.data(), cnt);
}
