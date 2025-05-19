// <copyright file="msr_sensor.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * PWROWG_DETAIL_NAMESPACE::msr_sensor::from_descriptions
 */
template<class TInput>
TInput PWROWG_DETAIL_NAMESPACE::msr_sensor::from_descriptions(
        _In_ list_type& dst,
        _In_ sample::source_type index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config) {
    typedef sensor_description_builder builder_type;

    // Find out which are the EMI sensors.
    auto retval = move_front_if(begin, end, is_msr_sensor);
#if (defined(DEBUG) || defined(_DEBUG))
    auto _rem = std::distance(begin, retval);
#endif /* (defined(DEBUG) || defined(_DEBUG)) */

    // Group the sensors by their device, which is identified by the path.
    std::sort(begin, retval,
        [](const sensor_description& lhs, const sensor_description& rhs) {
            return (compare(lhs.path(), rhs.path(), true) < 0);
        });

    for (auto it = begin; it != retval; /* [sic] */) {
        std::vector<register_identifier> registers;
        auto path = it->path();

        while ((it != retval) && equals(it->path(), path)) {
            auto r = builder_type::private_data<register_identifier>(*it++);
            if (r != nullptr) {
                registers.push_back(*r);
            }
#if (defined(DEBUG) || defined(_DEBUG))
            --_rem;
#endif /* (defined(DEBUG) || defined(_DEBUG)) */
        }

        const auto used_indices = registers.size();
        dst.emplace_back(path, std::move(registers), index);
        index += used_indices;
    }

#if (defined(DEBUG) || defined(_DEBUG))
    assert(_rem == 0);
#endif /* (defined(DEBUG) || defined(_DEBUG)) */
    return retval;
}
