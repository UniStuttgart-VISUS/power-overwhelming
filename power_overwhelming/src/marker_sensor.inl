// <copyright file="marker_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::marker_sensor::from_descriptions
 */
template<class TInput>
TInput PWROWG_DETAIL_NAMESPACE::marker_sensor::from_descriptions(
        _In_ list_type& dst,
        _In_ std::size_t index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config) {
    assert(owner != nullptr);
    auto retval = move_front_if(begin, end, is_marker_sensor);

    if (begin != retval) {
        dst.emplace(index, owner, config);
    }

    return retval;
}
