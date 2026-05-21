// <copyright file="igcl_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::igcl_sensor::from_descriptions
 */
template<class TInput>
TInput PWROWG_DETAIL_NAMESPACE::igcl_sensor::from_descriptions(
        _In_ list_type& dst,
        _In_ std::size_t index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config) {
    auto retval = move_front_if(begin, end, is_igcl_sensor);

    for (auto it = begin; it != retval; ++it) {
        dst.emplace_back(it->path(), index++);
        dst.back().time_sync();
    }

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::igcl_sensor::make_timestamp
 */
template<class TType>
std::enable_if_t<std::is_floating_point_v<TType>, PWROWG_NAMESPACE::timestamp>
PWROWG_DETAIL_NAMESPACE::igcl_sensor::make_timestamp(_In_ const TType value) {
    // Note: Adding the '_offset' is a major hazard here as this is not
    // following the documentation. We think this is a bug in IGCL
    // (documentation or cod). If it is fixed in code, the following will
    // produce wrong results that are way off into the future. The assertion
    // should catch this situation in debug builds.
    assert(value < timestamp::now() - std::chrono::hours(1));
    const auto d = std::chrono::duration<TType>(value) + this->_offset;
    return timestamp::from_duration(d);
}
