// <copyright file="hmc8015_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::from_descriptions
 */
template<class TInput>
TInput PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::from_descriptions(
        _In_ list_type& dst,
        _In_ std::size_t index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const configuration_type& config) {
    auto retval = move_front_if(begin, end, is_hmc8015_sensor);

    for (auto it = begin; it != retval; ++it) {
        dst.emplace_back(it->path(), index++, config);
    }

    return retval;
}
